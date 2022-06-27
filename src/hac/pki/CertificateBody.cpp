#include <nn/pki/CertificateBody.h>

nn::pki::CertificateBody::CertificateBody()
{
	clear();
}

nn::pki::CertificateBody::CertificateBody(const CertificateBody& other)
{
	*this = other;
}

void nn::pki::CertificateBody::operator=(const CertificateBody& other)
{
	mRawBinary = other.mRawBinary;
	mIssuer = other.mIssuer;
	mSubject = other.mSubject;
	mCertId = other.mCertId;
	mPublicKeyType = other.mPublicKeyType;
	mRsa4096PublicKey = other.mRsa4096PublicKey;
	mRsa2048PublicKey = other.mRsa2048PublicKey;
	mEcdsa240PublicKey = other.mEcdsa240PublicKey;
}

bool nn::pki::CertificateBody::operator==(const CertificateBody& other) const
{
	return (mIssuer == other.mIssuer) \
		&& (mSubject == other.mSubject) \
		&& (mCertId == other.mCertId) \
		&& (mPublicKeyType == other.mPublicKeyType) \
		&& (mRsa4096PublicKey.n == other.mRsa4096PublicKey.n) \
		&& (mRsa4096PublicKey.e == other.mRsa4096PublicKey.e) \
		&& (mRsa2048PublicKey.n == other.mRsa2048PublicKey.n) \
		&& (mRsa2048PublicKey.e == other.mRsa2048PublicKey.e) \
		&& (mEcdsa240PublicKey.r == other.mEcdsa240PublicKey.r) \
		&& (mEcdsa240PublicKey.s == other.mEcdsa240PublicKey.s);
}

bool nn::pki::CertificateBody::operator!=(const CertificateBody& other) const
{
	return !(*this == other);
}

void nn::pki::CertificateBody::toBytes()
{
	// get public key size
	size_t pubkeySize = 0;
	switch (mPublicKeyType)
	{
		case (cert::RSA4096):
			pubkeySize = sizeof(sRsa4096PublicKeyBlock);
			break;
		case (cert::RSA2048):
			pubkeySize = sizeof(sRsa2048PublicKeyBlock);
			break;
		case (cert::ECDSA240):
			pubkeySize = sizeof(sEcdsa240PublicKeyBlock);
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kModuleName, "Unknown public key type.");
	}

	mRawBinary = tc::ByteData(sizeof(sCertificateHeader) + pubkeySize);
	sCertificateHeader* hdr = (sCertificateHeader*)mRawBinary.data();

	// copy header vars
	hdr->issuer.encode(mIssuer);
	hdr->key_type.wrap(mPublicKeyType);
	hdr->subject.encode(mSubject);
	hdr->cert_id.wrap(mCertId);

	// copy public key
	if (mPublicKeyType == cert::RSA4096)
	{
		sRsa4096PublicKeyBlock* pubkey = (sRsa4096PublicKeyBlock*)(mRawBinary.data() + sizeof(sCertificateHeader));
		memcpy(pubkey->modulus.data(), mRsa4096PublicKey.n.data(), mRsa4096PublicKey.n.size());
		memcpy(pubkey->public_exponent.data(), mRsa4096PublicKey.e.data(), mRsa4096PublicKey.e.size());
	}
	else if (mPublicKeyType == cert::RSA2048)
	{
		sRsa2048PublicKeyBlock* pubkey = (sRsa2048PublicKeyBlock*)(mRawBinary.data() + sizeof(sCertificateHeader));
		memcpy(pubkey->modulus.data(), mRsa2048PublicKey.n.data(), mRsa2048PublicKey.n.size());
		memcpy(pubkey->public_exponent.data(), mRsa2048PublicKey.e.data(), mRsa2048PublicKey.e.size());
	}
	else if (mPublicKeyType == cert::ECDSA240)
	{
		sEcdsa240PublicKeyBlock* pubkey = (sEcdsa240PublicKeyBlock*)(mRawBinary.data() + sizeof(sCertificateHeader));
		pubkey->r = mEcdsa240PublicKey.r;
		pubkey->s = mEcdsa240PublicKey.s;
	}
}

