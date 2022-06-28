#include <pietendo/hac/KernelVersionHandler.h>

pie::hac::KernelVersionHandler::KernelVersionHandler() :
	mIsSet(false),
	mEntry(0,0)
{}

void pie::hac::KernelVersionHandler::operator=(const KernelVersionHandler & other)
{
	mIsSet = other.mIsSet;
	mEntry.setKernelCapability(other.mEntry.getKernelCapability());
}

bool pie::hac::KernelVersionHandler::operator==(const KernelVersionHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mEntry.getKernelCapability() == other.mEntry.getKernelCapability());
}

bool pie::hac::KernelVersionHandler::operator!=(const KernelVersionHandler & other) const
{
	return !(*this == other);
}

void pie::hac::KernelVersionHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
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

void pie::hac::KernelVersionHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	caps.push_back(mEntry.getKernelCapability());
}

void pie::hac::KernelVersionHandler::clear()
{
	mIsSet = false;
	mEntry.setVerMajor(0);
	mEntry.setVerMinor(0);
}

bool pie::hac::KernelVersionHandler::isSet() const
{
	return mIsSet;
}

uint16_t pie::hac::KernelVersionHandler::getVerMajor() const
{
	return mEntry.getVerMajor();
}

void pie::hac::KernelVersionHandler::setVerMajor(uint16_t major)
{
	mEntry.setVerMajor(major);
	mIsSet = true;
}

uint8_t pie::hac::KernelVersionHandler::getVerMinor() const
{
	return mEntry.getVerMinor();
}

void pie::hac::KernelVersionHandler::setVerMinor(uint8_t minor)
{
	mEntry.setVerMinor(minor);
	mIsSet = true;
}