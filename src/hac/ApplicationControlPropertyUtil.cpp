#include <pietendo/hac/ApplicationControlPropertyUtil.h>
#include <sstream>
#include <iomanip>

bool pie::hac::ApplicationControlPropertyUtil::validateSaveDataSizeMax(int64_t size, int64_t alignment)
{
	return (alignment != 0 && (size & (alignment - 1)) != 0) == false;
}

bool pie::hac::ApplicationControlPropertyUtil::validateSaveDataSize(int64_t size)
{
	return (size & 0x3fff) == 0;
}

std::string pie::hac::ApplicationControlPropertyUtil::getSaveDataSizeAsString(int64_t size)
{
	static const int64_t kKiloByte = 1024;
	static const int64_t kMegaByte = 1024 * 1024;

	std::stringstream ss;


	if (size < kKiloByte)
	{
		ss << size << " B";
	}
	else if (size < kMegaByte)
	{
		ss << (size/kKiloByte) << " KiB";
	}
	else
	{
		ss << (size/kMegaByte) << " MiB";
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getAddOnContentRegistrationTypeAsString(pie::hac::nacp::AddOnContentRegistrationType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::AddOnContentRegistrationType_AllOnLaunch):
		ss << "AllOnLaunch";
		break;
	case (pie::hac::nacp::AddOnContentRegistrationType_OnDemand):
		ss << "OnDemand";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getAttributeFlagAsString(pie::hac::nacp::AttributeFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::AttributeFlag_Demo):
		ss << "Demo";
		break;
	case (pie::hac::nacp::AttributeFlag_RetailInteractiveDisplay):
		ss << "RetailInteractiveDisplay";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getCrashReportAsString(pie::hac::nacp::CrashReport val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::CrashReport_Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::CrashReport_Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getCrashScreenshotForDevAsString(pie::hac::nacp::CrashScreenshotForDev val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::CrashScreenshotForDev_Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::CrashScreenshotForDev_Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getCrashScreenshotForProdAsString(pie::hac::nacp::CrashScreenshotForProd val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::CrashScreenshotForProd_Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::CrashScreenshotForProd_Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getDataLossConfirmationAsString(pie::hac::nacp::DataLossConfirmation val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::DataLossConfirmation_None):
		ss << "None";
		break;
	case (pie::hac::nacp::DataLossConfirmation_Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getHdcpAsString(pie::hac::nacp::Hdcp val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::Hdcp_None):
		ss << "None";
		break;
	case (pie::hac::nacp::Hdcp_Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getJitConfigurationFlagAsString(pie::hac::nacp::JitConfigurationFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::JitConfigurationFlag_Enabled):
		ss << "Enabled";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(8) << std::setfill('0') << (uint64_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getLanguageAsString(pie::hac::nacp::Language val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::Language_AmericanEnglish):
		ss << "AmericanEnglish";
		break;
	case (pie::hac::nacp::Language_BritishEnglish):
		ss << "BritishEnglish";
		break;
	case (pie::hac::nacp::Language_Japanese):
		ss << "Japanese";
		break;
	case (pie::hac::nacp::Language_French):
		ss << "French";
		break;
	case (pie::hac::nacp::Language_German):
		ss << "German";
		break;
	case (pie::hac::nacp::Language_LatinAmericanSpanish):
		ss << "LatinAmericanSpanish";
		break;
	case (pie::hac::nacp::Language_Spanish):
		ss << "Spanish";
		break;
	case (pie::hac::nacp::Language_Italian):
		ss << "Italian";
		break;
	case (pie::hac::nacp::Language_Dutch):
		ss << "Dutch";
		break;
	case (pie::hac::nacp::Language_CanadianFrench):
		ss << "CanadianFrench";
		break;
	case (pie::hac::nacp::Language_Portuguese):
		ss << "Portuguese";
		break;
	case (pie::hac::nacp::Language_Russian):
		ss << "Russian";
		break;
	case (pie::hac::nacp::Language_Korean):
		ss << "Korean";
		break;
	case (pie::hac::nacp::Language_TraditionalChinese):
		ss << "TraditionalChinese";
		break;
	case (pie::hac::nacp::Language_SimplifiedChinese):
		ss << "SimplifiedChinese";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getLogoHandlingAsString(pie::hac::nacp::LogoHandling val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::LogoHandling_Auto):
		ss << "Auto";
		break;
	case (pie::hac::nacp::LogoHandling_None):
		ss << "None";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getLogoTypeAsString(pie::hac::nacp::LogoType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::LogoType_LicensedByNintendo):
		ss << "LicensedByNintendo";
		break;
	case (pie::hac::nacp::LogoType_DistributedByNintendo):
		ss << "DistributedByNintendo";
		break;
	case (pie::hac::nacp::LogoType_Nintendo):
		ss << "Nintendo";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getOrganisationAsString(pie::hac::nacp::Organisation val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::Organisation_CERO):
		ss << "CERO";
		break;
	case (pie::hac::nacp::Organisation_GRACGCRB):
		ss << "GRACGCRB";
		break;
	case (pie::hac::nacp::Organisation_GSRMR):
		ss << "GSRMR";
		break;
	case (pie::hac::nacp::Organisation_ESRB):
		ss << "ESRB";
		break;
	case (pie::hac::nacp::Organisation_ClassInd):
		ss << "ClassInd";
		break;
	case (pie::hac::nacp::Organisation_USK):
		ss << "USK";
		break;
	case (pie::hac::nacp::Organisation_PEGI):
		ss << "PEGI";
		break;
	case (pie::hac::nacp::Organisation_PEGIPortugal):
		ss << "PEGIPortugal";
		break;
	case (pie::hac::nacp::Organisation_PEGIBBFC):
		ss << "PEGIBBFC";
		break;
	case (pie::hac::nacp::Organisation_Russian):
		ss << "Russian";
		break;
	case (pie::hac::nacp::Organisation_ACB):
		ss << "ACB";
		break;
	case (pie::hac::nacp::Organisation_OFLC):
		ss << "OFLC";
		break;
	case (pie::hac::nacp::Organisation_IARCGeneric):
		ss << "IARCGeneric";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getParentalControlFlagAsString(pie::hac::nacp::ParentalControlFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::ParentalControlFlag_FreeCommunication):
		ss << "FreeCommunication";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getPlayLogPolicyAsString(pie::hac::nacp::PlayLogPolicy val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::PlayLogPolicy_Open):
		ss << "Open";
		break;
	case (pie::hac::nacp::PlayLogPolicy_LogOnly):
		ss << "LogOnly";
		break;
	case (pie::hac::nacp::PlayLogPolicy_None):
		ss << "None";
		break;
	case (pie::hac::nacp::PlayLogPolicy_Closed):
		ss << "Closed";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getPlayLogQueryCapabilityAsString(pie::hac::nacp::PlayLogQueryCapability val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::PlayLogQueryCapability_None):
		ss << "None";
		break;
	case (pie::hac::nacp::PlayLogQueryCapability_Whitelist):
		ss << "Whitelist";
		break;
	case (pie::hac::nacp::PlayLogQueryCapability_All):
		ss << "All";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getPlayReportPermissionAsString(pie::hac::nacp::PlayReportPermission val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::PlayReportPermission_None):
		ss << "None";
		break;
	case (pie::hac::nacp::PlayReportPermission_TargetMarketing):
		ss << "TargetMarketing";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getRepairFlagAsString(pie::hac::nacp::RepairFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::RepairFlag_SuppressGameCardAccess):
		ss << "SuppressGameCardAccess";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getRequiredNetworkServiceLicenseOnLaunchFlagAsString(pie::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag_Common):
		ss << "Common";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getRuntimeAddOnContentInstallAsString(pie::hac::nacp::RuntimeAddOnContentInstall val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::RuntimeAddOnContentInstall_Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::RuntimeAddOnContentInstall_AllowAppend):
		ss << "AllowAppend";
		break;
	case (pie::hac::nacp::RuntimeAddOnContentInstall_AllowAppendButDontDownloadWhenUsingNetwork):
		ss << "AllowAppendButDontDownloadWhenUsingNetwork";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getRuntimeParameterDeliveryAsString(pie::hac::nacp::RuntimeParameterDelivery val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::RuntimeParameterDelivery_Always):
		ss << "Always";
		break;
	case (pie::hac::nacp::RuntimeParameterDelivery_AlwaysIfUserStateMatched):
		ss << "AlwaysIfUserStateMatched";
		break;
	case (pie::hac::nacp::RuntimeParameterDelivery_OnRestart):
		ss << "OnRestart";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getScreenshotAsString(pie::hac::nacp::Screenshot val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::Screenshot_Allow):
		ss << "Allow";
		break;
	case (pie::hac::nacp::Screenshot_Deny):
		ss << "Deny";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getStartupUserAccountAsString(pie::hac::nacp::StartupUserAccount val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::StartupUserAccount_None):
		ss << "None";
		break;
	case (pie::hac::nacp::StartupUserAccount_Required):
		ss << "Required";
		break;
	case (pie::hac::nacp::StartupUserAccount_RequiredWithNetworkServiceAccountAvailable):
		ss << "RequiredWithNetworkServiceAccountAvailable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getStartupUserAccountOptionFlagAsString(pie::hac::nacp::StartupUserAccountOptionFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::StartupUserAccountOptionFlag_IsOptional):
		ss << "IsOptional";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getUserAccountSwitchLockAsString(pie::hac::nacp::UserAccountSwitchLock val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::UserAccountSwitchLock_Disable):
		ss << "Disable";
		break;
	case (pie::hac::nacp::UserAccountSwitchLock_Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ApplicationControlPropertyUtil::getVideoCaptureAsString(pie::hac::nacp::VideoCapture val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::nacp::VideoCapture_Disable):
		ss << "Disable";
		break;
	case (pie::hac::nacp::VideoCapture_Manual):
		ss << "Manual";
		break;
	case (pie::hac::nacp::VideoCapture_Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}