#ifndef _ImportantAlgorithms_h_
#define _ImportantAlgorithms_h_

#include <string>
#include <unordered_set>
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
int MinHeapFind(struct MinHeap* pHeap, int node); // find the index containing the node value
void MinHeapChangeNodeWeight(struct MinHeap* pHeap, int index, int newWeight);

// --------------- sorting

void BubbleSort(int* array, int length);
void Shuffle(int* arrayToShuffle, int len);
void InsertionSort(int* array, int len);
void HeapSort(int* array, int len);

// --------------- string functions

void ReverseStringRecursive(char* pString);
void RemoveCharFromString(char* pString, char toRemove);
unsigned int BinaryNumberToUnsignedInt(const char* pBinaryNum);
std::string SumBinaryNumbers(const std::string& binaryNumOne, const std::string& binaryNumTwo);
std::string SubtractBinaryNumbers(const std::string& binaryNumOne, const std::string& binaryNumTwo); // <<== implement this http://www.wikihow.com/Subtract-Binary-Numbers
void RemoveCommonElementsFromStrings(char* pStringOne, char* pStringTwo);

// --------------- tree functions

BinaryTreeNode* BinaryTreeBreadthFirstSearch(BinaryTreeNode* pRoot, int val);
BinaryTreeNode* BinarySearchTreeFindIterative(BinaryTreeNode* pRoot, int val); // tree where left node is less than parent, right node is higher
BinaryTreeNode* BinarySearchTreeFindRecurse(BinaryTreeNode* pRoot, int val); // tree where left node is less than parent, right node is higher
bool BinarySearchTreeAddNoDuplicatesIterative(BinaryTreeNode** pRoot, int val); // tree where left node is less than parent, right node is higher
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
const GraphNode* GraphDepthFirstSearchIterative(const GraphNode& graph, int val);

namespace AStarSearch
{
struct AStarPath;
struct Grid;
struct GridCell;
// use this when there are traversal costs between nodes (when there are no traversal costs a bidirectional breadth first search can be used)
bool AStar(AStarPath& outPath, const Grid& grid, const GridCell& start, const GridCell& end);
}

// use this when you have a start and end, but no traversal costs between nodes
std::vector<const GraphNode*> GraphBidirectionalBreadthFirstSearch(const GraphNode& from, const GraphNode& to);

// ----------------- general

bool IsPrime(int number);
// index:			   0, 1, 2, 3, 4, 5, 6, 7,	8,	9	10
// Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13,	21,	34,	55
int FibonacciIterative(int FibonacciNumberAtIndex);
int FibonacciRecursive(int FibonacciNumberAtIndex);
void RemoveDuplicatesFromSortedArray(int* array, int& arrayLength); // {5,6,6,7} becomes {5,6,7}
void RemoveDuplicatesFromArrayPreserveFirst(int* array, int& arrayLength);
void RemoveDuplicatesFromArrayPreserveLast(int* array, int& arrayLength);
void RemoveDuplicatesFromArrayPreserveNth(int array[], int& len, int N);

template <class T> void RemoveCommonElementsFromArrays(T* pArrayOne, int& arrayOneLen, T* pArrayTwo, int& arrayTwoLen);
bool GetNthSmallestElementFromUnionOfSortedNoDuplicatesArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo);
bool GetNthSmallestElementFromUnionOfSortedArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo); // could be duplicates
void RemoveCommonElementsFromSortedArrays(int* arrOne, int& lenOne, int* arrTwo, int& lenTwo);
void RemoveCommonIntegers(int* intNumbers, const char** stringNumbers, int& numIntNumbers, int& numStringNumbers); // arrays not sorted
namespace boggle
{
	/* Boggle Rules
	Players have three minutes(shown by the countdown timer) to find as many words as they can in the grid, according to the following rules :
		-The letters must be adjoining in a 'chain'. (Letter cubes in the chain may be adjacent horizontally, vertically, or diagonally.)
		- Words must contain at least three letters.
		- No letter cube may be used more than once within a single word.
		- all letter cube sides contain a single character accept for 'Qu' 
	*/
	void Boggle(const std::unordered_set<std::string>& dictionary, const char* dice, int dimension, std::unordered_set<std::string>& found);
}
namespace findLargestEncompassingRectangle
{
	// for explanation: http://stackoverflow.com/questions/7770945/largest-rectangular-sub-matrix-with-the-same-number?lq=1
	int FindLargestEncompassingRectangleOfZeros(char* array, int rows, int cols);
}

std::string IntToBinaryString(int val);
std::string UnsignedIntToBinaryString(unsigned int val);
int BinaryStringToUnsignedInt(const char* string);
std::string UnsignedIntToHexString(unsigned int num);
unsigned int HexStringToUnsignedInt(const char* hexString);

#endif