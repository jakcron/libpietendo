#pragma once
#include <nn/hac/define/types.h>
#include <nn/hac/KernelCapabilityEntry.h>

namespace nn
{
namespace hac
{
	class MiscParamsEntry
	{
	public:
		MiscParamsEntry();
		MiscParamsEntry(const KernelCapabilityEntry& kernel_cap);
		MiscParamsEntry(kc::ProgramType program_type);

		void operator=(const MiscParamsEntry& other);
		bool operator==(const MiscParamsEntry& other) const;
		bool operator!=(const MiscParamsEntry& other) const;

		// kernel capability
		const KernelCapabilityEntry& getKernelCapability() const;
		void setKernelCapability(const KernelCapabilityEntry& kernel_cap);

		// variables
		kc::ProgramType getProgramType() const;
		void setProgramType(kc::ProgramType type);
	private:
		const std::string kModuleName = "MISC_PARAMS_ENTRY";
		static const kc::KernelCapId kCapId = kc::KernelCapId::MiscParams;
		static const byte_t kValBits = 3;
		static const byte_t kMaxProgramType = (1 << kValBits) - 1;

		KernelCapabilityEntry mCap;
		kc::ProgramType mProgramType;

		inline void updateCapField()
		{
			uint32_t field = (byte_t)mProgramType & kMaxProgramType;
			mCap.setField(field);
		}

		inline void processCapField()
		{
			uint32_t field = mCap.getField();
			mProgramType = kc::ProgramType(field & kMaxProgramType);
		}
	};
}
}