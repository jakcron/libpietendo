#include <nn/hac/NroHeader.h>

nn::hac::NroHeader::NroHeader()
{
	clear();
}

nn::hac::NroHeader::NroHeader(const NroHeader& other)
{
	*this = other;
}

void nn::hac::NroHeader::operator=(const NroHeader& other)
{
	clear();
	mRoCrtEntryPoint = other.mRoCrtEntryPoint;
	mRoCrtModOffset = other.mRoCrtModOffset;
	mNroSize = other.mNroSize;
	mTextInfo = other.mTextInfo;
	mTextInfo = other.mTextInfo;
	mRoInfo = other.mRoInfo;
	mDataInfo = other.mDataInfo;
	mBssSize = other.mBssSize;
	mModuleId = other.mModuleId;
	mRoEmbeddedInfo = other.mRoEmbeddedInfo;
	mRoDynStrInfo = other.mRoDynStrInfo;
	mRoDynSymInfo = other.mRoDynSymInfo;
}

bool nn::hac::NroHeader::operator==(const NroHeader& other) const
{
	return (mRoCrtEntryPoint == other.mRoCrtEntryPoint) \
		&& (mRoCrtModOffset == other.mRoCrtModOffset) \
		&& (mNroSize == other.mNroSize) \
		&& (mTextInfo == other.mTextInfo) \
		&& (mTextInfo == other.mTextInfo) \
		&& (mRoInfo == other.mRoInfo) \
		&& (mDataInfo == other.mDataInfo) \
		&& (mBssSize == other.mBssSize) \
		&& (mModuleId == other.mModuleId) \
		&& (mRoEmbeddedInfo == other.mRoEmbeddedInfo) \
		&& (mRoDynStrInfo == other.mRoDynStrInfo) \
		&& (mRoDynSymInfo == other.mRoDynSymInfo);
}

bool nn::hac::NroHeader::operator!=(const NroHeader& other) const
{
	return !(*this == other);
}

void nn::hac::NroHeader::toBytes()
{
	mRawBinary = tc::ByteData(sizeof(sNroHeader));
	nn::hac::sNroHeader* hdr = (nn::hac::sNroHeader*)mRawBinary.data();

	// set header identifers
	hdr->st_magic.wrap(nro::kNroStructMagic);
	hdr->format_version.wrap(nro::kDefaultFormatVersion);
	hdr->flags.wrap(0);

	// set ro crt
	hdr->ro_crt.entry_point_insn.wrap(mRoCrtEntryPoint);
	hdr->ro_crt.mod_offset.wrap(mRoCrtModOffset);

	// set nro size
	hdr->size.wrap(mNroSize);

	// set text section
	hdr->text.memory_offset.wrap(mTextInfo.memory_offset);
	hdr->text.size.wrap(mTextInfo.size);

	// set ro section
	hdr->ro.memory_offset.wrap(mRoInfo.memory_offset);
	hdr->ro.size.wrap(mRoInfo.size);

	// set data section
	hdr->data.memory_offset.wrap(mDataInfo.memory_offset);
	hdr->data.size.wrap(mDataInfo.size);

	// set bss size
	hdr->bss_size.wrap(mBssSize);

	// set moduleid
	hdr->module_id = mModuleId;

	// set ro embedded info
	hdr->embedded.memory_offset.wrap(mRoEmbeddedInfo.memory_offset);
	hdr->embedded.size.wrap(mRoEmbeddedInfo.size);

	// set ro dyn str info
	hdr->dyn_str.memory_offset.wrap(mRoDynStrInfo.memory_offset);
	hdr->dyn_str.size.wrap(mRoDynStrInfo.size);

	// set ro dyn sym info
	hdr->dyn_sym.memory_offset.wrap(mRoDynSymInfo.memory_offset);
	hdr->dyn_sym.size.wrap(mRoDynSymInfo.size);
}

