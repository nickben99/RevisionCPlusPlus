#include "ImportantAlgorithms.h"
#include "ProgrammingInterviewsBook.h" // for StringToInt()
#include <stdlib.h> // for malloc
#include <string.h>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>
#include <functional>

// -------------------------- linked list

bool LinkedListAddToEnd( LinkedListElement** head, void* data )
{
	if (!head)
	{
		return false;
	}

	LinkedListElement* pNewElement = new LinkedListElement();
	if (!pNewElement)
	{
		return false;
	}
	pNewElement->data = data;
	pNewElement->next = nullptr;

	LinkedListElement** pCurr = head;
	while (*pCurr)
	{
		pCurr = &(*pCurr)->next;
	}
	*pCurr = pNewElement;
	return true;
}

void LinkedListReverse(LinkedListElement** head)
{
	if (!head)
	{
		return;
	}

	LinkedListElement* prev = nullptr;
	while (*head)
	{
		LinkedListElement* next = (*head)->next;
		(*head)->next = prev;
		prev = *head;
		*head = next;
	}
	*head = prev;
}

bool LinkedListAddToEnd(DoubleLinkedListElement** head, DoubleLinkedListElement** end, void* data)
{
	DoubleLinkedListElement* newNode = new DoubleLinkedListElement();
	if (!newNode)
	{
		return false;
	}

	newNode->data = data;
	newNode->next = nullptr;
	if (nullptr == *head)
	{
		*head = *end = newNode;
	}
	else
	{
		(*end)->next = newNode;
		newNode->prev = *end;
		*end = newNode;
	}
	return true;
}

bool LinkedListStackPush(DoubleLinkedListElement** head, DoubleLinkedListElement** end, void* data)
{
	DoubleLinkedListElement* newNode = new DoubleLinkedListElement();
	if (!newNode)
	{
		return false;
	}
	newNode->data = data;
	newNode->next = newNode->prev = nullptr;
	
	if (!*head)
	{
		*head = *end = newNode;
	}
	else
	{
		newNode->next = *head;
		(*head)->prev = newNode;
		*head = newNode;
	}
	return true;
}

bool LinkedListStackPop(DoubleLinkedListElement** head, DoubleLinkedListElement** end, void*& outData)
{
	if (!head || !*head)
	{
		return false;
	}
	outData = (*head)->data;
	DoubleLinkedListElement* pTemp = (*head)->next;
	delete *head;
	*head = pTemp;
	if (nullptr == *head)
	{
		*end = nullptr;
	}
	else
	{
		(*head)->prev = nullptr;
	}
	return true;
}

// NOTE: this only supports positive ints. to make it support negative ints:
// 1. at the top record whether the signs were different, then make both numbers positive
// 2. at the bottom, if both numbers had different signs, negate the result
int DivideByWithoutMultDivQuot(int numerator, int denominator)
{	
	int counter = 0;

	if (denominator > 0)
	{
		while (numerator >= denominator)
		{
			numerator -= denominator;
			++counter;
		}
	}
	return counter;
}

// --------------------------- min heap

bool MinHeapInit(struct MinHeap* pHeap, int maxElements)
{
	if (pHeap)
	{
		MinHeapDestroy(pHeap);

		pHeap->numElements = 0;
		pHeap->maxElements = maxElements;
		pHeap->elements = nullptr;
		if (pHeap->maxElements > 0)
		{
			pHeap->elements = new int[maxElements];
			if (!pHeap->elements)
			{
				return false;
			}			
		}
		return true;
	}
	return false;
}

void MinHeapDestroy(struct MinHeap* pHeap)
{
	if (pHeap)
	{
		if (pHeap->elements)
		{
			delete[] pHeap->elements;
			pHeap->elements = nullptr;
		}
		pHeap->maxElements = pHeap->numElements = 0;		
	}
}

void MinHeapBubbleDown(struct MinHeap* pHeap, int index)
{
	if (pHeap && index >= 0 && index < pHeap->numElements)
	{
		int childIndexLeft = index*2+1;
		int childIndexRight = childIndexLeft + 1;

		while (childIndexLeft < pHeap->numElements)
		{
			int smallestChild = childIndexLeft;
			if (childIndexRight < pHeap->numElements && pHeap->elements[childIndexRight] < pHeap->elements[childIndexLeft])
			{
				smallestChild = childIndexRight;
			}

			if (pHeap->elements[smallestChild] < pHeap->elements[index])
			{
				int temp = pHeap->elements[index];
				pHeap->elements[index] = pHeap->elements[smallestChild];
				pHeap->elements[smallestChild] = temp;
			}
			else
			{
				break;
			}

			index = smallestChild;			
			childIndexLeft = index*2+1;
			childIndexRight = childIndexLeft + 1;
		}
	}
}

void MinHeapBubbleUp(struct MinHeap* pHeap, int index)
{
	if (pHeap && index < pHeap->numElements)
	{
		int parentIndex = (index-1)/2;

		while (index > 0 && pHeap->elements[index] < pHeap->elements[parentIndex])
		{
			int temp = pHeap->elements[index];
			pHeap->elements[index] = pHeap->elements[parentIndex];
			pHeap->elements[parentIndex] = temp;

			index = parentIndex;
			parentIndex = (index-1)/2;
		}
	}
}

