	/**
	 * @file PartitionFsHeader.h
	 * @brief Declaration of pie::hac::PartitionFsHeader
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/pfs.h>

namespace pie { namespace hac {
	
class PartitionFsHeader
{
public:
	enum FsType
	{
		TYPE_PFS0,
		TYPE_HFS0
	};

	struct sFile
	{
		std::string name;
		int64_t offset;
		int64_t size;
		int64_t hash_protected_size;
		detail::sha256_hash_t hash;

		sFile& operator=(const sFile& other)
		{
			name = other.name;
			offset = other.offset;
			size = other.size;
			hash_protected_size = other.hash_protected_size;
			hash = other.hash;
			return *this;
		}

		bool operator==(const sFile& other) const
		{
			return (name == other.name) \
				&& (offset == other.offset) \
				&& (size == other.size) \
				&& (hash_protected_size == other.hash_protected_size) \
				&& (hash == other.hash);
		}

		bool operator!=(const sFile& other) const
		{
			return !operator==(other);
		}

		bool operator==(const std::string& other) const
		{
			return (name == other);
		}

		bool operator!=(const std::string& other) const
		{
			return !operator==(other);
		}
	};

	PartitionFsHeader();
	PartitionFsHeader(const PartitionFsHeader& other);

	void operator=(const PartitionFsHeader& other);
	bool operator==(const PartitionFsHeader& other) const;
	bool operator!=(const PartitionFsHeader& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	FsType getFsType() const;
	void setFsType(FsType type);
	const std::vector<sFile>& getFileList() const;
	void addFile(const std::string& name, int64_t size);
	void addFile(const std::string& name, int64_t size, int64_t hash_protected_size, const pie::hac::detail::sha256_hash_t& hash);

private:
	const std::string kModuleName = "PARTITIONFS_HEADER";

	// binary blob
	tc::ByteData mRawBinary;

	// variables
	FsType mFsType;
	std::vector<sFile> mFileList;

	size_t getFileEntrySize(FsType fs_type);
	void calculateOffsets(int64_t data_offset);
};

}} // namespace pie::hac