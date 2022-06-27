#pragma once
#include <nn/hac/define/meta.h>
#include <nn/hac/AccessControlInfo.h>
#include <nn/hac/AccessControlInfoDesc.h>

namespace nn
{
namespace hac
{
	class Meta
	{
	public:
		Meta();
		Meta(const Meta& other);

		void operator=(const Meta& other);
		bool operator==(const Meta& other) const;
		bool operator!=(const Meta& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		byte_t getAccessControlInfoDescKeyGeneration() const;
		void setAccessControlInfoDescKeyGeneration(byte_t key_generation);

		bool getIs64BitInstructionFlag() const;
		void setIs64BitInstructionFlag(bool flag);

		meta::ProcessAddressSpace getProcessAddressSpace() const;
		void setProcessAddressSpace(meta::ProcessAddressSpace type);

		bool getOptimizeMemoryAllocationFlag() const;
		void setOptimizeMemoryAllocationFlag(bool flag);

		byte_t getMainThreadPriority() const;
		void setMainThreadPriority(byte_t priority);

		byte_t getMainThreadCpuId() const;
		void setMainThreadCpuId(byte_t cpu_id);

		uint32_t getSystemResourceSize() const;
		void setSystemResourceSize(uint32_t size);

		uint32_t getVersion() const;
		void setVersion(uint32_t version);

		uint32_t getMainThreadStackSize() const;
		void setMainThreadStackSize(uint32_t size);

		const std::string& getName() const;
		void setName(const std::string& name);

		const std::string& getProductCode() const;
		void setProductCode(const std::string& product_code);

		const AccessControlInfo& getAccessControlInfo() const;
		void setAccessControlInfo(const AccessControlInfo& aci);

		const AccessControlInfoDesc& getAccessControlInfoDesc() const;
		void setAccessControlInfoDesc(const AccessControlInfoDesc& aci_desc);
	private:
		const std::string kModuleName = "META";

		// raw binary
		tc::ByteData mRawBinary;

		// variables
		byte_t mAccessControlInfoDescKeyGeneration;
		bool mIs64BitInstructionFlag;
		meta::ProcessAddressSpace mProcessAddressSpace;
		bool mOptimizeMemoryAllocationFlag;
		byte_t mMainThreadPriority;
		byte_t mMainThreadCpuId;
		uint32_t mSystemResourceSize;
		uint32_t mVersion;
		uint32_t mMainThreadStackSize;
		std::string mName;
		std::string mProductCode;
		AccessControlInfo mAccessControlInfo;
		AccessControlInfoDesc mAccessControlInfoDesc;
	};
}
}
