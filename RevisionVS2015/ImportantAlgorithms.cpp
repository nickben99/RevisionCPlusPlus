#include "ImportantAlgorithms.h"
#include "ProgrammingInterviewsBook.h" // for StringToInt()
#include "CrackingTheCodingInterviewQuestions.h" // for BinaryTreeNodeWithParent
#include <stdlib.h> // for malloc
#include <string.h>
#include <queue>
#include <stack>
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
	if (!head || !end)
	{
		return false;
	}

	DoubleLinkedListElement* newNode = new DoubleLinkedListElement();
	if (!newNode)
	{
		return false;
	}

	newNode->data = data;
	newNode->next = newNode->prev = nullptr;
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

int DivideByWithoutMultDivQuot(int numerator, int denominator)
{	
	// to make it support negative numbers
	bool numeratorPositive = (numerator > 0);
	if (!numeratorPositive) { numerator = -numerator; }
	bool denominatorPositive = (denominator > 0);
	if (!denominatorPositive) { denominator = -denominator; }

	int counter = 0;
	if (denominator > 0)
	{
		while (numerator >= denominator)
		{
			numerator -= denominator;
			++counter;
		}
	}
	return numeratorPositive == denominatorPositive ? counter : -counter; // to make it support negative numbers
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

bool MinHeapPop(struct MinHeap* pHeap, int& outNode)
{
	if (pHeap && pHeap->numElements > 0)
	{
		outNode = pHeap->elements[0];
		pHeap->elements[0] = pHeap->elements[--pHeap->numElements];
		MinHeapBubbleDown(pHeap, 0);
		return true;
	}
	return false;
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
		bool swaps = false; // NOTE: this is an optimized bubble sort so that if the array is sorted, we can exit, meaning a best case big O(n)
		for (int index = 0; index < iterateTo; ++index)
		{
			if (array[index] > array[index + 1]) // this will end with low values at low indecis
			{
				swaps = true; // NOTE: this is an optimized bubble sort so that if the array is sorted, we can exit, meaning a best case big O(n)
				int temp = array[index];
				array[index] = array[index + 1];
				array[index + 1] = temp;
			}
		}

		if (!swaps) { // NOTE: this is an optimized bubble sort so that if the array is sorted, we can exit, meaning a best case big O(n)
			return;
		}
	}
}

