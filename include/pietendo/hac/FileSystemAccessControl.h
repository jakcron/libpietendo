	/**
	 * @file FileSystemAccessControl.h
	 * @brief Declaration of pie::hac::FileSystemAccessControl
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/fac.h>

namespace pie { namespace hac {
	
class FileSystemAccessControl
{
public:
	struct sSaveDataOwnerId
	{
		pie::hac::fac::SaveDataOwnerIdAccessType access_type;
		uint64_t id;

		void operator=(const sSaveDataOwnerId& other)
		{
			access_type = other.access_type;
			id = other.id;
		}

		bool operator==(const sSaveDataOwnerId& other) const
		{
			return (access_type == other.access_type) \
				&& (id == other.id);
		}

		bool operator!=(const sSaveDataOwnerId& other) const
		{
			return !(*this == other);
		}
	}; 

	FileSystemAccessControl();
	FileSystemAccessControl(const FileSystemAccessControl& other);

	void operator=(const FileSystemAccessControl& other);
	bool operator==(const FileSystemAccessControl& other) const;
	bool operator!=(const FileSystemAccessControl& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* data, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	uint32_t getFormatVersion() const;
	void setFormatVersion(uint32_t version);

	const std::vector<pie::hac::fac::FsAccessFlag>& getFsAccess() const;
	void setFsAccess(const std::vector<pie::hac::fac::FsAccessFlag>& access);

	const std::vector<uint64_t>& getContentOwnerIdList() const;
	void setContentOwnerIdList(const std::vector<uint64_t>& list);

	const std::vector<sSaveDataOwnerId>& getSaveDataOwnerIdList() const;
	void setSaveDataOwnerIdList(const std::vector<sSaveDataOwnerId>& list);
private:
	const std::string kModuleName = "FILE_SYSTEM_ACCESS_CONTROL";

	// raw data
	tc::ByteData mRawBinary;

	// variables
	uint32_t mVersion;
	std::vector<pie::hac::fac::FsAccessFlag> mFsAccess;
	std::vector<uint64_t> mContentOwnerIdList;
	std::vector<sSaveDataOwnerId> mSaveDataOwnerIdList;
};

}} // namespace pie::hac