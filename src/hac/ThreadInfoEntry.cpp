#include <pietendo/hac/ThreadInfoEntry.h>

pie::hac::ThreadInfoEntry::ThreadInfoEntry() :
	mCap(kCapId),
	mMinPriority(kDefaultPriority),
	mMaxPriority(kDefaultPriority),
	mMinCpuId(kDefaultCpuId),
	mMaxCpuId(kDefaultCpuId)
{}

pie::hac::ThreadInfoEntry::ThreadInfoEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mMinPriority(kDefaultPriority),
	mMaxPriority(kDefaultPriority),
	mMinCpuId(kDefaultCpuId),
	mMaxCpuId(kDefaultCpuId)
{
	setKernelCapability(kernel_cap);
}

pie::hac::ThreadInfoEntry::ThreadInfoEntry(uint8_t min_priority, uint8_t max_priority, uint8_t min_core_number, uint8_t max_core_number) :
	mCap(kCapId),
	mMinPriority(kDefaultPriority),
	mMaxPriority(kDefaultPriority),
	mMinCpuId(kDefaultCpuId),
	mMaxCpuId(kDefaultCpuId)
{
	setMinPriority(min_priority);
	setMaxPriority(max_priority);
	setMinCpuId(min_core_number);
	setMaxCpuId(max_core_number);
}

void pie::hac::ThreadInfoEntry::operator=(const ThreadInfoEntry& other)
{
	mMinPriority = other.mMinPriority;
	mMaxPriority = other.mMaxPriority;
	mMinCpuId = other.mMinCpuId;
	mMaxCpuId = other.mMaxCpuId;
	updateCapField();
}

bool pie::hac::ThreadInfoEntry::operator==(const ThreadInfoEntry& other) const
{
	return (mMinPriority == other.mMinPriority) \
		&& (mMaxPriority == other.mMaxPriority) \
		&& (mMinCpuId == other.mMinCpuId) \
		&& (mMaxCpuId == other.mMaxCpuId);
}

bool pie::hac::ThreadInfoEntry::operator!=(const ThreadInfoEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::ThreadInfoEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::ThreadInfoEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'ThreadInfo'");
	}

	mCap = kernel_cap;
	processCapField();
}

uint8_t pie::hac::ThreadInfoEntry::getMinPriority() const
{
	return mMinPriority;
}

void pie::hac::ThreadInfoEntry::setMinPriority(uint8_t priority)
{
	if (priority > kMaxVal)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal MinPriority (range 0-63)");
	}

	mMinPriority = priority;
	updateCapField();
}

uint8_t pie::hac::ThreadInfoEntry::getMaxPriority() const
{
	return mMaxPriority;
}

void pie::hac::ThreadInfoEntry::setMaxPriority(uint8_t priority)
{
	if (priority > kMaxVal)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal MaxPriority (range 0-63)");
	}

	mMaxPriority = priority;
	updateCapField();
}

uint8_t pie::hac::ThreadInfoEntry::getMinCpuId() const
{
	return mMinCpuId;
}

void pie::hac::ThreadInfoEntry::setMinCpuId(uint8_t core_num)
{
	if (core_num > kMaxVal)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal MinCoreNumber (range 0-63)");
	}

	mMinCpuId = core_num;
	updateCapField();
}

uint8_t pie::hac::ThreadInfoEntry::getMaxCpuId() const
{
	return mMaxCpuId;
}

void pie::hac::ThreadInfoEntry::setMaxCpuId(uint8_t core_num)
{
	if (core_num > kMaxVal)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal MaxCoreNumber (range 0-63)");
	}

	mMaxCpuId = core_num;
	updateCapField();
}
