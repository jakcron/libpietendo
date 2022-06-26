	/**
	 * @file ticket.h
	 * @brief Declaration of ES Ticket structs and data types for the ES library
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/25
	 **/
#pragma once
#include <pietendo/es/sign.h>

namespace pie { namespace es {

	/**
	 * @brief ES license types
	 * 
	 */
enum ESLicenseType : uint8_t
{
	ESLicenseType_PERMANENT = 0, /**< Permanent */
	ESLicenseType_DEMO = 1, /**< Demo */
	ESLicenseType_TRIAL = 2, /**< Trial */
	ESLicenseType_RENTAL = 3, /**< Rental */
	ESLicenseType_SUBSCRIPTION = 4, /**< Subscription */
	ESLicenseType_SERVICE = 5, /**< Service */
};

	/**
	 * @brief Maximum 
	 * 
	 */
static const uint8_t ES_LICENSE_MASK = 0xf;

	/**
	 * @brief ES title-level limit codes
	 * 
	 */
enum ESLimitCode : uint32_t
{
	ESLimitCode_DURATION_TIME = 1, /**< Duration time */
	ESLimitCode_ABSOLUTE_TIME = 2, /**< Absolute time */
	ESLimitCode_NUM_TITLES = 3, /**< Number of titles */
	ESLimitCode_NUM_LAUNCH = 4, /**< Number of launches */
	ESLimitCode_ELAPSED_TIME = 5, /**< Elapsed time */
};
static const uint32_t ES_MAX_LIMIT_TYPE = 8;

	/**
	 * @brief ES item-level rights
	 * 
	 */
enum ESItemType : uint32_t
{
	ESItemType_PERMANENT = 1, /**< Permanent */
	ESItemType_SUBSCRIPTION = 2, /**< Subscription */
	ESItemType_CONTENT = 3, /**< Content */
	ESItemType_CONTENT_CONSUMPTION = 4, /**< Content Consumption */
	ESItemType_ACCESS_TITLE = 5, /**< Access Title  */
	ESItemType_LIMITED_RESOURCE = 6, /**< Limited Resource  */
};

	/**
	 * @brief ES PropertyMask flags
	 * 
	 */
enum class ESPropertyMaskFlag : uint16_t
{
	ESPropertyMaskFlag_PRE_INSTALL = 0x1, /**< Pre-install */
	ESPropertyMaskFlag_SHARED_TITLE = 0x2, /**< Shared title */
	ESPropertyMaskFlag_ALLOW_ALL_CONTENT = 0x4, /**< Allow all content */
	ESPropertyMaskFlag_DEVICE_LINK_INDEPENDENT = 0x8, /**< Device link independent */
	ESPropertyMaskFlag_VOLATILE = 0x10, /**< Volatile */
	ESPropertyMaskFlag_ELICENSE_REQUIRED = 0x20, /**< eLicense required */
};

	/**
	 * @brief ES v1 SectionHeader flags
	 * 
	 */
enum ESV1SectionHeaderFlag : uint16_t
{
	ESV1SectionHeaderFlag_COMPRESSED = 0x1 /**< Compressed (This is defined, but not supported by clients.) */
};

	/**
	 * @brief Describes the method of TitleKey encryption.
	 * 
	 * * __COMMON__ - TitleKey is encrypted using AES128-CBC with the CommonKey (as indicated in the ticket header).
	 * * __PERSONALIZED__ - Same as __COMMON__ but the encrypted payload is further encrypted using RSA2048-OAEP, with the device specific RSA key.
	 */
enum ESV2TitleKekType : byte_t
{
	ESV2TitleKekType_COMMON = 0, /**< Common `AES128-CBC(TitleKey)` */
	ESV2TitleKekType_PERSONALIZED = 1, /**< Personalized `RSA2048-OAEP(AES128-CBC(TitleKey))` */
};

#pragma pack(push, 4)

#ifdef _WIN32
#pragma warning(disable : 4200) // silence warnings for usage of empty arrays in stucts
#endif


	/**
	 * @brief This struct describes a limited play restriction
	 * @details 
	 * 
	 * * __code__ Describes the limitation type @ref pie::es::ESLimitCode.
	 * * __limit__ Integer representation of the limitation (seconds, launch count, etc).
	 */
struct ESLimitedPlayEntry
{
	tc::bn::be32<uint32_t> code;
	tc::bn::be32<uint32_t> limit;
};
static_assert(sizeof(ESLimitedPlayEntry) == 8, "ESLimitedPlayEntry size");

