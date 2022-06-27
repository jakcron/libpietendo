#pragma once
#include <nn/hac/define/cnmt.h>


namespace nn
{
namespace hac
{
	class ContentMetaInfo
	{
	public:
		ContentMetaInfo();
		ContentMetaInfo(const ContentMetaInfo& other);

		void operator=(const ContentMetaInfo& other);
		bool operator==(const ContentMetaInfo& other) const;
		bool operator!=(const ContentMetaInfo& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint64_t getTitleId() const;
		void setTitleId(uint64_t title_id);
		
		uint32_t getTitleVersion() const;
		void setTitleVersion(uint32_t ver);
		
		nn::hac::cnmt::ContentMetaType getContentMetaType() const;
		void setContentMetaType(nn::hac::cnmt::ContentMetaType type);
		
		const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& getAttribute() const;
		void setAttribute(const std::vector<nn::hac::cnmt::ContentMetaAttributeFlag>& attr);
		
	private:
		const std::string kModuleName = "CONTENT_META_INFO";

		// byte model
		tc::ByteData mRawBinary;

		// variables
		uint64_t mTitleId;
		uint32_t mTitleVersion;
		nn::hac::cnmt::ContentMetaType mType;
		std::vector<nn::hac::cnmt::ContentMetaAttributeFlag> mAttribute;
	};
}
}