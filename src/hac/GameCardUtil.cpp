#include <nn/hac/GameCardUtil.h>
#include <sstream>
#include <iomanip>

void nn::hac::GameCardUtil::getXciHeaderAesIv(const nn::hac::sGcHeader* hdr, nn::hac::detail::aes_iv_t& iv)
{
	for (size_t i = 0; i < 16; i++)
	{
		iv[15-i] = hdr->aescbc_iv[i];
	}
}

void nn::hac::GameCardUtil::decryptXciHeader(nn::hac::sGcHeader* hdr, const byte_t* key)
{
	nn::hac::detail::aes_iv_t iv;

	getXciHeaderAesIv(hdr, iv);
	// decrypt encrypted data
	tc::crypto::DecryptAes128Cbc(hdr->extended_header.raw_data.data(), hdr->extended_header.raw_data.data(), hdr->extended_header.raw_data.size(), key, sizeof(nn::hac::detail::aes128_key_t), iv.data(), iv.size());
}

std::string nn::hac::GameCardUtil::getKekIndexAsString(nn::hac::gc::KekIndex val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::gc::KEK_PROD):
		ss << "Production";
		break;
	case (nn::hac::gc::KEK_DEV):
		ss << "Development";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::GameCardUtil::getRomSizeAsString(nn::hac::gc::RomSize val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::gc::ROM_SIZE_1GB):
		ss << "1GB";
		break;
	case (nn::hac::gc::ROM_SIZE_2GB):
		ss << "2GB";
		break;
	case (nn::hac::gc::ROM_SIZE_4GB):
		ss << "4GB";
		break;
	case (nn::hac::gc::ROM_SIZE_8GB):
		ss << "8GB";
		break;
	case (nn::hac::gc::ROM_SIZE_16GB):
		ss << "16GB";
		break;
	case (nn::hac::gc::ROM_SIZE_32GB):
		ss << "32GB";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::GameCardUtil::getHeaderFlagsAsString(nn::hac::gc::HeaderFlags val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::gc::FLAG_AUTOBOOT):
		ss << "AutoBoot";
		break;
	case (nn::hac::gc::FLAG_HISTORY_ERASE):
		ss << "HistoryErase";
		break;
	case (nn::hac::gc::FLAG_REPAIR_TIME_REVISOR_TOOL):
		ss << "RepairTimeRevisorTool";
		break;
	case (nn::hac::gc::FLAG_ALLOW_CUP_TO_CHINA):
		ss << "AllowCupToChina";
		break;
	case (nn::hac::gc::FLAG_ALLOW_CUP_TO_GLOBAL):
		ss << "AllowCupToGlobal";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::GameCardUtil::getCardFwVersionDescriptionAsString(nn::hac::gc::FwVersion val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::gc::FWVER_DEV):
		ss << "ForDevelopment";
		break;
	case (nn::hac::gc::FWVER_PROD):
		ss << "1.0.0+";
		break;
	case (nn::hac::gc::FWVER_PROD_SINCE_4_0_0NUP):
		ss << "4.0.0+";
		break;
	case (nn::hac::gc::FWVER_PROD_SINCE_11_0_0NUP):
		ss << "11.0.0+";
		break;
	case (nn::hac::gc::FWVER_PROD_SINCE_12_0_0NUP):
		ss << "12.0.0+";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(16) << std::setfill('0') << (uint64_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::GameCardUtil::getCardClockRateAsString(nn::hac::gc::CardClockRate val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::gc::CLOCK_RATE_25):
		ss << "20 MHz";
		break;
	case (nn::hac::gc::CLOCK_RATE_50):
		ss << "50 MHz";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(8) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string nn::hac::GameCardUtil::getCompatibilityTypeAsString(nn::hac::gc::CompatibilityType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::gc::COMPAT_GLOBAL):
		ss << "Global";
		break;
	case (nn::hac::gc::COMPAT_CHINA):
		ss << "China";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}