	/**
	 * @brief ES Ticket (format v0)
	 * 
	 * Platforms that use this version:
	 * * Nintendo Wii (RVL)
	 * * Nintendo DSi (TWL)
	 */
struct ESTicket
{
	using ESSysAccessMask = std::array<byte_t, 2>;
	using ESTicketCustomData = std::array<byte_t, 20>;
	using ESTicketReserved = std::array<byte_t, 25>;
	using ESCidxMask = std::array<byte_t, 64>;
	using ESLimitedPlayArray = std::array<ESLimitedPlayEntry, 8>;

	ESSigRsa2048              sig;               /**< RSA 2048-bit sign of the ticket */
	Ecc233PublicKey           serverPubKey;      /**< Ticketing server public key */
	uint8_t                   version;           /**< Ticket data structure version number */
	uint8_t                   caCrlVersion;      /**< CA CRL version number */
	uint8_t                   signerCrlVersion;  /**< Signer CRL version number */
	Aes128Key                 titleKey;          /**< Published title key */
	/* 1 byte alignment padding */
	tc::bn::be64<uint64_t>    ticketId;          /**< Unique 64bit ticket ID */
	tc::bn::be32<uint32_t>    deviceId;          /**< Unique 32bit device ID */
	tc::bn::be64<uint64_t>    titleId;           /**< Unique 64bit title ID */
	ESSysAccessMask           sysAccessMask;     /**< 16-bit cidx mask to indicate which of the first 16 pieces of contents can be accessed by the system app */
	tc::bn::be16<uint16_t>    ticketVersion;     /**< 16-bit ticket version */
	tc::bn::be32<uint32_t>    accessTitleId;     /**< 32-bit title ID for access control */
	tc::bn::be32<uint32_t>    accessTitleMask;   /**< 32-bit title ID mask */
	uint8_t                   licenseType;       /**< License type */
	uint8_t                   keyId;             /**< Common key ID */
	tc::bn::be16<uint16_t>    propertyMask;      /**< 16-bit property mask */
	ESTicketCustomData        customData;        /**< 20-byte custom data */
	ESTicketReserved          reserved;          /**< 25-byte reserved info */
	uint8_t                   audit;             /**< 8-bit audit value */
	ESCidxMask                cidxMask;          /**< Bit-mask of the content indices */
	/* 2 bytes alignment padding */
	ESLimitedPlayArray        limits;            /**< Limited play entries */
};
static_assert(sizeof(ESTicket) == 676, "ESTicket size");

struct ESV1TicketHeader
{
	tc::bn::be16<uint16_t>  hdrVersion;         /**< Version of the ticket header */
	tc::bn::be16<uint16_t>  hdrSize;            /**< Size of ticket header */
	tc::bn::be32<uint32_t>  ticketSize;         /**< Size of the v1 portion of the ticket */
	tc::bn::be32<uint32_t>  sectHdrOfst;        /**< Offset of the section header table */
	tc::bn::be16<uint16_t>  nSectHdrs;          /**< Number of section headers */
	tc::bn::be16<uint16_t>  sectHdrEntrySize;   /**< Size of each section header */
	tc::bn::be32<uint32_t>  flags;              /**< Miscellaneous attributes */
};
static_assert(sizeof(ESV1TicketHeader) == 20, "ESV1TicketHeader size");

struct ESV1SectionHeader
{
	tc::bn::be32<uint32_t>  sectOfst;       /**< Offset of this section */
	tc::bn::be32<uint32_t>  nRecords;       /**< Number of records in this section */
	tc::bn::be32<uint32_t>  recordSize;     /**< Size of each record */
	tc::bn::be32<uint32_t>  sectionSize;    /**< Total size of this section */
	tc::bn::be16<uint16_t>  sectionType;    /**< Type code of this section */
	tc::bn::be16<uint16_t>  flags;          /**< Miscellaneous attributes */
};
static_assert(sizeof(ESV1SectionHeader) == 20, "ESV1SectionHeader size");

	/**
	 * @brief ES Ticket (format v1)
	 * 
	 * Platforms that use this version:
	 * * Nintendo WiiU (CAFE)
	 * * Nintendo 3DS (CTR)
	 */
struct ESV1Ticket
{
	ESTicket          head;                    /**< v0 Header */
	ESV1TicketHeader  v1Head;                  /**< v1 Header extension */
	ESV1SectionHeader sectHdrs[];              /**< v1 Section Headers */
};
static_assert(sizeof(ESV1Ticket) == 696, "ESV1Ticket size");

struct ESV1PermanentRecord
{
	using ESReferenceId = std::array<byte_t, 16>;

	ESReferenceId          referenceId;        /**< Reference ID */
	tc::bn::be32<uint32_t> referenceIdAttr;    /**< Reference ID attributes */
};
static_assert(sizeof(ESV1PermanentRecord) == 20, "ESV1PermanentRecord size");

struct ESV1SubscriptionRecord
{
	using ESReferenceId = std::array<byte_t, 16>;

