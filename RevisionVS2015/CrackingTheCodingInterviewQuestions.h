#ifndef _CrackingTheCodingInterviewQuestions_h_
#define _CrackingTheCodingInterviewQuestions_h_

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <list>
#include "ImportantAlgorithms.h"
#include "2KSports.h"

class CVector4;

// technical questions ------------------------------------------

// chapter 1, arrays and strings, p88 --------------------------------------------------------------------------------------------------

int CountCommonElementsInSortedArrays(int* arrOne, int lenOne, int* arrTwo, int lenTwo);
bool ConvertHexedecimalStringToUnsignedInt(const char* pHexedecimalString, int& outputInt);
bool ConvertUnsignedIntToHexedecimalString(int inputInt, std::string& outputHexedecimalString);

bool AreAllCharactersUniqueNoExtraDataStructures(const char* string);
bool IsPermutationOf(const char* jhs, const char* rhs);
bool IsPermutationOfNoExtraDataStructures(char* jhs, char* rhs); // implement this, sort both strings, then check each index is the same
void ReplaceSubString(char* string, int currentLength, int capacity, char remove = ' ', char* replaceWith = "%20"); // implement, p90, capacity should be big enough to update in-place
bool IsPermutationOfAPalindrome(const char* string); // << implement, can the string be rearranged to become a palindrome
bool AreStringsOneEditDifferenceFromEachOther(const char* source, const char* target); // <<== implement, are the two strings just one insert/remove/edit from each other
void CompressString(std::string& str); // convert "aaabbccccde" to "a3b2c4de", only perform the compression if the compressed string would be smaller than the original
void RotateMatrix90Degrees(int* matrix, int dimension); // <<==implement, matrix is dimension*dimension, rotate 90 degrees
void ZeroRowsAndColumns(int* matrix, int rows, int cols); // <<==implement, p91, when a zero is found in the matrix, set the entire row and column to zeros
bool IsStringOneARotationOfStringTwo(const char* stringOne, const char* stringTwo); // <<== implement, p91 "waterbottle" is a rotation of "terbottlewa"

// chapter 2, linked lists

void RemoveDuplicatesFromUnsortedLinkedList(LinkedListElement** head); // <<== implement
void DeleteNode(LinkedListElement* nodeToDelete); // <<== implement, p94, the passed in node is not the head, it is a node in the middle of the linked list, it cannot be the head or end
void PartitionLinkedList(LinkedListElement** head, int partitionVal); // <== implement, everything less than partition must be put before everything greater or equal to partition

int SumLists(LinkedListElement* listOne, LinkedListElement* listTwo); // <<== implement, see p95
bool IsPalindromeNoneRecursive(LinkedListElement* head); // <<== implement, p95, the linked list is a sentance, is the sentance a palindrome?
bool IsPalindromeRecursive(LinkedListElement* head); // << implement, p95, the linked list is a sentance, is the sentance a palindrome?
LinkedListElement* GetLinkedListIntersectionNode(LinkedListElement* listOne, LinkedListElement* listTwo); // << implement this, p95, do lists converge?
LinkedListElement* GetLoopNode(LinkedListElement* head); // <<implement this, p95

// chapter 3, stacks and queues

// IMPORTANT NOTE: 3.1 p98 -> this is nearly implemented by ImportantAlgorithms.h: LinkedListStackNoMemAlloc2KInterview, the only upgrade 
// is to make mHead an array in the base class LinkedListNoMemAlloc2KInterview, then update the Add() and Remove() functions to specify which mHead in the 
// array you want to use (also update Push() and Pop() in LinkedListStackNoMemAlloc2KInterview to do the same thing)

struct StackData 
{
	StackData* mpPrev;
	StackData* mpNext;
	void* mpData;
};

template <int N> struct StackWithMinElement : private LinkedListStackNoMemAlloc2KInterview<StackData, N> // implement 3.2, p98, min stack based method
{
	LinkedListStackNoMemAlloc2KInterview<StackData, N> minStack;

	StackData* Push(void*) // implement 3.2, p98, min stack based method
	{
		return nullptr;
	}

	void Pop(void*&) // implement 3.2, p98, min stack based method
	{
	}
};

// p99 3.3
class StackOfPlates // <<== implement
{

};

// p99 3.4
class QueueWith2Stacks // <<== implement
{

};

void SortStackUsingOneTemporaryStack(std::stack<int>& toSort); //<<== implement 3.5, p99

class AnimalShelter // <<== implement p99
{

};

// chapter 4 trees and graphs ------------------------------------------------------------------------

struct TreeAndGraphNode {};
struct Chapter4Graph {};
bool DoesRouteExistBetweenNodes(Chapter4Graph& graph, TreeAndGraphNode& from, TreeAndGraphNode& to); // << implement
BinaryTreeNode* CreateBinarySearchTreeFromSortedArray(int array[], int arrayLength); //<<== implement // 4.2 p109 create binary search tree with minimal height from sorted array
void ListOfDepths(std::vector<std::list<TreeAndGraphNode*>>& result); // <<== implement p109
struct BinaryNode { BinaryNode* left; BinaryNode* right; };
bool CheckBalanced(BinaryNode* root); //<<== implement p110
bool IsBinarySearchTree(BinaryTreeNode* node); // p110
struct BinaryTreeNodeWithParent { BinaryTreeNodeWithParent* left; BinaryTreeNodeWithParent* right; BinaryTreeNodeWithParent* parent; };
BinaryTreeNodeWithParent* FindNextNodeInBinarySearchTree(BinaryTreeNodeWithParent* node); // p110
bool SortDependancies(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes); // p110
bool SortDependanciesAltDFS(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes); // p110
BinaryTreeNode* FindFirstCommonAnscester(BinaryTreeNode* root, int nodeOne, int nodeTwo);
std::vector<std::vector<int>> CalculateBSTSequences(BinaryTreeNode* root); // <<<< implement, p110
bool IsSubTree(BinaryTreeNode* mainTree, BinaryTreeNode* potentialSubTree); // p111, 4.10
bool IsSubTreeAltMethod(BinaryTreeNode* mainTree, BinaryTreeNode* potentialSubTree); // p111, 4.10

