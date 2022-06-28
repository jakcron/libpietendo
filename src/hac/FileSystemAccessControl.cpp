#include <cstring>
#include <pietendo/hac/FileSystemAccessControl.h>

pie::hac::FileSystemAccessControl::FileSystemAccessControl()
{
	clear();
}

pie::hac::FileSystemAccessControl::FileSystemAccessControl(const FileSystemAccessControl & other)
{
	*this = other;
}

void pie::hac::FileSystemAccessControl::operator=(const FileSystemAccessControl & other)
{
	mRawBinary = other.mRawBinary;
	mVersion = other.mVersion;
	mFsAccess = other.mFsAccess;
	mContentOwnerIdList = other.mContentOwnerIdList;
	mSaveDataOwnerIdList = other.mSaveDataOwnerIdList;
}

bool pie::hac::FileSystemAccessControl::operator==(const FileSystemAccessControl & other) const
{
	return (mVersion == other.mVersion) \
		&& (mFsAccess == other.mFsAccess) \
		&& (mContentOwnerIdList == other.mContentOwnerIdList) \
		&& (mSaveDataOwnerIdList == other.mSaveDataOwnerIdList);
}

bool pie::hac::FileSystemAccessControl::operator!=(const FileSystemAccessControl & other) const
{
	return !(*this == other);
}

void pie::hac::FileSystemAccessControl::toBytes()
{
	// determine section layout
	struct sLayout {
		uint32_t offset, size;
	} content, savedata;

	content.offset = (uint32_t)align<size_t>(sizeof(sFacHeader), fac::kSectionAlignSize);
	if (mContentOwnerIdList.size() > 0)
		content.size = (uint32_t)(sizeof(uint32_t) + mContentOwnerIdList.size() * sizeof(uint64_t));
	else
		content.size = 0;

	savedata.offset = (uint32_t)(content.offset + (content.size > 0 ? align<uint32_t>(content.size, (uint32_t)fac::kSectionAlignSize) : 0));
	if (mSaveDataOwnerIdList.size() > 0)
		savedata.size = (uint32_t)(sizeof(uint32_t) + (uint32_t)align<size_t>(mSaveDataOwnerIdList.size(), fac::kSectionAlignSize) + (uint32_t)(mSaveDataOwnerIdList.size() * sizeof(uint64_t)));
	else
		savedata.size = 0;
	

	// get total size                                                                                     
	size_t total_size = std::max<uint32_t>(std::max<uint32_t>(content.offset + content.size, savedata.offset + savedata.size), (uint32_t)align<size_t>(sizeof(sFacHeader), fac::kSectionAlignSize));

	mRawBinary = tc::ByteData(total_size);
	sFacHeader* hdr = (sFacHeader*)mRawBinary.data();

	// set type
	hdr->version.wrap(mVersion);

	// flags
	for (size_t i = 0; i < mFsAccess.size(); i++)
	{
		hdr->fac_flags.set((size_t)mFsAccess[i]);
	}

	// set offset/size
	hdr->content_owner_ids.offset.wrap(content.offset);
	if (content.size > 0)
		hdr->content_owner_ids.size.wrap(content.size);
	hdr->save_data_owner_ids.offset.wrap(savedata.offset);
	if (savedata.size > 0)
		hdr->save_data_owner_ids.size.wrap(savedata.size);

	// set ids
	tc::bn::le32<uint32_t>* content_owner_id_num = (tc::bn::le32<uint32_t>*)(mRawBinary.data() + content.offset);
	tc::bn::le64<uint64_t>* content_owner_ids = (tc::bn::le64<uint64_t>*)(mRawBinary.data() + content.offset + sizeof(uint32_t));
	content_owner_id_num->wrap((uint32_t)mContentOwnerIdList.size());
	for (size_t i = 0; i < mContentOwnerIdList.size(); i++)
	{
		content_owner_ids[i].wrap(mContentOwnerIdList[i]);
	}

	tc::bn::le32<uint32_t>* save_data_owner_id_num = (tc::bn::le32<uint32_t>*)(mRawBinary.data() + savedata.offset);
	byte_t* save_data_owner_id_accessibility_array = (mRawBinary.data() + savedata.offset + sizeof(uint32_t));
	tc::bn::le64<uint64_t>* save_data_owner_ids = (tc::bn::le64<uint64_t>*)(mRawBinary.data() + savedata.offset + sizeof(uint32_t) + align<size_t>(mSaveDataOwnerIdList.size(), sizeof(uint32_t)));
	save_data_owner_id_num->wrap((uint32_t)mSaveDataOwnerIdList.size());
	for (size_t i = 0; i < mSaveDataOwnerIdList.size(); i++)
	{
		save_data_owner_id_accessibility_array[i] = (byte_t)mSaveDataOwnerIdList[i].access_type;
		save_data_owner_ids[i].wrap(mSaveDataOwnerIdList[i].id);
	}
}