void MinHeapAddTo(struct MinHeap* pHeap, int node)
{
	if (pHeap && pHeap->numElements < pHeap->maxElements)
	{
		pHeap->elements[pHeap->numElements++] = node;
		MinHeapBubbleUp(pHeap, pHeap->numElements-1);
	}
}

void MinHeapPop(struct MinHeap* pHeap, int& outNode)
{
	if (pHeap && pHeap->numElements > 0)
	{
		outNode = pHeap->elements[0];
		pHeap->elements[0] = pHeap->elements[--pHeap->numElements];
		MinHeapBubbleDown(pHeap, 0);
	}
}

int MinHeapFind(struct MinHeap* pHeap, int node)
{	
	for (int index = 0; index < pHeap->numElements; ++index)
	{
		if (pHeap->elements[index] == node)
		{
			return index;
		}
	}
	return -1;
}

void MinHeapChangeNodeWeight(struct MinHeap* pHeap, int index, int newWeight)
{
	if (pHeap && index >= 0 && index < pHeap->numElements && newWeight != pHeap->elements[index])
	{
		if (newWeight < pHeap->elements[index]) // bubble up
		{
			pHeap->elements[index] = newWeight;
			MinHeapBubbleUp(pHeap, index);
		}
		else // bubble down
		{
			pHeap->elements[index] = newWeight;
			MinHeapBubbleDown(pHeap, index);
		}
	}
}

// ------------------- sorting

void BubbleSort(int* array, int length)
{
	for (int iterateTo = length-1; iterateTo > 0; --iterateTo)
	{
		//bool swaps = false; // NOTE: this is an optimized bubble sort so that if the array is sorted, we can exit, meaning a best case big O(n)
		for (int index = 0; index < iterateTo; ++index)
		{
			if (array[index] > array[index + 1]) // this will end with low values at low indecis
			{
				//swaps = true;
				int temp = array[index];
				array[index] = array[index + 1];
				array[index + 1] = temp;
			}
		}

		//if (!swaps) {
		//	return;
		//}
	}
}

void Shuffle(int* arrayToShuffle, int len)
{
	if (arrayToShuffle)
	{
		for (int index = 0; index < len; ++index)
		{
			int randomSwapPos = rand() % len; // a while loop would make sure randomSwapPos != index to ensure a better shuffle
			int temp = arrayToShuffle[index]; // would use std::swap() in reality
			arrayToShuffle[index] = arrayToShuffle[randomSwapPos];
			arrayToShuffle[randomSwapPos] = temp;
		}
	}
}

void InsertionSort(int array[], int length)
{
	for (int i = 1; i < length; ++i)
	{
		int value = array[i];
		int j = i - 1;
		for (; j >= 0 && array[j] > value; --j)
		{
			array[j + 1] = array[j];
		}
		array[j + 1] = value;
	}
}

// ------------------ string functions

int StringLen(const char* pStr)
{
	if (nullptr == pStr)
	{
		return 0;
	}
	const char* pStart = pStr;
	for (; *pStr != '\0'; ++pStr) { }
	return (pStr - pStart);
}

void ReverseStringRecursiveInternal(char* pStringStart, char* pStringEnd)
{
	if (pStringStart < pStringEnd)
	{
		char temp = *pStringStart; // std::swap() used here in real c++ code
		*pStringStart = *pStringEnd;
		*pStringEnd = temp;
		ReverseStringRecursiveInternal(++pStringStart, --pStringEnd);
	}
}

void ReverseStringRecursive(char* pString)
{
	ReverseStringRecursiveInternal(pString, pString+(StringLen(pString)-1));
}

void RemoveCharFromString(char* pString, char toRemove)
{
	char* pTarget = pString;
	while(*pString != '\0')
	{
		*pTarget = *pString;
		if (*pString != toRemove)
		{
			++pTarget;
		}
		++pString;
	}
	*pTarget = *pString; // alternately *pTarget = '\0';
}

unsigned int BinaryNumberToUnsignedInt(const char* pBinaryNumString)
{
	unsigned int binaryNum = 0;
	if (pBinaryNumString)
	{
		for (; '\0' != *pBinaryNumString; ++pBinaryNumString)
		{
			binaryNum <<= 1;
			if ('1' == *pBinaryNumString)
			{
				++binaryNum;
			}
		}
	}
	return binaryNum;
}

std::string SumBinaryNumbers(const std::string& binaryNumOne, const std::string& binaryNumTwo)
{
	int lengthOneIterator = binaryNumOne.size() - 1;
	int lengthTwoIterator = binaryNumTwo.size() - 1;

	std::string result;
	int carry = 0;
	for (; lengthOneIterator >= 0 || lengthTwoIterator >= 0; --lengthOneIterator, --lengthTwoIterator)
	{
		int numOne = lengthOneIterator >= 0 ? (binaryNumOne[lengthOneIterator] - '0') : 0;
		int numTwo = lengthTwoIterator >= 0 ? (binaryNumTwo[lengthTwoIterator] - '0') : 0;
		int sum = numOne + numTwo + carry;
	
		result.insert(0, sum % 2 ? "1" : "0");
		carry = sum / 2;
	}

	if (carry)
	{
		result.insert(0, "1");
	}
	return result;
}

std::string SubtractBinaryNumbers(const std::string&, const std::string&)
{
	return std::string();
}

