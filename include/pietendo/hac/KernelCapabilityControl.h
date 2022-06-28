	/**
	 * @file KernelCapabilityControl.h
	 * @brief Declaration of pie::hac::KernelCapabilityControl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/ThreadInfoHandler.h>
#include <pietendo/hac/SystemCallHandler.h>
#include <pietendo/hac/MemoryMappingHandler.h>
#include <pietendo/hac/InteruptHandler.h>
#include <pietendo/hac/MiscParamsHandler.h>
#include <pietendo/hac/KernelVersionHandler.h>
#include <pietendo/hac/HandleTableSizeHandler.h>
#include <pietendo/hac/MiscFlagsHandler.h>

namespace pie { namespace hac {
	
class KernelCapabilityControl
{
public:
	KernelCapabilityControl();
	KernelCapabilityControl(const KernelCapabilityControl& other);

	void operator=(const KernelCapabilityControl& other);
	bool operator==(const KernelCapabilityControl& other) const;
	bool operator!=(const KernelCapabilityControl& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	virtual const tc::ByteData& getBytes() const;

	// variables (consider further abstraction?)
	void clear();
	const ThreadInfoHandler& getThreadInfo() const;
	ThreadInfoHandler& getThreadInfo();

	const SystemCallHandler& getSystemCalls() const;
	SystemCallHandler& getSystemCalls();

	const MemoryMappingHandler& getMemoryMaps() const;
	MemoryMappingHandler& getMemoryMaps();

	const InteruptHandler& getInterupts() const;
	InteruptHandler& getInterupts();

	const MiscParamsHandler& getMiscParams() const;
	MiscParamsHandler& getMiscParams();

	const KernelVersionHandler& getKernelVersion() const;
	KernelVersionHandler& getKernelVersion();

	const HandleTableSizeHandler& getHandleTableSize() const;
	HandleTableSizeHandler& getHandleTableSize();

	const MiscFlagsHandler& getMiscFlags() const;
	MiscFlagsHandler& getMiscFlags();

private:
	const std::string kModuleName = "KERNEL_CAPABILITY_CONTROL";

	// raw binary
	tc::ByteData mRawBinary;

	// variables
	ThreadInfoHandler mThreadInfo;
	SystemCallHandler mSystemCalls;
	MemoryMappingHandler mMemoryMap;
	InteruptHandler mInterupts;
	MiscParamsHandler mMiscParams;
	KernelVersionHandler mKernelVersion;
	HandleTableSizeHandler mHandleTableSize;
	MiscFlagsHandler mMiscFlags;
};

}} // namespace pie::hac