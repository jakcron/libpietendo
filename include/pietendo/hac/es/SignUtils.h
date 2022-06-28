	/**
	 * @file SignUtils.h
	 * @brief Declaration of ES Signature utilities
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/es/sign.h>

namespace pie { namespace hac { namespace es {

namespace sign
{
	pie::hac::es::sign::SignatureAlgo getSignatureAlgo(es::sign::SignatureId sign_id);
	pie::hac::es::sign::HashAlgo getHashAlgo(es::sign::SignatureId sign_id);
}
	
}}} // namespace pie::hac::es