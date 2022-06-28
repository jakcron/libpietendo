#include <limits>
#include <pietendo/hac/ContentArchiveHeader.h>

#include <tc/io/IOUtil.h>

pie::hac::ContentArchiveHeader::ContentArchiveHeader()
{
	clear();
}

pie::hac::ContentArchiveHeader::ContentArchiveHeader(const ContentArchiveHeader & other) :
	ContentArchiveHeader()
{
	*this = other;
}

bool pie::hac::ContentArchiveHeader::operator==(const ContentArchiveHeader & other) const
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

bool pie::hac::ContentArchiveHeader::operator!=(const ContentArchiveHeader & other) const
{
	return !(*this == other);
}

void pie::hac::ContentArchiveHeader::operator=(const ContentArchiveHeader & other)
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

void pie::hac::ContentArchiveHeader::toBytes()
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

void pie::hac::ContentArchiveHeader::fromBytes(const byte_t * data, size_t len)
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

const tc::ByteData& pie::hac::ContentArchiveHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::ContentArchiveHeader::clear()
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

byte_t pie::hac::ContentArchiveHeader::getFormatVersion() const
{
	return mFormatVersion;
}

void pie::hac::ContentArchiveHeader::setFormatVersion(byte_t version)
{
	mFormatVersion = version;
}

pie::hac::nca::DistributionType pie::hac::ContentArchiveHeader::getDistributionType() const
{
	return mDistributionType;
}

void pie::hac::ContentArchiveHeader::setDistributionType(nca::DistributionType type)
{
	mDistributionType = type;
}

pie::hac::nca::ContentType pie::hac::ContentArchiveHeader::getContentType() const
{
	return mContentType;
}

void pie::hac::ContentArchiveHeader::setContentType(nca::ContentType type)
{
	mContentType = type;
}

byte_t pie::hac::ContentArchiveHeader::getKeyGeneration() const
{
	return mKeyGeneration;
}

void pie::hac::ContentArchiveHeader::setKeyGeneration(byte_t gen)
{
	mKeyGeneration = gen;
}

byte_t pie::hac::ContentArchiveHeader::getSignatureKeyGeneration() const
{
	return mSignatureKeyGeneration;
}

void pie::hac::ContentArchiveHeader::setSignatureKeyGeneration(byte_t gen)
{
	mSignatureKeyGeneration = gen;
}

byte_t pie::hac::ContentArchiveHeader::getKeyAreaEncryptionKeyIndex() const
{
	return mKaekIndex;
}

void pie::hac::ContentArchiveHeader::setKeyAreaEncryptionKeyIndex(byte_t index)
{
	mKaekIndex = index;
}

uint64_t pie::hac::ContentArchiveHeader::getContentSize() const
{
	return mContentSize;
}

void pie::hac::ContentArchiveHeader::setContentSize(uint64_t size)
{
	mContentSize = size;
}

uint64_t pie::hac::ContentArchiveHeader::getProgramId() const
{
	return mProgramId;
}

void pie::hac::ContentArchiveHeader::setProgramId(uint64_t program_id)
{
	mProgramId = program_id;
}

uint32_t pie::hac::ContentArchiveHeader::getContentIndex() const
{
	return mContentIndex;
}

void pie::hac::ContentArchiveHeader::setContentIndex(uint32_t index)
{
	mContentIndex = index;
}

uint32_t pie::hac::ContentArchiveHeader::getSdkAddonVersion() const
{
	return mSdkAddonVersion;
}

void pie::hac::ContentArchiveHeader::setSdkAddonVersion(uint32_t version)
{
	mSdkAddonVersion = version;
}

bool pie::hac::ContentArchiveHeader::hasRightsId() const
{
	bool rightsIdIsSet = false;

	for (size_t i = 0; i < nca::kRightsIdLen; i++)
	{
		if (mRightsId[i] != 0)
			rightsIdIsSet = true;
	}

	return rightsIdIsSet;
}

const pie::hac::detail::rights_id_t& pie::hac::ContentArchiveHeader::getRightsId() const
{
	return mRightsId;
}

void pie::hac::ContentArchiveHeader::setRightsId(const pie::hac::detail::rights_id_t& rights_id)
{
	mRightsId = rights_id;
}

const std::vector<pie::hac::ContentArchiveHeader::sPartitionEntry>& pie::hac::ContentArchiveHeader::getPartitionEntryList() const
{
	return mPartitionEntryList;
}

void pie::hac::ContentArchiveHeader::setPartitionEntryList(const std::vector<pie::hac::ContentArchiveHeader::sPartitionEntry>& partition_entry_list)
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

const pie::hac::nca::key_area_t& pie::hac::ContentArchiveHeader::getKeyArea() const
{
	return mKeyArea;
}

void pie::hac::ContentArchiveHeader::setKeyArea(const pie::hac::nca::key_area_t& key_area)
{
	mKeyArea = key_area;
}

int64_t pie::hac::ContentArchiveHeader::blockNumToSize(uint32_t block_num) const
{
	return block_num * nca::kSectorSize;
}

uint32_t pie::hac::ContentArchiveHeader::sizeToBlockNum(int64_t real_size) const
{
	static const int64_t kMaxValue = int64_t(std::numeric_limits<uint32_t>::max()) * int64_t(nca::kSectorSize);

	if (real_size >= kMaxValue) { throw tc::Exception (kModuleName, "Cannot convert address to block address"); }

	return uint32_t(align<int64_t>(real_size, int64_t(nca::kSectorSize)) / int64_t(nca::kSectorSize));
}