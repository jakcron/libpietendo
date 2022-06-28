	/**
	 * @file MetaUtil.h
	 * @brief Declaration of pie::hac::MetaUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/meta.h>

namespace pie { namespace hac {
	
class MetaUtil
{
public:
	static std::string getProcessAddressSpaceAsString(pie::hac::meta::ProcessAddressSpace type);

private:
	const std::string kModuleName = "META_UTIL";
};

}} // namespace pie::hac