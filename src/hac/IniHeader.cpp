#include <nn/hac/IniHeader.h>

nn::hac::IniHeader::IniHeader()
{
	clear();
}

nn::hac::IniHeader::IniHeader(const IniHeader& other)
{
	*this = other;
}

void nn::hac::IniHeader::operator=(const IniHeader& other)
{
	clear();
	this->mSize = other.mSize;
	this->mKipNum = other.mKipNum;
}

bool nn::hac::IniHeader::operator==(const IniHeader& other) const
{
	return (this->mSize == other.mSize) \
		&& (this->mKipNum == other.mKipNum);
}

bool nn::hac::IniHeader::operator!=(const IniHeader& other) const
{
	return !(*this == other);
}

void nn::hac::IniHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sIniHeader));
	nn::hac::sIniHeader* hdr = (nn::hac::sIniHeader*)mRawBinary.data();

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

void nn::hac::IniHeader::fromBytes(const byte_t* data, size_t len)
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
	const nn::hac::sIniHeader* hdr = (const nn::hac::sIniHeader*)mRawBinary.data();
	
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

const tc::ByteData& nn::hac::IniHeader::getBytes() const
{
	return mRawBinary;
}

void nn::hac::IniHeader::clear()
{
	mRawBinary = tc::ByteData();
	mSize = 0;
	mKipNum = 0;
}

uint32_t nn::hac::IniHeader::getSize() const
{
	return mSize;
}

void nn::hac::IniHeader::setSize(uint32_t size)
{
	mSize = size;
}

uint32_t nn::hac::IniHeader::getKipNum() const
{
	return mKipNum;
}

void nn::hac::IniHeader::setKipNum(uint32_t num)
{
	mKipNum = num;
}