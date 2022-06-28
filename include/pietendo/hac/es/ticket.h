	/**
	 * @file ticket.h
	 * @brief Declaration of ES Ticket structs and constants for the HAC library.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <bitset>
#include <tc/types.h>
#include <tc/crypto.h>

namespace pie { namespace hac { namespace es {

namespace ticket
{
	enum TitleKeyEncType
	{
		AES128_CBC,
		RSA2048
	};

	enum LicenseType
	{
		LICENSE_PERMANENT = 0,
		LICENSE_DEMO = 1,
		LICENSE_TRIAL = 2,
		LICENSE_RENTAL = 3,
		LICENSE_SUBSCRIPTION = 4,
		LICENSE_SERVICE = 5,
	};

	enum PropertyMaskFlags
	{
		FLAG_PRE_INSTALL,
		FLAG_SHARED_TITLE,
		FLAG_ALLOW_ALL_CONTENT,
		FLAG_DEVICE_LINK_INDEPENDENT,
		FLAG_VOLATILE,
		FLAG_ELICENSE_REQUIRED,
	};

	enum SectionType
	{
		SECTION_PERMANENT = 1,
		SECTION_SUBSCRIPTION = 2,
		SECTION_CONTENT = 3,
		SECTION_CONTENT_CONSUMPTION = 4,
		SECTION_ACCESS_TITLE = 5,
		SECTION_LIMITED_RESOURCE = 6,
	};

	static const size_t kIssuerSize = 0x40;
	static const byte_t kFormatVersion = 2;
	static const size_t kEncTitleKeySize = tc::crypto::Rsa2048OaepSha256Encryptor::kBlockSize;
	static const size_t kReservedRegionSize = 8;
	static const size_t kRightsIdSize = 16;
}

#pragma pack(push,1)
struct sTicketBody_v2
{
	tc::bn::string<ticket::kIssuerSize> issuer;
	std::array<byte_t, ticket::kEncTitleKeySize> enc_title_key;
	byte_t format_version;
	byte_t title_key_enc_type;
	tc::bn::le16<uint16_t> ticket_version;
	byte_t license_type;
	byte_t common_key_id;
	tc::bn::bitarray<sizeof(uint16_t)> property_mask;
	std::array<byte_t, ticket::kReservedRegionSize> reserved_region; // explicitly reserved
	tc::bn::le64<uint64_t> ticket_id;
	tc::bn::le64<uint64_t> device_id;
	std::array<byte_t, ticket::kRightsIdSize> rights_id;
	tc::bn::le32<uint32_t> account_id;
	tc::bn::le32<uint32_t> sect_total_size;
	tc::bn::le32<uint32_t> sect_header_offset;
	tc::bn::le16<uint16_t> sect_num;
	tc::bn::le16<uint16_t> sect_entry_size;
};

struct sSectionHeader_v2
{
	tc::bn::le32<uint32_t> section_offset;
	tc::bn::le32<uint32_t> record_size;
	tc::bn::le32<uint32_t> section_size;
	tc::bn::le16<uint16_t> record_num;
	tc::bn::le16<uint16_t> section_type;
};

struct sContentRecord_v1
{
private:
	static const size_t kAccessMaskSize = 0x80;
	static const uint16_t kGroupMask = 0xFC00;
	static const uint16_t kAccessMaskMask = 0x3FF;

	tc::bn::be32<uint32_t> group;
	tc::bn::bitarray<kAccessMaskSize> access_mask;
	//byte_t access_mask[kAccessMaskSize];
public:
	uint32_t index_group() const { return group.unwrap(); }
	bool is_index_enabled(uint16_t index) const { return access_mask.test(get_access_mask(index));}
	/*
	{
		return (index_group() == get_group(index)) \
			&& ((access_mask[get_access_mask(index) / 8] & BIT(get_access_mask(index) % 8)) != 0);
	}
	*/

	void clear() { memset(this, 0, sizeof(sContentRecord_v1)); }

	void set_index_group(uint16_t index) { group.wrap(get_group(index)); }
	void enable_index(uint16_t index) { access_mask.set(get_access_mask(index)); } //{ access_mask[get_access_mask(index) / 8] |= BIT(get_access_mask(index) % 8); }
	void disable_index(uint16_t index) { access_mask.reset(get_access_mask(index)); } //{ access_mask[get_access_mask(index) / 8] &= ~BIT(get_access_mask(index) % 8); }

	inline uint16_t get_access_mask(uint16_t index) const { return index & kAccessMaskMask; }
	inline uint16_t get_group(uint16_t index) const { return index & kGroupMask; }
};
#pragma pack(pop)

}}} // namespace pie::hac::es