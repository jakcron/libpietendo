#include <nn/hac/RomFsSnapshotGenerator.h>
#include <tc/io/SubStream.h>
#include <tc/io/MemoryStream.h>
#include <tc/io/IOUtil.h>
#include <tc/crypto/Sha256Generator.h>
#include <tc/crypto/CryptoException.h>

#include <nn/hac/define/romfs.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

nn::hac::RomFsSnapshotGenerator::RomFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream) :
	FileSystemSnapshot(),
	mBaseStream(stream),
	mDataOffset(0),
	mDirEntryTable(),
	mDirParentVaddrMap(),
	mFileEntryTable()
{
	//std::cout << "RomFsSnapshotGenerator begin" << std::endl;

	// validate stream properties
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException("nn::hac::RomFsSnapshotGenerator", "Failed to open input stream.");
	}
	if (mBaseStream->canRead() == false || mBaseStream->canSeek() == false)
	{
		throw tc::NotSupportedException("nn::hac::RomFsSnapshotGenerator", "Input stream requires read/seek permissions.");
	}

	//std::cout << "pos() -> " << mBaseStream->position() << std::endl;

	// validate and read ROMFS header
	nn::hac::sRomfsHeader hdr;
	if (mBaseStream->length() < tc::io::IOUtil::castSizeToInt64(sizeof(nn::hac::sRomfsHeader)))
	{
		throw tc::ArgumentOutOfRangeException("nn::hac::RomFsSnapshotGenerator", "Input stream is too small.");
	}
	mBaseStream->seek(0, tc::io::SeekOrigin::Begin);
	mBaseStream->read((byte_t*)(&hdr), sizeof(nn::hac::sRomfsHeader));

	/*
	std::cout << "hdr.header_size             : " << hdr.header_size.unwrap() << std::endl;
	std::cout << "sizeof(nn::hac::sRomfsHeader)  : " << sizeof(nn::hac::sRomfsHeader) << std::endl;
	std::cout << "hdr.dir_hash_bucket.offset : " << hdr.dir_hash_bucket.offset.unwrap() << std::endl;
	std::cout << "hdr.data_offset             : " << hdr.data_offset.unwrap() << std::endl;
	std::cout << "expected data offset        : " << align<int64_t>(hdr.header_size.unwrap(), nn::hac::romfs::kRomfsHeaderAlign) << std::endl;
	*/


	if (hdr.header_size.unwrap() != sizeof(nn::hac::sRomfsHeader) ||
	    hdr.dir_entry.offset.unwrap() != (hdr.dir_hash_bucket.offset.unwrap() + hdr.dir_hash_bucket.size.unwrap()) ||
	    hdr.data_offset.unwrap() != align<int64_t>(hdr.header_size.unwrap(), nn::hac::romfs::kRomfsHeaderAlign))
	{
		throw tc::ArgumentOutOfRangeException("nn::hac::RomFsSnapshotGenerator", "RomFsHeader is corrupted.");
	}

	// save data offset
	mDataOffset = hdr.data_offset.unwrap();

	// get dir entry ptr
	mDirEntryTable = tc::ByteData(tc::io::IOUtil::castInt64ToSize(hdr.dir_entry.size.unwrap()));
	mBaseStream->seek(hdr.dir_entry.offset.unwrap(), tc::io::SeekOrigin::Begin);
	mBaseStream->read(mDirEntryTable.data(), mDirEntryTable.size());
	

	// get file entry ptr
	mFileEntryTable = tc::ByteData(tc::io::IOUtil::castInt64ToSize(hdr.file_entry.size.unwrap()));
	mBaseStream->seek(hdr.file_entry.offset.unwrap(), tc::io::SeekOrigin::Begin);
	mBaseStream->read(mFileEntryTable.data(), mFileEntryTable.size());

	//std::cout << "DirTable:" << std::endl;
	//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(mDirEntryTable.data(), mDirEntryTable.size());

	/*
	for (uint32_t v_addr = 0; v_addr < mDirEntryTable.size();)
	{
		std::cout << "Dir:            0x" << std::hex << v_addr << std::endl;
		std::cout << " > parent:       0x" << std::hex << getDirEntry(v_addr)->parent_offset.unwrap() << std::endl;
		std::cout << " > sibling:      0x" << std::hex << getDirEntry(v_addr)->sibling_offset.unwrap() << std::endl;
		std::cout << " > child_offset: 0x" << std::hex << getDirEntry(v_addr)->child_offset.unwrap() << std::endl;
		std::cout << " > file_offset:  0x" << std::hex << getDirEntry(v_addr)->file_offset.unwrap() << std::endl;
		std::cout << " > hash_sibling: 0x" << std::hex << getDirEntry(v_addr)->hash_sibling_offset.unwrap() << std::endl;
		std::cout << " > name_size:    0x" << std::hex << getDirEntry(v_addr)->name_size.unwrap() << std::endl;

		uint32_t total_size = sizeof(nn::hac::sRomfsDirEntry) + align<uint32_t>(getDirEntry(v_addr)->name_size.unwrap(), 4);
		std::cout << " > entry_size:   0x" << std::hex << total_size << std::endl;

		if (getDirEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			std::cout << "DirEntry looks sus" << std::endl;
			break;
		}

		v_addr += total_size;
	}
	*/

	//std::cout << "FileTable:" << std::endl;
	//std::cout << tc::cli::FormatUtil::formatBytesAsHxdHexString(mFileEntryTable.data(), mFileEntryTable.size());
	/*
	for (uint32_t v_addr = 0; v_addr < mFileEntryTable.size();)
	{
		std::cout << "File:            0x" << std::hex << v_addr << std::endl;
		std::cout << " > parent:       0x" << std::hex << getFileEntry(v_addr)->parent_offset.unwrap() << std::endl;
		std::cout << " > sibling:      0x" << std::hex << getFileEntry(v_addr)->sibling_offset.unwrap() << std::endl;
		std::cout << " > data_offset:  0x" << std::hex << getFileEntry(v_addr)->data_offset.unwrap() << std::endl;
		std::cout << " > data_size:    0x" << std::hex << getFileEntry(v_addr)->data_size.unwrap() << std::endl;
		std::cout << " > hash_sibling: 0x" << std::hex << getFileEntry(v_addr)->hash_sibling_offset.unwrap() << std::endl;
		std::cout << " > name_size:    0x" << std::hex << getFileEntry(v_addr)->name_size.unwrap() << std::endl;

		uint32_t total_size = sizeof(nn::hac::sRomfsFileEntry) + align<uint32_t>(getFileEntry(v_addr)->name_size.unwrap(), 4);
		std::cout << " > entry_size:   0x" << std::hex << total_size << std::endl;

		if (getFileEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			std::cout << "FileEntry looks sus" << std::endl;
			break;
		}

		v_addr += total_size;
	}
	*/

	if (getDirEntry(0)->parent_offset.unwrap() != 0 ||
	    getDirEntry(0)->sibling_offset.unwrap() != 0xffffffff ||
	    getDirEntry(0)->name_size.unwrap() != 0)
	{
		throw tc::ArgumentOutOfRangeException("nn::hac::RomFsSnapshotGenerator", "Root sRomfsDirEntry corrupted.");
	}

	// add/index directories
	DirEntry dir_tmp;
	for (uint32_t v_addr = 0; size_t(v_addr) < mDirEntryTable.size();)
	{
		// create root entry
		if (v_addr == 0)
		{
			// create dir path
			tc::io::Path dir_path = tc::io::Path("/");
			dir_tmp.dir_listing.abs_path = dir_path;

			// add dir entry to list
			dir_entries.push_back(dir_tmp);

			// add dir entry to map
			dir_entry_path_map[dir_path] = dir_entries.size() - 1;
			mDirParentVaddrMap[v_addr] = dir_entries.size() - 1;
		}
		// else create a regular entry
		else
		{
			// check parent is in map
			if (mDirParentVaddrMap.find(getDirEntry(v_addr)->parent_offset.unwrap()) == mDirParentVaddrMap.end())
				throw tc::InvalidOperationException("nn::hac::RomFsSnapshotGenerator", "Directory had invalid parent");

			// save file name
			std::string file_name_str = std::string(getDirEntry(v_addr)->name, getDirEntry(v_addr)->name_size.unwrap());

			// create dir path
			size_t parent_index = mDirParentVaddrMap[getDirEntry(v_addr)->parent_offset.unwrap()];
			tc::io::Path dir_path = dir_entries[parent_index].dir_listing.abs_path + file_name_str;
			dir_tmp.dir_listing.abs_path = dir_path;

			// add dir entry to list
			dir_entries.push_back(std::move(dir_tmp));

			// add dir entry to map
			dir_entry_path_map[dir_path] = dir_entries.size() - 1;
			mDirParentVaddrMap[v_addr] = dir_entries.size() - 1;

			// add name to parent directory listing
			dir_entries[parent_index].dir_listing.dir_list.push_back(file_name_str);
		}
		

		uint32_t total_size = sizeof(nn::hac::sRomfsDirEntry) + align<uint32_t>(getDirEntry(v_addr)->name_size.unwrap(), 4);

		if (getDirEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			throw tc::InvalidOperationException("nn::hac::RomFsSnapshotGenerator", "Possibly corrupted directory entry");
		}

		v_addr += total_size;
	}

	// add files
	FileEntry file_tmp;
	for (uint32_t v_addr = 0; size_t(v_addr) < mFileEntryTable.size();)
	{
		// check parent is in map
		if (mDirParentVaddrMap.find(getFileEntry(v_addr)->parent_offset.unwrap()) == mDirParentVaddrMap.end())
			throw tc::InvalidOperationException("nn::hac::RomFsSnapshotGenerator", "File had invalid parent");

		if (getFileEntry(v_addr)->data_size.unwrap() != 0)
		{
			// substream
			//std::cout << "trying to add file" << std::endl;
			//std::cout << "offset " << std::hex << getFileEntry(v_addr)->data_offset.unwrap() << std::endl;
			//std::cout << "size   " << std::hex << getFileEntry(v_addr)->data_size.unwrap() << std::endl;
			file_tmp.stream = std::shared_ptr<tc::io::SubStream>(new tc::io::SubStream(mBaseStream, mDataOffset + getFileEntry(v_addr)->data_offset.unwrap(), getFileEntry(v_addr)->data_size.unwrap()));
			//std::cout << "file was added" << std::endl;
		}
		else
		{
			// empty stream
			file_tmp.stream = std::shared_ptr<tc::io::MemoryStream>(new tc::io::MemoryStream());
		}

		// save file name
		std::string file_name_str = std::string(getFileEntry(v_addr)->name, getFileEntry(v_addr)->name_size.unwrap());


		// create file path
		size_t parent_index = mDirParentVaddrMap[getFileEntry(v_addr)->parent_offset.unwrap()];
		tc::io::Path file_path = dir_entries[parent_index].dir_listing.abs_path + file_name_str;

		// add file entry to list
		file_entries.push_back(std::move(file_tmp));

		// add file entry to map
		file_entry_path_map[file_path] = file_entries.size() - 1;

		// add name to parent directory listing
		dir_entries[parent_index].dir_listing.file_list.push_back(file_name_str);

		uint32_t total_size = sizeof(nn::hac::sRomfsFileEntry) + align<uint32_t>(getFileEntry(v_addr)->name_size.unwrap(), 4);

		if (getFileEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			throw tc::InvalidOperationException("nn::hac::RomFsSnapshotGenerator", "Possibly corrupted file entry");
		}

		v_addr += total_size;
	}
}