void Shuffle(int* arrayToShuffle, int len)
{
	if (arrayToShuffle)
	{
		for (int index = 0; index < len; ++index)
		{
			int randomSwapPos = rand() % len;
			// a while loop would make sure randomSwapPos != index to ensure a better shuffle
			// NOTE: checking for len > 2 as without this check, when len == 1, it would cause an infinite loop, and when
			// len == 2, the order would never change
			//while (len > 2 && index == randomSwapPos)
			//{
			//	randomSwapPos = rand() % len;
			//}
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

void MaxHeapBubbleUp(int* /* array */, int /* indexToBubble */, int /* numElements */) {}; // do a max heap bubble up
int MaxHeapPopHead(int* /* array */, int& /* numElements */) { return 0; }; // pop max heap head (max element), the int reference numElements would be decremented
void HeapSort(int* array, int len) 
{
	if (array && len > 1) 
	{
		for (int i = 1; i < len; ++i) 
		{
			int indexToBubble = i;
			int numElements = indexToBubble + 1;
			MaxHeapBubbleUp(array, indexToBubble, numElements);
		}

		for (int i = len; i > 1; --i)
		{
			int lenAfterPop = i;
			array[i - 1] = MaxHeapPopHead(array, lenAfterPop); // MaxHeapPopHead would decrement lenAfterPop
		}
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
	return (int)(pStr - pStart);
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
			++pTarget; // NOTE: if not doing this in place, we would populate our target buffer here, like targetStdString.push_back(*pString)
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
	int lengthOneIterator = (int)binaryNumOne.size() - 1;
	int lengthTwoIterator = (int)binaryNumTwo.size() - 1;

	std::string result;
	int carry = 0;
	for (; lengthOneIterator >= 0 || lengthTwoIterator >= 0 || carry > 0; --lengthOneIterator, --lengthTwoIterator)
	{
		int numOne = lengthOneIterator >= 0 ? (binaryNumOne[lengthOneIterator] - '0') : 0;
		int numTwo = lengthTwoIterator >= 0 ? (binaryNumTwo[lengthTwoIterator] - '0') : 0;
		int sum = numOne + numTwo + carry;
	
		// NOTE!! much better big O is result.push_back(), then at end: std::reverse(result.begin(), result.end())
		result.insert(0, sum % 2 ? "1" : "0");
		carry = sum / 2;
	}
	return result;
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

BinaryTreeNode* BinarySearchTreeFindIterative(BinaryTreeNode* pRoot, int val)
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

bool BinarySearchTreeAddNoDuplicatesIterative(BinaryTreeNode** pRoot, int val)
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

BinaryTreeNodeWithParent* FindPrevNodeInBinarySearchTree(BinaryTreeNodeWithParent* node)
{
	if (!node)
	{
		return nullptr;
	}

	if (node->left)
	{
		BinaryTreeNodeWithParent* prev = node->left;
		while (prev->right)
		{
			prev = prev->right;
		}
		return prev;
	}

	while (node->parent && node->parent->left == node)
	{
		node = node->parent;
	}
	return node->parent;
}

// graphs -------------------------------

const GraphNode* GraphDepthFirstSearch(const GraphNode& graph, int val, std::unordered_set<const GraphNode*>& searched);
const GraphNode* GraphDepthFirstSearch(const GraphNode& graph, int val)
{
	std::unordered_set<const GraphNode*> searched;
	return GraphDepthFirstSearch(graph, val, searched);
}

// NOTE: alternate to using an unordered_set is flagging searched nodes (both methods are O(1))
const GraphNode* GraphDepthFirstSearch(const GraphNode& graphNode, int val, std::unordered_set<const GraphNode*>& searched)
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

// NOTE: very similar to GraphBreadthFirstSearch (differences marked)
const GraphNode* GraphDepthFirstSearchIterative(const GraphNode& graph, int val)
{
	std::unordered_set<const GraphNode*> searched; // NOTE: alternate to a searched list is flaging each searched node (std::queue CANNOT be searched, but would be O(n) anyway)
	std::stack<const GraphNode*> nodes; // NOTE: different to bfs, Stack is used
	nodes.push(&graph); // NOTE: different to bfs, not added to searched at this point
	while (!nodes.empty())
	{
		const GraphNode* frontNode = nodes.top();
		nodes.pop();

		if (searched.end() != searched.find(frontNode)) { // already searched, NOTE: different to bfs
			continue;
		}

		if (frontNode->val == val)
		{
			return frontNode;
		}
		searched.insert(frontNode); // NOTE: different to bfs, for iterative depth first search, this is the correct place to mark visited
		
		for (std::vector<GraphNode*>::const_reverse_iterator childNode = frontNode->children.rbegin(); childNode != frontNode->children.rend(); ++childNode)
		{
			if (*childNode && searched.end() == searched.find(*childNode)) // O(1) for set.find() (assuming no hashing collisions)
			{
				// NOTE: different to bfs, NOT added to searched here
				nodes.push(*childNode);
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

	std::vector<GridCell*> adjacentTraversableGridCells; // grid cells next to this grid cell which can be traversed to
};
struct PathCell 
{
	bool operator<(const PathCell& rhs)
	{
		return heuristic + distance < rhs.heuristic + rhs.distance;
	}
	const GridCell* parent; // used to index into the closed list
	const GridCell* cell; 
	int heuristic, distance;
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

// NOTE: this example uses a closed list, see DavidByttowAlgorithms.h/cpp DijkstraSearch() for an example where nodes has an isOpen flag instead
bool AStar(AStarPath& outPath, const Grid& grid, const GridCell& start, const GridCell& end)
{
	std::vector<PathCell> openList; // would usually be a minheap
	std::unordered_map<const GridCell*, const GridCell*> closedList; // NOTE: could also pre-allocate pathnodes which are marked as unexplored/open/closed
		
	PathCell startCell;
	startCell.cell = &start;
	startCell.parent = nullptr; // no parent 
	startCell.distance = 0;
	startCell.heuristic = grid.CalculateHeuristic(start, end); // estimate of how far to end
	AddToMinHeap(openList, startCell);
	
	while( !openList.empty() )
	{
		PathCell parentCell = PopElementWithSmallestDistancePlusHeuristic(openList); // get smallest element and remove from list 
		closedList.insert(std::make_pair(parentCell.cell, parentCell.parent)); // add element to explored closedList 

		if ( end == *parentCell.cell ) // end cell added to closed list
		{	
			const GridCell* cell = parentCell.cell;
			while (nullptr != cell)
			{
				outPath.AddToFront(*cell);
				cell = closedList[cell];
			}
			return true;
		}

		const std::vector<GridCell*>& adjacentCells = parentCell.cell->adjacentTraversableGridCells;

		int numAdjacentCells = (int)adjacentCells.size();
		for (int adjacent = 0; adjacent < numAdjacentCells; ++adjacent)
		{
			if ( closedList.end() != closedList.find(adjacentCells[ adjacent ]) )
			{
				continue; // grid cell has already been explored and put onto the closed list, don't re-explore
			}

			int openListIndex = GetItemIndex(openList, *adjacentCells[ adjacent ]);
			if (openListIndex >= 0) // it's on the open list
			{
				int newDistToHere = parentCell.distance + grid.CalculateCost(*parentCell.cell, *adjacentCells[ adjacent ]);
				if (newDistToHere < openList[ openListIndex ].distance)
				{
					openList[openListIndex].parent = parentCell.cell;
					openList[ openListIndex ].distance = newDistToHere;
					MinHeapReSort(openListIndex); // resort the index which has changed in the minheap
				}
			}
			else
			{
				PathCell newCell;
				newCell.cell = adjacentCells[ adjacent ];
				newCell.parent = parentCell.cell;
				newCell.distance = parentCell.distance + grid.CalculateCost(*parentCell.cell, *newCell.cell);
				newCell.heuristic = grid.CalculateHeuristic(*newCell.cell, end); // estimate of how far to end
				AddToMinHeap(openList, newCell);
			}
		}
	}	
	return false;
}

} // AStarSearch AStarSearch AStarSearch AStarSearch AStarSearch AStarSearch

typedef std::unordered_map<const GraphNode*, const GraphNode*> BidirectionalVisited; // node to parent node
std::vector<const GraphNode*> MakePath(const GraphNode* intersection, BidirectionalVisited& fromStart, BidirectionalVisited& fromEnd)
{
	std::vector<const GraphNode*> result;
	// get the nodes from the start node to the intersection node
	for (const GraphNode* iter = intersection; iter; iter = fromStart[iter])
	{
		result.push_back(iter); // O(1), alternately, insert front would be O(N) shuffle down
	}
	std::reverse(result.begin(), result.end()); // better than inserting front in the above loop, as that causes an O(N) shuffle down every insert

	// get the nodes after the intersection node to the end node
	for (const GraphNode* iter = fromEnd[intersection]; iter; iter = fromEnd[iter])
	{
		result.push_back(iter);
	}
	return result;
}

std::vector<const GraphNode*> GraphBidirectionalBreadthFirstSearch(const GraphNode& start, const GraphNode& to)
{
	enum {fromStart = 0, fromEnd, MaxDirections};
	BidirectionalVisited visited[MaxDirections]; // two visited, one coming from start, one from end
	std::queue<const GraphNode*> toSearch[MaxDirections]; // two toSearch queues, one coming from start, one from end
	visited[fromStart].insert(std::make_pair(&start, nullptr));
	toSearch[fromStart].push(&start);

	visited[fromEnd].insert(std::make_pair(&to, nullptr));
	toSearch[fromEnd].push(&to);

	while (!toSearch[fromStart].empty() && !toSearch[fromEnd].empty())
	{
		for (int i = fromStart; i < MaxDirections; ++i) {
			const GraphNode* curr = toSearch[i].front();
			toSearch[i].pop();

			BidirectionalVisited otherVisitedList = visited[(i + 1) % MaxDirections];
			if (otherVisitedList.end() != otherVisitedList.find(curr)) { // if it's in the other visited list
				return MakePath(curr, visited[fromStart], visited[fromEnd]);
			}

			for (GraphNode* child : curr->children) {
				if (visited[i].end() == visited[i].find(child)) { // not in visited
					visited[i].insert(std::make_pair(const_cast<const GraphNode*>(child), curr));
					toSearch[i].push(child);
				}
			}
		}
	}
	return std::vector<const GraphNode*>();
}

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
	// see http://stackoverflow.com/questions/1518726/recursive-fibonacci - alternate algo is slow as is (but could be improved with memoization)
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
	std::unordered_map<int, int> counts;
	for (int source = 0; source < len; ++source)
	{
		auto iter = counts.find(array[source]);
		if (counts.end() == iter) // doesn't exist
		{
			counts.insert(std::make_pair(array[source], -1)); // insert -1 for count initially, -1 means 1 instance
		}
		else
		{
			iter->second = 0; // don't make count higher than 0, -1 means 1 instance, and 0 means multiple instances		
		}
	}

	int target = 0;
	for (int source = 0; source < len; ++source)
	{
		array[target] = array[source];
		if (counts[array[source]] >= 0) // if this entry has dupes
		{
			if (counts[array[source]]++ == N) // NOTE: post increment of count
			{
				++target;
			}
		}
		else { // this entry is unique (-1 for counts)
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
		// it's not in both, we want to keep it (every arrayOne element has an entry in common)
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
bool GetNthSmallestElementFromUnionOfSortedNoDuplicatesArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo)
{
	lenOne = arrOne ? lenOne : 0;
	lenTwo = arrTwo ? lenTwo : 0;
	
	if (N >= lenOne + lenTwo) {
		return false;
	}

	int oneIndex = 0;
	int twoIndex = 0;
	for (;oneIndex+twoIndex <= N;)
	{
		if ( oneIndex < lenOne && twoIndex < lenTwo ) // both in bounds
		{
			NthSmallestElement = arrOne[oneIndex] < arrTwo[twoIndex] ? arrOne[oneIndex++] : arrTwo[twoIndex++];			
		}
		else // either one or two will be in bounds (not both)
		{
			NthSmallestElement = oneIndex < lenOne ? arrOne[oneIndex++] : arrTwo[twoIndex++];
		}
	}
	return true;
}

bool GetNthSmallestElementFromUnionOfSortedArrays(int& NthSmallestElement, int N, int* arrOne, int lenOne, int* arrTwo, int lenTwo)
{
	lenOne = arrOne ? lenOne : 0;
	lenTwo = arrTwo ? lenTwo : 0;

	if (N >= (lenOne + lenTwo)) {
		return false;
	}

	int oneIndex = 0;
	int twoIndex = 0;	
	int NthCounter = 0;
	for (; NthCounter <= N && (oneIndex < lenOne || twoIndex < lenTwo);)
	{
		int newValue = 0;
		if (oneIndex < lenOne && twoIndex < lenTwo) // both in bounds
		{
			newValue = arrOne[oneIndex] < arrTwo[twoIndex] ? arrOne[oneIndex++] : arrTwo[twoIndex++];
		}
		else // one or two will be in bounds (not both)
		{
			newValue = oneIndex < lenOne ? arrOne[oneIndex++] : arrTwo[twoIndex++];
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
				// checking here is only required if we are allowing duplicate entries in the array
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
	std::unordered_map<int, bool> used;
	for (int intArrayIndex = 0; intArrayIndex < numIntNumbers; ++intArrayIndex)
	{
		used.insert(std::make_pair(intNumbers[intArrayIndex], false));
	}

	// IMPORTANT: go over string numbers second so that StringToInt() is only called once for each number
	std::unordered_map<int, bool>::iterator endIter = used.end();
	int targetCounter = 0;
	for (int stringArrayIndex = 0; stringArrayIndex < numStringNumbers; ++stringArrayIndex)
	{
		stringNumbers[targetCounter] = stringNumbers[stringArrayIndex];
		std::unordered_map<int, bool>::iterator iter = used.find(StringToInt(stringNumbers[stringArrayIndex])); // in reality std::stoi() would be used instead of StringToInt()
		if (endIter != iter)
		{
			iter->second = true; // in both
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
		if (!used[intNumbers[intArrayIndex]]) // used in only the first list
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

bool IsInDictionary(const std::unordered_set<std::string>& dictionary, const char* word)
{
	return dictionary.end() != dictionary.find(word);
}

void FindWords(int dimension, const std::unordered_set<std::string>& dictionary, int parentDice, int currentSequencePosition,
			bool* usedDice, const char* dice, char* currentSequence, std::unordered_set<std::string>& found)
{
	if (!usedDice[parentDice])
	{
		usedDice[parentDice] = true;
		currentSequence[currentSequencePosition] = dice[parentDice];

		if (currentSequencePosition >= 2 && IsInDictionary(dictionary, currentSequence)) // if we have a word in the dictionary which is at least 3 letters long
		{
			found.insert(currentSequence);
		}

		if ('Q' == dice[parentDice])
		{
			currentSequence[currentSequencePosition+1] = 'U';
			if (currentSequencePosition+1 >= 2 && IsInDictionary(dictionary, currentSequence)) // if we have a word in the dictionary which is at least 3 letters long
			{
				found.insert(currentSequence);
			}
			currentSequence[currentSequencePosition+1] = '\0';
		}

		int row = 0;
		int col = 0;
		ToRowAndCol(parentDice, dimension, row, col);

		for (int childRow = row - 1; childRow <= row + 1; ++childRow)
		{
			if (childRow >= 0 && childRow < dimension)
			{
				for (int childCol = col - 1; childCol <= col + 1; ++childCol)
				{
					if (childCol >= 0 && childCol < dimension)
					{
						int childDice = ToIndex(childRow, childCol, dimension);
						FindWords(dimension, dictionary, childDice, currentSequencePosition+1, usedDice, dice, currentSequence, found);
						if (currentSequence[currentSequencePosition] == 'Q')
						{
							currentSequence[currentSequencePosition+1] = 'U';
							FindWords(dimension, dictionary, childDice, currentSequencePosition + 2, usedDice, dice, currentSequence, found);
							currentSequence[currentSequencePosition+1] = '\0';
						}
					}
				}
			}
		}
		currentSequence[currentSequencePosition] = '\0';
		usedDice[parentDice] = false;
	}
}

// IMPROVEMENTS/SIMPLIFICATIONS
// make dice: char dice[][4]
// remove usedDice array, instead set members of dice to '\0' when they have been used (this works ok when dice is char dice[][4])
// remove dimension, assume literal 4 everywhere
void Boggle(const std::unordered_set<std::string>& dictionary, const char* dice, int dimension, std::unordered_set<std::string>& found)
{
	int diceLength = dimension*dimension;
	bool* usedDice = new bool[diceLength];
	if (usedDice) 
	{
		memset(usedDice, 0, sizeof(bool) * diceLength);
		char* currentSequence = new char[diceLength*2 + 1]; // worst case scenario
		if (currentSequence) 
		{
			memset(currentSequence, '\0', sizeof(char)*(diceLength*2 + 1));

			for (int index = 0; index < diceLength; ++index)
			{
				FindWords(dimension, dictionary, index, 0, usedDice, dice, currentSequence, found);
			}
			delete[] currentSequence;
		}
		delete[] usedDice;
	}
}

} // end namespace boggle

namespace findLargestEncompassingRectangle
{
// using list for activeRectangles as we delete from the middle (O(1) operation for list)
int AddRectangleColumn(std::list<std::pair<int, int>>& activeRectangles, int newHeight, int largestRectangleArea)
{
	bool equalHeightFound = false; // used to see if we need to add a new rectangle
	for (auto iter = activeRectangles.begin(); iter != activeRectangles.end();)
	{
		if (iter->first >= newHeight) // if this rectangle is larger than the height of the column added, it's finished
		{			
			if (equalHeightFound) // if an earlier rectangle was found with equal height, we don't need this one
			{
				iter = activeRectangles.erase(iter); // this rectangle will have a smaller width than the earlier one added, so don't need this one
				continue;
			}
			iter->first = newHeight; // only need to keep the portion of the rectangle which is equal to the height of the new column added
			equalHeightFound = true; // don't need to add a new rectangle, as we have updated this existing one
		}

		++iter->second; // rectangle width expands by one column
		largestRectangleArea = std::max(iter->first*iter->second, largestRectangleArea);
		++iter; // goto next rectangle
	}

	if (!equalHeightFound)
	{
		activeRectangles.push_back(std::make_pair(newHeight, 1));
		largestRectangleArea = std::max(newHeight, largestRectangleArea);
	}
	return largestRectangleArea;
}

int FindLargestEncompassingRectangleOfZeros(char* array, int numRows, int numColumns)
{
	int* freeColumnHeights = new int[numRows*numColumns]; // NOTE: instead of allocating this, we could overwrite array (if clobbering array is ok)

	// go over columns recording height of 0's at each slot
	int largestArea = 0;
	for (int row = 0; row < numRows; ++row)	
	{
		std::list<std::pair<int, int>> activeRectangles; // using list as AddRectangleColumn() deletes from the middle (O(1) operation for list)
		for (int col = 0; col < numColumns; ++col)
		{
			int arrayIndex = boggle::ToIndex(row, col, numColumns);
			if (0 != array[arrayIndex]) // it's not a zero
			{
				freeColumnHeights[arrayIndex] = 0;
				activeRectangles.clear();
			}
			else
			{
				freeColumnHeights[arrayIndex] = 1 + (row > 0 ? freeColumnHeights[boggle::ToIndex(row - 1, col, numColumns)] : 0);
				largestArea = AddRectangleColumn(activeRectangles, freeColumnHeights[arrayIndex], largestArea);
			}
		}
	}

	delete[] freeColumnHeights;
	return largestArea;
}

} // findLargestEncompassingRectangle


std::string IntToBinaryString(int input)
{
	if (0 == input)
	{
		return "0";
	}
	int numBits = sizeof(int) * 8;

	std::string numString;
	for (int bit = numBits - 1; bit >= 0; --bit)
	{
		unsigned int result = (1 << bit) & input;

		if (result || !numString.empty())
		{
			numString.push_back(result ? '1' : '0');
		}
	}
	return numString;
}

std::string UnsignedIntToBinaryString(unsigned int val)
{
	// if you want to use a char array, then below loop must be done twice, first time just to get char array length
	// alternately, 1 + (base 2 log of number) will get the length
	std::string numString;
	do
	{
		int figure = val % 2;
		numString.push_back(figure ? '1' : '0');
		val /= 2;
	} while (0 != val);
	
	std::reverse(numString.begin(), numString.end());
	return numString;
}

bool BinaryStringToUnsignedInt(const char* string, unsigned int& returnNumber)
{
	if (!string || '\0' == *string)
	{
		return false;
	}

	returnNumber = 0;
	while ('\0' != *string)
	{
		returnNumber *= 2;
		if (*string >= '0' && *string <= '1')
		{
			returnNumber += *string - '0';
		}
		else
		{
			return false; // error
		}
		++string;
	}
	return true;
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
		numString.push_back(IntToHexChar(figure));
		val /= 16;
	} while (0 != val);

	std::reverse(numString.begin(), numString.end());
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