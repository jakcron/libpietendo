#include <limits>
#include <nn/hac/ContentArchiveHeader.h>

#include <tc/io/IOUtil.h>

nn::hac::ContentArchiveHeader::ContentArchiveHeader()
{
	clear();
}

nn::hac::ContentArchiveHeader::ContentArchiveHeader(const ContentArchiveHeader & other) :
	ContentArchiveHeader()
{
	*this = other;
}

bool nn::hac::ContentArchiveHeader::operator==(const ContentArchiveHeader & other) const
{
	return (mFormatVersion == other.mFormatVersion) \
		&& (mDistributionType == other.mDistributionType) \
		&& (mContentType == other.mContentType) \
		&& (mKeyGeneration == other.mKeyGeneration) \
		&& (mSignatureKeyGeneration == other.mSignatureKeyGeneration) \
		&& (mKaekIndex == other.mKaekIndex) \
		&& (mContentSize == other.mContentSize) \
		&& (mProgramId == other.mProgramId) \
		&& (mContentIndex == other.mContentIndex) \
		&& (mSdkAddonVersion == other.mSdkAddonVersion) \
		&& (mRightsId == other.mRightsId) \
		&& (mPartitionEntryList == other.mPartitionEntryList) \
		&& (mKeyArea == other.mKeyArea);
}

bool nn::hac::ContentArchiveHeader::operator!=(const ContentArchiveHeader & other) const
{
	return !(*this == other);
}

void nn::hac::ContentArchiveHeader::operator=(const ContentArchiveHeader & other)
{
	mRawBinary = other.mRawBinary;
	mDistributionType = other.mDistributionType;
	mContentType = other.mContentType;
	mKeyGeneration = other.mKeyGeneration;
	mSignatureKeyGeneration = other.mSignatureKeyGeneration;
	mKaekIndex = other.mKaekIndex;
	mContentSize = other.mContentSize;
	mProgramId = other.mProgramId;
	mContentIndex = other.mContentIndex;
	mSdkAddonVersion = other.mSdkAddonVersion;
	mRightsId = other.mRightsId;
	mPartitionEntryList = other.mPartitionEntryList;
	mKeyArea = other.mKeyArea;
}

void nn::hac::ContentArchiveHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sContentArchiveHeader));
	sContentArchiveHeader* hdr = (sContentArchiveHeader*)mRawBinary.data();

	// set header magic
	switch(mFormatVersion)
	{
	case (nca::FORMAT_NCA2):
		hdr->st_magic.wrap(nca::kNca2StructMagic);
		break;
	case (nca::FORMAT_NCA3):
		hdr->st_magic.wrap(nca::kNca3StructMagic);
		break;
	default:
		throw tc::ArgumentOutOfRangeException(kModuleName, "Unsupported format version");
	}

	// set variables
	hdr->distribution_type = (byte_t)mDistributionType;
	hdr->content_type = (byte_t)mContentType;
	if (mKeyGeneration > 2)
	{
		hdr->key_generation = 2;
		hdr->key_generation_2 = mKeyGeneration;
	}
	else
	{
		hdr->key_generation = mKeyGeneration;
		hdr->key_generation_2 = 0;
	}
	hdr->signature_key_generation = mSignatureKeyGeneration;
	hdr->key_area_encryption_key_index = mKaekIndex;
	hdr->content_size.wrap(mContentSize);
	hdr->program_id.wrap(mProgramId);
	hdr->content_index.wrap(mContentIndex);
	hdr->sdk_addon_version.wrap(mSdkAddonVersion);
	memcpy(hdr->rights_id.data(), mRightsId.data(), hdr->rights_id.size());
	hdr->key_area = mKeyArea;

	for (size_t i = 0; i < mPartitionEntryList.size(); i++)
	{
		byte_t index = mPartitionEntryList[i].header_index;
		
		if (index >= nca::kPartitionNum) continue;

		hdr->partition_entry[index].start_blk.wrap(sizeToBlockNum(mPartitionEntryList[index].offset));
		hdr->partition_entry[index].end_blk.wrap((sizeToBlockNum(mPartitionEntryList[index].offset + mPartitionEntryList[index].size)));
		hdr->partition_entry[index].enabled = true;
		hdr->fs_header_hash[index] = mPartitionEntryList[i].fs_header_hash;	
	}
}

