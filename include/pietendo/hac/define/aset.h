#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace aset
	{
		static const uint32_t kAssetStructMagic = tc::bn::make_struct_magic_uint32("ASET");

		static const uint32_t kDefaultAssetFormatVersion = 0;
	}

#pragma pack(push,1)
	struct sAssetSection
	{
		tc::bn::le64<int64_t> offset;
		tc::bn::le64<int64_t> size;
	};

	struct sAssetHeader
	{
		tc::bn::le32<uint32_t> st_magic;
		tc::bn::le32<uint32_t> format_version;
		sAssetSection icon;
		sAssetSection nacp;
		sAssetSection romfs;
	};
#pragma pack(pop)
}
}