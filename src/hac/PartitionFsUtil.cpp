#include <pietendo/hac/PartitionFsUtil.h>
#include <fmt/format.h>

std::string pie::hac::PartitionFsUtil::getFsTypeAsString(pie::hac::PartitionFsHeader::FsType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::PartitionFsHeader::TYPE_PFS0):
		str = "PFS0";
		break;
	case (pie::hac::PartitionFsHeader::TYPE_HFS0):
		str = "HFS0";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}

std::string pie::hac::PartitionFsUtil::getFsTypeAsStringDescription(pie::hac::PartitionFsHeader::FsType val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::PartitionFsHeader::TYPE_PFS0):
		str = "Partition FileSystem";
		break;
	case (pie::hac::PartitionFsHeader::TYPE_HFS0):
		str = "Hashed Partition FileSystem";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}