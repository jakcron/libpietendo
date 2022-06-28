#include <pietendo/hac/MiscFlagsEntry.h>

pie::hac::MiscFlagsEntry::MiscFlagsEntry() :
	mCap(kCapId),
	mFlags(0)
{}

pie::hac::MiscFlagsEntry::MiscFlagsEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mFlags(0)
{
	setKernelCapability(kernel_cap);
}

pie::hac::MiscFlagsEntry::MiscFlagsEntry(uint32_t flags) :
	mCap(kCapId),
	mFlags(0)
{
	setFlags(flags);
}

void pie::hac::MiscFlagsEntry::operator=(const MiscFlagsEntry& other)
{
	mFlags = other.mFlags;
	updateCapField();
}

bool pie::hac::MiscFlagsEntry::operator==(const MiscFlagsEntry& other) const
{
	return (mFlags == other.mFlags);
}

bool pie::hac::MiscFlagsEntry::operator!=(const MiscFlagsEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::MiscFlagsEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::MiscFlagsEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'MiscFlags'");
	}

	mCap = kernel_cap;
	processCapField();
}

uint32_t pie::hac::MiscFlagsEntry::getFlags() const
{
	return mFlags;
}

void pie::hac::MiscFlagsEntry::setFlags(uint32_t flags)
{
	if ((flags & ~kMaxVal) != 0)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal MiscFlag bits set. (settable bits: 0-14 inclusive)");
	}

	mFlags = flags;
	updateCapField();
}
