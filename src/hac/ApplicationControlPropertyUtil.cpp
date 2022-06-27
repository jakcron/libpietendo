#include <nn/hac/ApplicationControlPropertyUtil.h>
#include <sstream>
#include <iomanip>

bool nn::hac::ApplicationControlPropertyUtil::validateSaveDataSizeMax(int64_t size, int64_t alignment)
{
	return (alignment != 0 && (size & (alignment - 1)) != 0) == false;
}

bool nn::hac::ApplicationControlPropertyUtil::validateSaveDataSize(int64_t size)
{
	return (size & 0x3fff) == 0;
}

std::string nn::hac::ApplicationControlPropertyUtil::getSaveDataSizeAsString(int64_t size)
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

std::string nn::hac::ApplicationControlPropertyUtil::getAddOnContentRegistrationTypeAsString(nn::hac::nacp::AddOnContentRegistrationType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::AddOnContentRegistrationType::AllOnLaunch):
		ss << "AllOnLaunch";
		break;
	case (nn::hac::nacp::AddOnContentRegistrationType::OnDemand):
		ss << "OnDemand";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getAttributeFlagAsString(nn::hac::nacp::AttributeFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::AttributeFlag::Demo):
		ss << "Demo";
		break;
	case (nn::hac::nacp::AttributeFlag::RetailInteractiveDisplay):
		ss << "RetailInteractiveDisplay";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getCrashReportAsString(nn::hac::nacp::CrashReport val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::CrashReport::Deny):
		ss << "Deny";
		break;
	case (nn::hac::nacp::CrashReport::Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getCrashScreenshotForDevAsString(nn::hac::nacp::CrashScreenshotForDev val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::CrashScreenshotForDev::Deny):
		ss << "Deny";
		break;
	case (nn::hac::nacp::CrashScreenshotForDev::Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getCrashScreenshotForProdAsString(nn::hac::nacp::CrashScreenshotForProd val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::CrashScreenshotForProd::Deny):
		ss << "Deny";
		break;
	case (nn::hac::nacp::CrashScreenshotForProd::Allow):
		ss << "Allow";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getDataLossConfirmationAsString(nn::hac::nacp::DataLossConfirmation val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::DataLossConfirmation::None):
		ss << "None";
		break;
	case (nn::hac::nacp::DataLossConfirmation::Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getHdcpAsString(nn::hac::nacp::Hdcp val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::Hdcp::None):
		ss << "None";
		break;
	case (nn::hac::nacp::Hdcp::Required):
		ss << "Required";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getJitConfigurationFlagAsString(nn::hac::nacp::JitConfigurationFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::JitConfigurationFlag::Enabled):
		ss << "Enabled";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(8) << std::setfill('0') << (uint64_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getLanguageAsString(nn::hac::nacp::Language val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::Language::AmericanEnglish):
		ss << "AmericanEnglish";
		break;
	case (nn::hac::nacp::Language::BritishEnglish):
		ss << "BritishEnglish";
		break;
	case (nn::hac::nacp::Language::Japanese):
		ss << "Japanese";
		break;
	case (nn::hac::nacp::Language::French):
		ss << "French";
		break;
	case (nn::hac::nacp::Language::German):
		ss << "German";
		break;
	case (nn::hac::nacp::Language::LatinAmericanSpanish):
		ss << "LatinAmericanSpanish";
		break;
	case (nn::hac::nacp::Language::Spanish):
		ss << "Spanish";
		break;
	case (nn::hac::nacp::Language::Italian):
		ss << "Italian";
		break;
	case (nn::hac::nacp::Language::Dutch):
		ss << "Dutch";
		break;
	case (nn::hac::nacp::Language::CanadianFrench):
		ss << "CanadianFrench";
		break;
	case (nn::hac::nacp::Language::Portuguese):
		ss << "Portuguese";
		break;
	case (nn::hac::nacp::Language::Russian):
		ss << "Russian";
		break;
	case (nn::hac::nacp::Language::Korean):
		ss << "Korean";
		break;
	case (nn::hac::nacp::Language::TraditionalChinese):
		ss << "TraditionalChinese";
		break;
	case (nn::hac::nacp::Language::SimplifiedChinese):
		ss << "SimplifiedChinese";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getLogoHandlingAsString(nn::hac::nacp::LogoHandling val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::LogoHandling::Auto):
		ss << "Auto";
		break;
	case (nn::hac::nacp::LogoHandling::None):
		ss << "None";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getLogoTypeAsString(nn::hac::nacp::LogoType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::LogoType::LicensedByNintendo):
		ss << "LicensedByNintendo";
		break;
	case (nn::hac::nacp::LogoType::DistributedByNintendo):
		ss << "DistributedByNintendo";
		break;
	case (nn::hac::nacp::LogoType::Nintendo):
		ss << "Nintendo";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getOrganisationAsString(nn::hac::nacp::Organisation val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::Organisation::CERO):
		ss << "CERO";
		break;
	case (nn::hac::nacp::Organisation::GRACGCRB):
		ss << "GRACGCRB";
		break;
	case (nn::hac::nacp::Organisation::GSRMR):
		ss << "GSRMR";
		break;
	case (nn::hac::nacp::Organisation::ESRB):
		ss << "ESRB";
		break;
	case (nn::hac::nacp::Organisation::ClassInd):
		ss << "ClassInd";
		break;
	case (nn::hac::nacp::Organisation::USK):
		ss << "USK";
		break;
	case (nn::hac::nacp::Organisation::PEGI):
		ss << "PEGI";
		break;
	case (nn::hac::nacp::Organisation::PEGIPortugal):
		ss << "PEGIPortugal";
		break;
	case (nn::hac::nacp::Organisation::PEGIBBFC):
		ss << "PEGIBBFC";
		break;
	case (nn::hac::nacp::Organisation::Russian):
		ss << "Russian";
		break;
	case (nn::hac::nacp::Organisation::ACB):
		ss << "ACB";
		break;
	case (nn::hac::nacp::Organisation::OFLC):
		ss << "OFLC";
		break;
	case (nn::hac::nacp::Organisation::IARCGeneric):
		ss << "IARCGeneric";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getParentalControlFlagAsString(nn::hac::nacp::ParentalControlFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::ParentalControlFlag::FreeCommunication):
		ss << "FreeCommunication";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getPlayLogPolicyAsString(nn::hac::nacp::PlayLogPolicy val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::PlayLogPolicy::Open):
		ss << "Open";
		break;
	case (nn::hac::nacp::PlayLogPolicy::LogOnly):
		ss << "LogOnly";
		break;
	case (nn::hac::nacp::PlayLogPolicy::None):
		ss << "None";
		break;
	case (nn::hac::nacp::PlayLogPolicy::Closed):
		ss << "Closed";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getPlayLogQueryCapabilityAsString(nn::hac::nacp::PlayLogQueryCapability val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::PlayLogQueryCapability::None):
		ss << "None";
		break;
	case (nn::hac::nacp::PlayLogQueryCapability::Whitelist):
		ss << "Whitelist";
		break;
	case (nn::hac::nacp::PlayLogQueryCapability::All):
		ss << "All";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getPlayReportPermissionAsString(nn::hac::nacp::PlayReportPermission val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::PlayReportPermission::None):
		ss << "None";
		break;
	case (nn::hac::nacp::PlayReportPermission::TargetMarketing):
		ss << "TargetMarketing";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRepairFlagAsString(nn::hac::nacp::RepairFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::RepairFlag::SuppressGameCardAccess):
		ss << "SuppressGameCardAccess";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRequiredNetworkServiceLicenseOnLaunchFlagAsString(nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag::Common):
		ss << "Common";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRuntimeAddOnContentInstallAsString(nn::hac::nacp::RuntimeAddOnContentInstall val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::RuntimeAddOnContentInstall::Deny):
		ss << "Deny";
		break;
	case (nn::hac::nacp::RuntimeAddOnContentInstall::AllowAppend):
		ss << "AllowAppend";
		break;
	case (nn::hac::nacp::RuntimeAddOnContentInstall::AllowAppendButDontDownloadWhenUsingNetwork):
		ss << "AllowAppendButDontDownloadWhenUsingNetwork";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getRuntimeParameterDeliveryAsString(nn::hac::nacp::RuntimeParameterDelivery val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::RuntimeParameterDelivery::Always):
		ss << "Always";
		break;
	case (nn::hac::nacp::RuntimeParameterDelivery::AlwaysIfUserStateMatched):
		ss << "AlwaysIfUserStateMatched";
		break;
	case (nn::hac::nacp::RuntimeParameterDelivery::OnRestart):
		ss << "OnRestart";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getScreenshotAsString(nn::hac::nacp::Screenshot val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::Screenshot::Allow):
		ss << "Allow";
		break;
	case (nn::hac::nacp::Screenshot::Deny):
		ss << "Deny";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getStartupUserAccountAsString(nn::hac::nacp::StartupUserAccount val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::StartupUserAccount::None):
		ss << "None";
		break;
	case (nn::hac::nacp::StartupUserAccount::Required):
		ss << "Required";
		break;
	case (nn::hac::nacp::StartupUserAccount::RequiredWithNetworkServiceAccountAvailable):
		ss << "RequiredWithNetworkServiceAccountAvailable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getStartupUserAccountOptionFlagAsString(nn::hac::nacp::StartupUserAccountOptionFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::StartupUserAccountOptionFlag::IsOptional):
		ss << "IsOptional";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getUserAccountSwitchLockAsString(nn::hac::nacp::UserAccountSwitchLock val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::UserAccountSwitchLock::Disable):
		ss << "Disable";
		break;
	case (nn::hac::nacp::UserAccountSwitchLock::Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ApplicationControlPropertyUtil::getVideoCaptureAsString(nn::hac::nacp::VideoCapture val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nacp::VideoCapture::Disable):
		ss << "Disable";
		break;
	case (nn::hac::nacp::VideoCapture::Manual):
		ss << "Manual";
		break;
	case (nn::hac::nacp::VideoCapture::Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}