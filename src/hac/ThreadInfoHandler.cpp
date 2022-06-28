#include <pietendo/hac/ThreadInfoHandler.h>

pie::hac::ThreadInfoHandler::ThreadInfoHandler() :
	mIsSet(false),
	mEntry(0,0,0,0)
{}

void pie::hac::ThreadInfoHandler::operator=(const ThreadInfoHandler & other)
{
	mIsSet = other.mIsSet;
	mEntry.setKernelCapability(other.mEntry.getKernelCapability());
}

bool pie::hac::ThreadInfoHandler::operator==(const ThreadInfoHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mEntry.getKernelCapability() == other.mEntry.getKernelCapability());
}

bool pie::hac::ThreadInfoHandler::operator!=(const ThreadInfoHandler & other) const
{
	return !(*this == other);
}

void pie::hac::ThreadInfoHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
{
	if (caps.size() > kMaxKernelCapNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Too many kernel capabilities");
	}

	if (caps.size() == 0)
		return;

	mEntry.setKernelCapability(caps[0]);
	mIsSet = true;
}

void pie::hac::ThreadInfoHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	caps.push_back(mEntry.getKernelCapability());
}

void pie::hac::ThreadInfoHandler::clear()
{
	mIsSet = false;
	mEntry.setMaxPriority(0);
	mEntry.setMinPriority(0);
	mEntry.setMaxCpuId(0);
	mEntry.setMinCpuId(0);
}

bool pie::hac::ThreadInfoHandler::isSet() const
{
	return mIsSet;
}

uint8_t pie::hac::ThreadInfoHandler::getMinPriority() const
{
	return mEntry.getMinPriority();
}

void pie::hac::ThreadInfoHandler::setMinPriority(uint8_t priority)
{
	mEntry.setMinPriority(priority);
	mIsSet = true;
}

uint8_t pie::hac::ThreadInfoHandler::getMaxPriority() const
{
	return mEntry.getMaxPriority();
}

void pie::hac::ThreadInfoHandler::setMaxPriority(uint8_t priority)
{
	mEntry.setMaxPriority(priority);
	mIsSet = true;
}

uint8_t pie::hac::ThreadInfoHandler::getMinCpuId() const
{
	return mEntry.getMinCpuId();
}

void pie::hac::ThreadInfoHandler::setMinCpuId(uint8_t core_num)
{
	mEntry.setMinCpuId(core_num);
	mIsSet = true;
}

uint8_t pie::hac::ThreadInfoHandler::getMaxCpuId() const
{
	return mEntry.getMaxCpuId();
}

void pie::hac::ThreadInfoHandler::setMaxCpuId(uint8_t core_num)
{
	mEntry.setMaxCpuId(core_num);
	mIsSet = true;
}