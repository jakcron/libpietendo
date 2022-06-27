#include <nn/hac/MiscFlagsHandler.h>

nn::hac::MiscFlagsHandler::MiscFlagsHandler() :
	mIsSet(false)
{}

void nn::hac::MiscFlagsHandler::operator=(const MiscFlagsHandler & other)
{
	mIsSet = other.mIsSet;
	mFlags = other.mFlags;
}

bool nn::hac::MiscFlagsHandler::operator==(const MiscFlagsHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mFlags == other.mFlags);
}

bool nn::hac::MiscFlagsHandler::operator!=(const MiscFlagsHandler & other) const
{
	return !(*this == other);
}

void nn::hac::MiscFlagsHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
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

void nn::hac::MiscFlagsHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	// create MiscFlag entry
	MiscFlagsEntry entry;
	entry.setFlags((uint32_t)mFlags.to_ulong());

	// add to list
	caps.push_back(entry.getKernelCapability());
}

void nn::hac::MiscFlagsHandler::clear()
{
	mIsSet = false;
	mFlags.reset();
}

bool nn::hac::MiscFlagsHandler::isSet() const
{
	return mIsSet;
}

const nn::hac::kc::MiscFlags& nn::hac::MiscFlagsHandler::getMiscFlags() const
{
	return mFlags;
}

void nn::hac::MiscFlagsHandler::setMiscFlags(const nn::hac::kc::MiscFlags& flags)
{
	mFlags = flags;
	mIsSet = true;
}