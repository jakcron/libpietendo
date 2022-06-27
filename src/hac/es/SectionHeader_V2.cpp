#include <nn/es/SectionHeader_V2.h>

nn::es::SectionHeader_V2::SectionHeader_V2()
{}

nn::es::SectionHeader_V2::SectionHeader_V2(const SectionHeader_V2 & other)
{
	*this = other;
}

void nn::es::SectionHeader_V2::operator=(const SectionHeader_V2 & other)
{
	if (other.getBytes().size())
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		memset(mRawBinary.data(), 0, mRawBinary.size());
		mSectionOffset = other.mSectionOffset;
		mRecordSize = other.mRecordSize;
		mSectionSize = other.mSectionSize;
		mRecordNum = other.mRecordNum;
		mSectionType = other.mSectionType;
	}
}

bool nn::es::SectionHeader_V2::operator==(const SectionHeader_V2 & other) const
{
	return (mSectionOffset == other.mSectionOffset) \
		&& (mRecordSize == other.mRecordSize) \
		&& (mSectionSize == other.mSectionSize) \
		&& (mRecordNum == other.mRecordNum) \
		&& (mSectionType == other.mSectionType);
}

bool nn::es::SectionHeader_V2::operator!=(const SectionHeader_V2 & other) const
{
	return !(*this ==other);
}

void nn::es::SectionHeader_V2::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sSectionHeader_v2));
	sSectionHeader_v2* hdr = (sSectionHeader_v2*)mRawBinary.data();

	hdr->section_offset.wrap(mSectionOffset);
	hdr->record_size.wrap(mRecordSize);
	hdr->section_size.wrap(mSectionSize);
	hdr->record_num.wrap(mRecordNum);
	hdr->section_type.wrap(mSectionType);
}

void nn::es::SectionHeader_V2::fromBytes(const byte_t * bytes, size_t len)
{
	if (bytes == nullptr) { throw tc::ArgumentNullException(kModuleName, "bytes was null."); }
	if (len < sizeof(sSectionHeader_v2)) { throw tc::ArgumentOutOfRangeException(kModuleName, "Binary too small."); }

	clear();

	mRawBinary = tc::ByteData(sizeof(sSectionHeader_v2));
	memcpy(mRawBinary.data(), bytes, mRawBinary.size());
	sSectionHeader_v2* hdr = (sSectionHeader_v2*)mRawBinary.data();

	mSectionOffset = hdr->section_offset.unwrap();
	mRecordSize = hdr->record_size.unwrap();
	mSectionSize = hdr->section_size.unwrap();
	mRecordNum = hdr->record_num.unwrap();
	mSectionType = (ticket::SectionType)hdr->section_type.unwrap();
}

const tc::ByteData& nn::es::SectionHeader_V2::getBytes() const
{
	return mRawBinary;
}

void nn::es::SectionHeader_V2::clear()
{
	memset(mRawBinary.data(), 0, mRawBinary.size());
	mSectionOffset = 0;
	mRecordSize = 0;
	mSectionSize = 0;
	mRecordNum = 0;
	mSectionType = ticket::SECTION_PERMANENT;
}

uint32_t nn::es::SectionHeader_V2::getSectionOffset() const
{
	return mSectionOffset;
}

void nn::es::SectionHeader_V2::setSectionOffset(uint32_t offset)
{
	mSectionOffset = offset;
}

uint32_t nn::es::SectionHeader_V2::getRecordSize() const
{
	return mRecordSize;
}

void nn::es::SectionHeader_V2::setRecordSize(uint32_t size)
{
	mRecordSize = size;
}

uint32_t nn::es::SectionHeader_V2::getSectionSize() const
{
	return mSectionSize;
}

void nn::es::SectionHeader_V2::getSectionSize(uint32_t size)
{
	mSectionSize = size;
}

uint16_t nn::es::SectionHeader_V2::getRecordNum() const
{
	return mRecordNum;
}

void nn::es::SectionHeader_V2::setRecordNum(uint16_t record_num)
{
	mRecordNum = record_num;
}

nn::es::ticket::SectionType nn::es::SectionHeader_V2::getSectionType() const
{
	return mSectionType;
}

void nn::es::SectionHeader_V2::setSectionType(ticket::SectionType type)
{
	mSectionType = type;
}


