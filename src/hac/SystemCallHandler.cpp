#include <pietendo/hac/SystemCallHandler.h>
#include <pietendo/hac/SystemCallEntry.h>

pie::hac::SystemCallHandler::SystemCallHandler() :
	mIsSet(false),
	mSystemCallIds()
{}

void pie::hac::SystemCallHandler::operator=(const SystemCallHandler & other)
{
	mIsSet = other.mIsSet;
	mSystemCallIds = other.mSystemCallIds;
}

bool pie::hac::SystemCallHandler::operator==(const SystemCallHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mSystemCallIds == other.mSystemCallIds);
}

bool pie::hac::SystemCallHandler::operator!=(const SystemCallHandler & other) const
{
	return !(*this == other);
}

void pie::hac::SystemCallHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
{
	if (caps.size() == 0)
		return;

	SystemCallEntry entry;

	uint8_t syscallUpper, syscall_id;
	for (size_t i = 0; i < caps.size(); i++)
	{
		entry.setKernelCapability(caps[i]);
		syscallUpper = byte_t(kEntrySyscallCount * entry.getSystemCallUpperBits());
		for (uint8_t j = 0; j < kEntrySyscallCount; j++)
		{
			syscall_id = syscallUpper + j;
			if (((entry.getSystemCallLowerBits() >> j) & 1) == 1)
			{
				mSystemCallIds.set(syscall_id);
			}
		}
	}


	mIsSet = true;
}

void pie::hac::SystemCallHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	SystemCallEntry entries[kSyscallTotalEntryNum];
	for (size_t i = 0; i < kSyscallTotalEntryNum; i++)
	{
		entries[i].setSystemCallUpperBits((uint32_t)i);
		entries[i].setSystemCallLowerBits(0);
	}

	for (size_t syscall_id = 0; syscall_id < mSystemCallIds.size(); syscall_id++)
	{
		if (mSystemCallIds.test(syscall_id) == false)
			continue;

		entries[syscall_id / kEntrySyscallCount].setSystemCallLowerBits(entries[syscall_id / kEntrySyscallCount].getSystemCallLowerBits() | (1 << syscall_id % kEntrySyscallCount));
	}

	for (size_t i = 0; i < kSyscallTotalEntryNum; i++)
	{
		if (entries[i].getSystemCallLowerBits() != 0)
		{
			caps.push_back(entries[i].getKernelCapability());
		}
	}
}

void pie::hac::SystemCallHandler::clear()
{
	mIsSet = false;
	mSystemCallIds.reset();
}

bool pie::hac::SystemCallHandler::isSet() const
{
	return mIsSet;
}

const pie::hac::kc::SystemCallIds& pie::hac::SystemCallHandler::getSystemCallIds() const
{
	return mSystemCallIds;
}

void pie::hac::SystemCallHandler::setSystemCallIds(const pie::hac::kc::SystemCallIds& syscall_ids)
{
	mSystemCallIds = syscall_ids;
	mIsSet = true;
}