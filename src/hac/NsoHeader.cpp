#include <pietendo/hac/NsoHeader.h>

pie::hac::NsoHeader::NsoHeader()
{
	clear();
}

pie::hac::NsoHeader::NsoHeader(const NsoHeader& other)
{
	*this = other;
}

void pie::hac::NsoHeader::operator=(const NsoHeader& other)
{
	clear();
	mModuleId = other.mModuleId;
	mBssSize = other.mBssSize;
	mTextSegmentInfo = other.mTextSegmentInfo;
	mRoSegmentInfo = other.mRoSegmentInfo;
	mDataSegmentInfo = other.mDataSegmentInfo;
	mModuleNameInfo = other.mModuleNameInfo;
	mRoEmbeddedInfo = other.mRoEmbeddedInfo;
	mRoDynStrInfo = other.mRoDynStrInfo;
	mRoDynSymInfo = other.mRoDynSymInfo;
}


bool pie::hac::NsoHeader::operator==(const NsoHeader& other) const
{
	return (mModuleId == other.mModuleId) \
		&& (mBssSize == other.mBssSize) \
		&& (mTextSegmentInfo == other.mTextSegmentInfo) \
		&& (mRoSegmentInfo == other.mRoSegmentInfo) \
		&& (mDataSegmentInfo == other.mDataSegmentInfo) \
		&& (mModuleNameInfo == other.mModuleNameInfo) \
		&& (mRoEmbeddedInfo == other.mRoEmbeddedInfo) \
		&& (mRoDynStrInfo == other.mRoDynStrInfo) \
		&& (mRoDynSymInfo == other.mRoDynSymInfo);
}

bool pie::hac::NsoHeader::operator!=(const NsoHeader& other) const
{
	return !(*this == other);
}

void pie::hac::NsoHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sNsoHeader));
	pie::hac::sNsoHeader* hdr = (pie::hac::sNsoHeader*)mRawBinary.data();

	// set header identifers
	hdr->st_magic.wrap(nso::kNsoStructMagic);
	hdr->format_version.wrap(nso::kDefaultFormatVersion);

	// set moduleid
	hdr->module_id = mModuleId;

	// set bss size
	hdr->bss_size.wrap(mBssSize);

	// set text segment
	hdr->text.file_offset.wrap(mTextSegmentInfo.file_layout.offset);
	hdr->text.memory_offset.wrap(mTextSegmentInfo.memory_layout.offset);
	hdr->text.size.wrap(mTextSegmentInfo.memory_layout.size);
	hdr->text_file_size.wrap(mTextSegmentInfo.file_layout.size);
	if (mTextSegmentInfo.is_compressed)
	{
		hdr->flags.set((size_t)nso::HeaderFlags_TextCompress);
	}
	if (mTextSegmentInfo.is_hashed)
	{
		hdr->flags.set((size_t)nso::HeaderFlags_TextHash);
		hdr->text_hash = mTextSegmentInfo.hash;
	}

	// set ro segment
	hdr->ro.file_offset.wrap(mRoSegmentInfo.file_layout.offset);
	hdr->ro.memory_offset.wrap(mRoSegmentInfo.memory_layout.offset);
	hdr->ro.size.wrap(mRoSegmentInfo.memory_layout.size);
	hdr->ro_file_size.wrap(mRoSegmentInfo.file_layout.size);
	if (mRoSegmentInfo.is_compressed)
	{
		hdr->flags.set((size_t)nso::HeaderFlags_RoCompress);
	}
	if (mRoSegmentInfo.is_hashed)
	{
		hdr->flags.set((size_t)nso::HeaderFlags_RoHash);
		hdr->ro_hash = mRoSegmentInfo.hash;
	}

	// set data segment
	hdr->data.file_offset.wrap(mDataSegmentInfo.file_layout.offset);
	hdr->data.memory_offset.wrap(mDataSegmentInfo.memory_layout.offset);
	hdr->data.size.wrap(mDataSegmentInfo.memory_layout.size);
	hdr->data_file_size.wrap(mDataSegmentInfo.file_layout.size);
	if (mDataSegmentInfo.is_compressed)
	{
		hdr->flags.set((size_t)nso::HeaderFlags_DataCompress);
	}
	if (mDataSegmentInfo.is_hashed)
	{
		hdr->flags.set((size_t)nso::HeaderFlags_DataHash);
		hdr->data_hash = mDataSegmentInfo.hash;
	}
		
	// set module name info
	hdr->module_name_offset.wrap(mModuleNameInfo.offset);
	hdr->module_name_size.wrap(mModuleNameInfo.size);

	// set ro embedded info
	hdr->embedded.offset.wrap(mRoEmbeddedInfo.offset);
	hdr->embedded.size.wrap(mRoEmbeddedInfo.size);

	// set ro dyn str info
	hdr->dyn_str.offset.wrap(mRoDynStrInfo.offset);
	hdr->dyn_str.size.wrap(mRoDynStrInfo.size);

	// set ro dyn sym info
	hdr->dyn_sym.offset.wrap(mRoDynSymInfo.offset);
	hdr->dyn_sym.size.wrap(mRoDynSymInfo.size);
}

