#pragma once
#include <nn/hac/define/cnmt.h>

namespace nn
{
namespace hac
{
	class SystemUpdateMetaExtendedHeader
	{
	public:
		SystemUpdateMetaExtendedHeader();
		SystemUpdateMetaExtendedHeader(const SystemUpdateMetaExtendedHeader& other);

		void operator=(const SystemUpdateMetaExtendedHeader& other);
		bool operator==(const SystemUpdateMetaExtendedHeader& other) const;
		bool operator!=(const SystemUpdateMetaExtendedHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint32_t getExtendedDataSize() const;
		void setExtendedDataSize(uint32_t size);

	private:
		const std::string kModuleName = "SYSTEM_UPDATE_META_EXTENDED_HEADER";

		// binary blob
		tc::ByteData mRawBinary;

		// variables
		uint32_t mExtendedDataSize;
	};
}
}