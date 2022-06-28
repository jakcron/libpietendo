#include <pietendo/hac/MiscParamsHandler.h>

pie::hac::MiscParamsHandler::MiscParamsHandler() :
	mIsSet(false),
	mEntry()
{}

void pie::hac::MiscParamsHandler::operator=(const MiscParamsHandler & other)
{
	mIsSet = other.mIsSet;
	mEntry.setKernelCapability(other.mEntry.getKernelCapability());
}

bool pie::hac::MiscParamsHandler::operator==(const MiscParamsHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mEntry.getKernelCapability() == other.mEntry.getKernelCapability());
}

bool pie::hac::MiscParamsHandler::operator!=(const MiscParamsHandler & other) const
{
	return !(*this == other);
}

void pie::hac::MiscParamsHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
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

void pie::hac::MiscParamsHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	caps.push_back(mEntry.getKernelCapability());
}

void pie::hac::MiscParamsHandler::clear()
{
	mIsSet = false;
	mEntry = MiscParamsEntry();
}

bool pie::hac::MiscParamsHandler::isSet() const
{
	return mIsSet;
}

pie::hac::kc::ProgramType pie::hac::MiscParamsHandler::getProgramType() const
{
	return mEntry.getProgramType();
}

void pie::hac::MiscParamsHandler::setProgramType(pie::hac::kc::ProgramType type)
{
	mEntry.setProgramType(type);
	mIsSet = true;
}