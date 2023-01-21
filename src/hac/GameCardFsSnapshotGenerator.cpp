#include <pietendo/hac/GameCardFsSnapshotGenerator.h>
#include <tc/io/SubStream.h>
#include <tc/io/IOUtil.h>
#include <tc/crypto/Sha2256Generator.h>
#include <tc/crypto/CryptoException.h>

#include <pietendo/hac/PartitionFsHeader.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

pie::hac::GameCardFsSnapshotGenerator::GameCardFsSnapshotGenerator(const std::shared_ptr<tc::io::IStream>& stream, size_t root_header_size, ValidationMode validate_mode) :
	FileSystemSnapshot()
{
	// validate stream properties
	if (stream == nullptr)
	{
		throw tc::ObjectDisposedException("pie::hac::GameCardFsSnapshotGenerator", "Failed to open input stream.");
	}
	if (stream->canRead() == false || stream->canSeek() == false)
	{
		throw tc::NotSupportedException("pie::hac::GameCardFsSnapshotGenerator", "Input stream requires read/seek permissions.");
	}

	// read/validate root HFS0 header
	if (stream->length() < tc::io::IOUtil::castSizeToInt64(root_header_size))
	{
		throw tc::ArgumentOutOfRangeException("pie::hac::GameCardFsSnapshotGenerator", "Input stream is too small.");
	}

	tc::ByteData root_header_raw = tc::ByteData(root_header_size);
	stream->seek(0, tc::io::SeekOrigin::Begin);
	stream->read(root_header_raw.data(), root_header_raw.size());

	pie::hac::PartitionFsHeader root_header;
	try {
		root_header.fromBytes(root_header_raw.data(), root_header_raw.size());
	} catch (tc::Exception&) {
		throw tc::Exception("pie::hac::GameCardFsSnapshotGenerator", "Failed to process root HFS0 header.");
	}
	
	if (root_header.getFsType() != pie::hac::PartitionFsHeader::TYPE_HFS0)
	{
		throw tc::Exception("pie::hac::GameCardFsSnapshotGenerator", "Root header was not HFS0.");
	}

	// parse header sections
	struct SectionInformation
	{
		std::string name;
		int64_t offset;
		int64_t size;
		size_t hashed_size;
		std::array<byte_t, 32> hash;
	};
	
	struct PartitionInformation
	{
		std::string name;
		std::vector<SectionInformation> file_list;
	};

	std::vector<PartitionInformation> dir_list;

	
	pie::hac::detail::sha256_hash_t calc_hash; // for hash checking

	// get partition metadata
	for (auto dirItr = root_header.getFileList().begin(); dirItr != root_header.getFileList().end(); dirItr++)
	{
		PartitionInformation dir_info_tmp;

		// create empty section information
		dir_info_tmp.name = dirItr->name;

		// process the partition header
		// the `hash_protected_size` of the partitions is always the header size
		tc::ByteData part_header_raw = tc::ByteData(dirItr->hash_protected_size);
		stream->seek(dirItr->offset, tc::io::SeekOrigin::Begin);
		stream->read(part_header_raw.data(), part_header_raw.size());

		// validate header if required
		if (validate_mode == ValidationMode_Warn || validate_mode == ValidationMode_Throw)
		{
			tc::crypto::GenerateSha2256Hash(calc_hash.data(), part_header_raw.data(), part_header_raw.size());
			if (memcmp(calc_hash.data(), dirItr->hash.data(), calc_hash.size()) != 0)
			{
				std::string error_msg = fmt::format("Partition \"{:s}\" failed hash check.", dirItr->name);
				if (validate_mode == ValidationMode_Throw)
				{
					throw tc::crypto::CryptoException("pie::hac::GameCardFsSnapshotGenerator", error_msg);
				}
				else if (validate_mode == ValidationMode_Warn)
				{
					fmt::print("[WARNING] {:s}\n", error_msg);
				}
			}
		}

		// parse partition header
		pie::hac::PartitionFsHeader part_header;
		try {
			part_header.fromBytes(part_header_raw.data(), part_header_raw.size());
		} catch (tc::Exception&) {
			throw tc::Exception("pie::hac::GameCardFsSnapshotGenerator", "Failed to process partition HFS0 header.");
		}
		
		// check the FsType is HFS0
		if (part_header.getFsType() != pie::hac::PartitionFsHeader::TYPE_HFS0)
		{
			throw tc::Exception("pie::hac::GameCardFsSnapshotGenerator", "Partition header was not HFS0.");
		}

		// iterate over files
		for (auto fileItr = part_header.getFileList().begin(); fileItr != part_header.getFileList().end(); fileItr++)
		{
			SectionInformation file_info_tmp;
			
			file_info_tmp.name = fileItr->name;
			file_info_tmp.offset = fileItr->offset + dirItr->offset;
			file_info_tmp.size = fileItr->size;
			file_info_tmp.hashed_size = fileItr->hash_protected_size;
			file_info_tmp.hash = fileItr->hash;

			dir_info_tmp.file_list.push_back(file_info_tmp);
		}
		
		dir_list.push_back(dir_info_tmp);
	}


	// Add root directory
	dir_entries.push_back(DirEntry());
	auto cur_dir = &dir_entries.front();
	cur_dir->dir_listing.abs_path = tc::io::Path("/");
	dir_entry_path_map[tc::io::Path("/")] = dir_entries.size()-1;

	// save root_dir_index
	size_t root_dir_index = dir_entry_path_map[tc::io::Path("/")];


	// populate virtual filesystem
	DirEntry dir_tmp;
	FileEntry file_tmp;
	for (auto dirItr = dir_list.begin(); dirItr != dir_list.end(); dirItr++)
	{
		// create dir path
		tc::io::Path dir_path = dir_entries[root_dir_index].dir_listing.abs_path + dirItr->name;
		dir_tmp.dir_listing.abs_path = dir_path;
		
		// add dir entry to list
		dir_entries.push_back(std::move(dir_tmp));

		// add dir entry to map
		dir_entry_path_map[dir_path] = dir_entries.size() - 1;

		// add name to parent directory listing
		dir_entries[root_dir_index].dir_listing.dir_list.push_back(dirItr->name);

		// save index for current directory
		size_t current_directory_index = dir_entry_path_map[dir_path];

		for (auto fileItr = dirItr->file_list.begin(); fileItr != dirItr->file_list.end(); fileItr++)
		{
			// if we verify the hashes, we import the hashable part first and verify
			if ((validate_mode == ValidationMode_Warn || validate_mode == ValidationMode_Throw))
			{	
				auto tmp_data = tc::ByteData(fileItr->hashed_size);
				stream->seek(fileItr->offset, tc::io::SeekOrigin::Begin);
				stream->read(tmp_data.data(), tmp_data.size());

				tc::crypto::GenerateSha2256Hash(calc_hash.data(), tmp_data.data(), tmp_data.size());
				if (memcmp(calc_hash.data(), fileItr->hash.data(), calc_hash.size()) != 0)
				{
					std::string error_msg = fmt::format("\"{:s}\" failed hash check.", fileItr->name);
					if (validate_mode == ValidationMode_Throw)
					{
						throw tc::crypto::CryptoException("pie::hac::GameCardFsSnapshotGenerator", error_msg);
					}
					else if (validate_mode == ValidationMode_Warn)
					{
						fmt::print("[WARNING] {:s}\n", error_msg);
					}
				}
			}
			
			// create file
			try {
				file_tmp.stream = std::make_shared<tc::io::SubStream>(tc::io::SubStream(stream, fileItr->offset, fileItr->size));
			} catch (tc::Exception& e) {
				fmt::print("[WARNING] Failed to add file \"{:s}\". ({:s})\n", fileItr->name, e.error());
			}

			// create file path
			tc::io::Path file_path = dir_entries[current_directory_index].dir_listing.abs_path + fileItr->name;

			// add file entry to list
			file_entries.push_back(std::move(file_tmp));

			// add file entry to map
			file_entry_path_map[file_path] = file_entries.size()-1;

			// add name to parent directory listing
			dir_entries[current_directory_index].dir_listing.file_list.push_back(fileItr->name);
		}	
	}
}