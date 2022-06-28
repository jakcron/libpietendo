	/**
	 * @file cert.h
	 * @brief Declaration of ES Certificate structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/types.h>
#include <pietendo/hac/es/ecdsa.h>

namespace pie { namespace hac { namespace es {

namespace cert
{
	enum PublicKeyType
	{
		RSA4096,
		RSA2048,
		ECDSA240
	};

	static const size_t kIssuerSize = 0x40;
	static const size_t kSubjectSize = 0x40;
	static const size_t kRsa2048Size = 0x100;
	static const size_t kRsa4096Size = 0x200;
	static const size_t kRsaPublicExponentSize = 4;
}

#pragma pack(push,1)
struct sCertificateHeader
{
	tc::bn::string<cert::kIssuerSize> issuer;
	tc::bn::be32<uint32_t> key_type;
	tc::bn::string<cert::kSubjectSize> subject;
	tc::bn::be32<uint32_t> cert_id;
};

struct sRsa4096PublicKeyBlock
{
	std::array<byte_t, cert::kRsa4096Size> modulus;
	std::array<byte_t, cert::kRsaPublicExponentSize> public_exponent;
	std::array<byte_t, 0x34> padding;
};

struct sRsa2048PublicKeyBlock
{
	std::array<byte_t, cert::kRsa2048Size> modulus;
	std::array<byte_t, cert::kRsaPublicExponentSize> public_exponent;
	std::array<byte_t, 0x34> padding;
};

struct sEcdsa240PublicKeyBlock
{
	ecdsa::sEcdsa233Int r;
	ecdsa::sEcdsa233Int s;
	std::array<byte_t, 0x3C> padding;
};
#pragma pack(pop)

}}} // namespace pie::hac::es