#pragma once
#include <nn/hac/define/types.h>

namespace nn
{
namespace hac
{
	namespace meta
	{
		static const uint32_t kMetaStructMagic = tc::bn::make_struct_magic_uint32("META");
		static const size_t kNameMaxLen = 0x10;
		static const size_t kProductCodeMaxLen = 0x10;
		static const uint32_t kMaxPriority = (1 << 6) - 1;
		static const size_t kSectionAlignSize = 0x10;
		static const uint32_t kDefaultMainThreadStackSize = 4096;
		static const uint32_t kAlignSystemResourceSize = 0x200000;
		static const uint32_t kAlignSystemResourceMask = kAlignSystemResourceSize - 1;
		static const uint32_t kMaxSystemResourceSize = 0x1FE00000;

		enum class InstructionType : bool
		{
			InstructionType32Bit,
			InstructionType64Bit
		};

		enum class ProcessAddressSpace : byte_t
		{
			AddressSpace32Bit,
			AddressSpace64BitOld,
			AddressSpace32BitNoReserved,
			AddressSpace64Bit
		};
	}
#pragma pack(push,1)
	struct sMetaHeader
	{
		tc::bn::le32<uint32_t> st_magic;
		byte_t aci_desc_key_generation;
		std::array<byte_t, 0x7> reserved_0;
		struct sFlag
		{
			byte_t is_64bit_instruction : 1;
			byte_t process_address_space : 3;
			byte_t optimise_memory_allocation : 1; // if KernelCaps.MiscParams.ProgramType == Application && system_resource_size != 0 this will be set if MemoryAllocationCompatiblityMode is false
			byte_t :0;
		} flag;
		byte_t reserved_1;
		byte_t main_thread_priority;
		byte_t main_thread_cpu_id;
		std::array<byte_t, 0x4> reserved_2;
		tc::bn::le32<uint32_t> system_resource_size; // this can only be set if KernelCaps.MiscParams.ProgramType is Application or Applet and flag.process_address_space == AddressSpace64Bit. Using this makes SystemCalls MapPhysicalMemory & UnmapPhysicalMemory unavailable.
		tc::bn::le32<uint32_t> version; // sdk will set this to default_core_version if available
		tc::bn::le32<uint32_t> main_thread_stack_size;
		tc::bn::string<meta::kNameMaxLen> name; // important
		tc::bn::string<meta::kProductCodeMaxLen> product_code; // can be empty
		std::array<byte_t, 0x30> reserved_3;
		struct sSection
		{
			tc::bn::le32<uint32_t> offset;
			tc::bn::le32<uint32_t> size;
		} aci, aci_desc;
	};
	static_assert(sizeof(sMetaHeader) == 0x80, "sMetaHeader size");
#pragma pack(pop)
}
}