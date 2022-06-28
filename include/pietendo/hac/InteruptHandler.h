	/**
	 * @file InteruptHandler.h
	 * @brief Declaration of pie::hac::InteruptHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>
#include <pietendo/hac/InteruptEntry.h>

namespace pie { namespace hac {
	
class InteruptHandler :
	public IKernelCapabilityHandler
{
public:
	InteruptHandler();

	void operator=(const InteruptHandler& other);
	bool operator==(const InteruptHandler& other) const;
	bool operator!=(const InteruptHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	const std::vector<uint16_t>& getInteruptList() const;
	void setInteruptList(const std::vector<uint16_t>& interupts);

private:
	const std::string kModuleName = "INTERUPT_HANDLER";

	bool mIsSet;
	std::vector<uint16_t> mInterupts;
};

}} // namespace pie::hac