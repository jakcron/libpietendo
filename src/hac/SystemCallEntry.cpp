#include <pietendo/hac/SystemCallEntry.h>

pie::hac::SystemCallEntry::SystemCallEntry() :
	mCap(kCapId),
	mSystemCallUpper(0),
	mSystemCallLower(0)
{

}

pie::hac::SystemCallEntry::SystemCallEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mSystemCallUpper(0),
	mSystemCallLower(0)
{
	setKernelCapability(kernel_cap);
}

pie::hac::SystemCallEntry::SystemCallEntry(uint32_t upper_bits, uint32_t lower_bits) :
	mCap(kCapId),
	mSystemCallUpper(0),
	mSystemCallLower(0)
{
	setSystemCallUpperBits(upper_bits);
	setSystemCallLowerBits(lower_bits);
}

void pie::hac::SystemCallEntry::operator=(const SystemCallEntry& other)
{
	mSystemCallUpper = other.mSystemCallUpper;
	mSystemCallLower = other.mSystemCallLower;
	updateCapField();
}

bool pie::hac::SystemCallEntry::operator==(const SystemCallEntry& other) const
{
	return (mSystemCallUpper == other.mSystemCallUpper) \
		&& (mSystemCallLower == other.mSystemCallLower);
}

bool pie::hac::SystemCallEntry::operator!=(const SystemCallEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::SystemCallEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::SystemCallEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'EnableSystemCalls'");
	}

	mCap = kernel_cap;
	processCapField();
}

uint32_t pie::hac::SystemCallEntry::getSystemCallUpperBits() const
{
	return mSystemCallUpper;
}

void pie::hac::SystemCallEntry::setSystemCallUpperBits(uint32_t upper_bits)
{
	if (upper_bits > kSysCallUpperMax)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal SystemCall upper bits.");
	}

	mSystemCallUpper = upper_bits;
	updateCapField();
}

uint32_t pie::hac::SystemCallEntry::getSystemCallLowerBits() const
{
	return mSystemCallLower;
}

void pie::hac::SystemCallEntry::setSystemCallLowerBits(uint32_t lower_bits)
{
	if (lower_bits > kSysCallLowerMax)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal SystemCall upper bits.");
	}

	mSystemCallLower = lower_bits;
	updateCapField();
}
