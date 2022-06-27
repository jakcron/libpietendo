#include <limits>
#include <nn/hac/PartitionFsHeader.h>

#include <tc/io/IOUtil.h>

nn::hac::PartitionFsHeader::PartitionFsHeader()
{
	clear();
}

nn::hac::PartitionFsHeader::PartitionFsHeader(const PartitionFsHeader & other)
{
	*this = other;
}

void nn::hac::PartitionFsHeader::operator=(const PartitionFsHeader & other)
{
	if (other.getBytes().size())
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		clear();
		mFsType = other.mFsType;
		mFileList = other.mFileList;
	}
}

bool nn::hac::PartitionFsHeader::operator==(const PartitionFsHeader & other) const
{
	return (mFsType == other.mFsType) \
		&& (mFileList == other.mFileList);
}

bool nn::hac::PartitionFsHeader::operator!=(const PartitionFsHeader & other) const
{
	return !(*this == other);
}

const tc::ByteData& nn::hac::PartitionFsHeader::getBytes() const
{
	return mRawBinary;
}


void nn::hac::PartitionFsHeader::toBytes()
{
	// calculate name table size
	int64_t name_table_size = 0;
	for (size_t i = 0; i < mFileList.size(); i++)
	{
		name_table_size += tc::io::IOUtil::castSizeToInt64(mFileList[i].name.length() + 1);
	}

	int64_t pfs_header_size = align<int64_t>(tc::io::IOUtil::castSizeToInt64(sizeof(sPfsHeader)) + tc::io::IOUtil::castSizeToInt64(getFileEntrySize(mFsType) * mFileList.size()) + name_table_size, tc::io::IOUtil::castSizeToInt64(pfs::kHeaderAlign));
	
	// align name_table_size
	name_table_size = pfs_header_size - (sizeof(sPfsHeader) + getFileEntrySize(mFsType) * mFileList.size());

	if (tc::io::IOUtil::castSizeToInt64(tc::io::IOUtil::castInt64ToSize(pfs_header_size)) != pfs_header_size)
	{
		throw tc::InvalidOperationException(kModuleName, "PfsHeader too large to serialise.");
	}

	// allocate pfs header binary
	mRawBinary = tc::ByteData(tc::io::IOUtil::castInt64ToSize(pfs_header_size));
	sPfsHeader* hdr = (sPfsHeader*)mRawBinary.data();

	// set header fields
	switch (mFsType)
	{
		case (TYPE_PFS0):
			hdr->st_magic.wrap(pfs::kPfsStructMagic);
			break;
		case (TYPE_HFS0):
			hdr->st_magic.wrap(pfs::kHashedPfsStructMagic);
			break;
	}
	
	hdr->file_num.wrap((uint32_t)mFileList.size());
	hdr->name_table_size.wrap((uint32_t)name_table_size);

	// set file entries
	if (mFsType == TYPE_PFS0)
	{
		sPfsFile* raw_files = (sPfsFile*)(mRawBinary.data() + sizeof(sPfsHeader));
		char* raw_name_table = (char*)(mRawBinary.data() + sizeof(sPfsHeader) + sizeof(sPfsFile) * mFileList.size());
		size_t raw_name_table_pos = 0;

		calculateOffsets(tc::io::IOUtil::castSizeToInt64(pfs_header_size));
		for (size_t i = 0; i < mFileList.size(); i++)
		{
			if (raw_name_table_pos >= size_t(std::numeric_limits<uint32_t>::max()))
			{
				throw tc::Exception(kModuleName, "raw_name_table_pos could not be safely serialised as it was too large.");
			}

			raw_files[i].data_offset.wrap(mFileList[i].offset - tc::io::IOUtil::castSizeToInt64(pfs_header_size));
			raw_files[i].size.wrap(mFileList[i].size);
			raw_files[i].name_offset.wrap(uint32_t(raw_name_table_pos));

			strcpy(raw_name_table + raw_name_table_pos, mFileList[i].name.c_str());
			raw_name_table_pos += (uint32_t)(mFileList[i].name.length() + 1);
		}
	}
	else if (mFsType == TYPE_HFS0)
	{
		sHashedPfsFile* raw_files = (sHashedPfsFile*)(mRawBinary.data() + sizeof(sPfsHeader));
		char* raw_name_table = (char*)(mRawBinary.data() + sizeof(sPfsHeader) + sizeof(sHashedPfsFile) * mFileList.size());
		size_t raw_name_table_pos = 0;

		calculateOffsets(tc::io::IOUtil::castSizeToInt64(pfs_header_size));
		for (size_t i = 0; i < mFileList.size(); i++)
		{
			if (raw_name_table_pos >= size_t(std::numeric_limits<uint32_t>::max()))
			{
				throw tc::Exception(kModuleName, "raw_name_table_pos could not be safely serialised as it was too large.");
			}

			if (mFileList[i].hash_protected_size >= int64_t(std::numeric_limits<uint32_t>::max()))
			{
				throw tc::Exception(kModuleName, "hash_protected_size could not be safely serialised as it was too large.");
			}

			raw_files[i].data_offset.wrap(mFileList[i].offset - tc::io::IOUtil::castSizeToInt64(pfs_header_size));
			raw_files[i].size.wrap(mFileList[i].size);
			raw_files[i].name_offset.wrap(uint32_t(raw_name_table_pos));
			raw_files[i].hash_protected_size.wrap(uint32_t(mFileList[i].hash_protected_size));
			raw_files[i].hash = mFileList[i].hash;

			strcpy(raw_name_table + raw_name_table_pos, mFileList[i].name.c_str());
			raw_name_table_pos += mFileList[i].name.length() + 1;
		}
	}
	
}

