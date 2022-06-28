	/**
	 * @file ApplicationControlPropertyUtil.h
	 * @brief Declaration of pie::hac::ApplicationControlPropertyUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/nacp.h>

namespace pie { namespace hac {
	
class ApplicationControlPropertyUtil
{
public:
	static bool validateSaveDataSizeMax(int64_t size, int64_t alignment);
	static bool validateSaveDataSize(int64_t size);
	static std::string getSaveDataSizeAsString(int64_t size);

	static std::string getAddOnContentRegistrationTypeAsString(pie::hac::nacp::AddOnContentRegistrationType val);
	static std::string getAttributeFlagAsString(pie::hac::nacp::AttributeFlag val);
	static std::string getCrashReportAsString(pie::hac::nacp::CrashReport val);
	static std::string getCrashScreenshotForDevAsString(pie::hac::nacp::CrashScreenshotForDev val);
	static std::string getCrashScreenshotForProdAsString(pie::hac::nacp::CrashScreenshotForProd val);
	static std::string getDataLossConfirmationAsString(pie::hac::nacp::DataLossConfirmation val);
	static std::string getHdcpAsString(pie::hac::nacp::Hdcp val);
	static std::string getJitConfigurationFlagAsString(pie::hac::nacp::JitConfigurationFlag val);
	static std::string getLanguageAsString(pie::hac::nacp::Language val);
	static std::string getLogoHandlingAsString(pie::hac::nacp::LogoHandling val);
	static std::string getLogoTypeAsString(pie::hac::nacp::LogoType val);
	static std::string getOrganisationAsString(pie::hac::nacp::Organisation val);
	static std::string getParentalControlFlagAsString(pie::hac::nacp::ParentalControlFlag val);
	static std::string getPlayLogPolicyAsString(pie::hac::nacp::PlayLogPolicy val);
	static std::string getPlayLogQueryCapabilityAsString(pie::hac::nacp::PlayLogQueryCapability val);
	static std::string getPlayReportPermissionAsString(pie::hac::nacp::PlayReportPermission val);
	static std::string getRepairFlagAsString(pie::hac::nacp::RepairFlag val);
	static std::string getRequiredNetworkServiceLicenseOnLaunchFlagAsString(pie::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag val);
	static std::string getRuntimeAddOnContentInstallAsString(pie::hac::nacp::RuntimeAddOnContentInstall val);
	static std::string getRuntimeParameterDeliveryAsString(pie::hac::nacp::RuntimeParameterDelivery val);
	static std::string getScreenshotAsString(pie::hac::nacp::Screenshot val);
	static std::string getStartupUserAccountAsString(pie::hac::nacp::StartupUserAccount val);
	static std::string getStartupUserAccountOptionFlagAsString(pie::hac::nacp::StartupUserAccountOptionFlag val);
	static std::string getUserAccountSwitchLockAsString(pie::hac::nacp::UserAccountSwitchLock val);
	static std::string getVideoCaptureAsString(pie::hac::nacp::VideoCapture val);
};

}} // namespace pie::hac