void nn::hac::NroHeader::fromBytes(const byte_t* data, size_t len)
{
	// check input data size
	if (len < sizeof(sNroHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NRO header size is too small");
	}

	// clear internal members
	clear();

	// allocate internal local binary copy
	mRawBinary = tc::ByteData(sizeof(sNroHeader));
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// get sNroHeader ptr
	const nn::hac::sNroHeader* hdr = (const nn::hac::sNroHeader*)mRawBinary.data();
	
	// check NRO signature
	if (hdr->st_magic.unwrap() != nro::kNroStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NRO header corrupt (unrecognised header signature)");
	}

	// check NRO format version
	if (hdr->format_version.unwrap() != nro::kDefaultFormatVersion)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NRO header corrupt (unsupported format version)");
	}

	// check NRO flags
	if (hdr->flags.unwrap() != 0)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "NRO header corrupt (unsupported flag)");
	}

	mRoCrtEntryPoint = hdr->ro_crt.entry_point_insn.unwrap();
	mRoCrtModOffset = hdr->ro_crt.mod_offset.unwrap();
	mNroSize = hdr->size.unwrap();
	mTextInfo.memory_offset = hdr->text.memory_offset.unwrap();
	mTextInfo.size = hdr->text.size.unwrap();
	mRoInfo.memory_offset = hdr->ro.memory_offset.unwrap();
	mRoInfo.size = hdr->ro.size.unwrap();
	mDataInfo.memory_offset = hdr->data.memory_offset.unwrap();
	mDataInfo.size = hdr->data.size.unwrap();
	mBssSize = hdr->bss_size.unwrap();
	mModuleId = hdr->module_id;

	mRoEmbeddedInfo.memory_offset = hdr->embedded.memory_offset.unwrap();
	mRoEmbeddedInfo.size = hdr->embedded.size.unwrap();

	mRoDynStrInfo.memory_offset = hdr->dyn_str.memory_offset.unwrap();
	mRoDynStrInfo.size = hdr->dyn_str.size.unwrap();

	mRoDynSymInfo.memory_offset = hdr->dyn_sym.memory_offset.unwrap();
	mRoDynSymInfo.size = hdr->dyn_sym.size.unwrap();
}

const tc::ByteData& nn::hac::NroHeader::getBytes() const
{
	return mRawBinary;
}

void nn::hac::NroHeader::clear()
{
	mRawBinary = tc::ByteData();
	mRoCrtEntryPoint = 0;
	mRoCrtModOffset = 0;
	mTextInfo = sSection();
	mRoInfo = sSection();
	mDataInfo = sSection();
	mBssSize = 0;
	memset(mModuleId.data(), 0, mModuleId.size());
	mRoEmbeddedInfo = sSection();
	mRoDynStrInfo = sSection();
	mRoDynSymInfo = sSection();
}

uint32_t nn::hac::NroHeader::getRoCrtEntryPoint() const
{
	return mRoCrtEntryPoint;
}

void nn::hac::NroHeader::setRoCrtEntryPoint(uint32_t addr)
{
	mRoCrtEntryPoint = addr;
}

uint32_t nn::hac::NroHeader::getRoCrtModOffset() const
{
	return mRoCrtModOffset;
}

void nn::hac::NroHeader::setRoCrtModOffset(uint32_t offset)
{
	mRoCrtModOffset = offset;
}

uint32_t nn::hac::NroHeader::getNroSize() const
{
	return mNroSize;
}

void nn::hac::NroHeader::setNroSize(uint32_t size)
{
	mNroSize = size;
}

const nn::hac::NroHeader::sSection& nn::hac::NroHeader::getTextInfo() const
{
	return mTextInfo;
}

void nn::hac::NroHeader::setTextInfo(const sSection& info)
{
	mTextInfo = info;
}

const nn::hac::NroHeader::sSection& nn::hac::NroHeader::getRoInfo() const
{
	return mRoInfo;
}

void nn::hac::NroHeader::setRoInfo(const sSection& info)
{
	mRoInfo = info;
}

const nn::hac::NroHeader::sSection& nn::hac::NroHeader::getDataInfo() const
{
	return mDataInfo;
}

void nn::hac::NroHeader::setDataInfo(const sSection& info)
{
	mDataInfo = info;
}

uint32_t nn::hac::NroHeader::getBssSize() const
{
	return mBssSize;
}

void nn::hac::NroHeader::setBssSize(uint32_t size)
{
	mBssSize = size;
}

const nn::hac::detail::module_id_t& nn::hac::NroHeader::getModuleId() const
{
	return mModuleId;
}

void nn::hac::NroHeader::setModuleId(const nn::hac::detail::module_id_t& id)
{
	mModuleId = id;
}

const nn::hac::NroHeader::sSection& nn::hac::NroHeader::getRoEmbeddedInfo() const
{
	return mRoEmbeddedInfo;
}

void nn::hac::NroHeader::setRoEmbeddedInfo(const sSection& info)
{
	mRoEmbeddedInfo = info;
}

const nn::hac::NroHeader::sSection& nn::hac::NroHeader::getRoDynStrInfo() const
{
	return mRoDynStrInfo;
}

void nn::hac::NroHeader::setRoDynStrInfo(const sSection& info)
{
	mRoDynStrInfo = info;
}

const nn::hac::NroHeader::sSection& nn::hac::NroHeader::getRoDynSymInfo() const
{
	return mRoDynSymInfo;
}

void nn::hac::NroHeader::setRoDynSymInfo(const sSection& info)
{
	mRoDynSymInfo = info;
}