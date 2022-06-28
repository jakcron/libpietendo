	/**
	 * @file ContentInfo.h
	 * @brief Declaration of pie::hac::ContentInfo
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/cnmt.h>

namespace pie { namespace hac {
	
class ContentInfo
{
public:
	ContentInfo();
	ContentInfo(const ContentInfo& other);

	void operator=(const ContentInfo& other);
	bool operator==(const ContentInfo& other) const;
	bool operator!=(const ContentInfo& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	const pie::hac::detail::sha256_hash_t& getContentHash() const;
	void setContentHash(const pie::hac::detail::sha256_hash_t& hash);

	const cnmt::content_id_t& getContentId() const;
	void setContentId(const cnmt::content_id_t& content_id);

	size_t getContentSize() const;
	void setContentSize(size_t size);

	cnmt::ContentType getContentType() const;
	void setContentType(cnmt::ContentType type);

	byte_t getIdOffset() const;
	void setIdOffset(byte_t id_offset);

private:
	const std::string kModuleName = "CONTENT_INFO";

	// binary blob
	tc::ByteData mRawBinary;

	// variables
	pie::hac::detail::sha256_hash_t mHash;
	cnmt::content_id_t mContentId;
	size_t mSize;
	cnmt::ContentType mType;
	byte_t mIdOffset;
};

}} // namespace pie::hac