#include <nn/hac/AesKeygen.h>

void nn::hac::AesKeygen::generateKey(byte_t* dst, const byte_t* src, const byte_t* src_key)
{
	tc::crypto::DecryptAes128Ecb(dst, src, sizeof(detail::aes128_key_t), src_key, sizeof(detail::aes128_key_t));
}

void nn::hac::AesKeygen::generateKey(byte_t* dst, const byte_t* src1, const byte_t* src2, const byte_t* src1_key)
{
	detail::aes128_key_t src2_key;
	generateKey(src2_key.data(), src1, src1_key);
	generateKey(dst, src2, src2_key.data());
}
void nn::hac::AesKeygen::generateKey(byte_t* dst, const byte_t* src1, const byte_t* src2, const byte_t* src3, const byte_t* src1_key)
{
	detail::aes128_key_t src3_key;
	generateKey(src3_key.data(), src1, src2, src1_key);
	generateKey(dst, src3, src3_key.data());
}

byte_t nn::hac::AesKeygen::getMasterKeyRevisionFromKeyGeneration(byte_t key_generation)
{
	return key_generation == 0 ? 0 : key_generation-1;
}