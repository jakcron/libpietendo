#include <pietendo/hac/BKTRSubsectionEncryptedStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <pietendo/hac/define/aesctrexstorage.h>
/*
#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>
*/

// inline utils
inline uint64_t castInt64ToUint64(int64_t val) { return val < 0 ? 0 : uint64_t(val); }
inline int64_t castUint64ToInt64(uint64_t val) { return (int64_t)std::min<uint64_t>(val, uint64_t(std::numeric_limits<int64_t>::max())); }

inline uint64_t offsetToBlockIndex(int64_t offset) { return castInt64ToUint64(offset / tc::io::IOUtil::castSizeToInt64(tc::crypto::Aes128CtrEncryptor::kBlockSize)); };
inline int64_t blockIndexToOffset(uint64_t block_index) { return castUint64ToInt64(block_index) * tc::io::IOUtil::castSizeToInt64(tc::crypto::Aes128CtrEncryptor::kBlockSize); };

inline size_t lengthToBlockNum(int64_t length) { return tc::io::IOUtil::castInt64ToSize(length / tc::io::IOUtil::castSizeToInt64(tc::crypto::Aes128CtrEncryptor::kBlockSize)); };
inline size_t offsetInBlock(int64_t offset) { return tc::io::IOUtil::castInt64ToSize(offset % tc::io::IOUtil::castSizeToInt64(tc::crypto::Aes128CtrEncryptor::kBlockSize)); };

const std::string pie::hac::BKTRSubsectionEncryptedStream::kClassName = "pie::hac::BKTRSubsectionEncryptedStream";


void setGenerationAesCtr(uint32_t generation, byte_t* aes_ctr)
{
	tc::bn::be32<uint32_t>* aes_ctr_words = (tc::bn::be32<uint32_t>*)aes_ctr;
	aes_ctr_words[1].wrap(generation);
}

pie::hac::BKTRSubsectionEncryptedStream::BKTRSubsectionEncryptedStream() :
	mLength(0),
	mCurrentPos(0)
{
}

pie::hac::BKTRSubsectionEncryptedStream::BKTRSubsectionEncryptedStream(const std::shared_ptr<tc::io::IStream>& stream, const key_t& key, const counter_t& counter, const pie::hac::sContentArchiveFsHeaderPatchInfo& patch_info) :
	BKTRSubsectionEncryptedStream()
{
	// validate stream properties
	if (stream == nullptr)
	{
		throw tc::ObjectDisposedException(kClassName, "stream is null.");
	}
	if (stream->canRead() == false)
	{
		throw tc::NotSupportedException(kClassName, "stream does not support reading.");
	}
	if (stream->canSeek() == false)
	{
		throw tc::NotSupportedException(kClassName, "stream does not support seeking.");
	}

	tc::crypto::Aes128CtrEncryptedStream sections_reader(stream, key, counter);

	// validate and read subsection header
	if (sections_reader.length() < patch_info.aes_ctr_ex_bucket.offset.unwrap() + patch_info.aes_ctr_ex_bucket.size.unwrap())
	{
		throw tc::ArgumentOutOfRangeException(kClassName, "Input stream is too small.");
	}
	tc::ByteData tmp_data = tc::ByteData(patch_info.aes_ctr_ex_bucket.size.unwrap());
	sections_reader.seek(patch_info.aes_ctr_ex_bucket.offset.unwrap(), tc::io::SeekOrigin::Begin);
	sections_reader.read(tmp_data.data(), tmp_data.size());
	const pie::hac::sAesCtrExStorageBlock* subsectionBlock = (const pie::hac::sAesCtrExStorageBlock*)tmp_data.data();

	mLength = stream->length();
	auto new_counter = counter;

	// Relation generation -> decrypted IStream
	std::map<uint32_t, std::shared_ptr<tc::io::IStream>> generationMap;

	for (size_t i = 0; i < subsectionBlock->header.bucket_count; ++i) {
		const sAesCtrExStorageBucket& subsection = subsectionBlock->buckets[i];
		for (size_t j = 0; j < subsection.header.entry_count; ++j) {
			const sAesCtrExStorageEntry& entry = subsection.entries[j];
			uint32_t newGeneration = entry.generation;
			int64_t subsec_offset = entry.offset;
			int64_t end_offset = (j + 1 == subsection.header.entry_count) ? subsection.header.end_offset_bucket : subsection.entries[j + 1].offset;
			setGenerationAesCtr(newGeneration, new_counter.data());
			std::shared_ptr<tc::io::IStream>& reader = generationMap[entry.generation];
			if (reader == nullptr) {
				reader = std::make_shared<tc::crypto::Aes128CtrEncryptedStream>(tc::crypto::Aes128CtrEncryptedStream(stream, key, new_counter));
			}

			Subsection& current_subsection = mSubsections[subsec_offset];
			current_subsection.mReader = reader;
			current_subsection.offset = subsec_offset;
			current_subsection.end_offset = end_offset;
		}
	}
}

