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

#pragma pack(pop)

}} // namespace pie::hac