#include <pietendo/hac/IdConverter.h>

uint64_t pie::hac::IdConverter::convertToAocBaseId(uint64_t application_id)
{
	return application_id + kAocBaseId;
}

uint64_t pie::hac::IdConverter::convertToDeltaId(uint64_t application_id)
{
	return application_id + kDeltaId;
}

uint64_t pie::hac::IdConverter::convertToPatchId(uint64_t application_id)
{
	return application_id + kPatchId;
}