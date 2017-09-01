#include "DavidByttowAlgorithms.h"
#include <vector>
#include <queue>
#include <functional>
#include <sstream>
#include <iostream>
#include <fstream>

namespace dijkstra
{

int ToIndex(int row, int col, int numCols)
{
	return row*numCols + col;
}

struct Node
{
	int cost = -1;
	Node* parent = nullptr;
	int nodeIndex = 0;

	enum State { unexplored = 0, open, closed };
	State state = State::unexplored;
	int openListIndex = -1; // would be valid whilst state == open, min heap would set it
};

struct MinHeap // stubbed out class
{
	bool IsEmpty() { return true; }
	Node* PopLowestCostNode() { return nullptr; }
	void Add(int /*priority*/, Node* /*node*/) {};
	bool Contains(Node* /*node*/) { return true; }
	void ChangePriority(int /*newPriority*/, Node* /*existingNode*/) {}
};

void DijkstraSearch(int* graph, int startNode, std::vector<int>& shortestDistanceToNodes, int numGraphNodes)
{
	Node* nodes = new Node[numGraphNodes];

	for (int index = 0; index < numGraphNodes; ++index)
	{
		nodes[index].nodeIndex = index;
	}

	nodes[startNode].cost = 0;
	nodes[startNode].state = Node::State::open;
	MinHeap openList;
	openList.Add(nodes[startNode].cost, &nodes[startNode]);
	
	while (!openList.IsEmpty())
	{
		Node* lowestCostOpenNode = openList.PopLowestCostNode();
		lowestCostOpenNode->state = Node::State::closed;

		for (int link = 0; link < numGraphNodes; ++link)
		{
			if (Node::State::closed != nodes[link].state &&
				graph[ToIndex(lowestCostOpenNode->nodeIndex, link, numGraphNodes)] >= 0)
			{
				int newCost = lowestCostOpenNode->cost + graph[ToIndex(lowestCostOpenNode->nodeIndex, link, numGraphNodes)];
				if (Node::State::unexplored == nodes[link].state || newCost < nodes[link].cost)
				{
					nodes[link].cost = newCost;
					nodes[link].parent = lowestCostOpenNode;

					if (Node::State::open == nodes[link].state)
					{
						openList.ChangePriority(nodes[link].cost, &nodes[link]); // bubble down as cost is now lower
					}
					else
					{
						nodes[link].state = Node::State::open;
						openList.Add(nodes[link].cost, &nodes[link]);
					}
				}
			}
		}
	}

	for (int index = 0; index < numGraphNodes; ++index)
	{
		shortestDistanceToNodes[index] = nodes[index].cost;
	}

	delete[] nodes;
}

void DijkstraSearch()
{
	const int numGraphNodes = 4;
	int graph[numGraphNodes*numGraphNodes] =  // -1 for no path
	{
		-1, 24, 3, 20,
		24, -1, -1, -1,
		3, -1, -1, 12,
		20, -1, 12, -1
	};
	const int startNode = 0;

	std::vector<int> shortestDistanceToNodes(numGraphNodes);
	DijkstraSearch(graph, startNode, shortestDistanceToNodes, numGraphNodes);

	std::cout << std::endl << "Dijkstra";
	for (unsigned int dist = 0; dist < shortestDistanceToNodes.size(); ++dist)
	{
		if (dist != startNode)
		{
			std::cout << shortestDistanceToNodes[dist] << " ";
		}
	}
}

} // end namespace dijkstra

namespace floydwarshall
{

struct PathNode
{
	int mVirtex;
	int mParentVirtex; // -1 means no parent (meaning untraversable for all nodes barring the start node)
	int mTime; // how long to get there, -1 is untraversable
	bool mIsOpen;
};

struct GraphData
{
	int numVirtices;
	PathNode* virtices;

	int GetMoveTime(int /*fromVirtex*/, int /*toVirtex*/) // would calculate using some type of adjacency table (would return -1 for untraversable)
	{
		return 0;
	}
};

// create the path from the next data
int FloydWarshallSearchCreatePath(int u, int v, int* next, const GraphData& graph, int* outputPath)
{
	int pathCount = 0;
	if (next[u*graph.numVirtices + v] != -1) // -1 meaning no path
	{
		outputPath[pathCount++] = u;
		while (u != v)
		{
			u = next[u*graph.numVirtices + v];
			outputPath[pathCount++] = u;
		}
	}
	return pathCount;
}

void FloydWarshallSearch(GraphData& graph)
{
	int* distances = new int[graph.numVirtices*graph.numVirtices];
	int* next = new int[graph.numVirtices*graph.numVirtices]; // used to construct the paths to the virtices

	// initialize all the distances between virtices (-1 is used to indicate there is no path between two virtices)
	for (int u = 0; u < graph.numVirtices; ++u)
	{
		for (int v = 0; v < graph.numVirtices; ++v)
		{
			int moveTime = -1;
			if (u != v)
			{
				moveTime = graph.GetMoveTime(u, v); // would calculate using some type of adjacency table, returning -1 for none traversable
			}
			distances[(u*graph.numVirtices) + v] = moveTime; // moveTime will be -1 if not traversable
			next[u*graph.numVirtices + v] = (distances[u*graph.numVirtices + v] >= 0) ? v : -1; // -1 for no path
		}
	}

	for (int k = 0; k < graph.numVirtices; ++k)
	{
		for (int i = 0; i < graph.numVirtices; ++i)
		{
			for (int j = 0; j < graph.numVirtices; ++j)
			{
				if (i != j && // not interested in traversing to ourselves
					distances[i*graph.numVirtices + k] >= 0 && distances[k*graph.numVirtices + j] >= 0) // if both intermediates are traversable
				{
					if (distances[i*graph.numVirtices + j] < 0 || // if current path is not traversable 
						distances[i*graph.numVirtices + j] > distances[i*graph.numVirtices + k] + distances[k*graph.numVirtices + j]) // shorter route
					{
						distances[i*graph.numVirtices + j] = distances[i*graph.numVirtices + k] + distances[k*graph.numVirtices + j];
						next[i*graph.numVirtices + j] = next[i*graph.numVirtices + k];
					}
				}
			}
		}
	}

	int* path = new int[graph.numVirtices];
	for (int endVirtex = 0; endVirtex < graph.numVirtices; ++endVirtex)
	{
		int pathLength = FloydWarshallSearchCreatePath(0, endVirtex, next, graph, path);
		if (pathLength > 0)
		{
			graph.virtices[endVirtex].mTime = distances[0 * graph.numVirtices + endVirtex];
			graph.virtices[endVirtex].mVirtex = endVirtex;
			graph.virtices[endVirtex].mParentVirtex = path[pathLength - 1];
		}
	}
	delete[] path;

	delete[] next;
	delete[] distances;
}

} // end namespace floydwarshall

