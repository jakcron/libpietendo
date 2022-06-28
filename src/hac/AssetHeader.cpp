#include <pietendo/hac/AssetHeader.h>

pie::hac::AssetHeader::AssetHeader()
{
	clear();
}

pie::hac::AssetHeader::AssetHeader(const AssetHeader& other)
{
	*this = other;
}

void pie::hac::AssetHeader::operator=(const AssetHeader& other)
{
	mRawBinary = other.mRawBinary;
	mIconInfo = other.mIconInfo;
	mNacpInfo = other.mNacpInfo;
	mRomfsInfo = other.mRomfsInfo;
}

bool pie::hac::AssetHeader::operator==(const AssetHeader& other) const
{
	return (mIconInfo == other.mIconInfo) \
		&& (mNacpInfo == other.mNacpInfo) \
		&& (mRomfsInfo == other.mRomfsInfo);
}

bool pie::hac::AssetHeader::operator!=(const AssetHeader& other) const
{
	return !(*this == other);
}

void pie::hac::AssetHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sAssetHeader));
	pie::hac::sAssetHeader* hdr = (pie::hac::sAssetHeader*)mRawBinary.data();

	// set header identifers
	hdr->st_magic.wrap(aset::kAssetStructMagic);
	hdr->format_version.wrap(aset::kDefaultAssetFormatVersion);

	// set icon section
	hdr->icon.offset.wrap(mIconInfo.offset);
	hdr->icon.size.wrap(mIconInfo.size);

	// set nacp section
	hdr->nacp.offset.wrap(mNacpInfo.offset);
	hdr->nacp.size.wrap(mNacpInfo.size);

	// set romfs section
	hdr->romfs.offset.wrap(mRomfsInfo.offset);
	hdr->romfs.size.wrap(mRomfsInfo.size);
}

void pie::hac::AssetHeader::fromBytes(const byte_t* bytes, size_t len)
{
	// check input data size
	if (len < sizeof(sAssetHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ASET header size is too small");
	}

	// clear internal members
	clear();

	// allocate internal local binary copy
	mRawBinary = tc::ByteData(sizeof(sAssetHeader));
	memcpy(mRawBinary.data(), bytes, mRawBinary.size());

	// get sAssetHeader ptr
	const pie::hac::sAssetHeader* hdr = (const pie::hac::sAssetHeader*)mRawBinary.data();
	
	// check NRO signature
	if (hdr->st_magic.unwrap() != aset::kAssetStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ASET header corrupt (unrecognised header signature)");
	}

	// check NRO format version
	if (hdr->format_version.unwrap() != aset::kDefaultAssetFormatVersion)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ASET header corrupt (unsupported format version)");
	}

	mIconInfo.offset = hdr->icon.offset.unwrap();
	mIconInfo.size = hdr->icon.size.unwrap();
	mNacpInfo.offset = hdr->nacp.offset.unwrap();
	mNacpInfo.size = hdr->nacp.size.unwrap();
	mRomfsInfo.offset = hdr->romfs.offset.unwrap();
	mRomfsInfo.size = hdr->romfs.size.unwrap();
}

const tc::ByteData& pie::hac::AssetHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::AssetHeader::clear()
{
	mRawBinary = tc::ByteData();
	mIconInfo = sSection();
	mNacpInfo = sSection();
	mRomfsInfo = sSection();
}

const pie::hac::AssetHeader::sSection& pie::hac::AssetHeader::getIconInfo() const
{
	return mIconInfo;
}

void pie::hac::AssetHeader::setIconInfo(const pie::hac::AssetHeader::sSection& info)
{
	mIconInfo = info;
}

const pie::hac::AssetHeader::sSection& pie::hac::AssetHeader::getNacpInfo() const
{
	return mNacpInfo;
}

void pie::hac::AssetHeader::setNacpInfo(const sSection& info)
{
	mNacpInfo = info;
}

const pie::hac::AssetHeader::sSection& pie::hac::AssetHeader::getRomfsInfo() const
{
	return mRomfsInfo;
}

void pie::hac::AssetHeader::setRomfsInfo(const sSection& info)
{
	mRomfsInfo = info;
}