// chapter 5 bit manipulation

void InsertSourceInTarget(int source, int sourceStartIndex, int sourceEndIndex, int& targetIndex); // implement, p115
std::string PrintBinary(float num); //<<== implement p116
int FlipBitToWin(int number); //<<== implement p116
void GetNextAndPreviousNumberWithSameAmountOfOnes(int number, int& previous, int& next); //<<== implement p116
int Conversion(int left, int right); // p116
int PairwiseSwap(int number);
void DrawLine(char screen[], int widthInBits, int x1Bit, int x2Bit, int y);

// chapter 6

// chapter 7

template<class T, int capacity> struct CircularArray
{
	T array[capacity];
	int start = 0;
	int numElements = 0;

	template<class T> struct Iterator
	{
		CircularArray<T, capacity>* array = nullptr;
		int index = 0;

		Iterator& operator++() // pre fix
		{
			++index;
			return *this;
		}

		Iterator operator++(int) // post fix
		{
			Iterator<T> temp(temp.array, index);
			++index;
			return temp;
		}

		T& operator*()
		{
			return array->array[index%capacity];
		}

		bool operator!=(const Iterator& rhs)
		{
			return index != rhs.index;
		}

		Iterator(CircularArray<T, capacity>* inputArray, int inputIndex)
			: array(inputArray)
			, index(inputIndex)
		{
		}
	};

	void Add(const T& newElement)
	{
		if (numElements < capacity)
		{
			array[(start + numElements) % capacity] = newElement;
			numElements = ++numElements;
		}		
		else
		{
			array[start] = newElement;
			start = ++start % capacity;
		}
	}

	Iterator<T> begin()
	{
		return Iterator<T>(this, start);
	}

	Iterator<T> end()
	{
		return Iterator<T>(this, start+numElements);
	}
};

// chapter 8 dynamic programming -----------------------------------------------------------------------

int HowMany321StepPathsExist(int pathLength); // <<== implement , p134
std::vector<std::pair<int, int>> GetRobotPathInGrid(int grid[], int rows, int cols); // p135
int MagicIndex(int array[], int length); // <<== implement, p135
void GenerateAllSubSets(const std::vector<int>& input, std::vector<std::vector<int>>& output); // p135
unsigned int RecursiveUnsignedIntMultiply(unsigned int numberOne, unsigned int numberTwo);
bool TowersOfHanoi(); //<<=== implement p135
void PrintAllPermutations(const char* string); // 135 
std::vector<std::string> GenerateAllPermutationsNoDups(const std::string& input); // (p135) output strings have no dupes, input string may do
//std::vector<std::string> GenerateAllPermutationsNoDupsAlt(const std::string& input); // (p135) output strings have no dupes, input string may do
std::unordered_set<std::string> GenerateParens(int numParanthesis); // p136
void PaintFloodFill(CVector4 screen[1024][1024], int clickRow, int clickCol, const CVector4& newColor);
void Coins(); //<<<<===== implement p362, 8.11
void Queens(); // <<<<==== implement p364, 8.12

// chapter 9 systems design and scalability --------------------------------------


// chapter 10 sorting and searching ------------------------------------------------------------------------

void SortedMerge(char arrayA[], int arrayALength, char arrayB[], int arrayBLength); // <<== implement p149, array has enough space for array b to be sorted into it
void GroupAanagrams(std::vector<std::string> stringsToGroup); // p150, group all the string together which are anagrams of one and other
int SearchInRotatedArray(int array[], int length); //<<== implement p150
int SearchInSparseArray(std::vector<std::string> strings); //p150

template<class T> struct vector_no_size : std::vector<T>
{
	T operator[](int index) const
	{
		if ((unsigned int)index >= size())
		{
			return -1;
		}
		return std::vector<T>::operator[](index);
	}
};
bool SortedSearchNoSize(const vector_no_size<int>& input, int searchFor, int& foundIndex); // p150
void SortedMatrixSearch(); //<<< implement p152

class RankFromStream // p151 10.10
{
public:
	void Track(int x);
	int GetRankOfNumber(int x);

private:
	struct RankData
	{
		int val = 0;
		int rank = 0;
		RankData* left = nullptr;
		RankData* right = nullptr;
	};
	RankData* stream = nullptr;
};

void PeaksAndValleys(int array[], int len); // p151 10.11

// chapter 12 ------------------------------------------------------------ C++

template<class T> class SmartPointer
{
public:
	SmartPointer(T* inPtr)
		: ptr(inPtr)
	{
		count = new int(1);
	}

	SmartPointer(const SmartPointer& sPtr)
		: ptr(sPtr.ptr)
		, count(sPtr.count)
	{
		++*count;
	}

	SmartPointer& operator=(const SmartPointer& sPtr)
	{
		if (this != &sPtr)
		{
			DecrementRef();

			ptr = sPtr.ptr;
			count = sPtr.count;
			++*count;
		}
		return *this;
	}

	~SmartPointer()
	{
		DecrementRef();
	}

private:
	void DecrementRef()
	{
		if (ptr && 0 == --*count)
		{
			delete ptr;
			delete count;

			ptr = nullptr;
			count = nullptr;			
		}
	}

	T* ptr = nullptr;
	int* count = nullptr;
};

#endif