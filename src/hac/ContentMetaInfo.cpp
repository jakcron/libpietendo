#include <pietendo/hac/ContentMetaInfo.h>

pie::hac::ContentMetaInfo::ContentMetaInfo()
{
	clear();
}

pie::hac::ContentMetaInfo::ContentMetaInfo(const ContentMetaInfo& other)
{
	*this = other;
}

void pie::hac::ContentMetaInfo::operator=(const ContentMetaInfo& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mTitleId = other.mTitleId;
	mTitleVersion = other.mTitleVersion;
	mType = other.mType;
	mAttribute = other.mAttribute;
}

bool pie::hac::ContentMetaInfo::operator==(const ContentMetaInfo& other) const
{
	return (mTitleId == other.mTitleId) \
		&& (mTitleVersion == other.mTitleVersion) \
		&& (mType == other.mType) \
		&& (mAttribute == other.mAttribute);
}

bool pie::hac::ContentMetaInfo::operator!=(const ContentMetaInfo& other) const
{
	return !(*this == other);
}

void pie::hac::ContentMetaInfo::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sContentMetaInfo));
	sContentMetaInfo* info = (sContentMetaInfo*)mRawBinary.data();

	info->id.wrap(mTitleId);
	info->version.wrap(mTitleVersion);
	info->type = (byte_t)mType;
	for (size_t i = 0; i < mAttribute.size(); i++)
	{
		info->attributes.set((size_t)mAttribute[i]);
	}
}

void pie::hac::ContentMetaInfo::fromBytes(const byte_t* bytes, size_t len)
{
	if (len < sizeof(sContentMetaInfo))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "ContentMetaInfo too small");
	}

	const sContentMetaInfo* info = (const sContentMetaInfo*)bytes;

	mTitleId = info->id.unwrap();
	mTitleVersion = info->version.unwrap();
	mType = (cnmt::ContentMetaType)info->type;
	for (size_t i = 0; i < info->attributes.bit_size(); i++)
	{
		if (info->attributes.test(i))
		{
			mAttribute.push_back((cnmt::ContentMetaAttributeFlag)i);
		}
	}
}

const tc::ByteData& pie::hac::ContentMetaInfo::getBytes() const
{
	return mRawBinary;
}

void pie::hac::ContentMetaInfo::clear()
{
	mRawBinary = tc::ByteData();
	mTitleId = 0;
	mTitleVersion = 0;
	mType = cnmt::ContentMetaType_Application;
	mAttribute.clear();
}

uint64_t pie::hac::ContentMetaInfo::getTitleId() const
{
	return mTitleId;
}

void pie::hac::ContentMetaInfo::setTitleId(uint64_t title_id)
{
	mTitleId = title_id;
}

uint32_t pie::hac::ContentMetaInfo::getTitleVersion() const
{
	return mTitleVersion;
}

void pie::hac::ContentMetaInfo::setTitleVersion(uint32_t ver)
{
	mTitleVersion = ver;
}	

pie::hac::cnmt::ContentMetaType pie::hac::ContentMetaInfo::getContentMetaType() const
{
	return mType;
}

void pie::hac::ContentMetaInfo::setContentMetaType(pie::hac::cnmt::ContentMetaType type)
{
	mType = type;
}	

const std::vector<pie::hac::cnmt::ContentMetaAttributeFlag>& pie::hac::ContentMetaInfo::getAttribute() const
{
	return mAttribute;
}

void pie::hac::ContentMetaInfo::setAttribute(const std::vector<pie::hac::cnmt::ContentMetaAttributeFlag>& attr)
{
	mAttribute = attr;
}
