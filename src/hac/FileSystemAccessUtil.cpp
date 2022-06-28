#include <pietendo/hac/FileSystemAccessUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::FileSystemAccessUtil::getFsAccessFlagAsString(pie::hac::fac::FsAccessFlag flag)
{
	std::stringstream ss;

	switch(flag)
	{
	case (pie::hac::fac::FsAccessFlag_ApplicationInfo):
		ss << "ApplicationInfo";
		break;
	case (pie::hac::fac::FsAccessFlag_BootModeControl):
		ss << "BootModeControl";
		break;
	case (pie::hac::fac::FsAccessFlag_Calibration):
		ss << "Calibration";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemSaveData):
		ss << "SystemSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_GameCard):
		ss << "GameCard";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataBackUp):
		ss << "SaveDataBackUp";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataManagement):
		ss << "SaveDataManagement";
		break;
	case (pie::hac::fac::FsAccessFlag_BisAllRaw):
		ss << "BisAllRaw";
		break;
	case (pie::hac::fac::FsAccessFlag_GameCardRaw):
		ss << "GameCardRaw";
		break;
	case (pie::hac::fac::FsAccessFlag_GameCardPrivate):
		ss << "GameCardPrivate";
		break;
	case (pie::hac::fac::FsAccessFlag_SetTime):
		ss << "SetTime";
		break;
	case (pie::hac::fac::FsAccessFlag_ContentManager):
		ss << "ContentManager";
		break;
	case (pie::hac::fac::FsAccessFlag_ImageManager):
		ss << "ImageManager";
		break;
	case (pie::hac::fac::FsAccessFlag_CreateSaveData):
		ss << "CreateSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemSaveDataManagement):
		ss << "SystemSaveDataManagement";
		break;
	case (pie::hac::fac::FsAccessFlag_BisFileSystem):
		ss << "BisFileSystem";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataMeta):
		ss << "SaveDataMeta";
		break;
	case (pie::hac::fac::FsAccessFlag_DeviceSaveData):
		ss << "DeviceSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_SettingsControl):
		ss << "SettingsControl";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemData):
		ss << "SystemData";
		break;
	case (pie::hac::fac::FsAccessFlag_SdCard):
		ss << "SdCard";
		break;
	case (pie::hac::fac::FsAccessFlag_Host):
		ss << "Host";
		break;
	case (pie::hac::fac::FsAccessFlag_FillBis):
		ss << "FillBis";
		break;
	case (pie::hac::fac::FsAccessFlag_CorruptSaveData):
		ss << "CorruptSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataForDebug):
		ss << "SaveDataForDebug";
		break;
	case (pie::hac::fac::FsAccessFlag_FormatSdCard):
		ss << "FormatSdCard";
		break;
	case (pie::hac::fac::FsAccessFlag_GetRightsId):
		ss << "GetRightsId";
		break;
	case (pie::hac::fac::FsAccessFlag_RegisterExternalKey):
		ss << "RegisterExternalKey";
		break;
	case (pie::hac::fac::FsAccessFlag_RegisterUpdatePartition):
		ss << "RegisterUpdatePartition";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataTransfer):
		ss << "SaveDataTransfer";
		break;
	case (pie::hac::fac::FsAccessFlag_DeviceDetection):
		ss << "DeviceDetection";
		break;
	case (pie::hac::fac::FsAccessFlag_AccessFailureResolution):
		ss << "AccessFailureResolution";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataTransferVersion2):
		ss << "SaveDataTransferVersion2";
		break;
	case (pie::hac::fac::FsAccessFlag_RegisterProgramIndexMapInfo):
		ss << "RegisterProgramIndexMapInfo";
		break;
	case (pie::hac::fac::FsAccessFlag_CreateOwnSaveData):
		ss << "CreateOwnSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_Debug):
		ss << "Debug";
		break;
	case (pie::hac::fac::FsAccessFlag_FullPermission):
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
	case (pie::hac::fac::SaveDataOwnerIdAccessType_Read):
		ss << "Read";
		break;
	case (pie::hac::fac::SaveDataOwnerIdAccessType_Write):
		ss << "Write";
		break;
	case (pie::hac::fac::SaveDataOwnerIdAccessType_ReadWrite):
		ss << "ReadWrite";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}