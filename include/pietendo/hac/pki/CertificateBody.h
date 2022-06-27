#pragma once
#include <tc.h>
#include <nn/pki/cert.h>

namespace nn
{
namespace pki
{
	class CertificateBody
	{
	public:
		CertificateBody();
		CertificateBody(const CertificateBody& other);

		void operator=(const CertificateBody& other);
		bool operator==(const CertificateBody& other) const;
		bool operator!=(const CertificateBody& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* src, size_t size);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		const std::string& getIssuer() const;
		void setIssuer(const std::string& issuer);

		pki::cert::PublicKeyType getPublicKeyType() const;
		void setPublicKeyType(cert::PublicKeyType type);

		const std::string& getSubject() const;
		void setSubject(const std::string& subject);

		uint32_t getCertId() const;
		void setCertId(uint32_t id);

		const tc::crypto::RsaKey& getRsa4096PublicKey() const;
		void setRsa4096PublicKey(const tc::crypto::RsaKey& key);

		const tc::crypto::RsaKey& getRsa2048PublicKey() const;
		void setRsa2048PublicKey(const tc::crypto::RsaKey& key);

		const nn::pki::sEcdsa233PublicKey& getEcdsa240PublicKey() const;
		void setEcdsa240PublicKey(const nn::pki::sEcdsa233PublicKey& key);
		
	private:
		const std::string kModuleName = "CERTIFICATE_BODY";

		// raw binary
		tc::ByteData mRawBinary;

		// variables
		std::string mIssuer;
		std::string mSubject;
		uint32_t mCertId;
		cert::PublicKeyType mPublicKeyType;

		tc::crypto::RsaKey mRsa4096PublicKey;
		tc::crypto::RsaKey mRsa2048PublicKey;
		nn::pki::sEcdsa233PublicKey mEcdsa240PublicKey;
	};
}
}