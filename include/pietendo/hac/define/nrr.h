	/**
	 * @file nrr.h
	 * @brief Declaration of NRR0 structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace nrr
{
	static const uint32_t kNrrStructMagic = tc::bn::make_struct_magic_uint32("NRR0");

	enum class NrrKind : byte_t
	{
		User = 0,
		JitPlugin = 1
	};
}

#pragma pack(push,1)

struct sNrrCertificate
{
	tc::bn::le64<uint64_t> application_id_mask;
	tc::bn::le64<uint64_t> application_id_pattern;
	std::array<byte_t, 0x10> reserved_00;
	detail::rsa2048_block_t nrr_body_modulus;
	detail::rsa2048_signature_t nrr_cert_signature;
};
static_assert(sizeof(sNrrCertificate) == 0x220, "sNrrCertificate size.");

struct sNrrHeader
{
	tc::bn::le32<uint32_t> st_magic;
	byte_t certificate_key_generation;
	std::array<byte_t, 0xB> reserved_0;
	sNrrCertificate certificate;
	detail::rsa2048_signature_t nrr_body_signature;
};
static_assert(sizeof(sNrrHeader) == 0x330, "sNrrHeader size.");

struct sNrrBodyHeader
{
	tc::bn::le64<uint64_t> application_id;
	tc::bn::le32<uint32_t> size;
	byte_t nrr_kind;
	std::array<byte_t, 0x3> reserved_0;
	tc::bn::le32<uint32_t> hash_offset;
	tc::bn::le32<uint32_t> hash_count;
	std::array<byte_t, 0x8> reserved_1;
};
static_assert(sizeof(sNrrBodyHeader) == 0x20, "sNrrBodyHeader size.");

#pragma pack(pop)

}} // namespace pie::hac