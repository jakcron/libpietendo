#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
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
			KEK_PROD = 0,
			KEK_DEV = 1
		};

		enum RomSize
		{
			ROM_SIZE_1GB = 0xFA,
			ROM_SIZE_2GB = 0xF8,
			ROM_SIZE_4GB = 0xF0,
			ROM_SIZE_8GB = 0xE0,
			ROM_SIZE_16GB = 0xE1,
			ROM_SIZE_32GB = 0xE2
		};

		enum HeaderFlags
		{
			FLAG_AUTOBOOT,
			FLAG_HISTORY_ERASE,
			FLAG_REPAIR_TIME_REVISOR_TOOL,
			FLAG_ALLOW_CUP_TO_CHINA,
			FLAG_ALLOW_CUP_TO_GLOBAL,
		};

		enum FwVersion
		{
			FWVER_DEV = 0,
			FWVER_PROD = 1,
			FWVER_PROD_SINCE_4_0_0NUP = 2,
			FWVER_PROD_SINCE_11_0_0NUP = 4,
			FWVER_PROD_SINCE_12_0_0NUP = 5,
		};

		enum CardClockRate
		{
			CLOCK_RATE_25 = 10551312,
			CLOCK_RATE_50 = 10551313,
		};

		enum CompatibilityType
		{
			COMPAT_GLOBAL,
			COMPAT_CHINA
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
}
}