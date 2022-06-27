#include <nn/hac/AccessControlInfoUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::AccessControlInfoUtil::getMemoryRegionAsString(nn::hac::aci::MemoryRegion mem_region)
{
	std::stringstream ss;

	switch(mem_region)
	{
	case (nn::hac::aci::MemoryRegion::Application):
		ss << "Application";
		break;
	case (nn::hac::aci::MemoryRegion::Applet):
		ss << "Applet";
		break;
	case (nn::hac::aci::MemoryRegion::SecureSystem):
		ss << "SecureSystem";
		break;
	case (nn::hac::aci::MemoryRegion::NonSecureSystem):
		ss << "NonSecureSystem";
		break;
	default:
		ss << "unk_0x" << std::hex << (uint32_t)mem_region;
		break;
	}

	return ss.str();
}