void RemoveCommonElementsFromStrings(char* pStringOne, char* pStringTwo)
{
	int common[CHAR_MAX + 1];
	memset(common, 0, sizeof(int)*(CHAR_MAX + 1));
	
	for (char* pStrOneCpy = pStringOne; *pStrOneCpy != '\0'; ++pStrOneCpy)
	{
		common[ *pStrOneCpy ] = 1;
	}

	// do remove chars from string algo here for string two...
	char* pTarget = pStringTwo;
	for (; *pStringTwo != '\0'; ++pStringTwo)
	{
		*pTarget = *pStringTwo;
		if (0 == common[*pTarget]) // wasn't in string one
		{
			++pTarget; // we'll keep it
		}
		else // must be equal to 1 (meaning in string one) or 2 (meaning it's in both)
		{
			common[*pTarget] = 2; // flag that it's in both strings (may already be 2, but not a problem)
		}		
	}
	*pTarget = '\0';

	// do remove chars from string algo here for string one...	
	for (pTarget = pStringOne; *pStringOne != '\0'; ++pStringOne)
	{
		*pTarget = *pStringOne;
		if ( 2 != common[ *pTarget ] ) // it's not in both, we want to keep it
		{
			++pTarget; // keep it
		}		
	}
	*pTarget = '\0';
}

// ---------------------- tree functions

BinaryTreeNode* BinaryTreeBreadthFirstSearch(BinaryTreeNode* pRoot, int val)
{
	if (!pRoot)
	{
		return nullptr;
	}
	std::queue<BinaryTreeNode*> nodes;
	nodes.push(pRoot);
	while(!nodes.empty())
	{
		pRoot = nodes.front();
		nodes.pop();
		
		if (pRoot->val == val)
		{
			return pRoot;
		}

		if (pRoot->left)
		{
			nodes.push(pRoot->left);
		}
		if (pRoot->right)
		{
			nodes.push(pRoot->right);
		}
	}
	return nullptr;
}

BinaryTreeNode* BinarySearchTreeFindNonRecurse(BinaryTreeNode* pRoot, int val)
{
	while (pRoot)
	{
		if (pRoot->val == val)
		{
			return pRoot;
		}
		else if (val > pRoot->val)
		{
			pRoot = pRoot->right;
		}
		else
		{
			pRoot = pRoot->left;
		}
	}
	return pRoot;
}

BinaryTreeNode* BinarySearchTreeFindRecurse(BinaryTreeNode* pRoot, int val)
{
	if (!pRoot)
	{
		return nullptr;
	}
	else if (pRoot->val == val)
	{
		return pRoot;
	}
	else if (val > pRoot->val)
	{
		return BinarySearchTreeFindRecurse(pRoot->right, val);
	}
	return BinarySearchTreeFindRecurse(pRoot->left, val);
}

bool BinarySearchTreeAddNoDuplicatesNonRecurse(BinaryTreeNode** pRoot, int val)
{
	if (!pRoot)
	{
		return false;
	}

	BinaryTreeNode** iter = pRoot;
	while (*iter)
	{
		if (val == (*iter)->val)
		{
			return false;
		}
		else if (val > (*iter)->val)
		{
			iter = &(*iter)->right;
		}
		else
		{
			iter = &(*iter)->left;
		}
	}
	*iter = new BinaryTreeNode();
	if (*iter)
	{
		(*iter)->val = val;
		(*iter)->left = (*iter)->right = nullptr;
		return true;
	}
	return false;
}

bool BinarySearchTreeAddNoDuplicatesRecurse(BinaryTreeNode** pRoot, int val)
{
	if (!pRoot)
	{
		return false;
	}

	if (!*pRoot) // the same as if (!(*pRoot))
	{
		*pRoot = new BinaryTreeNode();
		if (*pRoot)
		{
			(*pRoot)->val = val;
			(*pRoot)->left = (*pRoot)->right = nullptr;
			return true;
		}
		return false;
	}
	
	if (val == (*pRoot)->val)
	{
		return false;
	}
	else if (val > (*pRoot)->val)
	{
		return BinarySearchTreeAddNoDuplicatesRecurse(&(*pRoot)->right, val);
	}
	return BinarySearchTreeAddNoDuplicatesRecurse(&(*pRoot)->left, val);
}

bool BinarySearchTreeDeleteNode(BinaryTreeNode** pNode)
{
	if ((*pNode)->left && (*pNode)->right ) // two children
	{
		BinaryTreeNode** nextInSequence = &(*pNode)->right;
		while ( (*nextInSequence)->left )
		{
			nextInSequence = &(*nextInSequence)->left;
		}
		(*pNode)->val = (*nextInSequence)->val;
		return BinarySearchTreeDeleteNode(nextInSequence);
	}
	else // one or zero child
	{
		BinaryTreeNode* pChild = (*pNode)->left ? (*pNode)->left : (*pNode)->right;
		delete *pNode;
		*pNode = pChild;
	}
	return true;
}

bool BinarySearchTreeRemove(BinaryTreeNode** pRoot, int val)
{
	if (pRoot && *pRoot)
	{
		if ( (*pRoot)->val == val )
		{
			return BinarySearchTreeDeleteNode(pRoot);
		}
		else if ( (*pRoot)->val < val )
		{
			return BinarySearchTreeRemove( &(*pRoot)->right, val);
		}
		return BinarySearchTreeRemove( &(*pRoot)->left, val);
	}
	return false;
}

int BinaryTreeMaxDepth(BinaryTreeNode* pRoot) 
{
	if (!pRoot)
	{
		return 0; //base case
	}

	int left = BinaryTreeMaxDepth(pRoot->left);
	int right = BinaryTreeMaxDepth(pRoot->right);
	return (left > right ? left : right) + 1;
}

