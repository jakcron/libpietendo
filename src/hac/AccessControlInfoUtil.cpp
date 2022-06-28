#include <pietendo/hac/AccessControlInfoUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::AccessControlInfoUtil::getMemoryRegionAsString(pie::hac::aci::MemoryRegion mem_region)
{
	std::stringstream ss;

	switch(mem_region)
	{
	case (pie::hac::aci::MemoryRegion_Application):
		ss << "Application";
		break;
	case (pie::hac::aci::MemoryRegion_Applet):
		ss << "Applet";
		break;
	case (pie::hac::aci::MemoryRegion_SecureSystem):
		ss << "SecureSystem";
		break;
	case (pie::hac::aci::MemoryRegion_NonSecureSystem):
		ss << "NonSecureSystem";
		break;
	default:
		ss << "unk_0x" << std::hex << (uint32_t)mem_region;
		break;
	}

	return ss.str();
}