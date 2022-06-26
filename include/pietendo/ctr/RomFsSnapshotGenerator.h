#pragma once
#include <tc/ByteData.h>
#include <tc/io/VirtualFileSystem.h>
#include <pietendo/ctr/romfs.h>

namespace pie { namespace ctr {

struct RomFsSnapshotGenerator : public tc::io::VirtualFileSystem::FileSystemSnapshot
{
public:
	RomFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream);
private:
	RomFsSnapshotGenerator();

	std::shared_ptr<tc::io::IStream> mBaseStream;

	int64_t mDataOffset;

	tc::ByteData mDirEntryTable;
	std::map<uint32_t, size_t> mDirParentVaddrMap;
	inline pie::ctr::RomFsDirectoryEntry* getDirEntry(uint32_t vaddr) { return (pie::ctr::RomFsDirectoryEntry*)(mDirEntryTable.data() + vaddr); }

	tc::ByteData mFileEntryTable;
	inline pie::ctr::RomFsFileEntry* getFileEntry(uint32_t vaddr) { return (pie::ctr::RomFsFileEntry*)(mFileEntryTable.data() + vaddr); }

	void addFile(const pie::ctr::RomFsFileEntry* file_entry, size_t parent_dir);
	void addDirectory(const pie::ctr::RomFsDirectoryEntry* dir_entry, size_t parent_dir);
};

}} // namespace pie::ctr