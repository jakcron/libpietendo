	/**
	 * @file KernelCapabilityEntry.h
	 * @brief Declaration of pie::hac::KernelCapabilityEntry
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/kc.h>

namespace pie { namespace hac {
	
class KernelCapabilityEntry
{
public:

	KernelCapabilityEntry();
	KernelCapabilityEntry(kc::KernelCapId type);
	KernelCapabilityEntry(kc::KernelCapId type, uint32_t field);

	void operator=(const KernelCapabilityEntry& other);
	bool operator==(const KernelCapabilityEntry& other) const;
	bool operator!=(const KernelCapabilityEntry& other) const;

	uint32_t getCap() const;
	void setCap(uint32_t cap);

	kc::KernelCapId getType() const;
	void setType(kc::KernelCapId type);

	uint32_t getField() const;
	void setField(uint32_t field);

private:
	kc::KernelCapId mType;
	uint32_t mField;

	inline uint32_t getFieldShift() const { return (uint32_t)mType + 1; }
	inline uint32_t getFieldMask() const { return (1 << (31 - (uint32_t)mType)) - 1; }
	inline uint32_t getCapMask() const { return (1 << ((uint32_t)mType)) - 1; }
	inline kc::KernelCapId getCapId(uint32_t cap) const
	{
		kc::KernelCapId id = kc::KernelCapId::Invalid;
		
		for (byte_t tmp = 0; tmp < 31; tmp++)
		{
			if (((cap >> tmp) & 1) == 0)
			{
				id = (kc::KernelCapId)tmp;
				break;
			}
		}

		if (id == kc::KernelCapId::Invalid && cap == (uint32_t)0xffffffff)
			id = kc::KernelCapId::Stubbed;

		return id;
	}
};

}} // namespace pie::hac