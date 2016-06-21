#ifndef _DavidByttowAlgorithms_h_
#define _DavidByttowAlgorithms_h_

#include <bitset>
#include <unordered_map>

namespace dijkstra
{
	void DijkstraSearch(); // can be used to get the shortest route from the root node to all other nodes
}

namespace floydwarshall
{
	struct GraphData;
	void FloydWarshallSearch(GraphData& graph); // can be used to get the shortest route from every node to every other node
}

namespace bloom
{
// see: https://medium.com/the-story/what-are-bloom-filters-1ec2a50c68ff#.nesb4lvok
// see: http://billmill.org/bloomfilter-tutorial/
// simple bloom filter
template<class T, int N> class BloomFilter
{
public:
	void Add(const T& addMe)
	{
		// using 3 hash functions, but bloom filter could use less, depends on requirements of the implementation
		buckets[HashFunc1(addMe)] = true; // might already be true
		buckets[HashFunc2(addMe)] = true; // might already be true		
		buckets[HashFunc3(addMe)] = true; // might already be true
	}

	bool Exists(const T& doIExist)
	{
		// using 3 hash functions, but bloom filter could use less, depends on requirements of the implementation
		if (!buckets[HashFunc1(doIExist)] || !buckets[HashFunc2(doIExist)] || !buckets[HashFunc3(doIExist)])
		{
			return false; // at least one bucket slot is false, so 'doIExist' is definitely not in the bloom filter
		}
		return true; // all the buckets are true, so object MAY BE (but NOT definitely) is in the bloom filter (slots could have been filled by other objects)
	}

private:
	int HashFunc1(const T& /* hashMe */) { return 0 % N; } // implement a real hash function here	
	int HashFunc2(const T& /* hashMe */) { return 0 % N; } // implement a real hash function here
	int HashFunc3(const T& /* hashMe */) { return 0 % N; } // implement a real hash function here

private:
	std::bitset<N> buckets;
};

}

// quick sort https://www.youtube.com/watch?v=aQiWF4E8flQ
// http://stackoverflow.com/questions/22504837/how-to-implement-quick-sort-algorithm-in-c
namespace quicksort
{
	template<class T> void QuickSort(T array[], int start, int end);
}

namespace mergesort
{
	template<class T> void MergeSort(T array[], int length);
}

namespace bucketsort
{
	// bucket sort can be used to distrbute sorting of each bucket on different machines
	// bucket sort depends on the input related to whether it's efficient or not (input should be evenly spread accross range, so buckets all have approximately the same amount)
	// you need to know the min and max of your input
	template<class T> void BucketSort(T inputArray[], int length, const T& minInput, const T& maxInput, int numBuckets);
}

template<class Identifier, class Data, int NumBuckets> class Hashtable
{
public:
	Hashtable()
	{
		memset(buckets, 0, sizeof(LinkedListElement*)*NumBuckets);
	}

	~Hashtable()
	{
		for (int bucket = 0; bucket < NumBuckets; ++bucket)
		{
			LinkedListElement* iter = buckets[bucket];
			for (; iter;)
			{
				LinkedListElement* temp = iter->next;
				delete iter;
				iter = temp;
			}
		}
	}

	void Add(const Identifier& id, const Data& data)
	{
		LinkedListElement** iter = &buckets[HashFunction(id)];
		for (; *iter; iter = &(*iter)->next)
		{
			if (id == (*iter)->identifier) // does it already exist?
			{
				(*iter)->data = data; // update value
				return;
			}
		}
		*iter = new LinkedListElement(id, data);
	}

	void Remove(const Identifier& id)
	{
		int bucket = HashFunction(id);
		LinkedListElement* iter = buckets[bucket];
		LinkedListElement* prev = nullptr;
		for (; iter;)
		{
			LinkedListElement* temp = iter->next;
			if (id == iter->identifier)
			{
				if (!prev)
				{
					buckets[bucket] = temp;
				}
				else
				{
					prev->next = temp;
				}
				delete iter;
				return;
			}
			else
			{
				prev = iter;
			}
			iter = temp;
		}
	}

	Data* Find(const Identifier& id)
	{
		LinkedListElement* iter = buckets[HashFunction(id)];
		for (; iter; iter = iter->next)
		{
			if (id == iter->identifier)
			{
				return &iter->data;
			}
		}
		return nullptr;
	}

private:
	int HashFunction(const Identifier& id)
	{
		return id.ToHash() % NumBuckets;
	}

private:
	struct LinkedListElement
	{
		LinkedListElement(const Identifier& id, const Data& inputData)
			: next(nullptr)
			, identifier(id)
			, data(inputData)
			{}

		LinkedListElement* next;
		Identifier identifier;
		Data data;
	};

	LinkedListElement* buckets[NumBuckets];
};

#endif