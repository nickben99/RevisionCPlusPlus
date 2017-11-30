#include "CrackingTheCodingInterviewQuestions.h"
#include <string>
#include <sstream>
#include <iostream>
#include <queue>
#include <algorithm> // for std::max
#include <unordered_set>
#include <unordered_map>
#include "DavidByttowAlgorithms.h"
#include "CrackingTheCodingInterviewAlgorithms.h"
#include "CVector.h"

// technical questions ------------------------------------------------------------------------------------------------------------

// chapter 1, arrays and strings, p88 --------------------------------------------------------------------------------------------------

int CountCommonElementsInSortedArrays(int* arrOne, int lenOne, int* arrTwo, int lenTwo)
{
	int commonElementsCounter = 0;

	int arrayOneIndex = 0;
	int arrayTwoIndex = 0;
	while (arrayOneIndex < lenOne && arrayTwoIndex < lenTwo)
	{
		if (arrOne[arrayOneIndex] == arrTwo[arrayTwoIndex])
		{
			++commonElementsCounter;
			++arrayOneIndex;
			++arrayTwoIndex;
		}
		else if (arrOne[arrayOneIndex] < arrTwo[arrayTwoIndex])
		{
			++arrayOneIndex;
		}
		else
		{
			++arrayTwoIndex;
		}
	}
	return commonElementsCounter;
}

bool ConvertHexedecimalCharacterToInt(char hexChar, int& outNumber)
{
	if (hexChar >= '0' && hexChar <= '9')
	{
		outNumber = hexChar - '0';
		return true;
	}

	if (hexChar >= 'a' && hexChar <= 'f')
	{
		outNumber = 10 + hexChar - 'a';
		return true;
	}
	return false;
}

