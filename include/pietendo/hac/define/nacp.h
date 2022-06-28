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

	enum AddOnContentRegistrationType : byte_t
	{
		AddOnContentRegistrationType_AllOnLaunch = 0,
		AddOnContentRegistrationType_OnDemand = 1
	};

	enum AttributeFlag : byte_t
	{
		AttributeFlag_Demo = 0,
		AttributeFlag_RetailInteractiveDisplay = 1
	};

	enum CrashReport : byte_t
	{
		CrashReport_Deny = 0,
		CrashReport_Allow = 1
	};

	enum CrashScreenshotForDev : byte_t
	{
		CrashScreenshotForDev_Deny = 0,
		CrashScreenshotForDev_Allow = 1
	};

	enum CrashScreenshotForProd : byte_t
	{
		CrashScreenshotForProd_Deny = 0,
		CrashScreenshotForProd_Allow = 1
	};

	enum DataLossConfirmation : byte_t
	{
		DataLossConfirmation_None = 0,
		DataLossConfirmation_Required = 1
	};

	enum Hdcp : byte_t
	{
		Hdcp_None = 0,
		Hdcp_Required = 1
	};

	enum JitConfigurationFlag : uint64_t
	{
		JitConfigurationFlag_Enabled = 0
	};

	enum Language : byte_t
	{
		Language_AmericanEnglish = 0,
		Language_BritishEnglish = 1,
		Language_Japanese = 2,
		Language_French = 3,
		Language_German = 4,
		Language_LatinAmericanSpanish = 5,
		Language_Spanish = 6,
		Language_Italian = 7,
		Language_Dutch = 8,
		Language_CanadianFrench = 9,
		Language_Portuguese = 10,
		Language_Russian = 11,
		Language_Korean = 12,
		Language_TraditionalChinese = 13,
		Language_SimplifiedChinese = 14,
		Language_BrazilianPortuguese = 15
	};

	enum LogoHandling : byte_t
	{
		LogoHandling_Auto = 0,
		LogoHandling_None = 1
	};

	enum LogoType : byte_t
	{
		LogoType_LicensedByNintendo = 0,
		LogoType_DistributedByNintendo = 1, // Removed in SDK 3.5.2
		LogoType_Nintendo = 2
	};

	enum Organisation : byte_t
	{
		Organisation_CERO = 0,
		Organisation_GRACGCRB = 1,
		Organisation_GSRMR = 2,
		Organisation_ESRB = 3,
		Organisation_ClassInd = 4,
		Organisation_USK = 5,
		Organisation_PEGI = 6,
		Organisation_PEGIPortugal = 7,
		Organisation_PEGIBBFC = 8,
		Organisation_Russian = 9,
		Organisation_ACB = 10,
		Organisation_OFLC = 11,
		Organisation_IARCGeneric = 12
	};

	enum ParentalControlFlag : uint32_t
	{
		ParentalControlFlag_FreeCommunication = 0
	};

	enum PlayLogPolicy : byte_t
	{
		PlayLogPolicy_Open = 0,
		PlayLogPolicy_LogOnly = 1,
		PlayLogPolicy_None = 2,
		PlayLogPolicy_Closed = 3,
		PlayLogPolicy_All = 0
	};

	enum PlayLogQueryCapability : byte_t
	{
		PlayLogQueryCapability_None = 0,
		PlayLogQueryCapability_Whitelist = 1,
		PlayLogQueryCapability_All = 2
	};

	enum PlayReportPermission : byte_t
	{
		PlayReportPermission_None = 0,
		PlayReportPermission_TargetMarketing = 1
	};

	enum RepairFlag : byte_t
	{
		RepairFlag_SuppressGameCardAccess = 0
	};

	enum RequiredNetworkServiceLicenseOnLaunchFlag : byte_t
	{
		RequiredNetworkServiceLicenseOnLaunchFlag_Common = 0
	};

	enum RuntimeAddOnContentInstall : byte_t
	{
		RuntimeAddOnContentInstall_Deny = 0,
		RuntimeAddOnContentInstall_AllowAppend = 1,
		RuntimeAddOnContentInstall_AllowAppendButDontDownloadWhenUsingNetwork = 2
	};

	enum RuntimeParameterDelivery : byte_t
	{
		RuntimeParameterDelivery_Always = 0,
		RuntimeParameterDelivery_AlwaysIfUserStateMatched = 1,
		RuntimeParameterDelivery_OnRestart = 2
	};

	enum Screenshot : byte_t
	{
		Screenshot_Allow = 0,
		Screenshot_Deny = 1
	};

	enum StartupUserAccount : byte_t
	{
		StartupUserAccount_None = 0,
		StartupUserAccount_Required = 1,
		StartupUserAccount_RequiredWithNetworkServiceAccountAvailable = 2
	};

	enum StartupUserAccountOptionFlag : byte_t
	{
		StartupUserAccountOptionFlag_IsOptional = 0
	};

	enum UserAccountSwitchLock : byte_t
	{
		UserAccountSwitchLock_Disable = 0,
		UserAccountSwitchLock_Enable = 1
	};

	enum VideoCapture : byte_t
	{
		VideoCapture_Disable = 0,
		VideoCapture_Manual = 1,
		VideoCapture_Enable = 2
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

	struct sRequiredAddOnContentEntry
	{
		uint16_t index : 15;
		uint16_t flag : 1;
	};
	static_assert(sizeof(sRequiredAddOnContentEntry) == sizeof(uint16_t), "sRequiredAddOnContentEntry size.");
	
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
	std::array<tc::bn::le16<sRequiredAddOnContentEntry>, nacp::kRequiredAddOnContentsSetCount> required_add_on_contents_set; // this is a collection of arrays of AddOnContent Indexes (valid values: 1-2000). Bit 0-14: AddOnContentIndex, Bit 15: If set, this array continues with next value, if not set, this array ends with this value
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