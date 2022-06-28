#include <pietendo/hac/HierarchicalSha256Header.h>

#include <fmt/format.h>

pie::hac::HierarchicalSha256Header::HierarchicalSha256Header()
{
	clear();
}

pie::hac::HierarchicalSha256Header::HierarchicalSha256Header(const HierarchicalSha256Header & other)
{
	*this = other;
}

void pie::hac::HierarchicalSha256Header::operator=(const HierarchicalSha256Header & other)
{
	if (other.getBytes().size() != 0)
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		mMasterHash = other.mMasterHash;
		mHashBlockSize = other.mHashBlockSize;
		mLayerInfo = other.mLayerInfo;
	}
}

bool pie::hac::HierarchicalSha256Header::operator==(const HierarchicalSha256Header & other) const
{
	return (mMasterHash == other.mMasterHash) \
		&& (mHashBlockSize == other.mHashBlockSize) \
		&& (mLayerInfo == other.mLayerInfo);
}

bool pie::hac::HierarchicalSha256Header::operator!=(const HierarchicalSha256Header & other) const
{
	return !(*this == other);
}

void pie::hac::HierarchicalSha256Header::toBytes()
{
	throw tc::NotImplementedException(kModuleName, "toBytes() not implemented");
}

void pie::hac::HierarchicalSha256Header::fromBytes(const byte_t* data, size_t len)
{
	if (len < sizeof(pie::hac::sHierarchicalSha256Header))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Header too small");
	}

	const pie::hac::sHierarchicalSha256Header* hdr = (const pie::hac::sHierarchicalSha256Header*)data;

	if (hdr->layer_num.unwrap() != pie::hac::hierarchicalsha256::kDefaultLayerNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, fmt::format("Invalid layer count. (actual={:d}, expected={:d})", hdr->layer_num.unwrap(), pie::hac::hierarchicalsha256::kDefaultLayerNum));
	}

	mMasterHash = hdr->master_hash;
	mHashBlockSize = hdr->hash_block_size.unwrap();
	for (size_t i = 0; i < hdr->layer_num.unwrap(); i++)
	{
		mLayerInfo.push_back({hdr->layer[i].offset.unwrap(), hdr->layer[i].size.unwrap()});
	}
}

const tc::ByteData& pie::hac::HierarchicalSha256Header::getBytes() const
{
	return mRawBinary;
}

void pie::hac::HierarchicalSha256Header::clear()
{
	memset(mMasterHash.data(), 0, mMasterHash.size());
	mHashBlockSize = 0;
	mLayerInfo.clear();
}

const pie::hac::detail::sha256_hash_t& pie::hac::HierarchicalSha256Header::getMasterHash() const
{
	return mMasterHash;
}

void pie::hac::HierarchicalSha256Header::setMasterHash(const pie::hac::detail::sha256_hash_t& master_hash)
{
	mMasterHash = master_hash;
}

size_t pie::hac::HierarchicalSha256Header::getHashBlockSize() const
{
	return mHashBlockSize;
}

void pie::hac::HierarchicalSha256Header::setHashBlockSize(size_t hash_block_size)
{
	mHashBlockSize = hash_block_size;
}

const std::vector<pie::hac::HierarchicalSha256Header::sLayer>& pie::hac::HierarchicalSha256Header::getLayerInfo() const
{
	return mLayerInfo;
}

void pie::hac::HierarchicalSha256Header::setLayerInfo(const std::vector<sLayer>& layer_info)
{
	mLayerInfo = layer_info;
}