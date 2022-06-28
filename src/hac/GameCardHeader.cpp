#include <pietendo/hac/GameCardHeader.h>

pie::hac::GameCardHeader::GameCardHeader()
{
	clear();
}

pie::hac::GameCardHeader::GameCardHeader(const GameCardHeader& other)
{
	*this = other;
}

void pie::hac::GameCardHeader::operator=(const GameCardHeader& other)
{
	mRomAreaStartPage = other.mRomAreaStartPage;
	mBackupAreaStartPage = other.mBackupAreaStartPage;
	mKekIndex = other.mKekIndex;
	mTitleKeyDecIndex = other.mTitleKeyDecIndex;
	mRomSize = other.mRomSize;
	mCardHeaderVersion = other.mCardHeaderVersion;
	mFlags = other.mFlags;
	mPackageId = other.mPackageId;
	mValidDataEndPage = other.mValidDataEndPage;
	mAesCbcIv = other.mAesCbcIv;
	mPartitionFsHeaderAddress = other.mPartitionFsHeaderAddress;
	mPartitionFsHeaderSize = other.mPartitionFsHeaderSize;
	mPartitionFsHeaderHash = other.mPartitionFsHeaderHash;
	mInitialDataHash = other.mInitialDataHash;
	mSelSec = other.mSelSec;
	mSelT1Key = other.mSelT1Key;
	mSelKey = other.mSelKey;
	mLimAreaPage = other.mLimAreaPage;
	mFwVersion = other.mFwVersion;
	mAccCtrl1 = other.mAccCtrl1;
	mWait1TimeRead = other.mWait1TimeRead;
	mWait2TimeRead = other.mWait2TimeRead;
	mWait1TimeWrite = other.mWait1TimeWrite;
	mWait2TimeWrite = other.mWait2TimeWrite;
	mFwMode = other.mFwMode;
	mUppVersion = other.mUppVersion;
	mCompatibilityType = other.mCompatibilityType;
	mUppHash = other.mUppHash;
	mUppId = other.mUppId;
}

bool pie::hac::GameCardHeader::operator==(const GameCardHeader& other) const
{
	return	(mRomAreaStartPage == other.mRomAreaStartPage)
		&&	(mBackupAreaStartPage == other.mBackupAreaStartPage)
		&&	(mKekIndex == other.mKekIndex)
		&&	(mTitleKeyDecIndex == other.mTitleKeyDecIndex)
		&&	(mRomSize == other.mRomSize)
		&&	(mCardHeaderVersion == other.mCardHeaderVersion)
		&&	(mFlags == other.mFlags)
		&&	(mPackageId == other.mPackageId)
		&&	(mValidDataEndPage == other.mValidDataEndPage)
		&&	(mAesCbcIv == other.mAesCbcIv)
		&&	(mPartitionFsHeaderAddress == other.mPartitionFsHeaderAddress)
		&&	(mPartitionFsHeaderSize == other.mPartitionFsHeaderSize)
		&&	(mPartitionFsHeaderHash == other.mPartitionFsHeaderHash)
		&&	(mInitialDataHash == other.mInitialDataHash)
		&&	(mSelSec == other.mSelSec)
		&&	(mSelT1Key == other.mSelT1Key)
		&&	(mSelKey == other.mSelKey)
		&&	(mLimAreaPage == other.mLimAreaPage)
		&&	(mFwVersion == other.mFwVersion)
		&&	(mAccCtrl1 == other.mAccCtrl1)
		&&	(mWait1TimeRead == other.mWait1TimeRead)
		&&	(mWait2TimeRead == other.mWait2TimeRead)
		&&	(mWait1TimeWrite == other.mWait1TimeWrite)
		&&	(mWait2TimeWrite == other.mWait2TimeWrite)
		&&	(mFwMode == other.mFwMode)
		&&	(mUppVersion == other.mUppVersion)
		&&  (mCompatibilityType == other.mCompatibilityType)
		&&	(mUppHash == other.mUppHash)
		&&	(mUppId == other.mUppId);
}

