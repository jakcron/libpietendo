#include <pietendo/hac/SystemUpdateMetaExtendedData.h>

pie::hac::SystemUpdateMetaExtendedData::SystemUpdateMetaExtendedData()
{
	clear();
}

pie::hac::SystemUpdateMetaExtendedData::SystemUpdateMetaExtendedData(const SystemUpdateMetaExtendedData& other)
{
	*this = other;
}

void pie::hac::SystemUpdateMetaExtendedData::operator=(const SystemUpdateMetaExtendedData& other)
{
	clear();
	mRawBinary = other.mRawBinary;
	mFormatVersion = other.mFormatVersion;
	mFirmwareVariationInfo = other.mFirmwareVariationInfo;
}

bool pie::hac::SystemUpdateMetaExtendedData::operator==(const SystemUpdateMetaExtendedData& other) const
{
	return mFormatVersion == other.mFormatVersion \
		&& mFirmwareVariationInfo == other.mFirmwareVariationInfo;
}

bool pie::hac::SystemUpdateMetaExtendedData::operator!=(const SystemUpdateMetaExtendedData& other) const
{
	return !(*this == other);
}

void pie::hac::SystemUpdateMetaExtendedData::toBytes()
{	
	if (mFormatVersion == 1)
	{
		mRawBinary = tc::ByteData(sizeof(sSystemUpdateMetaExtendedDataHeader) + sizeof(sFirmwareVariationInfo_v1) * mFirmwareVariationInfo.size());

		sSystemUpdateMetaExtendedDataHeader* hdr = (sSystemUpdateMetaExtendedDataHeader*)(mRawBinary.data() + 0x0);
		sFirmwareVariationInfo_v1* variation_info = (sFirmwareVariationInfo_v1*)(mRawBinary.data() + sizeof(sSystemUpdateMetaExtendedDataHeader));

		// write header
		hdr->version.wrap(1);
		hdr->variation_count.wrap((uint32_t)mFirmwareVariationInfo.size());

		// write variations
		for (auto info = mFirmwareVariationInfo.begin(); info != mFirmwareVariationInfo.end(); info++, variation_info++)
		{
			if (info->meta.size() != 0)
			{
				throw tc::ArgumentException(kModuleName, "Overriding ContentInfoMeta is not supported in format version 1");
			}

			variation_info->firmware_variation_id.wrap(info->variation_id);
		}
	}
	else if (mFormatVersion == 2)
	{
		size_t total_size = 0;

		size_t header_offset = total_size;
		total_size += sizeof(sSystemUpdateMetaExtendedDataHeader);

		// include firmware_variation_id array
		size_t firmware_variation_ids_offset = total_size;
		total_size += sizeof(tc::bn::le32<uint32_t>) * mFirmwareVariationInfo.size();

		// include firmare variation info array
		size_t firmware_variation_info_offset = total_size;
		total_size += sizeof(sFirmwareVariationInfo_v2) * mFirmwareVariationInfo.size();

		// include any included ContentInfoMeta
		size_t content_info_meta_offset = total_size;
		for (auto info = mFirmwareVariationInfo.begin(); info != mFirmwareVariationInfo.end(); info++)
		{
			total_size += sizeof(sContentMetaInfo) * info->meta.size();
		}

		mRawBinary = tc::ByteData(total_size);

		// get pointers to each section
		sSystemUpdateMetaExtendedDataHeader* hdr_ptr = (sSystemUpdateMetaExtendedDataHeader*)(mRawBinary.data() + header_offset);
		tc::bn::le32<uint32_t>* firmware_variation_ids_ptr = (tc::bn::le32<uint32_t>*)(mRawBinary.data() + firmware_variation_ids_offset);
		sFirmwareVariationInfo_v2* variation_info_ptr = (sFirmwareVariationInfo_v2*)(mRawBinary.data() + firmware_variation_info_offset);
		sContentMetaInfo* meta_info_ptr = (sContentMetaInfo*)(mRawBinary.data() + content_info_meta_offset);

		// write header
		hdr_ptr->version.wrap(2);
		hdr_ptr->variation_count.wrap((uint32_t)mFirmwareVariationInfo.size());

		// write variation
		for (auto variation_info_itr = mFirmwareVariationInfo.begin(); \
			variation_info_itr != mFirmwareVariationInfo.end(); \
			variation_info_itr++, firmware_variation_ids_ptr++, variation_info_ptr++)
		{
			(*firmware_variation_ids_ptr).wrap(variation_info_itr->variation_id);
			variation_info_ptr->refer_to_base = variation_info_itr->meta.size() == 0;
			variation_info_ptr->meta_count.wrap((uint32_t)variation_info_itr->meta.size());

			for (auto meta_itr = variation_info_itr->meta.begin(); meta_itr != variation_info_itr->meta.end(); meta_itr++, meta_info_ptr++)
			{
				meta_itr->toBytes();
				auto meta_bytes = meta_itr->getBytes();
				memcpy(meta_info_ptr, meta_bytes.data(), sizeof(sContentMetaInfo));
			}
		}
	}
	else
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Unsupported format version");
	}
	
}

