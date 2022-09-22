	/**
	 * @file sign.h
	 * @brief Declaration of ES Signature structs and data types for the ES library
	 * @author Jack (jakcron)
	 * @version 0.2
	 * @date 2022/09/22
	 **/
#pragma once
#include <pietendo/es/types.h>

namespace pie { namespace es {

	/**
     * @brief ES Signature type
     */
enum ESSigType : uint32_t
{
    ESSigType_RSA4096_SHA1    = 0x00010000, /**< __RSA-4096-PKCS1-SHA1__ signature */
    ESSigType_RSA2048_SHA1    = 0x00010001, /**< __RSA-2048-PKCS1-SHA1__ signature */
    ESSigType_ECCB233_SHA1    = 0x00010002, /**< __ECC-B233-ECDSA-SHA1__ signature */
    ESSigType_RSA4096_SHA2256 = 0x00010003, /**< __RSA-4096-PKCS1-SHA2-256__ signature */
    ESSigType_RSA2048_SHA2256 = 0x00010004, /**< __RSA-2048-PKCS1-SHA2-256__ signature */
    ESSigType_ECCB233_SHA2256 = 0x00010005, /**< __ECC-B233-ECDSA-SHA2-256__ signature */
    ESSigType_HMAC_SHA1       = 0x00010006, /**< __HMAC-SHA1__ signature (This uses the ESSigRsa2048 sign structure, with spare sig space padded with nulls) */
};

	/**
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
using ESIssuer = tc::bn::string<64>;  

/* pack to 4 byte boundaries */
#pragma pack(push,4)

	/**
	 * @brief ES Signature (RSA-2048)
	 * 
	 */
struct ESSigRsa2048
{
	tc::bn::be32<ESSigType>    sigType; /**< Signature type */
	detail::Rsa2048Sig         sig;     /**< Signature data */
	detail::Padding<60>        pad;     /**< Padding */
	ESIssuer                   issuer;  /**< Signature issuer */
};
static_assert(sizeof(ESSigRsa2048) == 384, "ESSigRsa2048 size");

	/**
	 * @brief ES Signature (RSA-2048) (Little Endian variant)
	 * @details This is used for Nintendo Switch Tickets
	 * 
	 */
struct ESSigRsa2048_LE
{
	tc::bn::le32<ESSigType>    sigType; /**< Signature type */
	detail::Rsa2048Sig         sig;     /**< Signature data */
	detail::Padding<60>        pad;     /**< Padding */
	ESIssuer                   issuer;  /**< Signature issuer */
};
static_assert(sizeof(ESSigRsa2048_LE) == 384, "ESSigRsa2048_LE size");


	/**
	 * @brief ES Signature (RSA-4096)
	 * 
	 */
struct ESSigRsa4096
{
	tc::bn::be32<ESSigType>    sigType; /**< Signature type */
	detail::Rsa4096Sig         sig;     /**< Signature data */
	detail::Padding<60>        pad;     /**< Padding */
	ESIssuer                   issuer;  /**< Signature issuer */
};
static_assert(sizeof(ESSigRsa4096) == 640, "ESSigRsa4096 size");

	/**
	 * @brief ES Signature (ECC-B233)
	 * 
	 */
struct ESSigEccB233
{
	tc::bn::be32<ESSigType>    sigType; /**< Signature type */
	detail::EccB233Sig         sig;     /**< Signature data */
	detail::Padding<64>        pad;     /**< Padding */
	ESIssuer                   issuer;  /**< Signature issuer */
};
static_assert(sizeof(ESSigEccB233) == 192, "ESSigEccB233 size");

#pragma pack(pop)

}} // namespace pie::es