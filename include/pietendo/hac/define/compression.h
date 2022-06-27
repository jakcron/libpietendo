#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace compression
	{
		// defines
		static const size_t kRomfsBlockSize = 0x10000;
		static const size_t kRomfsBlockAlign = 0x10;

		// enums
		enum class CompressionType : byte_t
		{
			None,
			Lz4
		};
	}
	
#pragma pack(push,1)
	// structures
	struct sCompressionEntry
	{
		tc::bn::le64<uint64_t> virtual_offset;
		tc::bn::le64<uint64_t> physical_offset;
		byte_t compression_type;
		std::array<byte_t, 0x3> reserved;
		tc::bn::le32<uint32_t> physical_size;
	};
	static_assert(sizeof(sCompressionEntry) == 24, "sCompressionEntry size.");

#pragma pack(pop)
}
}