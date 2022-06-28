	/**
	 * @file MiscParamsHandler.h
	 * @brief Declaration of pie::hac::MiscParamsHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>
#include <pietendo/hac/MiscParamsEntry.h>

namespace pie { namespace hac {
	
class MiscParamsHandler :
	public IKernelCapabilityHandler
{
public:
	MiscParamsHandler();

	void operator=(const MiscParamsHandler& other);
	bool operator==(const MiscParamsHandler& other) const;
	bool operator!=(const MiscParamsHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	kc::ProgramType getProgramType() const;
	void setProgramType(kc::ProgramType type);

private:
	const std::string kModuleName = "MISC_PARAMS_HANDLER";
	static const size_t kMaxKernelCapNum = 1;

	bool mIsSet;
	MiscParamsEntry mEntry;
};

}} // namespace pie::hac