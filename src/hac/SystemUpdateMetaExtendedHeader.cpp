#include <nn/hac/SystemUpdateMetaExtendedHeader.h>

nn::hac::SystemUpdateMetaExtendedHeader::SystemUpdateMetaExtendedHeader()
{
	clear();
}

nn::hac::SystemUpdateMetaExtendedHeader::SystemUpdateMetaExtendedHeader(const SystemUpdateMetaExtendedHeader& other)
{
	*this = other;
}

void nn::hac::SystemUpdateMetaExtendedHeader::operator=(const SystemUpdateMetaExtendedHeader& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mExtendedDataSize = other.mExtendedDataSize;
}

bool nn::hac::SystemUpdateMetaExtendedHeader::operator==(const SystemUpdateMetaExtendedHeader& other) const
{
	return (mExtendedDataSize == other.mExtendedDataSize);
}

bool nn::hac::SystemUpdateMetaExtendedHeader::operator!=(const SystemUpdateMetaExtendedHeader& other) const
{
	return !(*this == other);
}

void nn::hac::SystemUpdateMetaExtendedHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sSystemUpdateMetaExtendedHeader));
	sSystemUpdateMetaExtendedHeader* info = (sSystemUpdateMetaExtendedHeader*)mRawBinary.data();

	info->extended_data_size.wrap(mExtendedDataSize);
}

void nn::hac::SystemUpdateMetaExtendedHeader::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sSystemUpdateMetaExtendedHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "SystemUpdateMetaExtendedHeader too small");
	}

	const sSystemUpdateMetaExtendedHeader* info = (const sSystemUpdateMetaExtendedHeader*)bytes;

	mExtendedDataSize = info->extended_data_size.unwrap();
}

const tc::ByteData& nn::hac::SystemUpdateMetaExtendedHeader::getBytes() const
{
	return mRawBinary;
}

void nn::hac::SystemUpdateMetaExtendedHeader::clear()
{
	mRawBinary = tc::ByteData();
	mExtendedDataSize = 0;
}

uint32_t nn::hac::SystemUpdateMetaExtendedHeader::getExtendedDataSize() const
{
	return mExtendedDataSize;
}

void nn::hac::SystemUpdateMetaExtendedHeader::setExtendedDataSize(uint32_t size)
{
	mExtendedDataSize = size;
}