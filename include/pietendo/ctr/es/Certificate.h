	/**
	 * @file Certificate.h
	 * @brief Declaration of CTR ES Certificate Classes / Utilities
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/27
	 **/
#pragma once
#include <bitset>
#include <tc/types.h>
#include <tc/io/IStream.h>
#include <tc/crypto/RsaKey.h>
#include <pietendo/es/cert.h>
#include <pietendo/ctr/es/Signature.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/InvalidOperationException.h>

namespace pie { namespace ctr { namespace es {

	/**
	 * @brief Get total size of certificate, from raw certificate blob.
	 * 
	 * @param[in] data Raw certificate data.
	 * 
	 * @return Size in bytes of certificate data, 0 if invalid data.
	 */
size_t getCertificateSize(byte_t* data);

	/**
	 * @brief Get total size of certificate signature structure, from raw certificate blob.
	 * 
	 * @param[in] data Raw certificate data.
	 * 
	 * @return Size in bytes of certificate signature structure, 0 if invalid data.
	 */
size_t getCertificateSignatureSize(byte_t* data);

	/**
	 * @brief Get offset of certificate signed data, from raw certificate blob.
	 * 
	 * @param[in] data Raw certificate data.
	 * 
	 * @return Offset in bytes of signed certificate data, 0 if invalid data.
	 */
size_t getCertificateSignableOffset(byte_t* data);

	/**
	 * @brief Get size of certificate signed data, from raw certificate blob.
	 * 
	 * @param[in] data Raw certificate data.
	 * 
	 * @return Size in bytes of signed certificate data, 0 if invalid data.
	 */
size_t getCertificateSignableSize(byte_t* data);

	/**
	 * @brief Get pointer to certificate header, from raw certificate blob.
	 * 
	 * @param[in] data Raw certificate data.
	 * 
	 * @return Void pointer to certificate header. See @ref pie::es::ESCertHeader.
	 */
void* getCertificateHeaderPtr(byte_t* data);

	/**
	 * @brief Get pointer to certificate public key, from raw certificate blob.
	 * 
	 * @param[in] data Raw certificate data.
	 * 
	 * @return Void pointer to certificate public. See @ref pie::es::ESCertRsa4096PublicKey @ref pie::es::ESCertRsa2048PublicKey @ref pie::es::ESCertEcc233PublicKey.
	 */
void* getCertificatePublicKeyPtr(byte_t* data);

struct Certificate
{
public:
	Certificate() :
		signature(),
		subject(),
		date(),
		public_key_type(),
		rsa4096_public_key(),
		rsa2048_public_key(),
		ecc233_public_key()
	{
		memset(calculated_hash.data(), 0, calculated_hash.size());
	}
public:
	// these fields are only used when deserialised
	pie::ctr::es::Signature signature; // This includes the signature type, signature data, and issuer
	std::array<byte_t, 32> calculated_hash; // This hash is calculated when deserialised so that signature validation can be performed.

	// these fields are used in both deserialisation & serialisation
	std::string subject;
	uint32_t date; // 32bit unix timestamp, not always set
	// public key
	pie::es::ESCertPubKeyType public_key_type;
	pie::es::detail::Rsa4096PublicKey rsa4096_public_key;
	pie::es::detail::Rsa2048PublicKey rsa2048_public_key;
	pie::es::detail::Ecc233PublicKey ecc233_public_key;
};

class CertificateDeserialiser : public Certificate
{
public:
	// cert stream
	CertificateDeserialiser(const std::shared_ptr<tc::io::IStream>& cert_stream);
private:
	std::string mModuleLabel;
};

/*
class CertificateSerialiser : public tc::io::IStream
{
public:
	CertificateSerialiser();
private:
	std::string mModuleLabel;
}
*/

}}} // namespace pie::ctr::es