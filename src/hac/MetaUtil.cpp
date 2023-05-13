#include <pietendo/hac/MetaUtil.h>
#include <fmt/format.h>

std::string pie::hac::MetaUtil::getProcessAddressSpaceAsString(pie::hac::meta::ProcessAddressSpace type)
{
	std::string str;

	switch(type)
	{
	case (pie::hac::meta::ProcessAddressSpace_32Bit):
		str = "AddressSpace32Bit";
		break;
	case (pie::hac::meta::ProcessAddressSpace_64BitOld):
		str = "AddressSpace64BitOld";
		break;
	case (pie::hac::meta::ProcessAddressSpace_32BitNoReserved):
		str = "AddressSpace32BitNoReserved";
		break;
	case (pie::hac::meta::ProcessAddressSpace_64Bit):
		str = "AddressSpace64Bit";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)type);
		break;
	}

	return str;
}