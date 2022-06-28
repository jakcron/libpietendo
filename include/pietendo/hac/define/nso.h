	/**
	 * @file nso.h
	 * @brief Declaration of NSO0 structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace nso
{
	static const uint32_t kNsoStructMagic = tc::bn::make_struct_magic_uint32("NSO0");
	static const uint32_t kDefaultFormatVersion = 0;
	static const size_t kModuleIdSize = 32;

	enum HeaderFlags
	{
		FLAG_TEXT_COMPRESS,
		FLAG_RO_COMPRESS,
		FLAG_DATA_COMPRESS,
		FLAG_TEXT_HASH,
		FLAG_RO_HASH,
		FLAG_DATA_HASH
	};
}

#pragma pack(push,1)

struct sNsoHeader
{
	struct sCodeSegment
	{
		tc::bn::le32<uint32_t> file_offset;
		tc::bn::le32<uint32_t> memory_offset;
		tc::bn::le32<uint32_t> size;
	};

	struct sSection
	{
		tc::bn::le32<uint32_t> offset;
		tc::bn::le32<uint32_t> size;
	};

	tc::bn::le32<uint32_t> st_magic;
	tc::bn::le32<uint32_t> format_version;
	std::array<byte_t, 0x4> reserved_1;
	tc::bn::bitarray<sizeof(uint32_t)> flags;
	sCodeSegment text;
	tc::bn::le32<uint32_t> module_name_offset;
	sCodeSegment ro;
	tc::bn::le32<uint32_t> module_name_size;
	sCodeSegment data;
	tc::bn::le32<uint32_t> bss_size;
	detail::module_id_t module_id;
	tc::bn::le32<uint32_t> text_file_size;
	tc::bn::le32<uint32_t> ro_file_size;
	tc::bn::le32<uint32_t> data_file_size;
	std::array<byte_t, 0x1C> reserved_2;
	sSection embedded;
	sSection dyn_str;
	sSection dyn_sym;
	detail::sha256_hash_t text_hash;
	detail::sha256_hash_t ro_hash;
	detail::sha256_hash_t data_hash;
};
static_assert(sizeof(sNsoHeader) == 0x100, "sNsoHeader size.");

#pragma pack(pop)

}} // namespace pie::hac