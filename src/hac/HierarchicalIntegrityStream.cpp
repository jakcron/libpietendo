#include <nn/hac/HierarchicalIntegrityStream.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <tc/cli/FormatUtil.h>
#include <fmt/format.h>

nn::hac::HierarchicalIntegrityStream::HierarchicalIntegrityStream() :
	mModuleLabel("nn::hac::HierarchicalIntegrityStream"),
	mBaseStream(),
	mDataStreamBlockSize(0),
	mDataStreamLogicalLength(0),
	mDataStream(),
	mHashCache(),
	mHashCalc(new tc::crypto::Sha256Generator())
{
}

nn::hac::HierarchicalIntegrityStream::HierarchicalIntegrityStream(const std::shared_ptr<tc::io::IStream>& stream, const nn::hac::HierarchicalIntegrityHeader& hash_header) :
	HierarchicalIntegrityStream()
{
	mBaseStream = stream;

	// validate stream properties
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException("nn::hac::HierarchicalIntegrityStream", "stream is null.");
	}
	if (mBaseStream->canRead() == false)
	{
		throw tc::InvalidOperationException("nn::hac::HierarchicalIntegrityStream", "stream does not support reading.");
	}
	if (mBaseStream->canSeek() == false)
	{
		throw tc::InvalidOperationException("nn::hac::HierarchicalIntegrityStream", "stream does not support seeking.");
	}

	// create raw master hash table
	tc::ByteData master_hash_data = tc::ByteData(hash_header.getMasterHashList().size() * sizeof(nn::hac::detail::sha256_hash_t));
	for (size_t i = 0; i < hash_header.getMasterHashList().size(); i++)
	{
		((nn::hac::detail::sha256_hash_t*)master_hash_data.data())[i] = hash_header.getMasterHashList()[i];
	}

	// import layers
	struct LayerInfo
	{
		int64_t offset;
		int64_t size;
		size_t block_size;
		size_t block_num;
	};

	std::vector<LayerInfo> hash_layer;
	LayerInfo data_layer;

	for (size_t i = 0; i < hash_header.getLayerInfo().size(); i++)
	{
		auto raw_layer = hash_header.getLayerInfo()[i];

		if (tc::is_int64_t_too_large_for_size_t(raw_layer.block_size) || (raw_layer.block_size & (raw_layer.block_size - 1)) != 0)
		{
			throw tc::Exception(mModuleLabel, fmt::format("IVFC layer {:d} block_size was invalid.", i));
		}

		if ((i+1) == hash_header.getLayerInfo().size())
		{
			data_layer = { raw_layer.offset, raw_layer.size, size_t(raw_layer.block_size), size_t((raw_layer.size + (raw_layer.block_size-1))/raw_layer.block_size)  };
		}
		else
		{
			if (tc::is_int64_t_too_large_for_size_t(raw_layer.size))
			{
				throw tc::Exception(mModuleLabel, fmt::format("IVFC hash layer {:d} was too large to read into memory", i));
			}

			hash_layer.push_back({ raw_layer.offset, raw_layer.size, size_t(raw_layer.block_size), size_t((raw_layer.size + (raw_layer.block_size-1))/raw_layer.block_size) });
		}
			
	}

	// validate hash layers
	std::vector<tc::ByteData> hash_layer_data;
	for (size_t i = 0; i < hash_layer.size(); i++)
	{
		tc::ByteData tmp = tc::ByteData(tc::io::IOUtil::castInt64ToSize(hash_layer[i].size));

		mBaseStream->seek(hash_layer[i].offset, tc::io::SeekOrigin::Begin);
		mBaseStream->read(tmp.data(), tmp.size());

		if (!validateLayerBlocksWithHashLayer(tmp.data(), hash_layer[i].block_size, hash_layer[i].block_num, i==0 ? master_hash_data.data() : hash_layer_data[i-1].data()))
		{
			throw tc::crypto::CryptoException(mModuleLabel, fmt::format("Hash layer {:d} failed hash verification.", i));
		}

		hash_layer_data.push_back(std::move(tmp));
	}

	// save final hash layer to verify data
	mHashCache = hash_layer_data.back();

	// create data layer
	mDataStreamBlockSize = data_layer.block_size;
	mDataStreamLogicalLength = data_layer.size;
	int64_t data_layer_physical_size = mBaseStream->length() > data_layer.offset ? (mBaseStream->length() - data_layer.offset) : 0;
	//fmt::print("make IVFC data stream:\n offset=0x{:x}\n size=0x{:x}\n", data_layer.offset, mDataStreamLogicalLength);
	mDataStream = std::shared_ptr<tc::io::SubStream>(new tc::io::SubStream(mBaseStream, data_layer.offset, data_layer_physical_size));
	//fmt::print("make IVFC data stream done\n");
}

