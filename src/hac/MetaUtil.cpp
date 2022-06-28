#include <pietendo/hac/MetaUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::MetaUtil::getProcessAddressSpaceAsString(pie::hac::meta::ProcessAddressSpace type)
{
	std::stringstream ss;

	switch(type)
	{
	case (pie::hac::meta::ProcessAddressSpace::AddressSpace32Bit):
		ss << "AddressSpace32Bit";
		break;
	case (pie::hac::meta::ProcessAddressSpace::AddressSpace64BitOld):
		ss << "AddressSpace64BitOld";
		break;
	case (pie::hac::meta::ProcessAddressSpace::AddressSpace32BitNoReserved):
		ss << "AddressSpace32BitNoReserved";
		break;
	case (pie::hac::meta::ProcessAddressSpace::AddressSpace64Bit):
		ss << "AddressSpace64Bit";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}