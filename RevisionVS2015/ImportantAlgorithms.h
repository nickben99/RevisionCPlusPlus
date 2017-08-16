#ifndef _ImportantAlgorithms_h_
#define _ImportantAlgorithms_h_

#include <string>
#include <set>
#include <vector>
#include "ProgrammingInterviewsBook.h"

// -------------- Linked List

struct LinkedListElement { LinkedListElement* next; void* data; };
bool LinkedListAddToEnd(LinkedListElement** head, void* data);
void LinkedListReverse(LinkedListElement** head);

struct DoubleLinkedListElement { DoubleLinkedListElement* next; DoubleLinkedListElement* prev; void* data; };
bool LinkedListAddToEnd(DoubleLinkedListElement** head, DoubleLinkedListElement** end, void* data);
bool LinkedListStackPush(DoubleLinkedListElement** head, DoubleLinkedListElement** end, void* data);
bool LinkedListStackPop(DoubleLinkedListElement** head, DoubleLinkedListElement** end, void*& outData);

// -------------- 2KSports interview --------------------------------------------------------

struct Element2KInterview
{
	Element2KInterview* mpPrev;
	Element2KInterview* mpNext;
	void* mpData;
};

template<class T, int N> struct LinkedListNoMemAlloc2KInterview
{
	LinkedListNoMemAlloc2KInterview()
		: mHead(nullptr)
		, mNextFree(mElements)
	{
		for (int i = 0; i < N; ++i)
		{
			mElements[i].mpPrev = (0 == i) ? nullptr : &(mElements[i - 1]);
			mElements[i].mpNext = (N - 1 == i) ? nullptr : mElements + i + 1; // using differnet method of getting pointer, just for illustration
		}
	}

	// add new element after 'addAfter', or at the front if 'addAfter' is NULL
	T* Add(void* pData, T* addAfter)
	{
		if (!mNextFree)
		{
			return nullptr; // no free spots
		}

		T* newElement = mNextFree;
		mNextFree = mNextFree->mpNext;
		newElement->mpNext = newElement->mpPrev = nullptr;

		if (!addAfter || !mHead) // add at front (if !mHead then addAfter should be null)
		{
			newElement->mpNext = mHead;
			mHead = newElement;
		}
		else
		{
			newElement->mpNext = addAfter->mpNext;
			addAfter->mpNext = newElement;
			newElement->mpPrev = addAfter;
		}

		if (newElement->mpNext)
		{
			newElement->mpNext->mpPrev = newElement;
		}

		newElement->mpData = pData;
		return newElement;
	}

	void Remove(void*& outData, T* remove)
	{
		if (!remove || !mHead)
		{
			return;
		}

		if (mHead == remove)
		{
			mHead = remove->mpNext;
		}

		if (remove->mpPrev)
		{
			remove->mpPrev->mpNext = remove->mpNext;
		}

		if (remove->mpNext)
		{
			remove->mpNext->mpPrev = remove->mpPrev;
		}
		
		remove->mpNext = mNextFree;

		// this section is commented out as mpPrev is not used for elements on the free list (but leaving it it would not cause bugs)
		//remove->mpPrev = nullptr;
		//if (mNextFree)
		//{
		//	mNextFree->mpPrev = remove;
		//}
		
		outData = remove->mpData;
		remove->mpData = nullptr;

		mNextFree = remove;
	}

	T* GetHead()
	{
		return mHead;
	}

	T mElements[N];
	T* mHead;
	T* mNextFree;
};

template<typename T, int N> struct LinkedListStackNoMemAlloc2KInterview : private LinkedListNoMemAlloc2KInterview<T, N>
{
	T* Push(void* pData)
	{
		return Add(pData, nullptr);
	}

	void Pop(void*& outData)
	{
		Remove(outData, GetHead());
	}
};

// divide numerator by denominator without using multiply/divide/quotiant
int DivideByWithoutMultDivQuot(int numerator, int denominator);

// --------------- min heap (same as max heap except has smallest at top rather than largest)

struct MinHeap
{ 
	int maxElements; // how much memory is allocated for elements
	int numElements; // of the memory allocated for elements, how many slots are we using right now  
	int* elements; 
};

bool MinHeapInit(struct MinHeap* pHeap, int maxElements);
void MinHeapDestroy(struct MinHeap* pHeap);
void MinHeapBubbleDown(struct MinHeap* pHeap, int index);
void MinHeapBubbleUp(struct MinHeap* pHeap, int index);
void MinHeapAddTo(struct MinHeap* pHeap, int node);
void MinHeapPop(struct MinHeap* pHeap, int& outNode);
int MinHeapFind(struct MinHeap* pHeap, int node);
void MinHeapChangeNodeWeight(struct MinHeap* pHeap, int index, int newWeight);

