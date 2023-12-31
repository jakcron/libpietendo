#include <pietendo/hac/BKTREncryptedStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <pietendo/hac/BKTRSubsectionEncryptedStream.h>
#include <pietendo/hac/define/indirectstorage.h>

#include <fmt/format.h>

// inline utils
inline int64_t virtualToPhysical(int64_t virtual_begin, int64_t physical_begin, int64_t virtual_offset) {
	return physical_begin + (virtual_offset - virtual_begin);
}

const std::string pie::hac::BKTREncryptedStream::kClassName = "pie::hac::BKTREncryptedStream";

pie::hac::BKTREncryptedStream::BKTREncryptedStream() :
	mLength(0),
	mCurrentPos(0),
	mIndirectEntries(),
	mBaseReader(nullptr),
	mPatchReader(nullptr)
{
}

pie::hac::BKTREncryptedStream::BKTREncryptedStream(const std::shared_ptr<tc::io::IStream>& stream, const key_t& key, const counter_t& counter, const pie::hac::sContentArchiveFsHeaderPatchInfo& patch_info, const std::shared_ptr<tc::io::IStream>& base) :
	BKTREncryptedStream()
{
	// validate stream properties
	if (stream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName, "stream is null.");
	}
	if (stream->canRead() == false)
	{
		throw tc::NotSupportedException(kClassName, "stream does not support reading.");
	}
	if (stream->canSeek() == false)
	{
		throw tc::NotSupportedException(kClassName, "stream does not support seeking.");
	}
	if (base == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName, "baseStream is null.");
	}
	if (base->canRead() == false)
	{
		throw tc::NotSupportedException(kClassName, "baseStream does not support reading.");
	}
	if (base->canSeek() == false)
	{
		throw tc::NotSupportedException(kClassName, "baseStream does not support seeking.");
	}

	tc::crypto::Aes128CtrEncryptedStream sections_reader(stream, key, counter);

	// validate and read indirect section
	if (sections_reader.length() < patch_info.indirect_bucket.offset.unwrap() + patch_info.indirect_bucket.size.unwrap())
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "Input stream is too small.");
	}
	tc::ByteData indirect_block_raw = tc::ByteData(patch_info.indirect_bucket.size.unwrap());
	sections_reader.seek(patch_info.indirect_bucket.offset.unwrap(), tc::io::SeekOrigin::Begin);
	sections_reader.read(indirect_block_raw.data(), indirect_block_raw.size());
	const pie::hac::sIndirectStorageBlock* indirect_block = (const pie::hac::sIndirectStorageBlock*)indirect_block_raw.data();

	// Prepare base reader (from base NCA) and patch reader (from update NCA)
	mBaseReader = base;
	mPatchReader = std::make_shared<pie::hac::BKTRSubsectionEncryptedStream>(pie::hac::BKTRSubsectionEncryptedStream(stream, key, counter, patch_info.aes_ctr_ex_bucket));
	
	mLength = indirect_block->header.total_size;
	int64_t end_virtual_offset = indirect_block->header.total_size;

	// Reverse lookup to save size from virtual offset
	for (size_t i = indirect_block->header.bucket_count; i > 0; --i)
	{
		const pie::hac::sIndirectStorageBucket& bucket = indirect_block->buckets[i - 1];
		int64_t base_virtual_offset = indirect_block->base_virtual_bucket_offset[i - 1];
		for (size_t j = bucket.header.entry_count; j > 0; --j)
		{
			const pie::hac::sIndirectStorageEntry& entry = bucket.entries[j - 1];
			int64_t virtual_offset = base_virtual_offset + entry.virt_offset;

			// Check ordered entries
			if (virtual_offset > end_virtual_offset)
			{
				throw tc::InvalidOperationException(kClassName, "Indirect storage not ascending ordered.");
			}

			IndirectEntry& indirect_entry = mIndirectEntries[virtual_offset];
			// Select reader for each indirect storage entry
			switch (entry.storage_index) 
			{
			case indirectstorage::StorageSource_BaseRomFs:
				indirect_entry.reader = mBaseReader;
				break;
			case indirectstorage::StorageSource_PatchRomFs:
				indirect_entry.reader = mPatchReader;
				break;
			default:
				throw tc::NotSupportedException(kClassName, fmt::format("StorageSource({:d}) not supported", entry.storage_index.unwrap()));
				break;
			}
			indirect_entry.physical_offset = entry.phys_offset;
			indirect_entry.virtual_offset = virtual_offset;

			indirect_entry.size = end_virtual_offset - indirect_entry.virtual_offset;
			end_virtual_offset = virtual_offset;
		}
	}
}

