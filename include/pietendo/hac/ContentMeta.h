	/**
	 * @file ContentMeta.h
	 * @brief Declaration of pie::hac::ContentMeta
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/cnmt.h>
#include <pietendo/hac/ContentInfo.h>
#include <pietendo/hac/ContentMetaInfo.h>
#include <pietendo/hac/ApplicationMetaExtendedHeader.h>
#include <pietendo/hac/PatchMetaExtendedHeader.h>
#include <pietendo/hac/AddOnContentMetaExtendedHeader.h>
#include <pietendo/hac/DeltaMetaExtendedHeader.h>
#include <pietendo/hac/SystemUpdateMetaExtendedHeader.h>
#include <pietendo/hac/SystemUpdateMetaExtendedData.h>

#include <tc/NotImplementedException.h>

namespace pie { namespace hac {
	
class ContentMeta
{
public:
	ContentMeta();
	ContentMeta(const ContentMeta& other);

	void operator=(const ContentMeta& other);
	bool operator==(const ContentMeta& other) const;
	bool operator!=(const ContentMeta& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	uint64_t getTitleId() const;
	void setTitleId(uint64_t title_id);

	uint32_t getTitleVersion() const;
	void setTitleVersion(uint32_t version);

	pie::hac::cnmt::ContentMetaType getContentMetaType() const;
	void setContentMetaType(pie::hac::cnmt::ContentMetaType type);

	const std::vector<pie::hac::cnmt::ContentMetaAttributeFlag>& getAttribute() const;
	void setAttribute(const std::vector<pie::hac::cnmt::ContentMetaAttributeFlag>& attr);

	pie::hac::cnmt::StorageId getStorageId() const;
	void setStorageId(pie::hac::cnmt::StorageId storage_id);

	pie::hac::cnmt::ContentInstallType getContentInstallType() const;
	void setContentInstallType(pie::hac::cnmt::ContentInstallType install_type);

	const std::vector<cnmt::InstallStateFlag>& getInstallState() const;
	void setInstallState(const std::vector<cnmt::InstallStateFlag>& install_state);

	uint32_t getRequiredDownloadSystemVersion() const;
	void setRequiredDownloadSystemVersion(uint32_t version);

	const pie::hac::ApplicationMetaExtendedHeader& getApplicationMetaExtendedHeader() const;
	void setApplicationMetaExtendedHeader(const pie::hac::ApplicationMetaExtendedHeader& exhdr);

	const pie::hac::PatchMetaExtendedHeader& getPatchMetaExtendedHeader() const;
	void setPatchMetaExtendedHeader(const pie::hac::PatchMetaExtendedHeader& exhdr);

	const pie::hac::AddOnContentMetaExtendedHeader& getAddOnContentMetaExtendedHeader() const;
	void setAddOnContentMetaExtendedHeader(const pie::hac::AddOnContentMetaExtendedHeader& exhdr);

	const pie::hac::DeltaMetaExtendedHeader& getDeltaMetaExtendedHeader() const;
	void setDeltaMetaExtendedHeader(const pie::hac::DeltaMetaExtendedHeader& exhdr);

	const pie::hac::SystemUpdateMetaExtendedHeader& getSystemUpdateMetaExtendedHeader() const;
	void setSystemUpdateMetaExtendedHeader(const pie::hac::SystemUpdateMetaExtendedHeader& exhdr);

	const std::vector<pie::hac::ContentInfo>& getContentInfo() const;
	void setContentInfo(const std::vector<pie::hac::ContentInfo>& info);

	const std::vector<pie::hac::ContentMetaInfo>& getContentMetaInfo() const;
	void setContentMetaInfo(const std::vector<pie::hac::ContentMetaInfo>& info);

	const tc::ByteData& getPatchMetaExtendedData() const;
	void setPatchMetaExtendedData(const tc::ByteData& exdata);

	const tc::ByteData& getDeltaMetaExtendedData() const;
	void setDeltaMetaExtendedData(const tc::ByteData& exdata);

	const pie::hac::SystemUpdateMetaExtendedData& getSystemUpdateMetaExtendedData() const;
	void setSystemUpdateMetaExtendedData(const pie::hac::SystemUpdateMetaExtendedData& exdata);

	const pie::hac::cnmt::digest_t& getDigest() const;
	void setDigest(const pie::hac::cnmt::digest_t& digest);

private:
	const std::string kModuleName = "CONTENT_META";

	// binary blob
	tc::ByteData mRawBinary;

	// variables
	uint64_t mTitleId;
	uint32_t mTitleVersion;
	pie::hac::cnmt::ContentMetaType mType;
	std::vector<pie::hac::cnmt::ContentMetaAttributeFlag> mAttribute;
	pie::hac::cnmt::StorageId mStorageId;
	pie::hac::cnmt::ContentInstallType mContentInstallType;
	std::vector<cnmt::InstallStateFlag> mInstallState;
	uint32_t mRequiredDownloadSystemVersion;

	pie::hac::ApplicationMetaExtendedHeader mApplicationMetaExtendedHeader;
	pie::hac::PatchMetaExtendedHeader mPatchMetaExtendedHeader;
	pie::hac::AddOnContentMetaExtendedHeader mAddOnContentMetaExtendedHeader;
	pie::hac::DeltaMetaExtendedHeader mDeltaMetaExtendedHeader;
	pie::hac::SystemUpdateMetaExtendedHeader mSystemUpdateMetaExtendedHeader;

	std::vector<ContentInfo> mContentInfo;
	std::vector<ContentMetaInfo> mContentMetaInfo;

	tc::ByteData mPatchMetaExtendedData;
	tc::ByteData mDeltaMetaExtendedData;
	pie::hac::SystemUpdateMetaExtendedData mSystemUpdateMetaExtendedData;		
	
	pie::hac::cnmt::digest_t mDigest;

	inline size_t getExtendedHeaderOffset() const { return sizeof(sContentMetaHeader); }
	inline size_t getContentInfoOffset(size_t exhdrSize) const { return getExtendedHeaderOffset() + exhdrSize; }
	inline size_t getContentMetaInfoOffset(size_t exhdrSize, size_t contentInfoNum) const { return getContentInfoOffset(exhdrSize) + contentInfoNum * sizeof(sContentInfo); }
	inline size_t getExtendedDataOffset(size_t exhdrSize, size_t contentInfoNum, size_t contentMetaNum) const { return getContentMetaInfoOffset(exhdrSize, contentInfoNum) + contentMetaNum * sizeof(sContentMetaInfo); }
	inline size_t getDigestOffset(size_t exhdrSize, size_t contentInfoNum, size_t contentMetaNum, size_t exdataSize) const { return getExtendedDataOffset(exhdrSize, contentInfoNum, contentMetaNum) + exdataSize; }
	inline size_t getTotalSize(size_t exhdrSize, size_t contentInfoNum, size_t contentMetaNum, size_t exdataSize) const { return getDigestOffset(exhdrSize, contentInfoNum, contentMetaNum, exdataSize) + cnmt::kDigestLen; }

	bool validateExtendedHeaderSize(pie::hac::cnmt::ContentMetaType type, size_t exhdrSize) const;
	size_t getExtendedDataSize(pie::hac::cnmt::ContentMetaType type, const byte_t* data) const;
	void validateBinary(const byte_t* bytes, size_t len) const;
};

}} // namespace pie::hac