void pie::hac::FileSystemAccessControl::fromBytes(const byte_t* data, size_t len)
{
	// check size
	if (len < sizeof(sFacHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "FileSystemAccessControlInfo binary is too small");
	}
	
	// clear variables
	clear();

	// save a copy of the header
	sFacHeader hdr;
	memcpy((void*)&hdr, data, sizeof(sFacHeader));

	// check format version
	if (hdr.version.unwrap() != fac::kFacFormatVersion)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "FileSystemAccessControlInfo format version unsupported");
	}
	
	// get total size
	size_t total_size = std::max<size_t>((size_t)std::max<uint32_t>(hdr.content_owner_ids.offset.unwrap() + hdr.content_owner_ids.size.unwrap(), hdr.save_data_owner_ids.offset.unwrap() + hdr.save_data_owner_ids.size.unwrap()), align<size_t>(sizeof(sFacHeader), fac::kSectionAlignSize));

	// validate binary size
	if (len < total_size)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "FileSystemAccessControlInfo binary is too small");
	}

	// allocate memory
	mRawBinary = tc::ByteData(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// save variables
	mVersion = hdr.version.unwrap();
	for (size_t i = 0; i < hdr.fac_flags.bit_size(); i++)
	{
		if (hdr.fac_flags.test(i))
		{
			mFsAccess.push_back((fac::FsAccessFlag)i);
		}
	}

	// save ids
	if (hdr.content_owner_ids.size.unwrap() > 0)
	{
		size_t content_owner_id_num = ((tc::bn::le32<uint32_t>*)(mRawBinary.data() + hdr.content_owner_ids.offset.unwrap()))->unwrap();
		tc::bn::le64<uint64_t>* content_owner_ids = (tc::bn::le64<uint64_t>*)(mRawBinary.data() + hdr.content_owner_ids.offset.unwrap() + sizeof(uint32_t));
		for (size_t i = 0; i < content_owner_id_num; i++)
		{
			mContentOwnerIdList.push_back(content_owner_ids[i].unwrap());
		}
	}
	if (hdr.save_data_owner_ids.size.unwrap() > 0)
	{
		size_t save_data_owner_id_num = ((tc::bn::le32<uint32_t>*)(mRawBinary.data() + hdr.save_data_owner_ids.offset.unwrap()))->unwrap();
		byte_t* save_data_owner_id_accessibility_array = (mRawBinary.data() + hdr.save_data_owner_ids.offset.unwrap() + sizeof(uint32_t));
		tc::bn::le64<uint64_t>* save_data_owner_ids = (tc::bn::le64<uint64_t>*)(mRawBinary.data() + hdr.save_data_owner_ids.offset.unwrap() + sizeof(uint32_t) + align(save_data_owner_id_num, fac::kSectionAlignSize));
		for (size_t i = 0; i < save_data_owner_id_num; i++)
		{
			mSaveDataOwnerIdList.push_back({ (fac::SaveDataOwnerIdAccessType)save_data_owner_id_accessibility_array[i], save_data_owner_ids[i].unwrap() });
		}
	}
}

const tc::ByteData& pie::hac::FileSystemAccessControl::getBytes() const
{
	return mRawBinary;
}

void pie::hac::FileSystemAccessControl::clear()
{
	mRawBinary = tc::ByteData();
	mVersion = 0;
	mFsAccess.clear();
	mContentOwnerIdList.clear();
	mSaveDataOwnerIdList.clear();
}

uint32_t pie::hac::FileSystemAccessControl::getFormatVersion() const
{
	return mVersion;
}

void pie::hac::FileSystemAccessControl::setFormatVersion(uint32_t format_version)
{
	mVersion = format_version;
}

const std::vector<pie::hac::fac::FsAccessFlag>& pie::hac::FileSystemAccessControl::getFsAccess() const
{
	return mFsAccess;
}

void pie::hac::FileSystemAccessControl::setFsAccess(const std::vector<pie::hac::fac::FsAccessFlag>& access)
{
	mFsAccess = access;
}

const std::vector<uint64_t>& pie::hac::FileSystemAccessControl::getContentOwnerIdList() const
{
	return mContentOwnerIdList;
}

void pie::hac::FileSystemAccessControl::setContentOwnerIdList(const std::vector<uint64_t>& list)
{
	mContentOwnerIdList = list;
}

const std::vector<pie::hac::FileSystemAccessControl::sSaveDataOwnerId>& pie::hac::FileSystemAccessControl::getSaveDataOwnerIdList() const
{
	return mSaveDataOwnerIdList;
}

void pie::hac::FileSystemAccessControl::setSaveDataOwnerIdList(const std::vector<sSaveDataOwnerId>& list)
{
	mSaveDataOwnerIdList = list;
}