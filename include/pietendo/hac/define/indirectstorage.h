#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/bktr.h>

namespace nn
{
namespace hac
{
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
}
}