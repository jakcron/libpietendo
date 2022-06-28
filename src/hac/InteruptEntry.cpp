#include <pietendo/hac/InteruptEntry.h>

pie::hac::InteruptEntry::InteruptEntry() :
	mCap(kCapId),
	mInterupt{0,0}
{
	
}

pie::hac::InteruptEntry::InteruptEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mInterupt{ 0,0 }
{
	setKernelCapability(kernel_cap);
}

pie::hac::InteruptEntry::InteruptEntry(uint32_t interupt0, uint32_t interupt1) :
	mCap(kCapId),
	mInterupt{ 0,0 }
{
	setInterupt(0, interupt0);
	setInterupt(1, interupt1);
}

void pie::hac::InteruptEntry::operator=(const InteruptEntry& other)
{
	mInterupt[0] = other.mInterupt[0];
	mInterupt[1] = other.mInterupt[1];
	updateCapField();
}

bool pie::hac::InteruptEntry::operator==(const InteruptEntry& other) const
{
	return (mInterupt[0] == other.mInterupt[0]) \
		&& (mInterupt[1] == other.mInterupt[1]);
}

bool pie::hac::InteruptEntry::operator!=(const InteruptEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::InteruptEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::InteruptEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'EnableInterupts'");
	}

	mCap = kernel_cap;
	processCapField();
}

uint32_t pie::hac::InteruptEntry::operator[](size_t index) const
{
	return getInterupt(index);
}

uint32_t pie::hac::InteruptEntry::getInterupt(size_t index) const
{
	return mInterupt[index % kInteruptNum];
}

void pie::hac::InteruptEntry::setInterupt(size_t index, uint32_t interupt)
{
	if (interupt > kInteruptMax)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal interupt value.");
	}

	mInterupt[index % kInteruptNum] = interupt;
	updateCapField();
}