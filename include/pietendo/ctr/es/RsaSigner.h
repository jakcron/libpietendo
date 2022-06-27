	/**
	 * @file RsaSigner.h
	 * @brief Declaration of pie::ctr::es::RsaSigner
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/27
	 **/
#pragma once
#include <bitset>
#include <tc/types.h>
#include <tc/crypto/RsaKey.h>
#include <pietendo/ctr/es/ISigner.h>

#include <tc/InvalidOperationException.h>
#include <tc/ArgumentOutOfRangeException.h>

namespace pie { namespace ctr { namespace es {

class RsaSigner : public pie::ctr::es::ISigner
{
public:
	RsaSigner(pie::es::ESSigType sig_type, const std::string& issuer, const tc::crypto::RsaKey& rsa_key);
	
	const std::string& getIssuer();
	
	pie::es::ESSigType getSigType();
	
	bool signHash(const byte_t* hash, byte_t* signature);
	
	bool verifyHash(const byte_t* hash, const byte_t* signature);
private:
	pie::es::ESSigType mSigType;
	std::string mIssuer;
	tc::crypto::RsaKey mRsaKey;
};

}}} // namespace pie::ctr::es