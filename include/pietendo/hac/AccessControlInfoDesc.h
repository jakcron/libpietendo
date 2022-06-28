	/**
	 * @file AccessControlInfoDesc.h
	 * @brief Declaration of pie::hac::AccessControlInfoDesc
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
	
class AccessControlInfoDesc
{
public:
	struct sProgramIdRestrict
	{
		uint64_t min;
		uint64_t max;

		void operator=(const sProgramIdRestrict& other)
		{
			min = other.min;
			max = other.max;
		}

		bool operator==(const sProgramIdRestrict& other) const
		{
			return (min == other.min) \
				&& (max == other.max);
		}

		bool operator!=(const sProgramIdRestrict& other) const
		{
			return !(*this == other);
		}
	};

	AccessControlInfoDesc();
	AccessControlInfoDesc(const AccessControlInfoDesc& other);

	void operator=(const AccessControlInfoDesc& other);
	bool operator==(const AccessControlInfoDesc& other) const;
	bool operator!=(const AccessControlInfoDesc& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* data, size_t len);
	const tc::ByteData& getBytes() const;

	void generateSignature(const tc::crypto::RsaKey& key);
	void validateSignature(const tc::crypto::RsaKey& key) const;

	// variables
	void clear();

	const tc::crypto::RsaKey& getContentArchiveHeaderSignature2Key() const;
	void setContentArchiveHeaderSignature2Key(const tc::crypto::RsaKey& key);

	bool getProductionFlag() const;
	void setProductionFlag(bool flag);

	bool getUnqualifiedApprovalFlag() const;
	void setUnqualifiedApprovalFlag(bool flag);

	pie::hac::aci::MemoryRegion getMemoryRegion() const;
	void setMemoryRegion(pie::hac::aci::MemoryRegion memory_region);

	const sProgramIdRestrict& getProgramIdRestrict() const;
	void setProgramIdRestrict(const sProgramIdRestrict& pid_restrict);

	const pie::hac::FileSystemAccessControl& getFileSystemAccessControl() const;
	void setFileSystemAccessControl(const FileSystemAccessControl& fac);

	const pie::hac::ServiceAccessControl& getServiceAccessControl() const;
	void setServiceAccessControl(const ServiceAccessControl& sac);

	const pie::hac::KernelCapabilityControl& getKernelCapabilities() const;
	void setKernelCapabilities(const KernelCapabilityControl& kc);
private:
	const std::string kModuleName = "ACCESS_CONTROL_INFO_DESC_BINARY";

	// raw data
	tc::ByteData mRawBinary;

	// variables
	tc::crypto::RsaKey mContentArchiveHeaderSignature2Key;
	bool mProductionFlag;
	bool mUnqualifiedApprovalFlag;
	pie::hac::aci::MemoryRegion mMemoryRegion;
	sProgramIdRestrict mProgramIdRestrict;
	pie::hac::FileSystemAccessControl mFileSystemAccessControl;
	pie::hac::ServiceAccessControl mServiceAccessControl;
	pie::hac::KernelCapabilityControl mKernelCapabilities;
};

}} // namespace pie::hac