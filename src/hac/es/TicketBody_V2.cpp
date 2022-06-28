#include <pietendo/hac/es/TicketBody_V2.h>
#include <bitset>

pie::hac::es::TicketBody_V2::TicketBody_V2()
{
	clear();
}

pie::hac::es::TicketBody_V2::TicketBody_V2(const TicketBody_V2 & other)
{
	*this = other;
}

void pie::hac::es::TicketBody_V2::operator=(const TicketBody_V2 & other)
{
	if (other.getBytes().size())
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		clear();
		mIssuer = other.mIssuer;
		mEncTitleKey = other.mEncTitleKey;
		mEncType = other.mEncType;
		mTicketVersion = other.mTicketVersion;
		mLicenseType = other.mLicenseType;
		mCommonKeyId = other.mCommonKeyId;
		mPropertyFlags = other.mPropertyFlags;
		mReservedRegion = other.mReservedRegion;
		mTicketId = other.mTicketId;
		mDeviceId = other.mDeviceId;
		mRightsId = other.mRightsId;
		mAccountId = other.mAccountId;
		mSectTotalSize = other.mSectTotalSize;
		mSectHeaderOffset = other.mSectHeaderOffset;
		mSectNum = other.mSectNum;
		mSectEntrySize = other.mSectEntrySize;
	}
}

bool pie::hac::es::TicketBody_V2::operator==(const TicketBody_V2 & other) const
{
	return (mIssuer == other.mIssuer) \
		&& (mEncTitleKey == other.mEncTitleKey) \
		&& (mEncType == other.mEncType) \
		&& (mTicketVersion == other.mTicketVersion) \
		&& (mLicenseType == other.mLicenseType) \
		&& (mPropertyFlags == other.mPropertyFlags) \
		&& (mReservedRegion == other.mReservedRegion) \
		&& (mTicketId == other.mTicketId) \
		&& (mDeviceId == other.mDeviceId) \
		&& (mRightsId == other.mRightsId) \
		&& (mAccountId == other.mAccountId) \
		&& (mSectTotalSize == other.mSectTotalSize) \
		&& (mSectHeaderOffset == other.mSectHeaderOffset) \
		&& (mSectNum == other.mSectNum) \
		&& (mSectEntrySize == other.mSectEntrySize);
}

bool pie::hac::es::TicketBody_V2::operator!=(const TicketBody_V2 & other) const
{
	return !(*this == other);
}

void pie::hac::es::TicketBody_V2::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sTicketBody_v2));
	sTicketBody_v2* body = (sTicketBody_v2*)mRawBinary.data();

	body->format_version = (ticket::kFormatVersion);

	body->issuer.encode(mIssuer);
	body->enc_title_key = mEncTitleKey;
	body->title_key_enc_type = (mEncType);
	body->ticket_version.wrap(mTicketVersion);
	body->license_type = mLicenseType;
	body->common_key_id = mCommonKeyId;
	for (size_t i = 0; i < mPropertyFlags.size(); i++)
	{
		body->property_mask.set((size_t)mPropertyFlags[i]);
	}
	body->reserved_region = mReservedRegion;
	body->ticket_id.wrap(mTicketId);
	body->device_id.wrap(mDeviceId);
	body->rights_id = mRightsId;
	body->account_id.wrap(mAccountId);
	body->sect_total_size.wrap(mSectTotalSize);
	body->sect_header_offset.wrap(mSectHeaderOffset);
	body->sect_num.wrap(mSectNum);
	body->sect_entry_size.wrap(mSectEntrySize);
}

void pie::hac::es::TicketBody_V2::fromBytes(const byte_t * bytes, size_t len)
{
	if (bytes == nullptr) { throw tc::ArgumentNullException(kModuleName, "bytes was null."); }
	if (len < sizeof(sSectionHeader_v2)) { throw tc::ArgumentOutOfRangeException(kModuleName, "Binary too small."); }


	clear();

	mRawBinary = tc::ByteData(sizeof(sTicketBody_v2));
	memcpy(mRawBinary.data(), bytes, mRawBinary.size());
	sTicketBody_v2* body = (sTicketBody_v2*)mRawBinary.data();

	if (body->format_version != ticket::kFormatVersion)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Unsupported format version");
	}

	mIssuer = body->issuer.decode();
	mEncTitleKey = body->enc_title_key;
	mEncType = (ticket::TitleKeyEncType)body->title_key_enc_type;
	mTicketVersion = body->ticket_version.unwrap();
	mLicenseType = (ticket::LicenseType)body->license_type;
	mCommonKeyId = body->common_key_id;
	for (size_t i = 0; i < body->property_mask.bit_size(); i++)
	{
		if (body->property_mask.test(i))
			mPropertyFlags.push_back((ticket::PropertyMaskFlags)i);
	}
	mReservedRegion = body->reserved_region;
	mTicketId = body->ticket_id.unwrap();
	mDeviceId = body->device_id.unwrap();
	mRightsId = body->rights_id;
	mAccountId = body->account_id.unwrap();
	mSectTotalSize = body->sect_total_size.unwrap();
	mSectHeaderOffset = body->sect_header_offset.unwrap();
	mSectNum = body->sect_num.unwrap();
	mSectEntrySize = body->sect_entry_size.unwrap();
}

