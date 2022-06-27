#include <nn/hac/MetaUtil.h>
#include <sstream>
#include <iomanip>

std::string nn::hac::MetaUtil::getProcessAddressSpaceAsString(nn::hac::meta::ProcessAddressSpace type)
{
	std::stringstream ss;

	switch(type)
	{
	case (nn::hac::meta::ProcessAddressSpace::AddressSpace32Bit):
		ss << "AddressSpace32Bit";
		break;
	case (nn::hac::meta::ProcessAddressSpace::AddressSpace64BitOld):
		ss << "AddressSpace64BitOld";
		break;
	case (nn::hac::meta::ProcessAddressSpace::AddressSpace32BitNoReserved):
		ss << "AddressSpace32BitNoReserved";
		break;
	case (nn::hac::meta::ProcessAddressSpace::AddressSpace64Bit):
		ss << "AddressSpace64Bit";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)type;
		break;
	}

	return ss.str();
}