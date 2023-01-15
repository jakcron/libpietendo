	/**
	 * @file indirectstorage.h
	 * @brief Declaration of IndirectStorage structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>
#include <pietendo/hac/define/bktr.h>

namespace pie { namespace hac {

namespace indirectstorage
{
	static const int32_t kStorageCount = 2;
	static const size_t kNodeSize = 0x4000; // 16KB

	enum StorageSource {
		StorageSource_BaseRomFs = 0,
		StorageSource_PatchRomFs = 1,
	};
}

#pragma pack(push,1)
struct sIndirectStorageEntry
{
	tc::bn::le64<int64_t> virt_offset;
	tc::bn::le64<int64_t> phys_offset;
	tc::bn::le32<int32_t> storage_index;
};
static_assert(sizeof(sIndirectStorageEntry) == 0x14, "sIndirectStorageEntry size.");

struct sIndirectStorageBucket
{
	union { // this union ensure size of kNodeSize
		struct {
			struct {
				tc::bn::pad<4> reserved;
				tc::bn::le32<uint32_t> entry_count;
				tc::bn::le64<uint64_t> end_offset_bucket;
			} header;
			std::array<sIndirectStorageEntry, (0x4000 - sizeof(header)) / sizeof(sIndirectStorageEntry)> entries;
		};
		std::array<byte_t, indirectstorage::kNodeSize> raw;
	};
};
static_assert(sizeof(sIndirectStorageBucket) == indirectstorage::kNodeSize, "sIndirectStorageBucket size.");

#ifdef _WIN32
#pragma warning(disable : 4200) // silence warnings for usage of empty arrays in stucts 
#endif

struct sIndirectStorageBlock
{
	struct {
		std::array<byte_t, 0x4> reserved_0;
		tc::bn::le32<uint32_t> bucket_count;
		tc::bn::le64<uint64_t> total_size;
	} header;
	std::array<tc::bn::le64<uint64_t>, (0x4000 - sizeof(header)) / sizeof(tc::bn::le64<uint64_t>)> base_virtual_bucket_offset;
	sIndirectStorageBucket buckets[];
};
static_assert(sizeof(sIndirectStorageBlock) == 0x4000, "sIndirectStorageBlock size.");

#ifdef _WIN32
#pragma warning(default : 4200)
#endif

#pragma pack(pop)

}} // namespace pie::hac