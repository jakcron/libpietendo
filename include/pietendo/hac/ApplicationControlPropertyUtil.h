#pragma once
#include <nn/hac/define/nacp.h>

namespace nn
{
namespace hac
{
	class ApplicationControlPropertyUtil
	{
	public:
		static bool validateSaveDataSizeMax(int64_t size, int64_t alignment);
		static bool validateSaveDataSize(int64_t size);
		static std::string getSaveDataSizeAsString(int64_t size);

		static std::string getAddOnContentRegistrationTypeAsString(nn::hac::nacp::AddOnContentRegistrationType val);
		static std::string getAttributeFlagAsString(nn::hac::nacp::AttributeFlag val);
		static std::string getCrashReportAsString(nn::hac::nacp::CrashReport val);
		static std::string getCrashScreenshotForDevAsString(nn::hac::nacp::CrashScreenshotForDev val);
		static std::string getCrashScreenshotForProdAsString(nn::hac::nacp::CrashScreenshotForProd val);
		static std::string getDataLossConfirmationAsString(nn::hac::nacp::DataLossConfirmation val);
		static std::string getHdcpAsString(nn::hac::nacp::Hdcp val);
		static std::string getJitConfigurationFlagAsString(nn::hac::nacp::JitConfigurationFlag val);
		static std::string getLanguageAsString(nn::hac::nacp::Language val);
		static std::string getLogoHandlingAsString(nn::hac::nacp::LogoHandling val);
		static std::string getLogoTypeAsString(nn::hac::nacp::LogoType val);
		static std::string getOrganisationAsString(nn::hac::nacp::Organisation val);
		static std::string getParentalControlFlagAsString(nn::hac::nacp::ParentalControlFlag val);
		static std::string getPlayLogPolicyAsString(nn::hac::nacp::PlayLogPolicy val);
		static std::string getPlayLogQueryCapabilityAsString(nn::hac::nacp::PlayLogQueryCapability val);
		static std::string getPlayReportPermissionAsString(nn::hac::nacp::PlayReportPermission val);
		static std::string getRepairFlagAsString(nn::hac::nacp::RepairFlag val);
		static std::string getRequiredNetworkServiceLicenseOnLaunchFlagAsString(nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag val);
		static std::string getRuntimeAddOnContentInstallAsString(nn::hac::nacp::RuntimeAddOnContentInstall val);
		static std::string getRuntimeParameterDeliveryAsString(nn::hac::nacp::RuntimeParameterDelivery val);
		static std::string getScreenshotAsString(nn::hac::nacp::Screenshot val);
		static std::string getStartupUserAccountAsString(nn::hac::nacp::StartupUserAccount val);
		static std::string getStartupUserAccountOptionFlagAsString(nn::hac::nacp::StartupUserAccountOptionFlag val);
		static std::string getUserAccountSwitchLockAsString(nn::hac::nacp::UserAccountSwitchLock val);
		static std::string getVideoCaptureAsString(nn::hac::nacp::VideoCapture val);
	};
}
}