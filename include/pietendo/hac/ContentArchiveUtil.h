#pragma once
#include <nn/hac/define/nca.h>

namespace nn
{
namespace hac
{
	class ContentArchiveUtil
	{
	public:
		static inline size_t sectorToOffset(size_t sector_index) { return sector_index * nn::hac::nca::kSectorSize; }
		static void decryptContentArchiveHeader(const byte_t* src, byte_t* dst, const detail::aes128_xtskey_t& key);
		static void getNcaPartitionAesCtr(const nn::hac::sContentArchiveFsHeader* hdr, byte_t* aes_ctr);
		static void getNcaPartitionAesCtr(uint32_t generation, uint32_t secure_value, byte_t* aes_ctr);

		static std::string getFormatHeaderVersionAsString(nn::hac::nca::HeaderFormatVersion val);
		static std::string getProgramContentParititionIndexAsString(nn::hac::nca::ProgramContentPartitionIndex val);
		static std::string getDistributionTypeAsString(nn::hac::nca::DistributionType val);
		static std::string getContentTypeAsString(nn::hac::nca::ContentType val);
		static std::string getFormatTypeAsString(nn::hac::nca::FormatType val);
		static std::string getHashTypeAsString(nn::hac::nca::HashType val);
		static std::string getEncryptionTypeAsString(nn::hac::nca::EncryptionType val);
		static std::string getMetaDataHashTypeAsString(nn::hac::nca::MetaDataHashType val);
		static std::string getKeyAreaEncryptionKeyIndexAsString(nn::hac::nca::KeyAreaEncryptionKeyIndex val);
		static std::string getSdkAddonVersionAsString(uint32_t version);

	private:
		const std::string kModuleName = "CONTENT_ARCHIVE_UTIL";
	};
}
}