#pragma once
#include <nn/hac/define/cnmt.h>
#include <nn/hac/ContentMetaInfo.h>

namespace nn
{
namespace hac
{
	class SystemUpdateMetaExtendedData
	{
	public:
		struct FirmwareVariationInfo
		{
			uint32_t variation_id;
			std::vector<nn::hac::ContentMetaInfo> meta;

			bool operator==(const FirmwareVariationInfo& other) const
			{
				return variation_id == other.variation_id \
					&& meta == other.meta;
			}

			bool operator!=(const FirmwareVariationInfo& other) const
			{
				return !(*this == other);
			}
		};

		SystemUpdateMetaExtendedData();
		SystemUpdateMetaExtendedData(const SystemUpdateMetaExtendedData& other);

		void operator=(const SystemUpdateMetaExtendedData& other);
		bool operator==(const SystemUpdateMetaExtendedData& other) const;
		bool operator!=(const SystemUpdateMetaExtendedData& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint32_t getFormatVersion() const;
		void setFormatVersion(uint32_t version);

		const std::vector<FirmwareVariationInfo>& getFirmwareVariationInfo() const;
		void setFirmwareVariationInfo(const std::vector<FirmwareVariationInfo>& info);
	private:
		const std::string kModuleName = "SYSTEM_UPDATE_META_EXTENDED_DATA";

		// byte model
		tc::ByteData mRawBinary;

		// variables
		uint32_t mFormatVersion;
		std::vector<FirmwareVariationInfo> mFirmwareVariationInfo;
	};
}
}