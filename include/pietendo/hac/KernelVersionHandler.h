	/**
	 * @file KernelVersionHandler.h
	 * @brief Declaration of pie::hac::KernelVersionHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>
#include <pietendo/hac/KernelVersionEntry.h>

namespace pie { namespace hac {
	
class KernelVersionHandler :
	public IKernelCapabilityHandler
{
public:
	KernelVersionHandler();

	void operator=(const KernelVersionHandler& other);
	bool operator==(const KernelVersionHandler& other) const;
	bool operator!=(const KernelVersionHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	uint16_t getVerMajor() const;
	void setVerMajor(uint16_t major);
	uint8_t getVerMinor() const;
	void setVerMinor(uint8_t minor);

private:
	const std::string kModuleName = "KERNEL_VERSION_HANDLER";
	static const size_t kMaxKernelCapNum = 1;

	bool mIsSet;
	KernelVersionEntry mEntry;
};

}} // namespace pie::hac