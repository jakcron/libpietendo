	/**
	 * @file romfs.h
	 * @brief Declaration of RomFs structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace romfs
{
	static const int64_t kRomfsHeaderAlign = 0x200;
	static const uint32_t kInvalidAddr = 0xffffffff;
}

#pragma pack(push,1)

struct sRomfsHeader
{
	struct sSection
	{
		tc::bn::le64<int64_t> offset;
		tc::bn::le64<int64_t> size;
	};

	tc::bn::le64<int64_t> header_size;
	sSection dir_hash_bucket;
	sSection dir_entry;
	sSection file_hash_bucket;
	sSection file_entry;
	tc::bn::le64<int64_t> data_offset;
};
static_assert(sizeof(sRomfsHeader) == 0x50, "sRomfsHeader size.");

#ifdef _WIN32
#pragma warning(disable : 4200) // silence warnings for usage of empty arrays in stucts (for char name[];)
#endif

struct sRomfsDirEntry
{
	tc::bn::le32<uint32_t> parent_offset;
	tc::bn::le32<uint32_t> sibling_offset;
	tc::bn::le32<uint32_t> child_offset;
	tc::bn::le32<uint32_t> file_offset;
	tc::bn::le32<uint32_t> hash_sibling_offset;
	tc::bn::le32<uint32_t> name_size;
	char name[];
};
static_assert(sizeof(sRomfsDirEntry) == 0x18, "sRomfsDirEntry size.");

struct sRomfsFileEntry
{
	tc::bn::le32<uint32_t> parent_offset;
	tc::bn::le32<uint32_t> sibling_offset;
	tc::bn::le64<int64_t> data_offset;
	tc::bn::le64<int64_t> data_size;
	tc::bn::le32<uint32_t> hash_sibling_offset;
	tc::bn::le32<uint32_t> name_size;
	char name[];
};
static_assert(sizeof(sRomfsFileEntry) == 0x20, "sRomfsFileEntry size.");

#ifdef _WIN32
#pragma warning(default : 4200)
#endif

#pragma pack(pop)

}} // namespace pie::hac