// graphs -------------------------------

const GraphNode* GraphDepthFirstSearch(const GraphNode& graph, int val, std::unordered_set<const GraphNode*> searched);
const GraphNode* GraphDepthFirstSearch(const GraphNode& graph, int val)
{
	std::unordered_set<const GraphNode*> searched;
	return GraphDepthFirstSearch(graph, val, searched);
}

// NOTE: alternate to using a unordered_set is flagging searched nodes (both methods are O(1))
const GraphNode* GraphDepthFirstSearch(const GraphNode& graphNode, int val, std::unordered_set<const GraphNode*> searched)
{
	if (graphNode.val == val)
	{
		return &graphNode;
	}
	searched.insert(&graphNode);
	for (auto childNode : graphNode.children)
	{
		if (childNode && searched.end() == searched.find(childNode)) // O(1) for unordered_set.find() (assuming no hashing collisions)
		{
			const GraphNode* found = GraphDepthFirstSearch(*childNode, val, searched);
			if (found)
			{
				return found;
			}
		}
	}
	return nullptr;
}

const GraphNode* GraphBreadthFirstSearch(const GraphNode& graph, int val)
{
	std::unordered_set<const GraphNode*> searched; // NOTE: alternate to a searched list is flaging each searched node (std::queue CANNOT be searched, but would be O(n) anyway)
	std::queue<const GraphNode*> nodes;	
	searched.insert(&graph);
	nodes.push(&graph);
	while (!nodes.empty())
	{
		const GraphNode* frontNode = nodes.front();
		nodes.pop();

		if (frontNode->val == val)
		{
			return frontNode;
		}

		for (auto childNode : frontNode->children)
		{
			if (childNode && searched.end() == searched.find(childNode)) // O(1) for set.find() (assuming no hashing collisions)
			{
				searched.insert(childNode);
				nodes.push(childNode);				
			}
		}
	}
	return nullptr;
}

namespace AStarSearch
{

struct GridCell {
	int x, y;
	bool operator==(const GridCell& rhs) const { return x == rhs.x && y == rhs.y; };
	bool operator!=(const GridCell& rhs) const { return !operator==(rhs); };

	std::vector<GridCell> adjacentTraversableGridCells; // grid cells next to this grid cell which can be traversed to
};
struct PathCell 
{
	bool operator<(const PathCell& rhs)
	{
		return heuristic + distance < rhs.heuristic + rhs.distance;
	}
	int parent; GridCell cell; int heuristic, distance; 
};
struct Grid { 
	int CalculateHeuristic(const GridCell& from, const GridCell& to) const { from; to; return 1; };
	int CalculateCost(const GridCell& from, const GridCell& to) const { from; to; return 0; };
};
struct AStarPath {
	void AddToFront(const GridCell& cell){cell;};
};

PathCell PopElementWithSmallestDistancePlusHeuristic(std::vector<PathCell>& aVect) 
{
	PathCell front = aVect[0];
	aVect.erase(aVect.begin());
	return front;
};
void AddToMinHeap(std::vector<PathCell>&, const PathCell&) {};
void MinHeapReSort(int /*index*/) {};
int GetItemIndex(const std::vector<PathCell>& aVector, const GridCell& cell) { aVector; cell; return 0; };

// NOTE: this example uses an closed list, see DavidByttowAlgorithms.h/cpp DijkstraSearch() for an example where nodes has an isOpen flag instead
bool AStar(AStarPath& outPath, const Grid& grid, const GridCell& start, const GridCell& end)
{
	std::vector<PathCell> openList; // would usually be a minheap
	std::vector<PathCell> closedList; // vector could be used but, should reserve it first to avoid mem frag
		
	PathCell startCell;
	startCell.cell = start;
	startCell.parent = -1; // no parent 
	startCell.distance = 0;
	startCell.heuristic = grid.CalculateHeuristic(start, end); // estimate of how far to end
	AddToMinHeap(openList, startCell);
	
	while( !openList.empty() )
	{
		PathCell parentCell = PopElementWithSmallestDistancePlusHeuristic(openList); // get smallest element and remove from list 
		closedList.push_back(parentCell); // add element to explored closedList 
		int closedListIndex = closedList.size() - 1;

		if ( end == parentCell.cell ) // end cell added to closed list
		{	
			PathCell cell = parentCell;
			while (cell.cell != start)
			{
				outPath.AddToFront(cell.cell);
				cell = closedList[cell.parent]; // closedlist structure has to guarentee index stays good
			}
			outPath.AddToFront(cell.cell);
			return true;
		}

		std::vector<GridCell>& adjacentCells = parentCell.cell.adjacentTraversableGridCells;

		int numAdjacentCells = adjacentCells.size();
		for (int adjacent = 0; adjacent < numAdjacentCells; ++adjacent)
		{
			if ( GetItemIndex(closedList, adjacentCells[ adjacent ]) >= 0 ) // NOTE: depending on set-up, may want to also check parentCell.cell != adjacentCells[adjacent]
			{
				continue; // grid cell has already been explored and put onto the closed list, don't re-explore
			}

			int openListIndex = GetItemIndex(openList, adjacentCells[ adjacent ]);
			if (openListIndex >= 0) // it's on the open list
			{
				int newDistToHere = parentCell.distance + grid.CalculateCost(parentCell.cell, adjacentCells[ adjacent ]);
				if (newDistToHere < openList[ openListIndex ].distance)
				{
					openList[ openListIndex ].parent = closedListIndex;
					openList[ openListIndex ].distance = newDistToHere;
					MinHeapReSort(openListIndex); // resort the index which has changed in the minheap
				}
			}
			else
			{
				PathCell newCell;
				newCell.cell = adjacentCells[ adjacent ];
				newCell.parent = closedListIndex;
				newCell.distance = parentCell.distance + grid.CalculateCost(parentCell.cell, newCell.cell);
				newCell.heuristic = grid.CalculateHeuristic(newCell.cell, end); // estimate of how far to end
				AddToMinHeap(openList, newCell);
			}
		}
	}	
	return false;
}

} // AStarSearch AStarSearch AStarSearch AStarSearch AStarSearch AStarSearch

