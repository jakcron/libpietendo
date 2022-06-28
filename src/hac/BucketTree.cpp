#include <pietendo/hac/BucketTree.h>

//#include <fmt/core.h>

pie::hac::BucketTree::BucketTree() :
	mModuleName("pie::hac::BucketTree"),
	mNodeSize(0),
	mEntrySize(0),
	mEntryCount(0),
	mNodeData(),
	mEntryList()
{}

void pie::hac::BucketTree::parse(const std::shared_ptr<tc::io::IStream>& table_stream, size_t node_size, size_t entry_size, size_t entry_count)
{
	if (table_stream == nullptr)
	{
		throw tc::ArgumentNullException(mModuleName, "table_stream was null.");
	}
	if (!table_stream->canRead() || !table_stream->canSeek())
	{
		throw tc::InvalidOperationException(mModuleName, "table_stream did not support reading and or seeking.");
	}
	if (entry_size < sizeof(int64_t))
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "entry_size cannot be smaller than 8 bytes.");
	}
	if (node_size < entry_size + sizeof(sNodeHeader))
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "node_size was too small to store entry data.");
	}
	if (kNodeSizeMin > node_size || node_size > kNodeSizeMax)
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "node_size was outside valid node size range.");
	}
	if (!isPowerOfTwo(node_size))
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "node_size was not a power of two.");
	}
	if (entry_count == 0)
	{
		throw tc::ArgumentOutOfRangeException(mModuleName, "entry_count was zero.");
	}

	// save BucketTree config
	mNodeSize = node_size;
	mEntrySize = entry_size;
	mEntryCount = entry_count;
	
	/*
	fmt::print("BucketTree overview:\n");
	fmt::print("node_size =              0x{:016x}\n", node_size);
	fmt::print("entry_size =             0x{:016x}\n", entry_size);
	fmt::print("entry_count =            0x{:016x}\n", entry_count);

	fmt::print("\n");
	fmt::print("getNodeEntryCapacity()=  0x{:016x}\n", getNodeEntryCapacity(node_size, entry_size));
	fmt::print("getNodeOffsetCapacity()= 0x{:016x}\n", getNodeOffsetCapacity(node_size));
	fmt::print("getL2NodeCount() =       0x{:016x}\n", getL2NodeCount(node_size, entry_size, entry_count));
	fmt::print("getEntrySetCount() =     0x{:016x}\n", getEntrySetCount(node_size, entry_size, entry_count));
	//fmt::print("divideUp(258,818) =      {:d}\n", divideUp(258, 818));
	

	fmt::print("\n");
	fmt::print("table_stream->length() = 0x{:016x}\n", table_stream->length());
	fmt::print("node_storage_size =      0x{:016x}\n", getNodeStorageSize(node_size, entry_size, entry_count));
	fmt::print("entry_set_storage_size = 0x{:016x}\n", getEntrySetStorageSize(node_size, entry_size, entry_count));
	*/

	int64_t stream_length = table_stream->length();

	int64_t expected_table_size = getNodeStorageSize(node_size, entry_size, entry_count) + getEntrySetStorageSize(node_size, entry_size, entry_count);

	if (stream_length < expected_table_size) 
	{
		throw tc::ArgumentException(mModuleName, "table_stream was too small.");
	}
	if (tc::is_int64_t_too_large_for_size_t(expected_table_size))
	{
		throw tc::InvalidOperationException(mModuleName, "table_size was too large to be read into memory.");
	}

	mNodeData = tc::ByteData(size_t(expected_table_size));
	
	// seek to begin
	table_stream->seek(0, tc::io::SeekOrigin::Begin);

	// read mNodeData
	if (table_stream->read(mNodeData.data(), mNodeData.size()) != mNodeData.size())
	{
		throw tc::io::IOException(mModuleName, "Failed to read raw bucket tree data.");
	}

	// process nodes
	size_t l1_node_count = 1;
	size_t l2_node_count = getL2NodeCount(node_size, entry_size, entry_count);
	size_t node_count = l1_node_count + l2_node_count;
	size_t entry_set_count = getEntrySetCount(node_size, entry_size, entry_count);

	if (l2_node_count != 0)
	{
		throw tc::InvalidOperationException(mModuleName, "BucketTree with L2 nodes are not supported yet.");
	}

	// index entries
	for (size_t i = 0; i < entry_set_count; i++)
	{
		sNodeHeader* hdr = getNodeHeader(node_count + i);

		/*
		fmt::print("EntrySet {:d}:\n", i);
		fmt::print(" index =  {:d}\n", hdr->index.unwrap());
		fmt::print(" count =  {:d}\n", hdr->count.unwrap());
		fmt::print(" offset = 0x{:016x}\n", hdr->offset.unwrap());
		fmt::print(" entries:\n");
		*/
		for (size_t j = 0; j < hdr->count.unwrap(); j++)
		{
			mEntryList.push_back(tc::ByteData(getNodeEntry(node_count + i, mEntrySize, j), mEntrySize));
			//fmt::print("  0x{:016x} (KEY)\n", getNodeEntryOffset(node_count + i, mEntrySize, j));
		}
	}
}

