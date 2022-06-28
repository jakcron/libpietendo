#include <pietendo/hac/AddOnContentMetaExtendedHeader.h>

pie::hac::AddOnContentMetaExtendedHeader::AddOnContentMetaExtendedHeader()
{
	clear();
}

pie::hac::AddOnContentMetaExtendedHeader::AddOnContentMetaExtendedHeader(const AddOnContentMetaExtendedHeader& other)
{
	*this = other;
}

void pie::hac::AddOnContentMetaExtendedHeader::operator=(const AddOnContentMetaExtendedHeader& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mApplicationId = other.mApplicationId;
	mRequiredApplicationVersion = other.mRequiredApplicationVersion;
}

bool pie::hac::AddOnContentMetaExtendedHeader::operator==(const AddOnContentMetaExtendedHeader& other) const
{
	return (mApplicationId == other.mApplicationId) \
		&& (mRequiredApplicationVersion == other.mRequiredApplicationVersion);
}

bool pie::hac::AddOnContentMetaExtendedHeader::operator!=(const AddOnContentMetaExtendedHeader& other) const
{
	return !(*this == other);
}

void pie::hac::AddOnContentMetaExtendedHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sAddOnContentMetaExtendedHeader));
	sAddOnContentMetaExtendedHeader* info = (sAddOnContentMetaExtendedHeader*)mRawBinary.data();

	info->application_id.wrap(mApplicationId);
	info->required_application_version.wrap(mRequiredApplicationVersion);
}

void pie::hac::AddOnContentMetaExtendedHeader::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sAddOnContentMetaExtendedHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AddOnContentMetaExtendedHeader too small");
	}

	const sAddOnContentMetaExtendedHeader* info = (const sAddOnContentMetaExtendedHeader*)bytes;

	mApplicationId = info->application_id.unwrap();
	mRequiredApplicationVersion = info->required_application_version.unwrap();
}

const tc::ByteData& pie::hac::AddOnContentMetaExtendedHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::AddOnContentMetaExtendedHeader::clear()
{
	mRawBinary = tc::ByteData();
	mApplicationId = 0;
	mRequiredApplicationVersion = 0;
}

uint64_t pie::hac::AddOnContentMetaExtendedHeader::getApplicationId() const
{
	return mApplicationId;
}

void pie::hac::AddOnContentMetaExtendedHeader::setApplicationId(uint64_t application_id)
{
	mApplicationId = application_id;
}

uint32_t pie::hac::AddOnContentMetaExtendedHeader::getRequiredApplicationVersion() const
{
	return mRequiredApplicationVersion;
}

void pie::hac::AddOnContentMetaExtendedHeader::setRequiredApplicationVersion(uint32_t sys_ver)
{
	mRequiredApplicationVersion = sys_ver;
}