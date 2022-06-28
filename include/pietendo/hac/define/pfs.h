	/**
	 * @file pfs.h
	 * @brief Declaration of PartitionFs structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace pfs
{
	static const uint32_t kPfsStructMagic = tc::bn::make_struct_magic_uint32("PFS0");
	static const uint32_t kHashedPfsStructMagic = tc::bn::make_struct_magic_uint32("HFS0");
	static const size_t kHeaderAlign = 64;
}

#pragma pack(push,1)

struct sPfsHeader
{
	tc::bn::le32<uint32_t> st_magic;
	tc::bn::le32<uint32_t> file_num;
	tc::bn::le32<uint32_t> name_table_size;
	std::array<byte_t, 0x04> padding;
};
static_assert(sizeof(sPfsHeader) == 0x10, "sPfsHeader size.");

struct sPfsFile
{
	tc::bn::le64<int64_t> data_offset;
	tc::bn::le64<int64_t> size;
	tc::bn::le32<uint32_t> name_offset;
	std::array<byte_t, 0x04> padding;
};
static_assert(sizeof(sPfsFile) == 0x18, "sPfsFile size.");

struct sHashedPfsFile
{
	tc::bn::le64<int64_t> data_offset;
	tc::bn::le64<int64_t> size;
	tc::bn::le32<uint32_t> name_offset;
	tc::bn::le32<uint32_t> hash_protected_size;
	std::array<byte_t, 0x08> padding;
	detail::sha256_hash_t hash;
};
static_assert(sizeof(sHashedPfsFile) == 0x40, "sHashedPfsFile size.");

#pragma pack(pop)

}} // namespace pie::hac