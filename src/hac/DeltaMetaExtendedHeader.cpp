#include <pietendo/hac/DeltaMetaExtendedHeader.h>

pie::hac::DeltaMetaExtendedHeader::DeltaMetaExtendedHeader()
{
	clear();
}

pie::hac::DeltaMetaExtendedHeader::DeltaMetaExtendedHeader(const DeltaMetaExtendedHeader& other)
{
	*this = other;
}

void pie::hac::DeltaMetaExtendedHeader::operator=(const DeltaMetaExtendedHeader& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mApplicationId = other.mApplicationId;
	mExtendedDataSize = other.mExtendedDataSize;
}

bool pie::hac::DeltaMetaExtendedHeader::operator==(const DeltaMetaExtendedHeader& other) const
{
	return (mApplicationId == other.mApplicationId) \
		&& (mExtendedDataSize == other.mExtendedDataSize);
}

bool pie::hac::DeltaMetaExtendedHeader::operator!=(const DeltaMetaExtendedHeader& other) const
{
	return !(*this == other);
}

void pie::hac::DeltaMetaExtendedHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sDeltaMetaExtendedHeader));
	sDeltaMetaExtendedHeader* info = (sDeltaMetaExtendedHeader*)mRawBinary.data();

	info->application_id.wrap(mApplicationId);
	info->extended_data_size.wrap(mExtendedDataSize);
}

void pie::hac::DeltaMetaExtendedHeader::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sDeltaMetaExtendedHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "DeltaMetaExtendedHeader too small");
	}

	const sDeltaMetaExtendedHeader* info = (const sDeltaMetaExtendedHeader*)bytes;

	mApplicationId = info->application_id.unwrap();
	mExtendedDataSize = info->extended_data_size.unwrap();
}

const tc::ByteData& pie::hac::DeltaMetaExtendedHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::DeltaMetaExtendedHeader::clear()
{
	mRawBinary = tc::ByteData();
	mApplicationId = 0;
	mExtendedDataSize = 0;
}

uint64_t pie::hac::DeltaMetaExtendedHeader::getApplicationId() const
{
	return mApplicationId;
}

void pie::hac::DeltaMetaExtendedHeader::setApplicationId(uint64_t application_id)
{
	mApplicationId = application_id;
}

uint32_t pie::hac::DeltaMetaExtendedHeader::getExtendedDataSize() const
{
	return mExtendedDataSize;
}

void pie::hac::DeltaMetaExtendedHeader::setExtendedDataSize(uint32_t size)
{
	mExtendedDataSize = size;
}