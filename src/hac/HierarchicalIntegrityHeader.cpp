#include <pietendo/hac/HierarchicalIntegrityHeader.h>

#include <fmt/format.h>

pie::hac::HierarchicalIntegrityHeader::HierarchicalIntegrityHeader()
{
	clear();
}

pie::hac::HierarchicalIntegrityHeader::HierarchicalIntegrityHeader(const HierarchicalIntegrityHeader & other)
{
	*this = other;
}

void pie::hac::HierarchicalIntegrityHeader::operator=(const HierarchicalIntegrityHeader & other)
{
	if (other.getBytes().size() != 0)
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		clear();
		mLayerInfo = other.mLayerInfo;
		mMasterHashList = other.mMasterHashList;
	}
}

bool pie::hac::HierarchicalIntegrityHeader::operator==(const HierarchicalIntegrityHeader & other) const
{
	return (mLayerInfo == other.mLayerInfo) \
		&& (mMasterHashList == other.mMasterHashList);
}

bool pie::hac::HierarchicalIntegrityHeader::operator!=(const HierarchicalIntegrityHeader & other) const
{
	return !(*this == other);
}

void pie::hac::HierarchicalIntegrityHeader::toBytes()
{
	throw tc::NotImplementedException(kModuleName, "toBytes() not implemented");
}

void pie::hac::HierarchicalIntegrityHeader::fromBytes(const byte_t* data, size_t len)
{
	// validate size for at least header
	if (len < sizeof(pie::hac::sHierarchicalIntegrityHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Header too small");
	}

	const pie::hac::sHierarchicalIntegrityHeader* hdr = (const pie::hac::sHierarchicalIntegrityHeader*)data;

	// Validate Header Sig "IVFC"
	if (hdr->st_magic.unwrap() != hierarchicalintegrity::kStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Invalid struct magic");
	}

	// Validate TypeId
	if (hdr->type_id.unwrap() != (uint32_t)pie::hac::hierarchicalintegrity::TypeId::HAC_RomFs)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, fmt::format("Unsupported type id (0x{:x})", hdr->type_id.unwrap()));
	}

	// Validate Layer Num
	if (hdr->layer_num.unwrap() != hierarchicalintegrity::kDefaultLayerNumForRomFs+1)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, fmt::format("Invalid layer count. (actual={:d}, expected={:d})", hdr->layer_num.unwrap(), pie::hac::hierarchicalintegrity::kDefaultLayerNumForRomFs + 1));
	}
	
	// Get Sizes/Offsets
	size_t master_hash_offset = align((sizeof(pie::hac::sHierarchicalIntegrityHeader) + sizeof(pie::hac::sHierarchicalIntegrityLayerInfo) * hdr->layer_num.unwrap()), pie::hac::hierarchicalintegrity::kHeaderAlignLen);
	size_t total_size = master_hash_offset + hdr->master_hash_size.unwrap();

	// Validate total size
	if (len < total_size)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Header too small");
	}

	// copy to internal storage
	mRawBinary = tc::ByteData(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// save layer info
	const pie::hac::sHierarchicalIntegrityLayerInfo* layer_info = (const pie::hac::sHierarchicalIntegrityLayerInfo*)(mRawBinary.data() + sizeof(pie::hac::sHierarchicalIntegrityHeader));
	for (size_t i = 0; i < hierarchicalintegrity::kDefaultLayerNumForRomFs; i++)
	{
		mLayerInfo.push_back({layer_info[i].offset.unwrap(), layer_info[i].size.unwrap(), (int64_t)1 << (int64_t)layer_info[i].block_size.unwrap()});
	}

	// save hash list
	const detail::sha256_hash_t* hash_list = (const detail::sha256_hash_t*)(mRawBinary.data() + master_hash_offset);
	for (size_t i = 0; i < hdr->master_hash_size.unwrap()/sizeof(detail::sha256_hash_t); i++)
	{
		mMasterHashList.push_back(hash_list[i]);
	}
}

const tc::ByteData& pie::hac::HierarchicalIntegrityHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::HierarchicalIntegrityHeader::clear()
{
	mLayerInfo.clear();
	mMasterHashList.clear();
}

const std::vector<pie::hac::HierarchicalIntegrityHeader::sLayer>& pie::hac::HierarchicalIntegrityHeader::getLayerInfo() const
{
	return mLayerInfo;
}

void pie::hac::HierarchicalIntegrityHeader::setLayerInfo(const std::vector<sLayer>& layer_info)
{
	mLayerInfo = layer_info;
}

const std::vector<pie::hac::detail::sha256_hash_t>& pie::hac::HierarchicalIntegrityHeader::getMasterHashList() const
{
	return mMasterHashList;
}

void pie::hac::HierarchicalIntegrityHeader::setMasterHashList(const std::vector<pie::hac::detail::sha256_hash_t>& master_hash_list)
{
	mMasterHashList = master_hash_list;
}