#include <nn/hac/NrrUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::NrrUtil::getNrrKindAsString(nn::hac::nrr::NrrKind val)
{
	std::stringstream ss;

	switch (val)
	{
	case (nn::hac::nrr::NrrKind::User):
		ss << "User";
		break;
	case (nn::hac::nrr::NrrKind::JitPlugin):
		ss << "JitPlugin";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}