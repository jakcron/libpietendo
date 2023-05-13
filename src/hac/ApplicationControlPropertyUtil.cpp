#include <pietendo/hac/ApplicationControlPropertyUtil.h>
#include <fmt/format.h>

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

	std::string str;


	if (size < kKiloByte)
	{
		str = fmt::format("{:d} B", size);
	}
	else if (size < kMegaByte)
	{
		str = fmt::format("{:d} KiB", (size/kKiloByte));
	}
	else
	{
		str = fmt::format("{:d} MiB", (size/kMegaByte));
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getAddOnContentRegistrationTypeAsString(pie::hac::nacp::AddOnContentRegistrationType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::AddOnContentRegistrationType_AllOnLaunch):
		str = "AllOnLaunch";
		break;
	case (pie::hac::nacp::AddOnContentRegistrationType_OnDemand):
		str = "OnDemand";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getAttributeFlagAsString(pie::hac::nacp::AttributeFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::AttributeFlag_Demo):
		str = "Demo";
		break;
	case (pie::hac::nacp::AttributeFlag_RetailInteractiveDisplay):
		str = "RetailInteractiveDisplay";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getCrashReportAsString(pie::hac::nacp::CrashReport val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::CrashReport_Deny):
		str = "Deny";
		break;
	case (pie::hac::nacp::CrashReport_Allow):
		str = "Allow";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getCrashScreenshotForDevAsString(pie::hac::nacp::CrashScreenshotForDev val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::CrashScreenshotForDev_Deny):
		str = "Deny";
		break;
	case (pie::hac::nacp::CrashScreenshotForDev_Allow):
		str = "Allow";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getCrashScreenshotForProdAsString(pie::hac::nacp::CrashScreenshotForProd val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::CrashScreenshotForProd_Deny):
		str = "Deny";
		break;
	case (pie::hac::nacp::CrashScreenshotForProd_Allow):
		str = "Allow";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getDataLossConfirmationAsString(pie::hac::nacp::DataLossConfirmation val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::DataLossConfirmation_None):
		str = "None";
		break;
	case (pie::hac::nacp::DataLossConfirmation_Required):
		str = "Required";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getHdcpAsString(pie::hac::nacp::Hdcp val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::Hdcp_None):
		str = "None";
		break;
	case (pie::hac::nacp::Hdcp_Required):
		str = "Required";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getJitConfigurationFlagAsString(pie::hac::nacp::JitConfigurationFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::JitConfigurationFlag_Enabled):
		str = "Enabled";
		break;
	default:
		str = fmt::format("unk_0x{:08x}", (uint64_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getLanguageAsString(pie::hac::nacp::Language val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::Language_AmericanEnglish):
		str = "AmericanEnglish";
		break;
	case (pie::hac::nacp::Language_BritishEnglish):
		str = "BritishEnglish";
		break;
	case (pie::hac::nacp::Language_Japanese):
		str = "Japanese";
		break;
	case (pie::hac::nacp::Language_French):
		str = "French";
		break;
	case (pie::hac::nacp::Language_German):
		str = "German";
		break;
	case (pie::hac::nacp::Language_LatinAmericanSpanish):
		str = "LatinAmericanSpanish";
		break;
	case (pie::hac::nacp::Language_Spanish):
		str = "Spanish";
		break;
	case (pie::hac::nacp::Language_Italian):
		str = "Italian";
		break;
	case (pie::hac::nacp::Language_Dutch):
		str = "Dutch";
		break;
	case (pie::hac::nacp::Language_CanadianFrench):
		str = "CanadianFrench";
		break;
	case (pie::hac::nacp::Language_Portuguese):
		str = "Portuguese";
		break;
	case (pie::hac::nacp::Language_Russian):
		str = "Russian";
		break;
	case (pie::hac::nacp::Language_Korean):
		str = "Korean";
		break;
	case (pie::hac::nacp::Language_TraditionalChinese):
		str = "TraditionalChinese";
		break;
	case (pie::hac::nacp::Language_SimplifiedChinese):
		str = "SimplifiedChinese";
		break;
	case (pie::hac::nacp::Language_BrazilianPortuguese):
		str = "BrazilianPortuguese";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getLogoHandlingAsString(pie::hac::nacp::LogoHandling val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::LogoHandling_Auto):
		str = "Auto";
		break;
	case (pie::hac::nacp::LogoHandling_None):
		str = "None";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getLogoTypeAsString(pie::hac::nacp::LogoType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::LogoType_LicensedByNintendo):
		str = "LicensedByNintendo";
		break;
	case (pie::hac::nacp::LogoType_DistributedByNintendo):
		str = "DistributedByNintendo";
		break;
	case (pie::hac::nacp::LogoType_Nintendo):
		str = "Nintendo";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getOrganisationAsString(pie::hac::nacp::Organisation val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::Organisation_CERO):
		str = "CERO";
		break;
	case (pie::hac::nacp::Organisation_GRACGCRB):
		str = "GRACGCRB";
		break;
	case (pie::hac::nacp::Organisation_GSRMR):
		str = "GSRMR";
		break;
	case (pie::hac::nacp::Organisation_ESRB):
		str = "ESRB";
		break;
	case (pie::hac::nacp::Organisation_ClassInd):
		str = "ClassInd";
		break;
	case (pie::hac::nacp::Organisation_USK):
		str = "USK";
		break;
	case (pie::hac::nacp::Organisation_PEGI):
		str = "PEGI";
		break;
	case (pie::hac::nacp::Organisation_PEGIPortugal):
		str = "PEGIPortugal";
		break;
	case (pie::hac::nacp::Organisation_PEGIBBFC):
		str = "PEGIBBFC";
		break;
	case (pie::hac::nacp::Organisation_Russian):
		str = "Russian";
		break;
	case (pie::hac::nacp::Organisation_ACB):
		str = "ACB";
		break;
	case (pie::hac::nacp::Organisation_OFLC):
		str = "OFLC";
		break;
	case (pie::hac::nacp::Organisation_IARCGeneric):
		str = "IARCGeneric";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getParentalControlFlagAsString(pie::hac::nacp::ParentalControlFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::ParentalControlFlag_FreeCommunication):
		str = "FreeCommunication";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getPlayLogPolicyAsString(pie::hac::nacp::PlayLogPolicy val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::PlayLogPolicy_Open):
		str = "Open";
		break;
	case (pie::hac::nacp::PlayLogPolicy_LogOnly):
		str = "LogOnly";
		break;
	case (pie::hac::nacp::PlayLogPolicy_None):
		str = "None";
		break;
	case (pie::hac::nacp::PlayLogPolicy_Closed):
		str = "Closed";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getPlayLogQueryCapabilityAsString(pie::hac::nacp::PlayLogQueryCapability val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::PlayLogQueryCapability_None):
		str = "None";
		break;
	case (pie::hac::nacp::PlayLogQueryCapability_Whitelist):
		str = "Whitelist";
		break;
	case (pie::hac::nacp::PlayLogQueryCapability_All):
		str = "All";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getPlayReportPermissionAsString(pie::hac::nacp::PlayReportPermission val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::PlayReportPermission_None):
		str = "None";
		break;
	case (pie::hac::nacp::PlayReportPermission_TargetMarketing):
		str = "TargetMarketing";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getRepairFlagAsString(pie::hac::nacp::RepairFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::RepairFlag_SuppressGameCardAccess):
		str = "SuppressGameCardAccess";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getRequiredNetworkServiceLicenseOnLaunchFlagAsString(pie::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag_Common):
		str = "Common";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getRuntimeAddOnContentInstallAsString(pie::hac::nacp::RuntimeAddOnContentInstall val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::RuntimeAddOnContentInstall_Deny):
		str = "Deny";
		break;
	case (pie::hac::nacp::RuntimeAddOnContentInstall_AllowAppend):
		str = "AllowAppend";
		break;
	case (pie::hac::nacp::RuntimeAddOnContentInstall_AllowAppendButDontDownloadWhenUsingNetwork):
		str = "AllowAppendButDontDownloadWhenUsingNetwork";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getRuntimeParameterDeliveryAsString(pie::hac::nacp::RuntimeParameterDelivery val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::RuntimeParameterDelivery_Always):
		str = "Always";
		break;
	case (pie::hac::nacp::RuntimeParameterDelivery_AlwaysIfUserStateMatched):
		str = "AlwaysIfUserStateMatched";
		break;
	case (pie::hac::nacp::RuntimeParameterDelivery_OnRestart):
		str = "OnRestart";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getScreenshotAsString(pie::hac::nacp::Screenshot val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::Screenshot_Allow):
		str = "Allow";
		break;
	case (pie::hac::nacp::Screenshot_Deny):
		str = "Deny";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getStartupUserAccountAsString(pie::hac::nacp::StartupUserAccount val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::StartupUserAccount_None):
		str = "None";
		break;
	case (pie::hac::nacp::StartupUserAccount_Required):
		str = "Required";
		break;
	case (pie::hac::nacp::StartupUserAccount_RequiredWithNetworkServiceAccountAvailable):
		str = "RequiredWithNetworkServiceAccountAvailable";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getStartupUserAccountOptionFlagAsString(pie::hac::nacp::StartupUserAccountOptionFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::StartupUserAccountOptionFlag_IsOptional):
		str = "IsOptional";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getUserAccountSwitchLockAsString(pie::hac::nacp::UserAccountSwitchLock val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::UserAccountSwitchLock_Disable):
		str = "Disable";
		break;
	case (pie::hac::nacp::UserAccountSwitchLock_Enable):
		str = "Enable";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ApplicationControlPropertyUtil::getVideoCaptureAsString(pie::hac::nacp::VideoCapture val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nacp::VideoCapture_Disable):
		str = "Disable";
		break;
	case (pie::hac::nacp::VideoCapture_Manual):
		str = "Manual";
		break;
	case (pie::hac::nacp::VideoCapture_Enable):
		str = "Enable";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}