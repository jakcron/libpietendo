	/**
	 * @file gc.h
	 * @brief Declaration of GameCard structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace gc
{
	static const uint32_t kGcHeaderStructMagic = tc::bn::make_struct_magic_uint32("HEAD");
	static const uint32_t kHeaderEncOffset = 0x90;
	static const uint32_t kHeaderEncSize = 0x70;
	static const uint32_t kPageSize = 0x200;
	static const uint32_t kUppHashLen = 8;
	/*
	static const uint32_t kCardKeyAreaPageCount = 8;
	static const uint32_t kCardHeaderPageCount = 1;
	static const uint32_t kReservedAreaPageCount = 55;
	static const uint32_t kCertAreaStartPageAddress = kCardHeaderPageCount + kReservedAreaPageCount + kCardKeyAreaPageCount;
	static const uint32_t kCertAreaPageCount = 64;
	static const uint32_t kNormalAreaStartPageAddress = kReservedAreaPageCount + kCertAreaPageCount + kCardHeaderPageCount + kCardKeyAreaPageCount;
	*/
	using upp_hash_t = std::array<byte_t, kUppHashLen>;

	const std::string kUpdatePartitionStr = "update"; 
	const std::string kLogoPartitionStr = "logo"; 
	const std::string kNormalPartitionStr = "normal"; 
	const std::string kSecurePartitionStr = "secure"; 

	enum KekIndex
	{
		KekIndex_Prod = 0,
		KekIndex_Dev = 1
	};

	enum RomSize
	{
		RomSize_1GB = 0xFA,
		RomSize_2GB = 0xF8,
		RomSize_4GB = 0xF0,
		RomSize_8GB = 0xE0,
		RomSize_16GB = 0xE1,
		RomSize_32GB = 0xE2
	};

	enum HeaderFlags
	{
		HeaderFlags_AutoBoot = 0,
		HeaderFlags_HistoryErase = 1,
		HeaderFlags_RepairTimeRevisorTool = 2,
		HeaderFlags_AllowCupToChina = 3,
		HeaderFlags_AllowCupToGlobal = 4
	};

	enum FwVersion
	{
		FwVersion_DevKit = 0,
		FwVersion_Prod = 1,
		FwVersion_Prod_Since4_0_0NUP = 2,
		FwVersion_Prod_Since11_0_0NUP = 4,
		FwVersion_Prod_Since12_0_0NUP = 5
	};

	enum CardClockRate
	{
		CardClockRate_25MHz = 10551312,
		CardClockRate_50MHz = 10551313
	};

	enum CompatibilityType
	{
		CompatibilityType_Global = 0,
		CompatibilityType_China = 1
	};
}

#pragma pack(push,1)

struct sGcPage
{
	byte_t data[gc::kPageSize];
};
static_assert(sizeof(sGcPage) == gc::kPageSize, "sGcPage size.");

struct sGcHeader
{
	tc::bn::le32<uint32_t> st_magic;
	tc::bn::le32<uint32_t> rom_area_start_page;
	tc::bn::le32<uint32_t> backup_area_start_page;
	byte_t key_flag;
	byte_t rom_size;
	byte_t card_header_version;
	tc::bn::bitarray<sizeof(byte_t)> flags;
	tc::bn::le64<uint64_t> package_id;
	tc::bn::le32<uint32_t> valid_data_end_page;
	std::array<byte_t, 0x4> reserved_00;
	detail::aes_iv_t aescbc_iv;
	tc::bn::le64<uint64_t> partition_fs_header_address;
	tc::bn::le64<uint64_t> partition_fs_header_size;
	detail::sha256_hash_t partition_fs_header_hash;
	detail::sha256_hash_t initial_data_hash;
	tc::bn::le32<uint32_t> sel_sec;
	tc::bn::le32<uint32_t> sel_t1_key;
	tc::bn::le32<uint32_t> sel_key;
	tc::bn::le32<uint32_t> lim_area;
	union {
		std::array<byte_t, gc::kHeaderEncSize> raw_data;
		struct {
			tc::bn::le64<uint64_t> fw_version;
			tc::bn::le32<uint32_t> acc_ctrl_1;
			tc::bn::le32<uint32_t> wait_1_time_read;
			tc::bn::le32<uint32_t> wait_2_time_read;
			tc::bn::le32<uint32_t> wait_1_time_write;
			tc::bn::le32<uint32_t> wait_2_time_write;
			tc::bn::le32<uint32_t> fw_mode;
			tc::bn::le32<uint32_t> upp_version;
			byte_t region_compatibility;
			std::array<byte_t, 0x3> reserved_01;
			gc::upp_hash_t upp_hash;
			tc::bn::le64<uint64_t> upp_id;
		};
	} extended_header;
};
static_assert(sizeof(sGcHeader) == 0x100, "sGcHeader size.");

struct sGcHeader_Rsa2048Signed
{
	detail::rsa2048_signature_t signature;
	sGcHeader header;
};
static_assert(sizeof(sGcHeader_Rsa2048Signed) == 0x200, "sGcHeader_Rsa2048Signed size.");

struct sGcInitialData
{
	std::array<byte_t, 16> key_source; // { package_id[8], zeros[8]}
	std::array<byte_t, 16> title_key_enc;
	std::array<byte_t, 16> ccm_mac;
	std::array<byte_t, 12> ccm_nonce;
};
static_assert(sizeof(sGcInitialData) == 0x3C, "sGcInitialData size.");

struct sGcKeyDataRegion
{
	union {
		std::array<sGcPage, 1> raw_page;
		sGcInitialData initial_data; // AES128-CCM encrypted {titlekey[16]}
	} initial_data_region;

	union {
		std::array<sGcPage, 6> raw_pages;
		struct {
			std::array<byte_t, gc::kPageSize * 6> encrypted_data; // AES128-CTR encrypted {titlekey[16]}
		} enc;
		struct {
			detail::aes128_key_t title_key;
		} dec;
	} title_key_region;
	
	union {
		std::array<sGcPage, 1> raw_page;
		struct {
			detail::rsa2048_block_t encrypted_data; // RSA2048-OAEP-SHA256 encrypted AES-CTR data used for encrypted_00 {key[16],iv[16]}
		} enc;
		struct {
			detail::aes128_key_t title_key_encryption_key;
			detail::aes_iv_t title_key_encryption_ctr;
		} dec;
	} title_key_encryption_params_region;
};
static_assert(sizeof(sGcKeyDataRegion) == gc::kPageSize * 8, "sGcKeyDataRegion size.");

struct sSdkGcHeader
{
	sGcKeyDataRegion keydata;
	sGcHeader_Rsa2048Signed signed_header;
};
static_assert(sizeof(sSdkGcHeader) == 0x1200, "sSdkGcHeader size.");

#pragma pack(pop)

}} // namespace pie::hac