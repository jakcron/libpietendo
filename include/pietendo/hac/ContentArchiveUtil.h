	/**
	 * @file ContentArchiveUtil.h
	 * @brief Declaration of pie::hac::ContentArchiveUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/nca.h>

namespace pie { namespace hac {
	
class ContentArchiveUtil
{
public:
	static inline size_t sectorToOffset(size_t sector_index) { return sector_index * pie::hac::nca::kSectorSize; }
	static void decryptContentArchiveHeader(const byte_t* src, byte_t* dst, const detail::aes128_xtskey_t& key);
	static void getNcaPartitionAesCtr(const pie::hac::sContentArchiveFsHeader* hdr, byte_t* aes_ctr);
	static void getNcaPartitionAesCtr(uint32_t generation, uint32_t secure_value, byte_t* aes_ctr);

	static std::string getFormatHeaderVersionAsString(pie::hac::nca::HeaderFormatVersion val);
	static std::string getProgramContentParititionIndexAsString(pie::hac::nca::ProgramContentPartitionIndex val);
	static std::string getDistributionTypeAsString(pie::hac::nca::DistributionType val);
	static std::string getContentTypeAsString(pie::hac::nca::ContentType val);
	static std::string getFormatTypeAsString(pie::hac::nca::FormatType val);
	static std::string getHashTypeAsString(pie::hac::nca::HashType val);
	static std::string getEncryptionTypeAsString(pie::hac::nca::EncryptionType val);
	static std::string getMetaDataHashTypeAsString(pie::hac::nca::MetaDataHashType val);
	static std::string getKeyAreaEncryptionKeyIndexAsString(pie::hac::nca::KeyAreaEncryptionKeyIndex val);
	static std::string getSdkAddonVersionAsString(uint32_t version);

private:
	const std::string kModuleName = "CONTENT_ARCHIVE_UTIL";
};

}} // namespace pie::hac