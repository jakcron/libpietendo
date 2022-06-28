#include <pietendo/hac/IniHeader.h>

pie::hac::IniHeader::IniHeader()
{
	clear();
}

pie::hac::IniHeader::IniHeader(const IniHeader& other)
{
	*this = other;
}

void pie::hac::IniHeader::operator=(const IniHeader& other)
{
	clear();
	this->mSize = other.mSize;
	this->mKipNum = other.mKipNum;
}

bool pie::hac::IniHeader::operator==(const IniHeader& other) const
{
	return (this->mSize == other.mSize) \
		&& (this->mKipNum == other.mKipNum);
}

bool pie::hac::IniHeader::operator!=(const IniHeader& other) const
{
	return !(*this == other);
}

void pie::hac::IniHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sIniHeader));
	pie::hac::sIniHeader* hdr = (pie::hac::sIniHeader*)mRawBinary.data();

	// set header identifers
	hdr->st_magic.wrap(ini::kIniStructMagic);
	
	if (mKipNum > ini::kMaxKipNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Cannot generate INI Header (Too many KIPs)");
	}

	// write variables
	hdr->size.wrap(mSize);
	hdr->kip_num.wrap(mKipNum);
}

void pie::hac::IniHeader::fromBytes(const byte_t* data, size_t len)
{
	// check input data size
	if (len < sizeof(sIniHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "INI header corrupt (header size is too small)");
	}

	// clear internal members
	clear();

	// allocate internal local binary copy
	mRawBinary = tc::ByteData(sizeof(sIniHeader));
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// get sIniHeader ptr
	const pie::hac::sIniHeader* hdr = (const pie::hac::sIniHeader*)mRawBinary.data();
	
	// check INI signature
	if (hdr->st_magic.unwrap() != ini::kIniStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "INI header corrupt (unrecognised header signature)");
	}

	// check KIP num
	if (hdr->kip_num.unwrap() > ini::kMaxKipNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "INI header corrupt (too many KIPs)");
	}

	// save variables
	mSize = hdr->size.unwrap();
	mKipNum = hdr->kip_num.unwrap();
}

const tc::ByteData& pie::hac::IniHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::IniHeader::clear()
{
	mRawBinary = tc::ByteData();
	mSize = 0;
	mKipNum = 0;
}

uint32_t pie::hac::IniHeader::getSize() const
{
	return mSize;
}

void pie::hac::IniHeader::setSize(uint32_t size)
{
	mSize = size;
}

uint32_t pie::hac::IniHeader::getKipNum() const
{
	return mKipNum;
}

void pie::hac::IniHeader::setKipNum(uint32_t num)
{
	mKipNum = num;
}