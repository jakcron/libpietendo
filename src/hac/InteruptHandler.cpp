#include <pietendo/hac/InteruptHandler.h>

pie::hac::InteruptHandler::InteruptHandler() :
	mIsSet(false),
	mInterupts()
{}

void pie::hac::InteruptHandler::operator=(const InteruptHandler & other)
{
	mIsSet = other.mIsSet;
	mInterupts = other.mInterupts;
}

bool pie::hac::InteruptHandler::operator==(const InteruptHandler & other) const
{
	return (mIsSet == other.mIsSet) \
		&& (mInterupts == other.mInterupts);
}

bool pie::hac::InteruptHandler::operator!=(const InteruptHandler & other) const
{
	return !(*this == other);
}

void pie::hac::InteruptHandler::importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps)
{
	if (caps.size() == 0)
		return;
	// convert to interupts
	std::vector<InteruptEntry> interupts;
	for (size_t i = 0; i < caps.size(); i++)
	{
		interupts.push_back(InteruptEntry(caps[i]));
	}

	mInterupts.clear();
	for (size_t i = 0; i < interupts.size(); i++)
	{
		// weird condition for first interupt
		if (interupts[i][1] == 0 && i == 0)
		{
			mInterupts.push_back(interupts[i][0]);
			continue;
		}

		// we found a stub
		if (interupts[i][0] == InteruptEntry::kInteruptMax && interupts[i][1] == InteruptEntry::kInteruptMax)
		{
			continue;
		}

		// add interupts
		for (size_t j = 0; j < mInterupts.size(); j++)
		{
			if (mInterupts[j] == interupts[i][0] || mInterupts[j] == interupts[i][1])
			{
				throw tc::Exception(kModuleName, "Interupt already added");
			}
		}
		mInterupts.push_back(interupts[i][0]);
		mInterupts.push_back(interupts[i][1]);
	}

	mIsSet = true;
}

void pie::hac::InteruptHandler::exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const
{
	if (isSet() == false)
		return;

	size_t i = 0;
	if (mInterupts.size() % 2)
	{
		caps.push_back(InteruptEntry(mInterupts[i], 0).getKernelCapability());
		i++;
	}
	for (; i < mInterupts.size(); i += 2)
	{
		if (mInterupts[i] == InteruptEntry::kInteruptMax)
		{
			caps.push_back(InteruptEntry(InteruptEntry::kInteruptMax, InteruptEntry::kInteruptMax).getKernelCapability());
		}
		caps.push_back(InteruptEntry(mInterupts[i], mInterupts[i+1]).getKernelCapability());
		if (mInterupts[i+1] == InteruptEntry::kInteruptMax)
		{
			caps.push_back(InteruptEntry(InteruptEntry::kInteruptMax, InteruptEntry::kInteruptMax).getKernelCapability());
		}

	}
}

void pie::hac::InteruptHandler::clear()
{
	mIsSet = false;
	mInterupts.clear();
}

bool pie::hac::InteruptHandler::isSet() const
{
	return mIsSet;
}

const std::vector<uint16_t>& pie::hac::InteruptHandler::getInteruptList() const
{
	return mInterupts;
}

void pie::hac::InteruptHandler::setInteruptList(const std::vector<uint16_t>& interupts)
{
	mInterupts.clear();
	for (size_t i = 0; i < interupts.size(); i++)
	{
		for (size_t j = 0; j < mInterupts.size(); j++)
		{
			if (mInterupts[j] == interupts[i])
			{
				throw tc::Exception(kModuleName, "Interupt already added");
			}
		}
		mInterupts.push_back(interupts[i]);
	}

	mIsSet = true;
}