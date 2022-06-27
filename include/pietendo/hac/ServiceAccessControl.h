#pragma once
#include <nn/hac/ServiceAccessControlEntry.h>

namespace nn
{
namespace hac
{
	class ServiceAccessControl
	{
	public:
		ServiceAccessControl();
		ServiceAccessControl(const ServiceAccessControl& other);

		void operator=(const ServiceAccessControl& other);
		bool operator==(const ServiceAccessControl& other) const;
		bool operator!=(const ServiceAccessControl& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();
		const std::vector<ServiceAccessControlEntry>& getServiceList() const;
		void setServiceList(const std::vector<ServiceAccessControlEntry>& list);
	private:
		const std::string kModuleName = "SERVICE_ACCESS_CONTROL";

		// raw binary
		tc::ByteData mRawBinary;

		// variables
		std::vector<ServiceAccessControlEntry> mServices;
	};
}
}
