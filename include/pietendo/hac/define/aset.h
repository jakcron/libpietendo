	/**
	 * @file aset.h
	 * @brief Declaration of Homebrew NRO Asset structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

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

}} // namespace pie::hac