// ----------------------- general

// first prime numbers: 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107
bool IsPrime(int number)
{
	if (number < 2)
	{
		return false; // 0, 1 not prime
	}
	if (number == 2)
	{
		return true; // 2 prime
	}
	if (number%2 == 0)
	{
		return false;
	}
	for (int i = 3; i*i <= number; i += 2) // iteration must start at 3, and can skip multiples of 2
	{
		if (number%i == 0)
		{
			return false;
		}
	}
	return true;
}

int FibonacciIterative(int FibonacciNumberAtIndex)
{
	if (FibonacciNumberAtIndex < 2)
	{
		return FibonacciNumberAtIndex;
	}

	int recent = 1;
	int older = 0;
	for (int count = 2; count <= FibonacciNumberAtIndex; ++count)
	{
		int newVal = recent + older;
		older = recent;
		recent = newVal;
	}
	return recent;
}

int FibonacciRecursiveInternal(int FibonacciNumberAtIndex, int count, int recent, int older)
{
	if (count <= FibonacciNumberAtIndex)
	{
		return FibonacciRecursiveInternal(FibonacciNumberAtIndex, count+1, recent+older, recent);
	}
	return recent;
}

int FibonacciRecursive(int FibonacciNumberAtIndex)
{
	// see http://stackoverflow.com/questions/1518726/recursive-fibonacci - don't use this alternate algo as it's very slow
	if (FibonacciNumberAtIndex < 2)
	{
		return FibonacciNumberAtIndex;
	}
	return FibonacciRecursiveInternal(FibonacciNumberAtIndex, 2, 1, 0);
}

void RemoveDuplicatesFromSortedArray(int* array, int& arrayLength)
{
	if (array && arrayLength > 1) // must be at least two elements for there to be any duplicates
	{
		int targetCount = 1;
		int sourceCount = 1;
		int toRemove = array[0];
		while (sourceCount < arrayLength)
		{
			array[targetCount] = array[sourceCount];
			if (array[targetCount] != toRemove)
			{
				toRemove = array[targetCount];
				++targetCount;
			}
			++sourceCount;
		}
		arrayLength = targetCount;
	}
}

void RemoveDuplicatesFromArrayPreserveFirst(int* array, int& arrayLength)
{
	std::unordered_set<int> dupes;
	int targetCount = 0;
	int sourceCount = 0;
	while (sourceCount < arrayLength)
	{
		array[targetCount] = array[sourceCount];
		std::unordered_set<int>::iterator iter = dupes.find(array[sourceCount]);
		if (dupes.end() == iter) // wasn't previously in there
		{
			dupes.insert(array[sourceCount]);
			++targetCount; // we want to keep this occurance
		}
		++sourceCount;
	}
	arrayLength = targetCount;
}

// NOTE: alternate to this method is reverse the string first, do the removal like RemoveDuplicatesFromArrayPreserveFirst(), then reverse again after
void RemoveDuplicatesFromArrayPreserveLast(int* array, int& len)
{
	std::unordered_map<int, int> lastIndecis;
	for (int sourceCount = 0; sourceCount < len; ++sourceCount)
	{
		lastIndecis[array[sourceCount]] = sourceCount;
	}

	int target = 0;
	for (int source = 0; source < len; ++source)
	{
		array[target] = array[source];
		if (lastIndecis[array[source]] == source)
		{
			++target;
		}
	}
	len = target;
}

void RemoveDuplicatesFromArrayPreserveNth(int array[], int& len, int N)
{
	std::unordered_map<int, int> dupes;
	for (int source = 0; source < len; ++source)
	{
		auto iter = dupes.find(array[source]);
		if (dupes.end() == iter)
		{
			iter = dupes.insert(std::make_pair(array[source], 0)).first;
		}
		++iter->second;		
	}

	std::unordered_map<int, int> counts;
	int target = 0;
	for (int source = 0; source < len; ++source)
	{
		array[target] = array[source];
		if (dupes[array[source]] > 1) // if this entry is a dupe
		{
			auto countsIter = counts.find(array[source]);
			if (counts.end() == countsIter)
			{
				countsIter = counts.insert(std::make_pair(array[source], -1)).first;
			}

			if (++countsIter->second == N)
			{
				++target;
			}
		}
		else // this entry is a one off
		{
			++target;
		}
	}
	len = target;
}

