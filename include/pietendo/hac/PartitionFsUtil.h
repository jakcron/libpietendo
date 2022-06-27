#pragma once
#include <nn/hac/define/pfs.h>
#include <nn/hac/PartitionFsHeader.h>

namespace nn
{
namespace hac
{
	class PartitionFsUtil
	{
	public:
		static std::string getFsTypeAsString(nn::hac::PartitionFsHeader::FsType val);
		static std::string getFsTypeAsStringDescription(nn::hac::PartitionFsHeader::FsType val);

	private:
		const std::string kModuleName = "PARTITION_FS_UTIL";
	};
}
}