#pragma once
#include <nn/hac/define/fac.h>

namespace nn
{
namespace hac
{
	class FileSystemAccessUtil
	{
	public:
		static std::string getFsAccessFlagAsString(nn::hac::fac::FsAccessFlag flag);
		static std::string getSaveDataOwnerAccessModeAsString(nn::hac::fac::SaveDataOwnerIdAccessType type);

	private:
		const std::string kModuleName = "FILE_SYSTEM_ACCESS_UTIL";
	};
}
}