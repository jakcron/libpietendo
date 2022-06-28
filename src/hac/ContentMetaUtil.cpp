#include <pietendo/hac/ContentMetaUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::ContentMetaUtil::getContentTypeAsString(pie::hac::cnmt::ContentType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::ContentType_Meta):
		ss << "Meta";
		break;
	case (pie::hac::cnmt::ContentType_Program):
		ss << "Program";
		break;
	case (pie::hac::cnmt::ContentType_Data):
		ss << "Data";
		break;
	case (pie::hac::cnmt::ContentType_Control):
		ss << "Control";
		break;
	case (pie::hac::cnmt::ContentType_HtmlDocument):
		ss << "HtmlDocument";
		break;
	case (pie::hac::cnmt::ContentType_LegalInformation):
		ss << "LegalInformation";
		break;
	case (pie::hac::cnmt::ContentType_DeltaFragment):
		ss << "DeltaFragment";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ContentMetaUtil::getContentMetaTypeAsString(pie::hac::cnmt::ContentMetaType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::ContentMetaType_SystemProgram):
		ss << "SystemProgram";
		break;
	case (pie::hac::cnmt::ContentMetaType_SystemData):
		ss << "SystemData";
		break;
	case (pie::hac::cnmt::ContentMetaType_SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (pie::hac::cnmt::ContentMetaType_BootImagePackage):
		ss << "BootImagePackage";
		break;
	case (pie::hac::cnmt::ContentMetaType_BootImagePackageSafe):
		ss << "BootImagePackageSafe";
		break;
	case (pie::hac::cnmt::ContentMetaType_Application):
		ss << "Application";
		break;
	case (pie::hac::cnmt::ContentMetaType_Patch):
		ss << "Patch";
		break;
	case (pie::hac::cnmt::ContentMetaType_AddOnContent):
		ss << "AddOnContent";
		break;
	case (pie::hac::cnmt::ContentMetaType_Delta):
		ss << "Delta";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ContentMetaUtil::getUpdateTypeAsString(pie::hac::cnmt::UpdateType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::UpdateType_ApplyAsDelta):
		ss << "ApplyAsDelta";
		break;
	case (pie::hac::cnmt::UpdateType_Overwrite):
		ss << "Overwrite";
		break;
	case (pie::hac::cnmt::UpdateType_Create):
		ss << "Create";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ContentMetaUtil::getContentInstallTypeAsString(pie::hac::cnmt::ContentInstallType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::ContentInstallType_Full):
		ss << "Full";
		break;
	case (pie::hac::cnmt::ContentInstallType_FragmentOnly):
		ss << "FragmentOnly";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ContentMetaUtil::getStorageIdAsString(pie::hac::cnmt::StorageId val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::StorageId_None):
		ss << "None";
		break;
	case (pie::hac::cnmt::StorageId_Host):
		ss << "Host";
		break;
	case (pie::hac::cnmt::StorageId_GameCard):
		ss << "GameCard";
		break;
	case (pie::hac::cnmt::StorageId_BuiltInSystem):
		ss << "BuiltInSystem";
		break;
	case (pie::hac::cnmt::StorageId_BuiltInUser):
		ss << "BuiltInUser";
		break;
	case (pie::hac::cnmt::StorageId_SdCard):
		ss << "SdCard";
		break;
	case (pie::hac::cnmt::StorageId_Any):
		ss << "Any";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ContentMetaUtil::getContentMetaAttributeFlagAsString(pie::hac::cnmt::ContentMetaAttributeFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::ContentMetaAttributeFlag_IncludesExFatDriver):
		ss << "IncludesExFatDriver";
		break;
	case (pie::hac::cnmt::ContentMetaAttributeFlag_Rebootless):
		ss << "Rebootless";
		break;
	case (pie::hac::cnmt::ContentMetaAttributeFlag_Compacted):
		ss << "Compacted";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::ContentMetaUtil::getVersionAsString(uint32_t version)
{
	std::stringstream ss;

	ss << (uint32_t)((version>>26) & 0x3f);
	ss << ".";
	ss << (uint32_t)((version>>20) & 0x3f);
	ss << ".";
	ss << (uint32_t)((version>>16) & 0xf);
	ss << "-";
	ss << (uint32_t)((version>>8) & 0xff);
	ss << ".";
	ss << (uint32_t)((version>>0) & 0xff);

	return ss.str();
}