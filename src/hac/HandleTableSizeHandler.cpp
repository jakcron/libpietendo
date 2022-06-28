#include <pietendo/hac/HandleTableSizeHandler.h>

pie::hac::HandleTableSizeHandler::HandleTableSizeHandler() :
	mIsSet(false),
	mEntry(0)
{}

void pie::hac::HandleTableSizeHandler::operator=(const HandleTableSizeHandler & other)
{
	mIsSet = other.mIsSet;
	mEntry.setKernelCapability(other.mEntry.getKernelCapability());
}

bool pie::hac::HandleTableSizeHandler::operator==(const HandleTableSizeHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mEntry.getKernelCapability() == other.mEntry.getKernelCapability());
}

bool pie::hac::HandleTableSizeHandler::operator!=(const HandleTableSizeHandler & other) const
{
	return !(*this == other);
}

void pie::hac::HandleTableSizeHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
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

void pie::hac::HandleTableSizeHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	caps.push_back(mEntry.getKernelCapability());
}

void pie::hac::HandleTableSizeHandler::clear()
{
	mIsSet = false;
	mEntry.setHandleTableSize(0);
}

bool pie::hac::HandleTableSizeHandler::isSet() const
{
	return mIsSet;
}

uint16_t pie::hac::HandleTableSizeHandler::getHandleTableSize() const
{
	return mEntry.getHandleTableSize();
}

void pie::hac::HandleTableSizeHandler::setHandleTableSize(uint16_t size)
{
	mEntry.setHandleTableSize(size);
	mIsSet = true;
}