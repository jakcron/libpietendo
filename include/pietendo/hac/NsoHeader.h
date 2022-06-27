#pragma once
#include <nn/hac/define/nso.h>

namespace nn
{
namespace hac
{
	class NsoHeader
	{
	public:
		struct sLayout
		{
			uint32_t offset;
			uint32_t size;

			sLayout() :
				offset(0),
				size(0)
			{}

			void operator=(const sLayout& other)
			{
				offset = other.offset;
				size = other.size;
			}

			bool operator==(const sLayout& other) const
			{
				return (offset == other.offset) \
					&& (size == other.size);
			}

			bool operator!=(const sLayout& other) const
			{
				return !(*this == other);
			}
		};

		struct sCodeSegment
		{
			sLayout file_layout;
			sLayout memory_layout;
			bool is_compressed;
			bool is_hashed;
			detail::sha256_hash_t hash;

			sCodeSegment() :
				file_layout(),
				memory_layout(),
				is_compressed(false),
				is_hashed(false),
				hash({0})
			{}
			
			void operator=(const sCodeSegment& other)
			{
				file_layout = other.file_layout;
				memory_layout = other.memory_layout;
				is_compressed = other.is_compressed;
				is_hashed = other.is_hashed;
				hash = other.hash;
			}

			bool operator==(const sCodeSegment& other) const
			{
				return (file_layout == other.file_layout) \
					&& (memory_layout == other.memory_layout) \
					&& (is_compressed == other.is_compressed) \
					&& (is_hashed == other.is_hashed) \
					&& (hash == other.hash);
			}

			bool operator!=(const sCodeSegment& other) const
			{
				return !(*this == other);
			}
		};

		NsoHeader();
		NsoHeader(const NsoHeader& other);

		void operator=(const NsoHeader& other);
		bool operator==(const NsoHeader& other) const;
		bool operator!=(const NsoHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();
		
		const nn::hac::detail::module_id_t& getModuleId() const;
		void setModuleId(const nn::hac::detail::module_id_t& id);

		uint32_t getBssSize() const;
		void setBssSize(uint32_t size);

		const sCodeSegment& getTextSegmentInfo() const;
		void setTextSegmentInfo(const sCodeSegment& info);

		const sCodeSegment& getRoSegmentInfo() const;
		void setRoSegmentInfo(const sCodeSegment& info);

		const sCodeSegment& getDataSegmentInfo() const;
		void setDataSegmentInfo(const sCodeSegment& info);

		const sLayout& getModuleNameInfo() const;
		void setModuleNameInfo(const sLayout& info);

		const sLayout& getRoEmbeddedInfo() const;
		void setRoEmbeddedInfo(const sLayout& info);

		const sLayout& getRoDynStrInfo() const;
		void setRoDynStrInfo(const sLayout& info);

		const sLayout& getRoDynSymInfo() const;
		void setRoDynSymInfo(const sLayout& info);
	private:
		const std::string kModuleName = "NSO_HEADER";

		// binary
		tc::ByteData mRawBinary;

		// data
		nn::hac::detail::module_id_t mModuleId;
		uint32_t mBssSize;
		sCodeSegment mTextSegmentInfo;
		sCodeSegment mRoSegmentInfo;
		sCodeSegment mDataSegmentInfo;
		sLayout mModuleNameInfo;
		sLayout mRoEmbeddedInfo;
		sLayout mRoDynStrInfo;
		sLayout mRoDynSymInfo;
	};
}
}