void pie::hac::NsoHeader::fromBytes(const byte_t* data, size_t len)
{
	// check input data size
	if (len < sizeof(sNsoHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NSO header size is too small");
	}

	// clear internal members
	clear();

	// allocate internal local binary copy
	mRawBinary = tc::ByteData(sizeof(sNsoHeader));
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// get sNsoHeader ptr
	const pie::hac::sNsoHeader* hdr = (const pie::hac::sNsoHeader*)mRawBinary.data();
	
	// check NSO signature
	if (hdr->st_magic.unwrap() != nso::kNsoStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NSO header corrupt (unrecognised header signature)");
	}

	// check NSO format version
	if (hdr->format_version.unwrap() != nso::kDefaultFormatVersion)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NSO header corrupt (unsupported format version)");
	}

	mModuleId = hdr->module_id;

	mBssSize = hdr->bss_size.unwrap();

	mTextSegmentInfo.file_layout.offset = hdr->text.file_offset.unwrap();
	mTextSegmentInfo.file_layout.size = hdr->text_file_size.unwrap();
	mTextSegmentInfo.memory_layout.offset = hdr->text.memory_offset.unwrap();
	mTextSegmentInfo.memory_layout.size = hdr->text.size.unwrap();
	mTextSegmentInfo.is_compressed = hdr->flags.test((size_t)nso::HeaderFlags_TextCompress);
	mTextSegmentInfo.is_hashed = hdr->flags.test((size_t)nso::HeaderFlags_TextHash);
	mTextSegmentInfo.hash = hdr->text_hash;

	mRoSegmentInfo.file_layout.offset = hdr->ro.file_offset.unwrap();
	mRoSegmentInfo.file_layout.size = hdr->ro_file_size.unwrap();
	mRoSegmentInfo.memory_layout.offset = hdr->ro.memory_offset.unwrap();
	mRoSegmentInfo.memory_layout.size = hdr->ro.size.unwrap();
	mRoSegmentInfo.is_compressed = hdr->flags.test((size_t)nso::HeaderFlags_RoCompress);
	mRoSegmentInfo.is_hashed = hdr->flags.test((size_t)nso::HeaderFlags_RoHash);
	mRoSegmentInfo.hash = hdr->ro_hash;

	mDataSegmentInfo.file_layout.offset = hdr->data.file_offset.unwrap();
	mDataSegmentInfo.file_layout.size = hdr->data_file_size.unwrap();
	mDataSegmentInfo.memory_layout.offset = hdr->data.memory_offset.unwrap();
	mDataSegmentInfo.memory_layout.size = hdr->data.size.unwrap();
	mDataSegmentInfo.is_compressed = hdr->flags.test((size_t)nso::HeaderFlags_DataCompress);
	mDataSegmentInfo.is_hashed = hdr->flags.test((size_t)nso::HeaderFlags_DataHash);
	mDataSegmentInfo.hash = hdr->data_hash;

	mModuleNameInfo.offset = hdr->module_name_offset.unwrap();
	mModuleNameInfo.size = hdr->module_name_size.unwrap();

	mRoEmbeddedInfo.offset = hdr->embedded.offset.unwrap();
	mRoEmbeddedInfo.size = hdr->embedded.size.unwrap();

	mRoDynStrInfo.offset = hdr->dyn_str.offset.unwrap();
	mRoDynStrInfo.size = hdr->dyn_str.size.unwrap();

	mRoDynSymInfo.offset = hdr->dyn_sym.offset.unwrap();
	mRoDynSymInfo.size = hdr->dyn_sym.size.unwrap();
}

