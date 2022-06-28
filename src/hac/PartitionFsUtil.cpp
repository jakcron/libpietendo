#include <pietendo/hac/PartitionFsUtil.h>
#include <sstream>
#include <iomanip>

std::string pie::hac::PartitionFsUtil::getFsTypeAsString(pie::hac::PartitionFsHeader::FsType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::PartitionFsHeader::TYPE_PFS0):
		ss << "PFS0";
		break;
	case (pie::hac::PartitionFsHeader::TYPE_HFS0):
		ss << "HFS0";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}

std::string pie::hac::PartitionFsUtil::getFsTypeAsStringDescription(pie::hac::PartitionFsHeader::FsType val)
{
	std::stringstream ss;

	switch (val)
	{
	case (pie::hac::PartitionFsHeader::TYPE_PFS0):
		ss << "Partition FileSystem";
		break;
	case (pie::hac::PartitionFsHeader::TYPE_HFS0):
		ss << "Hashed Partition FileSystem";
		break;
	default:
		ss << "unk_0x" << std::hex << std::setw(2) << std::setfill('0') << (uint32_t)val;
		break;
	}

	return ss.str();
}