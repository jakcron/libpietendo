	/**
	 * @file Ticket.h
	 * @brief Declaration of CTR ES Ticket Classes / Utilities
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/27
	 **/
#pragma once
#include <bitset>
#include <tc/types.h>
#include <tc/io/IStream.h>
#include <pietendo/ctr/es/Signature.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/InvalidOperationException.h>

namespace pie { namespace ctr { namespace es {

struct Ticket
{
public:
	Ticket() :
		signature(),
		ticket_id(0),
		device_id(0),
		title_id(0),
		ticket_version(0),
		license_type(0),
		key_id(0),
		ec_account_id(0),
		launch_count(0),
		enabled_content()
	{
		memset(calculated_hash.data(), 0, calculated_hash.size());
		memset(title_key.data(), 0, title_key.size());
	}

public:
	// these fields are only used in deserialisation
	pie::ctr::es::Signature signature;
	std::array<byte_t, 32> calculated_hash;

	// these fields are used in both deserialisation & serialisation
	std::array<byte_t, 16> title_key;
	uint64_t ticket_id;
	uint32_t device_id;
	uint64_t title_id;
	uint16_t ticket_version;
	byte_t license_type;
	byte_t key_id;
	// reserved region data
	uint32_t ec_account_id;
	// lp record
	uint32_t launch_count; // 0 = unlimited, x = limited to x launches
	std::bitset<0x10000> enabled_content;
};

class TicketDeserialiser : public Ticket
{
public:
	// tik stream
	TicketDeserialiser(const std::shared_ptr<tc::io::IStream>& tik_stream);
private:
	std::string mModuleLabel;
};

/*
class TicketSerialiser : public tc::io::IStream
{
public:
	// tmd Ticket, issuer, RsaKey
	TicketSerialiser();
private:
	std::string mModuleLabel;
}
*/

}}} // namespace pie::ctr::es