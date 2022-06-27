#include <nn/hac/AccessControlInfo.h>

nn::hac::AccessControlInfo::AccessControlInfo()
{
	clear();
}

nn::hac::AccessControlInfo::AccessControlInfo(const AccessControlInfo & other)
{
	*this = other;
}

void nn::hac::AccessControlInfo::operator=(const AccessControlInfo & other)
{
	mRawBinary = other.mRawBinary;
	mProgramId = other.mProgramId;
	mFileSystemAccessControl = other.mFileSystemAccessControl;
	mServiceAccessControl = other.mServiceAccessControl;
	mKernelCapabilities = other.mKernelCapabilities;
}

bool nn::hac::AccessControlInfo::operator==(const AccessControlInfo & other) const
{
	return (mProgramId == other.mProgramId) \
		&& (mFileSystemAccessControl == other.mFileSystemAccessControl) \
		&& (mServiceAccessControl == other.mServiceAccessControl) \
		&& (mKernelCapabilities == other.mKernelCapabilities);
}

bool nn::hac::AccessControlInfo::operator!=(const AccessControlInfo & other) const
{
	return !(*this == other);
}

void nn::hac::AccessControlInfo::toBytes()
{
	// serialise the sections
	mFileSystemAccessControl.toBytes();
	mServiceAccessControl.toBytes();
	mKernelCapabilities.toBytes();

	// determine section layout
	struct sLayout {
		uint32_t offset, size;
	} fac, sac, kc;

	fac.offset = (uint32_t)align<size_t>(sizeof(sAciHeader), aci::kSectionAlignSize);
	fac.size = (uint32_t)mFileSystemAccessControl.getBytes().size();
	sac.offset = (uint32_t)align<size_t>(fac.offset + fac.size, aci::kSectionAlignSize);
	sac.size = (uint32_t)mServiceAccessControl.getBytes().size();
	kc.offset = (uint32_t)align<size_t>(sac.offset + sac.size, aci::kSectionAlignSize);
	kc.size = (uint32_t)mKernelCapabilities.getBytes().size();

	// get total size
	size_t total_size = (size_t)std::max<uint32_t>(std::max<uint32_t>(fac.offset + fac.size, sac.offset + sac.size), kc.offset + kc.size); 

	mRawBinary = tc::ByteData(total_size);
	sAciHeader* hdr = (sAciHeader*)mRawBinary.data();

	// set type
	hdr->st_magic.wrap(aci::kAciStructMagic);

	// set program id
	hdr->program_id.wrap(mProgramId);

	// set offset/size
	hdr->fac.offset.wrap(fac.offset);
	hdr->fac.size.wrap(fac.size);
	hdr->sac.offset.wrap(sac.offset);
	hdr->sac.size.wrap(sac.size);
	hdr->kc.offset.wrap(kc.offset);
	hdr->kc.size.wrap(kc.size);

	// write data
	memcpy(mRawBinary.data() + fac.offset, mFileSystemAccessControl.getBytes().data(), fac.size);
	memcpy(mRawBinary.data() + sac.offset, mServiceAccessControl.getBytes().data(), sac.size);
	memcpy(mRawBinary.data() + kc.offset, mKernelCapabilities.getBytes().data(), kc.size);
}

void nn::hac::AccessControlInfo::fromBytes(const byte_t* data, size_t len)
{
	// check size
	if (len < sizeof(sAciHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AccessControlInfo binary is too small");
	}
	
	// clear variables
	clear();

	// save a copy of the header
	sAciHeader hdr;
	memcpy((void*)&hdr, data, sizeof(sAciHeader));

	// check magic
	if (hdr.st_magic.unwrap() != aci::kAciStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AccessControlInfo header corrupt");
	}
	
	// get total size
	size_t total_size = std::max<uint32_t>(std::max<uint32_t>(hdr.fac.offset.unwrap() + hdr.fac.size.unwrap(), hdr.sac.offset.unwrap() + hdr.sac.size.unwrap()), hdr.kc.offset.unwrap() + hdr.kc.size.unwrap()); 

	// validate binary size
	if (len < total_size)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AccessControlInfo binary is too small");
	}

	// allocate memory for header
	mRawBinary = tc::ByteData(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// save variables
	mProgramId = hdr.program_id.unwrap();
	mFileSystemAccessControl.fromBytes(mRawBinary.data() + hdr.fac.offset.unwrap(), hdr.fac.size.unwrap());
	mServiceAccessControl.fromBytes(mRawBinary.data() + hdr.sac.offset.unwrap(), hdr.sac.size.unwrap());
	mKernelCapabilities.fromBytes(mRawBinary.data() + hdr.kc.offset.unwrap(), hdr.kc.size.unwrap());
}

const tc::ByteData& nn::hac::AccessControlInfo::getBytes() const
{
	return mRawBinary;
}

void nn::hac::AccessControlInfo::clear()
{
	mRawBinary =tc::ByteData();
	mProgramId = 0;
	mFileSystemAccessControl.clear();
	mServiceAccessControl.clear();
	mKernelCapabilities.clear();
}

uint64_t nn::hac::AccessControlInfo::getProgramId() const
{
	return mProgramId;
}

void nn::hac::AccessControlInfo::setProgramId(uint64_t program_id)
{
	mProgramId = program_id;
}

const nn::hac::FileSystemAccessControl& nn::hac::AccessControlInfo::getFileSystemAccessControl() const
{
	return mFileSystemAccessControl;
}

void nn::hac::AccessControlInfo::setFileSystemAccessControl(const nn::hac::FileSystemAccessControl& fac)
{
	mFileSystemAccessControl = fac;
}

const nn::hac::ServiceAccessControl& nn::hac::AccessControlInfo::getServiceAccessControl() const
{
	return mServiceAccessControl;
}

void nn::hac::AccessControlInfo::setServiceAccessControl(const nn::hac::ServiceAccessControl& sac)
{
	mServiceAccessControl = sac;
}

const nn::hac::KernelCapabilityControl& nn::hac::AccessControlInfo::getKernelCapabilities() const
{
	return mKernelCapabilities;
}

void nn::hac::AccessControlInfo::setKernelCapabilities(const nn::hac::KernelCapabilityControl& kc)
{
	mKernelCapabilities = kc;
}