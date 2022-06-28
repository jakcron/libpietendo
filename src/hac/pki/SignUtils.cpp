#include <pietendo/hac/pki/SignUtils.h>

pie::hac::pki::sign::SignatureAlgo pie::hac::pki::sign::getSignatureAlgo(pie::hac::pki::sign::SignatureId sign_id)
{
	SignatureAlgo sign_algo = SIGN_ALGO_RSA4096;

	switch (sign_id)
	{
	case (pie::hac::pki::sign::SIGN_ID_RSA4096_SHA1):
	case (pie::hac::pki::sign::SIGN_ID_RSA4096_SHA256):
		sign_algo = SIGN_ALGO_RSA4096;
		break;
	case (pie::hac::pki::sign::SIGN_ID_RSA2048_SHA1):
	case (pie::hac::pki::sign::SIGN_ID_RSA2048_SHA256):
		sign_algo = SIGN_ALGO_RSA2048;
		break;
	case (pie::hac::pki::sign::SIGN_ID_ECDSA240_SHA1):
	case (pie::hac::pki::sign::SIGN_ID_ECDSA240_SHA256):
		sign_algo = SIGN_ALGO_ECDSA240;
		break;
	};

	return sign_algo;
}

pie::hac::pki::sign::HashAlgo pie::hac::pki::sign::getHashAlgo(pie::hac::pki::sign::SignatureId sign_id)
{
	HashAlgo hash_algo = HASH_ALGO_SHA1;

	switch (sign_id)
	{
	case (pie::hac::pki::sign::SIGN_ID_RSA4096_SHA1):
	case (pie::hac::pki::sign::SIGN_ID_RSA2048_SHA1):
	case (pie::hac::pki::sign::SIGN_ID_ECDSA240_SHA1):
		hash_algo = HASH_ALGO_SHA1;
		break;
	case (pie::hac::pki::sign::SIGN_ID_RSA4096_SHA256):
	case (pie::hac::pki::sign::SIGN_ID_RSA2048_SHA256):
	case (pie::hac::pki::sign::SIGN_ID_ECDSA240_SHA256):
		hash_algo = HASH_ALGO_SHA256;
		break;
	};

	return hash_algo;
}