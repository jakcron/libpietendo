	/**
	 * @file MiscFlagsHandler.h
	 * @brief Declaration of pie::hac::MiscFlagsHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>
#include <pietendo/hac/MiscFlagsEntry.h>

namespace pie { namespace hac {
	
class MiscFlagsHandler :
	public IKernelCapabilityHandler
{
public:
	MiscFlagsHandler();

	void operator=(const MiscFlagsHandler& other);
	bool operator==(const MiscFlagsHandler& other) const;
	bool operator!=(const MiscFlagsHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	const kc::MiscFlags& getMiscFlags() const;
	void setMiscFlags(const kc::MiscFlags& flag);

private:
	const std::string kModuleName = "MISC_FLAGS_HANDLER";
	static const size_t kMaxKernelCapNum = 1;

	bool mIsSet;
	kc::MiscFlags mFlags;
};

}} // namespace pie::hac