// --------------- sorting

void BubbleSort(int* array, int length);
void Shuffle(int* arrayToShuffle, int len);
void InsertionSort(int* arrayToShuffle, int len);

// --------------- string functions

void ReverseStringRecursive(char* pString);
void RemoveCharFromString(char* pString, char toRemove);
unsigned int BinaryNumberToUnsignedInt(const char* pBinaryNum);
std::string SumBinaryNumbers(const std::string& binaryNumOne, const std::string& binaryNumTwo);
std::string SubtractBinaryNumbers(const std::string& binaryNumOne, const std::string& binaryNumTwo); // <<== implement this http://www.wikihow.com/Subtract-Binary-Numbers
void RemoveCommonElementsFromStrings(char* pStringOne, char* pStringTwo);

// --------------- tree functions

BinaryTreeNode* BinaryTreeBreadthFirstSearch(BinaryTreeNode* pRoot, int val);
BinaryTreeNode* BinarySearchTreeFindNonRecurse(BinaryTreeNode* pRoot, int val); // tree where left node is less than parent, right node is higher
BinaryTreeNode* BinarySearchTreeFindRecurse(BinaryTreeNode* pRoot, int val); // tree where left node is less than parent, right node is higher
bool BinarySearchTreeAddNoDuplicatesNonRecurse(BinaryTreeNode** pRoot, int val); // tree where left node is less than parent, right node is higher
bool BinarySearchTreeAddNoDuplicatesRecurse(BinaryTreeNode** pRoot, int val); // tree where left node is less than parent, right node is higher
bool BinarySearchTreeRemove(BinaryTreeNode** pRoot, int val);
int BinaryTreeMaxDepth(BinaryTreeNode* pRoot);

// graphs ---------------------------------------------------

struct GraphNode
{
	int val;
	std::vector<GraphNode*> children;
};

const GraphNode* GraphDepthFirstSearch(const GraphNode& graph, int val);
const GraphNode* GraphBreadthFirstSearch(const GraphNode& graph, int val);

namespace AStarSearch
{
struct AStarPath;
struct Grid;
struct GridCell;
bool AStar(AStarPath& outPath, const Grid& grid, const GridCell& start, const GridCell& end);
}

// ----------------- general

bool IsPrime(int number);
// index:				0, 1, 2, 3, 4, 5, 6, 7,		8,		9		10
// Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13,	21,		34,		55
int FibonacciIterative(int FibonacciNumberAtIndex);
int FibonacciRecursive(int FibonacciNumberAtIndex);
void RemoveDuplicatesFromSortedArray(int* array, int& arrayLength);
void RemoveDuplicatesFromArrayPreserveFirst(int* array, int& arrayLength);
void RemoveDuplicatesFromArrayPreserveLast(int* array, int& arrayLength);
void RemoveDuplicatesFromArrayPreserveNth(int array[], int& len, int N);

// ==================================== upto here 4/17/2016

template <class T> void RemoveCommonElementsFromArrays(T* pArrayOne, int& arrayOneLen, T* pArrayTwo, int& arrayTwoLen);
bool GetNthElementFromUnionOfSortedNoDuplicatesArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo);
bool GetNthElementFromUnionOfSortedArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo); // could be duplicates
void RemoveCommonElementsFromSortedArrays(int* arrOne, int& lenOne, int* arrTwo, int& lenTwo);
void RemoveCommonIntegers(int* intNumbers, const char** stringNumbers, int& numIntNumbers, int& numStringNumbers);
namespace boggle
{
	void Boggle(const std::set<std::string>& dictionary, const char* dice, int dimension, std::set<std::string>& found);
}
namespace findLargestEncompassingRectangle
{
	// for explanation: http://stackoverflow.com/questions/7770945/largest-rectangular-sub-matrix-with-the-same-number?lq=1
	int FindLargestEncompassingRectangleOfZeros(char* array, int rows, int cols);
}
BinaryTreeNode* BinaryTreeInOrderSearchNoRecursion(BinaryTreeNode* root, int val); // <<== tricky to implement
BinaryTreeNode* BinaryTreePostOrderSearchNoRecursion(BinaryTreeNode* root, int val); // <<== tricky to implement
std::string IntToBinaryString(int val);
std::string UnsignedIntToBinaryString(unsigned int val);
int BinaryStringToUnsignedInt(const char* string);
std::string UnsignedIntToHexString(unsigned int num);
unsigned int HexStringToUnsignedInt(const char* hexString);

#endif