pie::hac::BucketTree::iterator pie::hac::BucketTree::begin()
{
	return mEntryList.begin();
}

pie::hac::BucketTree::const_iterator pie::hac::BucketTree::begin() const
{
	return mEntryList.begin();
}

pie::hac::BucketTree::iterator pie::hac::BucketTree::end()
{
	return mEntryList.end();
}

pie::hac::BucketTree::const_iterator pie::hac::BucketTree::end() const
{
	return mEntryList.end();
}

pie::hac::BucketTree::iterator pie::hac::BucketTree::find(int64_t offset)
{
	// TODO input checks

	size_t entry_index = 0;
	if (findEntryIndex(offset, entry_index))
	{
		return this->begin() + entry_index;
	}
	else
	{
		return this->end();
	}
}

pie::hac::BucketTree::const_iterator pie::hac::BucketTree::find(int64_t offset) const
{
	// TODO input checks

	size_t entry_index = 0;
	if (findEntryIndex(offset, entry_index))
	{
		return this->begin() + entry_index;
	}
	else
	{
		return this->end();
	}
}

bool pie::hac::BucketTree::findEntryIndex(int64_t offset, size_t& found_entry_index) const
{
	// TODO input checks

	size_t l1_node_count = 1;
	size_t l2_node_count = getL2NodeCount(mNodeSize, mEntrySize, mEntryCount);
	size_t node_count = l1_node_count + l2_node_count;
	size_t entry_set_capacity = getNodeEntryCapacity(mNodeSize, mEntrySize);

	
	// process nodes
	size_t node_index = 0; 
	sNodeHeader* node_hdr = getNodeHeader(node_index);

	// if the offset exceeds the valid range for this BucketTree return end()
	if (offset >= node_hdr->offset.unwrap())
	{
		return false;
	}

	// not implementing l2 node support yet
	if (l2_node_count != 0)
	{
		throw tc::InvalidOperationException(mModuleName, "BucketTree with L2 nodes are not supported yet.");
	}

	// Find entry set
	for (size_t entry_set_index = 0, entry_set_count = node_hdr->count.unwrap(); entry_set_index < entry_set_count; entry_set_index++)
	{
		sNodeHeader* entry_set_hdr = getNodeHeader(node_count + entry_set_index);

		int64_t entry_set_begin_offset = getNodeEntryOffset(node_index, sizeof(int64_t), entry_set_index);
		int64_t entry_set_end_offset = entry_set_hdr->offset.unwrap();
		
		// if this range is correct find entry in this entry set
		if (entry_set_begin_offset <= offset && offset < entry_set_end_offset)
		{
			for (size_t entry_index = 0, entry_count = entry_set_hdr->count.unwrap(); entry_index < entry_count; entry_index++)
			{
				int64_t entry_begin_offset = getNodeEntryOffset(node_count + entry_set_index, mEntrySize, entry_index);
				int64_t entry_end_offset = (entry_index + 1) < entry_count ? getNodeEntryOffset(node_count + entry_set_index, mEntrySize, entry_index+1) : entry_set_end_offset;
				
				// if this range is correct save the index
				if (entry_begin_offset <= offset && offset < entry_end_offset)
				{
					found_entry_index = (entry_set_capacity * entry_set_index) + entry_index;
					return true;
				}
			}
		}
	}

	return false;
}
