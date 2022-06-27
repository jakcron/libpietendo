#pragma once
#include <nn/hac/define/nrr.h>

namespace nn
{
namespace hac
{
	class NrrUtil
	{
	public:
		static std::string getNrrKindAsString(nn::hac::nrr::NrrKind val);

	private:
		const std::string kModuleName = "NRR_UTIL";
	};
}
}