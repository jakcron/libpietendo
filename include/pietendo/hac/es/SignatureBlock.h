	/**
	 * @file SignatureBlock.h
	 * @brief Declaration of pie::hac::es::SignatureBlock
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/ByteData.h>
#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <pietendo/hac/es/sign.h>

namespace pie { namespace hac { namespace es {

class SignatureBlock
{
public:
	SignatureBlock();
	SignatureBlock(const SignatureBlock& other);

	void operator=(const SignatureBlock& other);
	bool operator==(const SignatureBlock& other) const;
	bool operator!=(const SignatureBlock& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* src, size_t size);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	es::sign::SignatureId getSignType() const;
	void setSignType(es::sign::SignatureId type);

	bool isLittleEndian() const;
	void setLittleEndian(bool isLE);

	const tc::ByteData& getSignature() const;
	void setSignature(const tc::ByteData& signature);

	
private:
	const std::string kModuleName = "SIGNATURE_BLOCK";

	// raw binary
	tc::ByteData mRawBinary;

	// variables
	es::sign::SignatureId mSignType;
	bool mIsLittleEndian;
	tc::ByteData mSignature;
};

}}} // namespace pie::hac::es