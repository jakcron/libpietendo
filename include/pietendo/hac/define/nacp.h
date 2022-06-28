	/**
	 * @file nacp.h
	 * @brief Declaration of Application Control Property structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace nacp
{
	static const size_t kNameLength = 512;
	static const size_t kNameStringLength = 127;
	static const size_t kPublisherLength = 256;
	static const size_t kPublisherStringLength = 63;
	static const size_t kMaxLanguageCount = 16;
	static const size_t kIsbnLength = 37;
	static const size_t kRatingAgeCount = 32;
	static const size_t kDisplayVersionLength = 16;
	static const size_t kApplicationErrorCodeCategoryLength = 8;
	static const size_t kLocalCommunicationIdCount = 8;
	static const size_t kBcatPassphraseLength = 65;
	static const size_t kPlayLogQueryableApplicationIdCount = 16;
	static const size_t kNeighborDetectionGroupConfigurationKeyLength = 16;
	static const size_t kReceivableGroupConfigurationCount = 16;
	static const size_t kRequiredAddOnContentsSetCount = 32;

	static const int8_t kUnusedAgeRating = -1;

	static const uint64_t kBcatAlignmentMask = 0xFFFFF; // cannot have size that isn't a multiple of 1MiB
	static const uint64_t kBcatMiniumSize = 5242880; // cannot have a size (non zero) that is smaller than 5MiB
	static const uint64_t kSaveDataAlignmentMask = 0x3FFF; // cannot have a size that isn't a multiple of 16KiB

	static const uint64_t kDefaultJitMemorySize = 0x400000;
	static const uint64_t kJitMemoryMultipleSize = 0x200000;

	static const size_t kMaxAccessibleLaunchRequiredVersionApplicationIdCount = 8;

	enum class AddOnContentRegistrationType : byte_t
	{
		AllOnLaunch = 0,
		OnDemand = 1
	};

	enum class AttributeFlag : byte_t
	{
		Demo = 0,
		RetailInteractiveDisplay = 1
	};

	enum class CrashReport : byte_t
	{
		Deny = 0,
		Allow = 1
	};

	enum class CrashScreenshotForDev : byte_t
	{
		Deny = 0,
		Allow = 1
	};

	enum class CrashScreenshotForProd : byte_t
	{
		Deny = 0,
		Allow = 1
	};

	enum class DataLossConfirmation : byte_t
	{
		None = 0,
		Required = 1
	};

	enum class Hdcp : byte_t
	{
		None = 0,
		Required = 1
	};

	enum class JitConfigurationFlag : uint64_t
	{
		Enabled
	};

	enum class Language : byte_t
	{
		AmericanEnglish = 0,
		BritishEnglish = 1,
		Japanese = 2,
		French = 3,
		German = 4,
		LatinAmericanSpanish = 5,
		Spanish = 6,
		Italian = 7,
		Dutch = 8,
		CanadianFrench = 9,
		Portuguese = 10,
		Russian = 11,
		Korean = 12,
		TraditionalChinese = 13,
		SimplifiedChinese = 14,
		BrazilianPortuguese = 15
	};

	enum class LogoHandling : byte_t
	{
		Auto = 0,
		None = 1
	};

	enum class LogoType : byte_t
	{
		LicensedByNintendo = 0,
		DistributedByNintendo = 1, // Removed in SDK 3.5.2
		Nintendo = 2
	};

	enum class Organisation : byte_t
	{
		CERO = 0,
		GRACGCRB = 1,
		GSRMR = 2,
		ESRB = 3,
		ClassInd = 4,
		USK = 5,
		PEGI = 6,
		PEGIPortugal = 7,
		PEGIBBFC = 8,
		Russian = 9,
		ACB = 10,
		OFLC = 11,
		IARCGeneric = 12
	};

	enum class ParentalControlFlag : uint32_t
	{
		FreeCommunication = 0
	};

	enum class PlayLogPolicy : byte_t
	{
		Open = 0,
		LogOnly = 1,
		None = 2,
		Closed = 3,
		All = 0
	};

	enum class PlayLogQueryCapability : byte_t
	{
		None = 0,
		Whitelist = 1,
		All = 2
	};

	enum class PlayReportPermission : byte_t
	{
		None = 0,
		TargetMarketing = 1
	};

	enum class RepairFlag : byte_t
	{
		SuppressGameCardAccess = 0
	};

	enum class RequiredNetworkServiceLicenseOnLaunchFlag : byte_t
	{
		Common = 0
	};

	enum class RuntimeAddOnContentInstall : byte_t
	{
		Deny = 0,
		AllowAppend = 1,
		AllowAppendButDontDownloadWhenUsingNetwork = 2
	};

	enum class RuntimeParameterDelivery : byte_t
	{
		Always = 0,
		AlwaysIfUserStateMatched = 1,
		OnRestart = 2
	};

	enum class Screenshot : byte_t
	{
		Allow = 0,
		Deny = 1
	};

	enum class StartupUserAccount : byte_t
	{
		None = 0,
		Required = 1,
		RequiredWithNetworkServiceAccountAvailable = 2
	};

	enum class StartupUserAccountOptionFlag : byte_t
	{
		IsOptional = 0
	};

	enum class UserAccountSwitchLock : byte_t
	{
		Disable = 0,
		Enable = 1
	};

	enum class VideoCapture : byte_t
	{
		Disable = 0,
		Manual = 1,
		Enable = 2
	};
}

#pragma pack(push,1)

struct sApplicationControlProperty
{
	struct sTitle
	{
		tc::bn::string<nacp::kNameLength> name; // utf8
		tc::bn::string<nacp::kPublisherLength> publisher; // utf8
	};
	
	std::array<sTitle, nacp::kMaxLanguageCount> title;
	tc::bn::string<nacp::kIsbnLength> isbn; // utf8
	byte_t startup_user_account;
	byte_t user_account_switch_lock;
	byte_t add_on_content_registration_type; // default=1=OnDemand
	tc::bn::bitarray<sizeof(uint32_t)> attribute_flag;
	tc::bn::bitarray<sizeof(uint32_t)> supported_language_flag;
	tc::bn::bitarray<sizeof(uint32_t)> parental_control_flag;
	byte_t screenshot;
	byte_t video_capture; // default=2=Enable
	byte_t data_loss_confirmation;
	byte_t play_log_policy;
	tc::bn::le64<uint64_t> presence_group_id;
	std::array<int8_t, nacp::kRatingAgeCount> rating_age;
	tc::bn::string<nacp::kDisplayVersionLength> display_version; // utf8
	tc::bn::le64<uint64_t> add_on_content_base_id;
	tc::bn::le64<uint64_t> save_data_owner_id;
	tc::bn::le64<uint64_t> user_account_save_data_size;
	tc::bn::le64<uint64_t> user_account_save_data_journal_size;
	tc::bn::le64<uint64_t> device_save_data_size;
	tc::bn::le64<uint64_t> device_save_data_journal_size;
	tc::bn::le64<uint64_t> bcat_delivery_cache_storage_size;
	tc::bn::string<nacp::kApplicationErrorCodeCategoryLength> application_error_code_category; // utf8
	std::array<tc::bn::le64<uint64_t>, nacp::kLocalCommunicationIdCount> local_communication_id;
	byte_t logo_type;
	byte_t logo_handling;
	byte_t runtime_add_on_content_install;
	byte_t runtime_parameter_delivery;
	std::array<byte_t, 0x2> reserved_00;
	byte_t crash_report; // default=1=Allow
	byte_t hdcp;
	tc::bn::le64<uint64_t> seed_for_pseudo_device_id;
	tc::bn::string<nacp::kBcatPassphraseLength> bcat_passphrase; // utf8
	tc::bn::bitarray<sizeof(byte_t)> startup_user_account_option;
	std::array<byte_t, 0x6> reserved_for_user_account_save_data_operation;
	tc::bn::le64<uint64_t> user_account_save_data_size_max;
	tc::bn::le64<uint64_t> user_account_save_data_journal_size_max;
	tc::bn::le64<uint64_t> device_save_data_size_max;
	tc::bn::le64<uint64_t> device_save_data_journal_size_max;
	tc::bn::le64<uint64_t> temporary_storage_size;
	tc::bn::le64<uint64_t> cache_storage_size;
	tc::bn::le64<uint64_t> cache_storage_journal_size;
	tc::bn::le64<uint64_t> cache_storage_data_and_journal_size_max;
	tc::bn::le16<uint16_t> cache_storage_index_max;
	std::array<byte_t, 0x6> reserved_01; // alignment to 0x8 bytes
	std::array<tc::bn::le64<uint64_t>, nacp::kPlayLogQueryableApplicationIdCount> play_log_queryable_application_id;
	byte_t play_log_query_capability;
	tc::bn::bitarray<sizeof(byte_t)> repair_flag;
	byte_t program_index; // last byte of programId, (programId - programIndex) is used as default values for PresenceGroupId, SaveDataOwnerId, LocalCommunicationId
	tc::bn::bitarray<sizeof(byte_t)> required_network_service_license_on_launch_flag;
	std::array<byte_t, 0x4> reserved_02;
	struct sNeighborDetectionClientConfiguration
	{
		// note that group config is empty if both group_id and key are 0/nulls
		// note that group config is valid if both group_id and key are ser
		// otherwise group config is invalid
		struct sGroupConfiguration
		{
			tc::bn::le64<uint64_t> group_id;
			std::array<byte_t, nacp::kNeighborDetectionGroupConfigurationKeyLength> key;
		};

		sGroupConfiguration send_group_configuration;
		std::array<sGroupConfiguration, nacp::kReceivableGroupConfigurationCount> receivable_group_configuration;
	} neighbour_detection_client_configuration;
	struct sJitConfiguration 
	{
		tc::bn::bitarray<sizeof(uint64_t)> jit_configuration_flag;
		tc::bn::le64<uint64_t> memory_size;
	} jit_configuration;
	std::array<tc::bn::le16<uint16_t>, nacp::kRequiredAddOnContentsSetCount> required_add_on_contents_set; // this is a collection of arrays of AddOnContent Indexes (valid values: 1-2000). Bit 0-14: AddOnContentIndex, Bit 15: If set, this array continues with next value, if not set, this array ends with this value
	byte_t play_report_permission;
	byte_t crash_screenshot_for_prod;
	byte_t crash_screenshot_for_dev;
	std::array<byte_t, 0x5> reserved_03;
	struct sAccessibleLaunchRequiredVersion
	{
		std::array<tc::bn::le64<uint64_t>, nacp::kMaxAccessibleLaunchRequiredVersionApplicationIdCount> application_id;
	} accessible_launch_required_verison;
	std::array<byte_t, 3000> _pad_to_0x4000;
};
static_assert(sizeof(sApplicationControlProperty) == 0x4000, "sApplicationControlProperty size.");

#pragma pack(pop)

}} // namespace pie::hac