const tc::ByteData& pie::hac::NsoHeader::getBytes() const
{
	return mRawBinary;
}

void pie::hac::NsoHeader::clear()
{
	mRawBinary = tc::ByteData();
	memset(mModuleId.data(), 0, mModuleId.size());
	mBssSize = 0;
	mTextSegmentInfo = sCodeSegment();
	mRoSegmentInfo = sCodeSegment();
	mDataSegmentInfo = sCodeSegment();
	mModuleNameInfo = sLayout();
	mRoEmbeddedInfo = sLayout();
	mRoDynStrInfo = sLayout();
	mRoDynSymInfo = sLayout();
}

const pie::hac::detail::module_id_t& pie::hac::NsoHeader::getModuleId() const
{
	return mModuleId;
}

void pie::hac::NsoHeader::setModuleId(const pie::hac::detail::module_id_t& id)
{
	mModuleId = id;
}

uint32_t pie::hac::NsoHeader::getBssSize() const
{
	return mBssSize;
}

void pie::hac::NsoHeader::setBssSize(uint32_t size)
{
	mBssSize = size;
}

const pie::hac::NsoHeader::sCodeSegment& pie::hac::NsoHeader::getTextSegmentInfo() const
{
	return mTextSegmentInfo;
}

void pie::hac::NsoHeader::setTextSegmentInfo(const sCodeSegment& info)
{
	mTextSegmentInfo = info;
}

const pie::hac::NsoHeader::sCodeSegment& pie::hac::NsoHeader::getRoSegmentInfo() const
{
	return mRoSegmentInfo;
}

void pie::hac::NsoHeader::setRoSegmentInfo(const sCodeSegment& info)
{
	mRoSegmentInfo = info;
}

const pie::hac::NsoHeader::sCodeSegment& pie::hac::NsoHeader::getDataSegmentInfo() const
{
	return mDataSegmentInfo;
}

void pie::hac::NsoHeader::setDataSegmentInfo(const sCodeSegment& info)
{
	mDataSegmentInfo = info;
}

const pie::hac::NsoHeader::sLayout& pie::hac::NsoHeader::getModuleNameInfo() const
{
	return mModuleNameInfo;
}

void pie::hac::NsoHeader::setModuleNameInfo(const sLayout& info)
{
	mModuleNameInfo = info;
}

const pie::hac::NsoHeader::sLayout& pie::hac::NsoHeader::getRoEmbeddedInfo() const
{
	return mRoEmbeddedInfo;
}

void pie::hac::NsoHeader::setRoEmbeddedInfo(const sLayout& info)
{
	mRoEmbeddedInfo = info;
}

const pie::hac::NsoHeader::sLayout& pie::hac::NsoHeader::getRoDynStrInfo() const
{
	return mRoDynStrInfo;
}

void pie::hac::NsoHeader::setRoDynStrInfo(const sLayout& info)
{
	mRoDynStrInfo = info;
}

const pie::hac::NsoHeader::sLayout& pie::hac::NsoHeader::getRoDynSymInfo() const
{
	return mRoDynSymInfo;
}

void pie::hac::NsoHeader::setRoDynSymInfo(const sLayout& info)
{
	mRoDynSymInfo = info;
}