	tc::bn::be32<uint32_t>  limit;              /**< Expiration time */
	ESReferenceId           referenceId;        /**< Reference ID */
	tc::bn::be32<uint32_t>  referenceIdAttr;    /**< Reference ID attributes */
};
static_assert(sizeof(ESV1SubscriptionRecord) == 24, "ESV1SubscriptionRecord size");

struct ESV1ContentRecord
{
	using ESV1CidxMask = std::array<byte_t, 128>;

	tc::bn::be32<uint32_t>  offset;             /**< Offset content index */
	ESV1CidxMask            accessMask;         /**< Access mask */
};
static_assert(sizeof(ESV1ContentRecord) == 132, "ESV1ContentRecord size");

struct ESV1ContentConsumptionRecord
{
	tc::bn::be16<uint16_t>  index;              /**< Content index */
	tc::bn::be16<uint16_t>  code;               /**< Limit code */
	tc::bn::be32<uint32_t>  limit;              /**< Limit value */
};
static_assert(sizeof(ESV1ContentConsumptionRecord) == 8, "ESV1ContentConsumptionRecord size");

struct ESV1AccessTitleRecord
{
	tc::bn::be64<uint64_t>  accessTitleId;      /**< Access title ID */
	tc::bn::be64<uint64_t>  accessTitleMask;    /**< Access title mask */
};
static_assert(sizeof(ESV1AccessTitleRecord) == 16, "ESV1AccessTitleRecord size");

struct ESV1LimitedResourceRecord
{
	using ESReferenceId = std::array<byte_t, 16>;

	tc::bn::be32<uint32_t>  limit;              /**< Expiration time */
	ESReferenceId           referenceId;        /**< Reference ID */
	tc::bn::be32<uint32_t>  referenceIdAttr;    /**< Reference ID attributes */
};
static_assert(sizeof(ESV1LimitedResourceRecord) == 24, "ESV1LimitedResourceRecord size");

	/**
	 * @brief ES Ticket (format v2)
	 * 
	 * Platforms that use this version:
	 * * Nintendo Switch (HAC)
	 */
struct ESV2Ticket
{
	using ESV2TitleKey = Rsa2048Integer;
	using ESRightsId = std::array<byte_t, 16>;
	using ESV2TicketReserved = std::array<byte_t, 8>;

	ESSigRsa2048            sig;                /**< RSA 2048-bit sign of the ticket */
	ESV2TitleKey            titleKey;           /**< Published title key */
	uint8_t                 version;            /**< Ticket data structure version number */
	uint8_t                 keyType;            /**< Title key encryption key type */
	tc::bn::le16<uint16_t>  ticketVersion;      /**< 16-bit ticket version */
	uint8_t                 licenseType;        /**< License type */
	uint8_t                 keyId;              /**< Common key ID */
	tc::bn::le16<uint16_t>  propertyMask;       /**< 16-bit property mask */
	ESV2TicketReserved      reservedRegion;     /**< probably the accessTitleId & mask */
	tc::bn::le64<uint64_t>  ticketId;           /**< Unique 64bit ticket ID */
	tc::bn::le64<uint64_t>  deviceId;           /**< Unique 64bit device ID */
	ESRightsId              rightsId;           /**< Unique 128bit rights ID */
	tc::bn::le32<uint32_t>  accountId;          /**< Unique 32bit account ID */
	tc::bn::le32<uint32_t>  sectTotalSize;      /**< Total size of sections */
	tc::bn::le32<uint32_t>  sectHdrOffset;      /**< Offset of the section header table */
	tc::bn::le16<uint16_t>  nSectHdrs;          /**< Number of section headers */
	tc::bn::le16<uint16_t>  nSectHdrEntrySize;  /**< Size of each section header */
};
static_assert(sizeof(ESV2Ticket) == 704, "ESV2Ticket size");

struct ESV2SectionHeader
{
	tc::bn::le32<uint32_t>  sectOfst;       /**< Offset of this section */
	tc::bn::le32<uint32_t>  recordSize;     /**< Size of each record */
	tc::bn::le32<uint32_t>  sectionSize;    /**< Total size of this section */
	tc::bn::le16<uint16_t>  nRecords;       /**< Number of records in this section */
	tc::bn::le16<uint16_t>  sectionType;    /**< Type code of this section */
};
static_assert(sizeof(ESV2SectionHeader) == 16, "ESV2SectionHeader size");

#ifdef _WIN32
#pragma warning(default : 4200)
#endif

#pragma pack(pop)

}} // namespace pie::es