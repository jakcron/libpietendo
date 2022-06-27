	/**
	 * @file    SparseStorageStream.h
	 * @brief   Declaration of nn::hac::SparseStorageStream
	 * @author  Jack (jakcron)
	 * @version 0.1
	 * @date    2021/11/14
	 **/
#pragma once
#include <limits>
#include <nn/hac/IndirectStorageStream.h>

#include <tc/io/IStream.h>

#include <tc/ArgumentOutOfRangeException.h>
#include <tc/ObjectDisposedException.h>
#include <tc/NotImplementedException.h>
#include <tc/NotSupportedException.h>
#include <tc/io/IOException.h>

namespace nn { namespace hac {

	/**
	 * @class SparseStorageStream
	 * @brief Class for constructing read-only a logical stream from a Nintendo Switch SparseStorage
	 */
class SparseStorageStream : public nn::hac::IndirectStorageStream
{
public:
	SparseStorageStream();
	SparseStorageStream(const std::shared_ptr<tc::io::IStream>& compacted_stream, int64_t stream_length, const nn::hac::BucketTree& bucket_tree);

private:	
	class ZerosStream : public tc::io::IStream
	{
	public:
		ZerosStream() : mPosition(0) {}
		
		bool canRead() const { return true; }
		bool canWrite() const { return false; }
		bool canSeek() const { return true; }

		int64_t length() { return std::numeric_limits<int64_t>::max(); }
		int64_t position() { return mPosition; }

		size_t read(byte_t* ptr, size_t count);
		size_t write(const byte_t* ptr, size_t count);
		int64_t seek(int64_t offset, tc::io::SeekOrigin origin);
		void setLength(int64_t length) { return; }
		void flush() { return; }
		void dispose() { return; }
	private:
		int64_t mPosition;
	};
};

}} // namespace tc::crypto