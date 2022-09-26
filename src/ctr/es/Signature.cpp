#include <pietendo/ctr/es/Signature.h>
#include <fmt/core.h>

#include <pietendo/es/cert.h>
#include <tc/ByteData.h>
#include <tc/crypto/Sha256Generator.h>

#include <tc/cli.h>

size_t pie::ctr::es::getSignatureSizeFromSigType(pie::es::ESSigType sig_type)
{
	size_t signature_size = 0;
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
			signature_size = 0;
	}

	return signature_size;
}

size_t pie::ctr::es::getSignatureIssuerOffset(pie::es::ESSigType sig_type)
{
	size_t issuer_offset = 0;
	switch (sig_type)
	{
		case pie::es::ESSigType_RSA4096_SHA1:
		case pie::es::ESSigType_RSA4096_SHA2256:
			issuer_offset = sizeof(pie::es::ESSigRsa4096) - sizeof(pie::es::ESIssuer);
			break;
		case pie::es::ESSigType_RSA2048_SHA1:
		case pie::es::ESSigType_RSA2048_SHA2256:
			issuer_offset = sizeof(pie::es::ESSigRsa2048) - sizeof(pie::es::ESIssuer);
			break;
		case pie::es::ESSigType_ECCB233_SHA1:
		case pie::es::ESSigType_ECCB233_SHA2256:
			issuer_offset = sizeof(pie::es::ESSigEccB233) - sizeof(pie::es::ESIssuer);
			break;
		default:
			issuer_offset = 0;
	}

	return issuer_offset;
}

pie::ctr::es::SignatureDeserialiser::SignatureDeserialiser(const std::shared_ptr<tc::io::IStream>& stream) :
	Signature(),
	mModuleLabel("pie::ctr::es::SignatureDeserialiser")
{
	if (stream == nullptr)
	{
		throw tc::ArgumentNullException(mModuleLabel, "Stream was null.");
	}

	// must have at least 4 bytes for signature magic code
	if (stream->length() < sizeof(uint32_t))
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "Stream was too small to import signature.");
	}

	// get signature
	enum class SignType {
		RSA4096,
		RSA2048,
		ECDSA233,
	};
	union SignatureSignature
	{
		tc::bn::be32<pie::es::ESSigType>    sigType;
		pie::es::ESSigRsa4096 rsa4096;
		pie::es::ESSigRsa2048 rsa2048;
		pie::es::ESSigEccB233 ecdsa233;
	} signature_data;
	size_t signature_size = 0;

	stream->seek(0, tc::io::SeekOrigin::Begin);
	if (stream->read((byte_t*)&signature_data, sizeof(uint32_t)) < sizeof(uint32_t))
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "Unexpected size after reading.");
	}
	switch (signature_data.sigType.unwrap())
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
			throw tc::ArgumentOutOfRangeException(mModuleLabel, "Unexpected signature type.");
	}
	stream->seek(0, tc::io::SeekOrigin::Begin);
	if (stream->read((byte_t*)&signature_data, signature_size) < signature_size)
	{
		throw tc::ArgumentOutOfRangeException(mModuleLabel, "Unexpected size after reading.");
	}

	// store properties
	this->sig_type = signature_data.sigType.unwrap();
	switch (signature_data.sigType.unwrap())
	{
		case pie::es::ESSigType_RSA4096_SHA1:
		case pie::es::ESSigType_RSA4096_SHA2256:
			this->sig = tc::ByteData(signature_data.rsa4096.sig.data(), signature_data.rsa4096.sig.size());
			this->issuer = signature_data.rsa4096.issuer.decode();
			break;
		case pie::es::ESSigType_RSA2048_SHA1:
		case pie::es::ESSigType_RSA2048_SHA2256:
			this->sig = tc::ByteData(signature_data.rsa2048.sig.data(), signature_data.rsa2048.sig.size());
			this->issuer = signature_data.rsa2048.issuer.decode();
			break;
		case pie::es::ESSigType_ECCB233_SHA1:
		case pie::es::ESSigType_ECCB233_SHA2256:
			this->sig = tc::ByteData((byte_t*)&signature_data.ecdsa233.sig, sizeof(pie::es::detail::EccB233Sig));
			this->issuer = signature_data.ecdsa233.issuer.decode();
			break;
		default:
			break;
	}
}