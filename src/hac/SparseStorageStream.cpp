#include <memory>
#include <nn/hac/SparseStorageStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

nn::hac::SparseStorageStream::SparseStorageStream(const std::shared_ptr<tc::io::IStream>& compacted_stream, int64_t stream_length, const nn::hac::BucketTree& bucket_tree) :
	IndirectStorageStream(compacted_stream, std::make_shared<ZerosStream>(ZerosStream()), stream_length, bucket_tree)
{
}

size_t nn::hac::SparseStorageStream::ZerosStream::read(byte_t* ptr, size_t count)
{
	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// read zeros
	memset(ptr, 0x00, data_read_count);

	// update stream positiion
	this->seek(data_read_count, tc::io::SeekOrigin::Current);

	// return data read count
	return data_read_count;
}

size_t nn::hac::SparseStorageStream::ZerosStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException("ZerosStream::write()", "write is not supported for ZerosStream");
}

int64_t nn::hac::SparseStorageStream::ZerosStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	mPosition = tc::io::StreamUtil::getSeekResult(offset, origin, mPosition, this->length());

	return mPosition;
}