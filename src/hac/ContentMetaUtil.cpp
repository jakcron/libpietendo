#include <pietendo/hac/ContentMetaUtil.h>
#include <fmt/format.h>

std::string pie::hac::ContentMetaUtil::getContentTypeAsString(pie::hac::cnmt::ContentType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::cnmt::ContentType_Meta):
		str = "Meta";
		break;
	case (pie::hac::cnmt::ContentType_Program):
		str = "Program";
		break;
	case (pie::hac::cnmt::ContentType_Data):
		str = "Data";
		break;
	case (pie::hac::cnmt::ContentType_Control):
		str = "Control";
		break;
	case (pie::hac::cnmt::ContentType_HtmlDocument):
		str = "HtmlDocument";
		break;
	case (pie::hac::cnmt::ContentType_LegalInformation):
		str = "LegalInformation";
		break;
	case (pie::hac::cnmt::ContentType_DeltaFragment):
		str = "DeltaFragment";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentMetaUtil::getContentMetaTypeAsString(pie::hac::cnmt::ContentMetaType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::cnmt::ContentMetaType_SystemProgram):
		str = "SystemProgram";
		break;
	case (pie::hac::cnmt::ContentMetaType_SystemData):
		str = "SystemData";
		break;
	case (pie::hac::cnmt::ContentMetaType_SystemUpdate):
		str = "SystemUpdate";
		break;
	case (pie::hac::cnmt::ContentMetaType_BootImagePackage):
		str = "BootImagePackage";
		break;
	case (pie::hac::cnmt::ContentMetaType_BootImagePackageSafe):
		str = "BootImagePackageSafe";
		break;
	case (pie::hac::cnmt::ContentMetaType_Application):
		str = "Application";
		break;
	case (pie::hac::cnmt::ContentMetaType_Patch):
		str = "Patch";
		break;
	case (pie::hac::cnmt::ContentMetaType_AddOnContent):
		str = "AddOnContent";
		break;
	case (pie::hac::cnmt::ContentMetaType_Delta):
		str = "Delta";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentMetaUtil::getUpdateTypeAsString(pie::hac::cnmt::UpdateType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::cnmt::UpdateType_ApplyAsDelta):
		str = "ApplyAsDelta";
		break;
	case (pie::hac::cnmt::UpdateType_Overwrite):
		str = "Overwrite";
		break;
	case (pie::hac::cnmt::UpdateType_Create):
		str = "Create";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentMetaUtil::getContentInstallTypeAsString(pie::hac::cnmt::ContentInstallType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::cnmt::ContentInstallType_Full):
		str = "Full";
		break;
	case (pie::hac::cnmt::ContentInstallType_FragmentOnly):
		str = "FragmentOnly";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentMetaUtil::getStorageIdAsString(pie::hac::cnmt::StorageId val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::cnmt::StorageId_None):
		str = "None";
		break;
	case (pie::hac::cnmt::StorageId_Host):
		str = "Host";
		break;
	case (pie::hac::cnmt::StorageId_GameCard):
		str = "GameCard";
		break;
	case (pie::hac::cnmt::StorageId_BuiltInSystem):
		str = "BuiltInSystem";
		break;
	case (pie::hac::cnmt::StorageId_BuiltInUser):
		str = "BuiltInUser";
		break;
	case (pie::hac::cnmt::StorageId_SdCard):
		str = "SdCard";
		break;
	case (pie::hac::cnmt::StorageId_Any):
		str = "Any";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentMetaUtil::getContentMetaAttributeFlagAsString(pie::hac::cnmt::ContentMetaAttributeFlag val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::cnmt::ContentMetaAttributeFlag_IncludesExFatDriver):
		str = "IncludesExFatDriver";
		break;
	case (pie::hac::cnmt::ContentMetaAttributeFlag_Rebootless):
		str = "Rebootless";
		break;
	case (pie::hac::cnmt::ContentMetaAttributeFlag_Compacted):
		str = "Compacted";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentMetaUtil::getVersionAsString(uint32_t version)
{
	std::string str;

	uint32_t major,minor,micro,patch_major,patch_minor;
	major = (uint32_t)((version>>26) & 0x3f);
	minor = (uint32_t)((version>>20) & 0x3f);
	micro = (uint32_t)((version>>16) & 0xf);
	patch_major = (uint32_t)((version>>8) & 0xff);
	patch_minor = (uint32_t)((version>>0) & 0xff);

	str = fmt::format("{:d}.{:d}.{:d}-{:d}.{:d}", major,minor,micro,patch_major,patch_minor);

	return str;
}