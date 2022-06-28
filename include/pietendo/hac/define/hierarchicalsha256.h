	/**
	 * @file hierarchicalsha256.h
	 * @brief Declaration of HierarchicalSha256 structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace hierarchicalsha256
{
	static const size_t kDefaultLayerNum = 2;
	static const size_t kMaxLayerNum = 2;
}

#pragma pack(push,1)

struct sHierarchicalSha256Header
{
	struct sLayer
	{
		tc::bn::le64<int64_t> offset;
		tc::bn::le64<int64_t> size;
	};

	detail::sha256_hash_t master_hash;
	tc::bn::le32<uint32_t> hash_block_size;
	tc::bn::le32<uint32_t> layer_num;
	std::array<sLayer, hierarchicalsha256::kMaxLayerNum> layer;
};
static_assert(sizeof(sHierarchicalSha256Header) == 0x48, "sHierarchicalSha256Header size.");

#pragma pack(pop)

}} // namespace pie::hac