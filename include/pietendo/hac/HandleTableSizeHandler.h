	/**
	 * @file HandleTableSizeHandler.h
	 * @brief Declaration of pie::hac::HandleTableSizeHandler
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/IKernelCapabilityHandler.h>
#include <pietendo/hac/HandleTableSizeEntry.h>

namespace pie { namespace hac {
	
class HandleTableSizeHandler :
	public IKernelCapabilityHandler
{
public:
	HandleTableSizeHandler();

	void operator=(const HandleTableSizeHandler& other);
	bool operator==(const HandleTableSizeHandler& other) const;
	bool operator!=(const HandleTableSizeHandler& other) const;

	// kernel capabilty list in/out
	void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
	void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
	void clear();
	bool isSet() const;

	// variables
	uint16_t getHandleTableSize() const;
	void setHandleTableSize(uint16_t size);

private:
	const std::string kModuleName = "HANDLE_TABLE_SIZE_HANDLER";
	static const size_t kMaxKernelCapNum = 1;

	bool mIsSet;
	HandleTableSizeEntry mEntry;
};

}} // namespace pie::hac