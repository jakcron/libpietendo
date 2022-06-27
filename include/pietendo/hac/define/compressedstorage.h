#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/define/bktr.h>

namespace nn
{
namespace hac
{
	namespace compressedstorage
	{
		static const size_t kNodeSize = 0x4000; // 16KB
		static const int8_t kDefaultCompressionLevel = 0;

		enum CompressionType
		{
			CompressionType_None = 0,
			CompressionType_Lz4  = 3
		};
	}

#pragma pack(push,1)
	struct sCompressedStorageEntry
	{
		tc::bn::le64<int64_t> virt_offset;
		tc::bn::le64<int64_t> phys_offset;
		byte_t                compression_type;
		int8_t                compression_level;               
		tc::bn::pad<2>        reserved_0;
		tc::bn::le32<int32_t> phys_size;
	};
	static_assert(sizeof(sCompressedStorageEntry) == 0x18, "sCompressedStorageEntry size.");
#pragma pack(pop)
}
}