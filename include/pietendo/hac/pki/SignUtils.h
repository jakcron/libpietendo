	/**
	 * @file SignUtils.h
	 * @brief Declaration of PKI Signature utilities
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/pki/sign.h>

namespace pie { namespace hac { namespace pki {

namespace sign
{
	pie::hac::pki::sign::SignatureAlgo getSignatureAlgo(pki::sign::SignatureId sign_id);
	pie::hac::pki::sign::HashAlgo getHashAlgo(pki::sign::SignatureId sign_id);
}
	
}}} // namespace pie::hac::pki