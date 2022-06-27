#include <nn/hac/KernelCapabilityControl.h>

nn::hac::KernelCapabilityControl::KernelCapabilityControl()
{}

nn::hac::KernelCapabilityControl::KernelCapabilityControl(const KernelCapabilityControl & other)
{
	*this = other;
}

void nn::hac::KernelCapabilityControl::operator=(const KernelCapabilityControl & other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mThreadInfo = other.mThreadInfo;
	mSystemCalls = other.mSystemCalls;
	mMemoryMap = other.mMemoryMap;
	mInterupts = other.mInterupts;
	mMiscParams = other.mMiscParams;
	mKernelVersion = other.mKernelVersion;
	mHandleTableSize = other.mHandleTableSize;
	mMiscFlags = other.mMiscFlags;
}

bool nn::hac::KernelCapabilityControl::operator==(const KernelCapabilityControl & other) const
{
	return (mThreadInfo == other.mThreadInfo) \
		&& (mSystemCalls == other.mSystemCalls) \
		&& (mMemoryMap == other.mMemoryMap) \
		&& (mInterupts == other.mInterupts) \
		&& (mMiscParams == other.mMiscParams) \
		&& (mKernelVersion == other.mKernelVersion) \
		&& (mHandleTableSize == other.mHandleTableSize) \
		&& (mMiscFlags == other.mMiscFlags);
}

bool nn::hac::KernelCapabilityControl::operator!=(const KernelCapabilityControl & other) const
{
	return !(*this == other);
}

void nn::hac::KernelCapabilityControl::toBytes()
{
	std::vector<KernelCapabilityEntry> caps;

	// get kernel capabiliteis
	mThreadInfo.exportKernelCapabilityList(caps);
	mSystemCalls.exportKernelCapabilityList(caps);
	mMemoryMap.exportKernelCapabilityList(caps);
	mInterupts.exportKernelCapabilityList(caps);
	mMiscParams.exportKernelCapabilityList(caps);
	mKernelVersion.exportKernelCapabilityList(caps);
	mHandleTableSize.exportKernelCapabilityList(caps);
	mMiscFlags.exportKernelCapabilityList(caps);

	// allocate memory
	mRawBinary = tc::ByteData(caps.size() * sizeof(uint32_t));

	// write to binary
	tc::bn::le32<uint32_t>* raw_caps = (tc::bn::le32<uint32_t>*)mRawBinary.data();
	for (size_t i = 0; i < caps.size(); i++)
	{
		raw_caps[i].wrap(caps[i].getCap());
	}
}

void nn::hac::KernelCapabilityControl::fromBytes(const byte_t * data, size_t len)
{
	if ((len % sizeof(uint32_t)) != 0)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "KernelCapabilityEntry list must be aligned to 4 bytes");
	}

	// save copy of KernelCapabilityControl
	mRawBinary = tc::ByteData(len);
	memcpy(mRawBinary.data(), data, len);

	std::vector<KernelCapabilityEntry> threadInfoCaps;
	std::vector<KernelCapabilityEntry> systemCallCaps;
	std::vector<KernelCapabilityEntry> memoryMapCaps;
	std::vector<KernelCapabilityEntry> interuptCaps;
	std::vector<KernelCapabilityEntry> miscParamCaps;
	std::vector<KernelCapabilityEntry> kernelVersionCaps;
	std::vector<KernelCapabilityEntry> handleTableSizeCaps;
	std::vector<KernelCapabilityEntry> miscFlagsCaps;

	const tc::bn::le32<uint32_t>* raw_caps = (const tc::bn::le32<uint32_t>*)mRawBinary.data();
	size_t cap_num = mRawBinary.size() / sizeof(uint32_t);
	KernelCapabilityEntry cap;
	for (size_t i = 0; i < cap_num; i++)
	{
		cap.setCap(raw_caps[i].unwrap());
		switch (cap.getType())
		{
			case (kc::KernelCapId::ThreadInfo) :
				threadInfoCaps.push_back(cap);
				break;
			case (kc::KernelCapId::EnableSystemCalls):
				systemCallCaps.push_back(cap);
				break;
			case (kc::KernelCapId::MemoryMap):
			case (kc::KernelCapId::IoMemoryMap):
				memoryMapCaps.push_back(cap);
				break;
			case (kc::KernelCapId::EnableInterrupts):
				interuptCaps.push_back(cap);
				break;
			case (kc::KernelCapId::MiscParams):
				miscParamCaps.push_back(cap);
				break;
			case (kc::KernelCapId::KernelVersion):
				kernelVersionCaps.push_back(cap);
				break;
			case (kc::KernelCapId::HandleTableSize):
				handleTableSizeCaps.push_back(cap);
				break;
			case (kc::KernelCapId::MiscFlags):
				miscFlagsCaps.push_back(cap);
				break;
			case (kc::KernelCapId::Stubbed):
				// ignore stubbed
				break;
			default:
				throw tc::ArgumentOutOfRangeException(kModuleName, "Unsupported kernel capability type");
		}
	}

	mThreadInfo.importKernelCapabilityList(threadInfoCaps);
	mSystemCalls.importKernelCapabilityList(systemCallCaps);
	mMemoryMap.importKernelCapabilityList(memoryMapCaps);
	mInterupts.importKernelCapabilityList(interuptCaps);
	mMiscParams.importKernelCapabilityList(miscParamCaps);
	mKernelVersion.importKernelCapabilityList(kernelVersionCaps);
	mHandleTableSize.importKernelCapabilityList(handleTableSizeCaps);
	mMiscFlags.importKernelCapabilityList(miscFlagsCaps);
}

