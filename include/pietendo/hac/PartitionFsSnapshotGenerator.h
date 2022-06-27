#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace nn { namespace hac {

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

}} // namespace nn::hac