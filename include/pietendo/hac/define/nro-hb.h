	/**
	 * @file nro-hb.h
	 * @brief Declaration of Homebrew NRO0 structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <pietendo/hac/define/nro.h>

namespace pie { namespace hac {

namespace nro
{
	static const uint64_t kNroHomebrewStructMagic = tc::bn::make_struct_magic_uint64("HOMEBREW");
}

}} // namespace pie::hac