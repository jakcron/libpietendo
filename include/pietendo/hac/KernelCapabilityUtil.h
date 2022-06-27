#pragma once
#include <nn/hac/define/kc.h>
#include <string>

namespace nn
{
namespace hac
{
	class KernelCapabilityUtil
	{
	public:
		static std::string getMiscFlagsBitAsString(nn::hac::kc::MiscFlagsBit flag);
		static std::string getProgramTypeAsString(nn::hac::kc::ProgramType type);
		static std::string getMemoryPermissionAsString(nn::hac::kc::MemoryPermission type);
		static std::string getMappingTypeAsString(nn::hac::kc::MappingType type);
		static std::string getSystemCallIdAsString(nn::hac::kc::SystemCallId svc);

	private:
		const std::string kModuleName = "KERNEL_CAPABILITY_UTIL";
	};
}
}