const tc::ByteData& pie::hac::es::TicketBody_V2::getBytes() const
{
	return mRawBinary;
}

void pie::hac::es::TicketBody_V2::clear()
{
	mRawBinary = tc::ByteData();
	mIssuer.clear();
	mEncTitleKey.fill(0);
	mEncType = ticket::AES128_CBC;
	mTicketVersion = 0;
	mLicenseType = ticket::LICENSE_PERMANENT;
	mCommonKeyId = 0;
	mPropertyFlags.clear();
	mReservedRegion.fill(0);
	mTicketId = 0;
	mDeviceId = 0;
	mRightsId.fill(0);
	mAccountId = 0;
	mSectTotalSize = 0;
	mSectHeaderOffset = 0;
	mSectNum = 0;
	mSectEntrySize = 0;
}

const std::string & pie::hac::es::TicketBody_V2::getIssuer() const
{
	return mIssuer;
}

void pie::hac::es::TicketBody_V2::setIssuer(const std::string & issuer)
{
	if (issuer.length() > ticket::kIssuerSize)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Issuer is too long");
	}

	mIssuer = issuer;
}

const byte_t * pie::hac::es::TicketBody_V2::getEncTitleKey() const
{
	return mEncTitleKey.data();
}

void pie::hac::es::TicketBody_V2::setEncTitleKey(const byte_t * data, size_t len)
{
	mEncTitleKey.fill(0);
	memcpy(mEncTitleKey.data(), data, std::min<size_t>(len, mEncTitleKey.size()));
}

pie::hac::es::ticket::TitleKeyEncType pie::hac::es::TicketBody_V2::getTitleKeyEncType() const
{
	return mEncType;
}

void pie::hac::es::TicketBody_V2::setTitleKeyEncType(ticket::TitleKeyEncType type)
{
	mEncType = type;
}

uint16_t pie::hac::es::TicketBody_V2::getTicketVersion() const
{
	return mTicketVersion;
}

void pie::hac::es::TicketBody_V2::setTicketVersion(uint16_t version)
{
	mTicketVersion = version;
}

pie::hac::es::ticket::LicenseType pie::hac::es::TicketBody_V2::getLicenseType() const
{
	return mLicenseType;
}

void pie::hac::es::TicketBody_V2::setLicenseType(ticket::LicenseType type)
{
	mLicenseType = type;
}

byte_t pie::hac::es::TicketBody_V2::getCommonKeyId() const
{
	return mCommonKeyId;
}

void pie::hac::es::TicketBody_V2::setCommonKeyId(byte_t id)
{
	mCommonKeyId = id;
}

const std::vector<pie::hac::es::ticket::PropertyMaskFlags>& pie::hac::es::TicketBody_V2::getPropertyFlags() const
{
	return mPropertyFlags;
}

void pie::hac::es::TicketBody_V2::setPropertyFlags(const std::vector<pie::hac::es::ticket::PropertyMaskFlags>& flags)
{
	mPropertyFlags = flags;
}

const byte_t * pie::hac::es::TicketBody_V2::getReservedRegion() const
{
	return mReservedRegion.data();
}

void pie::hac::es::TicketBody_V2::setReservedRegion(const byte_t * data, size_t len)
{
	mReservedRegion.fill(0);
	memcpy(mReservedRegion.data(), data, std::min<size_t>(len, mReservedRegion.size()));
}

uint64_t pie::hac::es::TicketBody_V2::getTicketId() const
{
	return mTicketId;
}

void pie::hac::es::TicketBody_V2::setTicketId(uint64_t id)
{
	mTicketId = id;
}

uint64_t pie::hac::es::TicketBody_V2::getDeviceId() const
{
	return mDeviceId;
}

void pie::hac::es::TicketBody_V2::setDeviceId(uint64_t id)
{
	mDeviceId = id;
}

const byte_t * pie::hac::es::TicketBody_V2::getRightsId() const
{
	return mRightsId.data();
}

void pie::hac::es::TicketBody_V2::setRightsId(const byte_t * id)
{
	mRightsId.fill(0);
	memcpy(mRightsId.data(), id, mRightsId.size());
}

uint32_t pie::hac::es::TicketBody_V2::getAccountId() const
{
	return mAccountId;
}

void pie::hac::es::TicketBody_V2::setAccountId(uint32_t id)
{
	mAccountId = id;
}

uint32_t pie::hac::es::TicketBody_V2::getSectionTotalSize() const
{
	return mSectTotalSize;
}

void pie::hac::es::TicketBody_V2::setSectionTotalSize(uint32_t size)
{
	mSectTotalSize = size;
}

uint32_t pie::hac::es::TicketBody_V2::getSectionHeaderOffset() const
{
	return mSectHeaderOffset;
}

void pie::hac::es::TicketBody_V2::setSectionHeaderOffset(uint32_t offset)
{
	mSectHeaderOffset = offset;
}

uint16_t pie::hac::es::TicketBody_V2::getSectionNum() const
{
	return mSectNum;
}

void pie::hac::es::TicketBody_V2::setSectionNum(uint16_t num)
{
	mSectNum = num;
}

uint16_t pie::hac::es::TicketBody_V2::getSectionEntrySize() const
{
	return mSectEntrySize;
}

void pie::hac::es::TicketBody_V2::setSectionEntrySize(uint16_t size)
{
	mSectEntrySize = size;
}