	/**
	 * @file sign.h
	 * @brief Declaration of ES Signature structs and data types for the ES library
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/25
	 **/
#pragma once
#include <pietendo/es/types.h>

namespace pie { namespace es {
	/**
     * @enum ESSigType
     * @brief ES Signature type definition
     */
enum ESSigType : uint32_t
{
    ES_SIGTYPE_RSA4096_SHA1   = 0x00010000, /**< __RSA4096-PKCS1-SHA1__ signature */
    ES_SIGTYPE_RSA2048_SHA1   = 0x00010001, /**< __RSA2048-PKCS1-SHA1__ signature */
    ES_SIGTYPE_ECC_SHA1       = 0x00010002, /**< __ECDSA233-SHA1__ signature */
    ES_SIGTYPE_RSA4096_SHA256 = 0x00010003, /**< __RSA4096-PKCS1-SHA2-256__ signature */
    ES_SIGTYPE_RSA2048_SHA256 = 0x00010004, /**< __RSA2048-PKCS1-SHA2-256__ signature (note that Switch Ticket has this word swapped) */
    ES_SIGTYPE_ECC_SHA256     = 0x00010005, /**< __ECDSA233-SHA256__ signature */
    ES_SIGTYPE_HMAC_SHA1      = 0x00010006, /**< __HMAC-SHA1__ signature */
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

	/**
	 * @typedef ESSigPad
	 * @brief Template for defining padding in ES structures.
	 * 
	 * @tparam _size Padding size in bytes.
	 */
template <size_t _size>
using ESSigPad = tc::bn::pad<_size>; 

/* pack to 4 byte boundaries */
#pragma pack(push,4)

struct ESSigRsa2048
{
	tc::bn::be32<ESSigType>    sigType; /**< Big-endian encoded pie::es::ESSigType */
	Rsa2048Sig                 sig;
	ESSigPad<60>               pad;
	ESIssuer                   issuer;
};
static_assert(sizeof(ESSigRsa2048) == 384, "ESSigRsa2048 size");

struct ESSigRsa4096
{
	tc::bn::be32<ESSigType>    sigType; /**< Big-endian encoded pie::es::ESSigType */
	Rsa4096Sig                 sig;
	ESSigPad<60>               pad;
	ESIssuer                   issuer;
};
static_assert(sizeof(ESSigRsa4096) == 640, "ESSigRsa4096 size");

struct ESSigEcc233
{
	tc::bn::be32<ESSigType>    sigType; /**< Big-endian encoded pie::es::ESSigType */
	Ecc233Sig                  sig;
	ESSigPad<64>               pad;
	ESIssuer                   issuer;
};
static_assert(sizeof(ESSigEcc233) == 192, "ESSigEcc233 size");

#pragma pack(pop)

}} // namespace pie::es