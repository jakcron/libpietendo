#pragma once
#include <nn/hac/IKernelCapabilityHandler.h>
#include <nn/hac/MiscFlagsEntry.h>

namespace nn
{
namespace hac
{
	class MiscFlagsHandler :
		public IKernelCapabilityHandler
	{
	public:
		MiscFlagsHandler();

		void operator=(const MiscFlagsHandler& other);
		bool operator==(const MiscFlagsHandler& other) const;
		bool operator!=(const MiscFlagsHandler& other) const;

		// kernel capabilty list in/out
		void importKernelCapabilityList(const std::vector<KernelCapabilityEntry>& caps);
		void exportKernelCapabilityList(std::vector<KernelCapabilityEntry>& caps) const;
		void clear();
		bool isSet() const;

		// variables
		const kc::MiscFlags& getMiscFlags() const;
		void setMiscFlags(const kc::MiscFlags& flag);

	private:
		const std::string kModuleName = "MISC_FLAGS_HANDLER";
		static const size_t kMaxKernelCapNum = 1;

		bool mIsSet;
		kc::MiscFlags mFlags;
	};
}
}