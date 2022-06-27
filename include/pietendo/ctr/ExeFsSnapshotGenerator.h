	/**
	 * @file ExeFsSnapshotGenerator.h
	 * @brief Declaration of pie::ctr::ExeFsSnapshotGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/27
	 **/
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