template <class T> void RemoveCommonElementsFromArrays(T* pArrayOne, int& arrayOneLen, T* pArrayTwo, int& arrayTwoLen)
{
	std::unordered_map<T, int> common;
	for (int i = 0; i < arrayOneLen; ++i)
	{
		common.insert( std::make_pair(pArrayOne[i], 1) );
	}

	int targetCount = 0;	
	for (int sourceCount = 0; sourceCount < arrayTwoLen; ++sourceCount)
	{
		pArrayTwo[targetCount] = pArrayTwo[sourceCount];
		std::unordered_map<T, int>::iterator iter = common.find( pArrayTwo[sourceCount] );
		if ( iter != common.end() ) // it was in array one
		{
			iter->second = 2; // indicate it was in both arrays
		}
		else // it wasn't in array one, so we want to keep it
		{
			++targetCount;
		}
	}
	arrayTwoLen = targetCount;

	// do remove from array algo here for array one...
	targetCount = 0;	
	for (int sourceCount = 0; sourceCount < arrayOneLen; ++sourceCount)
	{
		pArrayOne[targetCount] = pArrayOne[sourceCount];
		// it's not in both, we want to keep it (every array one element has an entry in common)
		if ( 2 != common[ pArrayOne[targetCount] ] ) 
		{
			++targetCount; // keep it
		}
	}
	arrayOneLen = targetCount;
}

// this function being here allows RemoveCommonElementsFromArrays() (above) to be defined in the implementation file
// this function does not need to be called
void MakeRemoveCommonElementsFromArraysLink()
{
	int num=0, numtwo=0;
	RemoveCommonElementsFromArrays<int>(0, num, 0, numtwo);
}

// will return nth smallest element if the input arrays are sorted
bool GetNthElementFromUnionOfSortedNoDuplicatesArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo)
{
	if (!arrOne)
	{
		lenOne = 0;
	}

	if (!arrTwo)
	{
		lenTwo = 0;
	}
	
	if (N >= (lenOne + lenTwo))
	{
		return false;
	}

	int oneIndex = 0, twoIndex = 0;
	for (;oneIndex+twoIndex <= N;)
	{
		if ( oneIndex < lenOne && twoIndex < lenTwo ) // both in bounds
		{
			if ( arrOne[oneIndex] < arrTwo[twoIndex] )
			{
				NthSmallestElement = arrOne[oneIndex++];
			}
			else
			{
				NthSmallestElement = arrTwo[twoIndex++];
			}
		}
		else if ( oneIndex < lenOne ) // one in bounds
		{
			NthSmallestElement = arrOne[oneIndex++];
		}
		else if ( twoIndex < lenTwo ) // two in bounds
		{
			NthSmallestElement = arrTwo[twoIndex++];
		}
	}
	return true;
}

bool GetNthElementFromUnionOfSortedArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo)
{
	if (!arrOne)
	{
		lenOne = 0;
	}

	if (!arrTwo)
	{
		lenTwo = 0;
	}

	if (N >= (lenOne + lenTwo))
	{
		return false;
	}

	int oneIndex = 0, twoIndex = 0;	
	int NthCounter = 0;
	for (; NthCounter <= N && (oneIndex < lenOne || twoIndex < lenTwo);)
	{
		int newValue = 0;
		if (oneIndex < lenOne && twoIndex < lenTwo) // both in bounds
		{
			if (arrOne[oneIndex] < arrTwo[twoIndex])
			{
				newValue = arrOne[oneIndex++];
			}
			else
			{
				newValue = arrTwo[twoIndex++];
			}
		}
		else if (oneIndex < lenOne) // one in bounds
		{
			newValue = arrOne[oneIndex++];
		}
		else if (twoIndex < lenTwo) // two in bounds
		{
			newValue = arrTwo[twoIndex++];
		}

		if (0 == NthCounter || newValue != NthSmallestElement)
		{
			NthSmallestElement = newValue;
			++NthCounter;
		}
	}
	return NthCounter - 1 == N;
}

void RemoveCommonElementsFromSortedArrays(int* arrOne, int& lenOne, int* arrTwo, int& lenTwo)
{
	int arrayOneSourceIndex = 0;
	int arrayTwoSourceIndex = 0;

	int arrayOneTargetIndex = 0;
	int arrayTwoTargetIndex = 0;
	while (arrayOneSourceIndex < lenOne || arrayTwoSourceIndex < lenTwo)
	{
		if (arrayOneSourceIndex < lenOne)
		{
			arrOne[arrayOneTargetIndex] = arrOne[arrayOneSourceIndex];
		}

		if (arrayTwoSourceIndex < lenTwo)
		{
			arrTwo[arrayTwoTargetIndex] = arrTwo[arrayTwoSourceIndex];
		}

		if (arrayOneSourceIndex < lenOne && arrayTwoSourceIndex < lenTwo) // both in range
		{
			if (arrOne[arrayOneTargetIndex] < arrTwo[arrayTwoTargetIndex])
			{
				++arrayOneSourceIndex;
				++arrayOneTargetIndex;
			}
			else if (arrOne[arrayOneTargetIndex] > arrTwo[arrayTwoTargetIndex])
			{
				++arrayTwoSourceIndex;
				++arrayTwoTargetIndex;
			}
			else // both the same, don't update target counters
			{
				// the if checking here is only required if we are allowing duplicate entries in the array
				if (arrayOneSourceIndex + 1 < lenOne && arrOne[arrayOneSourceIndex] == arrOne[arrayOneSourceIndex + 1]) // next entry in one will also need deleting
				{
					++arrayOneSourceIndex;
				}
				else if (arrayTwoSourceIndex + 1 < lenTwo && arrTwo[arrayTwoSourceIndex] == arrTwo[arrayTwoSourceIndex + 1]) // next entry in two will also need deleting
				{
					++arrayTwoSourceIndex;
				}
				else
				{
					++arrayOneSourceIndex;
					++arrayTwoSourceIndex;
				}
			}
		}
		else if (arrayOneSourceIndex < lenOne) // one in range
		{
			++arrayOneSourceIndex;
			++arrayOneTargetIndex;
		}
		else // two in range
		{
			++arrayTwoSourceIndex;
			++arrayTwoTargetIndex;
		}
	}
	lenOne = arrayOneTargetIndex;
	lenTwo = arrayTwoTargetIndex;
}

