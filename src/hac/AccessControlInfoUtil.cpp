#include <pietendo/hac/AccessControlInfoUtil.h>
#include <fmt/format.h>

std::string pie::hac::AccessControlInfoUtil::getMemoryRegionAsString(pie::hac::aci::MemoryRegion mem_region)
{
	std::string str;

	switch(mem_region)
	{
	case (pie::hac::aci::MemoryRegion_Application):
		str = "Application";
		break;
	case (pie::hac::aci::MemoryRegion_Applet):
		str = "Applet";
		break;
	case (pie::hac::aci::MemoryRegion_SecureSystem):
		str = "SecureSystem";
		break;
	case (pie::hac::aci::MemoryRegion_NonSecureSystem):
		str = "NonSecureSystem";
		break;
	default:
		str = fmt::format("unk_0x{:x}", (uint32_t)mem_region);
		break;
	}

	return str;
}