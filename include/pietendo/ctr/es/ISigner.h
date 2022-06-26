#pragma once
#include <bitset>
#include <tc/types.h>
#include <pietendo/es/sign.h>

namespace pie { namespace ctr { namespace es {

class ISigner
{
public:
	virtual ~ISigner() = default;
	virtual const std::string& getIssuer() = 0;
	virtual pie::es::ESSigType getSigType() = 0;
	virtual bool signHash(const byte_t* hash, byte_t* signature) = 0;
	virtual bool verifyHash(const byte_t* hash, const byte_t* signature) = 0;
};

}}} // namespace pie::ctr::es