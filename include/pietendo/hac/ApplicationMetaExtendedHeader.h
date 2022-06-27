#pragma once
#include <nn/hac/define/cnmt.h>

namespace nn
{
namespace hac
{
	class ApplicationMetaExtendedHeader
	{
	public:
		ApplicationMetaExtendedHeader();
		ApplicationMetaExtendedHeader(const ApplicationMetaExtendedHeader& other);

		void operator=(const ApplicationMetaExtendedHeader& other);
		bool operator==(const ApplicationMetaExtendedHeader& other) const;
		bool operator!=(const ApplicationMetaExtendedHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint64_t getPatchId() const;
		void setPatchId(uint64_t patch_id);

		uint32_t getRequiredSystemVersion() const;
		void setRequiredSystemVersion(uint32_t sys_ver);

		uint32_t getRequiredApplicationVersion() const;
		void setRequiredApplicationVersion(uint32_t app_ver);
	private:
		const std::string kModuleName = "APPLICATION_META_EXTENDED_HEADER";

		// binary blob
		tc::ByteData mRawBinary;

		// variables
		uint64_t mPatchId;
		uint32_t mRequiredSystemVersion;
		uint32_t mRequiredApplicationVersion;
	};
}
}