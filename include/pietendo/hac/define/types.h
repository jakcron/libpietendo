#pragma once
#include <tc/types.h>
#include <tc/crypto.h>
#include <cstdint>
#include <cstring>
#include <array>

namespace nn { namespace hac { namespace detail {
#pragma pack(push,1)
	using sha256_hash_t = std::array<byte_t, tc::crypto::Sha256Generator::kHashSize>;

	using aes128_key_t = std::array<byte_t, tc::crypto::Aes128CbcEncryptor::kKeySize>;
	using aes128_xtskey_t = std::array<aes128_key_t, 2>;
	using aes_iv_t = std::array<byte_t, tc::crypto::Aes128CbcEncryptor::kBlockSize>;

	using rsa2048_signature_t = std::array<byte_t, tc::crypto::Rsa2048Pkcs1Sha256Signer::kSignatureSize>;
	using rsa2048_block_t = std::array<byte_t, tc::crypto::Rsa2048OaepSha256Encryptor::kBlockSize>;

	using rsa4096_signature_t = std::array<byte_t, tc::crypto::Rsa4096Pkcs1Sha256Signer::kSignatureSize>;
	using rsa4096_block_t = std::array<byte_t, tc::crypto::Rsa4096OaepSha256Encryptor::kBlockSize>;

	using rights_id_t = std::array<byte_t, 16>;

	using module_id_t = std::array<byte_t, 32>;
#pragma pack(pop)
}}} // end namespace nn::hac::detail