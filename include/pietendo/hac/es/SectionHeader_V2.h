	/**
	 * @file SectionHeader_V2.h
	 * @brief Declaration of pie::hac::es::SectionHeader_V2
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

class SectionHeader_V2
{
public:
	SectionHeader_V2();
	SectionHeader_V2(const SectionHeader_V2& other);

	void operator=(const SectionHeader_V2& other);
	bool operator==(const SectionHeader_V2& other) const;
	bool operator!=(const SectionHeader_V2& other) const;

	// IByteModel
	void toBytes();
	void fromBytes(const byte_t* data, size_t len);
	const tc::ByteData& getBytes() const;

	// variables
	virtual void clear();

	uint32_t getSectionOffset() const;
	void setSectionOffset(uint32_t offset);

	uint32_t getRecordSize() const;
	void setRecordSize(uint32_t size);

	uint32_t getSectionSize() const;
	void getSectionSize(uint32_t size);

	uint16_t getRecordNum() const;
	void setRecordNum(uint16_t record_num);

	ticket::SectionType getSectionType() const;
	void setSectionType(ticket::SectionType type);

private:
	const std::string kModuleName = "SECTION_HEADER_V2";
	
	// raw binary
	tc::ByteData mRawBinary;

	// variables
	uint32_t mSectionOffset;
	uint32_t mRecordSize;
	uint32_t mSectionSize;
	uint16_t mRecordNum;
	ticket::SectionType mSectionType;
};

}}} // namespace pie::hac::es