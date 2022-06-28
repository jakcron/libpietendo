#include <pietendo/hac/KernelCapabilityEntry.h>

pie::hac::KernelCapabilityEntry::KernelCapabilityEntry() :
	mType(kc::KernelCapId::Invalid)
{}

pie::hac::KernelCapabilityEntry::KernelCapabilityEntry(kc::KernelCapId type) :
	mType(type),
	mField(0)
{}

pie::hac::KernelCapabilityEntry::KernelCapabilityEntry(kc::KernelCapId type, uint32_t field) :
	mType(type),
	mField(field)
{}

void pie::hac::KernelCapabilityEntry::operator=(const KernelCapabilityEntry & other)
{
	mType = other.mType;
	mField = other.mField;
}

bool pie::hac::KernelCapabilityEntry::operator==(const KernelCapabilityEntry & other) const
{
	return (mType == other.mType) \
		&& (mField == other.mField);
}

bool pie::hac::KernelCapabilityEntry::operator!=(const KernelCapabilityEntry & other) const
{
	return !operator==(other);
}

uint32_t pie::hac::KernelCapabilityEntry::getCap() const
{
	return (mField & getFieldMask()) << getFieldShift() | getCapMask();
}

void pie::hac::KernelCapabilityEntry::setCap(uint32_t cap)
{
	mType = getCapId(cap);
	mField = (cap >> getFieldShift()) & getFieldMask();
}

pie::hac::kc::KernelCapId pie::hac::KernelCapabilityEntry::getType() const
{
	return mType;
}

void pie::hac::KernelCapabilityEntry::setType(kc::KernelCapId type)
{
	mType = type;
}

uint32_t pie::hac::KernelCapabilityEntry::getField() const
{
	return mField & getFieldMask();
}

void pie::hac::KernelCapabilityEntry::setField(uint32_t field)
{
	mField = field;
}
