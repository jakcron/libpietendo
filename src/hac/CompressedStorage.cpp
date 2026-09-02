#include <pietendo/hac/CompressedStorage.h>

#include <cstring>
#include <algorithm>
#include <tc/Exception.h>
#include <tc/io/IOUtil.h>
#include <fmt/format.h>

namespace pie { namespace hac {

namespace
{
	inline int64_t readInt64LE(const byte_t* p)
	{
		int64_t v = 0;
		for (size_t i = 0; i < 8; i++) v |= (int64_t)p[i] << (8 * i);
		return v;
	}

	inline int32_t readInt32LE(const byte_t* p)
	{
		int32_t v = 0;
		for (size_t i = 0; i < 4; i++) v |= (int32_t)p[i] << (8 * i);
		return v;
	}

	inline uint32_t readUInt32LE(const byte_t* p)
	{
		uint32_t v = 0;
		for (size_t i = 0; i < 4; i++) v |= (uint32_t)p[i] << (8 * i);
		return v;
	}
}

CompressedStorage::CompressedStorage() :
	mModuleLabel("pie::hac::CompressedStorage"),
	mBaseStream(),
	mTableOffset(0),
	mTableSize(0),
	mEntryCount(0),
	mLogicalStart(0),
	mLogicalEnd(0),
	mEntrySetCount(0),
	mEntriesPerNode(0),
	mOffsetCountPerNode(0),
	mPosition(0)
{
}

CompressedStorage::CompressedStorage(const std::shared_ptr<tc::io::IStream>& stream, int64_t table_offset, int64_t table_size, int64_t entry_count) :
	CompressedStorage()
{
	// validate stream
	if (stream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "stream is null.");
	}
	if (stream->canRead() == false || stream->canSeek() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream does not support reading/seeking.");
	}

	mBaseStream = stream;
	mTableOffset = table_offset;
	mTableSize = table_size;
	mEntryCount = entry_count;

	mEntriesPerNode = (kNodeSize - kNodeHeaderSize) / kEntrySize;      // 682
	mOffsetCountPerNode = (kNodeSize - kNodeHeaderSize) / sizeof(int64_t); // 2046
	mEntrySetCount = (mEntryCount + (int64_t)mEntriesPerNode - 1) / (int64_t)mEntriesPerNode;

	parseBucketTree();