void RemoveCommonIntegers(int* intNumbers, const char** stringNumbers, int& numIntNumbers, int& numStringNumbers)
{
	std::unordered_map<int, int> used;
	for (int intArrayIndex = 0; intArrayIndex < numIntNumbers; ++intArrayIndex)
	{
		used.insert(std::make_pair(intNumbers[intArrayIndex], 0));
	}

	// IMPORTANT: go over string numbers second so that StringToInt() is only called once for each number
	std::unordered_map<int, int>::iterator endIter = used.end();
	int targetCounter = 0;
	for (int stringArrayIndex = 0; stringArrayIndex < numStringNumbers; ++stringArrayIndex)
	{
		stringNumbers[targetCounter] = stringNumbers[stringArrayIndex];
		std::unordered_map<int, int>::iterator iter = used.find(StringToInt(stringNumbers[stringArrayIndex])); // in reality std::stoi() would be used instead of StringToInt()
		if (endIter != iter)
		{
			iter->second = 1; // in both
		}
		else // we want to keep it
		{
			++targetCounter;
		}
	}
	numStringNumbers = targetCounter;
		
	// remove from the int array
	targetCounter = 0;
	for (int intArrayIndex = 0; intArrayIndex < numIntNumbers; ++intArrayIndex)
	{
		intNumbers[targetCounter] = intNumbers[intArrayIndex];
		if (0 == used[intNumbers[intArrayIndex]]) // used in only the first list
		{
			++targetCounter; // keep it
		}
	}
	numIntNumbers = targetCounter;
}

namespace boggle
{

void ToRowAndCol(int index, int columns, int& row, int& col)
{
	row = index / columns;
	col = index % columns;
}

int ToIndex(int row, int col, int columns)
{
	return row * columns + col;
}

bool IsInDictionary(const std::set<std::string>& dictionary, const char* word)
{
	return dictionary.end() != dictionary.find(std::string(word));
}

void FindWords(int dimension, const std::set<std::string>& dictionary, int parentDice, int currentSequencePosition,
				bool* usedDice, const char* dice, char* currentSequence, std::set<std::string>& found)
{
	usedDice[parentDice] = true;
	currentSequence[currentSequencePosition] = dice[parentDice];

	int nextPosition = currentSequencePosition + 1;
	if ('Q' == dice[parentDice])
	{
		currentSequence[nextPosition++] = 'U';
	}
	currentSequence[nextPosition] = '\0';

	if (nextPosition > 2 && IsInDictionary(dictionary, currentSequence)) // if we have a word in the dictionary which is at least 3 letters long
	{
		found.insert(currentSequence);
	}

	int row = 0;
	int col = 0;
	ToRowAndCol(parentDice, dimension, row, col);

	for (int rowAdd = -1; rowAdd < 2; ++rowAdd)
	{
		int childRow = row + rowAdd;
		if (childRow >= 0 && childRow < dimension)
		{
			for (int colAdd = -1; colAdd < 2; ++colAdd)
			{
				int childCol = col + colAdd;					
				if (!(0 == childRow && 0 == childCol) && childCol >= 0 && childCol < dimension)
				{
					int childIndex = ToIndex(childRow, childCol, dimension);
					if (!usedDice[childIndex])
					{
						FindWords(dimension, dictionary, childIndex, nextPosition, usedDice, dice, currentSequence, found);
					}
				}
			}
		}
	}
	currentSequence[currentSequencePosition] = '\0';
	usedDice[parentDice] = false;
}

void Boggle(const std::set<std::string>& dictionary, const char* dice, int dimension, std::set<std::string>& found)
{
	int diceLength = dimension*dimension;
	bool* usedDice = new bool[diceLength];
	memset(usedDice, 0, sizeof(bool) * diceLength);
	char* currentSequence = new char[diceLength * 2 + 1];
	memset(currentSequence, '\0', sizeof(char)*diceLength * 2 + 1);

	for (int index = 0; index < diceLength; ++index)
	{
		FindWords(dimension, dictionary, index, 0, usedDice, dice, currentSequence, found);
	}
	delete[] currentSequence;
	delete[] usedDice;
}

} // end namespace boggle

