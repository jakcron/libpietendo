#pragma once
#include <tc/io/VirtualFileSystem.h>

namespace nn { namespace hac {

struct GameCardFsSnapshotGenerator : public tc::io::VirtualFileSystem::FileSystemSnapshot
{
public:
	enum ValidationMode
	{
		ValidationMode_None,
		ValidationMode_Warn,
		ValidationMode_Throw
	};

	GameCardFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream, size_t root_header_size, ValidationMode validate_mode = ValidationMode_Warn);
private:
	GameCardFsSnapshotGenerator();
};

}} // namespace nn::hac