	mPosition = 0;
}

void CompressedStorage::parseBucketTree()
{
	if (mEntryCount <= 0)
	{
		throw tc::Exception(mModuleLabel, "Invalid entry count.");
	}
	if (mEntrySetCount > mOffsetCountPerNode)
	{
		throw tc::Exception(mModuleLabel, "BucketTree with L2 nodes is not supported.");
	}

	// read the L1 (root) node: NodeHeader { int32 index; int32 count; int64 offsetEnd; } + array of int64 offsets
	std::vector<byte_t> l1(kNodeSize);
	mBaseStream->seek(mTableOffset, tc::io::SeekOrigin::Begin);
	mBaseStream->read(l1.data(), l1.size());

	int32_t l1_index = readInt32LE(l1.data() + 0);
	int32_t l1_count = readInt32LE(l1.data() + 4);
	int64_t l1_end   = readInt64LE(l1.data() + 8);

	if (l1_index != 0)
	{
		throw tc::Exception(mModuleLabel, "Invalid bucket tree root node index.");
	}
	if (l1_count <= 0 || (size_t)l1_count > mOffsetCountPerNode)
	{
		throw tc::Exception(mModuleLabel, "Invalid bucket tree root node entry count.");
	}
	if (l1_end < 0)
	{
		throw tc::Exception(mModuleLabel, "Invalid bucket tree offset.");
	}

	mL1Offsets.clear();
	mL1Offsets.reserve((size_t)l1_count);
	for (size_t i = 0; i < (size_t)l1_count; i++)
	{
		mL1Offsets.push_back(readInt64LE(l1.data() + kNodeHeaderSize + i * sizeof(int64_t)));
	}

	mLogicalStart = mL1Offsets.front();
	mLogicalEnd = l1_end;

	if (mLogicalStart < 0 || mLogicalStart >= mLogicalEnd)
	{
		throw tc::Exception(mModuleLabel, "Invalid bucket tree offset range.");
	}
}

bool CompressedStorage::canRead() const
{
	return mBaseStream != nullptr && mBaseStream->canRead();
}

bool CompressedStorage::canWrite() const
{
	return false;
}

bool CompressedStorage::canSeek() const
{
	return mBaseStream != nullptr && mBaseStream->canSeek();
}

int64_t CompressedStorage::length()
{
	return (mLogicalEnd - mLogicalStart) > 0 ? (mLogicalEnd - mLogicalStart) : 0;
}

int64_t CompressedStorage::position()
{
	return mPosition;
}

// Returns the index of the entry set whose first entry virtual offset is the largest one <= vaddr.
int64_t CompressedStorage::findEntrySet(int64_t vaddr) const
{
	int64_t lo = 0, hi = (int64_t)mL1Offsets.size() - 1;
	int64_t result = -1;
	while (lo <= hi)
	{
		int64_t mid = (lo + hi) / 2;
		if (mL1Offsets[(size_t)mid] <= vaddr)
		{
			result = mid;
			lo = mid + 1;
		}
		else
		{
			hi = mid - 1;
		}
	}
	if (result < 0)
	{
		throw tc::Exception(mModuleLabel, "Virtual offset out of range.");
	}
	return result;
}

// entry storage is placed right after the node storage (1 node when no L2 nodes).
static int64_t entryStorageBaseFor(int64_t table_offset)
{
	return table_offset + (int64_t)pie::hac::CompressedStorage::kNodeSize;
}

void CompressedStorage::readEntrySetHeader(size_t entry_set_index, size_t& out_count) const
{
	std::vector<byte_t> hdr(kNodeHeaderSize);
	int64_t off = entryStorageBaseFor(mTableOffset) + (int64_t)entry_set_index * (int64_t)kNodeSize;
	mBaseStream->seek(off, tc::io::SeekOrigin::Begin);
	mBaseStream->read(hdr.data(), hdr.size());

	int32_t set_index = readInt32LE(hdr.data() + 0);
	int32_t set_count = readInt32LE(hdr.data() + 4);
	if ((size_t)set_index != entry_set_index || set_count <= 0)
	{
		throw tc::Exception(mModuleLabel, "Invalid bucket tree entry set header.");
	}
	out_count = (size_t)set_count;
}

void CompressedStorage::readEntryAt(size_t entry_set_index, int32_t entry_index, sEntry& out) const
{
	std::vector<byte_t> raw(kEntrySize);
	int64_t off = entryStorageBaseFor(mTableOffset) + (int64_t)entry_set_index * (int64_t)kNodeSize + (int64_t)kNodeHeaderSize + (int64_t)entry_index * (int64_t)kEntrySize;
	mBaseStream->seek(off, tc::io::SeekOrigin::Begin);
	mBaseStream->read(raw.data(), raw.size());

	out.virt_offset = readInt64LE(raw.data() + 0);
	out.phys_offset = readInt64LE(raw.data() + 8);
	out.compression_type = raw[16];
	out.compression_level = (int8_t)raw[17];
	out.phys_size = readUInt32LE(raw.data() + 20);
}

int32_t CompressedStorage::findEntryInSet(int64_t vaddr, size_t entry_set_index) const
{
	size_t set_count = 0;
	readEntrySetHeader(entry_set_index, set_count);

	int64_t lo = 0, hi = (int64_t)set_count - 1;
	int64_t result = -1;
	while (lo <= hi)
	{
		int64_t mid = (lo + hi) / 2;
		int64_t off = entryStorageBaseFor(mTableOffset) + (int64_t)entry_set_index * (int64_t)kNodeSize + (int64_t)kNodeHeaderSize + mid * (int64_t)kEntrySize;
		std::vector<byte_t> raw(sizeof(int64_t));
		mBaseStream->seek(off, tc::io::SeekOrigin::Begin);
		mBaseStream->read(raw.data(), raw.size());
		int64_t ev = readInt64LE(raw.data());
		if (ev <= vaddr)
		{
			result = mid;
			lo = mid + 1;
		}
		else
		{
			hi = mid - 1;
		}
	}
	if (result < 0)
	{
		throw tc::Exception(mModuleLabel, "Virtual offset out of range within entry set.");
	}
	return (int32_t)result;
}

int64_t CompressedStorage::getNextEntryOffset(int64_t vaddr, size_t entry_set_index, int32_t entry_index) const
{
	size_t set_count = 0;
	readEntrySetHeader(entry_set_index, set_count);

	if ((size_t)(entry_index + 1) < set_count)
	{
		sEntry next;
		readEntryAt(entry_set_index, entry_index + 1, next);
		return next.virt_offset;
	}
	else if (entry_set_index + 1 < mL1Offsets.size())
	{
		return mL1Offsets[entry_set_index + 1];
	}
	else
	{
		return mLogicalEnd;
	}
}

size_t CompressedStorage::read(byte_t* ptr, size_t count)
{
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "stream is disposed");
	}

	int64_t logical_len = length();

	// clamp read to logical length
	if (mPosition >= logical_len)
	{
		return 0;
	}
	if (count > tc::io::IOUtil::castInt64ToSize(logical_len - mPosition))
	{
		count = tc::io::IOUtil::castInt64ToSize(logical_len - mPosition);
	}
	if (count == 0)
	{
		return 0;
	}

	int64_t base_vaddr = mLogicalStart;
	int64_t current_vaddr = base_vaddr + mPosition;
	int64_t end_vaddr = current_vaddr + tc::io::IOUtil::castSizeToInt64(count);

	while (current_vaddr < end_vaddr)
	{
		size_t entry_set_index = (size_t)findEntrySet(current_vaddr);
		int32_t entry_index = findEntryInSet(current_vaddr, entry_set_index);

		sEntry entry;
		readEntryAt(entry_set_index, entry_index, entry);

		int64_t next_vaddr = getNextEntryOffset(current_vaddr, entry_set_index, entry_index);

		int64_t entry_span = next_vaddr - entry.virt_offset;
		if (entry_span <= 0)
		{
			throw tc::Exception(mModuleLabel, "Invalid compressed storage entry span.");
		}

		int64_t data_offset_in_entry = current_vaddr - entry.virt_offset;
		int64_t remaining = end_vaddr - current_vaddr;
		int64_t to_write = std::min<int64_t>(remaining, entry_span - data_offset_in_entry);
		if (to_write <= 0)
		{
			throw tc::Exception(mModuleLabel, "Invalid compressed storage entry range.");
		}

		byte_t* dst = ptr + tc::io::IOUtil::castInt64ToSize(current_vaddr - base_vaddr - mPosition);

		switch (entry.compression_type)
		{
			case CompressionType_Lz4:
			{
				if (entry.phys_size == 0)
				{
					memset(dst, 0, tc::io::IOUtil::castInt64ToSize(to_write));
				}
				else
				{
					std::vector<byte_t> enc(tc::io::IOUtil::castInt64ToSize(entry.phys_size));
					mBaseStream->seek(entry.phys_offset, tc::io::SeekOrigin::Begin);
					mBaseStream->read(enc.data(), enc.size());

					std::vector<byte_t> dec(tc::io::IOUtil::castInt64ToSize(entry_span));
					int dec_size = decompressLz4Block(enc.data(), enc.size(), dec.data(), dec.size());
					if (dec_size < 0 || (size_t)dec_size != tc::io::IOUtil::castInt64ToSize(entry_span))
					{

						throw tc::Exception(mModuleLabel, "LZ4 block decompression failed.");
					}

					memcpy(dst, dec.data() + tc::io::IOUtil::castInt64ToSize(data_offset_in_entry), tc::io::IOUtil::castInt64ToSize(to_write));
				}
				break;
			}
			case CompressionType_None:
			{
				mBaseStream->seek(entry.phys_offset + data_offset_in_entry, tc::io::SeekOrigin::Begin);
				mBaseStream->read(dst, tc::io::IOUtil::castInt64ToSize(to_write));
				break;
			}
			case CompressionType_Zeroed:
			{
				memset(dst, 0, tc::io::IOUtil::castInt64ToSize(to_write));
				break;
			}
			default:
				throw tc::Exception(mModuleLabel, fmt::format("Unknown compressed storage entry compression type ({:d}).", entry.compression_type));
		}

		current_vaddr += to_write;
	}

	mPosition += tc::io::IOUtil::castSizeToInt64(count);
	return count;
}

