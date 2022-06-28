	/**
	 * @file ThreadInfoHandler.h
	 * @brief Declaration of pie::hac::ThreadInfoHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>
#include <pietendo/hac/ThreadInfoEntry.h>

namespace pie { namespace hac {
	
class ThreadInfoHandler :
	public IKernelCapabilityHandler
{
public:
	ThreadInfoHandler();

	void operator=(const ThreadInfoHandler& other);
	bool operator==(const ThreadInfoHandler& other) const;
	bool operator!=(const ThreadInfoHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	uint8_t getMinPriority() const;
	void setMinPriority(uint8_t priority);
	uint8_t getMaxPriority() const;
	void setMaxPriority(uint8_t priority);
	uint8_t getMinCpuId() const;
	void setMinCpuId(uint8_t core_num);
	uint8_t getMaxCpuId() const;
	void setMaxCpuId(uint8_t core_num);

private:
	const std::string kModuleName = "THREAD_INFO_HANDLER";
	static const size_t kMaxKernelCapNum = 1;

	bool mIsSet;
	ThreadInfoEntry mEntry;
};

}} // namespace pie::hac