bool pie::hac::BKTRSubsectionEncryptedStream::canRead() const
{
	for (auto stream : mStreams) {
		if (!stream->canRead())
			return false;
	}
	return true;
}

bool pie::hac::BKTRSubsectionEncryptedStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool pie::hac::BKTRSubsectionEncryptedStream::canSeek() const
{
	for (auto stream : mStreams) {
		if (!stream->canSeek())
			return false;
	}
	return true;
}

int64_t pie::hac::BKTRSubsectionEncryptedStream::length()
{
	return mLength;
}

int64_t pie::hac::BKTRSubsectionEncryptedStream::position()
{
	return mCurrentPos;
}

size_t pie::hac::BKTRSubsectionEncryptedStream::read(byte_t* ptr, size_t count)
{
	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// get current position
	int64_t current_pos = mCurrentPos;
	if (current_pos < 0)
	{
		throw tc::InvalidOperationException(kClassName+"::read()", "Current stream position is negative.");
	}

	// get subsection info for current position
	// upper_bound returns first key is greater than key, it means next entry (so need to get previous entry)
	// map must to contain an entry for offset 0, but never retrieve by upper bound (because the key returned must be greater)
	// and in case ask for a offset greater (or equal) to last entry its return "end", so its safe to get previous entry
	const Subsection& section = (--mSubsections.upper_bound(current_pos))->second;

	std::shared_ptr<IStream> reader = section.mReader;

	// determine begin & end offsets
	int64_t begin_read_offset    = current_pos;
	int64_t end_read_offset      = begin_read_offset + tc::io::IOUtil::castSizeToInt64(count);
	int64_t count_partial_read   = count;
	int64_t end_offset_section = section.end_offset;

	if (end_read_offset > end_offset_section) {
		count_partial_read = end_offset_section - begin_read_offset;
	}

	reader->seek(begin_read_offset, tc::io::SeekOrigin::Begin);
	data_read_count += reader->read(ptr, count_partial_read);

	// reads from diferent subsections
	if (count_partial_read != count) {
		seek(count_partial_read, tc::io::SeekOrigin::Current);
		// read remeaning data (recursively)
		data_read_count += read(ptr + count_partial_read, count - count_partial_read);
	}

	// restore expected logical position
	seek(begin_read_offset + tc::io::IOUtil::castSizeToInt64(data_read_count), tc::io::SeekOrigin::Begin);

	// return data read count
	return data_read_count;
}

size_t pie::hac::BKTRSubsectionEncryptedStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException(kClassName+"::write()", "write is not implemented for BKTRSubsectionEncryptedStream");
}

int64_t pie::hac::BKTRSubsectionEncryptedStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	return mCurrentPos = tc::io::StreamUtil::getSeekResult(offset, origin, mCurrentPos, mLength);
}

void pie::hac::BKTRSubsectionEncryptedStream::setLength(int64_t length)
{
	throw tc::NotImplementedException(kClassName+"::setLength()", "setLength is not implemented for BKTRSubsectionEncryptedStream");
}

void pie::hac::BKTRSubsectionEncryptedStream::flush()
{
	for (auto stream : mStreams) {
		stream->flush();
	}
}

void pie::hac::BKTRSubsectionEncryptedStream::dispose()
{
	for (auto stream : mStreams)
	{
		// dispose base stream
		stream->dispose();

		// release ptr
		stream.reset();
	}
	mSubsections.clear();
}