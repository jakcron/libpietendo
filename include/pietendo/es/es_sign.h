	/**
	 * @file es_sign.h
	 * @brief Declaration of structures and enums related to ES Signature
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/07/04
	 **/
#pragma once
#include <pietendo/es/types.h>

namespace pie { namespace es {
	/**
     @enum ESSigType
     @brief ES Signature type definition
     */
enum class ESSigType : uint32_t
{
    RSA4096_SHA1 = 0x00010000, /** RSA 4096 bit signature */
    RSA2048_SHA1 = 0x00010001, /** RSA 2048 bit signature */
    ECC_SHA1 = 0x00010002, /** ECC 233 bit signature */
    RSA4096_SHA256 = 0x00010003, /** RSA 4096 bit sig using SHA-256 */
    RSA2048_SHA256 = 0x00010004, /** RSA 2048 bit sig using SHA-256 (note that Switch Ticket has this word swapped) */
    ECC_SHA256 = 0x00010005, /** ECC sig 233 bits using SHA-256 */
    HMAC_SHA1 = 0x00010006, /** HMAC-SHA1 160 bit signature */
};

static const size_t ES_ISSUER_SIZE = 64;

	/**
	 * @typedef ESIssuer
	 * @brief The signature issuer ASCII encoded certificate hierarchy. Padded with nulls.
	 * @details
	 * 
	 * Examples: 
	 * * __Root__ (issued by __Root__)
	 * * __Root-CAxxxxxxxx__ (issued by Certifcate Authority server __xxxxxxxx__)
	 * * __Root-CAxxxxxxxx-XSxxxxxxxx__ (issued by Ticket/Transaction server __xxxxxxxx__)
	 * * __Root-CAxxxxxxxx-CPxxxxxxxx__ (issued by Content Publishing server __xxxxxxxx__)
	 * * __Root-CAxxxxxxxx-MSxxxxxxxx__ (issued by Manufacturing server __xxxxxxxx__)
	 * * __Root-CAxxxxxxxx-MSxxxxxxxx-YYxxxxxxxx__ (issued by Device with of type __YY__ and serial number __xxxxxxxx__)
	 * 
	 * __xxxxxxxx__ represents the server/device serial number encoded in hex. (e.g. __XS0000000f__ is ticket server 15).
	 */
using ESIssuer = tc::bn::string<ES_ISSUER_SIZE>;  

template <size_t _size>
using ESSigPad = tc::bn::pad<_size>; 

/* pack to 4 byte boundaries */
#pragma pack(push,4)

struct ESSigRsa2048
{
	tc::bn::be32<ESSigType>    sigType; /** Big-endian encoded @see pie::es::ESSigType */
	Rsa2048Sig     sig;
	ESSigPad<60>   pad;
	ESIssuer       issuer;
};
static_assert(sizeof(ESSigRsa2048) == 384, "ESSigRsa2048 size");

struct ESSigRsa4096
{
	tc::bn::be32<ESSigType>    sigType;
	Rsa4096Sig    sig;
	ESSigPad<60>  pad;
	ESIssuer      issuer;
};
static_assert(sizeof(ESSigRsa4096) == 640, "ESSigRsa4096 size");

struct ESSigEcc233
{
	tc::bn::be32<ESSigType>    sigType;
	Ecc233Sig     sig;
	ESSigPad<64>  pad;
	ESIssuer      issuer;
};
static_assert(sizeof(ESSigEcc233) == 192, "ESSigEcc233 size");

#pragma pack(pop)

}} // namespace pie::es