#include <pietendo/hac/NrrUtil.h>
#include <fmt/format.h>

std::string pie::hac::NrrUtil::getNrrKindAsString(pie::hac::nrr::NrrKind val)
{
	std::string str;

	switch (val)
	{
	case (pie::hac::nrr::NrrKind_User):
		str = "User";
		break;
	case (pie::hac::nrr::NrrKind_JitPlugin):
		str = "JitPlugin";
		break;
	default:
		str = fmt::format("unk_0x{:02x}", (uint32_t)val);
		break;
	}

	return str;
}