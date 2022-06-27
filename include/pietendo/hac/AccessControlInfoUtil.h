#pragma once
#include <nn/hac/define/aci.h>

namespace nn
{
namespace hac
{
	class AccessControlInfoUtil
	{
	public:
		static std::string getMemoryRegionAsString(nn::hac::aci::MemoryRegion mem_region);

	private:
		const std::string kModuleName = "ACCESS_CONTROL_INFO_UTIL";
	};
}
}