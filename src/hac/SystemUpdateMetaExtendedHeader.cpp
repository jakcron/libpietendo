#include <pietendo/hac/SystemUpdateMetaExtendedHeader.h>

pie::hac::SystemUpdateMetaExtendedHeader::SystemUpdateMetaExtendedHeader()
{
	clear();
}

pie::hac::SystemUpdateMetaExtendedHeader::SystemUpdateMetaExtendedHeader(const SystemUpdateMetaExtendedHeader& other)
{
	*this = other;
}

void pie::hac::SystemUpdateMetaExtendedHeader::operator=(const SystemUpdateMetaExtendedHeader& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mExtendedDataSize = other.mExtendedDataSize;
}

bool pie::hac::SystemUpdateMetaExtendedHeader::operator==(const SystemUpdateMetaExtendedHeader& other) const
{
	return (mExtendedDataSize == other.mExtendedDataSize);
}

bool pie::hac::SystemUpdateMetaExtendedHeader::operator!=(const SystemUpdateMetaExtendedHeader& other) const
{
	return !(*this == other);
}

void pie::hac::SystemUpdateMetaExtendedHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sSystemUpdateMetaExtendedHeader));
	sSystemUpdateMetaExtendedHeader* info = (sSystemUpdateMetaExtendedHeader*)mRawBinary.data();

	info->extended_data_size.wrap(mExtendedDataSize);
}

void pie::hac::SystemUpdateMetaExtendedHeader::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sSystemUpdateMetaExtendedHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "SystemUpdateMetaExtendedHeader too small");
	}

	const sSystemUpdateMetaExtendedHeader* info = (const sSystemUpdateMetaExtendedHeader*)bytes;

	mExtendedDataSize = info->extended_data_size.unwrap();
}

const tc::ByteData& pie::hac::SystemUpdateMetaExtendedHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::SystemUpdateMetaExtendedHeader::clear()
{
	mRawBinary = tc::ByteData();
	mExtendedDataSize = 0;
}

uint32_t pie::hac::SystemUpdateMetaExtendedHeader::getExtendedDataSize() const
{
	return mExtendedDataSize;
}

void pie::hac::SystemUpdateMetaExtendedHeader::setExtendedDataSize(uint32_t size)
{
	mExtendedDataSize = size;
}