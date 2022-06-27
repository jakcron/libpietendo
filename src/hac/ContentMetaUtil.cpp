#include <nn/hac/ContentMetaUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::ContentMetaUtil::getContentTypeAsString(nn::hac::cnmt::ContentType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentType::Meta):
		ss << "Meta";
		break;
	case (nn::hac::cnmt::ContentType::Program):
		ss << "Program";
		break;
	case (nn::hac::cnmt::ContentType::Data):
		ss << "Data";
		break;
	case (nn::hac::cnmt::ContentType::Control):
		ss << "Control";
		break;
	case (nn::hac::cnmt::ContentType::HtmlDocument):
		ss << "HtmlDocument";
		break;
	case (nn::hac::cnmt::ContentType::LegalInformation):
		ss << "LegalInformation";
		break;
	case (nn::hac::cnmt::ContentType::DeltaFragment):
		ss << "DeltaFragment";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getContentMetaTypeAsString(nn::hac::cnmt::ContentMetaType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentMetaType::SystemProgram):
		ss << "SystemProgram";
		break;
	case (nn::hac::cnmt::ContentMetaType::SystemData):
		ss << "SystemData";
		break;
	case (nn::hac::cnmt::ContentMetaType::SystemUpdate):
		ss << "SystemUpdate";
		break;
	case (nn::hac::cnmt::ContentMetaType::BootImagePackage):
		ss << "BootImagePackage";
		break;
	case (nn::hac::cnmt::ContentMetaType::BootImagePackageSafe):
		ss << "BootImagePackageSafe";
		break;
	case (nn::hac::cnmt::ContentMetaType::Application):
		ss << "Application";
		break;
	case (nn::hac::cnmt::ContentMetaType::Patch):
		ss << "Patch";
		break;
	case (nn::hac::cnmt::ContentMetaType::AddOnContent):
		ss << "AddOnContent";
		break;
	case (nn::hac::cnmt::ContentMetaType::Delta):
		ss << "Delta";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getUpdateTypeAsString(nn::hac::cnmt::UpdateType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::UpdateType::ApplyAsDelta):
		ss << "ApplyAsDelta";
		break;
	case (nn::hac::cnmt::UpdateType::Overwrite):
		ss << "Overwrite";
		break;
	case (nn::hac::cnmt::UpdateType::Create):
		ss << "Create";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getContentInstallTypeAsString(nn::hac::cnmt::ContentInstallType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentInstallType::Full):
		ss << "Full";
		break;
	case (nn::hac::cnmt::ContentInstallType::FragmentOnly):
		ss << "FragmentOnly";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getStorageIdAsString(nn::hac::cnmt::StorageId val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::StorageId::None):
		ss << "None";
		break;
	case (nn::hac::cnmt::StorageId::Host):
		ss << "Host";
		break;
	case (nn::hac::cnmt::StorageId::GameCard):
		ss << "GameCard";
		break;
	case (nn::hac::cnmt::StorageId::BuiltInSystem):
		ss << "BuiltInSystem";
		break;
	case (nn::hac::cnmt::StorageId::BuiltInUser):
		ss << "BuiltInUser";
		break;
	case (nn::hac::cnmt::StorageId::SdCard):
		ss << "SdCard";
		break;
	case (nn::hac::cnmt::StorageId::Any):
		ss << "Any";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getContentMetaAttributeFlagAsString(nn::hac::cnmt::ContentMetaAttributeFlag val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::cnmt::ContentMetaAttributeFlag::IncludesExFatDriver):
		ss << "IncludesExFatDriver";
		break;
	case (nn::hac::cnmt::ContentMetaAttributeFlag::Rebootless):
		ss << "Rebootless";
		break;
	case (nn::hac::cnmt::ContentMetaAttributeFlag::Compacted):
		ss << "Compacted";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::ContentMetaUtil::getVersionAsString(uint32_t version)
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