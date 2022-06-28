#include <pietendo/hac/ContentInfo.h>

pie::hac::ContentInfo::ContentInfo()
{
	clear();
}

pie::hac::ContentInfo::ContentInfo(const ContentInfo& other)
{
	*this = other;
}

void pie::hac::ContentInfo::operator=(const ContentInfo& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mHash = other.mHash;
	mContentId = other.mContentId;
	mSize = other.mSize;
	mType = other.mType;
}

bool pie::hac::ContentInfo::operator==(const ContentInfo& other) const
{
	return (mHash == other.mHash) \
		&& (mContentId == other.mContentId) \
		&& (mSize == other.mSize) \
		&& (mType == other.mType);
}

bool pie::hac::ContentInfo::operator!=(const ContentInfo& other) const
{
	return !(*this == other);
}

void pie::hac::ContentInfo::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sContentInfo));
	sContentInfo* info = (sContentInfo*)mRawBinary.data();

	info->content_hash = mHash;
	info->content_id = mContentId;
	info->size_lower.wrap(mSize & (uint32_t)(-1));
	info->size_higher.wrap((mSize >> 32) & (uint16_t)(-1));
	info->content_type = (byte_t)mType;
	info->id_offset = mIdOffset;
}

void pie::hac::ContentInfo::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sContentInfo))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ContentInfo too small");
	}

	const sContentInfo* info = (const sContentInfo*)bytes;

	mHash = info->content_hash;
	mContentId = info->content_id;
	mSize = (uint64_t)(info->size_lower.unwrap()) | (uint64_t)(info->size_higher.unwrap()) << 32;
	mType = (cnmt::ContentType)info->content_type;
	mIdOffset = info->id_offset;
}

const tc::ByteData& pie::hac::ContentInfo::getBytes() const
{
	return mRawBinary;
}

void pie::hac::ContentInfo::clear()
{
	mRawBinary = tc::ByteData();
}

const pie::hac::detail::sha256_hash_t& pie::hac::ContentInfo::getContentHash() const
{
	return mHash;
}

void pie::hac::ContentInfo::setContentHash(const pie::hac::detail::sha256_hash_t& hash)
{
	mHash = hash;
}

const pie::hac::cnmt::content_id_t& pie::hac::ContentInfo::getContentId() const
{
	return mContentId;
}

void pie::hac::ContentInfo::setContentId(const pie::hac::cnmt::content_id_t& content_id)
{
	mContentId = content_id;
}

size_t pie::hac::ContentInfo::getContentSize() const
{
	return mSize;
}

void pie::hac::ContentInfo::setContentSize(size_t size)
{
	mSize = size;
}

pie::hac::cnmt::ContentType pie::hac::ContentInfo::getContentType() const
{
	return mType;
}

void pie::hac::ContentInfo::setContentType(cnmt::ContentType type)
{
	mType = type;
}

byte_t pie::hac::ContentInfo::getIdOffset() const
{
	return mIdOffset;
}

void pie::hac::ContentInfo::setIdOffset(byte_t id_offset)
{
	mIdOffset = id_offset;
}