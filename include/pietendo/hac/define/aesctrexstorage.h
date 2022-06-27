#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/bktr.h>

namespace nn
{
namespace hac
{
	namespace aesctrexstorage
	{
		static const size_t kNodeSize = 0x4000; // 16KB
	}

#pragma pack(push,1)
	struct sAesCtrExStorageEntry
	{
		tc::bn::le64<int64_t> offset;
		tc::bn::pad<4>        reserved;
		tc::bn::le32<int32_t> generation;
	};
	static_assert(sizeof(sAesCtrExStorageEntry) == 0x10, "sAesCtrExStorageEntry size.");
#pragma pack(pop)
}
}