bool pie::hac::BKTREncryptedStream::canRead() const
{
	if (mBaseReader == nullptr || !mBaseReader->canRead())
	{
		return false;
	}
	if (mPatchReader == nullptr || !mPatchReader->canRead())
	{
		return false;
	}
	return true;
}

bool pie::hac::BKTREncryptedStream::canWrite() const
{
	return false; // always false this is a read-only stream
}

bool pie::hac::BKTREncryptedStream::canSeek() const
{
	if (mBaseReader == nullptr || !mBaseReader->canSeek())
	{
		return false;
	}
	if (mPatchReader == nullptr || !mPatchReader->canSeek())
	{
		return false;
	}
	return true;
}

int64_t pie::hac::BKTREncryptedStream::length()
{
	return mLength;
}

int64_t pie::hac::BKTREncryptedStream::position()
{
	return mCurrentPos;
}

size_t pie::hac::BKTREncryptedStream::read(byte_t* ptr, size_t count)
{
	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// get current position
	int64_t current_pos = mCurrentPos;
	if (current_pos < 0)
	{
		throw tc::InvalidOperationException(kClassName+"::read()", "Current stream position is negative.");
	}

	// get indirect storage info for current position
	// upper_bound returns first key is greater than key, it means next entry (so need to get previous entry)
	// map must to contain an entry for offset 0, but never retrieve by upper bound (because the key returned must be greater)
	// and in case ask for a offset greater (or equal) to last entry its return "end", so its safe to get previous entry
	const IndirectEntry& entry = (--mIndirectEntries.upper_bound(current_pos))->second;

	std::shared_ptr<tc::io::IStream> reader = entry.reader;

	// determine begin & end offsets
	int64_t begin_read_offset	= current_pos;
	int64_t end_read_offset	  = begin_read_offset + tc::io::IOUtil::castSizeToInt64(count);
	int64_t count_first_relocation = count;
	int64_t end_first_relocation = entry.virtual_offset + entry.size;

	// check 
	if (end_read_offset > end_first_relocation)
	{
		// Read for first relocation
		count_first_relocation = end_first_relocation - begin_read_offset;
	}

	int64_t physical_reader_offset = virtualToPhysical(entry.virtual_offset, entry.physical_offset, begin_read_offset);
	reader->seek(physical_reader_offset, tc::io::SeekOrigin::Begin);
	data_read_count += reader->read(ptr, count_first_relocation);

	if (count_first_relocation != count)
	{
		// update position to continue reading
		this->seek(count_first_relocation, tc::io::SeekOrigin::Current);
		// read data from other(s) storages (recursively)
		data_read_count += this->read(ptr + count_first_relocation, count - count_first_relocation);
	}

	// update expected logical position
	this->seek(begin_read_offset + tc::io::IOUtil::castSizeToInt64(data_read_count), tc::io::SeekOrigin::Begin);

	// return data read count
	return data_read_count;
}

size_t pie::hac::BKTREncryptedStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotSupportedException(kClassName+"::write()", "write is not supported for BKTREncryptedStream");
}

int64_t pie::hac::BKTREncryptedStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	return mCurrentPos = tc::io::StreamUtil::getSeekResult(offset, origin, mCurrentPos, mLength);
}

void pie::hac::BKTREncryptedStream::setLength(int64_t length)
{
	throw tc::NotSupportedException(kClassName+"::setLength()", "setLength is not supported for BKTREncryptedStream");
}

void pie::hac::BKTREncryptedStream::flush()
{
	if (mBaseReader == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName+"::seek()", "Failed to flush base stream (stream is disposed)");
	}
	mBaseReader->flush();

	if (mPatchReader == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName + "::seek()", "Failed to flush patch stream (stream is disposed)");
	}
	mPatchReader->flush();
}

void pie::hac::BKTREncryptedStream::dispose()
{
	if (mBaseReader != nullptr)
	{
		// dispose base stream
		mBaseReader->dispose();

		// release ptr
		mBaseReader.reset();
	}
	if (mPatchReader != nullptr)
	{
		// dispose base stream
		mPatchReader->dispose();

		// release ptr
		mPatchReader.reset();
	}
	mIndirectEntries.clear();
}