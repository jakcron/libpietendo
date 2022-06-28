#include <pietendo/hac/ContentArchiveUtil.h>
#include <fmt/core.h>

void pie::hac::ContentArchiveUtil::decryptContentArchiveHeader(const byte_t* src, byte_t* dst, const detail::aes128_xtskey_t& key)
{
	// init aes-xts
	tc::crypto::Aes128XtsEncryptor enc;
	enc.initialize(key[0].data(), key[0].size(), key[1].data(), key[1].size(), pie::hac::nca::kSectorSize, false);

	// decrypt main header
	byte_t raw_hdr[pie::hac::nca::kSectorSize];
	enc.decrypt(raw_hdr, src + sectorToOffset(1), pie::hac::nca::kSectorSize, 1);
	bool useNca2SectorIndex = ((pie::hac::sContentArchiveHeader*)(raw_hdr))->st_magic.unwrap() == pie::hac::nca::kNca2StructMagic;

	// decrypt whole header
	for (size_t i = 0; i < pie::hac::nca::kHeaderSectorNum; i++)
	{
		enc.decrypt(dst + sectorToOffset(i), src + sectorToOffset(i), pie::hac::nca::kSectorSize, (i >= 2 && useNca2SectorIndex)? 0 : i);
	}
}

void pie::hac::ContentArchiveUtil::getNcaPartitionAesCtr(const pie::hac::sContentArchiveFsHeader* hdr, byte_t* aes_ctr)
{
	getNcaPartitionAesCtr(hdr->generation.unwrap(), hdr->secure_value.unwrap(), aes_ctr);
}

void pie::hac::ContentArchiveUtil::getNcaPartitionAesCtr(uint32_t generation, uint32_t secure_value, byte_t* aes_ctr)
{
	/*
	for (size_t i = 0; i < 8; i++)
	{
		ctr[7-i] = hdr->aes_ctr_upper[i];
		ctr[15-i] = 0;
	}
	*/
	// hdr->aes_ctr_upper = 00 01 02 03 04 05 06 07
	// output             = 07 06 05 04 03 02 01 00 
	// generation = 03020100, secure_value = 07060504
	tc::bn::be32<uint32_t>* aes_ctr_words = (tc::bn::be32<uint32_t>*)aes_ctr;
	aes_ctr_words[0].wrap(secure_value);
	aes_ctr_words[1].wrap(generation);
	aes_ctr_words[2].wrap(0);
	aes_ctr_words[3].wrap(0);
}


std::string pie::hac::ContentArchiveUtil::getFormatHeaderVersionAsString(pie::hac::nca::HeaderFormatVersion val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::FORMAT_NCA2):
		str = "NCA2";
		break;
	case (pie::hac::nca::FORMAT_NCA3):
		str = "NCA3";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getProgramContentParititionIndexAsString(pie::hac::nca::ProgramContentPartitionIndex val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::PARTITION_CODE):
		str = "code";
		break;
	case (pie::hac::nca::PARTITION_DATA):
		str = "data";
		break;
	case (pie::hac::nca::PARTITION_LOGO):
		str = "logo";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getDistributionTypeAsString(pie::hac::nca::DistributionType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::DistributionType::Download):
		str = "Download";
		break;
	case (pie::hac::nca::DistributionType::GameCard):
		str = "Game Card";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getContentTypeAsString(pie::hac::nca::ContentType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::ContentType::Program):
		str = "Program";
		break;
	case (pie::hac::nca::ContentType::Meta):
		str = "Meta";
		break;
	case (pie::hac::nca::ContentType::Control):
		str = "Control";
		break;
	case (pie::hac::nca::ContentType::Manual):
		str = "Manual";
		break;
	case (pie::hac::nca::ContentType::Data):
		str = "Data";
		break;
	case (pie::hac::nca::ContentType::PublicData):
		str = "PublicData";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getFormatTypeAsString(pie::hac::nca::FormatType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::FormatType::RomFs):
		str = "RomFs";
		break;
	case (pie::hac::nca::FormatType::PartitionFs):
		str = "PartitionFs";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getHashTypeAsString(pie::hac::nca::HashType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::HashType::Auto):
		str = "Auto";
		break;
	case (pie::hac::nca::HashType::None):
		str = "None";
		break;
	case (pie::hac::nca::HashType::HierarchicalSha256):
		str = "HierarchicalSha256";
		break;
	case (pie::hac::nca::HashType::HierarchicalIntegrity):
		str = "HierarchicalIntegrity";
		break;
	case (pie::hac::nca::HashType::AutoSha3):
		str = "AutoSha3";
		break;
	case (pie::hac::nca::HashType::HierarchicalSha3256):
		str = "HierarchicalSha3256";
		break;
	case (pie::hac::nca::HashType::HierarchicalIntegritySha3):
		str = "HierarchicalIntegritySha3";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getEncryptionTypeAsString(pie::hac::nca::EncryptionType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::EncryptionType::Auto):
		str = "Auto";
		break;
	case (pie::hac::nca::EncryptionType::None):
		str = "None";
		break;
	case (pie::hac::nca::EncryptionType::AesXts):
		str = "AesXts";
		break;
	case (pie::hac::nca::EncryptionType::AesCtr):
		str = "AesCtr";
		break;
	case (pie::hac::nca::EncryptionType::AesCtrEx):
		str = "AesCtrEx";
		break;
	case (pie::hac::nca::EncryptionType::AesCtrSkipLayerHash):
		str = "AesCtrSkipLayerHash";
		break;
	case (pie::hac::nca::EncryptionType::AesCtrExSkipLayerHash):
		str = "AesCtrExSkipLayerHash";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}


std::string pie::hac::ContentArchiveUtil::getMetaDataHashTypeAsString(pie::hac::nca::MetaDataHashType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::MetaDataHashType::None):
		str = "None";
		break;
	case (pie::hac::nca::MetaDataHashType::HierarchicalIntegrity):
		str = "HierarchicalIntegrity";
		break;
	case (pie::hac::nca::MetaDataHashType::HierarchicalIntegritySha3):
		str = "HierarchicalIntegritySha3";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getKeyAreaEncryptionKeyIndexAsString(pie::hac::nca::KeyAreaEncryptionKeyIndex val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nca::KAEK_IDX_APPLICATION):
		str = "Application";
		break;
	case (pie::hac::nca::KAEK_IDX_OCEAN):
		str = "Ocean";
		break;
	case (pie::hac::nca::KAEK_IDX_SYSTEM):
		str = "System";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::ContentArchiveUtil::getSdkAddonVersionAsString(uint32_t version)
{
	std::string str;

	uint32_t major, minor, build, relstep;
	major = (uint32_t)((version>>24) & 0xff);
	minor = (uint32_t)((version>>16) & 0xff);
	build = (uint32_t)((version>>8) & 0xff);
	relstep = (uint32_t)((version>>0) & 0xff);

	str = fmt::format("{:d}.{:d}.{:d}", major, minor, build);
	if (relstep > 0)
	{
		str += fmt::format("-{:d}", relstep);
	}
	
	return str;
}