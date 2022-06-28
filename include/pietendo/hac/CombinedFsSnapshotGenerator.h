	/**
	 * @file CombinedFsSnapshotGenerator.h
	 * @brief Declaration of pie::hac::CombinedFsSnapshotGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace pie { namespace hac {

struct CombinedFsSnapshotGenerator : public tc::io::VirtualFileSystem::FileSystemSnapshot
{
public:
	struct MountPointInfo
	{
		std::string name;
		tc::io::VirtualFileSystem::FileSystemSnapshot fs_meta;
	};

	CombinedFsSnapshotGenerator(const std::vector<MountPointInfo>& mount_point_info);
private:
	CombinedFsSnapshotGenerator();
};

}} // namespace pie::hac