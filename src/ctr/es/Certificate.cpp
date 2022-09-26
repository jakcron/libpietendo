#include <pietendo/ctr/es/Certificate.h>
#include <fmt/core.h>

#include <pietendo/es/cert.h>
#include <tc/ByteData.h>
#include <tc/crypto/Sha256Generator.h>

#include <tc/cli.h>

size_t pie::ctr::es::getCertificateSize(byte_t* data)
{
	size_t signature_size = 0;
	size_t public_key_size = 0;

	if (data == nullptr) { return 0; }

	signature_size = getCertificateSignatureSize(data);
	if (signature_size == 0) { return 0; }

	pie::es::ESCertHeader* header = (pie::es::ESCertHeader*)(data + signature_size);
	pie::es::ESCertPubKeyType public_key_type = header->pubKeyType.unwrap();
	switch (public_key_type)
	{
		case pie::es::ESCertPubKeyType_RSA4096:
			public_key_size = sizeof(pie::es::ESCertRsa4096PublicKey);
			break;
		case pie::es::ESCertPubKeyType_RSA2048:
			public_key_size = sizeof(pie::es::ESCertRsa2048PublicKey);
			break;
		case pie::es::ESCertPubKeyType_ECCB233:
			public_key_size = sizeof(pie::es::ESCertEccB233PublicKey);
			break;
		default:
			return 0;
	}

	return signature_size + sizeof(pie::es::ESCertHeader) + public_key_size;
}

size_t pie::ctr::es::getCertificateSignatureSize(byte_t* data)
{
	size_t signature_size = 0;

	if (data == nullptr) { return 0; }

	pie::es::ESSigType sig_type = ((tc::bn::be32<pie::es::ESSigType>*)data)->unwrap();
	switch (sig_type)
	{
		case pie::es::ESSigType_RSA4096_SHA1:
		case pie::es::ESSigType_RSA4096_SHA2256:
			signature_size = sizeof(pie::es::ESSigRsa4096);
			break;
		case pie::es::ESSigType_RSA2048_SHA1:
		case pie::es::ESSigType_RSA2048_SHA2256:
			signature_size = sizeof(pie::es::ESSigRsa2048);
			break;
		case pie::es::ESSigType_ECCB233_SHA1:
		case pie::es::ESSigType_ECCB233_SHA2256:
			signature_size = sizeof(pie::es::ESSigEccB233);
			break;
		default:
			return 0;
	}

	return signature_size;
}

size_t pie::ctr::es::getCertificateSignableOffset(byte_t* data)
{
	size_t signature_size = 0;

	if (data == nullptr) { return 0; }

	signature_size = getCertificateSignatureSize(data);
	if (signature_size == 0) { return 0; }

	return signature_size - sizeof(pie::es::ESIssuer);
}

size_t pie::ctr::es::getCertificateSignableSize(byte_t* data)
{
	return getCertificateSize(data) - getCertificateSignableOffset(data);
}

void* pie::ctr::es::getCertificateHeaderPtr(byte_t* data)
{
	size_t signature_size = 0;

	if (data == nullptr) { return nullptr; }

	signature_size = getCertificateSignatureSize(data);
	if (signature_size == 0) { return nullptr; }

	return (data + signature_size);
}

void* pie::ctr::es::getCertificatePublicKeyPtr(byte_t* data)
{
	size_t signature_size = 0;

	if (data == nullptr) { return nullptr; }

	signature_size = getCertificateSignatureSize(data);
	if (signature_size == 0) { return nullptr; }

	return (data + signature_size + sizeof(pie::es::ESCertHeader));
}

