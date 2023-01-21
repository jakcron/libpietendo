#include <pietendo/ctr/es/RsaSigner.h>

#include <tc/crypto/RsaPkcs1Sha1Signer.h>
#include <tc/crypto/RsaPkcs1Sha2256Signer.h>

pie::ctr::es::RsaSigner::RsaSigner(pie::es::ESSigType sig_type, const std::string& issuer, const tc::crypto::RsaKey& rsa_key) :
	mSigType(sig_type),
	mIssuer(issuer),
	mRsaKey(rsa_key)
{
	switch (mSigType) {
		case pie::es::ESSigType_RSA4096_SHA1:
		case pie::es::ESSigType_RSA4096_SHA2256:
			if ((mRsaKey.n.size() << 3) != 4096) throw tc::ArgumentOutOfRangeException("pie::ctr::es::RsaSigner::RsaSigner()", "Key size inferred from SigType did not match actual key size.");
			break;
		case pie::es::ESSigType_RSA2048_SHA1:
		case pie::es::ESSigType_RSA2048_SHA2256:
			if ((mRsaKey.n.size() << 3) != 2048) throw tc::ArgumentOutOfRangeException("pie::ctr::es::RsaSigner::RsaSigner()", "Key size inferred from SigType did not match actual key size.");
			break;
		default:
			throw tc::ArgumentOutOfRangeException("pie::ctr::es::RsaSigner::RsaSigner()", "SigType not supported for RsaSigner.");
			break;
	}
}

const std::string& pie::ctr::es::RsaSigner::getIssuer()
{
	return mIssuer;
}

pie::es::ESSigType pie::ctr::es::RsaSigner::getSigType()
{
	return mSigType;
}

bool pie::ctr::es::RsaSigner::signHash(const byte_t* hash, byte_t* signature)
{
	bool signSucceed = false;

	switch (mSigType) {
		case pie::es::ESSigType_RSA4096_SHA1:
			signSucceed = tc::crypto::SignRsa4096Pkcs1Sha1(signature, hash, mRsaKey);
			break;
		case pie::es::ESSigType_RSA2048_SHA1:
			signSucceed = tc::crypto::SignRsa2048Pkcs1Sha1(signature, hash, mRsaKey);
			break;
		case pie::es::ESSigType_RSA4096_SHA2256:
			signSucceed = tc::crypto::SignRsa4096Pkcs1Sha2256(signature, hash, mRsaKey);
			break;
		case pie::es::ESSigType_RSA2048_SHA2256:
			signSucceed = tc::crypto::SignRsa2048Pkcs1Sha2256(signature, hash, mRsaKey);
			break;
		default:
			signSucceed = false;
			break;
	}

	return signSucceed;
}

bool pie::ctr::es::RsaSigner::verifyHash(const byte_t* hash, const byte_t* signature)
{
	bool verifySucceed = false;

	switch (mSigType) {
		case pie::es::ESSigType_RSA4096_SHA1:
			verifySucceed = tc::crypto::VerifyRsa4096Pkcs1Sha1(signature, hash, mRsaKey);
			break;
		case pie::es::ESSigType_RSA2048_SHA1:
			verifySucceed = tc::crypto::VerifyRsa2048Pkcs1Sha1(signature, hash, mRsaKey);
			break;
		case pie::es::ESSigType_RSA4096_SHA2256:
			verifySucceed = tc::crypto::VerifyRsa4096Pkcs1Sha2256(signature, hash, mRsaKey);
			break;
		case pie::es::ESSigType_RSA2048_SHA2256:
			verifySucceed = tc::crypto::VerifyRsa2048Pkcs1Sha2256(signature, hash, mRsaKey);
			break;
		default:
			verifySucceed = false;
			break;
	}

	return verifySucceed;
}