// quick sort ----------------------------------------------------------------------------------------------

namespace quicksort
{
	template<class T> int Partition(T arr[], int left, int right) {
		int pivot = arr[(left + right) / 2]; // Pick a pivot point. Can be an element		

		while (left <= right) { // Until we've gone through the whole array
								// Find element on left that should be on right
			while (arr[left] < pivot) {
				left++;
			}

			// Find element on right that should be on left
			while (arr[right] > pivot) {
				right--;
			}

			// Swap elements, and move left and right indices
			if (left <= right) {
				std::swap(arr[left], arr[right]);
				left++;
				right--;
			}
		}
		return left;
	}

	template<class T> void QuickSort(T arr[], int left, int right) {
		int index = Partition(arr, left, right);
		if (left < index - 1) { // Sort left half
			QuickSort(arr, left, index - 1);
		}
		if (index < right) { // Sort right half
			QuickSort(arr, index, right);
		}
	}

	// this is just being used so quicksort can be placed in the implementation file
	void CompileQuickSort()
	{
		QuickSort<char>(nullptr, 0, 0); // it's used with a char array in CrackingTheCodingInterviewQuestions.cpp
		QuickSort<int>(nullptr, 0, 0); // it's used with an int array in Revision.cpp
	}
}

namespace mergesort
{
	template<class T> void Merge(T array[], T helper[], int low, int middle, int high)
	{
		for (int copyOver = low; copyOver <= high; ++copyOver)
		{
			helper[copyOver] = array[copyOver];
		}

		int helperLeft = low;
		int helperRight = middle + 1;
		int current = low;
		for (; helperLeft <= middle && helperRight <= high;)
		{
			if (helper[helperLeft] <= helper[helperRight])
			{
				array[current++] = helper[helperLeft++];
			}
			else
			{
				array[current++] = helper[helperRight++];
			}
		}

		int remaining = middle - helperLeft; // only need to copy remaining left side (right side will already be there)
		for (int i = 0; i <= remaining; ++i)
		{
			array[current + i] = helper[helperLeft + i];
		}
	}

	template<class T> void MergeSort(T array[], T helper[], int low, int high)
	{
		if (low < high)
		{
			int middle = (low + high) / 2;
			MergeSort(array, helper, low, middle);
			MergeSort(array, helper, middle + 1, high);
			Merge(array, helper, low, middle, high);
		}
	}

	template<class T> void MergeSort(T array[], int length)
	{
		T* helper = new T[length];
		MergeSort(array, helper, 0, length - 1);
		delete[] helper;
	}

	// this is just being used so mergesort can be placed in the implementation file
	void CompileMergeSort()
	{
		MergeSort<int>(nullptr, 0); // it's used with an int array in Revision.cpp
	}
}

// bucket sort
namespace bucketsort
{
	template<class T> void BucketSort(T inputArray[], int length, const T& minInput, const T& maxInput, int numBuckets)
	{
		// 1) Create n empty buckets
		std::vector<T>* allBuckets = new std::vector<T>[numBuckets];

		// 2) Put array elements in different buckets
		for (int i = 0; i < length; ++i)
		{
			// this will mean the last bucket always has the last element only (not great)
			int bucketIndex = (int)((float(inputArray[i] - minInput) / (maxInput - minInput)) * (numBuckets - 1));
			allBuckets[bucketIndex].push_back(inputArray[i]);
		}

		// 3) Sort individual buckets 
		// (NOTE: some implementations do step 4 now, then after that do a sort on the inputArray. This could work well using insertion 
		// sort on a nearly sorted array)
		for (int i = 0; i < numBuckets; i++)
		{
			std::sort(allBuckets[i].begin(), allBuckets[i].end()); // use insertion sort or any sort here
		}

		// 4) Concatenate all buckets into inputArray[]
		int index = 0;
		for (int bucketIndex = 0; bucketIndex < numBuckets; ++bucketIndex)
		{
			for (unsigned int j = 0; j < allBuckets[bucketIndex].size(); ++j)
			{
				inputArray[index++] = allBuckets[bucketIndex][j];
			}
		}
		delete[] allBuckets;
	}

	// this is just being used so bucketsort can be placed in the implementation file
	void CompileBucketSort()
	{
		BucketSort<int>(nullptr, 0, 0, 0, 0);
	}
}