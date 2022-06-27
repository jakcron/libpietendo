#pragma once
#include <nn/hac/define/gc.h>

namespace nn
{
namespace hac
{
	class GameCardUtil
	{
	public:
		static inline uint64_t blockToAddr(uint32_t block) { return ((uint64_t)block) << 9; }
		static void getXciHeaderAesIv(const nn::hac::sGcHeader* hdr, nn::hac::detail::aes_iv_t& iv);
		static void decryptXciHeader(nn::hac::sGcHeader* hdr, const byte_t* key);

		static std::string getKekIndexAsString(nn::hac::gc::KekIndex val);
		static std::string getRomSizeAsString(nn::hac::gc::RomSize val);
		static std::string getHeaderFlagsAsString(nn::hac::gc::HeaderFlags val);
		static std::string getCardFwVersionDescriptionAsString(nn::hac::gc::FwVersion val);
		static std::string getCardClockRateAsString(nn::hac::gc::CardClockRate val);
		static std::string getCompatibilityTypeAsString(nn::hac::gc::CompatibilityType val);
	};
}
}