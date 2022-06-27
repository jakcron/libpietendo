#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace bktr
	{
		static const uint32_t kBktrStructMagic = tc::bn::make_struct_magic_uint32("BKTR");
		static const uint32_t kBktrVersion = 1;

		static const size_t kNodeSizeMin = 0x400; // 1KB
		static const size_t kNodeSizeMax = 0x80000; // 512KB
	}

#pragma pack(push,1)
	struct sBucketTreeHeader
	{	
		tc::bn::le32<uint32_t> st_magic; // BKTR
		tc::bn::le32<int32_t> version;
		tc::bn::le32<int32_t> entry_count;
		std::array<byte_t, 0x4> reserved_0;
	};
	static_assert(sizeof(sBucketTreeHeader) == 0x10, "sBucketTreeHeader size.");

	struct sBucketTreeNodeHeader
	{
		tc::bn::le32<int32_t> index;
		tc::bn::le32<int32_t> count;
		tc::bn::le64<int64_t> offset;
	};
	static_assert(sizeof(sBucketTreeNodeHeader) == 0x10, "sBucketTreeNodeHeader size.");
#pragma pack(pop)
}
}