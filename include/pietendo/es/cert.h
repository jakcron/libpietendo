	/**
	 * @file cert.h
	 * @brief Declaration of Certificate structs and enums for the ES library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/25
	 **/
#pragma once
#include <pietendo/es/sign.h>

namespace pie { namespace es {

	/**
	 * @brief ES Certificate public key type
	 */
enum ESCertPubKeyType : uint32_t
{
	ESCertPubKeyType_RSA4096 = 0, /**< RSA 4096 bit key */
	ESCertPubKeyType_RSA2048 = 1, /**< RSA 2048 bit key */
	ESCertPubKeyType_ECC233 = 2, /**< ECC 233 bit key */
};

	/**
	 * @brief The ASCII encoded certificate name. Padded with nulls.
	 * @details
	 * 
	 * Examples: 
	 * * __Root__ (__Root__ issuer)
	 * * __CAxxxxxxxx__ (Certifcate Authority server __xxxxxxxx__)
	 * * __XSxxxxxxxx__ (Ticket/Transaction server __xxxxxxxx__)
	 * * __CPxxxxxxxx__ (Content Publishing server __xxxxxxxx__)
	 * * __MSxxxxxxxx__ (Manufacturing server __xxxxxxxx__)
	 * * __YYxxxxxxxx__ (Device with of type __YY__ and serial number __xxxxxxxx__)
	 * 
	 * __xxxxxxxx__ represents the server/device serial number encoded in hex. (e.g. __XS0000000f__ is ticket server 15).
	 */
using ESCertName = tc::bn::string<64>;
using ESServerId = ESCertName;
using ESDeviceId = ESCertName;

	/**
	 * @brief Template for defining padding in ES public key structures.
	 * 
	 * @tparam _size Padding size in bytes.
	 */
template <size_t _size>
using ESPubKeyPad = std::array<byte_t, _size>; 

/* pack to 4 byte boundaries */
#pragma pack(push,4)

	/**
	 * @brief Certificate Header
	 * 
	 */
struct ESCertHeader
{
	tc::bn::be32<ESCertPubKeyType> pubKeyType; /**< Public key type */
	union {
		ESServerId serverId;
		ESDeviceId deviceId;
	} name;                                    /**< Certificate name */
	tc::bn::be32<uint32_t> date;               /**< Unix time-stamp (this isn't honoured often) */
};
static_assert(sizeof(ESCertHeader) == 72, "ESCertHeader size");

	/**
	 * @brief Certificate Public Key (RSA2048)
	 * 
	 */
struct ESCertRsa2048PublicKey
{
	Rsa2048PublicKey      pubKey; /**< RSA2048 Public Key */
	ESPubKeyPad<52>       pad;    /**< Padding */
};
static_assert(sizeof(ESCertRsa2048PublicKey) == 312, "ESCertRsa2048PublicKey size");

	/**
	 * @brief Certificate Public Key (RSA4096)
	 * 
	 */
struct ESCertRsa4096PublicKey
{
	Rsa4096PublicKey      pubKey; /**< RSA4096 Public Key */
	ESPubKeyPad<52>       pad;    /**< Padding */
};
static_assert(sizeof(ESCertRsa4096PublicKey) == 568, "ESCertRsa4096PublicKey size");

	/**
	 * @brief Certificate Public Key (ECC233)
	 * 
	 */
struct ESCertEcc233PublicKey
{
	Ecc233PublicKey       pubKey; /**< ECC233 Public Key */
	ESPubKeyPad<60>       pad;    /**< Padding */
};
static_assert(sizeof(ESCertEcc233PublicKey) == 120, "ESCertEcc233PublicKey size");

	/**
	 * @brief Root Certificate
	 * 
	 */
struct ESRootCert
{
	ESSigRsa4096             sig;  /**< RSA 4096-bit sign of the certificate */
	ESCertHeader             head; /**< Certificate header */
	ESCertRsa4096PublicKey   body; /**< Certificate body */
};
static_assert(sizeof(ESRootCert) == 1280, "ESRootCert size");

	/**
	 * @brief Certificate Authority (CA) Certificate
	 * @details 
	 * These are always signed by __Root__
	 */
struct ESCACert
{
	ESSigRsa4096             sig;  /**< RSA 4096-bit sign of the certificate */
	ESCertHeader             head; /**< Certificate header */
	ESCertRsa2048PublicKey   body; /**< Certificate body */
};
static_assert(sizeof(ESCACert) == 1024, "ESCACert size");

	/**
	 * @brief CA Signed Certificate
	 * 
	 */
struct ESCASignedCert
{
	ESSigRsa2048             sig;  /**< RSA 2048-bit sign of the certificate */
	ESCertHeader             head; /**< Certificate header */
	ESCertRsa2048PublicKey   body; /**< Certificate body */
};
static_assert(sizeof(ESCASignedCert) == 768, "ESCASignedCert size");

	/**
	 * @brief Device Certificate
	 * @details 
	 * These are unique to a given device, used to identify genuine devices.
	 */
struct ESDeviceCert
{
	ESSigRsa2048             sig;  /**< RSA 2048-bit sign of the certificate */
	ESCertHeader             head; /**< Certificate header */
	ESCertEcc233PublicKey    body; /**< Certificate body */
};
static_assert(sizeof(ESDeviceCert) == 576, "ESDeviceCert size");

	/**
	 * @brief Device Signed Certificate
	 * @details 
	 * These are used to sign content exported to untrusted/external storage by a device (e.g. save data)
	 */
struct ESDeviceSignedCert
{
	ESSigEcc233              sig;  /**< ECDSA 233-bit sign of the certificate */
	ESCertHeader             head; /**< Certificate header */
	ESCertEcc233PublicKey    body; /**< Certificate body */
};
static_assert(sizeof(ESDeviceSignedCert) == 384, "ESDeviceSignedCert size");

#pragma pack(pop)

}} // namespace pie::es
