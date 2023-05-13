#include <pietendo/hac/FileSystemAccessUtil.h>
#include <fmt/format.h>

std::string pie::hac::FileSystemAccessUtil::getFsAccessFlagAsString(pie::hac::fac::FsAccessFlag flag)
{
	std::string str;

	switch(flag)
	{
	case (pie::hac::fac::FsAccessFlag_ApplicationInfo):
		str = "ApplicationInfo";
		break;
	case (pie::hac::fac::FsAccessFlag_BootModeControl):
		str = "BootModeControl";
		break;
	case (pie::hac::fac::FsAccessFlag_Calibration):
		str = "Calibration";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemSaveData):
		str = "SystemSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_GameCard):
		str = "GameCard";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataBackUp):
		str = "SaveDataBackUp";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataManagement):
		str = "SaveDataManagement";
		break;
	case (pie::hac::fac::FsAccessFlag_BisAllRaw):
		str = "BisAllRaw";
		break;
	case (pie::hac::fac::FsAccessFlag_GameCardRaw):
		str = "GameCardRaw";
		break;
	case (pie::hac::fac::FsAccessFlag_GameCardPrivate):
		str = "GameCardPrivate";
		break;
	case (pie::hac::fac::FsAccessFlag_SetTime):
		str = "SetTime";
		break;
	case (pie::hac::fac::FsAccessFlag_ContentManager):
		str = "ContentManager";
		break;
	case (pie::hac::fac::FsAccessFlag_ImageManager):
		str = "ImageManager";
		break;
	case (pie::hac::fac::FsAccessFlag_CreateSaveData):
		str = "CreateSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemSaveDataManagement):
		str = "SystemSaveDataManagement";
		break;
	case (pie::hac::fac::FsAccessFlag_BisFileSystem):
		str = "BisFileSystem";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemUpdate):
		str = "SystemUpdate";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataMeta):
		str = "SaveDataMeta";
		break;
	case (pie::hac::fac::FsAccessFlag_DeviceSaveData):
		str = "DeviceSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_SettingsControl):
		str = "SettingsControl";
		break;
	case (pie::hac::fac::FsAccessFlag_SystemData):
		str = "SystemData";
		break;
	case (pie::hac::fac::FsAccessFlag_SdCard):
		str = "SdCard";
		break;
	case (pie::hac::fac::FsAccessFlag_Host):
		str = "Host";
		break;
	case (pie::hac::fac::FsAccessFlag_FillBis):
		str = "FillBis";
		break;
	case (pie::hac::fac::FsAccessFlag_CorruptSaveData):
		str = "CorruptSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataForDebug):
		str = "SaveDataForDebug";
		break;
	case (pie::hac::fac::FsAccessFlag_FormatSdCard):
		str = "FormatSdCard";
		break;
	case (pie::hac::fac::FsAccessFlag_GetRightsId):
		str = "GetRightsId";
		break;
	case (pie::hac::fac::FsAccessFlag_RegisterExternalKey):
		str = "RegisterExternalKey";
		break;
	case (pie::hac::fac::FsAccessFlag_RegisterUpdatePartition):
		str = "RegisterUpdatePartition";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataTransfer):
		str = "SaveDataTransfer";
		break;
	case (pie::hac::fac::FsAccessFlag_DeviceDetection):
		str = "DeviceDetection";
		break;
	case (pie::hac::fac::FsAccessFlag_AccessFailureResolution):
		str = "AccessFailureResolution";
		break;
	case (pie::hac::fac::FsAccessFlag_SaveDataTransferVersion2):
		str = "SaveDataTransferVersion2";
		break;
	case (pie::hac::fac::FsAccessFlag_RegisterProgramIndexMapInfo):
		str = "RegisterProgramIndexMapInfo";
		break;
	case (pie::hac::fac::FsAccessFlag_CreateOwnSaveData):
		str = "CreateOwnSaveData";
		break;
	case (pie::hac::fac::FsAccessFlag_Debug):
		str = "Debug";
		break;
	case (pie::hac::fac::FsAccessFlag_FullPermission):
		str = "FullPermission";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)flag);
		break;
	}

	return str;
}

std::string pie::hac::FileSystemAccessUtil::getSaveDataOwnerAccessModeAsString(pie::hac::fac::SaveDataOwnerIdAccessType type)
{
	std::string str;

	switch(type)
	{
	case (pie::hac::fac::SaveDataOwnerIdAccessType_Read):
		str = "Read";
		break;
	case (pie::hac::fac::SaveDataOwnerIdAccessType_Write):
		str = "Write";
		break;
	case (pie::hac::fac::SaveDataOwnerIdAccessType_ReadWrite):
		str = "ReadWrite";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)type);
		break;
	}

	return str;
}