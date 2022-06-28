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
	case (pie::hac::gc::KEK_PROD):
		ss << "Production";
		break;
	case (pie::hac::gc::KEK_DEV):
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
	case (pie::hac::gc::ROM_SIZE_1GB):
		ss << "1GB";
		break;
	case (pie::hac::gc::ROM_SIZE_2GB):
		ss << "2GB";
		break;
	case (pie::hac::gc::ROM_SIZE_4GB):
		ss << "4GB";
		break;
	case (pie::hac::gc::ROM_SIZE_8GB):
		ss << "8GB";
		break;
	case (pie::hac::gc::ROM_SIZE_16GB):
		ss << "16GB";
		break;
	case (pie::hac::gc::ROM_SIZE_32GB):
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
	case (pie::hac::gc::FLAG_AUTOBOOT):
		ss << "AutoBoot";
		break;
	case (pie::hac::gc::FLAG_HISTORY_ERASE):
		ss << "HistoryErase";
		break;
	case (pie::hac::gc::FLAG_REPAIR_TIME_REVISOR_TOOL):
		ss << "RepairTimeRevisorTool";
		break;
	case (pie::hac::gc::FLAG_ALLOW_CUP_TO_CHINA):
		ss << "AllowCupToChina";
		break;
	case (pie::hac::gc::FLAG_ALLOW_CUP_TO_GLOBAL):
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
	case (pie::hac::gc::FWVER_DEV):
		ss << "ForDevelopment";
		break;
	case (pie::hac::gc::FWVER_PROD):
		ss << "1.0.0+";
		break;
	case (pie::hac::gc::FWVER_PROD_SINCE_4_0_0NUP):
		ss << "4.0.0+";
		break;
	case (pie::hac::gc::FWVER_PROD_SINCE_11_0_0NUP):
		ss << "11.0.0+";
		break;
	case (pie::hac::gc::FWVER_PROD_SINCE_12_0_0NUP):
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
	case (pie::hac::gc::CLOCK_RATE_25):
		ss << "20 MHz";
		break;
	case (pie::hac::gc::CLOCK_RATE_50):
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
	case (pie::hac::gc::COMPAT_GLOBAL):
		ss << "Global";
		break;
	case (pie::hac::gc::COMPAT_CHINA):
		ss << "China";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}