	/**
	 * @file PartitionFsUtil.h
	 * @brief Declaration of pie::hac::PartitionFsUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/pfs.h>
#include <pietendo/hac/PartitionFsHeader.h>

namespace pie { namespace hac {
	
class PartitionFsUtil
{
public:
	static std::string getFsTypeAsString(pie::hac::PartitionFsHeader::FsType val);
	static std::string getFsTypeAsStringDescription(pie::hac::PartitionFsHeader::FsType val);

private:
	const std::string kModuleName = "PARTITION_FS_UTIL";
};

}} // namespace pie::hac