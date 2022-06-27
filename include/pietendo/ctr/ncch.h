	/**
	 * @file ncch.h
	 * @brief Declaration of NCCH structs and enums for the CTR library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/27
	 **/
#pragma once
#include <tc/types.h>

namespace pie { namespace ctr {

#pragma pack(push,4)

struct NcchCommonHeader
{
	static const uint32_t kStructMagic = tc::bn::make_struct_magic_uint32("NCCH");

		/**
		 * @brief NCCH Format Version
		 * @details 
		 * The current version is 2. However due to a bug in the SDK, CFAs do not have this field set, making this field unreliable.
		 */
	enum FormatVersion
	{
		FormatVersion_PROTOTYPE_0 = 0,
		FormatVersion_PROTOTYPE_1 = 1,
		FormatVersion_PRODUCTION = 2,
	};

		/**
		 * @brief NCCH Flag Index
		 * 
		 */
	enum FlagIndex
	{
		FlagIndex_SecurityVersion = 3, /**< Security version for secure crypto */
		FlagIndex_ContentPlatform = 4, /**< Supported platforms */
		FlagIndex_ContentTypeFlag = 5, /**< NCCH Type */
		FlagIndex_BlockSizeLog = 6, /**< NCCH BlockSize (`block_size = 1 << (block_size_log + 9)`, alternatively this is always 0, and the blocksize is always 0x200) */
		FlagIndex_OtherFlag = 7, /**< Misc Other Flags */
	};

		/**
		 * @brief ContentPlatform BitFlags
		 * 
		 */
	enum ContentPlatform
	{
		ContentPlatform_CTR = 0, /**< CTR (3DS) */
		ContentPlatform_SNAKE = 1, /**< SNAKE (New3DS) */
	};

		/**
		 * @brief NCCH Form Type
		 * @details This describes the 
		 */
	enum FormType
	{
		FormType_Unassigned = 0, /**< Invalid */
		FormType_SimpleContent = 1, /**< CFA (Non-executable data archive) */
		FormType_ExecutableWithoutRomFS = 2, /**< CXI (ExeFS Only) */
		FormType_Executable = 3, /**< CXI (ExeFS & RomFS) */
	};

		/**
		 * @brief NCCH Content Type
		 * 
		 */
	enum ContentType
	{
		ContentType_Application = 0, /**< Applicaton */
		ContentType_SystemUpdate = 1, /**< Update Archive (CTR) */
		ContentType_Manual = 2, /**< eManual Archive */
		ContentType_Child = 3, /**< DLP Child Archive */
		ContentType_Trial = 4, /**< Trial Application */
		ContentType_ExtendedSystemUpdate = 5, /**< Update Archive (SNAKE) */
	};

	enum OtherFlag
	{
		OtherFlag_FixedAesKey = 0, /**< Fixed AES key is used */
		OtherFlag_NoMountRomFS = 1, /**< RomFs not present */
		OtherFlag_NoEncryption = 2, /**< NCCH not encrypted */
		OtherFlag_SeededAesKeyY = 5, /**< Secure KeyY requires seed */
		OtherFlag_ManualDisclosure = 6, /**< Manual does not require KeyY seed (only required if application does required seed) */
	};

	struct NcchFlags
	{
		struct ContentTypeFlag
		{
			byte_t form_type : 2;
			byte_t content_type : 6;
		};
		static_assert(sizeof(ContentTypeFlag) == 1, "ContentTypeFlag had incorrect size.");

		tc::bn::pad<3>        reserved;
		byte_t                security_version; // this determines the secure crypto mode, where != 0 this uses a different key for: romfs, & non .icon&.banner exefs
		tc::bn::bitarray<1>   content_platform;
		ContentTypeFlag       content_flag;
		byte_t                block_size_log; // this flag determines the block_size = 1 << (block_size_log + 9), alternatively this is always 0, and the blocksize is always 0x200
		tc::bn::bitarray<1>   other_flag;

		// raw byte access
		byte_t& operator[](size_t index) { return ((byte_t*)this)[index]; }
		const byte_t& operator[](size_t index) const { return ((const byte_t*)this)[index]; }
		const byte_t* data() const { return ((const byte_t*)this); }
		const size_t size() const { return sizeof(uint64_t); }
	};
	static_assert(sizeof(NcchFlags) == 8, "NcchFlags had incorrect size.");

	// 0x00
	tc::bn::le32<uint32_t>    struct_magic; // NCCH
	tc::bn::le32<uint32_t>    content_blk_size;
	tc::bn::le64<uint64_t>    content_id;
	// 0x10
	tc::bn::string<2>         maker_code;
	tc::bn::le16<uint16_t>    format_version;
	std::array<byte_t, 4>     seed_checksum;
	tc::bn::le64<uint64_t>    program_id;
	// 0x20
	tc::bn::pad<16>           reserved_00;
	// 0x30
	std::array<byte_t, 0x20>  logo_hash; // SHA-256 over the entire logo region
	// 0x50
	tc::bn::string<16>        product_code;
	// 0x60
	std::array<byte_t, 0x20>  exhdr_hash; // SHA-256 over exhdr_size of the exhdr region
	// 0x80
	tc::bn::le32<uint32_t>    exhdr_size; // note that this size does not include the access_desc binary that follows the exheader
	tc::bn::pad<4>            reserved_01;
	NcchFlags                 flags;
	// 0x90
	tc::bn::le32<uint32_t>    plain_region_blk_offset;
	tc::bn::le32<uint32_t>    plain_region_blk_size;
	tc::bn::le32<uint32_t>    logo_blk_offset;
	tc::bn::le32<uint32_t>    logo_blk_size;
	// 0xA0
	tc::bn::le32<uint32_t>    exefs_blk_offset;
	tc::bn::le32<uint32_t>    exefs_blk_size;
	tc::bn::le32<uint32_t>    exefs_prot_blk_size;
	tc::bn::pad<4>            reserved_02;
	// 0xB0
	tc::bn::le32<uint32_t>    romfs_blk_offset;
	tc::bn::le32<uint32_t>    romfs_blk_size;
	tc::bn::le32<uint32_t>    romfs_prot_blk_size;
	tc::bn::pad<4>            reserved_03;
	// 0xC0
	std::array<byte_t, 0x20>  exefs_prot_hash;
	// 0xE0
	std::array<byte_t, 0x20>  romfs_prot_hash;
	// 0x100
};
static_assert(sizeof(NcchCommonHeader) == 0x100, "NcchCommonHeader had incorrect size.");

struct NcchHeader
{
	// 0x000-0x0FF : RSA2048-PKCS1-SHA2-256 signature over 0x100-0x1FF
	std::array<byte_t, 0x100> signature;
	// 0x100-0x1FF : NcchCommonHeader
	NcchCommonHeader          header;
	// 0x200
};
static_assert(sizeof(NcchHeader) == 0x200, "NcchHeader had incorrect size.");

struct CxiHeader
{
	// 0x000-0x0FF : RSA2048-PKCS1-SHA2-256 signature over 0x100-0x1FF
	std::array<byte_t, 0x100> signature;
	// 0x100-0x1FF : NcchCommonHeader
	NcchCommonHeader          header;
	// 0x200-0x5FF : NcchExtendedHeader
	std::array<byte_t, 0x400> extended_header;
	// 0x600-0x9FF : NcchAccessControlExtended
	std::array<byte_t, 0x400> access_ctrl_ext;
	// 0xA00
};
static_assert(sizeof(CxiHeader) == 0xA00, "CxiHeader had incorrect size.");


#pragma pack(pop)

}} // namespace pie::ctr