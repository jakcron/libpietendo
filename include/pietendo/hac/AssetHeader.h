#pragma once
#include <nn/hac/define/aset.h>

namespace nn
{
namespace hac
{
	class AssetHeader
	{
	public:
		struct sSection
		{
			int64_t offset;
			int64_t size;

			sSection() :
				offset(0),
				size(0)
			{}

			void operator=(const sSection& other)
			{
				offset = other.offset;
				size = other.size;
			}

			bool operator==(const sSection& other) const
			{
				return (offset == other.offset) \
					&& (size == other.size);
			}

			bool operator!=(const sSection& other) const
			{
				return !operator==(other);
			}
		};

		AssetHeader();
		AssetHeader(const AssetHeader& other);

		void operator=(const AssetHeader& other);
		bool operator==(const AssetHeader& other) const;
		bool operator!=(const AssetHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		const sSection& getIconInfo() const;
		void setIconInfo(const sSection& info);

		const sSection& getNacpInfo() const;
		void setNacpInfo(const sSection& info);

		const sSection& getRomfsInfo() const;
		void setRomfsInfo(const sSection& info);
	private:
		const std::string kModuleName = "NRO_ASSET_HEADER";

		// binary
		tc::ByteData mRawBinary;

		// data
		sSection mIconInfo;
		sSection mNacpInfo;
		sSection mRomfsInfo;
	};
}
}