int CompressedStorage::decompressLz4Block(const byte_t* src, size_t src_size, byte_t* dst, size_t dst_capacity)
{
	size_t cmp_pos = 0;
	size_t dec_pos = 0;

	auto get_len = [&](int length) -> int
	{
		if (length == 0xf)
		{
			for (;;)
			{
				if (cmp_pos >= src_size) return -1;
				byte_t sum = src[cmp_pos++];
				length += (int)sum;
				if (sum != 0xff) break;
			}
		}
		return length;
	};

	for (;;)
	{
		if (cmp_pos >= src_size || dec_pos >= dst_capacity) break;

		byte_t token = src[cmp_pos++];

		int enc_count = token & 0xf;
		int lit_count = token >> 4;

		lit_count = get_len(lit_count);
		if (lit_count < 0 || (size_t)lit_count > src_size - cmp_pos || (size_t)lit_count > dst_capacity - dec_pos)
		{
			return -1;
		}

		// copy literals
		memcpy(dst + dec_pos, src + cmp_pos, (size_t)lit_count);
		cmp_pos += (size_t)lit_count;
		dec_pos += (size_t)lit_count;

		// last sequence can be literals only
		if (cmp_pos >= src_size) break;

		// read 2-byte offset
		if (cmp_pos + 2 > src_size) return -1;
		int back = (int)src[cmp_pos] | ((int)src[cmp_pos + 1] << 8);
		cmp_pos += 2;
		if (back == 0 || (size_t)back > dec_pos) return -1;

		enc_count = get_len(enc_count);
		if (enc_count < 0) return -1;
		enc_count += 4;

		if ((size_t)enc_count > dst_capacity - dec_pos) return -1;

		size_t enc_pos = dec_pos - (size_t)back;
		if ((size_t)enc_count <= (size_t)back)
		{
			memcpy(dst + dec_pos, dst + enc_pos, (size_t)enc_count);
			dec_pos += (size_t)enc_count;
		}
		else
		{
			while (enc_count-- > 0)
			{
				dst[dec_pos++] = dst[enc_pos++];
			}
		}
	}

	return (int)dec_pos;
}

size_t CompressedStorage::write(const byte_t* ptr, size_t count)
{
	throw tc::NotSupportedException(mModuleLabel + "::write()", "write is not supported for CompressedStorage");
}

int64_t CompressedStorage::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	int64_t new_pos = 0;
	switch (origin)
	{
		case (tc::io::SeekOrigin::Begin):
			new_pos = offset;
			break;
		case (tc::io::SeekOrigin::Current):
			new_pos = mPosition + offset;
			break;
		case (tc::io::SeekOrigin::End):
			new_pos = length() + offset;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(mModuleLabel, "Invalid seek origin.");
	}

	if (new_pos < 0)
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "Cannot seek to negative position.");
	}

	mPosition = new_pos;
	return mPosition;
}

void CompressedStorage::setLength(int64_t length)
{
	throw tc::NotSupportedException(mModuleLabel + "::setLength()", "setLength is not supported for CompressedStorage");
}

void CompressedStorage::flush()
{
	if (mBaseStream != nullptr)
	{
		mBaseStream->flush();
	}
}

void CompressedStorage::dispose()
{
	if (mBaseStream != nullptr)
	{
		mBaseStream->dispose();
		mBaseStream.reset();
	}
	mPosition = 0;
}

}} // namespace pie::hac
