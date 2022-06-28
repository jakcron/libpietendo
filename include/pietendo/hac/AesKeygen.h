	/**
	 * @file AesKeygen.h
	 * @brief Declaration of pie::hac::AesKeygen
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {
	
class AesKeygen
{
public:

	// 1 stage key generation dst = src_key.decrypt(src)
	static void generateKey(byte_t* dst, const byte_t* src, const byte_t* src_key);
	// 2 stage key generation dst = (src1_key.decrypt(src1)).decrypt(src2)
	static void generateKey(byte_t* dst, const byte_t* src1, const byte_t* src2, const byte_t* src1_key);
	// 3 stage key generation dst = ((src1_key.decrypt(src1)).decrypt(src2)).decrypt(src3)
	static void generateKey(byte_t* dst, const byte_t* src1, const byte_t* src2, const byte_t* src3, const byte_t* src1_key);

	static byte_t getMasterKeyRevisionFromKeyGeneration(byte_t key_generation);
};

}} // namespace pie::hac