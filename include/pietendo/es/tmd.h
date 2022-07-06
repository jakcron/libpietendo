	/**
	 * @file tmd.h
	 * @brief Declaration of TitleMeta structs and enums for the ES library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/25
	 **/
#pragma once
#include <pietendo/es/sign.h>

namespace pie { namespace es {

	/**
	 * @brief ES title type
	 * 
	 */
enum ESTitleType : uint32_t
{
	//ESTitleType_NC_TITLE   = (1 << 0), /**< NetCard Title - NetCard, End-of-life (bit0) */
	//ESTitleType_NG_TITLE   = (1 << 1), /**< NextGen Title - Wii/NDEV (bit1) */
	//ESTitleType_DS_TITLE   = (1 << 2), /**< DS Title - TWL/DSi (bit2) */
	//ESTitleType_DATA       = (1 << 3), /**< Data Title (bit3) */
	//ESTitleType_CT_TITLE   = (1 << 6), /**< CTR Title - CTR/3DS (bit6) */
	//ESTitleType_GVM_TITLE  = (1 << 7), /**< GVM Title - Graphics Virtual Machine (bit7) */
	//ESTitleType_CAFE_TITLE = (1 << 8), /**< Cafe Title - WiiU (bit8) */
};

	/**
	 * @brief ES content type (ContentType BitMasks)
	 * @details
	 * These flags describe properties about a particular content.
	 * 
	 * Supported flags vary from platform to platform.
	 * 
	 * RVL (Wii) supported flags:
	 * * ESContentType_ENCRYPTED
	 * * ESContentType_HASHED
	 * * ESContentType_OPTIONAL
	 * * ESContentType_SHARED
	 * 
	 * TWL (DSi) supported flags:
	 * * ESContentType_ENCRYPTED
	 * 
	 * CTR (3DS) supported flags:
	 * * ESContentType_ENCRYPTED
	 * * ESContentType_OPTIONAL
	 * 
	 * CAFE (WiiU) supported flags:
	 * * ESContentType_ENCRYPTED
	 * * ESContentType_HASHED
	 * * ESContentType_SHA1_HASH
	 * * ESContentType_OPTIONAL
	 */
enum ESContentType : uint16_t
{
	ESContentType_ENCRYPTED = (1 <<  0), /**< Encrypted - (bit0) */
	ESContentType_HASHED    = (1 <<  1), /**< Hashed (Previously this was called DISC, because only RVL discs had the hashed data) - (bit1) */
	ESContentType_CFM       = (1 <<  2), /**< Content File Metadata - (bit2) */
	ESContentType_SHA1_HASH = (1 << 13), /**< SHA1 Hash - (bit13) */
	ESContentType_OPTIONAL  = (1 << 14), /**< Optional Content - (bit14) */
	ESContentType_SHARED    = (1 << 15), /**< Shared Content - (bit15) */
};

	/**
	 * @brief Maximum possible content index
	 * @details
	 * Maximum possible content index value is 64K - 2, since
	 * the maximum number of contents per title is 64K - 1
	 */
static const size_t ES_CONTENT_INDEX_MAX = 65534;

	/**
	 * @brief Maximum possible CMD groups
	 * @details
	 * There are a maximum of 64 CMD groups.
	 */
static const size_t ES_MAX_CMD_GROUPS = 64;

	/**
	 * @brief Maximum possible CMDs in CMD group
	 * @details
	 * Witin a given CMD group, there can be a maximum of 1K CMDs
	 */
static const size_t ES_MAX_CMDS_IN_GROUP = 1024;

#pragma pack(push, 4)

#ifdef _WIN32
#pragma warning(disable : 4200) // silence warnings for usage of empty arrays in stucts
#endif

	/**
	 * @brief ContentMetaData (format v0)
	 * @details 
	 * 
	 * This is used with v0 TitleMetaData.
	 */
struct ESContentMeta
{
	tc::bn::be32<uint32_t> cid;    /**< 32-bit content ID */
	tc::bn::be16<uint16_t> index;  /**< Content index, unique per title */
	tc::bn::be16<uint16_t> type;   /**< Content type */
	tc::bn::be64<uint64_t> size;   /**< Unencrypted content size in bytes */
	detail::Sha1Hash       hash;   /**< Hash of the content */
};
static_assert(sizeof(ESContentMeta) == 36, "ESContentMeta size");

