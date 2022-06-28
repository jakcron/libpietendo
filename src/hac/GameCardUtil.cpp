#include <pietendo/hac/GameCardUtil.h>
#include <sstream>
#include <iomanip>

void pie::hac::GameCardUtil::getXciHeaderAesIv(const pie::hac::sGcHeader* hdr, pie::hac::detail::aes_iv_t& iv)
{
	for (size_t i = 0; i < 16; i++)
	{
		iv[15-i] = hdr->aescbc_iv[i];
	}
}

void pie::hac::GameCardUtil::decryptXciHeader(pie::hac::sGcHeader* hdr, const byte_t* key)
{
	pie::hac::detail::aes_iv_t iv;

	getXciHeaderAesIv(hdr, iv);
	// decrypt encrypted data
	tc::crypto::DecryptAes128Cbc(hdr->extended_header.raw_data.data(), hdr->extended_header.raw_data.data(), hdr->extended_header.raw_data.size(), key, sizeof(pie::hac::detail::aes128_key_t), iv.data(), iv.size());
}

std::string pie::hac::GameCardUtil::getKekIndexAsString(pie::hac::gc::KekIndex val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::gc::KekIndex_Prod):
		ss << "Production";
		break;
	case (pie::hac::gc::KekIndex_Dev):
		ss << "Development";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::GameCardUtil::getRomSizeAsString(pie::hac::gc::RomSize val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::gc::RomSize_1GB):
		ss << "1GB";
		break;
	case (pie::hac::gc::RomSize_2GB):
		ss << "2GB";
		break;
	case (pie::hac::gc::RomSize_4GB):
		ss << "4GB";
		break;
	case (pie::hac::gc::RomSize_8GB):
		ss << "8GB";
		break;
	case (pie::hac::gc::RomSize_16GB):
		ss << "16GB";
		break;
	case (pie::hac::gc::RomSize_32GB):
		ss << "32GB";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::GameCardUtil::getHeaderFlagsAsString(pie::hac::gc::HeaderFlags val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::gc::HeaderFlags_AutoBoot):
		ss << "AutoBoot";
		break;
	case (pie::hac::gc::HeaderFlags_HistoryErase):
		ss << "HistoryErase";
		break;
	case (pie::hac::gc::HeaderFlags_RepairTimeRevisorTool):
		ss << "RepairTimeRevisorTool";
		break;
	case (pie::hac::gc::HeaderFlags_AllowCupToChina):
		ss << "AllowCupToChina";
		break;
	case (pie::hac::gc::HeaderFlags_AllowCupToGlobal):
		ss << "AllowCupToGlobal";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::GameCardUtil::getCardFwVersionDescriptionAsString(pie::hac::gc::FwVersion val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::gc::FwVersion_DevKit):
		ss << "ForDevelopment";
		break;
	case (pie::hac::gc::FwVersion_Prod):
		ss << "1.0.0+";
		break;
	case (pie::hac::gc::FwVersion_Prod_Since4_0_0NUP):
		ss << "4.0.0+";
		break;
	case (pie::hac::gc::FwVersion_Prod_Since11_0_0NUP):
		ss << "11.0.0+";
		break;
	case (pie::hac::gc::FwVersion_Prod_Since12_0_0NUP):
		ss << "12.0.0+";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(16) << std::setfill('0') << (uint64_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::GameCardUtil::getCardClockRateAsString(pie::hac::gc::CardClockRate val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::gc::CardClockRate_25MHz):
		ss << "20 MHz";
		break;
	case (pie::hac::gc::CardClockRate_50MHz):
		ss << "50 MHz";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(8) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::GameCardUtil::getCompatibilityTypeAsString(pie::hac::gc::CompatibilityType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::gc::CompatibilityType_Global):
		ss << "Global";
		break;
	case (pie::hac::gc::CompatibilityType_China):
		ss << "China";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}