#include <cstring>
#include <pietendo/hac/ServiceAccessControl.h>

pie::hac::ServiceAccessControl::ServiceAccessControl()
{
	clear();
}

pie::hac::ServiceAccessControl::ServiceAccessControl(const ServiceAccessControl & other)
{
	*this = other;
}

void pie::hac::ServiceAccessControl::operator=(const ServiceAccessControl & other)
{
	mRawBinary = other.mRawBinary;
	mServices = other.mServices;
}

bool pie::hac::ServiceAccessControl::operator==(const ServiceAccessControl & other) const
{
	return (mServices == other.mServices);
}

bool pie::hac::ServiceAccessControl::operator!=(const ServiceAccessControl & other) const
{
	return !(*this == other);
}

void pie::hac::ServiceAccessControl::toBytes()
{
	size_t totalSize = 0;
	for (size_t i = 0; i < mServices.size(); i++)
	{
		mServices[i].toBytes();
		totalSize += mServices[i].getBytes().size();
	}

	mRawBinary = tc::ByteData(totalSize);
	for (size_t i = 0, pos = 0; i < mServices.size(); pos += mServices[i].getBytes().size(), i++)
	{
		memcpy((mRawBinary.data() + pos), mServices[i].getBytes().data(), mServices[i].getBytes().size());
	}
}

void pie::hac::ServiceAccessControl::fromBytes(const byte_t* data, size_t len)
{
	clear();
	mRawBinary = tc::ByteData(len);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	ServiceAccessControlEntry sac;
	for (size_t pos = 0; pos < len; pos += mServices.back().getBytes().size())
	{
		sac.fromBytes((const byte_t*)(mRawBinary.data() + pos), len - pos);
		mServices.push_back(sac);
	}
}

const tc::ByteData& pie::hac::ServiceAccessControl::getBytes() const
{
	return mRawBinary;
}

void pie::hac::ServiceAccessControl::clear()
{
	mRawBinary = tc::ByteData();
	mServices.clear();
}

const std::vector<pie::hac::ServiceAccessControlEntry>& pie::hac::ServiceAccessControl::getServiceList() const
{
	return mServices;
}

void pie::hac::ServiceAccessControl::setServiceList(const std::vector<ServiceAccessControlEntry>& list)
{
	mServices = list;
}