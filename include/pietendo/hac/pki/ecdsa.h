	/**
	 * @file ecdsa.h
	 * @brief Declaration of PKI ECDSA structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/types.h>

namespace pie { namespace hac { namespace pki {

namespace ecdsa
{
	static const size_t kEcdsa233IntSize = 0x1E;

	using sEcdsa233Int = std::array<byte_t, kEcdsa233IntSize>;
}

struct sEcdsa233Point
{
	ecdsa::sEcdsa233Int r,s;
};

using sEcdsa233PrivateKey = ecdsa::sEcdsa233Int;

using sEcdsa233PublicKey = sEcdsa233Point;

using sEcdsa233Signature = sEcdsa233Point;

}}} // namespace pie::hac::pki