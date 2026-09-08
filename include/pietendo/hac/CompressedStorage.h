/**
 * @file CompressedStorage.h
 * @brief Declaration of pie::hac::CompressedStorage
 *
 * Reads the decompressed logical content of an NCA section that uses the
 * compression layer (CompressionInfo). Reference logic ported from LibHac's
 * Tools/FsSystem/CompressedStorage + FsSystem/BucketTree.
 **/
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>
#include <tc/io/IStream.h>
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

class CompressedStorage : public tc::io::IStream
{
public:
	// BucketTree constants
	static const size_t kNodeSize = 0x4000;
	static const size_t kEntrySize = 0x18;
	static const size_t kNodeHeaderSize = 0x10;

	enum CompressionType : byte_t
	{
		CompressionType_None   = 0,
		CompressionType_Zeroed = 1,
		CompressionType_Lz4    = 3
	};

	CompressedStorage();
	CompressedStorage(const std::shared_ptr<tc::io::IStream>& stream, int64_t table_offset, int64_t table_size, int64_t entry_count);

	bool canRead() const;
	bool canWrite() const;
	bool canSeek() const;

	int64_t length();
	int64_t position();

	size_t read(byte_t* ptr, size_t count);
	size_t write(const byte_t* ptr, size_t count);
	int64_t seek(int64_t offset, tc::io::SeekOrigin origin);
	void setLength(int64_t length);
	void flush();
	void dispose();
private:
	struct sEntry
	{
		int64_t virt_offset;
		int64_t phys_offset;
		byte_t compression_type;
		int8_t compression_level;
		uint32_t phys_size;
	};

	std::string mModuleLabel;

	// base stream (the hash-verified section data stream)
	std::shared_ptr<tc::io::IStream> mBaseStream;

	// compression/bucket tree info
	int64_t mTableOffset;
	int64_t mTableSize;
	int64_t mEntryCount;
	int64_t mLogicalStart;
	int64_t mLogicalEnd;

	size_t mEntrySetCount;
	size_t mEntriesPerNode;
	size_t mOffsetCountPerNode;

	// L1 (root) node long array: virtual offset of the first entry of each entry set
	std::vector<int64_t> mL1Offsets;

	// logical stream position (decompressed space)
	int64_t mPosition;

	void parseBucketTree();
	int64_t findEntrySet(int64_t vaddr) const;
	void readEntrySetHeader(size_t entry_set_index, size_t& out_count) const;
	int32_t findEntryInSet(int64_t vaddr, size_t entry_set_index) const;
	void readEntryAt(size_t entry_set_index, int32_t entry_index, sEntry& out) const;
	int64_t getNextEntryOffset(int64_t vaddr, size_t entry_set_index, int32_t entry_index) const;

	static int decompressLz4Block(const byte_t* src, size_t src_size, byte_t* dst, size_t dst_capacity);
};

}} // namespace pie::hac
