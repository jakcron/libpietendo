	/**
	 * @file indirectstorage.h
	 * @brief Declaration of IndirectStorage structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>
#include <pietendo/hac/define/bktr.h>

namespace pie { namespace hac {

namespace indirectstorage
{
	static const int32_t kStorageCount = 2;
	static const size_t kNodeSize = 0x4000; // 16KB
}

#pragma pack(push,1)
struct sIndirectStorageEntry
{
	tc::bn::le64<int64_t> virt_offset;
	tc::bn::le64<int64_t> phys_offset;
	tc::bn::le32<int32_t> storage_index;
};
static_assert(sizeof(sIndirectStorageEntry) == 0x14, "sIndirectStorageEntry size.");
#pragma pack(pop)

}} // namespace pie::hac