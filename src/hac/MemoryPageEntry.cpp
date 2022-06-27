#include <nn/hac/MemoryPageEntry.h>

nn::hac::MemoryPageEntry::MemoryPageEntry() :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(false)
{}

nn::hac::MemoryPageEntry::MemoryPageEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(false)
{
	setKernelCapability(kernel_cap);
}

nn::hac::MemoryPageEntry::MemoryPageEntry(uint32_t page) :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(false)
{
	setPage(page);
}

nn::hac::MemoryPageEntry::MemoryPageEntry(uint32_t page, bool flag) :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(true)
{
	setPage(page);
	setFlag(flag);
}

void nn::hac::MemoryPageEntry::operator=(const MemoryPageEntry& other)
{
	mPage = other.mPage;
	mFlag = other.mFlag;
	mMapMultiplePages = other.mMapMultiplePages;
	updateCapField();
}

bool nn::hac::MemoryPageEntry::operator==(const MemoryPageEntry& other) const
{
	return (mPage == other.mPage) \
		&& (mFlag == other.mFlag) \
		&& (mMapMultiplePages == other.mMapMultiplePages);
}

bool nn::hac::MemoryPageEntry::operator!=(const MemoryPageEntry& other) const
{
	return !(*this == other);
}

const nn::hac::KernelCapabilityEntry & nn::hac::MemoryPageEntry::getKernelCapability() const
{
	return mCap;
}

void nn::hac::MemoryPageEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kc::KernelCapId::MemoryMap && kernel_cap.getType() != kc::KernelCapId::IoMemoryMap)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'MemoryMap' or 'IOMemoryMap");
	}

	mCap = kernel_cap;
	processCapField();
}

uint32_t nn::hac::MemoryPageEntry::getPage() const
{
	return mPage;
}

void nn::hac::MemoryPageEntry::setPage(uint32_t page)
{
	if (page > kMaxPage)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal memory page. (range: 0x000000 - 0xFFFFFF)");
	}

	mPage = page;
	updateCapField();
}

bool nn::hac::MemoryPageEntry::getFlag() const
{
	return mFlag;
}

void nn::hac::MemoryPageEntry::setFlag(bool flag)
{
	mFlag = flag;
	updateCapField();
}

bool nn::hac::MemoryPageEntry::isMultiplePages() const
{
	return mMapMultiplePages;
}

void nn::hac::MemoryPageEntry::setMapMultiplePages(bool useFlag)
{
	mMapMultiplePages = useFlag;
}
