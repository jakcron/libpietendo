#include <pietendo/hac/CombinedFsSnapshotGenerator.h>
#include <tc/io/IOUtil.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

pie::hac::CombinedFsSnapshotGenerator::CombinedFsSnapshotGenerator(const std::vector<MountPointInfo>& mount_point_info) :
	FileSystemSnapshot()
{
	// Add root directory
	dir_entries.push_back(DirEntry());
	dir_entries.back().dir_listing.abs_path = tc::io::Path("/");
	dir_entry_path_map[tc::io::Path("/")] = dir_entries.size()-1;

	size_t root_dir_index = dir_entry_path_map[tc::io::Path("/")];

	// migrate virtual filesystem
	//std::string old_path_str, new_path_str;
	for (auto mount = mount_point_info.begin(); mount != mount_point_info.end(); mount++)
	{
		// save new base path
		tc::io::Path new_base_path = dir_entries[root_dir_index].dir_listing.abs_path + mount->name;

		// write this directory to the root directory record
		dir_entries[root_dir_index].dir_listing.dir_list.push_back(mount->name);

		for (auto oldDirEntry = mount->fs_meta.dir_entries.begin(); oldDirEntry != mount->fs_meta.dir_entries.end(); oldDirEntry++)
		{
			// generate old and new path
			tc::io::Path old_dir_path = oldDirEntry->dir_listing.abs_path;
			tc::io::Path new_dir_path = old_dir_path;
			new_dir_path.pop_front();
			new_dir_path = new_base_path + new_dir_path;
			
			//fmt::print("Migrate DirEntry from: \"{:s}\" -> \"{:s}\"\n", old_dir_path.to_string(), new_dir_path.to_string());

			// migriate dir entry (update abs path aswell)
			dir_entries.push_back(*oldDirEntry);
			dir_entries.back().dir_listing.abs_path = new_dir_path;
			dir_entry_path_map[new_dir_path] = dir_entries.size()-1;

			// locate and migrate file children
			for (auto oldDirChildFileName = oldDirEntry->dir_listing.file_list.begin();  oldDirChildFileName != oldDirEntry->dir_listing.file_list.end(); oldDirChildFileName++)
			{
				tc::io::Path old_file_path = old_dir_path + *oldDirChildFileName;
				tc::io::Path new_file_path = new_dir_path + *oldDirChildFileName;

				//fmt::print("Migrate FileEntry from: \"{:s}\" -> \"{:s}\"\n", old_file_path.to_string(), new_file_path.to_string());

				size_t old_file_entry_index = mount->fs_meta.file_entry_path_map.at(old_file_path);

				file_entries.push_back(mount->fs_meta.file_entries[old_file_entry_index]);
				file_entry_path_map[new_file_path] = file_entries.size()-1;
			}
		}
	}
}