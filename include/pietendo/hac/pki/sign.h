#pragma once
#include <nn/pki/cert.h>

namespace nn
{
namespace pki
{
	namespace sign
	{
		enum SignatureId
		{
			SIGN_ID_RSA4096_SHA1 = 0x10000,
			SIGN_ID_RSA2048_SHA1,
			SIGN_ID_ECDSA240_SHA1,
			SIGN_ID_RSA4096_SHA256,
			SIGN_ID_RSA2048_SHA256,
			SIGN_ID_ECDSA240_SHA256,
		};

		enum SignatureAlgo
		{
			SIGN_ALGO_RSA4096,
			SIGN_ALGO_RSA2048,
			SIGN_ALGO_ECDSA240
		};

		enum HashAlgo
		{
			HASH_ALGO_SHA1,
			HASH_ALGO_SHA256
		};

		static const size_t kEcdsaSigSize = 0x3C;

		static const std::string kRootIssuerStr = "Root";
		static const std::string kIdentDelimiter = "-";
	}
#pragma pack(push,1)
	struct sRsa4096SignBlock
	{
		tc::bn::be32<uint32_t> sign_type;
		std::array<byte_t, cert::kRsa4096Size> signature;
		std::array<byte_t, 0x3C> padding;
	};

	struct sRsa2048SignBlock
	{
		tc::bn::be32<uint32_t> sign_type;
		std::array<byte_t, cert::kRsa2048Size> signature;
		std::array<byte_t, 0x3C> padding;
	};

	struct sEcdsa240SignBlock
	{
		tc::bn::be32<uint32_t> sign_type;
		std::array<byte_t, sign::kEcdsaSigSize> signature;
		std::array<byte_t, 0x40> padding;
	};
#pragma pack(pop)
}
}