void pie::hac::SystemUpdateMetaExtendedData::fromBytes(const byte_t* bytes, size_t len)
{
	clear();

	size_t total_size = sizeof(sSystemUpdateMetaExtendedDataHeader);

	if (len < total_size)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "SystemUpdateMetaExtendedData too small");
	}

	const sSystemUpdateMetaExtendedDataHeader* hdr_ptr = (const sSystemUpdateMetaExtendedDataHeader*)bytes;
	uint32_t format_version = hdr_ptr->version.unwrap();
	uint32_t variation_count = hdr_ptr->variation_count.unwrap();

	if (format_version == 1)
	{
		total_size += sizeof(sFirmwareVariationInfo_v1) * variation_count;

		if (len < total_size)
		{
			throw tc::ArgumentOutOfRangeException(kModuleName, "SystemUpdateMetaExtendedData too small");
		}

		mRawBinary = tc::ByteData(total_size);
		memcpy(mRawBinary.data(), bytes, mRawBinary.size());

		hdr_ptr = (const sSystemUpdateMetaExtendedDataHeader*)(mRawBinary.data() + 0);
		const sFirmwareVariationInfo_v1* firmware_variation_info_ptr = (const sFirmwareVariationInfo_v1*)(mRawBinary.data() + sizeof(sSystemUpdateMetaExtendedDataHeader));

		// save format version
		mFormatVersion = format_version;

		// save firmware variation info
		for (size_t i = 0; i < variation_count; i++, firmware_variation_info_ptr++)
		{
			mFirmwareVariationInfo.push_back({firmware_variation_info_ptr->firmware_variation_id.unwrap(), std::vector<ContentMetaInfo>()});
		}
	}
	else if (format_version == 2)
	{
		size_t firmware_variation_id_offset = 0;
		const tc::bn::le32<uint32_t>* firmware_variation_id_ptr = nullptr;

		size_t firmware_variation_info_offset = 0;
		const sFirmwareVariationInfo_v2* firmware_variation_info_ptr = nullptr;

		size_t content_meta_info_offset = 0;
		const sContentMetaInfo* content_meta_info_ptr = nullptr;


		firmware_variation_id_offset = total_size;
		total_size += sizeof(tc::bn::le32<uint32_t>) * variation_count;

		firmware_variation_info_offset = total_size;
		total_size += sizeof(sFirmwareVariationInfo_v2) * variation_count;

		// check if data can contain extended data if no content meta info is present
		if (len < total_size)
		{
			throw tc::ArgumentOutOfRangeException(kModuleName, "SystemUpdateMetaExtendedData too small");
		}

		content_meta_info_offset = total_size;
		
		// update total size with content meta info if present
		firmware_variation_info_ptr = (const sFirmwareVariationInfo_v2*)(bytes + firmware_variation_info_offset);
		for (size_t i = 0; i < variation_count; i++)
		{
			total_size += sizeof(sContentMetaInfo) * firmware_variation_info_ptr[i].meta_count.unwrap();
		}

		// check if data can contain extended data
		if (len < total_size)
		{
			throw tc::ArgumentOutOfRangeException(kModuleName, "SystemUpdateMetaExtendedData too small");
		}

		mRawBinary = tc::ByteData(total_size);
		memcpy(mRawBinary.data(), bytes, mRawBinary.size());

		firmware_variation_id_ptr = (const tc::bn::le32<uint32_t>*)(mRawBinary.data() + firmware_variation_id_offset);
		firmware_variation_info_ptr = (const sFirmwareVariationInfo_v2*)(mRawBinary.data() + firmware_variation_info_offset);
		content_meta_info_ptr = (const sContentMetaInfo*)(mRawBinary.data() + content_meta_info_offset);

		// save format version
		mFormatVersion = format_version;

		// save firmware variation info
		for (size_t i = 0; i < variation_count; i++, firmware_variation_id_ptr++, firmware_variation_info_ptr++)
		{
			FirmwareVariationInfo firmware_variation_info;
			firmware_variation_info.variation_id = firmware_variation_id_ptr->unwrap();
			if (firmware_variation_info_ptr->refer_to_base == false)
			{
				for (size_t j = 0; j < firmware_variation_info_ptr->meta_count.unwrap(); j++)
				{
					ContentMetaInfo content_meta_info;
					content_meta_info.fromBytes((const byte_t*)content_meta_info_ptr, sizeof(sContentMetaInfo));
					firmware_variation_info.meta.push_back(content_meta_info);
				}
			}
			mFirmwareVariationInfo.push_back({firmware_variation_info.variation_id, firmware_variation_info.meta});
		}
	}
	else
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Unsupported format version");
	}
}

const tc::ByteData& pie::hac::SystemUpdateMetaExtendedData::getBytes() const
{
	return mRawBinary;
}

void pie::hac::SystemUpdateMetaExtendedData::clear()
{
	mRawBinary = tc::ByteData();
	mFormatVersion = 0;
	mFirmwareVariationInfo.clear();
}

uint32_t pie::hac::SystemUpdateMetaExtendedData::getFormatVersion() const
{
	return mFormatVersion;
}

void pie::hac::SystemUpdateMetaExtendedData::setFormatVersion(uint32_t version)
{
	mFormatVersion = version;
}

const std::vector<pie::hac::SystemUpdateMetaExtendedData::FirmwareVariationInfo>& pie::hac::SystemUpdateMetaExtendedData::getFirmwareVariationInfo() const
{
	return mFirmwareVariationInfo;
}

void pie::hac::SystemUpdateMetaExtendedData::setFirmwareVariationInfo(const std::vector<pie::hac::SystemUpdateMetaExtendedData::FirmwareVariationInfo>& info)
{
	mFirmwareVariationInfo = info;
}
