#pragma once
#include <nn/hac/define/meta.h>

namespace nn
{
namespace hac
{
	class MetaUtil
	{
	public:
		static std::string getProcessAddressSpaceAsString(nn::hac::meta::ProcessAddressSpace type);

	private:
		const std::string kModuleName = "META_UTIL";
	};
}
}