#include <pietendo/hac/FileSystemAccessUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::FileSystemAccessUtil::getFsAccessFlagAsString(pie::hac::fac::FsAccessFlag flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (pie::hac::fac::FsAccessFlag::ApplicationInfo):
		ss << "ApplicationInfo";
		break;
	case (pie::hac::fac::FsAccessFlag::BootModeControl):
		ss << "BootModeControl";
		break;
	case (pie::hac::fac::FsAccessFlag::Calibration):
		ss << "Calibration";
		break;
	case (pie::hac::fac::FsAccessFlag::SystemSaveData):
		ss << "SystemSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag::GameCard):
		ss << "GameCard";
		break;
	case (pie::hac::fac::FsAccessFlag::SaveDataBackUp):
		ss << "SaveDataBackUp";
		break;
	case (pie::hac::fac::FsAccessFlag::SaveDataManagement):
		ss << "SaveDataManagement";
		break;
	case (pie::hac::fac::FsAccessFlag::BisAllRaw):
		ss << "BisAllRaw";
		break;
	case (pie::hac::fac::FsAccessFlag::GameCardRaw):
		ss << "GameCardRaw";
		break;
	case (pie::hac::fac::FsAccessFlag::GameCardPrivate):
		ss << "GameCardPrivate";
		break;
	case (pie::hac::fac::FsAccessFlag::SetTime):
		ss << "SetTime";
		break;
	case (pie::hac::fac::FsAccessFlag::ContentManager):
		ss << "ContentManager";
		break;
	case (pie::hac::fac::FsAccessFlag::ImageManager):
		ss << "ImageManager";
		break;
	case (pie::hac::fac::FsAccessFlag::CreateSaveData):
		ss << "CreateSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag::SystemSaveDataManagement):
		ss << "SystemSaveDataManagement";
		break;
	case (pie::hac::fac::FsAccessFlag::BisFileSystem):
		ss << "BisFileSystem";
		break;
	case (pie::hac::fac::FsAccessFlag::SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (pie::hac::fac::FsAccessFlag::SaveDataMeta):
		ss << "SaveDataMeta";
		break;
	case (pie::hac::fac::FsAccessFlag::DeviceSaveData):
		ss << "DeviceSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag::SettingsControl):
		ss << "SettingsControl";
		break;
	case (pie::hac::fac::FsAccessFlag::SystemData):
		ss << "SystemData";
		break;
	case (pie::hac::fac::FsAccessFlag::SdCard):
		ss << "SdCard";
		break;
	case (pie::hac::fac::FsAccessFlag::Host):
		ss << "Host";
		break;
	case (pie::hac::fac::FsAccessFlag::FillBis):
		ss << "FillBis";
		break;
	case (pie::hac::fac::FsAccessFlag::CorruptSaveData):
		ss << "CorruptSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag::SaveDataForDebug):
		ss << "SaveDataForDebug";
		break;
	case (pie::hac::fac::FsAccessFlag::FormatSdCard):
		ss << "FormatSdCard";
		break;
	case (pie::hac::fac::FsAccessFlag::GetRightsId):
		ss << "GetRightsId";
		break;
	case (pie::hac::fac::FsAccessFlag::RegisterExternalKey):
		ss << "RegisterExternalKey";
		break;
	case (pie::hac::fac::FsAccessFlag::RegisterUpdatePartition):
		ss << "RegisterUpdatePartition";
		break;
	case (pie::hac::fac::FsAccessFlag::SaveDataTransfer):
		ss << "SaveDataTransfer";
		break;
	case (pie::hac::fac::FsAccessFlag::DeviceDetection):
		ss << "DeviceDetection";
		break;
	case (pie::hac::fac::FsAccessFlag::AccessFailureResolution):
		ss << "AccessFailureResolution";
		break;
	case (pie::hac::fac::FsAccessFlag::SaveDataTransferVersion2):
		ss << "SaveDataTransferVersion2";
		break;
	case (pie::hac::fac::FsAccessFlag::RegisterProgramIndexMapInfo):
		ss << "RegisterProgramIndexMapInfo";
		break;
	case (pie::hac::fac::FsAccessFlag::CreateOwnSaveData):
		ss << "CreateOwnSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag::Debug):
		ss << "Debug";
		break;
	case (pie::hac::fac::FsAccessFlag::FullPermission):
		ss << "FullPermission";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)flag;
		break;
	}

	return ss.str();
}

std::string pie::hac::FileSystemAccessUtil::getSaveDataOwnerAccessModeAsString(pie::hac::fac::SaveDataOwnerIdAccessType type)
{
	std::stringstream ss;

	switch(type)
	{
	case (pie::hac::fac::SaveDataOwnerIdAccessType::Read):
		ss << "Read";
		break;
	case (pie::hac::fac::SaveDataOwnerIdAccessType::Write):
		ss << "Write";
		break;
	case (pie::hac::fac::SaveDataOwnerIdAccessType::ReadWrite):
		ss << "ReadWrite";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}