void nn::hac::ContentArchiveHeader::fromBytes(const byte_t * data, size_t len)
{
	if (len < sizeof(sContentArchiveHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ContentArchive header size is too small");
	}

	clear();

	mRawBinary = tc::ByteData(sizeof(sContentArchiveHeader));
	memcpy(mRawBinary.data(), data, sizeof(sContentArchiveHeader));

	sContentArchiveHeader* hdr = (sContentArchiveHeader*)mRawBinary.data();

	// check magic
	switch(hdr->st_magic.unwrap())
	{
		case (nca::kNca2StructMagic) :
			mFormatVersion = nca::FORMAT_NCA2;
			break;
		case (nca::kNca3StructMagic) :
			mFormatVersion = nca::FORMAT_NCA3;
			break;
		throw tc::ArgumentOutOfRangeException(kModuleName, "ContentArchive header corrupt (unrecognised header magic).");
	}

	// variables
	mDistributionType = nca::DistributionType(hdr->distribution_type);
	mContentType = nca::ContentType(hdr->content_type);
	mKeyGeneration = std::max<byte_t>(hdr->key_generation, hdr->key_generation_2);
	mSignatureKeyGeneration = hdr->signature_key_generation;
	mKaekIndex = hdr->key_area_encryption_key_index;
	mContentSize = hdr->content_size.unwrap();
	mProgramId = hdr->program_id.unwrap();
	mContentIndex = hdr->content_index.unwrap();
	mSdkAddonVersion = hdr->sdk_addon_version.unwrap();
	mRightsId = hdr->rights_id;
	mKeyArea = hdr->key_area;

	for (size_t i = 0; i < nca::kPartitionNum; i++)
	{
		if (hdr->partition_entry[i].enabled)
		{
			mPartitionEntryList.push_back({(byte_t)i, blockNumToSize(hdr->partition_entry[i].start_blk.unwrap()), blockNumToSize(hdr->partition_entry[i].end_blk.unwrap() - hdr->partition_entry[i].start_blk.unwrap()), hdr->fs_header_hash[i] });
		}
	}
}

const tc::ByteData& nn::hac::ContentArchiveHeader::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ContentArchiveHeader::clear()
{
	mFormatVersion = nca::FORMAT_NCA3;
	mDistributionType = nca::DistributionType::Download;
	mContentType = nca::ContentType::Program;
	mKeyGeneration = 0;
	mKaekIndex = 0;
	mContentSize = 0;
	mProgramId = 0;
	mContentIndex = 0;
	mSdkAddonVersion = 0;
	memset(mRightsId.data(), 0, mRightsId.size());
	mPartitionEntryList.clear();
	for (auto itr = mKeyArea.begin(); itr != mKeyArea.end(); itr++)
	{
		memset(itr->data(), 0, itr->size());
	}
}

byte_t nn::hac::ContentArchiveHeader::getFormatVersion() const
{
	return mFormatVersion;
}

void nn::hac::ContentArchiveHeader::setFormatVersion(byte_t version)
{
	mFormatVersion = version;
}

nn::hac::nca::DistributionType nn::hac::ContentArchiveHeader::getDistributionType() const
{
	return mDistributionType;
}

void nn::hac::ContentArchiveHeader::setDistributionType(nca::DistributionType type)
{
	mDistributionType = type;
}

nn::hac::nca::ContentType nn::hac::ContentArchiveHeader::getContentType() const
{
	return mContentType;
}

void nn::hac::ContentArchiveHeader::setContentType(nca::ContentType type)
{
	mContentType = type;
}

byte_t nn::hac::ContentArchiveHeader::getKeyGeneration() const
{
	return mKeyGeneration;
}

void nn::hac::ContentArchiveHeader::setKeyGeneration(byte_t gen)
{
	mKeyGeneration = gen;
}

byte_t nn::hac::ContentArchiveHeader::getSignatureKeyGeneration() const
{
	return mSignatureKeyGeneration;
}

void nn::hac::ContentArchiveHeader::setSignatureKeyGeneration(byte_t gen)
{
	mSignatureKeyGeneration = gen;
}

byte_t nn::hac::ContentArchiveHeader::getKeyAreaEncryptionKeyIndex() const
{
	return mKaekIndex;
}

void nn::hac::ContentArchiveHeader::setKeyAreaEncryptionKeyIndex(byte_t index)
{
	mKaekIndex = index;
}

uint64_t nn::hac::ContentArchiveHeader::getContentSize() const
{
	return mContentSize;
}

void nn::hac::ContentArchiveHeader::setContentSize(uint64_t size)
{
	mContentSize = size;
}

uint64_t nn::hac::ContentArchiveHeader::getProgramId() const
{
	return mProgramId;
}

void nn::hac::ContentArchiveHeader::setProgramId(uint64_t program_id)
{
	mProgramId = program_id;
}

uint32_t nn::hac::ContentArchiveHeader::getContentIndex() const
{
	return mContentIndex;
}

void nn::hac::ContentArchiveHeader::setContentIndex(uint32_t index)
{
	mContentIndex = index;
}

uint32_t nn::hac::ContentArchiveHeader::getSdkAddonVersion() const
{
	return mSdkAddonVersion;
}

void nn::hac::ContentArchiveHeader::setSdkAddonVersion(uint32_t version)
{
	mSdkAddonVersion = version;
}

bool nn::hac::ContentArchiveHeader::hasRightsId() const
{
	bool rightsIdIsSet = false;

	for (size_t i = 0; i < nca::kRightsIdLen; i++)
	{
		if (mRightsId[i] != 0)
			rightsIdIsSet = true;
	}

	return rightsIdIsSet;
}

const nn::hac::detail::rights_id_t& nn::hac::ContentArchiveHeader::getRightsId() const
{
	return mRightsId;
}

void nn::hac::ContentArchiveHeader::setRightsId(const nn::hac::detail::rights_id_t& rights_id)
{
	mRightsId = rights_id;
}

const std::vector<nn::hac::ContentArchiveHeader::sPartitionEntry>& nn::hac::ContentArchiveHeader::getPartitionEntryList() const
{
	return mPartitionEntryList;
}

void nn::hac::ContentArchiveHeader::setPartitionEntryList(const std::vector<nn::hac::ContentArchiveHeader::sPartitionEntry>& partition_entry_list)
{
	mPartitionEntryList = partition_entry_list;

	// sanity check the list
	if (mPartitionEntryList.size() >= nca::kPartitionNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Too many partitions");
	}
	for (size_t i = 0; i < mPartitionEntryList.size(); i++)
	{
		if (mPartitionEntryList[i].header_index >= nca::kPartitionNum)
		{
			throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal partition index");
		}
		for (size_t j = i+1; j < mPartitionEntryList.size(); j++)
		{
			if (mPartitionEntryList[i].header_index == mPartitionEntryList[j].header_index)
			{
				throw tc::ArgumentOutOfRangeException(kModuleName, "Duplicated partition index");
			}
		}
	}
}

const nn::hac::nca::key_area_t& nn::hac::ContentArchiveHeader::getKeyArea() const
{
	return mKeyArea;
}

void nn::hac::ContentArchiveHeader::setKeyArea(const nn::hac::nca::key_area_t& key_area)
{
	mKeyArea = key_area;
}

int64_t nn::hac::ContentArchiveHeader::blockNumToSize(uint32_t block_num) const
{
	return block_num * nca::kSectorSize;
}

uint32_t nn::hac::ContentArchiveHeader::sizeToBlockNum(int64_t real_size) const
{
	static const int64_t kMaxValue = int64_t(std::numeric_limits<uint32_t>::max()) * int64_t(nca::kSectorSize);

	if (real_size >= kMaxValue) { throw tc::Exception (kModuleName, "Cannot convert address to block address"); }

	return uint32_t(align<int64_t>(real_size, int64_t(nca::kSectorSize)) / int64_t(nca::kSectorSize));
}