#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/KernelCapabilityEntry.h>

namespace nn
{
namespace hac
{
	class IKernelCapabilityHandler
	{
	public:
		virtual void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps) = 0;
		virtual void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const = 0;
		virtual void clear() = 0;
		virtual bool isSet() const = 0;
	};
}
}