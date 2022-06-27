#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace cnmt
	{
		enum class ContentType : byte_t
		{
			Meta = 0,
			Program,
			Data,
			Control,
			HtmlDocument,
			LegalInformation,
			DeltaFragment
		};

		enum class ContentMetaType : byte_t
		{
			SystemProgram = 1,
			SystemData,
			SystemUpdate,
			BootImagePackage,
			BootImagePackageSafe,

			Application = 0x80,
			Patch, // can have extended data
			AddOnContent,
			Delta // can have extended data
		};

		enum class UpdateType : byte_t
		{
			ApplyAsDelta,
			Overwrite,
			Create
		};

		enum class ContentInstallType : byte_t 
		{
			Full,
			FragmentOnly
		};

		enum class StorageId : byte_t
		{
			None,
			Host,
			GameCard,
			BuiltInSystem,
			BuiltInUser,
			SdCard,
			Any
		};

		enum class ContentMetaAttributeFlag
		{
			IncludesExFatDriver,
			Rebootless,
			Compacted
		};
		
		using content_meta_attribute_t = tc::bn::bitarray<sizeof(byte_t)>;

		enum class InstallStateFlag
		{
			Committed
		};

		using install_state_t = tc::bn::bitarray<sizeof(byte_t)>;

		static const size_t kContentIdLen = 0x10;
		using content_id_t = std::array<byte_t, kContentIdLen>;

		static const size_t kDigestLen = 0x20;
		using digest_t = detail::sha256_hash_t;
	}


#pragma pack(push,1)
	/*
	struct sContentMeta
	{
		sContentMetaHeader hdr;
		byte_t exhdr[]; // optional
		sContentInfo info[];
		sContentMetaInfo meta[];
		byte_t extdata[];
		byte_t digest[32]
	};
	*/

	struct sContentMetaHeader
	{
		tc::bn::le64<uint64_t> id;
		tc::bn::le32<uint32_t> version;
		byte_t type;
		byte_t reserved_0;
		tc::bn::le16<uint16_t> exhdr_size;
		tc::bn::le16<uint16_t> content_count;
		tc::bn::le16<uint16_t> content_meta_count;
		cnmt::content_meta_attribute_t attributes;
		byte_t storage_id;
		byte_t install_type;
		cnmt::install_state_t install_state;
		tc::bn::le32<uint32_t> required_download_system_version;
		std::array<byte_t, 0x4> reserved_1;
	};
	static_assert(sizeof(sContentMetaHeader) == 0x20, "sContentMetaHeader size.");

	struct sContentInfo
	{
		detail::sha256_hash_t content_hash;
		cnmt::content_id_t content_id;
		tc::bn::le32<uint32_t> size_lower;
		tc::bn::le16<uint16_t> size_higher;
		byte_t content_type;
		byte_t id_offset;
	};
	static_assert(sizeof(sContentInfo) == 0x38, "sContentInfo size.");

	struct sContentMetaInfo
	{
		tc::bn::le64<uint64_t> id;
		tc::bn::le32<uint32_t> version;
		byte_t type;
		cnmt::content_meta_attribute_t attributes;
		std::array<byte_t, 0x2> reserved;
	};
	static_assert(sizeof(sContentMetaInfo) == 0x10, "sContentMetaInfo size.");

	struct sApplicationMetaExtendedHeader
	{
		tc::bn::le64<uint64_t> patch_id;
		tc::bn::le32<uint32_t> required_system_version;
		tc::bn::le32<uint32_t> required_application_version;
	};
	static_assert(sizeof(sApplicationMetaExtendedHeader) == 0x10, "sApplicationMetaExtendedHeader size.");

	struct sPatchMetaExtendedHeader
	{
		tc::bn::le64<uint64_t> application_id;
		tc::bn::le32<uint32_t> required_system_version;
		tc::bn::le32<uint32_t> extended_data_size;
		std::array<byte_t, 0x8> reserved;
	};
	static_assert(sizeof(sPatchMetaExtendedHeader) == 0x18, "sPatchMetaExtendedHeader size.");

	struct sAddOnContentMetaExtendedHeader
	{
		tc::bn::le64<uint64_t> application_id;
		tc::bn::le32<uint32_t> required_application_version;
		std::array<byte_t, 0x4> reserved;
	};
	static_assert(sizeof(sAddOnContentMetaExtendedHeader) == 0x10, "sAddOnContentMetaExtendedHeader size.");

	struct sDeltaMetaExtendedHeader
	{
		tc::bn::le64<uint64_t> application_id;
		tc::bn::le32<uint32_t> extended_data_size;
		std::array<byte_t, 0x4> reserved;
	};
	static_assert(sizeof(sDeltaMetaExtendedHeader) == 0x10, "sDeltaMetaExtendedHeader size.");

	struct sSystemUpdateMetaExtendedHeader
	{
		tc::bn::le32<uint32_t> extended_data_size;
	};
	static_assert(sizeof(sSystemUpdateMetaExtendedHeader) == 0x4, "sSystemUpdateMetaExtendedHeader size.");

	/*
	struct sSystemUpdateMetaData
	{
		sSystemUpdateMetaExtendedDataHeader header;
		if (header.version == 1)
		{
			sFirmwareVariationInfo_v1 variation_info[header.variation_count];
		}
		else if (header.version == 2)
		{
			tc::bn::le32<uint32_t> firmware_variation_id[header.variation_count];
			sFirmwareVariationInfo_v2 variation_info[header.variation_count];
			sContentMetaInfo content_meta_info[total of variation_infos.meta_count IF refer_to_base is false]
		}
		else
		{
			undefined
		}
	}
	*/

	struct sSystemUpdateMetaExtendedDataHeader
	{
		tc::bn::le32<uint32_t> version;
		tc::bn::le32<uint32_t> variation_count;
	};
	static_assert(sizeof(sSystemUpdateMetaExtendedDataHeader) == 0x8, "sSystemUpdateMetaExtendedDataHeader size.");

	struct sFirmwareVariationInfo_v1
	{
		tc::bn::le32<uint32_t> firmware_variation_id;
		std::array<byte_t, 0x1C> reserved_x04;
	};
	static_assert(sizeof(sFirmwareVariationInfo_v1) == 0x20, "sFirmwareVariationInfo_v1 size.");

	struct sFirmwareVariationInfo_v2
	{
		byte_t refer_to_base;
		std::array<byte_t, 0x3> reserved_x01;
		tc::bn::le32<uint32_t> meta_count;
		std::array<byte_t, 0x18> reserved_x08;
	};
	static_assert(sizeof(sFirmwareVariationInfo_v2) == 0x20, "sFirmwareVariationInfo_v2 size.");

#pragma pack(pop)
}
}