	/**
	 * @brief ContentMetaData (format v1)
	 * @details
	 * 
	 * This is used with v1 TitleMetaData.
	 */
struct ESV1ContentMeta
{
	tc::bn::be32<uint32_t> cid;    /**< 32-bit content ID */
	tc::bn::be16<uint16_t> index;  /**< Content index, unique per title */
	tc::bn::be16<uint16_t> type;   /**< Content type */
	tc::bn::be64<uint64_t> size;   /**< Unencrypted content size in bytes */
	detail::Sha256Hash     hash;   /**< Hash of the content */
};
static_assert(sizeof(ESV1ContentMeta) == 48, "ESV1ContentMeta size");

	/**
	 * @brief TitleMetaData v0 Header
	 * 
	 */
struct ESTitleMetaHeader
{
	using ESTmdCustomData = std::array<uint8_t, 32>;
	using ESTmdReserved = std::array<uint8_t, 30>;

	uint8_t                   version;            /**< TMD version number */
	uint8_t                   caCrlVersion;       /**< CA CRL version number */
	uint8_t                   signerCrlVersion;   /**< Signer CRL version number */
	uint8_t                   customFlag;         /**< 1-byte custom flag. Used only in WiiU vWii TMDs (set to 1). */
	tc::bn::be64<uint64_t>    sysVersion;         /**< System software version number */
	tc::bn::be64<uint64_t>    titleId;            /**< 64-bit title id */
	tc::bn::be32<ESTitleType> type;               /**< 32-bit title type */
	tc::bn::be16<uint16_t>    groupId;            /**< 16-bit group id */
	ESTmdCustomData           customData;         /**< 32-byte custom data */
	ESTmdReserved             reserved;           /**< 30-byte reserved info */
	tc::bn::be32<uint32_t>    accessRights;       /**< Rights to system resources */
	tc::bn::be16<uint16_t>    titleVersion;       /**< 16-bit title version */
	tc::bn::be16<uint16_t>    numContents;        /**< Number of contents */
	tc::bn::be16<uint16_t>    bootIndex;          /**< Boot content index */
	tc::bn::be16<uint16_t>    minorTitleVersion;  /**< 16-bit minor title version */
};
static_assert(sizeof(ESTitleMetaHeader) == 100, "ESTitleMetaHeader size");

struct ESV1ContentMetaGroup
{
	tc::bn::be16<uint16_t> offset;             /**< Offset content index */
	tc::bn::be16<uint16_t> nCmds;              /**< Number of CMDs in this group */
	detail::Sha256Hash     groupHash;          /**< Hash for this group of CMDs */
};
static_assert(sizeof(ESV1ContentMetaGroup) == 36, "ESV1ContentMetaGroup size");

	/**
	 * @brief TitleMetaData v1 Header Extension
	 * 
	 */
struct ESV1TitleMetaHeader
{
	using ESV1ContentMetaGroupArray = std::array<ESV1ContentMetaGroup, ES_MAX_CMD_GROUPS>;

	detail::Sha256Hash        hash;          /**< Hash for the CMD groups */
	ESV1ContentMetaGroupArray cmdGroups;     /**< CMD Groups */
};
static_assert(sizeof(ESV1TitleMetaHeader) == 2336, "ESV1TitleMetaHeader size");

	/**
	 * @brief TitleMetaData (format v0)
	 * 
	 * Platforms that use this version:
	 * * Nintendo Wii (RVL)
	 * * Nintendo DSi (TWL)
	 */
struct ESTitleMeta
{
	ESSigRsa2048      sig;            /**< RSA 2048-bit sign of the TMD header */
	ESTitleMetaHeader head;           /**< TMD v0 header */ 
	ESContentMeta     contents[];     /**< CMD array sorted by content index */
};
static_assert(sizeof(ESTitleMeta) == 484, "ESTitleMeta size");

	/**
	 * @brief TitleMetaData (format v1)
	 * 
	 * Platforms that use this version:
	 * * Nintendo 3DS (CTR)
	 * * Nintendo WiiU (CAFE)
	 */
struct ESV1TitleMeta
{
	ESSigRsa2048        sig;            /**< RSA 2048-bit sign of the TMD header */
	ESTitleMetaHeader   head;           /**< TMD v0 header */ 
	ESV1TitleMetaHeader v1Head;         /**< Extension to the v0 TMD header */
	ESV1ContentMeta     contents[];     /**< CMD array sorted by content index */
};
static_assert(sizeof(ESV1TitleMeta) == 2820, "ESV1TitleMeta size");

#ifdef _WIN32
#pragma warning(default : 4200)
#endif

#pragma pack(pop)

}} // namespace pie::es