	/**
	 * @file AccessControlInfoUtil.h
	 * @brief Declaration of pie::hac::AccessControlInfoUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/aci.h>

namespace pie { namespace hac {
	
class AccessControlInfoUtil
{
public:
	static std::string getMemoryRegionAsString(pie::hac::aci::MemoryRegion mem_region);

private:
	const std::string kModuleName = "ACCESS_CONTROL_INFO_UTIL";
};

}} // namespace pie::hac