#pragma once
#include <nn/hac/define/nro.h>

namespace nn
{
namespace hac
{
	class NroHeader
	{
	public:
		struct sSection
		{
			uint32_t memory_offset;
			uint32_t size;

			sSection() :
				memory_offset(0),
				size(0)
			{}

			void operator=(const sSection& other)
			{
				memory_offset = other.memory_offset;
				size = other.size;
			}

			bool operator==(const sSection& other) const
			{
				return (memory_offset == other.memory_offset) \
					&& (size == other.size);
			}

			bool operator!=(const sSection& other) const
			{
				return !(*this == other);
			}
		};

		NroHeader();
		NroHeader(const NroHeader& other);

		void operator=(const NroHeader& other);
		bool operator==(const NroHeader& other) const;
		bool operator!=(const NroHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		uint32_t getRoCrtEntryPoint() const;
		void setRoCrtEntryPoint(uint32_t addr);

		uint32_t getRoCrtModOffset() const;
		void setRoCrtModOffset(uint32_t mod_offset);

		uint32_t getNroSize() const;
		void setNroSize(uint32_t size);

		const sSection& getTextInfo() const;
		void setTextInfo(const sSection& info);

		const sSection& getRoInfo() const;
		void setRoInfo(const sSection& info);

		const sSection& getDataInfo() const;
		void setDataInfo(const sSection& info);

		uint32_t getBssSize() const;
		void setBssSize(uint32_t size);

		const nn::hac::detail::module_id_t& getModuleId() const;
		void setModuleId(const nn::hac::detail::module_id_t& id);

		const sSection& getRoEmbeddedInfo() const;
		void setRoEmbeddedInfo(const sSection& info);

		const sSection& getRoDynStrInfo() const;
		void setRoDynStrInfo(const sSection& info);

		const sSection& getRoDynSymInfo() const;
		void setRoDynSymInfo(const sSection& info);
	private:
		const std::string kModuleName = "NRO_HEADER";

		// binary
		tc::ByteData mRawBinary;

		// data
		uint32_t mRoCrtEntryPoint;
		uint32_t mRoCrtModOffset;
		uint32_t mNroSize;
		sSection mTextInfo;
		sSection mRoInfo;
		sSection mDataInfo;
		uint32_t mBssSize;
		nn::hac::detail::module_id_t mModuleId;
		sSection mRoEmbeddedInfo;
		sSection mRoDynStrInfo;
		sSection mRoDynSymInfo;
	};
}
}