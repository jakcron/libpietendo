	/**
	 * @file TicketBody_V2.h
	 * @brief Declaration of pie::hac::es::TicketBody_V2
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2022/06/28
	 **/
#pragma once
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ArgumentNullException.h>
#include <tc/ByteData.h>
#include <pietendo/hac/es/ticket.h>

namespace pie { namespace hac { namespace es {

class TicketBody_V2
{
public:
	TicketBody_V2();
	TicketBody_V2(const TicketBody_V2& other);

	void operator=(const TicketBody_V2& other);
	bool operator==(const TicketBody_V2& other) const;
	bool operator!=(const TicketBody_V2& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* bytes, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	void clear();
	
	const std::string& getIssuer() const;
	void setIssuer(const std::string& issuer);

	const byte_t* getEncTitleKey() const;
	void setEncTitleKey(const byte_t* data, size_t len);

	ticket::TitleKeyEncType getTitleKeyEncType() const;
	void setTitleKeyEncType(ticket::TitleKeyEncType type);

	uint16_t getTicketVersion() const;
	void setTicketVersion(uint16_t version);

	ticket::LicenseType getLicenseType() const;
	void setLicenseType(ticket::LicenseType type);

	byte_t getCommonKeyId() const;
	void setCommonKeyId(byte_t id);

	const std::vector<es::ticket::PropertyMaskFlags>& getPropertyFlags() const;
	void setPropertyFlags(const std::vector<es::ticket::PropertyMaskFlags>& flags);

	const byte_t* getReservedRegion() const;
	void setReservedRegion(const byte_t* data, size_t len);

	uint64_t getTicketId() const;
	void setTicketId(uint64_t id);

	uint64_t getDeviceId() const;
	void setDeviceId(uint64_t id);

	const byte_t* getRightsId() const;
	void setRightsId(const byte_t* id);

	uint32_t getAccountId() const;
	void setAccountId(uint32_t id);

	uint32_t getSectionTotalSize() const;
	void setSectionTotalSize(uint32_t size);

	uint32_t getSectionHeaderOffset() const;
	void setSectionHeaderOffset(uint32_t offset);

	uint16_t getSectionNum() const;
	void setSectionNum(uint16_t num);

	uint16_t getSectionEntrySize() const;
	void setSectionEntrySize(uint16_t size);

private:
	const std::string kModuleName = "TICKET_BODY_V2";
	
	// raw binary
	tc::ByteData mRawBinary;

	// variables
	std::string mIssuer;
	std::array<byte_t, ticket::kEncTitleKeySize> mEncTitleKey;
	ticket::TitleKeyEncType mEncType;
	uint16_t mTicketVersion;
	ticket::LicenseType mLicenseType;
	byte_t mCommonKeyId;
	std::vector<es::ticket::PropertyMaskFlags> mPropertyFlags;
	std::array<byte_t, ticket::kReservedRegionSize> mReservedRegion; // explicitly reserved
	uint64_t mTicketId;
	uint64_t mDeviceId;
	std::array<byte_t, ticket::kRightsIdSize> mRightsId;
	uint32_t mAccountId;
	uint32_t mSectTotalSize;
	uint32_t mSectHeaderOffset;
	uint16_t mSectNum;
	uint16_t mSectEntrySize;
};

}}} // namespace pie::hac::es