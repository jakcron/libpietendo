#pragma once
#include <nn/hac/define/bktr.h>

#include <tc/ArgumentNullException.h>
#include <tc/ArgumentOutOfRangeException.h>
#include <tc/InvalidOperationException.h>

namespace nn { namespace hac {

class BucketTree
{
public:
	using sNodeHeader = sBucketTreeNodeHeader;
	static const size_t kNodeSizeMin = bktr::kNodeSizeMin;
	static const size_t kNodeSizeMax = bktr::kNodeSizeMax;

		/// Type of const_iterator for Path
	using const_iterator = typename std::vector<tc::ByteData>::const_iterator;

		/// Type of iterator for Path
	using iterator = typename std::vector<tc::ByteData>::iterator;


	BucketTree();

	void parse(const std::shared_ptr<tc::io::IStream>& table_stream, size_t node_size, size_t entry_size, size_t entry_count);

		/// Begin Iterator, points to front element
	iterator begin();

		/// Const Begin Iterator, points to front element
	const_iterator begin() const;

		/// End Iterator, points to after the last element
	iterator end();

		/// Const End Iterator, points to after the last element
	const_iterator end() const;

		/// Find Iterator, finds element that offset exists in
	iterator find(int64_t offset);

		/// Const Find Iterator, finds element that offset exists in
	const_iterator find(int64_t offset) const;

private:
	// this divides rounding up
	// where numerator = entry_num, and denominator = entry_capacity
	// this will be the number of containers (of entry_capacity) that are required to store entry_num entries
	static size_t divideUp(size_t numerator, size_t denonminator)
	{
		// avoid dividing by zero
		if (denonminator == 0)
		{
			return 0;
		}

		return (numerator / denonminator) + ((numerator % denonminator > 0) ? 1 : 0);
	}
	
	static bool isPowerOfTwo(size_t val)
	{
		return (val & (val - 1)) == 0;
	}

	static size_t getNodeEntryCapacity(size_t node_size, size_t entry_size)
	{
		if (node_size < sizeof(sNodeHeader))
		{
			return 0;
		}

		return (node_size - sizeof(sNodeHeader)) / entry_size;
	}

	static size_t getNodeOffsetCapacity(size_t node_size)
	{
		return getNodeEntryCapacity(node_size, sizeof(int64_t));
	}

	static size_t getL2NodeCount(size_t node_size, size_t entry_size, size_t entry_count)
	{
		const size_t offset_count_per_node = getNodeOffsetCapacity(node_size); // how many offsets can be stored in a node 
		const size_t entry_set_count       = getEntrySetCount(node_size, entry_size, entry_count);  // how many nodes are needed to store the entries

		// if there are less entry sets than offsets storable in a node, then there needs not be any L2 nodes
		if (entry_set_count <= offset_count_per_node)
		{ 
			return 0;
		}

		// determine l2 node count by determining how many nodes are required to refer to the entry sets (based on the node offset capacity)
		const size_t node_l2_count = divideUp(entry_set_count, offset_count_per_node);

		// node_l2_count cannot exceed offset_count_per_node, because the l2 nodes are indexed in the l1 node. And there are no l3 nodes
		if (node_l2_count > offset_count_per_node)
		{
			throw tc::InvalidOperationException("BucketTree::getL2NodeCount()", "Too many entries in BucketTree.");
		}

		// ???
		return divideUp(entry_set_count - (offset_count_per_node - (node_l2_count - 1)), offset_count_per_node);
	};

	static size_t getEntrySetCount(size_t node_size, size_t entry_size, size_t entry_count)
	{
		return divideUp(entry_count, getNodeEntryCapacity(node_size, entry_size));
	}

	static int64_t getNodeStorageSize(size_t node_size, size_t entry_size, size_t entry_count)
	{
		// (l1 node (1) + l2 nodes (0 or more)) * node_size
		return int64_t(1 + getL2NodeCount(node_size, entry_size, entry_count)) * int64_t(node_size);
	}

	static int64_t getEntrySetStorageSize(size_t node_size, size_t entry_size, size_t entry_count)
	{
		return int64_t(getEntrySetCount(node_size, entry_size, entry_count)) * int64_t(node_size);
	}


private:
	std::string mModuleName;

	size_t mNodeSize;
	size_t mEntrySize;
	size_t mEntryCount;

	tc::ByteData mNodeData;
	byte_t* getNodePtr(size_t node_index) const { return mNodeData.data() + (mNodeSize * node_index); }
	sNodeHeader* getNodeHeader(size_t node_index) const { return (sNodeHeader*)getNodePtr(node_index); }
	byte_t* getNodeEntry(size_t node_index, size_t entry_size, size_t entry_index) const { return (getNodePtr(node_index) + sizeof(sNodeHeader) + (entry_size * entry_index)); }
	int64_t getNodeEntryOffset(size_t node_index, size_t entry_size, size_t entry_index) const { return ((tc::bn::le64<int64_t>*)getNodeEntry(node_index, entry_size, entry_index))->unwrap(); }

	bool findEntryIndex(int64_t offset, size_t& found_entry_index) const;

	std::vector<tc::ByteData> mEntryList;
};

}} // namespace nn::hac