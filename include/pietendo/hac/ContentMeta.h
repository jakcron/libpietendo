#pragma once
#include <nn/hac/define/cnmt.h>
#include <nn/hac/ContentInfo.h>
#include <nn/hac/ContentMetaInfo.h>
#include <nn/hac/ApplicationMetaExtendedHeader.h>
#include <nn/hac/PatchMetaExtendedHeader.h>
#include <nn/hac/AddOnContentMetaExtendedHeader.h>
#include <nn/hac/DeltaMetaExtendedHeader.h>
#include <nn/hac/SystemUpdateMetaExtendedHeader.h>
#include <nn/hac/SystemUpdateMetaExtendedData.h>

#include <tc/NotImplementedException.h>

namespace nn
{
namespace hac
{
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

		nn::hac::cnmt::ContentMetaType getContentMetaType() const;
		void setContentMetaType(nn::hac::cnmt::ContentMetaType type);

		const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& getAttribute() const;
		void setAttribute(const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& attr);

		nn::hac::cnmt::StorageId getStorageId() const;
		void setStorageId(nn::hac::cnmt::StorageId storage_id);

		nn::hac::cnmt::ContentInstallType getContentInstallType() const;
		void setContentInstallType(nn::hac::cnmt::ContentInstallType install_type);

		const std::vector<cnmt::InstallStateFlag>& getInstallState() const;
		void setInstallState(const std::vector<cnmt::InstallStateFlag>& install_state);

		uint32_t getRequiredDownloadSystemVersion() const;
		void setRequiredDownloadSystemVersion(uint32_t version);

		const nn::hac::ApplicationMetaExtendedHeader& getApplicationMetaExtendedHeader() const;
		void setApplicationMetaExtendedHeader(const nn::hac::ApplicationMetaExtendedHeader& exhdr);

		const nn::hac::PatchMetaExtendedHeader& getPatchMetaExtendedHeader() const;
		void setPatchMetaExtendedHeader(const nn::hac::PatchMetaExtendedHeader& exhdr);

		const nn::hac::AddOnContentMetaExtendedHeader& getAddOnContentMetaExtendedHeader() const;
		void setAddOnContentMetaExtendedHeader(const nn::hac::AddOnContentMetaExtendedHeader& exhdr);

		const nn::hac::DeltaMetaExtendedHeader& getDeltaMetaExtendedHeader() const;
		void setDeltaMetaExtendedHeader(const nn::hac::DeltaMetaExtendedHeader& exhdr);

		const nn::hac::SystemUpdateMetaExtendedHeader& getSystemUpdateMetaExtendedHeader() const;
		void setSystemUpdateMetaExtendedHeader(const nn::hac::SystemUpdateMetaExtendedHeader& exhdr);

		const std::vector<nn::hac::ContentInfo>& getContentInfo() const;
		void setContentInfo(const std::vector<nn::hac::ContentInfo>& info);

		const std::vector<nn::hac::ContentMetaInfo>& getContentMetaInfo() const;
		void setContentMetaInfo(const std::vector<nn::hac::ContentMetaInfo>& info);

		const tc::ByteData& getPatchMetaExtendedData() const;
		void setPatchMetaExtendedData(const tc::ByteData& exdata);

		const tc::ByteData& getDeltaMetaExtendedData() const;
		void setDeltaMetaExtendedData(const tc::ByteData& exdata);

		const nn::hac::SystemUpdateMetaExtendedData& getSystemUpdateMetaExtendedData() const;
		void setSystemUpdateMetaExtendedData(const nn::hac::SystemUpdateMetaExtendedData& exdata);

		const nn::hac::cnmt::digest_t& getDigest() const;
		void setDigest(const nn::hac::cnmt::digest_t& digest);

	private:
		const std::string kModuleName = "CONTENT_META";

		// binary blob
		tc::ByteData mRawBinary;

		// variables
		uint64_t mTitleId;
		uint32_t mTitleVersion;
		nn::hac::cnmt::ContentMetaType mType;
		std::vector<nn::hac::cnmt::ContentMetaAttributeFlag> mAttribute;
		nn::hac::cnmt::StorageId mStorageId;
		nn::hac::cnmt::ContentInstallType mContentInstallType;
		std::vector<cnmt::InstallStateFlag> mInstallState;
		uint32_t mRequiredDownloadSystemVersion;

		nn::hac::ApplicationMetaExtendedHeader mApplicationMetaExtendedHeader;
		nn::hac::PatchMetaExtendedHeader mPatchMetaExtendedHeader;
		nn::hac::AddOnContentMetaExtendedHeader mAddOnContentMetaExtendedHeader;
		nn::hac::DeltaMetaExtendedHeader mDeltaMetaExtendedHeader;
		nn::hac::SystemUpdateMetaExtendedHeader mSystemUpdateMetaExtendedHeader;

		std::vector<ContentInfo> mContentInfo;
		std::vector<ContentMetaInfo> mContentMetaInfo;

		tc::ByteData mPatchMetaExtendedData;
		tc::ByteData mDeltaMetaExtendedData;
		nn::hac::SystemUpdateMetaExtendedData mSystemUpdateMetaExtendedData;		
		
		nn::hac::cnmt::digest_t mDigest;

		inline size_t getExtendedHeaderOffset() const { return sizeof(sContentMetaHeader); }
		inline size_t getContentInfoOffset(size_t exhdrSize) const { return getExtendedHeaderOffset() + exhdrSize; }
		inline size_t getContentMetaInfoOffset(size_t exhdrSize, size_t contentInfoNum) const { return getContentInfoOffset(exhdrSize) + contentInfoNum * sizeof(sContentInfo); }
		inline size_t getExtendedDataOffset(size_t exhdrSize, size_t contentInfoNum, size_t contentMetaNum) const { return getContentMetaInfoOffset(exhdrSize, contentInfoNum) + contentMetaNum * sizeof(sContentMetaInfo); }
		inline size_t getDigestOffset(size_t exhdrSize, size_t contentInfoNum, size_t contentMetaNum, size_t exdataSize) const { return getExtendedDataOffset(exhdrSize, contentInfoNum, contentMetaNum) + exdataSize; }
		inline size_t getTotalSize(size_t exhdrSize, size_t contentInfoNum, size_t contentMetaNum, size_t exdataSize) const { return getDigestOffset(exhdrSize, contentInfoNum, contentMetaNum, exdataSize) + cnmt::kDigestLen; }

		bool validateExtendedHeaderSize(nn::hac::cnmt::ContentMetaType type, size_t exhdrSize) const;
		size_t getExtendedDataSize(nn::hac::cnmt::ContentMetaType type, const byte_t* data) const;
		void validateBinary(const byte_t* bytes, size_t len) const;
	};
}
}