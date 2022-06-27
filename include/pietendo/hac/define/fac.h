#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace fac
	{
		static const uint32_t kFacFormatVersion = 1;
		static const size_t kSectionAlignSize = 4;
		
		enum class FsAccessFlag
		{
			ApplicationInfo,
			BootModeControl,
			Calibration,
			SystemSaveData,
			GameCard,
			SaveDataBackUp,
			SaveDataManagement,
			BisAllRaw,
			GameCardRaw,
			GameCardPrivate,
			SetTime,
			ContentManager,
			ImageManager,
			CreateSaveData,
			SystemSaveDataManagement,
			BisFileSystem,
			SystemUpdate,
			SaveDataMeta,
			DeviceSaveData,
			SettingsControl,
			SystemData,
			SdCard,
			Host,
			FillBis,
			CorruptSaveData,
			SaveDataForDebug,
			FormatSdCard,
			GetRightsId,
			RegisterExternalKey,
			RegisterUpdatePartition,
			SaveDataTransfer,
			DeviceDetection,
			AccessFailureResolution,
			SaveDataTransferVersion2,
			RegisterProgramIndexMapInfo,
			CreateOwnSaveData,
			Debug = 62,
			FullPermission = 63,
		};

		using fs_access_t = tc::bn::bitarray<sizeof(uint64_t)>;

		enum class SaveDataOwnerIdAccessType
		{
			Read = 1,
			Write,
			ReadWrite
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
}
}