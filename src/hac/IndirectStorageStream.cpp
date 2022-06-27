#include <nn/hac/IndirectStorageStream.h>
#include <tc/io/IOUtil.h>
#include <tc/io/StreamUtil.h>

#include <fmt/core.h>
#include <tc/cli/FormatUtil.h>

nn::hac::IndirectStorageStream::IndirectStorageStream() :
	mModuleLabel("nn::hac::IndirectStorageStream"),
	mBaseStream({nullptr, nullptr}),
	mStreamLength(0),
	mStreamPositition(0),
	mBucketTree()
{
}

nn::hac::IndirectStorageStream::IndirectStorageStream(const std::shared_ptr<tc::io::IStream>& stream0, const std::shared_ptr<tc::io::IStream>& stream1, int64_t stream_length, const nn::hac::BucketTree& bucket_tree) :
	IndirectStorageStream()
{
	mBaseStream[0] = stream0;
	mBaseStream[1] = stream1;
	mStreamLength = stream_length;
	mStreamPositition = 0;
	mBucketTree = bucket_tree;

	// validate stream properties
	if (mBaseStream[0] == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "stream0 is null.");
	}
	if (mBaseStream[0]->canRead() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream0 does not support reading.");
	}
	if (mBaseStream[0]->canSeek() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream0 does not support seeking.");
	}
	if (mBaseStream[1] == nullptr)
	{
		throw tc::ObjectDisposedException(mModuleLabel, "stream1 is null.");
	}
	if (mBaseStream[1]->canRead() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream1 does not support reading.");
	}
	if (mBaseStream[1]->canSeek() == false)
	{
		throw tc::InvalidOperationException(mModuleLabel, "stream1 does not support seeking.");
	}

	if (mStreamLength > 0 && mBucketTree.find(0) == mBucketTree.end())
	{
		throw tc::InvalidOperationException(mModuleLabel, "bucket_tree cannot describe the begin of the stream.");
	}

	if (mStreamLength > 0 && mBucketTree.find(mStreamLength-1) == mBucketTree.end())
	{
		throw tc::InvalidOperationException(mModuleLabel, "bucket_tree cannot describe the end of the stream.");
	}
}

bool nn::hac::IndirectStorageStream::canRead() const
{
	// this stream once initialised must be support read
	return isStreamInit() ? true : false;
}

bool nn::hac::IndirectStorageStream::canWrite() const
{
	return false; // always false this is a read-only stream
}
bool nn::hac::IndirectStorageStream::canSeek() const
{
	// this stream once initialised must be support seek
	return isStreamInit() ? true : false;
}

int64_t nn::hac::IndirectStorageStream::length()
{
	return isStreamInit() ? 0 : mStreamLength;
}

int64_t nn::hac::IndirectStorageStream::position()
{
	return isStreamInit() ? 0 : mStreamPositition;
}

size_t nn::hac::IndirectStorageStream::read(byte_t* ptr, size_t count)
{
	if (isStreamInit() == false)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::read()", "Failed to read from stream (stream is disposed)");
	}

	// track read_count
	size_t data_read_count = 0;

	// get predicted read count
	count = tc::io::IOUtil::getReadableCount(this->length(), this->position(), count);
	
	// if count is 0 just return
	if (count == 0) return data_read_count;

	// begin reading data

	// update stream positiion
	this->seek(data_read_count, tc::io::SeekOrigin::Current);

	// return data read count
	return data_read_count;
}

size_t nn::hac::IndirectStorageStream::write(const byte_t* ptr, size_t count)
{
	throw tc::NotImplementedException(mModuleLabel+"::write()", "write is not supported for IndirectStorageStream");
}

int64_t nn::hac::IndirectStorageStream::seek(int64_t offset, tc::io::SeekOrigin origin)
{
	if (isStreamInit() == false)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::seek()", "Failed to set stream position (stream is disposed)");
	}

	mStreamPositition = tc::io::StreamUtil::getSeekResult(offset, origin, mStreamPositition, mStreamLength);

	return mStreamPositition;
}

void nn::hac::IndirectStorageStream::setLength(int64_t length)
{
	if (isStreamInit() == false)
	{
		throw tc::ObjectDisposedException(mModuleLabel+"::setLength()", "Failed to set stream length (stream is disposed)");
	}

	throw tc::NotSupportedException(mModuleLabel+"::setLength()", "setLength is not supported for IndirectStorageStream");
}

void nn::hac::IndirectStorageStream::flush()
{
	if (mBaseStream[0] != nullptr)
		mBaseStream[0]->flush();

	if (mBaseStream[1] != nullptr)
		mBaseStream[1]->flush();
}

void nn::hac::IndirectStorageStream::dispose()
{
	if (mBaseStream[0] != nullptr)
	{
		// dispose base stream
		mBaseStream[0]->dispose();

		// release ptr
		mBaseStream[0].reset();
	}
	if (mBaseStream[1] != nullptr)
	{
		// dispose base stream
		mBaseStream[1]->dispose();

		// release ptr
		mBaseStream[1].reset();
	}

	mStreamLength = 0;
	mStreamPositition = 0;
	mBucketTree = nn::hac::BucketTree();
}