bool pie::hac::GameCardHeader::operator!=(const GameCardHeader& other) const
{
	return !(*this == other);
}

void pie::hac::GameCardHeader::toBytes()
{
	tc::NotImplementedException(kModuleName, "toBytes() not implemented");
}

void pie::hac::GameCardHeader::fromBytes(const byte_t* data, size_t len)
{
	// check input data size
	if (len < sizeof(sGcHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "GameCardImage header size is too small");
	}

	// clear internal members
	clear();

	// allocate internal local binary copy
	mRawBinary = tc::ByteData(sizeof(sGcHeader));
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// get sGcHeader ptr
	const pie::hac::sGcHeader* hdr = (const pie::hac::sGcHeader*)mRawBinary.data();
	
	// check GameCardImage signature
	if (hdr->st_magic.unwrap() != gc::kGcHeaderStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "GameCardImage header corrupt");
	}

	mRomAreaStartPage = hdr->rom_area_start_page.unwrap();
	mBackupAreaStartPage = hdr->backup_area_start_page.unwrap();
	mKekIndex = hdr->key_flag & 7;
	mTitleKeyDecIndex = (hdr->key_flag >> 4) & 7;
	mRomSize = hdr->rom_size;
	mCardHeaderVersion = hdr->card_header_version;
	for (size_t i = 0; i < hdr->flags.bit_size(); i++)
	{
		if (hdr->flags.test(i))
		{
			mFlags.push_back(pie::hac::gc::HeaderFlags(i));
		}
	}
	mPackageId = hdr->package_id.unwrap();
	mValidDataEndPage = hdr->valid_data_end_page.unwrap();
	for (size_t i = 0; i < mAesCbcIv.size(); i++)
		mAesCbcIv[i] = hdr->aescbc_iv[15-i];
	mPartitionFsHeaderAddress = hdr->partition_fs_header_address.unwrap();
	mPartitionFsHeaderSize = hdr->partition_fs_header_size.unwrap();
	mPartitionFsHeaderHash = hdr->partition_fs_header_hash;
	mInitialDataHash = hdr->initial_data_hash;
	mSelSec = hdr->sel_sec.unwrap();
	mSelT1Key = hdr->sel_t1_key.unwrap();
	mSelKey = hdr->sel_key.unwrap();
	mLimAreaPage = hdr->lim_area.unwrap();

	mFwVersion = hdr->extended_header.fw_version.unwrap();
	mAccCtrl1 = hdr->extended_header.acc_ctrl_1.unwrap();
	mWait1TimeRead = hdr->extended_header.wait_1_time_read.unwrap();
	mWait2TimeRead = hdr->extended_header.wait_2_time_read.unwrap();
	mWait1TimeWrite = hdr->extended_header.wait_1_time_write.unwrap();
	mWait2TimeWrite = hdr->extended_header.wait_2_time_write.unwrap();
	mFwMode = hdr->extended_header.fw_mode.unwrap();
	mUppVersion = hdr->extended_header.upp_version.unwrap();
	mCompatibilityType = hdr->extended_header.region_compatibility;
	mUppHash = hdr->extended_header.upp_hash;
	mUppId = hdr->extended_header.upp_id.unwrap();
}

const tc::ByteData& pie::hac::GameCardHeader::getBytes() const
{
	return mRawBinary;
}

// variables
void pie::hac::GameCardHeader::clear()
{
	mRomAreaStartPage = 0;
	mBackupAreaStartPage = 0;
	mKekIndex = 0;
	mTitleKeyDecIndex = 0;
	mRomSize = 0;
	mCardHeaderVersion = 0;
	mFlags.clear();
	mPackageId = 0;
	mValidDataEndPage = 0;
	memset(mAesCbcIv.data(), 0, mAesCbcIv.size());
	mPartitionFsHeaderAddress = 0;
	mPartitionFsHeaderSize = 0;
	memset(mPartitionFsHeaderHash.data(), 0, mPartitionFsHeaderHash.size());
	memset(mInitialDataHash.data(), 0, mInitialDataHash.size());
	mSelSec = 0;
	mSelT1Key = 0;
	mSelKey = 0;
	mLimAreaPage = 0;
	mFwVersion = 0;
	mAccCtrl1 = 0;
	mWait1TimeRead = 0;
	mWait2TimeRead = 0;
	mWait1TimeWrite = 0;
	mWait2TimeWrite = 0;
	mFwMode = 0;
	mUppVersion = 0;
	mCompatibilityType = 0;
	memset(mUppHash.data(), 0, mUppHash.size());
	mUppId = 0;
}

