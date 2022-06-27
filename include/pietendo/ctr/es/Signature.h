	/**
	 * @file Signature.h
	 * @brief Declaration of CTR ES Signature Classes / Utilities
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/27
	 **/
#pragma once
#include <bitset>
#include <tc/types.h>
#include <tc/io/IStream.h>
#include <tc/crypto/RsaKey.h>
#include <pietendo/es/sign.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/InvalidOperationException.h>

namespace pie { namespace ctr { namespace es {

size_t getSignatureSizeFromSigType(pie::es::ESSigType sig_type);
size_t getSignatureIssuerOffset(pie::es::ESSigType sig_type);

struct Signature
{
public:
	Signature() :
		sig_type(),
		sig(),
		issuer()
	{}
public:
	pie::es::ESSigType sig_type;
	tc::ByteData sig;
	std::string issuer;
};

class SignatureDeserialiser : public Signature
{
public:
	// input stream
	SignatureDeserialiser(const std::shared_ptr<tc::io::IStream>& stream);
private:
	std::string mModuleLabel;
};

/*
class SignatureSerialiser : public tc::io::IStream
{
public:
	SignatureSerialiser();
private:
	std::string mModuleLabel;
}
*/

}}} // namespace pie::ctr::es