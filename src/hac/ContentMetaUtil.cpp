#include <pietendo/hac/ContentMetaUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::ContentMetaUtil::getContentTypeAsString(pie::hac::cnmt::ContentType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::cnmt::ContentType::Meta):
		ss << "Meta";
		break;
	case (pie::hac::cnmt::ContentType::Program):
		ss << "Program";
		break;
	case (pie::hac::cnmt::ContentType::Data):
		ss << "Data";
		break;
	case (pie::hac::cnmt::ContentType::Control):
		ss << "Control";
		break;
	case (pie::hac::cnmt::ContentType::HtmlDocument):
		ss << "HtmlDocument";
		break;
	case (pie::hac::cnmt::ContentType::LegalInformation):
		ss << "LegalInformation";
		break;
	case (pie::hac::cnmt::ContentType::DeltaFragment):
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
	case (pie::hac::cnmt::ContentMetaType::SystemProgram):
		ss << "SystemProgram";
		break;
	case (pie::hac::cnmt::ContentMetaType::SystemData):
		ss << "SystemData";
		break;
	case (pie::hac::cnmt::ContentMetaType::SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (pie::hac::cnmt::ContentMetaType::BootImagePackage):
		ss << "BootImagePackage";
		break;
	case (pie::hac::cnmt::ContentMetaType::BootImagePackageSafe):
		ss << "BootImagePackageSafe";
		break;
	case (pie::hac::cnmt::ContentMetaType::Application):
		ss << "Application";
		break;
	case (pie::hac::cnmt::ContentMetaType::Patch):
		ss << "Patch";
		break;
	case (pie::hac::cnmt::ContentMetaType::AddOnContent):
		ss << "AddOnContent";
		break;
	case (pie::hac::cnmt::ContentMetaType::Delta):
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
	case (pie::hac::cnmt::UpdateType::ApplyAsDelta):
		ss << "ApplyAsDelta";
		break;
	case (pie::hac::cnmt::UpdateType::Overwrite):
		ss << "Overwrite";
		break;
	case (pie::hac::cnmt::UpdateType::Create):
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
	case (pie::hac::cnmt::ContentInstallType::Full):
		ss << "Full";
		break;
	case (pie::hac::cnmt::ContentInstallType::FragmentOnly):
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
	case (pie::hac::cnmt::StorageId::None):
		ss << "None";
		break;
	case (pie::hac::cnmt::StorageId::Host):
		ss << "Host";
		break;
	case (pie::hac::cnmt::StorageId::GameCard):
		ss << "GameCard";
		break;
	case (pie::hac::cnmt::StorageId::BuiltInSystem):
		ss << "BuiltInSystem";
		break;
	case (pie::hac::cnmt::StorageId::BuiltInUser):
		ss << "BuiltInUser";
		break;
	case (pie::hac::cnmt::StorageId::SdCard):
		ss << "SdCard";
		break;
	case (pie::hac::cnmt::StorageId::Any):
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
	case (pie::hac::cnmt::ContentMetaAttributeFlag::IncludesExFatDriver):
		ss << "IncludesExFatDriver";
		break;
	case (pie::hac::cnmt::ContentMetaAttributeFlag::Rebootless):
		ss << "Rebootless";
		break;
	case (pie::hac::cnmt::ContentMetaAttributeFlag::Compacted):
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