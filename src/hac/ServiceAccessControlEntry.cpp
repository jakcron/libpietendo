#include <cstring>
#include <nn/hac/ServiceAccessControlEntry.h>

nn::hac::ServiceAccessControlEntry::ServiceAccessControlEntry()
{
	clear();
}

nn::hac::ServiceAccessControlEntry::ServiceAccessControlEntry(const std::string & name, bool isServer) :
	mIsServer(isServer),
	mName(name)
{
	toBytes();
}

nn::hac::ServiceAccessControlEntry::ServiceAccessControlEntry(const ServiceAccessControlEntry & other)
{
	*this = other;
}

void nn::hac::ServiceAccessControlEntry::operator=(const ServiceAccessControlEntry & other)
{
	if (other.getBytes().size())
	{
		fromBytes(other.getBytes().data(), other.getBytes().size());
	}
	else
	{
		clear();
		this->mIsServer = other.mIsServer;
		this->mName = other.mName;
	}
}

bool nn::hac::ServiceAccessControlEntry::operator==(const ServiceAccessControlEntry & other) const
{
	return (mIsServer == other.mIsServer) \
		&& (mName == other.mName);
}

bool nn::hac::ServiceAccessControlEntry::operator!=(const ServiceAccessControlEntry & other) const
{
	return !(*this == other);
}


void nn::hac::ServiceAccessControlEntry::toBytes()
{
	try {
		mRawBinary = tc::ByteData(mName.size() + 1);
	}
	catch (const tc::OutOfMemoryException& e)
	{
		throw tc::OutOfMemoryException(kModuleName, "Failed to allocate memory for ServiceAccessControlEntry: " + std::string(e.what()));
	}

	if (mName.length() == 0)
	{
		throw tc::ArgumentException(kModuleName, "Service name is empty");
	}

	if (mName.length() > kMaxServiceNameLen)
	{
		throw tc::ArgumentException(kModuleName, "Service name string too long (max 8 chars)");
	}

	// copy data into binary blob
	mRawBinary[0] = (mIsServer ? SAC_IS_SERVER : 0) | ((mName.length()-1) & SAC_NAME_LEN_MASK); // bug?
	memcpy(mRawBinary.data() + 1, mName.c_str(), mName.length());
}

void nn::hac::ServiceAccessControlEntry::fromBytes(const byte_t* data, size_t len)
{
	bool isServer = (data[0] & SAC_IS_SERVER) == SAC_IS_SERVER;
	size_t nameLen = (data[0] & SAC_NAME_LEN_MASK) + 1; // bug?

	if (nameLen+1 > len)
	{
		throw tc::ArgumentException(kModuleName, "SAC entry is too small");
	}

	if (nameLen == 0)
	{
		throw tc::ArgumentException(kModuleName, "SAC entry has no service name");
	}
	else if (nameLen > kMaxServiceNameLen)
	{
		throw tc::ArgumentException(kModuleName, "Service name string too long (max 8 chars)");
	}

	mRawBinary = tc::ByteData(nameLen + 1);
	memcpy(mRawBinary.data(), data, mRawBinary.size());

	mIsServer = isServer;
	mName = std::string((const char*)(mRawBinary.data() + 1), nameLen);
}

const tc::ByteData& nn::hac::ServiceAccessControlEntry::getBytes() const
{
	return mRawBinary;
}

void nn::hac::ServiceAccessControlEntry::clear()
{
	mIsServer = false;
	mName.clear();
}

bool nn::hac::ServiceAccessControlEntry::isServer() const
{
	return mIsServer;
}

void nn::hac::ServiceAccessControlEntry::setIsServer(bool isServer)
{
	mIsServer = isServer;
}

const std::string & nn::hac::ServiceAccessControlEntry::getName() const
{
	return mName;
}

void nn::hac::ServiceAccessControlEntry::setName(const std::string & name)
{
	if (name.length() > kMaxServiceNameLen)
	{
		throw tc::ArgumentOutOfRangeException(kModuleName, "Service name string too long (max 8 chars)");
	}

	mName = name;
}