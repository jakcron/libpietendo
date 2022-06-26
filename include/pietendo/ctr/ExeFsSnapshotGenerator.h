#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace pie { namespace ctr {

struct ExeFsSnapshotGenerator : public tc::io::VirtualFileSystem::FileSystemSnapshot
{
public:
	ExeFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream, bool verify_hashes = true);
private:
	ExeFsSnapshotGenerator();
};

}} // namespace pie::ctr