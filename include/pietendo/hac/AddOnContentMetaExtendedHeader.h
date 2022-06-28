	/**
	 * @file AddOnContentMetaExtendedHeader.h
	 * @brief Declaration of pie::hac::AddOnContentMetaExtendedHeader
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/cnmt.h>

namespace pie { namespace hac {
	
class AddOnContentMetaExtendedHeader
{
public:
	AddOnContentMetaExtendedHeader();
	AddOnContentMetaExtendedHeader(const AddOnContentMetaExtendedHeader& other);

	void operator=(const AddOnContentMetaExtendedHeader& other);
	bool operator==(const AddOnContentMetaExtendedHeader& other) const;
	bool operator!=(const AddOnContentMetaExtendedHeader& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();

	uint64_t getApplicationId() const;
	void setApplicationId(uint64_t application_id);

	uint32_t getRequiredApplicationVersion() const;
	void setRequiredApplicationVersion(uint32_t app_ver);
private:
	const std::string kModuleName = "ADD_ON_CONTENT_META_EXTENDED_HEADER";

	// binary blob
	tc::ByteData mRawBinary;

	// variables
	uint64_t mApplicationId;
	uint32_t mRequiredApplicationVersion;
};

}} // namespace pie::hac