	/**
	 * @file RomFsSnapshotGenerator.h
	 * @brief Declaration of pie::hac::RomFsSnapshotGenerator
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/io/VirtualFileSystem.h>

#include <pietendo/hac/define/romfs.h>

namespace pie { namespace hac {

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
	inline pie::hac::sRomfsDirEntry* getDirEntry(uint32_t vaddr) { return (pie::hac::sRomfsDirEntry*)(mDirEntryTable.data() + vaddr); }

	tc::ByteData mFileEntryTable;
	inline pie::hac::sRomfsFileEntry* getFileEntry(uint32_t vaddr) { return (pie::hac::sRomfsFileEntry*)(mFileEntryTable.data() + vaddr); }

	//void addFile(const pie::hac::sRomfsFileEntry* file_entry, size_t parent_dir);
	//void addDirectory(const pie::hac::sRomfsDirEntry* dir_entry, size_t parent_dir);
};

}} // namespace pie::hac