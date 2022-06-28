	/**
	 * @file NrrUtil.h
	 * @brief Declaration of pie::hac::NrrUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/nrr.h>

namespace pie { namespace hac {
	
class NrrUtil
{
public:
	static std::string getNrrKindAsString(pie::hac::nrr::NrrKind val);

private:
	const std::string kModuleName = "NRR_UTIL";
};

}} // namespace pie::hac