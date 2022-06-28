#include <pietendo/hac/MemoryPageEntry.h>

pie::hac::MemoryPageEntry::MemoryPageEntry() :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(false)
{}

pie::hac::MemoryPageEntry::MemoryPageEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(false)
{
	setKernelCapability(kernel_cap);
}

pie::hac::MemoryPageEntry::MemoryPageEntry(uint32_t page) :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(false)
{
	setPage(page);
}

pie::hac::MemoryPageEntry::MemoryPageEntry(uint32_t page, bool flag) :
	mCap(kc::KernelCapId::Invalid),
	mPage(0),
	mFlag(false),
	mMapMultiplePages(true)
{
	setPage(page);
	setFlag(flag);
}

void pie::hac::MemoryPageEntry::operator=(const MemoryPageEntry& other)
{
	mPage = other.mPage;
	mFlag = other.mFlag;
	mMapMultiplePages = other.mMapMultiplePages;
	updateCapField();
}

bool pie::hac::MemoryPageEntry::operator==(const MemoryPageEntry& other) const
{
	return (mPage == other.mPage) \
		&& (mFlag == other.mFlag) \
		&& (mMapMultiplePages == other.mMapMultiplePages);
}

bool pie::hac::MemoryPageEntry::operator!=(const MemoryPageEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::MemoryPageEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::MemoryPageEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kc::KernelCapId::MemoryMap && kernel_cap.getType() != kc::KernelCapId::IoMemoryMap)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'MemoryMap' or 'IOMemoryMap");
	}

	mCap = kernel_cap;
	processCapField();
}

uint32_t pie::hac::MemoryPageEntry::getPage() const
{
	return mPage;
}

void pie::hac::MemoryPageEntry::setPage(uint32_t page)
{
	if (page > kMaxPage)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal memory page. (range: 0x000000 - 0xFFFFFF)");
	}

	mPage = page;
	updateCapField();
}

bool pie::hac::MemoryPageEntry::getFlag() const
{
	return mFlag;
}

void pie::hac::MemoryPageEntry::setFlag(bool flag)
{
	mFlag = flag;
	updateCapField();
}

bool pie::hac::MemoryPageEntry::isMultiplePages() const
{
	return mMapMultiplePages;
}

void pie::hac::MemoryPageEntry::setMapMultiplePages(bool useFlag)
{
	mMapMultiplePages = useFlag;
}
