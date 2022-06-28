#include <pietendo/hac/MemoryMappingHandler.h>
#include <pietendo/hac/MemoryPageEntry.h>

pie::hac::MemoryMappingHandler::MemoryMappingHandler() :
	mIsSet(false)
{}

void pie::hac::MemoryMappingHandler::operator=(const MemoryMappingHandler & other)
{
	mIsSet = other.mIsSet;
	mMemRange = other.mMemRange;
	mMemPage = other.mMemPage;
}

bool pie::hac::MemoryMappingHandler::operator==(const MemoryMappingHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mMemRange == other.mMemRange) \
		&& (mMemPage == other.mMemPage);
}

bool pie::hac::MemoryMappingHandler::operator!=(const MemoryMappingHandler & other) const
{
	return !(*this == other);
}

void pie::hac::MemoryMappingHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
{
	if (caps.size() == 0)
		return;

	// get entry list
	std::vector<MemoryPageEntry> entries;
	for (size_t i = 0; i < caps.size(); i++)
	{
		entries.push_back(caps[i]);
	}

	mMemRange.clear();
	mMemPage.clear();
	for (size_t i = 0; i < entries.size();)
	{
		// has flag means "MemMap"
		if (entries[i].isMultiplePages())
		{
			// this entry is the last one or the next one isn't a memory map
			if ((i + 1) == entries.size() || entries[i+1].isMultiplePages() == false)
			{
				throw tc::ArgumentOutOfRangeException(kModuleName, "No paired entry");
			}

			// check valid page address
			if (entries[i].getPage() > kMaxPageAddr)
			{
				throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal page address");
			}

			// check valid page num
			if (entries[i+1].getPage() > kMaxPageAddr)
			{
				throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal page num");
			}

			// add to list
			mMemRange.push_back({ entries[i].getPage(), entries[i+1].getPage(), entries[i].getFlag() ? kc::MemoryPermission_Ro : kc::MemoryPermission_Rw, entries[i+1].getFlag() ? kc::MappingType_Static : kc::MappingType_Io });

			// increment i by two
			i += 2;
		}
		// otherwise means "IoMemMap"
		else
		{
			// check valid page address
			if (entries[i].getPage() > kMaxPageAddr)
			{
				throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal page address");
			}

			// add to list
			mMemPage.push_back({ entries[i].getPage(), 1, kc::MemoryPermission_Rw, kc::MappingType_Io });

			// increment i by one
			i += 1;
		}
	}

	mIsSet = true;
}

void pie::hac::MemoryMappingHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	MemoryPageEntry cap;

	// "mem maps"
	cap.setMapMultiplePages(true);
	for (size_t i = 0; i < mMemRange.size(); i++)
	{
		cap.setPage(mMemRange[i].addr & kMaxPageAddr);
		cap.setFlag(mMemRange[i].perm == kc::MemoryPermission_Ro);
		caps.push_back(cap.getKernelCapability());

		cap.setPage(mMemRange[i].size & kMaxPageNum);
		cap.setFlag(mMemRange[i].type == kc::MappingType_Static);
		caps.push_back(cap.getKernelCapability());
	}

	// "io maps"
	cap.setMapMultiplePages(false);
	for (size_t i = 0; i < mMemPage.size(); i++)
	{
		cap.setPage(mMemPage[i].addr & kMaxPageAddr);
		caps.push_back(cap.getKernelCapability());
	}
}

void pie::hac::MemoryMappingHandler::clear()
{
	mIsSet = false;
	mMemRange.clear();
	mMemPage.clear();
}

bool pie::hac::MemoryMappingHandler::isSet() const
{
	return mIsSet;
}

const std::vector<pie::hac::MemoryMappingHandler::sMemoryMapping>& pie::hac::MemoryMappingHandler::getMemoryMaps() const
{
	return mMemRange;
}

const std::vector<pie::hac::MemoryMappingHandler::sMemoryMapping>& pie::hac::MemoryMappingHandler::getIoMemoryMaps() const
{
	return mMemPage;
}