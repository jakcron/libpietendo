	/**
	 * @file MiscFlagsEntry.h
	 * @brief Declaration of pie::hac::MiscFlagsEntry
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>
#include <pietendo/hac/KernelCapabilityEntry.h>

namespace pie { namespace hac {
	
class MiscFlagsEntry
{
public:
	MiscFlagsEntry();
	MiscFlagsEntry(const KernelCapabilityEntry& kernel_cap);
	MiscFlagsEntry(uint32_t flags);

	void operator=(const MiscFlagsEntry& other);
	bool operator==(const MiscFlagsEntry& other) const;
	bool operator!=(const MiscFlagsEntry& other) const;

	// kernel capability
	const KernelCapabilityEntry& getKernelCapability() const;
	void setKernelCapability(const KernelCapabilityEntry& kernel_cap);

	// variables
	uint32_t getFlags() const;
	void setFlags(uint32_t flags);
private:
	const std::string kModuleName = "MISC_FLAG_ENTRY";
	static const kc::KernelCapId kCapId = kc::KernelCapId::MiscFlags;
	static const uint32_t kValueBits = 15;
	static const uint32_t kMaxVal = (1 << kValueBits) - 1;

	KernelCapabilityEntry mCap;
	uint32_t mFlags;

	inline void updateCapField()
	{
		uint32_t field = mFlags & kMaxVal;
		mCap.setField(field);
	}

	inline void processCapField()
	{
		uint32_t field = mCap.getField();
		mFlags = field & kMaxVal;
	}
};

}} // namespace pie::hac