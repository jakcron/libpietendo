#include <pietendo/hac/RomFsSnapshotGenerator.h>
#include <tc/io/SubStream.h>
#include <tc/io/MemoryStream.h>
#include <tc/io/EmptyStream.h>
#include <tc/io/IOUtil.h>
#include <tc/crypto/Sha2256Generator.h>
#include <tc/crypto/CryptoException.h>

#include <pietendo/hac/define/romfs.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

pie::hac::RomFsSnapshotGenerator::RomFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream) :
	FileSystemSnapshot(),
	mBaseStream(stream),
	mDataOffset(0),
	mDirEntryTable(),
	mDirParentVaddrMap(),
	mFileEntryTable()
{
	//fmt::print("RomFsSnapshotGenerator BEGIN\n");

	// validate stream properties
	if (mBaseStream == nullptr)
	{
		throw tc::ObjectDisposedException("pie::hac::RomFsSnapshotGenerator", "Failed to open input stream.");
	}
	if (mBaseStream->canRead() == false || mBaseStream->canSeek() == false)
	{
		throw tc::NotSupportedException("pie::hac::RomFsSnapshotGenerator", "Input stream requires read/seek permissions.");
	}

	//fmt::print("pos() -> 0x{:08x}\n", mBaseStream->position());

	// validate and read ROMFS header
	pie::hac::sRomfsHeader hdr;
	if (mBaseStream->length() < tc::io::IOUtil::castSizeToInt64(sizeof(pie::hac::sRomfsHeader)))
	{
		throw tc::ArgumentOutOfRangeException("pie::hac::RomFsSnapshotGenerator", "Input stream is too small.");
	}
	mBaseStream->seek(0, tc::io::SeekOrigin::Begin);
	mBaseStream->read((byte_t*)(&hdr), sizeof(pie::hac::sRomfsHeader));

	/*
	fmt::print("RomFsHeader:\n");
	fmt::print(" > header_size = 0x{:04x} (expected: 0x{:04x})\n", hdr.header_size.unwrap(), sizeof(pie::hac::sRomfsHeader));
	fmt::print(" > dir_hash_bucket\n");
	fmt::print("   > offset =    0x{:04x}\n", hdr.dir_hash_bucket.offset.unwrap());
	fmt::print("   > size =      0x{:04x}\n", hdr.dir_hash_bucket.size.unwrap());
	fmt::print(" > dir_entry\n");
	fmt::print("   > offset =    0x{:04x}\n", hdr.dir_entry.offset.unwrap());
	fmt::print("   > size =      0x{:04x}\n", hdr.dir_entry.size.unwrap());
	fmt::print(" > file_hash_bucket\n");
	fmt::print("   > offset =    0x{:04x}\n", hdr.file_hash_bucket.offset.unwrap());
	fmt::print("   > size =      0x{:04x}\n", hdr.file_hash_bucket.size.unwrap());
	fmt::print(" > file_entry\n");
	fmt::print("   > offset =    0x{:04x}\n", hdr.file_entry.offset.unwrap());
	fmt::print("   > size =      0x{:04x}\n", hdr.file_entry.size.unwrap());
	fmt::print(" > data_offset = 0x{:04x} (expected: 0x{:04x})\n", hdr.data_offset.unwrap(), align<int64_t>(hdr.header_size.unwrap(), pie::hac::romfs::kRomfsHeaderAlign));
	*/

	if (hdr.header_size.unwrap() != sizeof(pie::hac::sRomfsHeader) ||
	    hdr.dir_entry.offset.unwrap() != (hdr.dir_hash_bucket.offset.unwrap() + hdr.dir_hash_bucket.size.unwrap()) ||
	    hdr.data_offset.unwrap() != align<int64_t>(hdr.header_size.unwrap(), pie::hac::romfs::kRomfsHeaderAlign))
	{
		throw tc::ArgumentOutOfRangeException("pie::hac::RomFsSnapshotGenerator", "RomFsHeader is corrupted.");
	}

	// save data offset
	mDataOffset = hdr.data_offset.unwrap();

	// get dir entry ptr
	if (hdr.dir_entry.size.unwrap() > 0)
	{
		mDirEntryTable = tc::ByteData(tc::io::IOUtil::castInt64ToSize(hdr.dir_entry.size.unwrap()));
		mBaseStream->seek(hdr.dir_entry.offset.unwrap(), tc::io::SeekOrigin::Begin);
		mBaseStream->read(mDirEntryTable.data(), mDirEntryTable.size());
	}
	else
	{
		mDirEntryTable = tc::ByteData();
	}

	// get file entry ptr
	if (hdr.file_entry.size.unwrap() > 0)
	{
		mFileEntryTable = tc::ByteData(tc::io::IOUtil::castInt64ToSize(hdr.file_entry.size.unwrap()));
		mBaseStream->seek(hdr.file_entry.offset.unwrap(), tc::io::SeekOrigin::Begin);
		mBaseStream->read(mFileEntryTable.data(), mFileEntryTable.size());
	}
	else
	{
		mFileEntryTable = tc::ByteData();
	}

	/*
	fmt::print("DirTable:\n");
	fmt::print("{:s}", tc::cli::FormatUtil::formatBytesAsHxdHexString(mDirEntryTable.data(), mDirEntryTable.size()));
	for (uint32_t v_addr = 0; v_addr < mDirEntryTable.size();)
	{
		fmt::print("Dir:             0x{:08x}\n", v_addr);
		fmt::print(" > parent:       0x{:08x}\n", getDirEntry(v_addr)->parent_offset.unwrap());
		fmt::print(" > sibling:      0x{:08x}\n", getDirEntry(v_addr)->sibling_offset.unwrap());
		fmt::print(" > child_offset: 0x{:08x}\n", getDirEntry(v_addr)->child_offset.unwrap());
		fmt::print(" > file_offset:  0x{:08x}\n", getDirEntry(v_addr)->file_offset.unwrap());
		fmt::print(" > hash_sibling: 0x{:08x}\n", getDirEntry(v_addr)->hash_sibling_offset.unwrap());
		fmt::print(" > name_size:    0x{:08x}\n", getDirEntry(v_addr)->name_size.unwrap());

		uint32_t total_size = sizeof(pie::hac::sRomfsDirEntry) + align<uint32_t>(getDirEntry(v_addr)->name_size.unwrap(), 4);
		fmt::print(" > entry_size:   0x{:x}\n", total_size);

		if (getDirEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			fmt::print("DirEntry looks sus\n");
			break;
		}

		v_addr += total_size;
	}
	*/
	
	/*
	fmt::print("FileTable:\n");
	fmt::print("{:s}", tc::cli::FormatUtil::formatBytesAsHxdHexString(mFileEntryTable.data(), mFileEntryTable.size()));
	for (uint32_t v_addr = 0; v_addr < mFileEntryTable.size();)
	{
		fmt::print("File:            0x{:08x}\n", v_addr);
		fmt::print(" > parent:       0x{:08x}\n", getFileEntry(v_addr)->parent_offset.unwrap());
		fmt::print(" > sibling:      0x{:08x}\n", getFileEntry(v_addr)->sibling_offset.unwrap());
		fmt::print(" > data_offset:  0x{:08x}\n", getFileEntry(v_addr)->data_offset.unwrap());
		fmt::print(" > data_size:    0x{:08x}\n", getFileEntry(v_addr)->data_size.unwrap());
		fmt::print(" > hash_sibling: 0x{:08x}\n", getFileEntry(v_addr)->hash_sibling_offset.unwrap());
		fmt::print(" > name_size:    0x{:08x}\n", getFileEntry(v_addr)->name_size.unwrap());

		uint32_t total_size = sizeof(pie::hac::sRomfsFileEntry) + align<uint32_t>(getFileEntry(v_addr)->name_size.unwrap(), 4);
		fmt::print(" > entry_size:   0x{:x}\n", total_size);

		if (getFileEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			fmt::print("DirEntry looks sus\n");
			break;
		}

		v_addr += total_size;
	}
	*/

	// validate root directory entry
	if (mDirEntryTable.size() == 0 ||
		getDirEntry(0)->parent_offset.unwrap() != 0 ||
	    getDirEntry(0)->sibling_offset.unwrap() != 0xffffffff ||
	    getDirEntry(0)->name_size.unwrap() != 0)
	{
		throw tc::ArgumentOutOfRangeException("pie::hac::RomFsSnapshotGenerator", "Root sRomfsDirEntry corrupted.");
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
				throw tc::InvalidOperationException("pie::hac::RomFsSnapshotGenerator", "Directory had invalid parent");

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
		
		uint32_t entry_total_size = sizeof(pie::hac::sRomfsDirEntry) + align<uint32_t>(getDirEntry(v_addr)->name_size.unwrap(), 4);

		if (getDirEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			throw tc::InvalidOperationException("pie::hac::RomFsSnapshotGenerator", "Possibly corrupted directory entry");
		}

		v_addr += entry_total_size;
	}

	// add files
	FileEntry file_tmp;
	for (uint32_t v_addr = 0; size_t(v_addr) < mFileEntryTable.size();)
	{
		// check parent is in map
		if (mDirParentVaddrMap.find(getFileEntry(v_addr)->parent_offset.unwrap()) == mDirParentVaddrMap.end())
			throw tc::InvalidOperationException("pie::hac::RomFsSnapshotGenerator", "File had invalid parent");

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
			file_tmp.stream = std::shared_ptr<tc::io::EmptyStream>(new tc::io::EmptyStream());
			fmt::print("stream properties: canRead()  = {}\n", file_tmp.stream->canRead());
			fmt::print("stream properties: canWrite() = {}\n", file_tmp.stream->canWrite());
			fmt::print("stream properties: canSeek()  = {}\n", file_tmp.stream->canSeek());
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

		uint32_t entry_total_size = sizeof(pie::hac::sRomfsFileEntry) + align<uint32_t>(getFileEntry(v_addr)->name_size.unwrap(), 4);

		if (getFileEntry(v_addr)->sibling_offset.unwrap() < v_addr)
		{
			throw tc::InvalidOperationException("pie::hac::RomFsSnapshotGenerator", "Possibly corrupted file entry");
		}

		v_addr += entry_total_size;
	}

	//fmt::print("RomFsSnapshotGenerator END\n");
}