const tc::ByteData& nn::hac::KernelCapabilityControl::getBytes() const
{
	return mRawBinary;
}

void nn::hac::KernelCapabilityControl::clear()
{
	mRawBinary = tc::ByteData();
	mThreadInfo.clear();
	mSystemCalls.clear();
	mMemoryMap.clear();
	mInterupts.clear();
	mMiscParams.clear();
	mKernelVersion.clear();
	mHandleTableSize.clear();
	mMiscFlags.clear();
}

const nn::hac::ThreadInfoHandler & nn::hac::KernelCapabilityControl::getThreadInfo() const
{
	return mThreadInfo;
}

nn::hac::ThreadInfoHandler & nn::hac::KernelCapabilityControl::getThreadInfo()
{
	return mThreadInfo;
}

const nn::hac::SystemCallHandler & nn::hac::KernelCapabilityControl::getSystemCalls() const
{
	return mSystemCalls;
}

nn::hac::SystemCallHandler & nn::hac::KernelCapabilityControl::getSystemCalls()
{
	return mSystemCalls;
}

const nn::hac::MemoryMappingHandler & nn::hac::KernelCapabilityControl::getMemoryMaps() const
{
	return mMemoryMap;
}

nn::hac::MemoryMappingHandler & nn::hac::KernelCapabilityControl::getMemoryMaps()
{
	return mMemoryMap;
}

const nn::hac::InteruptHandler & nn::hac::KernelCapabilityControl::getInterupts() const
{
	return mInterupts;
}

nn::hac::InteruptHandler & nn::hac::KernelCapabilityControl::getInterupts()
{
	return mInterupts;
}

const nn::hac::MiscParamsHandler & nn::hac::KernelCapabilityControl::getMiscParams() const
{
	return mMiscParams;
}

nn::hac::MiscParamsHandler & nn::hac::KernelCapabilityControl::getMiscParams()
{
	return mMiscParams;
}

const nn::hac::KernelVersionHandler & nn::hac::KernelCapabilityControl::getKernelVersion() const
{
	return mKernelVersion;
}

nn::hac::KernelVersionHandler & nn::hac::KernelCapabilityControl::getKernelVersion()
{
	return mKernelVersion;
}

const nn::hac::HandleTableSizeHandler & nn::hac::KernelCapabilityControl::getHandleTableSize() const
{
	return mHandleTableSize;
}

nn::hac::HandleTableSizeHandler & nn::hac::KernelCapabilityControl::getHandleTableSize()
{
	return mHandleTableSize;
}

const nn::hac::MiscFlagsHandler & nn::hac::KernelCapabilityControl::getMiscFlags() const
{
	return mMiscFlags;
}

nn::hac::MiscFlagsHandler & nn::hac::KernelCapabilityControl::getMiscFlags()
{
	return mMiscFlags;
}