	/**
	 * @file ServiceAccessControlEntry.h
	 * @brief Declaration of pie::hac::ServiceAccessControlEntry
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {
	
class ServiceAccessControlEntry
{
public:
	ServiceAccessControlEntry();
	ServiceAccessControlEntry(const std::string& name, bool isServer);
	ServiceAccessControlEntry(const ServiceAccessControlEntry& other);

	void operator=(const ServiceAccessControlEntry& other);
	bool operator==(const ServiceAccessControlEntry& other) const;
	bool operator!=(const ServiceAccessControlEntry& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();
	bool isServer() const;
	void setIsServer(bool isServer);
	const std::string& getName() const;
	void setName(const std::string& name);
private:
	const std::string kModuleName = "SERVICE_ACCESS_CONTROL_ENTRY";
	static const size_t kMaxServiceNameLen = 8;

	enum ServiceAccessControlEntryFlag
	{
		SAC_IS_SERVER = (1 << 7),
		SAC_NAME_LEN_MASK = (1 << 7) - 1
	};

	// raw binary
	tc::ByteData mRawBinary;

	// variables
	bool mIsServer;
	std::string mName;
};

}} // namespace pie::hac