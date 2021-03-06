#include <pietendo/hac/PatchMetaExtendedHeader.h>

pie::hac::PatchMetaExtendedHeader::PatchMetaExtendedHeader()
{
	clear();
}

pie::hac::PatchMetaExtendedHeader::PatchMetaExtendedHeader(const PatchMetaExtendedHeader& other)
{
	*this = other;
}

void pie::hac::PatchMetaExtendedHeader::operator=(const PatchMetaExtendedHeader& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mApplicationId = other.mApplicationId;
	mRequiredSystemVersion = other.mRequiredSystemVersion;
	mExtendedDataSize = other.mExtendedDataSize;
}

bool pie::hac::PatchMetaExtendedHeader::operator==(const PatchMetaExtendedHeader& other) const
{
	return (mApplicationId == other.mApplicationId) \
		&& (mRequiredSystemVersion == other.mRequiredSystemVersion) \
		&& (mExtendedDataSize == other.mExtendedDataSize);
}

bool pie::hac::PatchMetaExtendedHeader::operator!=(const PatchMetaExtendedHeader& other) const
{
	return !(*this == other);
}

void pie::hac::PatchMetaExtendedHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sPatchMetaExtendedHeader));
	sPatchMetaExtendedHeader* info = (sPatchMetaExtendedHeader*)mRawBinary.data();

	info->application_id.wrap(mApplicationId);
	info->required_system_version.wrap(mRequiredSystemVersion);
	info->extended_data_size.wrap(mExtendedDataSize);
}

void pie::hac::PatchMetaExtendedHeader::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sPatchMetaExtendedHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "PatchMetaExtendedHeader too small");
	}

	const sPatchMetaExtendedHeader* info = (const sPatchMetaExtendedHeader*)bytes;

	mApplicationId = info->application_id.unwrap();
	mRequiredSystemVersion = info->required_system_version.unwrap();
	mExtendedDataSize = info->extended_data_size.unwrap();
}

const tc::ByteData& pie::hac::PatchMetaExtendedHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::PatchMetaExtendedHeader::clear()
{
	mRawBinary = tc::ByteData();
	mApplicationId = 0;
	mRequiredSystemVersion = 0;
	mExtendedDataSize = 0;
}

uint64_t pie::hac::PatchMetaExtendedHeader::getApplicationId() const
{
	return mApplicationId;
}

void pie::hac::PatchMetaExtendedHeader::setApplicationId(uint64_t application_id)
{
	mApplicationId = application_id;
}

uint32_t pie::hac::PatchMetaExtendedHeader::getRequiredSystemVersion() const
{
	return mRequiredSystemVersion;
}

void pie::hac::PatchMetaExtendedHeader::setRequiredSystemVersion(uint32_t sys_ver)
{
	mRequiredSystemVersion = sys_ver;
}

uint32_t pie::hac::PatchMetaExtendedHeader::getExtendedDataSize() const
{
	return mExtendedDataSize;
}

void pie::hac::PatchMetaExtendedHeader::setExtendedDataSize(uint32_t size)
{
	mExtendedDataSize = size;
}