	/**
	 * @file KernelCapabilityUtil.h
	 * @brief Declaration of pie::hac::KernelCapabilityUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/kc.h>
#include <string>

namespace pie { namespace hac {
	
class KernelCapabilityUtil
{
public:
	static std::string getMiscFlagsBitAsString(pie::hac::kc::MiscFlagsBit flag);
	static std::string getProgramTypeAsString(pie::hac::kc::ProgramType type);
	static std::string getMemoryPermissionAsString(pie::hac::kc::MemoryPermission type);
	static std::string getMappingTypeAsString(pie::hac::kc::MappingType type);
	static std::string getSystemCallIdAsString(pie::hac::kc::SystemCallId svc);

private:
	const std::string kModuleName = "KERNEL_CAPABILITY_UTIL";
};

}} // namespace pie::hac