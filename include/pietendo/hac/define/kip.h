	/**
	 * @file kip.h
	 * @brief Declaration of KIP1 structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace kip
{
	static const uint32_t kKipStructMagic = tc::bn::make_struct_magic_uint32("KIP1");
	static const uint32_t kDefaultKipVersion = 1;
	static const size_t kNameMaxLen = 0xC;
	static const size_t kKernCapabilityNum = 0x20;
	static const size_t kKernCapabilitySize = kKernCapabilityNum * sizeof(uint32_t);
}

#pragma pack(push,1)

struct sKipHeader
{
	// sub struct definitions
	struct sFlag 
	{
		byte_t text_compress : 1;
		byte_t ro_compress : 1;
		byte_t data_compress : 1;
		byte_t is_64bit_instruction : 1;
		byte_t is_64bit_address_space : 1;
		byte_t use_secure_memory : 1;
		byte_t :0;
	};
	struct sCodeSegment
	{
		tc::bn::le32<uint32_t> memory_offset;
		tc::bn::le32<uint32_t> memory_size;
		tc::bn::le32<uint32_t> file_size;
	};

	// layout
	tc::bn::le32<uint32_t> st_magic;
	tc::bn::string<kip::kNameMaxLen> name;
	tc::bn::le64<uint64_t> title_id;
	tc::bn::le32<uint32_t> version;
	byte_t main_thread_priority;
	byte_t main_thread_cpu_id;
	byte_t reserved_01;
	sFlag flags;
	sCodeSegment text;
	byte_t reserved_02[4];
	sCodeSegment ro;
	tc::bn::le32<uint32_t> main_thread_stack_size;
	sCodeSegment data;
	std::array<byte_t, 0x4> reserved_03;
	sCodeSegment bss;
	std::array<byte_t, 0x4> reserved_04;
	std::array<byte_t, 0x20> reserved_05;
	std::array<byte_t, kip::kKernCapabilitySize> capabilities;
};
static_assert(sizeof(sKipHeader) == 0x100, "sKipHeader size.");

#pragma pack(pop)

}} // namespace pie::hac