	/**
	 * @file ContentMetaInfo.h
	 * @brief Declaration of pie::hac::ContentMetaInfo
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/cnmt.h>

namespace pie { namespace hac {
	
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
	
	pie::hac::cnmt::ContentMetaType getContentMetaType() const;
	void setContentMetaType(pie::hac::cnmt::ContentMetaType type);
	
	const std::vector<pie::hac::cnmt::ContentMetaAttributeFlag>& getAttribute() const;
	void setAttribute(const std::vector<pie::hac::cnmt::ContentMetaAttributeFlag>& attr);
	
private:
	const std::string kModuleName = "CONTENT_META_INFO";

	// byte model
	tc::ByteData mRawBinary;

	// variables
	uint64_t mTitleId;
	uint32_t mTitleVersion;
	pie::hac::cnmt::ContentMetaType mType;
	std::vector<pie::hac::cnmt::ContentMetaAttributeFlag> mAttribute;
};

}} // namespace pie::hac