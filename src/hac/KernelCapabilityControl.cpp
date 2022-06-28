#include <pietendo/hac/KernelCapabilityControl.h>

pie::hac::KernelCapabilityControl::KernelCapabilityControl()
{}

pie::hac::KernelCapabilityControl::KernelCapabilityControl(const KernelCapabilityControl & other)
{
	*this = other;
}

void pie::hac::KernelCapabilityControl::operator=(const KernelCapabilityControl & other)
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

bool pie::hac::KernelCapabilityControl::operator==(const KernelCapabilityControl & other) const
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

bool pie::hac::KernelCapabilityControl::operator!=(const KernelCapabilityControl & other) const
{
	return !(*this == other);
}

void pie::hac::KernelCapabilityControl::toBytes()
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

void pie::hac::KernelCapabilityControl::fromBytes(const byte_t * data, size_t len)
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
			case (kc::KernelCapId_ThreadInfo) :
				threadInfoCaps.push_back(cap);
				break;
			case (kc::KernelCapId_EnableSystemCalls):
				systemCallCaps.push_back(cap);
				break;
			case (kc::KernelCapId_MemoryMap):
			case (kc::KernelCapId_IoMemoryMap):
				memoryMapCaps.push_back(cap);
				break;
			case (kc::KernelCapId_EnableInterrupts):
				interuptCaps.push_back(cap);
				break;
			case (kc::KernelCapId_MiscParams):
				miscParamCaps.push_back(cap);
				break;
			case (kc::KernelCapId_KernelVersion):
				kernelVersionCaps.push_back(cap);
				break;
			case (kc::KernelCapId_HandleTableSize):
				handleTableSizeCaps.push_back(cap);
				break;
			case (kc::KernelCapId_MiscFlags):
				miscFlagsCaps.push_back(cap);
				break;
			case (kc::KernelCapId_Stubbed):
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

const tc::ByteData& pie::hac::KernelCapabilityControl::getBytes() const
{
	return mRawBinary;
}

void pie::hac::KernelCapabilityControl::clear()
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

const pie::hac::ThreadInfoHandler & pie::hac::KernelCapabilityControl::getThreadInfo() const
{
	return mThreadInfo;
}

pie::hac::ThreadInfoHandler & pie::hac::KernelCapabilityControl::getThreadInfo()
{
	return mThreadInfo;
}

const pie::hac::SystemCallHandler & pie::hac::KernelCapabilityControl::getSystemCalls() const
{
	return mSystemCalls;
}

pie::hac::SystemCallHandler & pie::hac::KernelCapabilityControl::getSystemCalls()
{
	return mSystemCalls;
}

const pie::hac::MemoryMappingHandler & pie::hac::KernelCapabilityControl::getMemoryMaps() const
{
	return mMemoryMap;
}

pie::hac::MemoryMappingHandler & pie::hac::KernelCapabilityControl::getMemoryMaps()
{
	return mMemoryMap;
}

const pie::hac::InteruptHandler & pie::hac::KernelCapabilityControl::getInterupts() const
{
	return mInterupts;
}

pie::hac::InteruptHandler & pie::hac::KernelCapabilityControl::getInterupts()
{
	return mInterupts;
}

const pie::hac::MiscParamsHandler & pie::hac::KernelCapabilityControl::getMiscParams() const
{
	return mMiscParams;
}

pie::hac::MiscParamsHandler & pie::hac::KernelCapabilityControl::getMiscParams()
{
	return mMiscParams;
}

const pie::hac::KernelVersionHandler & pie::hac::KernelCapabilityControl::getKernelVersion() const
{
	return mKernelVersion;
}

pie::hac::KernelVersionHandler & pie::hac::KernelCapabilityControl::getKernelVersion()
{
	return mKernelVersion;
}

const pie::hac::HandleTableSizeHandler & pie::hac::KernelCapabilityControl::getHandleTableSize() const
{
	return mHandleTableSize;
}

pie::hac::HandleTableSizeHandler & pie::hac::KernelCapabilityControl::getHandleTableSize()
{
	return mHandleTableSize;
}

const pie::hac::MiscFlagsHandler & pie::hac::KernelCapabilityControl::getMiscFlags() const
{
	return mMiscFlags;
}

pie::hac::MiscFlagsHandler & pie::hac::KernelCapabilityControl::getMiscFlags()
{
	return mMiscFlags;
}