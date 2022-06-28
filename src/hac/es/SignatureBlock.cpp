#include <pietendo/hac/es/SignatureBlock.h>

pie::hac::es::SignatureBlock::SignatureBlock()
{
	clear();
}

pie::hac::es::SignatureBlock::SignatureBlock(const SignatureBlock& other)
{
	*this = other;
}

void pie::hac::es::SignatureBlock::operator=(const SignatureBlock& other)
{
	if (other.mRawBinary.data() != nullptr)
	{
		fromBytes(other.mRawBinary.data(), other.mRawBinary.size());
	}
	else
	{
		clear();
		mSignType = other.mSignType;
		mIsLittleEndian = other.mIsLittleEndian;
		mSignature = other.mSignature;
	}	
}

bool pie::hac::es::SignatureBlock::operator==(const SignatureBlock& other) const
{
	return (mSignType == other.mSignType) \
		&& (mIsLittleEndian == other.mIsLittleEndian) \
		&& (memcmp(mSignature.data(), other.mSignature.data(), mSignature.size()) == 0);
}

bool pie::hac::es::SignatureBlock::operator!=(const SignatureBlock& other) const
{
	return !(*this == other);
}

void pie::hac::es::SignatureBlock::toBytes()
{
	size_t totalSize = 0;
	size_t sigSize = 0;

	switch (mSignType)
	{
		case (sign::SIGN_ID_RSA4096_SHA1):
		case (sign::SIGN_ID_RSA4096_SHA256):
			totalSize = sizeof(sRsa4096SignBlock);
			sigSize = cert::kRsa4096Size;
			break;
		case (sign::SIGN_ID_RSA2048_SHA1):
		case (sign::SIGN_ID_RSA2048_SHA256):
			totalSize = sizeof(sRsa2048SignBlock);
			sigSize = cert::kRsa2048Size;
			break;
		case (sign::SIGN_ID_ECDSA240_SHA1):
		case (sign::SIGN_ID_ECDSA240_SHA256):
			totalSize = sizeof(sEcdsa240SignBlock);
			sigSize = sign::kEcdsaSigSize;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kModuleName, "Unknown signature type");
	}

	if (mSignature.size() != sigSize) { throw tc::ArgumentException(kModuleName, "Signature size is incorrect"); }

	// commit to binary
	mRawBinary = tc::ByteData(totalSize);
	if (mIsLittleEndian)
		((tc::bn::le32<uint32_t>*)mRawBinary.data())->wrap(mSignType);
	else
		((tc::bn::be32<uint32_t>*)mRawBinary.data())->wrap(mSignType);
	memcpy(mRawBinary.data() + 4, mSignature.data(), sigSize);
}

void pie::hac::es::SignatureBlock::fromBytes(const byte_t* src, size_t size)
{
	if (src == nullptr) { throw tc::ArgumentNullException(kModuleName, "src was null."); }
	if (size < sizeof(sEcdsa240SignBlock)) { throw tc::ArgumentOutOfRangeException(kModuleName, "src was too small."); }

	clear();

	size_t totalSize = 0;
	size_t sigSize = 0;
	uint32_t signType = 0;

	// try Big Endian sign type
	signType = ((tc::bn::be32<uint32_t>*)src)->unwrap();
	switch (signType)
	{
	case (sign::SIGN_ID_RSA4096_SHA1): 
	case (sign::SIGN_ID_RSA4096_SHA256):
		totalSize = sizeof(sRsa4096SignBlock);
		sigSize = cert::kRsa4096Size;
		break;
	case (sign::SIGN_ID_RSA2048_SHA1): 
	case (sign::SIGN_ID_RSA2048_SHA256):
		totalSize = sizeof(sRsa2048SignBlock);
		sigSize = cert::kRsa2048Size;
		break;
	case (sign::SIGN_ID_ECDSA240_SHA1): 
	case (sign::SIGN_ID_ECDSA240_SHA256):
		totalSize = sizeof(sEcdsa240SignBlock);
		sigSize = sign::kEcdsaSigSize;
		break;
	}

	// try Little Endian sign type
	if (totalSize == 0)
	{
		signType = ((tc::bn::le32<uint32_t>*)src)->unwrap();
		switch (signType)
		{
		case (sign::SIGN_ID_RSA4096_SHA1): 
		case (sign::SIGN_ID_RSA4096_SHA256):
			totalSize = sizeof(sRsa4096SignBlock);
			sigSize = cert::kRsa4096Size;
			break;
		case (sign::SIGN_ID_RSA2048_SHA1): 
		case (sign::SIGN_ID_RSA2048_SHA256):
			totalSize = sizeof(sRsa2048SignBlock);
			sigSize = cert::kRsa2048Size;
			break;
		case (sign::SIGN_ID_ECDSA240_SHA1): 
		case (sign::SIGN_ID_ECDSA240_SHA256):
			totalSize = sizeof(sEcdsa240SignBlock);
			sigSize = sign::kEcdsaSigSize;
			break;
		default:
			throw tc::ArgumentOutOfRangeException(kModuleName, "Unknown signature type");
		}

		mIsLittleEndian = true;
	}

	// check size again
	if (size < totalSize) { throw tc::ArgumentOutOfRangeException(kModuleName, "src was too small."); }

	mRawBinary  = tc::ByteData(totalSize);
	memcpy(mRawBinary.data(), src, mRawBinary.size());

	mSignType = (sign::SignatureId)signType;
	mSignature = tc::ByteData(sigSize);
	memcpy(mSignature.data(), mRawBinary.data() + 4, sigSize);
}

const tc::ByteData& pie::hac::es::SignatureBlock::getBytes() const
{
	return mRawBinary;
}

void pie::hac::es::SignatureBlock::clear()
{
	memset(mRawBinary.data(), 0, mRawBinary.size());
	mSignType = sign::SIGN_ID_RSA4096_SHA1;
	mIsLittleEndian = false;
	memset(mSignature.data(), 0, mSignature.size());
}

pie::hac::es::sign::SignatureId pie::hac::es::SignatureBlock::getSignType() const
{
	return mSignType;
}

void pie::hac::es::SignatureBlock::setSignType(pie::hac::es::sign::SignatureId type)
{
	mSignType = type;
}

bool pie::hac::es::SignatureBlock::isLittleEndian() const
{
	return mIsLittleEndian;
}

void pie::hac::es::SignatureBlock::setLittleEndian(bool isLE)
{
	mIsLittleEndian = isLE;
}

const tc::ByteData& pie::hac::es::SignatureBlock::getSignature() const
{
	return mSignature;
}

void pie::hac::es::SignatureBlock::setSignature(const tc::ByteData& signature)
{
	mSignature = signature;
}
