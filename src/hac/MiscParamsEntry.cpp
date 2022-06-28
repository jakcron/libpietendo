#include <pietendo/hac/MiscParamsEntry.h>

pie::hac::MiscParamsEntry::MiscParamsEntry() :
	mCap(kCapId),
	mProgramType(kc::ProgramType(0))
{}

pie::hac::MiscParamsEntry::MiscParamsEntry(const KernelCapabilityEntry & kernel_cap) :
	mCap(kCapId),
	mProgramType(kc::ProgramType(0))
{
	setKernelCapability(kernel_cap);
}

pie::hac::MiscParamsEntry::MiscParamsEntry(kc::ProgramType program_type) :
	mCap(kCapId),
	mProgramType(kc::ProgramType(0))
{
	setProgramType(program_type);
}

void pie::hac::MiscParamsEntry::operator=(const MiscParamsEntry& other)
{
	mProgramType = other.mProgramType;
	updateCapField();
}

bool pie::hac::MiscParamsEntry::operator==(const MiscParamsEntry& other) const
{
	return (mProgramType == other.mProgramType);
}

bool pie::hac::MiscParamsEntry::operator!=(const MiscParamsEntry& other) const
{
	return !(*this == other);
}

const pie::hac::KernelCapabilityEntry & pie::hac::MiscParamsEntry::getKernelCapability() const
{
	return mCap;
}

void pie::hac::MiscParamsEntry::setKernelCapability(const KernelCapabilityEntry & kernel_cap)
{
	if (kernel_cap.getType() != kCapId)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry is not type 'ThreadInfo'");
	}

	mCap = kernel_cap;
	processCapField();
}

pie::hac::kc::ProgramType pie::hac::MiscParamsEntry::getProgramType() const
{
	return mProgramType;
}

void pie::hac::MiscParamsEntry::setProgramType(pie::hac::kc::ProgramType type)
{
	if ((byte_t)type > kMaxProgramType)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Illegal ProgramType. (range: 0-7 inclusive)");
	}

	mProgramType = type;
	updateCapField();
}