namespace findLargestEncompassingRectangle
{

int AddRectangleColumn(std::vector<std::pair<int, int>>& activeRectangles, int newHeight, int largestRectangleArea)
{
	bool equalHeightFound = false; // used to see if we need to add a new rectangle
	for (auto iter = activeRectangles.begin(); iter != activeRectangles.end();)
	{
		if (iter->first > newHeight) // this rectangle is larger than the height of the column added, so it's finished
		{
			iter->first = newHeight;
		}		

		if (iter->first == newHeight)
		{
			if (equalHeightFound) // if an earlier rectangle was found with equal height, we don't need this one
			{
				iter = activeRectangles.erase(iter); // this rectangle will have a smaller width than the earlier one added, so don't need this one
				continue;
			}
			equalHeightFound = true; // don't need to add a new rectangle, as we have updated this existing one
		}

		++iter->second; // rectangle width expands by one column
		if (iter->first*iter->second > largestRectangleArea)
		{
			largestRectangleArea = iter->first*iter->second;
		}	
		++iter; // goto next rectangle
	}

	if (!equalHeightFound)
	{
		activeRectangles.push_back(std::make_pair(newHeight, 1));
		if (newHeight > largestRectangleArea)
		{
			largestRectangleArea = newHeight;
		}
	}
	return largestRectangleArea;
}

int FindLargestEncompassingRectangleOfZeros(char* array, int numRows, int numColumns)
{
	int* freeColumnHeights = new int[numRows*numColumns];

	// go over columns recording height of 0's at each slot
	for (int col = 0; col < numColumns; ++col)
	{
		for (int row = 0; row < numRows; ++row)
		{
			int arrayIndex = boggle::ToIndex(row, col, numColumns);
			if (0 != array[arrayIndex]) // it's not a zero
			{
				freeColumnHeights[arrayIndex] = 0;
			}
			else if (row - 1 >= 0) // there are rows beneath
			{
				freeColumnHeights[arrayIndex] = freeColumnHeights[boggle::ToIndex(row - 1, col, numColumns)] + 1;
			}
			else // bottom row
			{
				freeColumnHeights[arrayIndex] = 1;
			}
		}
	}

	int largestEncompassingRectangleOfZeros = 0;
	// go over all the rows
	for (int row = numRows - 1; row >= 0; --row)
	{
		std::vector<std::pair<int, int>> activeRectangles;
		for (int col = 0; col < numColumns; ++col)
		{
			int freeColumnHeight = freeColumnHeights[boggle::ToIndex(row, col, numColumns)];
			if (0 == freeColumnHeight)
			{
				activeRectangles.clear();
			}
			else
			{
				largestEncompassingRectangleOfZeros = AddRectangleColumn(activeRectangles, freeColumnHeight, largestEncompassingRectangleOfZeros);
			}
		}
	}	

	delete[] freeColumnHeights;
	return largestEncompassingRectangleOfZeros;
}

} // findLargestEncompassingRectangle

BinaryTreeNode* BinaryTreeInOrderSearchNoRecursion(BinaryTreeNode* , int )
{
	return nullptr;
}

BinaryTreeNode* BinaryTreePostOrderSearchNoRecursion(BinaryTreeNode* , int )
{
	return nullptr;
}

std::string IntToBinaryString(int input)
{
	if (0 == input)
	{
		return "0";
	}
	int numBits = sizeof(int) * 8;

	std::string numString;

	bool hasNumberStarted = false;
	for (int bit = numBits - 1; bit >= 0; --bit)
	{
		unsigned int result = (1 << bit) & input;

		if (result || hasNumberStarted)
		{
			numString.push_back(result ? '1' : '0');
			hasNumberStarted = true;
		}
	}
	return numString;
}

std::string UnsignedIntToBinaryString(unsigned int val)
{
	std::string numString; // if you want to use a char array, then below loop must be done twice, first time just to get char array length
	do
	{
		int figure = val % 2;
		numString.insert(0, figure ? "1" : "0"); // NOTE: this is doing a push onto the front each time
		val /= 2;
	} while (0 != val);
	
	return numString;
}

int BinaryStringToUnsignedInt(const char* string)
{
	if (!string || '\0' == *string)
	{
		return 0;
	}

	int returnNumber = 0;
	while ('\0' != *string)
	{
		returnNumber *= 2;
		if (*string >= '0' && *string <= '1')
		{
			returnNumber += *string - '0';
		}
		else
		{
			return 0; // error
		}
		++string;
	}
	return returnNumber;
}

char IntToHexChar(int number)
{
	if (number < 10)
	{
		return (char)('0' + number);
	}
	else if (number < 16)
	{
		return (char)('a' + number - 10);
	}
	return '\0';
}

int HexCharToInt(char hexChar)
{
	if (hexChar >= '0' && hexChar <= '9')
	{
		return hexChar - '0';
	}
	else if (hexChar >= 'a' && hexChar <= 'f')
	{
		return hexChar - 'a' + 10;
	}
	return -1;
}

std::string UnsignedIntToHexString(unsigned int val)
{
	std::string numString; // if you want to use a char array, then below loop must be done twice, first time just to get char array length
	do
	{
		int figure = val % 16;
		char charArray[2] = { '\0', '\0' };
		charArray[0] = IntToHexChar(figure);
		numString.insert(0, charArray); // NOTE: this is doing a push onto the front each time
		val /= 16;
	} while (0 != val);

	return numString;
}

unsigned int HexStringToUnsignedInt(const char* hexString)
{
	if (!hexString || !*hexString)
	{
		return 0;
	}

	int returnNumber = 0;
	for (; *hexString; ++hexString)
	{
		returnNumber *= 16;
		int hexNumber = HexCharToInt(*hexString);
		if (hexNumber >= 0) // -1 indicates failure
		{
			returnNumber += hexNumber;
		}
		else
		{
			return 0; // error
		}
	}
	return returnNumber;
}