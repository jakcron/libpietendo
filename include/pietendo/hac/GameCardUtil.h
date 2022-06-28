	/**
	 * @file GameCardUtil.h
	 * @brief Declaration of pie::hac::GameCardUtil
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/gc.h>

namespace pie { namespace hac {
	
class GameCardUtil
{
public:
	static inline uint64_t blockToAddr(uint32_t block) { return ((uint64_t)block) << 9; }
	static void getXciHeaderAesIv(const pie::hac::sGcHeader* hdr, pie::hac::detail::aes_iv_t& iv);
	static void decryptXciHeader(pie::hac::sGcHeader* hdr, const byte_t* key);

	static std::string getKekIndexAsString(pie::hac::gc::KekIndex val);
	static std::string getRomSizeAsString(pie::hac::gc::RomSize val);
	static std::string getHeaderFlagsAsString(pie::hac::gc::HeaderFlags val);
	static std::string getCardFwVersionDescriptionAsString(pie::hac::gc::FwVersion val);
	static std::string getCardClockRateAsString(pie::hac::gc::CardClockRate val);
	static std::string getCompatibilityTypeAsString(pie::hac::gc::CompatibilityType val);
};

}} // namespace pie::hac