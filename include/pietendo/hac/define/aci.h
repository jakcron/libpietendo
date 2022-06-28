	/**
	 * @file aci.h
	 * @brief Declaration of ACI structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace aci
{
	static const uint32_t kAciStructMagic = tc::bn::make_struct_magic_uint32("ACI0");
	static const uint32_t kAciDescStructMagic = tc::bn::make_struct_magic_uint32("ACID");
	static const size_t kSectionAlignSize = 0x10;

	enum class MemoryRegion : byte_t
	{
		Application,
		Applet,
		SecureSystem,
		NonSecureSystem
	};
}

#pragma pack(push,1)

struct sAciSection
{
	tc::bn::le32<uint32_t> offset;
	tc::bn::le32<uint32_t> size;
};
static_assert(sizeof(sAciSection) == 0x8, "sAciSection size"); 

struct sAciHeader
{
	tc::bn::le32<uint32_t> st_magic;
	std::array<byte_t, 0xC> reserved_00;
	tc::bn::le64<uint64_t> program_id;
	std::array<byte_t, 0x8> reserved_01;
	sAciSection fac;
	sAciSection sac;
	sAciSection kc;
};
static_assert(sizeof(sAciHeader) == 0x38, "sAciHeader size"); 

union sAciDescHeaderFlag
{
	struct 
	{
		uint32_t production : 1;
		uint32_t unqualified_approval : 1;
		uint32_t memory_region : 2; // added in FW 5.0.0 / kernel version 9.1.0??
		uint32_t :0; 
	};
	uint32_t raw;
};
static_assert(sizeof(sAciDescHeaderFlag) == 0x4, "sAciDescHeaderFlag size"); 

struct sAciDescHeader
{
	detail::rsa2048_signature_t signature;
	detail::rsa2048_signature_t nca_rsa_signature2_modulus;
	tc::bn::le32<uint32_t> st_magic;
	tc::bn::le32<uint32_t> signed_size;
	std::array<byte_t, 0x4> reserved_00;
	tc::bn::le32<uint32_t> flags;
	tc::bn::le64<uint64_t> program_id_min;
	tc::bn::le64<uint64_t> program_id_max;
	sAciSection fac;
	sAciSection sac;
	sAciSection kc;
};
static_assert(sizeof(sAciDescHeader) == 0x238, "sAciDescHeader size"); 

#pragma pack(pop)

}} // namespace pie::hac