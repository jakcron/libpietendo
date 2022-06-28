	/**
	 * @file fac.h
	 * @brief Declaration of FileAccessControl structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace fac
{
	static const uint32_t kFacFormatVersion = 1;
	static const size_t kSectionAlignSize = 4;
	
	enum FsAccessFlag
	{
		FsAccessFlag_ApplicationInfo = 0,
		FsAccessFlag_BootModeControl = 1,
		FsAccessFlag_Calibration = 2,
		FsAccessFlag_SystemSaveData = 3,
		FsAccessFlag_GameCard = 4,
		FsAccessFlag_SaveDataBackUp = 5,
		FsAccessFlag_SaveDataManagement = 6,
		FsAccessFlag_BisAllRaw = 7,
		FsAccessFlag_GameCardRaw = 8,
		FsAccessFlag_GameCardPrivate = 9,
		FsAccessFlag_SetTime = 10,
		FsAccessFlag_ContentManager = 11,
		FsAccessFlag_ImageManager = 12,
		FsAccessFlag_CreateSaveData = 13,
		FsAccessFlag_SystemSaveDataManagement = 14,
		FsAccessFlag_BisFileSystem = 15,
		FsAccessFlag_SystemUpdate = 16,
		FsAccessFlag_SaveDataMeta = 17,
		FsAccessFlag_DeviceSaveData = 18,
		FsAccessFlag_SettingsControl = 19,
		FsAccessFlag_SystemData = 20,
		FsAccessFlag_SdCard = 21,
		FsAccessFlag_Host = 22,
		FsAccessFlag_FillBis = 23,
		FsAccessFlag_CorruptSaveData = 24,
		FsAccessFlag_SaveDataForDebug = 25,
		FsAccessFlag_FormatSdCard = 26,
		FsAccessFlag_GetRightsId = 27,
		FsAccessFlag_RegisterExternalKey = 28,
		FsAccessFlag_RegisterUpdatePartition = 29,
		FsAccessFlag_SaveDataTransfer = 30,
		FsAccessFlag_DeviceDetection = 31,
		FsAccessFlag_AccessFailureResolution = 32,
		FsAccessFlag_SaveDataTransferVersion2 = 33,
		FsAccessFlag_RegisterProgramIndexMapInfo = 34,
		FsAccessFlag_CreateOwnSaveData = 35,


		FsAccessFlag_Debug = 62,
		FsAccessFlag_FullPermission = 63,
	};

	using fs_access_t = tc::bn::bitarray<sizeof(uint64_t)>;

	enum SaveDataOwnerIdAccessType
	{
		SaveDataOwnerIdAccessType_Read = 1,
		SaveDataOwnerIdAccessType_Write = 2,
		SaveDataOwnerIdAccessType_ReadWrite = 3
	};
}

#pragma pack(push,1)

struct sFacHeader
{
	tc::bn::le32<uint32_t> version; // default 1
	fac::fs_access_t fac_flags;
	struct sFacSection
	{
		tc::bn::le32<uint32_t> offset;
		tc::bn::le32<uint32_t> size;
	} content_owner_ids, save_data_owner_ids; // the data for these follow later in binary. start/end relative to base of FacData instance
};
static_assert(sizeof(sFacHeader) == 0x1C, "sFacHeader size.");

#pragma pack(pop)

}} // namespace pie::hac