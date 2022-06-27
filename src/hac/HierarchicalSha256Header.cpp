#include <nn/hac/HierarchicalSha256Header.h>

#include <fmt/format.h>

nn::hac::HierarchicalSha256Header::HierarchicalSha256Header()
{
	clear();
}

nn::hac::HierarchicalSha256Header::HierarchicalSha256Header(const HierarchicalSha256Header & other)
{
	*this = other;
}

void nn::hac::HierarchicalSha256Header::operator=(const HierarchicalSha256Header & other)
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

bool nn::hac::HierarchicalSha256Header::operator==(const HierarchicalSha256Header & other) const
{
	return (mMasterHash == other.mMasterHash) \
		&& (mHashBlockSize == other.mHashBlockSize) \
		&& (mLayerInfo == other.mLayerInfo);
}

bool nn::hac::HierarchicalSha256Header::operator!=(const HierarchicalSha256Header & other) const
{
	return !(*this == other);
}

void nn::hac::HierarchicalSha256Header::toBytes()
{
	throw tc::NotImplementedException(kModuleName, "toBytes() not implemented");
}

void nn::hac::HierarchicalSha256Header::fromBytes(const byte_t* data, size_t len)
{
	if (len < sizeof(nn::hac::sHierarchicalSha256Header))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Header too small");
	}

	const nn::hac::sHierarchicalSha256Header* hdr = (const nn::hac::sHierarchicalSha256Header*)data;

	if (hdr->layer_num.unwrap() != nn::hac::hierarchicalsha256::kDefaultLayerNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, fmt::format("Invalid layer count. (actual={:d}, expected={:d})", hdr->layer_num.unwrap(), nn::hac::hierarchicalsha256::kDefaultLayerNum));
	}

	mMasterHash = hdr->master_hash;
	mHashBlockSize = hdr->hash_block_size.unwrap();
	for (size_t i = 0; i < hdr->layer_num.unwrap(); i++)
	{
		mLayerInfo.push_back({hdr->layer[i].offset.unwrap(), hdr->layer[i].size.unwrap()});
	}
}

const tc::ByteData& nn::hac::HierarchicalSha256Header::getBytes() const
{
	return mRawBinary;
}

void nn::hac::HierarchicalSha256Header::clear()
{
	memset(mMasterHash.data(), 0, mMasterHash.size());
	mHashBlockSize = 0;
	mLayerInfo.clear();
}

const nn::hac::detail::sha256_hash_t& nn::hac::HierarchicalSha256Header::getMasterHash() const
{
	return mMasterHash;
}

void nn::hac::HierarchicalSha256Header::setMasterHash(const nn::hac::detail::sha256_hash_t& master_hash)
{
	mMasterHash = master_hash;
}

size_t nn::hac::HierarchicalSha256Header::getHashBlockSize() const
{
	return mHashBlockSize;
}

void nn::hac::HierarchicalSha256Header::setHashBlockSize(size_t hash_block_size)
{
	mHashBlockSize = hash_block_size;
}

const std::vector<nn::hac::HierarchicalSha256Header::sLayer>& nn::hac::HierarchicalSha256Header::getLayerInfo() const
{
	return mLayerInfo;
}

void nn::hac::HierarchicalSha256Header::setLayerInfo(const std::vector<sLayer>& layer_info)
{
	mLayerInfo = layer_info;
}