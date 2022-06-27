#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace nn { namespace hac {

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

}} // namespace nn::hac