void nn::hac::PartitionFsHeader::fromBytes(const byte_t* data, size_t len)
{
	// check input length meets minimum size
	if (len < sizeof(sPfsHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "PFS header too small");
	}

	// clear variables
	clear();
	
	// import minimum header
	mRawBinary = tc::ByteData(sizeof(sPfsHeader));
	memcpy(mRawBinary.data(), data, mRawBinary.size());
	const sPfsHeader* hdr = (const sPfsHeader*)mRawBinary.data();

	// check struct signature
	FsType fs_type;
	switch(hdr->st_magic.unwrap())
	{
		case (pfs::kPfsStructMagic):
			fs_type = TYPE_PFS0;
			break;
		case (pfs::kHashedPfsStructMagic):
			fs_type = TYPE_HFS0;
			break;	
		default:
			throw tc::ArgumentOutOfRangeException(kModuleName, "PFS header corrupt");
	}

	// determine complete header size
	size_t pfs_full_header_size = sizeof(sPfsHeader) + getFileEntrySize(fs_type) * hdr->file_num.unwrap() + hdr->name_table_size.unwrap();

	// check input length meets complete size
	if (len < pfs_full_header_size)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "PFS header too small");
	}

	// import full header
	mRawBinary = tc::ByteData(pfs_full_header_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());
	hdr = (const sPfsHeader*)mRawBinary.data();

	mFsType = fs_type;
	if (mFsType == TYPE_PFS0)
	{
		// get pointers to raw data
		const sPfsFile* raw_files = (const sPfsFile*)(mRawBinary.data() + sizeof(sPfsHeader));
		const char* raw_name_table = (const char*)(mRawBinary.data() + sizeof(sPfsHeader) + sizeof(sPfsFile) * hdr->file_num.unwrap());

		// process file entries
		for (size_t i = 0; i < hdr->file_num.unwrap(); i++)
		{
			mFileList.push_back({ 
				std::string(raw_name_table + raw_files[i].name_offset.unwrap()), 
				raw_files[i].data_offset.unwrap() + tc::io::IOUtil::castSizeToInt64(pfs_full_header_size), 
				raw_files[i].size.unwrap() 
				});
		}
	}
	else if (mFsType == TYPE_HFS0)
	{
		// get pointers to raw data
		const sHashedPfsFile* raw_files = (const sHashedPfsFile*)(mRawBinary.data() + sizeof(sPfsHeader));
		const char* raw_name_table = (const char*)(mRawBinary.data() + sizeof(sPfsHeader) + sizeof(sHashedPfsFile) * hdr->file_num.unwrap());

		// process file entries
		for (size_t i = 0; i < hdr->file_num.unwrap(); i++)
		{
			mFileList.push_back({
				std::string(raw_name_table + raw_files[i].name_offset.unwrap()), 
				raw_files[i].data_offset.unwrap() + tc::io::IOUtil::castSizeToInt64(pfs_full_header_size), 
				raw_files[i].size.unwrap(),
				int64_t(raw_files[i].hash_protected_size.unwrap()),
				raw_files[i].hash 
				});
		}
	}
	
}

void nn::hac::PartitionFsHeader::clear()
{
	mRawBinary = tc::ByteData();
	mFsType = TYPE_PFS0;
	mFileList.clear();
}

nn::hac::PartitionFsHeader::FsType nn::hac::PartitionFsHeader::getFsType() const
{
	return mFsType;
}

void nn::hac::PartitionFsHeader::setFsType(FsType type)
{
	mFsType = type;
}

const std::vector<nn::hac::PartitionFsHeader::sFile>& nn::hac::PartitionFsHeader::getFileList() const
{
	return mFileList;
}

void nn::hac::PartitionFsHeader::addFile(const std::string & name, int64_t size)
{
	mFileList.push_back({ name, 0, size, 0 });
}

void nn::hac::PartitionFsHeader::addFile(const std::string & name, int64_t size, int64_t hash_protected_size, const nn::hac::detail::sha256_hash_t& hash)
{
	if (hash_protected_size >= int64_t(std::numeric_limits<uint32_t>::max()))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName+"::addFile()", "hash_protected_size cannot exceed 0xffffffff (max for uint32_t)");
	}

	mFileList.push_back({ name, 0, size, hash_protected_size, hash });
}

size_t nn::hac::PartitionFsHeader::getFileEntrySize(FsType fs_type)
{
	size_t size = 0;
	switch(fs_type)
	{
		case (TYPE_PFS0):
			size = sizeof(sPfsFile);
			break;
		case (TYPE_HFS0):
			size = sizeof(sHashedPfsFile);
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kModuleName, "Unknown PFS type");
	}
	return size;
}

void nn::hac::PartitionFsHeader::calculateOffsets(int64_t data_offset)
{
	for (size_t i = 0; i < mFileList.size(); i++)
	{
		mFileList[i].offset = (i == 0) ? data_offset : mFileList[i - 1].offset + mFileList[i - 1].size;
	}
}