#include <pietendo/hac/KernelVersionEntry.h>

pie::hac::KernelVersionEntry::KernelVersionEntry() :
	mCap(kCapId),
	mVerMajor(0),
	mVerMinor(0)
{}

pie::hac::KernelVersionEntry::KernelVersionEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mVerMajor(0),
	mVerMinor(0)
{
	setKernelCapability(kernel_cap);
}

pie::hac::KernelVersionEntry::KernelVersionEntry(uint16_t major, uint8_t minor) :
	mCap(kCapId),
	mVerMajor(0),
	mVerMinor(0)
{
	setVerMajor(major);
	setVerMinor(minor);
}

void pie::hac::KernelVersionEntry::operator=(const KernelVersionEntry& other)
{
	mVerMajor = other.mVerMajor;
	mVerMinor = other.mVerMinor;
	updateCapField();
}

bool pie::hac::KernelVersionEntry::operator==(const KernelVersionEntry& other) const
{
	return (mVerMajor == other.mVerMajor) \
		&& (mVerMinor == other.mVerMinor);
}

bool pie::hac::KernelVersionEntry::operator!=(const KernelVersionEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::KernelVersionEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::KernelVersionEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'KernelVersion'");
	}

	mCap = kernel_cap;
	processCapField();
}

uint16_t pie::hac::KernelVersionEntry::getVerMajor() const
{
	return mVerMajor;
}

void pie::hac::KernelVersionEntry::setVerMajor(uint16_t major)
{
	if (major > kVerMajorMax)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal KernelVersionMajor. (range: 0-0x1fff)");
	}

	mVerMajor = major;
	updateCapField();
}

uint8_t pie::hac::KernelVersionEntry::getVerMinor() const
{
	return mVerMinor;
}

void pie::hac::KernelVersionEntry::setVerMinor(uint8_t minor)
{
	if (minor > kVerMinorMax)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal KernelVersionMinor. (range: 0-0xf)");
	}

	mVerMinor = minor;
	updateCapField();
}
