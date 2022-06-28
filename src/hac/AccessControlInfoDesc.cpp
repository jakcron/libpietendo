#include <pietendo/hac/AccessControlInfoDesc.h>

pie::hac::AccessControlInfoDesc::AccessControlInfoDesc()
{
	clear();
}

pie::hac::AccessControlInfoDesc::AccessControlInfoDesc(const AccessControlInfoDesc & other)
{
	*this = other;
}

void pie::hac::AccessControlInfoDesc::operator=(const AccessControlInfoDesc & other)
{
	mRawBinary = other.mRawBinary;
	mContentArchiveHeaderSignature2Key = other.mContentArchiveHeaderSignature2Key;
	mProductionFlag = other.mProductionFlag;
	mUnqualifiedApprovalFlag = other.mUnqualifiedApprovalFlag;
	mMemoryRegion = other.mMemoryRegion;
	mProgramIdRestrict = other.mProgramIdRestrict;
	mFileSystemAccessControl = other.mFileSystemAccessControl;
	mServiceAccessControl = other.mServiceAccessControl;
	mKernelCapabilities = other.mKernelCapabilities;
}

bool pie::hac::AccessControlInfoDesc::operator==(const AccessControlInfoDesc & other) const
{
	return (mContentArchiveHeaderSignature2Key.n == other.mContentArchiveHeaderSignature2Key.n) \
		&& (mContentArchiveHeaderSignature2Key.e == other.mContentArchiveHeaderSignature2Key.e) \
		&& (mContentArchiveHeaderSignature2Key.d == other.mContentArchiveHeaderSignature2Key.d) \
		&& (mProductionFlag == other.mProductionFlag) \
		&& (mUnqualifiedApprovalFlag == other.mUnqualifiedApprovalFlag) \
		&& (mMemoryRegion == other.mMemoryRegion) \
		&& (mProgramIdRestrict == other.mProgramIdRestrict) \
		&& (mFileSystemAccessControl == other.mFileSystemAccessControl) \
		&& (mServiceAccessControl == other.mServiceAccessControl) \
		&& (mKernelCapabilities == other.mKernelCapabilities);
}

bool pie::hac::AccessControlInfoDesc::operator!=(const AccessControlInfoDesc & other) const
{
	return !(*this == other);
}

