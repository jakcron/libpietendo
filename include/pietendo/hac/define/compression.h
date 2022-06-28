	/**
	 * @file compression.h
	 * @brief Declaration of Compression structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/types.h>

namespace pie { namespace hac {

namespace compression
{
	// defines
	static const size_t kRomfsBlockSize = 0x10000;
	static const size_t kRomfsBlockAlign = 0x10;

	// enums
	enum class CompressionType : byte_t
	{
		None = 0x0,
		Lz4 = 0x1
	};
}

#pragma pack(push,1)

// structures
struct sCompressionEntry
{
	tc::bn::le64<uint64_t> virtual_offset;
	tc::bn::le64<uint64_t> physical_offset;
	byte_t compression_type;
	std::array<byte_t, 0x3> reserved;
	tc::bn::le32<uint32_t> physical_size;
};
static_assert(sizeof(sCompressionEntry) == 24, "sCompressionEntry size.");

#pragma pack(pop)

}} // namespace pie::hac