uint32_t pie::hac::GameCardHeader::getRomAreaStartPage() const
{
	return mRomAreaStartPage;
}

void pie::hac::GameCardHeader::setRomAreaStartPage(uint32_t startPage)
{
	mRomAreaStartPage = startPage;
}

uint32_t pie::hac::GameCardHeader::getBackupAreaStartPage() const
{
	return mBackupAreaStartPage;
}

void pie::hac::GameCardHeader::setBackupAreaStartPage(uint32_t startPage)
{
	mBackupAreaStartPage = startPage;
}

byte_t pie::hac::GameCardHeader::getKekIndex() const
{
	return mKekIndex;
}

void pie::hac::GameCardHeader::setKekIndex(byte_t kekIndex)
{
	mKekIndex = kekIndex;
}

byte_t pie::hac::GameCardHeader::getTitleKeyDecIndex() const
{
	return mTitleKeyDecIndex;
}

void pie::hac::GameCardHeader::setTitleKeyDecIndex(byte_t index)
{
	mTitleKeyDecIndex = index;
}

byte_t pie::hac::GameCardHeader::getRomSizeType() const
{
	return mRomSize;
}

void pie::hac::GameCardHeader::setRomSizeType(byte_t romSizeType)
{
	mRomSize = romSizeType;
}

byte_t pie::hac::GameCardHeader::getCardHeaderVersion() const
{
	return mCardHeaderVersion;
}

void pie::hac::GameCardHeader::setCardHeaderVersion(byte_t version)
{
	mCardHeaderVersion = version;
}

byte_t pie::hac::GameCardHeader::getCompatibilityType() const
{
	return mCompatibilityType;
}

void pie::hac::GameCardHeader::setCompatibilityType(byte_t compat_type)
{
	mCompatibilityType = compat_type;
}

uint64_t pie::hac::GameCardHeader::getPackageId() const
{
	return mPackageId;
}

void pie::hac::GameCardHeader::setPackageId(uint64_t id)
{
	mPackageId = id;
}

uint32_t pie::hac::GameCardHeader::getValidDataEndPage() const
{
	return mValidDataEndPage;
}

void pie::hac::GameCardHeader::setValidDataEndPage(uint32_t page)
{
	mValidDataEndPage = page;
}

const pie::hac::detail::aes_iv_t& pie::hac::GameCardHeader::getAesCbcIv() const
{
	return mAesCbcIv;
}

void pie::hac::GameCardHeader::setAesCbcIv(const pie::hac::detail::aes_iv_t& iv)
{
	mAesCbcIv = iv;
}

uint64_t pie::hac::GameCardHeader::getPartitionFsAddress() const
{
	return mPartitionFsHeaderAddress;
}

void pie::hac::GameCardHeader::setPartitionFsAddress(uint64_t address)
{
	mPartitionFsHeaderAddress = address;
}

uint64_t pie::hac::GameCardHeader::getPartitionFsSize() const
{
	return mPartitionFsHeaderSize;
}

void pie::hac::GameCardHeader::setPartitionFsSize(uint64_t size)
{
	mPartitionFsHeaderSize = size;
}

const pie::hac::detail::sha256_hash_t& pie::hac::GameCardHeader::getPartitionFsHash() const
{
	return mPartitionFsHeaderHash;
}

void pie::hac::GameCardHeader::setPartitionFsHash(const pie::hac::detail::sha256_hash_t& hash)
{
	mPartitionFsHeaderHash = hash;
}

