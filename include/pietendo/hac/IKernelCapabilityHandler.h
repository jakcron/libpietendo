	/**
	 * @file IKernelCapabilityHandler.h
	 * @brief Declaration of pie::hac::IKernelCapabilityHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>
#include <pietendo/hac/KernelCapabilityEntry.h>

namespace pie { namespace hac {
	
class IKernelCapabilityHandler
{
public:
	virtual void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps) = 0;
	virtual void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const = 0;
	virtual void clear() = 0;
	virtual bool isSet() const = 0;
};

}} // namespace pie::hac