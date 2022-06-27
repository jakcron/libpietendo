#include <nn/hac/ContentMetaInfo.h>

nn::hac::ContentMetaInfo::ContentMetaInfo()
{
	clear();
}

nn::hac::ContentMetaInfo::ContentMetaInfo(const ContentMetaInfo& other)
{
	*this = other;
}

void nn::hac::ContentMetaInfo::operator=(const ContentMetaInfo& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mTitleId = other.mTitleId;
	mTitleVersion = other.mTitleVersion;
	mType = other.mType;
	mAttribute = other.mAttribute;
}

bool nn::hac::ContentMetaInfo::operator==(const ContentMetaInfo& other) const
{
	return (mTitleId == other.mTitleId) \
		&& (mTitleVersion == other.mTitleVersion) \
		&& (mType == other.mType) \
		&& (mAttribute == other.mAttribute);
}

bool nn::hac::ContentMetaInfo::operator!=(const ContentMetaInfo& other) const
{
	return !(*this == other);
}

void nn::hac::ContentMetaInfo::toBytes()
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

void nn::hac::ContentMetaInfo::fromBytes(const byte_t* bytes, size_t len)
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

const tc::ByteData& nn::hac::ContentMetaInfo::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ContentMetaInfo::clear()
{
	mRawBinary = tc::ByteData();
	mTitleId = 0;
	mTitleVersion = 0;
	mType = cnmt::ContentMetaType::Application;
	mAttribute.clear();
}

uint64_t nn::hac::ContentMetaInfo::getTitleId() const
{
	return mTitleId;
}

void nn::hac::ContentMetaInfo::setTitleId(uint64_t title_id)
{
	mTitleId = title_id;
}

uint32_t nn::hac::ContentMetaInfo::getTitleVersion() const
{
	return mTitleVersion;
}

void nn::hac::ContentMetaInfo::setTitleVersion(uint32_t ver)
{
	mTitleVersion = ver;
}	

nn::hac::cnmt::ContentMetaType nn::hac::ContentMetaInfo::getContentMetaType() const
{
	return mType;
}

void nn::hac::ContentMetaInfo::setContentMetaType(nn::hac::cnmt::ContentMetaType type)
{
	mType = type;
}	

const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& nn::hac::ContentMetaInfo::getAttribute() const
{
	return mAttribute;
}

void nn::hac::ContentMetaInfo::setAttribute(const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& attr)
{
	mAttribute = attr;
}