pie::ctr::es::CertificateDeserialiser::CertificateDeserialiser(const std::shared_ptr<tc::io::IStream>& cert_stream) :
	Certificate(),
	mModuleLabel("pie::ctr::es::CertificateDeserialiser")
{
	if (cert_stream == nullptr)
	{
		throw tc::ArgumentNullException(mModuleLabel, "Stream was null.");
	}

	// process signature
	this->signature = SignatureDeserialiser(cert_stream);
	switch (this->signature.sig_type)
	{
		case pie::es::ESSigType_RSA4096_SHA1:
		case pie::es::ESSigType_RSA4096_SHA2256:
		case pie::es::ESSigType_RSA2048_SHA1:
		case pie::es::ESSigType_RSA2048_SHA2256:
		case pie::es::ESSigType_ECCB233_SHA1:
		case pie::es::ESSigType_ECCB233_SHA2256:
			break;
		default:
			throw tc::ArgumentOutOfRangeException(mModuleLabel, "CERT had unexpected signature type.");
	}
	size_t signature_size = getSignatureSizeFromSigType(this->signature.sig_type);

	// get certificate header
	pie::es::ESCertHeader header;
	cert_stream->seek(signature_size, tc::io::SeekOrigin::Begin);
	if (cert_stream->read((byte_t*)&header, sizeof(pie::es::ESCertHeader)) < sizeof(pie::es::ESCertHeader))
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "CERT had unexpected size after reading.");
	}

	// get public key
	union CertificatePublicKey
	{
		pie::es::ESCertRsa4096PublicKey rsa4096;
		pie::es::ESCertRsa2048PublicKey rsa2048;
		pie::es::ESCertEccB233PublicKey ecc233;
	} public_key;
	size_t public_key_size;

	switch (header.pubKeyType.unwrap())
	{
		case pie::es::ESCertPubKeyType_RSA4096:
			public_key_size = sizeof(pie::es::ESCertRsa4096PublicKey);
			break;
		case pie::es::ESCertPubKeyType_RSA2048:
			public_key_size = sizeof(pie::es::ESCertRsa2048PublicKey);
			break;
		case pie::es::ESCertPubKeyType_ECCB233:
			public_key_size = sizeof(pie::es::ESCertEccB233PublicKey);
			break;
		default:
			throw tc::ArgumentOutOfRangeException(mModuleLabel, "CERT had unexpected public key type.");
	}

	cert_stream->seek(signature_size + sizeof(pie::es::ESCertHeader), tc::io::SeekOrigin::Begin);
	if (cert_stream->read((byte_t*)&public_key, public_key_size) < public_key_size)
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "CERT had unexpected size after reading.");
	}

	// calculate hash for optional signature validation later
	tc::ByteData total_cert_data = tc::ByteData(signature_size + sizeof(pie::es::ESCertHeader) + public_key_size);
	cert_stream->seek(0, tc::io::SeekOrigin::Begin);
	if (cert_stream->read(total_cert_data.data(), total_cert_data.size()) < total_cert_data.size())
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "CERT had unexpected size after reading.");
	}
	tc::crypto::GenerateSha256Hash(calculated_hash.data(), total_cert_data.data() + getCertificateSignableOffset(total_cert_data.data()), pie::ctr::es::getCertificateSignableSize(total_cert_data.data()));


	// store properties
	//this->signature = SignatureDeserialiser(cert_stream);
	this->subject = header.name.deviceId.decode();
	this->date = header.date.unwrap();
	this->public_key_type = header.pubKeyType.unwrap();
	switch (header.pubKeyType.unwrap())
	{
		case pie::es::ESCertPubKeyType_RSA4096:
			memcpy(&this->rsa4096_public_key, &public_key.rsa4096.pubKey, sizeof(pie::es::detail::Rsa4096PublicKey));
			break;
		case pie::es::ESCertPubKeyType_RSA2048:
			memcpy(&this->rsa2048_public_key, &public_key.rsa2048.pubKey, sizeof(pie::es::detail::Rsa2048PublicKey));
			break;
		case pie::es::ESCertPubKeyType_ECCB233:
			memcpy(&this->ecc233_public_key, &public_key.ecc233.pubKey, sizeof(pie::es::detail::EccB233PublicKey));
			break;
	}
	
}