bool ConvertHexedecimalStringToUnsignedInt(const char* pHexedecimalString, int& outputInt)
{
	outputInt = 0;
	for (;'\0' != *pHexedecimalString; ++pHexedecimalString)
	{
		outputInt *= 16;
		int number = 0;
		if (ConvertHexedecimalCharacterToInt(*pHexedecimalString, number))
		{
			outputInt += number;
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool ConvertUnsignedIntToHexedecimalString(int, std::string&)
{
	// see UnsignedIntToHexString() in ImportantAlgorithms.h/cpp
	return true;
}

// an alternative to using quickSort in this function is to do an O(n^2) everything to everything check
bool AreAllCharactersUniqueNoExtraDataStructures(char* string)
{
	char* endIter = string;
	while (endIter)
	{
		++endIter;
	}
	int stringEndIndex = std::max((int)(endIter-string)-1, 0);
	quicksort::QuickSort(string, 0, stringEndIndex);

	while (string)
	{
		if (*(string + 1) && *string == *(string + 1))
		{
			return false;
		}
	}
	return true;
}

// lengths of strings could be checked first in this function, but getting the length of a string adds 
// another O(n), but avoids the higher cost O(1) comparisons
bool IsPermutationOf(const char* left, const char* right)
{
	int amountOfTimesUsed[CHAR_MAX + 1]; // could be std::unordered_map<int, int> amountOfTimesUsed;
	memset(amountOfTimesUsed, 0, sizeof(int)*(CHAR_MAX + 1));

	const char* leftIter = left;
	for (; *leftIter; ++leftIter)
	{
		++amountOfTimesUsed[*leftIter];
	}

	const char* rightIter = right;
	for (; *rightIter; ++rightIter)
	{
		if (amountOfTimesUsed[*rightIter] <= 0)
		{
			return false;
		}
		--amountOfTimesUsed[*rightIter];
	}
	return (leftIter-left) == (rightIter-right); // if they're the same length
}

bool AreStringsOneEditDifferenceFromEachOther(const std::string& str1, const std::string& str2)
{
	size_t str1Length = str1.size();
	size_t str2Length = str2.size();

	const std::string* longStr = &str1;
	size_t longStrLength = str1Length;

	const std::string* shortStr = &str2;
	size_t shortStrLength = str2Length;

	if (shortStrLength > longStrLength)
	{
		std::swap(longStr, shortStr);
		std::swap(longStrLength, shortStrLength);
	}

	int longStrIter = 0;
	int shortStrIter = 0;
	for (; longStrIter < longStrLength;)
	{
		if (shortStrIter < shortStrLength && (*longStr)[longStrIter] == (*shortStr)[shortStrIter]) {
			++shortStrIter;
		}

		if (++longStrIter-shortStrIter > 1) {
			return false;
		}
	}
	return true;
}

int NumFigures(int input) {
	int figures = 0;
	do {
		++figures;
		input /= 10;
	} while (input != 0);
	return figures;
}

void CompressString(std::string& str)
{
	int totalCount = 0;
	int consecutiveCount = 0;
	for (unsigned int count = 0; count < str.length(); ++count)
	{
		++consecutiveCount;
		if (count + 1 >= str.length() || str[count] != str[count + 1])
		{
			totalCount += 1;
			totalCount += NumFigures(consecutiveCount);
			consecutiveCount = 0;
		}
	}

	if (totalCount > str.length()) {
		return;
	}

	std::ostringstream oss;
	consecutiveCount = 0;
	for (unsigned int count = 0; count < str.length(); ++count)
	{
		++consecutiveCount;
		if (count + 1 >= str.length() || str[count] != str[count + 1])
		{		
			oss << str[count];
			oss << consecutiveCount;
						
			consecutiveCount = 0;
		}
	}
	str = oss.str();
}

void RotateImage(int** array, unsigned int N)
{
	unsigned int halfN = N / 2;
	for (unsigned int layer = 0; layer < halfN; ++layer)
	{
		unsigned int oppositeLayer = N - layer - 1;
		for (unsigned int index = layer; index < oppositeLayer; ++index)
		{
			int oppositeIndex = N - index - 1;
			int temp = array[oppositeIndex][layer]; // save left column
			array[oppositeIndex][layer] = array[oppositeLayer][oppositeIndex]; // left column = bottom row
			array[oppositeLayer][oppositeIndex] = array[index][oppositeLayer]; // bottom row = right column
			array[index][oppositeLayer] = array[layer][index]; // right column = top row
			array[layer][index] = temp; // top row = left column
		}
	}
}

void ZeroCol(int** mat, int rows, int col)
{
	for (int row = 0; row < rows; ++row)
	{
		mat[row][col] = 0;
	}
}

void ZeroRow(int** mat, int cols, int row)
{
	for (int col = 0; col < cols; ++col)
	{
		mat[row][col] = 0;
	}
}

void ZeroMatrix(int** mat, int rows, int cols)
{
	if (rows > 0 && cols > 0)
	{
		bool zeroTopRow = false;
		for (int col = 0; col < cols; ++col)
		{
			if (0 == mat[0][col]) {
				zeroTopRow = true;
				break;
			}
		}

		bool zeroLeftCol = false;
		for (int row = 0; row < rows; ++row)
		{
			if (0 == mat[row][0]) {
				zeroLeftCol = true;
				break;
			}
		}

		for (int col = 1; col < cols; ++col)
		{
			for (int row = 1; row < rows; ++row)
			{
				if (0 == mat[row][col])
				{
					mat[0][col] = mat[row][0] = 0;
				}
			}
		}

		for (int col = 0; col < cols; ++col)
		{
			if (mat[0][col]) {
				ZeroCol(mat, rows, col);
			}
		}

		for (int row = 0; row < rows; ++row)
		{
			if (mat[row][0]) {
				ZeroRow(mat, cols, row);
			}
		}

		if (zeroTopRow) {
			ZeroRow(mat, cols, 0);
		}

		if (zeroLeftCol) {
			ZeroCol(mat, rows, 0);
		}
	}
}

bool IsStringOneARotationOfStringTwo(const char* stringOne, const char* stringTwo)
{
	size_t lenOne = strlen(stringOne);
	if (lenOne > 0 && lenOne == strlen(stringTwo))
	{
		std::string findIn(stringOne);
		findIn += stringOne; // now StringOneStringOne
		return findIn.find(stringTwo) >= 0;
	}
	return false;
}

// chapter 2 linked lists ---------------------------------------------------------------------------------------------------

void RemoveDuplicatesFromUnsortedLinkedList(LinkedListElement** head)
{
	if (head && *head)
	{
		std::unordered_set<void*> dupes;
		LinkedListElement* prev = *head;
		LinkedListElement* iter = (*head)->next;
		dupes.insert((*head)->data);

		while (iter)
		{
			LinkedListElement* next = iter->next;
			if (dupes.end() != dupes.find(iter->data))
			{
				prev->next = next; // NOTE: prev will never be null
				delete iter;
			}
			else
			{
				dupes.insert(iter->data);
				prev = iter;
			}
			iter = next;
		}
	}
}

void RemoveDuplicatesFromUnsortedLinkedListO1Space(LinkedListElement** head)
{
	if (head)
	{
		for (LinkedListElement* outer = *head; outer; outer = outer->next)
		{
			LinkedListElement* prev = outer;
			for (LinkedListElement* inner = outer->next; inner;)
			{
				LinkedListElement* next = inner->next;
				if (outer->data == inner->data)
				{
					prev->next = next;
					delete inner;
				}
				else
				{
					prev = inner;
				}
				inner = next;
			}
		}
	}
}

// NOTE: this function assumes the data element in LinkedListElement contains a pointer to an int
LinkedListElement* SumListsReverse(LinkedListElement* listOne, LinkedListElement* listTwo) 
{
	LinkedListElement* newNumber = nullptr;
	int carry = 0;
	for (; nullptr != listOne || nullptr != listTwo || carry > 0; listOne = listOne->next, listTwo = listTwo->next)
	{
		int numOne = (nullptr != listOne) ? *(int*)listOne->data : 0;
		int numTwo = (nullptr != listTwo) ? *(int*)listTwo->data : 0;

		int sum = numOne + numTwo + carry;
		int digit = sum % 10;
		carry = sum / 10;

		LinkedListElement* node = new LinkedListElement();
		node->data = new int(digit);
		node->next = newNumber;
		newNumber = node;
	}
	return newNumber;
}

LinkedListElement* SumListsForward(LinkedListElement* /* listOne */, LinkedListElement* /* listTwo */)
{
	return nullptr; // implement
}

bool IsPalindromeIterative(LinkedListElement* head)
{
	std::stack<char> theStack;
	LinkedListElement* slow = head;
	LinkedListElement* fast = head;

	while (fast && fast->next)
	{
		theStack.push(*(char*)slow->data);
		slow = slow->next;
		fast = fast->next->next;
	}

	if (fast != nullptr) {
		slow = slow->next;
	}

	while (slow)
	{
		if (*(char*)slow->data != theStack.top()) {
			return false;
		}
		theStack.pop();
		slow = slow->next;
	}
	return true;
}

LinkedListElement* GetNoneLoopedLinkedListsIntersectionNode(LinkedListElement* listZero, LinkedListElement* listOne)
{
	if (listZero && listOne)
	{
		const int NumLists = 2;
		LinkedListElement* theLists[NumLists] = { listZero, listOne };
		int listLength[NumLists] = { 1, 1 };
		for (int list = 0; list < NumLists; ++list)
		{
			for (; theLists[list]->next; theLists[list] = theLists[list]->next)
			{
				++listLength[list];
			}
		}

		if (theLists[0] == theLists[1]) // lists do convergence onto the same end node
		{
			LinkedListElement** longerList = listLength[0] > listLength[1] ? &listZero : &listOne;
			int lengthDiff = std::abs(listLength[0] - listLength[1]);
			for (int i = 0; i < lengthDiff; ++i)
			{
				*longerList = (*longerList)->next;
			}

			for (; listZero != listOne; listZero = listZero->next, listOne = listOne->next) {}
			return listZero; // or listOne would also work
		}
	}
	return nullptr;
}

// chapter 3 stacks and queues ---------------------------------------------------------------

// this function implements the solution using an insertion sort type algorithm
void SortStackUsingOneTemporaryStack(std::stack<int>& toSort)
{
	std::stack<int> spareStack;
	while (!toSort.empty())
	{
		int curr = toSort.top();
		toSort.pop();
		while (!spareStack.empty() && curr < spareStack.top())
		{
			toSort.push(spareStack.top());
			spareStack.pop();
		}
		spareStack.push(curr);
	}

	while (!spareStack.empty())
	{
		toSort.push(spareStack.top());
		spareStack.pop();
	}
}

// chapter 4 trees and graphs -------------------------------------------------------------------

bool IsBinarySearchTree(BinaryTreeNode* node, BinaryTreeNode* left, BinaryTreeNode* right)
{
	if (node)
	{
		if ((nullptr == left || node->val > left->val) && (nullptr == right || node->val <= right->val))
		{
			return IsBinarySearchTree(node->left, left, node) && IsBinarySearchTree(node->right, node, right);
		}
		return false;
	}
	return true;
}

bool IsBinarySearchTree(BinaryTreeNode* node)
{
	return IsBinarySearchTree(node, nullptr, nullptr);
}

BinaryTreeNodeWithParent* FindNextNodeInBinarySearchTree(BinaryTreeNodeWithParent* node)
{
	if (!node)
	{
		return nullptr;
	}

	if (node->right)
	{
		BinaryTreeNodeWithParent* next = node->right;
		while (next->left)
		{
			next = next->left;
		}
		return next;
	}

	BinaryTreeNodeWithParent* parent = node->parent;
	while (parent && parent->right == node)
	{
		node = parent;
		parent = node->parent;
	}
	return parent;
}

bool SortDependancies(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes)
{
	return TopologicalSortBreadthFirstSearch(allInputNodes, nodeDependancies, outputNodes);
}

bool SortDependanciesAltDFS(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes)
{
	return TopologicalSortDepthFirstSearch(allInputNodes, nodeDependancies, outputNodes);
}

BinaryTreeNode* FindFirstCommonAnscesterInternal(BinaryTreeNode* root, int nodeOne, int nodeTwo, bool& foundOne, bool& foundTwo)
{
	if (root)
	{
		bool zeroFound = !foundOne && !foundTwo;	
		BinaryTreeNode* node = FindFirstCommonAnscesterInternal(root->left, nodeOne, nodeTwo, foundOne, foundTwo);
		if (node)
		{
			return node;
		}
		
		bool oneFound = foundOne || foundTwo;		
		node = FindFirstCommonAnscesterInternal(root->right, nodeOne, nodeTwo, foundOne, foundTwo);
		if (node)
		{
			return node;
		}		

		foundOne = nodeOne == root->val ? true : foundOne;
		foundTwo = nodeTwo == root->val ? true : foundTwo;

		if (zeroFound && oneFound && foundOne && foundTwo)
		{
			return root;
		}
	}
	return nullptr;
}

BinaryTreeNode* FindFirstCommonAnscester(BinaryTreeNode* root, int nodeOne, int nodeTwo)
{
	bool foundOne = false;
	bool foundTwo = false;
	return FindFirstCommonAnscesterInternal(root, nodeOne, nodeTwo, foundOne, foundTwo);
}

bool CheckAllChildren(BinaryTreeNode* mainTreeNode, BinaryTreeNode* potentialSubTreeNode)
{
	if (nullptr == mainTreeNode && nullptr == potentialSubTreeNode)
	{
		return true;
	}
	else if (nullptr != mainTreeNode && nullptr != potentialSubTreeNode)
	{
		return 	mainTreeNode->val == potentialSubTreeNode->val &&
			CheckAllChildren(mainTreeNode->left, potentialSubTreeNode->left) &&
			CheckAllChildren(mainTreeNode->right, potentialSubTreeNode->right);
	}
	return false;
}

bool IsSubTree(BinaryTreeNode* mainTree, BinaryTreeNode* potentialSubTree)
{
	if (!potentialSubTree)
	{
		return true;
	}
	if (mainTree)
	{
		if (mainTree->val == potentialSubTree->val &&
			CheckAllChildren(mainTree->left, potentialSubTree->left) &&
			CheckAllChildren(mainTree->right, potentialSubTree->right))
		{
			return true;
		}
		return IsSubTree(mainTree->left, potentialSubTree) || IsSubTree(mainTree->right, potentialSubTree);
	}
	return false;
}

void PreOrderSequenceCreate(BinaryTreeNode* root, std::string& preOrderSequence)
{
	if (!root)
	{
		preOrderSequence += "X ";
	}
	else
	{
		preOrderSequence += std::to_string(root->val) + " ";
		PreOrderSequenceCreate(root->left, preOrderSequence);
		PreOrderSequenceCreate(root->right, preOrderSequence);
	}
}

bool IsSubTreeAltMethod(BinaryTreeNode* mainTree, BinaryTreeNode* potentialSubTree)
{
	std::string mainTreeSequence;
	PreOrderSequenceCreate(mainTree, mainTreeSequence);

	std::string potentialSubTreeSequence;
	PreOrderSequenceCreate(potentialSubTree, potentialSubTreeSequence);
	return mainTreeSequence.find(potentialSubTreeSequence) >= 0;
}

// chapter 5 bit manipulation --------------------------------------------------------------------
void updateInt(int& n, int m, int i, int j)
{
	if (i >= 0 && i <= j && j < sizeof(int)*8)
	{
		int left = ~0 << (j + 1);
		int right = (1 << i) - 1;
		int mask = left | right;

		n &= mask;
		n |= ((m << i) & ~mask);
	}
}

std::string PrintBinary(float num)
{
	if (num >= 1 || num <= 0) 
	{
		return "ERROR";
	}

	std::string binary;
	binary.push_back('.');
	while (num > 0) 
	{
		/* Setting a limit on length: 32 characters */
		if (binary.size() > 32) {
			return "ERROR";
		}
		float r = num * 2;
		if (r >= 1) 
		{
			binary.push_back('1');
			num = r - 1;
		}
		else 
		{
			binary.push_back('0');
			num = r;
		}
	}
	return binary;
}

void PrintNextAndPreviousNumberWithSameAmountOfOnes(unsigned int number) //<<== p116, 5.4
{	
	unsigned int numberShifted = number;
	int numOnesToRight = 0;
	int index = 0;
	for (; 0 != numberShifted; numberShifted >>= 1, ++index) {
		bool isOne = 1 & numberShifted;
		bool nextIsZero = !(2 & numberShifted);

		if (isOne) {
			if (nextIsZero) {
				unsigned int nextHigherNumber = ~(1 << index) & number; // change 1 to 0 at index
				nextHigherNumber |= (1 << (index + 1)); // change 0 to 1 at index + 1
				nextHigherNumber &= ~((1 << index) - 1); // clear bits below index
				nextHigherNumber |= (1 << numOnesToRight) - 1; // put all the ones to the right in the lowest slots
				std::cout << std::endl << nextHigherNumber;
			}
			else {
				++numOnesToRight;
			}
		}
	}

	numberShifted = number;
	numOnesToRight = 0;
	index = 0;
	for (; 0 != numberShifted; numberShifted >>= 1, ++index) {
		bool isZero = !(1 & numberShifted);
		bool nextIsOne = 2 & numberShifted;

		if (isZero) {
			if (nextIsOne) {
				unsigned int nextLowerNumber = (1 << index); // change 0 to 1 at index
				nextLowerNumber |= ~(1 << (index + 1)) & number; // change 1 to 0 at index + 1
				nextLowerNumber &= ~((1 << index) - 1); // clear bits below index
				unsigned int temp = (1 << numOnesToRight) - 1;
				nextLowerNumber |= temp << (index = numOnesToRight); // move all ones to right to the right of the index
				std::cout << std::endl << nextLowerNumber;
			}
		}
		else {
			++numOnesToRight;
		}
	}
}

int Conversion(int left, int right)
{
	int count = 0;
	for (int diffs = left ^ right; diffs; diffs &= diffs - 1)
	{
		++count;
	}
	return count;
}

int PairwiseSwap(int number)
{
	int shiftedUp = (number & 0x55555555) << 1;
	int shiftedDown = ((number & 0xaaaaaaaa) >> 1) & 0x7fffffff; // & with 0x7fffffff to remove sign bit (not required if number was unsigned)
	return shiftedUp | shiftedDown;
}

// NOTE: this code would draw the line from x1 to x2 INCLUSIVE (although the question was not clear about whether x2 is inclusive/exclusive)
void DrawLine(std::vector<char>& screen, int widthInBits, int x1Bit, int x2Bit, int y)
{
	if (0 == widthInBits || x1Bit > x2Bit || x1Bit < 0 || x1Bit >= widthInBits || x2Bit < 0 || x2Bit >= widthInBits)
	{
		return;
	}

	int numCharBits = sizeof(char) * 8;
	int numRows = int((screen.size()*numCharBits) / widthInBits);
	if (y < 0 && y >= numRows)
	{
		return;
	}
	
	int startBit = y*widthInBits + x1Bit;
	int startByte = startBit / numCharBits;
	int endBit = y*widthInBits + x2Bit;
	int endByte = endBit / numCharBits;

	for (int iter = startByte; iter <= endByte; ++iter)
	{
		int startOffsetBit = (iter == startByte) ? startBit%numCharBits : 0;
		int endOffsetBit = (iter == endByte) ? endBit%numCharBits : (numCharBits - 1);
		unsigned char mask = (unsigned char)~0;
		mask >>= startOffsetBit;
		mask &= ~((1 << ((numCharBits - 1) - endOffsetBit)) - 1);
		screen[iter] |= mask;
	}
}

// chapter 8 dynamic programming --------------------------------------------------------------------------

void GenerateAllSubsetsInternal(std::vector<int>& current, const std::vector<int>& input, unsigned int position, std::vector<std::vector<int>>& output)
{
	if (position + 1 < input.size())
	{
		GenerateAllSubsetsInternal(current, input, position + 1, output);
		current.push_back(input[position]);
		GenerateAllSubsetsInternal(current, input, position + 1, output);
		current.erase(current.end() - 1);
	}
	else
	{
		output.push_back(current);
		current.push_back(input[position]);
		output.push_back(current);
		current.erase(current.end() - 1);
	}
}

void GenerateAllSubSets(const std::vector<int>& input, std::vector<std::vector<int>>& output)
{
	std::vector<int> current;
	GenerateAllSubsetsInternal(current, input, 0, output);
}

unsigned int RecursiveMultiplyHelper(int smaller, int bigger) 
{
	if (smaller == 0) {
		return 0;
	}
	else if (smaller == 1) {
		return bigger;
	}

	int s = smaller >> 1;
	int halfProd = RecursiveMultiplyHelper(s, bigger);

	if (smaller % 2 == 0) 
	{
		return halfProd + halfProd;
	}
	else 
	{
		return halfProd + halfProd + bigger;
	}
}

unsigned int RecursiveUnsignedIntMultiply(unsigned int numberOne, unsigned int numberTwo)
{
	int bigger = numberOne < numberTwo ? numberTwo : numberOne;
	int smaller = numberOne < numberTwo ? numberOne : numberTwo;

	return RecursiveMultiplyHelper(smaller, bigger);
}

void PrintAllPermutations(const char* string)
{
	PrintAllStringPermutations(string); // PrintAllStringPermutations() handles strings of unique and none unqique characters
}

std::vector<std::string> GetAllPermutations(const std::string& input, int index, const std::vector<std::string>& inputStrings)
{
	if (index < input.length())
	{
		std::vector<std::string> outputStrings;
		for (std::string inputStr : inputStrings)
		{
			for (int pos = 0; pos <= inputStr.length(); ++pos)
			{
				std::string cpy = inputStr;
				cpy.insert(inputStr.begin() + pos, input[index]);
				outputStrings.push_back(cpy);
			}
		}
		return GetAllPermutations(input, index + 1, outputStrings);
	}
	return inputStrings;
}

std::vector<std::string> GetAllPermutations(const std::string& input)
{
	return GetAllPermutations(input, 0, { "" });
}

void GenerateAllPermutationsNoDups(std::unordered_map<char, int>& used, size_t inputLen, size_t caret, char* curr, std::vector<std::string>& found)
{
	if (caret >= inputLen)
	{
		found.push_back(curr);
	}
	else
	{
		for (std::unordered_map<char, int>::iterator iter = used.begin(); iter != used.end(); ++iter)
		{
			if (iter->second > 0)
			{
				--iter->second;
				curr[caret] = iter->first;
				GenerateAllPermutationsNoDups(used, inputLen, caret + 1, curr, found);
				++iter->second;
			}
		}
	}
}

std::vector<std::string> GenerateAllPermutationsNoDups(const std::string& input)
{
	std::vector<std::string> results;
	if (input.length() > 0)
	{
		std::unordered_map<char, int> used;
		for (char letter : input)
		{
			std::unordered_map<char, int>::iterator found = used.find(letter);
			if (used.end() == found)
			{
				found = used.insert(std::make_pair(letter, 0)).first;
			}
			++found->second;
		}

		char* curr = new char[input.size() + 1];
		if (curr)
		{
			memset(curr, '\0', sizeof(char)*(input.size() + 1));
			GenerateAllPermutationsNoDups(used, input.length(), 0, curr, results);
			delete[] curr;
		}
	}
	return results;
}

//void GeneratePermutationsInternalAlt(const std::string& input, unsigned int position, int& dupeCount, std::string& current, 
//									std::unordered_map<char, int>& used, std::vector<std::string>& results)
//{
//	for (unsigned int index = 0; index < input.size(); ++index)
//	{
//		auto iter = used.find(input[index]);
//		if (used.end() == iter)
//		{
//			iter = used.insert(std::make_pair(input[index], 0)).first;
//		}		
//
//		if (1 == ++iter->second)
//		{
//			current.push_back(input[index]);
//		}
//		else
//		{
//			++dupeCount;
//		}
//
//		if (position + dupeCount + 1 < input.size())
//		{
//			GeneratePermutationsInternalAlt(input, position + 1, dupeCount, current, used, results);
//		}
//		else
//		{
//			results.push_back(current);
//		}		
//
//		iter = used.find(input[index]);
//		if (0 == --iter->second)
//		{
//			current.resize(current.size() - 1);
//		}
//		else
//		{
//			--dupeCount;
//		}
//	}
//}
//
//std::vector<std::string> GenerateAllPermutationsNoDupsAlt(const std::string& input)
//{
//	std::unordered_map<char, int> used;
//	std::string currentString;
//	std::vector<std::string> results;
//	int dupeCount = 0;
//	GeneratePermutationsInternalAlt(input, 0, dupeCount, currentString, used, results);
//	return results;
//}

std::unordered_set<std::string> GenerateParens(int numParanthesis)
{
	std::unordered_set<std::string> returnStrings;
	if (numParanthesis <= 0)
	{
		return returnStrings;
	}
	else if (1 == numParanthesis)
	{
		returnStrings.insert("()");
	}
	else
	{
		std::unordered_set<std::string> tempStrings = GenerateParens(numParanthesis - 1);
		for (std::string temp : tempStrings)
		{
			int startInsertionPoint = (int)temp.size() / 2;
			std::string centerCopy = temp;
			centerCopy.insert(startInsertionPoint, "()");
			returnStrings.insert(centerCopy);

			for (int insertionPoint = 1; insertionPoint <= startInsertionPoint; ++insertionPoint)
			{
				std::string leftCopy = temp;
				leftCopy.insert(startInsertionPoint - insertionPoint, "()");
				std::string rightCopy = temp;
				rightCopy.insert(startInsertionPoint + insertionPoint, "()");

				returnStrings.insert(leftCopy);
				returnStrings.insert(rightCopy);				
			}
		}
	}
	return returnStrings;
}

void PaintFloodFillInternal(CVector4 screen[1024][1024], int row, int col, const CVector4& clickPointColor, const CVector4& newColor)
{
	if (row >= 0 && row < 1024 && col >= 0 && col < 1024 && clickPointColor == screen[row][col])
	{
		screen[row][col] = newColor;

		PaintFloodFillInternal(screen, row - 1, col - 1, clickPointColor, newColor); // top left
		PaintFloodFillInternal(screen, row - 1, col, clickPointColor, newColor); // top top
		PaintFloodFillInternal(screen, row - 1, col + 1, clickPointColor, newColor); // top right
		PaintFloodFillInternal(screen, row, col - 1, clickPointColor, newColor); // left
		PaintFloodFillInternal(screen, row, col + 1, clickPointColor, newColor); // right
		PaintFloodFillInternal(screen, row + 1, col - 1, clickPointColor, newColor); // bottom left
		PaintFloodFillInternal(screen, row + 1, col, clickPointColor, newColor); // bottom bottom
		PaintFloodFillInternal(screen, row + 1, col + 1, clickPointColor, newColor); // bottom right
	}
}

void PaintFloodFill(CVector4 screen[1024][1024], int clickRow, int clickCol, const CVector4& newColor)
{
	CVector4 clickPointColor = screen[clickRow][clickCol];
	PaintFloodFillInternal(screen, clickRow, clickCol, clickPointColor, newColor);
}

// chapter 10 sorting and searching ----------------------------------------------------------------------

int SearchInSparseArrayInternal(const std::vector<std::string>& strings, const std::string& searchFor, int lowIndex, int highIndex)
{
	if (lowIndex > highIndex)
	{
		return -1;
	}

	int centralIndex = (lowIndex + highIndex) / 2;
	if (0 == strings[centralIndex].size())
	{
		int lowCentralIndex = centralIndex;
		int highCentralIndex = centralIndex;
		while (true)
		{
			if (lowCentralIndex > lowIndex && 0 != strings[--lowCentralIndex].size())
			{
				centralIndex = lowCentralIndex;
				break;
			}
			else if (highCentralIndex < highIndex && 0 != strings[++highCentralIndex].size())
			{
				centralIndex = highCentralIndex;
				break;
			}
			else if (lowCentralIndex == lowIndex && highCentralIndex == highIndex)
			{
				return -1;
			}
		}
	}

	if (strings[centralIndex] == searchFor)
	{
		return centralIndex;
	}
	else if (searchFor > strings[centralIndex])
	{
		return SearchInSparseArrayInternal(strings, searchFor, centralIndex + 1, highIndex);
	}
	return SearchInSparseArrayInternal(strings, searchFor, lowIndex, centralIndex - 1);	
}

int SearchInSparseArray(const std::vector<std::string>& strings, std::string searchFor)
{
	if (0 == searchFor.size())
	{
		return -1;
	}
	return SearchInSparseArrayInternal(strings, searchFor, 0, (int)strings.size() - 1);
}

// using a vector, but assuming it would give -1 for an out of bounds
bool SortedSearchNoSize(const vector_no_size<int>& input, int searchFor, int& foundIndex)
{
	int highIndex = 1;
	for (; input[highIndex] != -1 && input[highIndex] < searchFor; highIndex *= 2)
	{
	}
	int lowIndex = highIndex / 2;

	while (lowIndex <= highIndex)
	{
		int centralIndex = (lowIndex + highIndex) / 2;
		int centralValue = input[centralIndex];
		if (centralValue == searchFor)
		{
			foundIndex = centralIndex;
			return true;
		}
		else if (centralValue == -1 || searchFor < centralValue)
		{
			highIndex = centralIndex - 1;
		}
		else
		{
			lowIndex = centralIndex + 1;
		}
	}
	return false;
}

void PrintDuplicates(const std::vector<int>& nums)
{
	std::bitset<32000> hashtable;
	for (int entry : nums)
	{
		if (hashtable[entry - 1])
		{
			std::cout << std::endl << entry;
		}
		hashtable[entry - 1] = true;
	}
}

void RankFromStream::Track(int x)
{
	RankFromStream::RankData** iter = &stream;
	for (; *iter; )
	{
		if (x > (*iter)->val)
		{
			iter = &(*iter)->right;
		}
		else
		{
			++(*iter)->rank;
			iter = &(*iter)->left;
		}
	}
	*iter = new RankFromStream::RankData();
	(*iter)->val = x;
}

int RankFromStream::GetRankOfNumber(int x)
{
	int rank = 0;
	RankFromStream::RankData* iter = stream;
	for (; iter; )
	{
		if (x == iter->val)
		{
			return rank + iter->rank;
		}
		else if (x > iter->val)
		{
			rank += iter->rank + 1;
			iter = iter->right;
		}
		else
		{			
			iter = iter->left;
		}
	}
	return -1;
}

int CalculateLargestIndex(int array[], int len, int indexA, int indexB, int indexC)
{
	int aVal = indexA < len ? array[indexA] : INT_MIN;
	int bVal = indexB < len ? array[indexB] : INT_MIN;
	int cVal = indexC < len ? array[indexC] : INT_MIN;

	int max = std::max(aVal, std::max(bVal, cVal));
	if (max == aVal)
	{
		return indexA;
	}
	else if (max == bVal)
	{
		return indexB;
	}
	return indexC;
}

void PeaksAndValleys(int array[], int len)
{
	for (int mid = 1; mid < len; mid += 2)
	{
		int largestIndex = CalculateLargestIndex(array, len, mid-1, mid, mid+1);
		if (largestIndex != mid)
		{
			int temp = array[mid];
			array[mid] = array[largestIndex];
			array[largestIndex] = temp;
		}
	}
}