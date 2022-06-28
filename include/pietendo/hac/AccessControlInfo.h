	/**
	 * @file AccessControlInfo.h
	 * @brief Declaration of pie::hac::AccessControlInfo
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/aci.h>
#include <pietendo/hac/FileSystemAccessControl.h>
#include <pietendo/hac/ServiceAccessControl.h>
#include <pietendo/hac/KernelCapabilityControl.h>

namespace pie { namespace hac {

class AccessControlInfo
{
public:
	AccessControlInfo();
	AccessControlInfo(const AccessControlInfo& other);

	void operator=(const AccessControlInfo& other);
	bool operator==(const AccessControlInfo& other) const;
	bool operator!=(const AccessControlInfo& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* data, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	uint64_t getProgramId() const;
	void setProgramId(uint64_t program_id);

	const pie::hac::FileSystemAccessControl& getFileSystemAccessControl() const;
	void setFileSystemAccessControl(const FileSystemAccessControl& fac);

	const pie::hac::ServiceAccessControl& getServiceAccessControl() const;
	void setServiceAccessControl(const ServiceAccessControl& sac);

	const pie::hac::KernelCapabilityControl& getKernelCapabilities() const;
	void setKernelCapabilities(const KernelCapabilityControl& kc);
private:
	const std::string kModuleName = "ACCESS_CONTROL_INFO_BINARY";

	// raw data
	tc::ByteData mRawBinary;

	// variables
	uint64_t mProgramId;
	pie::hac::FileSystemAccessControl mFileSystemAccessControl;
	pie::hac::ServiceAccessControl mServiceAccessControl;
	pie::hac::KernelCapabilityControl mKernelCapabilities;
};

}} // namespace pie::hac