#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace delta
	{
		static const uint32_t kDeltaStructMagic = tc::bn::make_struct_magic_uint32("NDV0");
	}
#pragma pack(push,1)
	struct sDeltaHeader
	{
		tc::bn::le32<uint32_t> st_magic;
		std::array<byte_t, 0x4> reserved_00;
		tc::bn::le64<uint64_t> source_size;
		tc::bn::le64<uint64_t> destination_size;
		tc::bn::le64<uint64_t> header_size;
		tc::bn::le64<uint64_t> body_size;
		std::array<byte_t, 0x18> reserved_01;
	};
	static_assert(sizeof(sDeltaHeader) == 0x40, "sDeltaHeader size.");
#pragma pack(pop)
}
}
