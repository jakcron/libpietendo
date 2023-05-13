#include <pietendo/hac/GameCardUtil.h>
#include <fmt/format.h>

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
	std::string str;

	switch (val)
	{
	case (pie::hac::gc::KekIndex_Prod):
		str = "Production";
		break;
	case (pie::hac::gc::KekIndex_Dev):
		str = "Development";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::GameCardUtil::getRomSizeAsString(pie::hac::gc::RomSize val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::gc::RomSize_1GB):
		str = "1GB";
		break;
	case (pie::hac::gc::RomSize_2GB):
		str = "2GB";
		break;
	case (pie::hac::gc::RomSize_4GB):
		str = "4GB";
		break;
	case (pie::hac::gc::RomSize_8GB):
		str = "8GB";
		break;
	case (pie::hac::gc::RomSize_16GB):
		str = "16GB";
		break;
	case (pie::hac::gc::RomSize_32GB):
		str = "32GB";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::GameCardUtil::getHeaderFlagsAsString(pie::hac::gc::HeaderFlags val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::gc::HeaderFlags_AutoBoot):
		str = "AutoBoot";
		break;
	case (pie::hac::gc::HeaderFlags_HistoryErase):
		str = "HistoryErase";
		break;
	case (pie::hac::gc::HeaderFlags_RepairTimeRevisorTool):
		str = "RepairTimeRevisorTool";
		break;
	case (pie::hac::gc::HeaderFlags_AllowCupToChina):
		str = "AllowCupToChina";
		break;
	case (pie::hac::gc::HeaderFlags_AllowCupToGlobal):
		str = "AllowCupToGlobal";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::GameCardUtil::getCardFwVersionDescriptionAsString(pie::hac::gc::FwVersion val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::gc::FwVersion_DevKit):
		str = "ForDevelopment";
		break;
	case (pie::hac::gc::FwVersion_Prod):
		str = "1.0.0+";
		break;
	case (pie::hac::gc::FwVersion_Prod_Since4_0_0NUP):
		str = "4.0.0+";
		break;
	case (pie::hac::gc::FwVersion_Prod_Since11_0_0NUP):
		str = "11.0.0+";
		break;
	case (pie::hac::gc::FwVersion_Prod_Since12_0_0NUP):
		str = "12.0.0+";
		break;
	default:
		str = fmt::format("unk_0x{:016x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::GameCardUtil::getCardClockRateAsString(pie::hac::gc::CardClockRate val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::gc::CardClockRate_25MHz):
		str = "20 MHz";
		break;
	case (pie::hac::gc::CardClockRate_50MHz):
		str = "50 MHz";
		break;
	default:
		str = fmt::format("unk_0x{:08x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::GameCardUtil::getCompatibilityTypeAsString(pie::hac::gc::CompatibilityType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::gc::CompatibilityType_Global):
		str = "Global";
		break;
	case (pie::hac::gc::CompatibilityType_China):
		str = "China";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}