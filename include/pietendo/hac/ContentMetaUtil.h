	/**
	 * @file ContentMetaUtil.h
	 * @brief Declaration of pie::hac::ContentMetaUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/cnmt.h>

namespace pie { namespace hac {
	
class ContentMetaUtil
{
public:
	static std::string getContentTypeAsString(pie::hac::cnmt::ContentType val);
	static std::string getContentMetaTypeAsString(pie::hac::cnmt::ContentMetaType val);
	static std::string getUpdateTypeAsString(pie::hac::cnmt::UpdateType val);
	static std::string getContentInstallTypeAsString(pie::hac::cnmt::ContentInstallType val);
	static std::string getStorageIdAsString(pie::hac::cnmt::StorageId val);
	static std::string getContentMetaAttributeFlagAsString(pie::hac::cnmt::ContentMetaAttributeFlag val);
	static std::string getVersionAsString(uint32_t version);

private:
	const std::string kModuleName = "CONTENT_META_UTIL";
};

}} // namespace pie::hac