const pie::hac::detail::sha256_hash_t& pie::hac::GameCardHeader::getInitialDataHash() const
{
	return mInitialDataHash;
}

void pie::hac::GameCardHeader::setInitialDataHash(const pie::hac::detail::sha256_hash_t& hash)
{
	mInitialDataHash = hash;
}

uint32_t pie::hac::GameCardHeader::getSelSec() const
{
	return mSelSec;
}

void pie::hac::GameCardHeader::setSelSec(uint32_t sel_sec)
{
	mSelSec = sel_sec;
}

uint32_t pie::hac::GameCardHeader::getSelT1Key() const
{
	return mSelT1Key;
}

void pie::hac::GameCardHeader::setSelT1Key(uint32_t sel_t1_key)
{
	mSelT1Key = sel_t1_key;
}

uint32_t pie::hac::GameCardHeader::getSelKey() const
{
	return mSelKey;
}

void pie::hac::GameCardHeader::setSelKey(uint32_t sel_key)
{
	mSelKey = sel_key;
}

uint32_t pie::hac::GameCardHeader::getLimAreaPage() const
{
	return mLimAreaPage;
}

void pie::hac::GameCardHeader::setLimAreaPage(uint32_t page)
{
	mLimAreaPage = page;
}


uint64_t pie::hac::GameCardHeader::getFwVersion() const
{
	return mFwVersion;
}

void pie::hac::GameCardHeader::setFwVersion(uint64_t version)
{
	mFwVersion = version;
}

uint32_t pie::hac::GameCardHeader::getAccCtrl1() const
{
	return mAccCtrl1;
}

void pie::hac::GameCardHeader::setAccCtrl1(uint32_t acc_ctrl_1)
{
	mAccCtrl1 = acc_ctrl_1;
}

uint32_t pie::hac::GameCardHeader::getWait1TimeRead() const
{
	return mWait1TimeRead;
}

void pie::hac::GameCardHeader::setWait1TimeRead(uint32_t seconds)
{
	mWait1TimeRead = seconds;
}

uint32_t pie::hac::GameCardHeader::getWait2TimeRead() const
{
	return mWait2TimeRead;
}

void pie::hac::GameCardHeader::setWait2TimeRead(uint32_t seconds)
{
	mWait2TimeRead = seconds;
}

uint32_t pie::hac::GameCardHeader::getWait1TimeWrite() const
{
	return mWait1TimeWrite;
}

void pie::hac::GameCardHeader::setWait1TimeWrite(uint32_t seconds)
{
	mWait1TimeWrite = seconds;
}

uint32_t pie::hac::GameCardHeader::getWait2TimeWrite() const
{
	return mWait2TimeWrite;
}

void pie::hac::GameCardHeader::setWait2TimeWrite(uint32_t seconds)
{
	mWait2TimeWrite = seconds;
}

uint32_t pie::hac::GameCardHeader::getFwMode() const
{
	return mFwMode;
}

void pie::hac::GameCardHeader::setFwMode(uint32_t fw_mode)
{
	mFwMode = fw_mode;
}

uint32_t pie::hac::GameCardHeader::getUppVersion() const
{
	return mUppVersion;
}

void pie::hac::GameCardHeader::setUppVersion(uint32_t version)
{
	mUppVersion = version;
}

const std::vector<pie::hac::gc::HeaderFlags>& pie::hac::GameCardHeader::getFlags() const
{
	return mFlags;
}

void pie::hac::GameCardHeader::setFlags(const std::vector<pie::hac::gc::HeaderFlags>& flags)
{
	mFlags = flags;
}

const pie::hac::gc::upp_hash_t& pie::hac::GameCardHeader::getUppHash() const
{
	return mUppHash;
}

void pie::hac::GameCardHeader::setUppHash(const pie::hac::gc::upp_hash_t& hash)
{
	mUppHash = hash;
}

uint64_t pie::hac::GameCardHeader::getUppId() const
{
	return mUppId;
}

void pie::hac::GameCardHeader::setUppId(uint64_t id)
{
	mUppId = id;
}

