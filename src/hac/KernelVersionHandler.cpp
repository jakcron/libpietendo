#include <nn/hac/KernelVersionHandler.h>

nn::hac::KernelVersionHandler::KernelVersionHandler() :
	mIsSet(false),
	mEntry(0,0)
{}

void nn::hac::KernelVersionHandler::operator=(const KernelVersionHandler & other)
{
	mIsSet = other.mIsSet;
	mEntry.setKernelCapability(other.mEntry.getKernelCapability());
}

bool nn::hac::KernelVersionHandler::operator==(const KernelVersionHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mEntry.getKernelCapability() == other.mEntry.getKernelCapability());
}

bool nn::hac::KernelVersionHandler::operator!=(const KernelVersionHandler & other) const
{
	return !(*this == other);
}

void nn::hac::KernelVersionHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
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

void nn::hac::KernelVersionHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	caps.push_back(mEntry.getKernelCapability());
}

void nn::hac::KernelVersionHandler::clear()
{
	mIsSet = false;
	mEntry.setVerMajor(0);
	mEntry.setVerMinor(0);
}

bool nn::hac::KernelVersionHandler::isSet() const
{
	return mIsSet;
}

uint16_t nn::hac::KernelVersionHandler::getVerMajor() const
{
	return mEntry.getVerMajor();
}

void nn::hac::KernelVersionHandler::setVerMajor(uint16_t major)
{
	mEntry.setVerMajor(major);
	mIsSet = true;
}

uint8_t nn::hac::KernelVersionHandler::getVerMinor() const
{
	return mEntry.getVerMinor();
}

void nn::hac::KernelVersionHandler::setVerMinor(uint8_t minor)
{
	mEntry.setVerMinor(minor);
	mIsSet = true;
}