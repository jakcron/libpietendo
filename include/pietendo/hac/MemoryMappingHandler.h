	/**
	 * @file MemoryMappingHandler.h
	 * @brief Declaration of pie::hac::MemoryMappingHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>

namespace pie { namespace hac {
	
class MemoryMappingHandler :
	public IKernelCapabilityHandler
{
public:
	struct sMemoryMapping
	{
		uint32_t addr; // page index
		uint32_t size; // page num
		kc::MemoryPermission perm;
		kc::MappingType type;

		bool operator==(const sMemoryMapping& other) const
		{
			return (addr == other.addr) \
				&& (size == other.size) \
				&& (perm == other.perm) \
				&& (type == other.type);
		}

		bool operator!=(const sMemoryMapping& other) const
		{
			return !operator==(other);
		}

		const sMemoryMapping& operator=(const sMemoryMapping& other)
		{
			addr = other.addr;
			size = other.size;
			perm = other.perm;
			type = other.type;

			return *this;
		}
	};

	MemoryMappingHandler();

	void operator=(const MemoryMappingHandler& other);
	bool operator==(const MemoryMappingHandler& other) const;
	bool operator!=(const MemoryMappingHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	const std::vector<sMemoryMapping>& getMemoryMaps() const;
	const std::vector<sMemoryMapping>& getIoMemoryMaps() const;

private:
	const std::string kModuleName = "MEMORY_MAPPING_HANDLER";
	static const uint32_t kMaxPageAddr = (1 << 24) - 1;
	static const uint32_t kMaxPageNum = (1 << 20) - 1;

	bool mIsSet;
	std::vector<sMemoryMapping> mMemRange;
	std::vector<sMemoryMapping> mMemPage;
};

}} // namespace pie::hac