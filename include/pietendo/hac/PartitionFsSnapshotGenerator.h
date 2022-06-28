	/**
	 * @file PartitionFsSnapshotGenerator.h
	 * @brief Declaration of pie::hac::PartitionFsSnapshotGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace pie { namespace hac {

struct PartitionFsSnapshotGenerator : public tc::io::VirtualFileSystem::FileSystemSnapshot
{
public:
	enum ValidationMode
	{
		ValidationMode_None,
		ValidationMode_Warn,
		ValidationMode_Throw
	};

	PartitionFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream, ValidationMode validate_mode = ValidationMode_Warn);
private:
	PartitionFsSnapshotGenerator();
};

}} // namespace pie::hac