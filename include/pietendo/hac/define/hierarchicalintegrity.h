	/**
	 * @file hierarchicalintegrity.h
	 * @brief Declaration of HierarchicalIntegrity structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace hierarchicalintegrity
{
	static const uint32_t kStructMagic = tc::bn::make_struct_magic_uint32("IVFC");
	static const size_t kDefaultLayerNumForRomFs = 6;
	static const size_t kHeaderAlignLen = 0x20;
	static const size_t kSaltSourceLen = 0x20;
	static const size_t kHacRomfsMasterHashLen = 0x20;

	enum TypeId
	{
		TypeId_CTR_RomFs = 0x10000, // Nintendo 3DS
		TypeId_HAC_RomFs = 0x20000 // Nintendo Switch
	};
}

#pragma pack(push,1)

struct sHierarchicalIntegrityHeader
{
	tc::bn::le32<uint32_t> st_magic;
	tc::bn::le32<uint32_t> type_id;
	tc::bn::le32<uint32_t> master_hash_size;
	tc::bn::le32<uint32_t> layer_num;
};
static_assert(sizeof(sHierarchicalIntegrityHeader) == 0x10, "sHierarchicalIntegrityHeader size.");

struct sHierarchicalIntegrityLayerInfo
{
	tc::bn::le64<int64_t> offset;
	tc::bn::le64<int64_t> size;
	tc::bn::le32<uint32_t> block_size;
	std::array<byte_t, 0x4> reserved;
};
static_assert(sizeof(sHierarchicalIntegrityLayerInfo) == 0x18, "sHierarchicalIntegrityLayerInfo size.");

struct sHierarchicalIntegrityForHacRomfs
{
	sHierarchicalIntegrityHeader header;
	std::array<sHierarchicalIntegrityLayerInfo, hierarchicalintegrity::kDefaultLayerNumForRomFs> layer;
	std::array<byte_t, hierarchicalintegrity::kSaltSourceLen> salt_source;
	std::array<byte_t, hierarchicalintegrity::kHacRomfsMasterHashLen> master_hash;
};
static_assert(sizeof(sHierarchicalIntegrityForHacRomfs) == 0xE0, "sHierarchicalIntegrityForHacRomfs size.");

#pragma pack(pop)

}} // namespace pie::hac