void pie::hac::AccessControlInfoDesc::toBytes()
{
	// serialise the sections
	mFileSystemAccessControl.toBytes();
	mServiceAccessControl.toBytes();
	mKernelCapabilities.toBytes();

	// determine section layout
	struct sLayout {
		uint32_t offset, size;
	} fac, sac, kc;

	fac.offset = (uint32_t)align<size_t>(sizeof(sAciDescHeader), aci::kSectionAlignSize);
	fac.size = (uint32_t)mFileSystemAccessControl.getBytes().size();
	sac.offset = (uint32_t)align<size_t>(fac.offset + fac.size, aci::kSectionAlignSize);
	sac.size = (uint32_t)mServiceAccessControl.getBytes().size();
	kc.offset = (uint32_t)align<size_t>(sac.offset + sac.size, aci::kSectionAlignSize);
	kc.size = (uint32_t)mKernelCapabilities.getBytes().size();

	// get total size
	size_t total_size = std::max<uint32_t>(std::max<uint32_t>(fac.offset + fac.size, sac.offset + sac.size), kc.offset + kc.size); 

	mRawBinary = tc::ByteData(total_size);
	sAciDescHeader* hdr = (sAciDescHeader*)mRawBinary.data();

	// set rsa modulus
	if (mContentArchiveHeaderSignature2Key.n.size() == hdr->nca_rsa_signature2_modulus.size())
	{
		memcpy(hdr->nca_rsa_signature2_modulus.data(), mContentArchiveHeaderSignature2Key.n.data(), hdr->nca_rsa_signature2_modulus.size());
	}
	else
	{
		// print warning when modulus isn't expected length?
		memset(hdr->nca_rsa_signature2_modulus.data(), 0x00, hdr->nca_rsa_signature2_modulus.size());
	}

	// set type
	hdr->st_magic.wrap(aci::kAciDescStructMagic);

	// set "acid size"
	hdr->signed_size.wrap((uint32_t)(total_size - sizeof(detail::rsa2048_signature_t)));

	// set flags
	sAciDescHeaderFlag flags;
	flags.production = mProductionFlag;
	flags.unqualified_approval = mUnqualifiedApprovalFlag;
	flags.memory_region = (byte_t)mMemoryRegion;
	hdr->flags.wrap(flags.raw);

	// set program id restrict settings
	hdr->program_id_min.wrap(mProgramIdRestrict.min);
	hdr->program_id_max.wrap(mProgramIdRestrict.max);

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

void pie::hac::AccessControlInfoDesc::fromBytes(const byte_t* data, size_t len)
{
	// check size
	if (len < sizeof(sAciDescHeader))
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AccessControlInfoDesc binary is too small");
	}
	
	// clear variables
	clear();

	// save a copy of the header
	sAciDescHeader hdr;
	memcpy((void*)&hdr, data, sizeof(sAciDescHeader));

	// check magic
	if (hdr.st_magic.unwrap() != aci::kAciDescStructMagic)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AccessControlInfoDesc header corrupt");
	}
	
	// get total size
	size_t total_size = std::max<uint32_t>(std::max<uint32_t>(hdr.fac.offset.unwrap() + hdr.fac.size.unwrap(), hdr.sac.offset.unwrap() + hdr.sac.size.unwrap()), hdr.kc.offset.unwrap() + hdr.kc.size.unwrap()); 

	// validate binary size
	if (len < total_size)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "AccessControlInfoDesc binary is too small");
	}

	// allocate memory for header
	mRawBinary = tc::ByteData(total_size);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	// save variables
	mContentArchiveHeaderSignature2Key = tc::crypto::RsaPublicKey(hdr.nca_rsa_signature2_modulus.data(), hdr.nca_rsa_signature2_modulus.size());

	// acid flags
	sAciDescHeaderFlag flags;
	flags.raw = hdr.flags.unwrap();
	mProductionFlag = flags.production;
	mUnqualifiedApprovalFlag = flags.unqualified_approval;
	mMemoryRegion = aci::MemoryRegion(flags.memory_region);

	// program id
	mProgramIdRestrict.min = hdr.program_id_min.unwrap();
	mProgramIdRestrict.max = hdr.program_id_max.unwrap();

	// fac,sac,kc
	mFileSystemAccessControl.fromBytes(mRawBinary.data() + hdr.fac.offset.unwrap(), hdr.fac.size.unwrap());
	mServiceAccessControl.fromBytes(mRawBinary.data() + hdr.sac.offset.unwrap(), hdr.sac.size.unwrap());
	mKernelCapabilities.fromBytes(mRawBinary.data() + hdr.kc.offset.unwrap(), hdr.kc.size.unwrap());
}

const tc::ByteData& pie::hac::AccessControlInfoDesc::getBytes() const
{
	return mRawBinary;
}

void pie::hac::AccessControlInfoDesc::generateSignature(const tc::crypto::RsaKey& key)
{
	if (mRawBinary.size() == 0)
		toBytes();

	detail::sha256_hash_t hash;
	tc::crypto::GenerateSha256Hash(hash.data(), mRawBinary.data() + sizeof(detail::rsa2048_signature_t), mRawBinary.size() - sizeof(detail::rsa2048_signature_t));

	if (tc::crypto::SignRsa2048PssSha256(mRawBinary.data(), hash.data(), key) == false)
	{
		throw tc::crypto::CryptoException(kModuleName, "Failed to sign Access Control Info Desc");
	}
}

