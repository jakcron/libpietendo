	/**
	 * @file SystemCallHandler.h
	 * @brief Declaration of pie::hac::SystemCallHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>

namespace pie { namespace hac {
	
class SystemCallHandler :
	public IKernelCapabilityHandler
{
public:
	SystemCallHandler();

	void operator=(const SystemCallHandler& other);
	bool operator==(const SystemCallHandler& other) const;
	bool operator!=(const SystemCallHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	const kc::SystemCallIds& getSystemCallIds() const;
	void setSystemCallIds(const kc::SystemCallIds& syscall_ids);

private:
	const std::string kModuleName = "SYSTEM_CALL_HANDLER";
	static const size_t kEntrySyscallCount = 24;
	static const size_t kSyscallTotalEntryNum = (kc::kMaxSystemCallId / kEntrySyscallCount) + 1;

	bool mIsSet;
	kc::SystemCallIds mSystemCallIds;
};

}} // namespace pie::hac
