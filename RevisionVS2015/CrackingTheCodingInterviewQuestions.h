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
bool AreStringsOneEditDifferenceFromEachOther(const std::string& str1, const std::string& str2); // 1.5, page 91, are the two strings just one insert/remove/edit from each other
void CompressString(std::string& str); // convert "aaabbccccde" to "a3b2c4de", only perform the compression if the compressed string would be smaller than the original
void RotateImage(int** array, unsigned int N); // 1.7, p91
void ZeroMatrix(int** mat, int rows, int cols); // <<==1.8, p91, when a zero is found in the matrix, set the entire row and column to zeros
bool IsStringOneARotationOfStringTwo(const char* stringOne, const char* stringTwo); // 1.9, p91 "waterbottle" is a rotation of "terbottlewa"

// chapter 2, linked lists

void RemoveDuplicatesFromUnsortedLinkedList(LinkedListElement** head); // 2.1
void RemoveDuplicatesFromUnsortedLinkedListO1Space(LinkedListElement** head); // 2.1 follow-up
LinkedListElement* GetKthToLastElement(LinkedListElement* ptr, int k); // 2.2
void DeleteNode(LinkedListElement* nodeToDelete); // <<== implement, p94, the passed in node is not the head, it is a node in the middle of the linked list, it cannot be the head or end
void PartitionLinkedList(LinkedListElement** head, int partitionVal); // <== implement, everything less than partition must be put before everything greater or equal to partition

LinkedListElement* SumListsReverse(LinkedListElement* listOne, LinkedListElement* listTwo); // <<== 2.5, see p95
LinkedListElement* SumListsForward(LinkedListElement* listOne, LinkedListElement* listTwo); // <<== implement, see p95
bool IsPalindromeIterative(LinkedListElement* head); // <<== 2.6, p95, the linked list is a sentance, is the sentance a palindrome?
bool IsPalindromeRecursive(LinkedListElement* head); // << implement, p95, the linked list is a sentance, is the sentance a palindrome?
LinkedListElement* GetNoneLoopedLinkedListsIntersectionNode(LinkedListElement* listOne, LinkedListElement* listTwo); // << p95 2.7, do lists converge?
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

template <class T> struct StackWithMinElement : private std::stack<T> // 3.2, p98, min stack based method
{
	std::stack<T> minStack;

	void push(const T& newVal) // name hides std::stack<T>::push()
	{
		std::stack<T>::push(newVal); // needs explicit scoping as std::stack<T>::push() is name hidden
		if (minStack.empty() || newVal <= minStack.top())
		{
			minStack.push(newVal);
		}
	}

	void pop() // name hides std::stack<T>::pop()
	{
		if (!empty())
		{
			T prevTop = std::stack<T>::top(); // needs explicit scoping as std::stack<T>::top() is name hidden
			std::stack<T>::pop(); // needs explicit scoping as std::stack<T>::pop() is name hidden
			if (prevTop == minStack.top())
			{
				minStack.pop();
			}		
		}
	}

	T min()
	{
		return minStack.top();
	}

	// NOTE: question doesn't require implementing this function - it is just used for debugging
	T top() // name hides std::stack<T>::push()
	{
		return std::stack<T>::top(); // needs explicit scoping as std::stack<T>::top() is name hidden
	}
};

// p99 3.3
template<class T, size_t N> class StackOfPlates
{
private:
	std::vector<std::vector<T>> stacks; // each stack represented by a vector so top and bottom can be accessed in PopAt() function

	void Push(const T& newEntry)
	{
		if (stacks.size() == 0 || stacks[stacks.size() - 1].size() == N)
		{
			stacks.push_back(std::vector<T>());
		}
		stacks[stacks.size() - 1].push_back(newEntry); // end of vector is the top of the stack
	}

	void Pop(T& outVal)
	{
		if (stacks.size() > 0)
		{
			std::vector<T>& laststack = stacks[stacks.size() - 1];
			outVal = *(laststack.end()-1); // end of vector is the top of the stack
			laststack.erase(laststack.end()-1);
			if (laststack.empty())
			{
				stacks.erase(stacks.end() - 1);
			}
		}
	}

	void PopAt(T& outVal, size_t index)
	{
		if (index < stacks.size())
		{
			outVal = *(stacks[index].end()-1);
			stacks[index].erase(stacks[index].end() - 1);
			for (++index; index < stacks.size(); ++index)
			{
				stacks[index - 1].push_back(stacks[index][0]);
				stacks[index].erase(stacks[index].begin());
			}
			if (stacks[stacks.size() - 1].empty()) {
				stacks.erase(stacks.end() - 1);
			}
		}
	}
};