void pie::hac::AccessControlInfoDesc::validateSignature(const tc::crypto::RsaKey& key) const
{
	if (mRawBinary.size() == 0)
		throw tc::ArgumentOutOfRangeException(kModuleName, "No Access Control Info Desc binary exists to verify");

	detail::sha256_hash_t hash;
	tc::crypto::GenerateSha256Hash(hash.data(), mRawBinary.data() + sizeof(detail::rsa2048_signature_t), mRawBinary.size() - sizeof(detail::rsa2048_signature_t));

	if (tc::crypto::VerifyRsa2048PssSha256(mRawBinary.data(), hash.data(), key) == false)
	{
		throw tc::crypto::CryptoException(kModuleName, "Failed to verify Access Control Info Desc");
	}
}

void pie::hac::AccessControlInfoDesc::clear()
{
	mRawBinary = tc::ByteData();
	mContentArchiveHeaderSignature2Key = tc::crypto::RsaKey();
	mProductionFlag = false;
	mUnqualifiedApprovalFlag = false;
	mMemoryRegion = aci::MemoryRegion::Application;
	mProgramIdRestrict.min = 0;
	mProgramIdRestrict.max = 0;
	mFileSystemAccessControl.clear();
	mServiceAccessControl.clear();
	mKernelCapabilities.clear();
}

const tc::crypto::RsaKey& pie::hac::AccessControlInfoDesc::getContentArchiveHeaderSignature2Key() const
{
	return mContentArchiveHeaderSignature2Key;
}

void pie::hac::AccessControlInfoDesc::setContentArchiveHeaderSignature2Key(const tc::crypto::RsaKey& key)
{
	mContentArchiveHeaderSignature2Key = key;
}

bool pie::hac::AccessControlInfoDesc::getProductionFlag() const
{
	return mProductionFlag;
}

void pie::hac::AccessControlInfoDesc::setProductionFlag(bool flag)
{
	mProductionFlag = flag;
}

bool pie::hac::AccessControlInfoDesc::getUnqualifiedApprovalFlag() const
{
	return mUnqualifiedApprovalFlag;
}

void pie::hac::AccessControlInfoDesc::setUnqualifiedApprovalFlag(bool flag)
{
	mUnqualifiedApprovalFlag = flag;
}

pie::hac::aci::MemoryRegion pie::hac::AccessControlInfoDesc::getMemoryRegion() const
{
	return mMemoryRegion;
}

void pie::hac::AccessControlInfoDesc::setMemoryRegion(pie::hac::aci::MemoryRegion memory_region)
{
	mMemoryRegion = memory_region;
}

const pie::hac::AccessControlInfoDesc::sProgramIdRestrict&  pie::hac::AccessControlInfoDesc::getProgramIdRestrict() const
{
	return mProgramIdRestrict;
}

void pie::hac::AccessControlInfoDesc::setProgramIdRestrict(const sProgramIdRestrict& pid_restrict)
{
	mProgramIdRestrict = pid_restrict;
}

const pie::hac::FileSystemAccessControl& pie::hac::AccessControlInfoDesc::getFileSystemAccessControl() const
{
	return mFileSystemAccessControl;
}

void pie::hac::AccessControlInfoDesc::setFileSystemAccessControl(const pie::hac::FileSystemAccessControl& fac)
{
	mFileSystemAccessControl = fac;
}

const pie::hac::ServiceAccessControl& pie::hac::AccessControlInfoDesc::getServiceAccessControl() const
{
	return mServiceAccessControl;
}

void pie::hac::AccessControlInfoDesc::setServiceAccessControl(const pie::hac::ServiceAccessControl& sac)
{
	mServiceAccessControl = sac;
}

const pie::hac::KernelCapabilityControl& pie::hac::AccessControlInfoDesc::getKernelCapabilities() const
{
	return mKernelCapabilities;
}

void pie::hac::AccessControlInfoDesc::setKernelCapabilities(const pie::hac::KernelCapabilityControl& kc)
{
	mKernelCapabilities = kc;
}