#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace ini
	{
		static const uint32_t kIniStructMagic = tc::bn::make_struct_magic_uint32("INI1");
		static const size_t kMaxKipNum = 0x50;
	}
	
#pragma pack(push,1)
	struct sIniHeader
	{
		tc::bn::le32<uint32_t> st_magic;
		tc::bn::le32<uint32_t> size;
		tc::bn::le32<uint32_t> kip_num;
		std::array<byte_t, 0x4> reserved_01;
	};
	static_assert(sizeof(sIniHeader) == 0x10, "sIniHeader size.");
#pragma pack(pop)
}
}