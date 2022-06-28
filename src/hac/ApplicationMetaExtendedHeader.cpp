#include <pietendo/hac/ApplicationMetaExtendedHeader.h>

pie::hac::ApplicationMetaExtendedHeader::ApplicationMetaExtendedHeader()
{
	clear();
}

pie::hac::ApplicationMetaExtendedHeader::ApplicationMetaExtendedHeader(const ApplicationMetaExtendedHeader& other)
{
	*this = other;
}

void pie::hac::ApplicationMetaExtendedHeader::operator=(const ApplicationMetaExtendedHeader& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mPatchId = other.mPatchId;
	mRequiredSystemVersion = other.mRequiredSystemVersion;
	mRequiredApplicationVersion = other.mRequiredApplicationVersion;
}

bool pie::hac::ApplicationMetaExtendedHeader::operator==(const ApplicationMetaExtendedHeader& other) const
{
	return (mPatchId == other.mPatchId) \
		&& (mRequiredSystemVersion == other.mRequiredSystemVersion) \
		&& (mRequiredApplicationVersion == other.mRequiredApplicationVersion);
}

bool pie::hac::ApplicationMetaExtendedHeader::operator!=(const ApplicationMetaExtendedHeader& other) const
{
	return !(*this == other);
}

void pie::hac::ApplicationMetaExtendedHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sApplicationMetaExtendedHeader));
	sApplicationMetaExtendedHeader* info = (sApplicationMetaExtendedHeader*)mRawBinary.data();

	info->patch_id.wrap(mPatchId);
	info->required_system_version.wrap(mRequiredSystemVersion);
	info->required_application_version.wrap(mRequiredApplicationVersion);
}

void pie::hac::ApplicationMetaExtendedHeader::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sApplicationMetaExtendedHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ApplicationMetaExtendedHeader too small");
	}

	const sApplicationMetaExtendedHeader* info = (const sApplicationMetaExtendedHeader*)bytes;

	mPatchId = info->patch_id.unwrap();
	mRequiredSystemVersion = info->required_system_version.unwrap();
	mRequiredApplicationVersion = info->required_application_version.unwrap();
}

const tc::ByteData& pie::hac::ApplicationMetaExtendedHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::ApplicationMetaExtendedHeader::clear()
{
	mRawBinary = tc::ByteData();
	mPatchId = 0;
	mRequiredSystemVersion = 0;
	mRequiredApplicationVersion = 0;
}

uint64_t pie::hac::ApplicationMetaExtendedHeader::getPatchId() const
{
	return mPatchId;
}

void pie::hac::ApplicationMetaExtendedHeader::setPatchId(uint64_t application_id)
{
	mPatchId = application_id;
}

uint32_t pie::hac::ApplicationMetaExtendedHeader::getRequiredSystemVersion() const
{
	return mRequiredSystemVersion;
}

void pie::hac::ApplicationMetaExtendedHeader::setRequiredSystemVersion(uint32_t sys_ver)
{
	mRequiredSystemVersion = sys_ver;
}

uint32_t pie::hac::ApplicationMetaExtendedHeader::getRequiredApplicationVersion() const
{
	return mRequiredApplicationVersion;
}

void pie::hac::ApplicationMetaExtendedHeader::setRequiredApplicationVersion(uint32_t app_ver)
{
	mRequiredApplicationVersion = app_ver;
}