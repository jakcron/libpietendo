	/**
	 * @file aesctrexstorage.h
	 * @brief Declaration of AesCtrExStroage structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>
#include <pietendo/hac/define/bktr.h>

namespace pie { namespace hac {

namespace aesctrexstorage
{
	static const size_t kNodeSize = 0x4000; // 16KB
}

#pragma pack(push,1)

struct sAesCtrExStorageEntry
{
	tc::bn::le64<int64_t> offset;
	tc::bn::pad<4>        reserved;
	tc::bn::le32<int32_t> generation;
};
static_assert(sizeof(sAesCtrExStorageEntry) == 0x10, "sAesCtrExStorageEntry size.");

struct sAesCtrExStorageBucket
{
	union { // this union ensure size of kNodeSize
		struct {
			struct {
				tc::bn::pad<4> reserved;
				tc::bn::le32<uint32_t> entry_count;
				tc::bn::le64<uint64_t> end_offset_bucket;
			} header;
			std::array<sAesCtrExStorageEntry, (aesctrexstorage::kNodeSize - sizeof(header) ) / sizeof(sAesCtrExStorageEntry)> entries;
		};
		std::array<byte_t, aesctrexstorage::kNodeSize> raw;
	};
};
static_assert(sizeof(sAesCtrExStorageBucket) == aesctrexstorage::kNodeSize, "sAesCtrExStorageBucket size.");

#ifdef _WIN32
#pragma warning(disable : 4200) // silence warnings for usage of empty arrays in stucts 
#endif

struct sAesCtrExStorageBlock
{
	struct {
		std::array<byte_t, 0x4> reserved_0;
		tc::bn::le32<uint32_t> bucket_count;
		tc::bn::le64<uint64_t> total_size;
	} header;
	std::array<tc::bn::le64<uint64_t>, (0x4000 - sizeof(header)) / sizeof(tc::bn::le64<uint64_t>)> base_physical_bucket_offset;
	sAesCtrExStorageBucket buckets[];
};
static_assert(sizeof(sAesCtrExStorageBlock) == 0x4000, "sAesCtrExStorageBlock size.");

#ifdef _WIN32
#pragma warning(default : 4200)
#endif

#pragma pack(pop)

}} // namespace pie::hac