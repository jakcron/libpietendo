	/**
	 * @file FileSystemAccessUtil.h
	 * @brief Declaration of pie::hac::FileSystemAccessUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/fac.h>

namespace pie { namespace hac {
	
class FileSystemAccessUtil
{
public:
	static std::string getFsAccessFlagAsString(pie::hac::fac::FsAccessFlag flag);
	static std::string getSaveDataOwnerAccessModeAsString(pie::hac::fac::SaveDataOwnerIdAccessType type);

private:
	const std::string kModuleName = "FILE_SYSTEM_ACCESS_UTIL";
};

}} // namespace pie::hac