bool nn::hac::HierarchicalIntegrityStream::canRead() const
{
	return mDataStream == nullptr ? false : mDataStream->canRead();
}

bool nn::hac::HierarchicalIntegrityStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool nn::hac::HierarchicalIntegrityStream::canSeek() const
{
	return mDataStream == nullptr ? false : mDataStream->canSeek();
}

int64_t nn::hac::HierarchicalIntegrityStream::length()
{
	return mDataStream == nullptr ? 0 : mDataStreamLogicalLength;
}

int64_t nn::hac::HierarchicalIntegrityStream::position()
{
	return mDataStream == nullptr ? 0 : mDataStream->position();
}

size_t nn::hac::HierarchicalIntegrityStream::read(byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::read()", "Failed to read from stream (stream is disposed)");
	}
	
	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// determine begin & end offsets
	int64_t begin_read_offset = this->position();
	int64_t end_read_offset   = begin_read_offset + tc::io::IOUtil::castSizeToInt64(count);
	int64_t begin_aligned_offset = begin_read_offset - offsetInBlock(begin_read_offset);
	int64_t end_aligned_offset   = end_read_offset - offsetInBlock(end_read_offset) + (offsetInBlock(end_read_offset) ? mDataStreamBlockSize : 0x0);
	size_t block_num = offsetToBlock(end_aligned_offset - begin_aligned_offset);

	bool read_partial_begin_block     = false;
	size_t partial_begin_block        = offsetToBlock(begin_read_offset);
	size_t partial_begin_block_offset = 0;
	size_t partial_begin_block_size   = mDataStreamBlockSize;

	bool read_partial_end_block     = false;
	size_t partial_end_block        = offsetToBlock(end_read_offset);
	size_t partial_end_block_offset = 0;
	size_t partial_end_block_size   = mDataStreamBlockSize;

	if (offsetInBlock(begin_read_offset) != 0)
	{
		read_partial_begin_block   = true;
		partial_begin_block_offset += offsetInBlock(begin_read_offset);
		partial_begin_block_size   -= partial_begin_block_offset;
	}
	if (offsetInBlock(end_read_offset) != 0)
	{
		if (partial_begin_block == partial_end_block)
		{
			read_partial_begin_block = true;
			partial_begin_block_size -= (mDataStreamBlockSize - offsetInBlock(end_read_offset));
		}
		else
		{
			read_partial_end_block = true;
			partial_end_block_size = offsetInBlock(end_read_offset);
		}
	}

	size_t continuous_block_num   = block_num - (size_t)read_partial_begin_block - (size_t)read_partial_end_block;
	size_t continuous_begin_block = (continuous_block_num == 0) ? 0 : (offsetToBlock(begin_aligned_offset) + (size_t)read_partial_begin_block);

	/*
	fmt::print("##############################################\n");
	fmt::print("count:                  0x{:x}\n", count);
	fmt::print("begin_read_offset:      0x{:x}\n", begin_read_offset);
	fmt::print("end_read_offset:        0x{:x}\n", end_read_offset);
	fmt::print("begin_aligned_offset:   0x{:x}\n", begin_aligned_offset);
	fmt::print("end_aligned_offset:     0x{:x}\n", end_aligned_offset);
	fmt::print("block_num:              0x{:x}\n", block_num);
	
	fmt::print("partial_begin:\n");
	fmt::print("  read_block:           {}\n", read_partial_begin_block);
	fmt::print("  block:                0x{:x}\n", partial_begin_block);
	fmt::print("  offset:               0x{:x}\n", partial_begin_block_offset);
	fmt::print("  size:                 0x{:x}\n", partial_begin_block_size);

	fmt::print("partial_end:\n");
	fmt::print("  read_block:           {}\n", read_partial_end_block);
	fmt::print("  block:                0x{:x}\n", partial_end_block);
	fmt::print("  offset:               0x{:x}\n", partial_end_block_offset);
	fmt::print("  size:                 0x{:x}\n", partial_end_block_size);

	fmt::print("continuous:\n");
	fmt::print("  block:                0x{:x}\n", continuous_begin_block);
	fmt::print("  block_num:            0x{:x}\n", continuous_block_num);
	*/

	if (block_num == 0)
	{
		tc::InvalidOperationException("nn::hac::HierarchicalIntegrityStream", "Invalid block number (0 blocks, would have returned before now if count==0)");
	}

	if (block_num < continuous_block_num)
	{
		tc::InvalidOperationException("nn::hac::HierarchicalIntegrityStream", "Invalid block number (underflow error)");
	}

	// allocate memory for partial block
	tc::ByteData partial_block = tc::ByteData(mDataStreamBlockSize);

	// read un-aligned begin block
	if (read_partial_begin_block)
	{	
		// read block
		this->seek(blockToOffset(partial_begin_block), tc::io::SeekOrigin::Begin);
		mDataStream->read(partial_block.data(), partial_block.size());
		
		// verify block
		if (validateLayerBlocksWithHashLayer(partial_block.data(), mDataStreamBlockSize, 1, getBlockHash(partial_begin_block)) == false)
		{
			throw tc::crypto::CryptoException("nn::hac::HierarchicalIntegrityStream", "Data layer block(s) failed hash validation.");
		}

		// copy out block carving
		memcpy(ptr + data_read_count, partial_block.data() + partial_begin_block_offset, partial_begin_block_size);

		// increment data read count
		data_read_count += partial_begin_block_size;
	}

	// read continous blocks
	if (continuous_block_num > 0)
	{
		// read blocks
		this->seek(blockToOffset(continuous_begin_block), tc::io::SeekOrigin::Begin);
		mDataStream->read(ptr + data_read_count, continuous_block_num * mDataStreamBlockSize);
		
		// verify blocks
		if (validateLayerBlocksWithHashLayer(ptr + data_read_count, mDataStreamBlockSize, continuous_block_num, getBlockHash(continuous_begin_block)) == false)
		{
			throw tc::crypto::CryptoException("nn::hac::HierarchicalIntegrityStream", "Data layer block(s) failed hash validation.");
		}

		// increment data read count
		data_read_count += continuous_block_num * mDataStreamBlockSize;
	}
	
	// read un-aligned end block
	if (read_partial_end_block)
	{
		// read block
		this->seek(blockToOffset(partial_end_block), tc::io::SeekOrigin::Begin);
		mDataStream->read(partial_block.data(), partial_block.size());
		
		// verify block
		if (validateLayerBlocksWithHashLayer(partial_block.data(), mDataStreamBlockSize, 1, getBlockHash(partial_end_block)) == false)
		{
			throw tc::crypto::CryptoException("nn::hac::HierarchicalIntegrityStream", "Data layer block(s) failed hash validation.");
		}

		// copy out block carving
		memcpy(ptr + data_read_count, partial_block.data() + partial_end_block_offset, partial_end_block_size);

		// increment
		data_read_count += partial_end_block_size;
	}

	// restore expected logical position
	this->seek(begin_read_offset + tc::io::IOUtil::castSizeToInt64(data_read_count), tc::io::SeekOrigin::Begin);

	// return data read count
	return data_read_count;
}

