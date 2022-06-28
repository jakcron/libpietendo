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
	case (pie::hac::nacp::AddOnContentRegistrationType::AllOnLaunch):
		ss << "AllOnLaunch";
		break;
	case (pie::hac::nacp::AddOnContentRegistrationType::OnDemand):
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
	case (pie::hac::nacp::AttributeFlag::Demo):
		ss << "Demo";
		break;
	case (pie::hac::nacp::AttributeFlag::RetailInteractiveDisplay):
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
	case (pie::hac::nacp::CrashReport::Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::CrashReport::Allow):
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
	case (pie::hac::nacp::CrashScreenshotForDev::Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::CrashScreenshotForDev::Allow):
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
	case (pie::hac::nacp::CrashScreenshotForProd::Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::CrashScreenshotForProd::Allow):
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
	case (pie::hac::nacp::DataLossConfirmation::None):
		ss << "None";
		break;
	case (pie::hac::nacp::DataLossConfirmation::Required):
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
	case (pie::hac::nacp::Hdcp::None):
		ss << "None";
		break;
	case (pie::hac::nacp::Hdcp::Required):
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
	case (pie::hac::nacp::JitConfigurationFlag::Enabled):
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
	case (pie::hac::nacp::Language::AmericanEnglish):
		ss << "AmericanEnglish";
		break;
	case (pie::hac::nacp::Language::BritishEnglish):
		ss << "BritishEnglish";
		break;
	case (pie::hac::nacp::Language::Japanese):
		ss << "Japanese";
		break;
	case (pie::hac::nacp::Language::French):
		ss << "French";
		break;
	case (pie::hac::nacp::Language::German):
		ss << "German";
		break;
	case (pie::hac::nacp::Language::LatinAmericanSpanish):
		ss << "LatinAmericanSpanish";
		break;
	case (pie::hac::nacp::Language::Spanish):
		ss << "Spanish";
		break;
	case (pie::hac::nacp::Language::Italian):
		ss << "Italian";
		break;
	case (pie::hac::nacp::Language::Dutch):
		ss << "Dutch";
		break;
	case (pie::hac::nacp::Language::CanadianFrench):
		ss << "CanadianFrench";
		break;
	case (pie::hac::nacp::Language::Portuguese):
		ss << "Portuguese";
		break;
	case (pie::hac::nacp::Language::Russian):
		ss << "Russian";
		break;
	case (pie::hac::nacp::Language::Korean):
		ss << "Korean";
		break;
	case (pie::hac::nacp::Language::TraditionalChinese):
		ss << "TraditionalChinese";
		break;
	case (pie::hac::nacp::Language::SimplifiedChinese):
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
	case (pie::hac::nacp::LogoHandling::Auto):
		ss << "Auto";
		break;
	case (pie::hac::nacp::LogoHandling::None):
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
	case (pie::hac::nacp::LogoType::LicensedByNintendo):
		ss << "LicensedByNintendo";
		break;
	case (pie::hac::nacp::LogoType::DistributedByNintendo):
		ss << "DistributedByNintendo";
		break;
	case (pie::hac::nacp::LogoType::Nintendo):
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
	case (pie::hac::nacp::Organisation::CERO):
		ss << "CERO";
		break;
	case (pie::hac::nacp::Organisation::GRACGCRB):
		ss << "GRACGCRB";
		break;
	case (pie::hac::nacp::Organisation::GSRMR):
		ss << "GSRMR";
		break;
	case (pie::hac::nacp::Organisation::ESRB):
		ss << "ESRB";
		break;
	case (pie::hac::nacp::Organisation::ClassInd):
		ss << "ClassInd";
		break;
	case (pie::hac::nacp::Organisation::USK):
		ss << "USK";
		break;
	case (pie::hac::nacp::Organisation::PEGI):
		ss << "PEGI";
		break;
	case (pie::hac::nacp::Organisation::PEGIPortugal):
		ss << "PEGIPortugal";
		break;
	case (pie::hac::nacp::Organisation::PEGIBBFC):
		ss << "PEGIBBFC";
		break;
	case (pie::hac::nacp::Organisation::Russian):
		ss << "Russian";
		break;
	case (pie::hac::nacp::Organisation::ACB):
		ss << "ACB";
		break;
	case (pie::hac::nacp::Organisation::OFLC):
		ss << "OFLC";
		break;
	case (pie::hac::nacp::Organisation::IARCGeneric):
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
	case (pie::hac::nacp::ParentalControlFlag::FreeCommunication):
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
	case (pie::hac::nacp::PlayLogPolicy::Open):
		ss << "Open";
		break;
	case (pie::hac::nacp::PlayLogPolicy::LogOnly):
		ss << "LogOnly";
		break;
	case (pie::hac::nacp::PlayLogPolicy::None):
		ss << "None";
		break;
	case (pie::hac::nacp::PlayLogPolicy::Closed):
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
	case (pie::hac::nacp::PlayLogQueryCapability::None):
		ss << "None";
		break;
	case (pie::hac::nacp::PlayLogQueryCapability::Whitelist):
		ss << "Whitelist";
		break;
	case (pie::hac::nacp::PlayLogQueryCapability::All):
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
	case (pie::hac::nacp::PlayReportPermission::None):
		ss << "None";
		break;
	case (pie::hac::nacp::PlayReportPermission::TargetMarketing):
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
	case (pie::hac::nacp::RepairFlag::SuppressGameCardAccess):
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
	case (pie::hac::nacp::RequiredNetworkServiceLicenseOnLaunchFlag::Common):
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
	case (pie::hac::nacp::RuntimeAddOnContentInstall::Deny):
		ss << "Deny";
		break;
	case (pie::hac::nacp::RuntimeAddOnContentInstall::AllowAppend):
		ss << "AllowAppend";
		break;
	case (pie::hac::nacp::RuntimeAddOnContentInstall::AllowAppendButDontDownloadWhenUsingNetwork):
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
	case (pie::hac::nacp::RuntimeParameterDelivery::Always):
		ss << "Always";
		break;
	case (pie::hac::nacp::RuntimeParameterDelivery::AlwaysIfUserStateMatched):
		ss << "AlwaysIfUserStateMatched";
		break;
	case (pie::hac::nacp::RuntimeParameterDelivery::OnRestart):
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
	case (pie::hac::nacp::Screenshot::Allow):
		ss << "Allow";
		break;
	case (pie::hac::nacp::Screenshot::Deny):
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
	case (pie::hac::nacp::StartupUserAccount::None):
		ss << "None";
		break;
	case (pie::hac::nacp::StartupUserAccount::Required):
		ss << "Required";
		break;
	case (pie::hac::nacp::StartupUserAccount::RequiredWithNetworkServiceAccountAvailable):
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
	case (pie::hac::nacp::StartupUserAccountOptionFlag::IsOptional):
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
	case (pie::hac::nacp::UserAccountSwitchLock::Disable):
		ss << "Disable";
		break;
	case (pie::hac::nacp::UserAccountSwitchLock::Enable):
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
	case (pie::hac::nacp::VideoCapture::Disable):
		ss << "Disable";
		break;
	case (pie::hac::nacp::VideoCapture::Manual):
		ss << "Manual";
		break;
	case (pie::hac::nacp::VideoCapture::Enable):
		ss << "Enable";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}