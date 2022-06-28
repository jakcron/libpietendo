	/**
	 * @file HierarchicalSha256Header.h
	 * @brief Declaration of pie::hac::HierarchicalSha256Header
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/hierarchicalsha256.h>

#include <tc/NotImplementedException.h>

namespace pie { namespace hac {
	
class HierarchicalSha256Header
{
public:
	struct sLayer
	{
		int64_t offset;
		int64_t size;

		void operator=(const sLayer& other)
		{
			offset = other.offset;
			size = other.size;
		}

		bool operator==(const sLayer& other) const
		{
			return (offset == other.offset && size == other.size);
		}

		bool operator!=(const sLayer& other) const
		{
			return !(*this == other);
		}
	};

	HierarchicalSha256Header();
	HierarchicalSha256Header(const HierarchicalSha256Header& other);

	void operator=(const HierarchicalSha256Header& other);
	bool operator==(const HierarchicalSha256Header& other) const;
	bool operator!=(const HierarchicalSha256Header& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData&  getBytes() const;

	// variables
	void clear();

	const pie::hac::detail::sha256_hash_t& getMasterHash() const;
	void setMasterHash(const pie::hac::detail::sha256_hash_t& master_hash);

	size_t getHashBlockSize() const;
	void setHashBlockSize(size_t hash_block_size);

	const std::vector<sLayer>& getLayerInfo() const;
	void setLayerInfo(const std::vector<sLayer>& layer_info);
private:
	const std::string kModuleName = "HIERARCHICAL_SHA256_HEADER";

	// binary
	tc::ByteData mRawBinary;

	// data
	pie::hac::detail::sha256_hash_t mMasterHash;
	size_t mHashBlockSize;
	std::vector<sLayer> mLayerInfo;
};

}} // namespace pie::hac