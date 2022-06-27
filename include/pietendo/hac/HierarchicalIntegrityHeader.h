#pragma once
#include <nn/hac/define/hierarchicalintegrity.h>

#include <tc/NotImplementedException.h>

namespace nn
{
namespace hac
{
	class HierarchicalIntegrityHeader
	{
	public:
		struct sLayer
		{
			int64_t offset;
			int64_t size;
			int64_t block_size;

			void operator=(const sLayer& other)
			{
				offset = other.offset;
				size = other.size;
				block_size = other.block_size;
			}

			bool operator==(const sLayer& other) const
			{
				return (offset == other.offset && size == other.size && block_size == other.block_size);
			}

			bool operator!=(const sLayer& other) const
			{
				return !(*this == other);
			}
		};

		HierarchicalIntegrityHeader();
		HierarchicalIntegrityHeader(const HierarchicalIntegrityHeader& other);

		void operator=(const HierarchicalIntegrityHeader& other);
		bool operator==(const HierarchicalIntegrityHeader& other) const;
		bool operator!=(const HierarchicalIntegrityHeader& other) const;

		// IByteModel
		void toBytes();
		void fromBytes(const byte_t* bytes, size_t len);
		const tc::ByteData& getBytes() const;

		// variables
		void clear();

		const std::vector<sLayer>& getLayerInfo() const;
		void setLayerInfo(const std::vector<sLayer>& layer_info);

		const std::vector<nn::hac::detail::sha256_hash_t>& getMasterHashList() const;
		void setMasterHashList(const std::vector<nn::hac::detail::sha256_hash_t>& master_hash_list);
	private:
		const std::string kModuleName = "HIERARCHICAL_INTEGRITY_HEADER";

		// binary
		tc::ByteData mRawBinary;

		// data
		std::vector<sLayer> mLayerInfo;
		std::vector<nn::hac::detail::sha256_hash_t> mMasterHashList;
	};
}
}