void nn::pki::CertificateBody::fromBytes(const byte_t* src, size_t size)
{
	if (src == nullptr) { throw tc::ArgumentNullException(kModuleName, "src was null."); }
	if (size < sizeof(sCertificateHeader)) { tc::ArgumentOutOfRangeException(kModuleName, "src was too small."); }

	clear();

	const sCertificateHeader* hdr = (const sCertificateHeader*)src;

	// get public key size
	size_t pubkeySize = 0;
	switch (hdr->key_type.unwrap())
	{
		case (cert::RSA4096):
			pubkeySize = sizeof(sRsa4096PublicKeyBlock);
			break;
		case (cert::RSA2048):
			pubkeySize = sizeof(sRsa2048PublicKeyBlock);
			break;
		case (cert::ECDSA240):
			pubkeySize = sizeof(sEcdsa240PublicKeyBlock);
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kModuleName, "Unknown public key type.");
	}

	// check total size
	if (size < (sizeof(sCertificateHeader) + pubkeySize)) { throw tc::ArgumentOutOfRangeException(kModuleName, "src was too small."); }

	// save raw binary
	mRawBinary = tc::ByteData((sizeof(sCertificateHeader) + pubkeySize));
	memcpy(mRawBinary.data(), src, mRawBinary.size());

	// save hdr variables
	hdr = (const sCertificateHeader*)mRawBinary.data();

	mIssuer = hdr->issuer.decode();
	mPublicKeyType = (cert::PublicKeyType)hdr->key_type.unwrap();
	mSubject = hdr->subject.decode();
	mCertId = hdr->cert_id.unwrap();

	// save public key
	if (mPublicKeyType == cert::RSA4096)
	{
		const sRsa4096PublicKeyBlock* pubkey = (const sRsa4096PublicKeyBlock*)(mRawBinary.data() + sizeof(sCertificateHeader));
		mRsa4096PublicKey = tc::crypto::RsaPublicKey(pubkey->modulus.data(), pubkey->modulus.size());
	}
	else if (mPublicKeyType == cert::RSA2048)
	{
		const sRsa2048PublicKeyBlock* pubkey = (const sRsa2048PublicKeyBlock*)(mRawBinary.data() + sizeof(sCertificateHeader));
		mRsa2048PublicKey = tc::crypto::RsaPublicKey(pubkey->modulus.data(), pubkey->modulus.size());
	}
	else if (mPublicKeyType == cert::ECDSA240)
	{
		const sEcdsa240PublicKeyBlock* pubkey = (const sEcdsa240PublicKeyBlock*)(mRawBinary.data() + sizeof(sCertificateHeader));
		mEcdsa240PublicKey.r = pubkey->r;
		mEcdsa240PublicKey.s = pubkey->s;
	}
}

const tc::ByteData& nn::pki::CertificateBody::getBytes() const
{
	return mRawBinary;
}


void nn::pki::CertificateBody::clear()
{
	mIssuer.clear();
	mSubject.clear();
	mCertId = 0;
	mPublicKeyType = cert::RSA2048;

	mRsa4096PublicKey = tc::crypto::RsaKey();
	mRsa2048PublicKey = tc::crypto::RsaKey();
	memset(&mEcdsa240PublicKey, 0, sizeof(nn::pki::sEcdsa233PublicKey));
}

const std::string& nn::pki::CertificateBody::getIssuer() const
{
	return mIssuer;
}

void nn::pki::CertificateBody::setIssuer(const std::string& issuer)
{
	if (issuer.size() > cert::kIssuerSize)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Issuer name too long.");
	}

	mIssuer = issuer;
}

nn::pki::cert::PublicKeyType nn::pki::CertificateBody::getPublicKeyType() const
{
	return mPublicKeyType;
}

void nn::pki::CertificateBody::setPublicKeyType(cert::PublicKeyType type)
{
	mPublicKeyType = type;
}

const std::string& nn::pki::CertificateBody::getSubject() const
{
	return mSubject;
}

void nn::pki::CertificateBody::setSubject(const std::string& subject)
{
	if (subject.size() > cert::kSubjectSize)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Subject name too long.");
	}

	mSubject = subject;
}

uint32_t nn::pki::CertificateBody::getCertId() const
{
	return mCertId;
}

void nn::pki::CertificateBody::setCertId(uint32_t id)
{
	mCertId = id;
}

const tc::crypto::RsaKey& nn::pki::CertificateBody::getRsa4096PublicKey() const
{
	return mRsa4096PublicKey;
}

void nn::pki::CertificateBody::setRsa4096PublicKey(const tc::crypto::RsaKey& key)
{
	if (key.n.size() != cert::kRsa4096Size) { throw tc::ArgumentOutOfRangeException(kModuleName, "RSA4096 public key a bad modulus size"); }

	static const byte_t kPublicExponent[4] = { 0x00, 0x01, 0x00, 0x01 };

	mRsa4096PublicKey.n = key.n;
	mRsa4096PublicKey.e = tc::ByteData(kPublicExponent, sizeof(kPublicExponent));
}

const tc::crypto::RsaKey& nn::pki::CertificateBody::getRsa2048PublicKey() const
{
	return mRsa2048PublicKey;
}

void nn::pki::CertificateBody::setRsa2048PublicKey(const tc::crypto::RsaKey& key)
{
	if (key.n.size() != cert::kRsa2048Size) { throw tc::ArgumentOutOfRangeException(kModuleName, "RSA2048 public key a bad modulus size"); }

	static const byte_t kPublicExponent[4] = { 0x00, 0x01, 0x00, 0x01 };

	mRsa2048PublicKey.n = key.n;
	mRsa2048PublicKey.e = tc::ByteData(kPublicExponent, sizeof(kPublicExponent));
}

const nn::pki::sEcdsa233PublicKey& nn::pki::CertificateBody::getEcdsa240PublicKey() const
{
	return mEcdsa240PublicKey;
}

void nn::pki::CertificateBody::setEcdsa240PublicKey(const nn::pki::sEcdsa233PublicKey& key)
{
	mEcdsa240PublicKey = key;
}