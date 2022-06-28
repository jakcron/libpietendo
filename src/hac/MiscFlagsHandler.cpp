#include <pietendo/hac/MiscFlagsHandler.h>

pie::hac::MiscFlagsHandler::MiscFlagsHandler() :
	mIsSet(false)
{}

void pie::hac::MiscFlagsHandler::operator=(const MiscFlagsHandler & other)
{
	mIsSet = other.mIsSet;
	mFlags = other.mFlags;
}

bool pie::hac::MiscFlagsHandler::operator==(const MiscFlagsHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mFlags == other.mFlags);
}

bool pie::hac::MiscFlagsHandler::operator!=(const MiscFlagsHandler & other) const
{
	return !(*this == other);
}

void pie::hac::MiscFlagsHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
{
	if (caps.size() > kMaxKernelCapNum)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Too many kernel capabilities");
	}

	if (caps.size() == 0)
		return;

	MiscFlagsEntry entry;
	entry.setKernelCapability(caps[0]);
	
	clear();

	mFlags = entry.getFlags();
	mIsSet = true;
}

void pie::hac::MiscFlagsHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	// create MiscFlag entry
	MiscFlagsEntry entry;
	entry.setFlags((uint32_t)mFlags.to_ulong());

	// add to list
	caps.push_back(entry.getKernelCapability());
}

void pie::hac::MiscFlagsHandler::clear()
{
	mIsSet = false;
	mFlags.reset();
}

bool pie::hac::MiscFlagsHandler::isSet() const
{
	return mIsSet;
}

const pie::hac::kc::MiscFlags& pie::hac::MiscFlagsHandler::getMiscFlags() const
{
	return mFlags;
}

void pie::hac::MiscFlagsHandler::setMiscFlags(const pie::hac::kc::MiscFlags& flags)
{
	mFlags = flags;
	mIsSet = true;
}