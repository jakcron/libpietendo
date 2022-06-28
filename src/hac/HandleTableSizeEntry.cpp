#include <pietendo/hac/HandleTableSizeEntry.h>

pie::hac::HandleTableSizeEntry::HandleTableSizeEntry() :
	mCap(kCapId),
	mHandleTableSize(0)
{}

pie::hac::HandleTableSizeEntry::HandleTableSizeEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mHandleTableSize(0)
{
	setKernelCapability(kernel_cap);
}

pie::hac::HandleTableSizeEntry::HandleTableSizeEntry(uint16_t size) :
	mCap(kCapId),
	mHandleTableSize(0)
{
	setHandleTableSize(size);
}

void pie::hac::HandleTableSizeEntry::operator=(const HandleTableSizeEntry& other)
{
	mHandleTableSize = other.mHandleTableSize;
	updateCapField();
}

bool pie::hac::HandleTableSizeEntry::operator==(const HandleTableSizeEntry& other) const
{
	return (mHandleTableSize == other.mHandleTableSize);
}

bool pie::hac::HandleTableSizeEntry::operator!=(const HandleTableSizeEntry& other) const
{
	return !(*this == other);
}


const pie::hac::KernelCapabilityEntry & pie::hac::HandleTableSizeEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::HandleTableSizeEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'HandleTableSize'");
	}

	mCap = kernel_cap;
	processCapField();
}

uint16_t pie::hac::HandleTableSizeEntry::getHandleTableSize() const
{
	return mHandleTableSize;
}

void pie::hac::HandleTableSizeEntry::setHandleTableSize(uint16_t size)
{
	if (size > kMaxHandleTableSize)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal HandleTableSize. (range: 0-1023 inclusive)");
	}

	mHandleTableSize = size;
	updateCapField();
}