size_t nn::hac::HierarchicalIntegrityStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException(mModuleLabel+"::write()", "write is not supported for HierarchicalIntegrityStream");
}

int64_t nn::hac::HierarchicalIntegrityStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	if (mDataStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to set stream position (stream is disposed)");
	}
	
	return mDataStream->seek(offset, origin);
}

void nn::hac::HierarchicalIntegrityStream::setLength(int64_t length)
{
	if (mDataStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::setLength()", "setLength is not supported for HierarchicalIntegrityStream");
}

void nn::hac::HierarchicalIntegrityStream::flush()
{
	if (mDataStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to flush stream (stream is disposed)");
	}

	mDataStream->flush();
	mBaseStream->flush();
}

void nn::hac::HierarchicalIntegrityStream::dispose()
{
	if (mDataStream.get() != nullptr)
	{
		// dispose data stream
		mDataStream->dispose();

		// release ptr
		mDataStream.reset();
	}

	if (mBaseStream.get() != nullptr)
	{
		// dispose base stream
		mBaseStream->dispose();

		// release ptr
		mBaseStream.reset();
	}
	
	// clear hash cache
	mHashCache = tc::ByteData();
}

bool nn::hac::HierarchicalIntegrityStream::validateLayerBlocksWithHashLayer(const byte_t* layer, size_t block_size, size_t block_num, const byte_t* hash_layer)
{
	size_t bad_block = block_num;
	for (size_t i = 0; i < block_num; i++)
	{
		const byte_t* blk_ptr = layer + (block_size * i);
		size_t blk_size = block_size;

		const byte_t* blk_hash_ptr = hash_layer + (mHashCalc->kHashSize * i);
		//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(blk_hash_ptr, block_size);

		mHashCalc->initialize();
		mHashCalc->update(blk_ptr, blk_size);
		mHashCalc->getHash(mHash.data());

		//fmt::print("test hash: {:s}\n", tc::cli::FormatUtil::formatBytesAsString(blk_hash_ptr, 32, true, ":"));
		//fmt::print("calc hash: {:s}\n", tc::cli::FormatUtil::formatBytesAsString(mHash.data(), 32, true, ":"));

		// if good hash, reduce bad block count
		if (memcmp(mHash.data(), blk_hash_ptr, mHashCalc->kHashSize) == 0)
		{
			bad_block -= 1;
		}
		else
		{
			//fmt::print("BadBlock:\n");
			//fmt::print("{:s}", tc::cli::FormatUtil::formatBytesAsHxdHexString(blk_ptr, blk_size));
		}
		
	}

	return bad_block == 0;
}