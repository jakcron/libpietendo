#include <nn/hac/FileSystemAccessUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::FileSystemAccessUtil::getFsAccessFlagAsString(nn::hac::fac::FsAccessFlag flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (nn::hac::fac::FsAccessFlag::ApplicationInfo):
		ss << "ApplicationInfo";
		break;
	case (nn::hac::fac::FsAccessFlag::BootModeControl):
		ss << "BootModeControl";
		break;
	case (nn::hac::fac::FsAccessFlag::Calibration):
		ss << "Calibration";
		break;
	case (nn::hac::fac::FsAccessFlag::SystemSaveData):
		ss << "SystemSaveData";
		break;
	case (nn::hac::fac::FsAccessFlag::GameCard):
		ss << "GameCard";
		break;
	case (nn::hac::fac::FsAccessFlag::SaveDataBackUp):
		ss << "SaveDataBackUp";
		break;
	case (nn::hac::fac::FsAccessFlag::SaveDataManagement):
		ss << "SaveDataManagement";
		break;
	case (nn::hac::fac::FsAccessFlag::BisAllRaw):
		ss << "BisAllRaw";
		break;
	case (nn::hac::fac::FsAccessFlag::GameCardRaw):
		ss << "GameCardRaw";
		break;
	case (nn::hac::fac::FsAccessFlag::GameCardPrivate):
		ss << "GameCardPrivate";
		break;
	case (nn::hac::fac::FsAccessFlag::SetTime):
		ss << "SetTime";
		break;
	case (nn::hac::fac::FsAccessFlag::ContentManager):
		ss << "ContentManager";
		break;
	case (nn::hac::fac::FsAccessFlag::ImageManager):
		ss << "ImageManager";
		break;
	case (nn::hac::fac::FsAccessFlag::CreateSaveData):
		ss << "CreateSaveData";
		break;
	case (nn::hac::fac::FsAccessFlag::SystemSaveDataManagement):
		ss << "SystemSaveDataManagement";
		break;
	case (nn::hac::fac::FsAccessFlag::BisFileSystem):
		ss << "BisFileSystem";
		break;
	case (nn::hac::fac::FsAccessFlag::SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (nn::hac::fac::FsAccessFlag::SaveDataMeta):
		ss << "SaveDataMeta";
		break;
	case (nn::hac::fac::FsAccessFlag::DeviceSaveData):
		ss << "DeviceSaveData";
		break;
	case (nn::hac::fac::FsAccessFlag::SettingsControl):
		ss << "SettingsControl";
		break;
	case (nn::hac::fac::FsAccessFlag::SystemData):
		ss << "SystemData";
		break;
	case (nn::hac::fac::FsAccessFlag::SdCard):
		ss << "SdCard";
		break;
	case (nn::hac::fac::FsAccessFlag::Host):
		ss << "Host";
		break;
	case (nn::hac::fac::FsAccessFlag::FillBis):
		ss << "FillBis";
		break;
	case (nn::hac::fac::FsAccessFlag::CorruptSaveData):
		ss << "CorruptSaveData";
		break;
	case (nn::hac::fac::FsAccessFlag::SaveDataForDebug):
		ss << "SaveDataForDebug";
		break;
	case (nn::hac::fac::FsAccessFlag::FormatSdCard):
		ss << "FormatSdCard";
		break;
	case (nn::hac::fac::FsAccessFlag::GetRightsId):
		ss << "GetRightsId";
		break;
	case (nn::hac::fac::FsAccessFlag::RegisterExternalKey):
		ss << "RegisterExternalKey";
		break;
	case (nn::hac::fac::FsAccessFlag::RegisterUpdatePartition):
		ss << "RegisterUpdatePartition";
		break;
	case (nn::hac::fac::FsAccessFlag::SaveDataTransfer):
		ss << "SaveDataTransfer";
		break;
	case (nn::hac::fac::FsAccessFlag::DeviceDetection):
		ss << "DeviceDetection";
		break;
	case (nn::hac::fac::FsAccessFlag::AccessFailureResolution):
		ss << "AccessFailureResolution";
		break;
	case (nn::hac::fac::FsAccessFlag::SaveDataTransferVersion2):
		ss << "SaveDataTransferVersion2";
		break;
	case (nn::hac::fac::FsAccessFlag::RegisterProgramIndexMapInfo):
		ss << "RegisterProgramIndexMapInfo";
		break;
	case (nn::hac::fac::FsAccessFlag::CreateOwnSaveData):
		ss << "CreateOwnSaveData";
		break;
	case (nn::hac::fac::FsAccessFlag::Debug):
		ss << "Debug";
		break;
	case (nn::hac::fac::FsAccessFlag::FullPermission):
		ss << "FullPermission";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string nn::hac::FileSystemAccessUtil::getSaveDataOwnerAccessModeAsString(nn::hac::fac::SaveDataOwnerIdAccessType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::fac::SaveDataOwnerIdAccessType::Read):
		ss << "Read";
		break;
	case (nn::hac::fac::SaveDataOwnerIdAccessType::Write):
		ss << "Write";
		break;
	case (nn::hac::fac::SaveDataOwnerIdAccessType::ReadWrite):
		ss << "ReadWrite";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}