// p99 3.4
template<class T> class QueueWith2Stacks
{
	std::stack<T> newest;
	std::stack<T> oldest;

	void Push(const T& add)
	{
		newest.push(add);
	}

	void Pop(T& result)
	{
		if (oldest.empty())
		{
			while (!newest.empty())
			{
				olest.push(newest.top());
				newest.pop();
			}
		}
		result = oldest.top();
		oldest.pop();
	}
};

void SortStackUsingOneTemporaryStack(std::stack<int>& toSort); // 3.5, p99

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
bool IsBinarySearchTree(BinaryTreeNode* node); // p110, 4.5
struct BinaryTreeNodeWithParent { BinaryTreeNodeWithParent* left; BinaryTreeNodeWithParent* right; BinaryTreeNodeWithParent* parent; };
BinaryTreeNodeWithParent* FindNextNodeInBinarySearchTree(BinaryTreeNodeWithParent* node); // p110
bool SortDependancies(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes); // p110
bool SortDependanciesAltDFS(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes); // p110
BinaryTreeNode* FindFirstCommonAnscester(BinaryTreeNode* root, int nodeOne, int nodeTwo);
std::vector<std::vector<int>> CalculateBSTSequences(BinaryTreeNode* root); // <<<< implement, p110
bool IsSubTree(BinaryTreeNode* mainTree, BinaryTreeNode* potentialSubTree); // p111, 4.10
bool IsSubTreeAltMethod(BinaryTreeNode* mainTree, BinaryTreeNode* potentialSubTree); // p111, 4.10

// chapter 5 bit manipulation

void updateInt(int& n, int m, int i, int j); // p115, 5.1
std::string PrintBinary(float num); //<<== implement p116
int FlipBitToWin(int number); //<<== implement p116
void PrintNextAndPreviousNumberWithSameAmountOfOnes(unsigned int number); //<<== p116, 5.4
int Conversion(int left, int right); // p116
int PairwiseSwap(int number);
void DrawLine(std::vector<char>& screen, int widthInBits, int x1Bit, int x2Bit, int y); // 5.8

// chapter 6

// chapter 7

template<class T, int capacity> struct CircularArray
{
	T array[capacity];
	int start = 0;
	int numElements = 0;

	struct Iterator
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
			++numElements;
		}		
		else
		{
			array[start] = newElement;
			start = ++start % capacity;
		}
	}

	Iterator begin()
	{
		return Iterator(this, start);
	}

	Iterator end()
	{
		return Iterator(this, start+numElements);
	}
};

// chapter 8 dynamic programming -----------------------------------------------------------------------

int HowMany321StepPathsExist(int pathLength); // <<== implement , p134
std::vector<std::pair<int, int>> GetRobotPathInGrid(int grid[], int rows, int cols); // p135
int MagicIndex(int array[], int length); // <<== implement, p135
void GenerateAllSubSets(const std::vector<int>& input, std::vector<std::vector<int>>& output); // p135
unsigned int RecursiveUnsignedIntMultiply(unsigned int numberOne, unsigned int numberTwo); //p135, 8.5
bool TowersOfHanoi(); //<<=== implement p135
void PrintAllPermutations(const char* string); // 135, 8.7
std::vector<std::string> GetAllPermutations(const std::string& input); // 135, 8.7
std::vector<std::string> GenerateAllPermutationsNoDups(const std::string& input); // p135, 8.8 output strings have no dupes, input string may do
//std::vector<std::string> GenerateAllPermutationsNoDupsAlt(const std::string& input); // (p135) output strings have no dupes, input string may do
std::unordered_set<std::string> GenerateParens(int numParanthesis); // p136
void PaintFloodFill(CVector4 screen[1024][1024], int clickRow, int clickCol, const CVector4& newColor); // 8.10
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
bool SortedSearchNoSize(const vector_no_size<int>& input, int searchFor, int& foundIndex); // p150, 10.4
void PrintDuplicates(const std::vector<int>& nums);
void SortedMatrixSearch(); //<<< implement p151, 10.9

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

#endif