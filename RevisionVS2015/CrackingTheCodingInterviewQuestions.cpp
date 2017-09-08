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

void CompressString(std::string& str)
{
	if (0 == str.length())
	{
		return;
	}

	int consecutiveCount = 0;
	char prevCharacter = '\0';
	for (unsigned int count = 0; count < str.length(); ++count)
	{
		if (str[count] != prevCharacter)
		{
			prevCharacter = str[count];
			consecutiveCount = 1;
		}
		else
		{
			++consecutiveCount;
			if (consecutiveCount >= 3)
			{
				break;
			}
		}
	}

	if (consecutiveCount < 3) // won't gain anything from the compression
	{
		return;
	}

	std::string compressed;
	consecutiveCount = 1;
	for (unsigned int count = 0; count < str.length(); ++count)
	{
		if (count + 1 >= str.length() || str[count] != str[count + 1])
		{
			compressed.append(1, str[count]);
			if (consecutiveCount > 1)
			{
				std::ostringstream oss;
				oss << consecutiveCount;
				compressed += oss.str();
			}			
			consecutiveCount = 1;
		}
		else
		{
			++consecutiveCount;
		}
	}
	str = compressed;
}

// chapter 4 trees and graphs -------------------------------------------------------------------

void IsBinarySearchTree(BinaryTreeNode* node, int min, int max, bool doDecrement, bool& result)
{
	if (node && result)
	{
		if (node->val <= min) // NOTE: if no duplicates, this would just be '<' check
		{
			result = false;
			return;
		}

		if (node->val > max)
		{
			result = false;
			return;
		}

		// NOTE: if no duplicates, we would never decrement max
		IsBinarySearchTree(node->right, node->val, doDecrement ? max - 1 : max, false, result);
		if (result)
		{
			IsBinarySearchTree(node->left, min, node->val, true, result);
		}
	}
}

bool IsBinarySearchTree(BinaryTreeNode* node)
{
	bool result = true;
	IsBinarySearchTree(node, INT_MAX, INT_MIN, false, result);
	return result;
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
		parent = parent->parent;
	}
	return parent;
}

bool SortDependancies(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes)
{
	return TopologicalSort(allInputNodes, nodeDependancies, outputNodes);
}

struct TopologicalSortNodeAlt
{
	TopologicalSortNodeAlt(char inChar)
		: character(inChar)
	{}

	char character;

	enum State
	{
		idle,
		processing,
		processed
	};
	State currentState = State::idle;
	std::vector<TopologicalSortNodeAlt*> outboundEdges;
};

bool SortDependanciesAltDepthFirstSearchInternal(TopologicalSortNodeAlt* node, std::vector<char>& outputNodes)
{
	if (!node || TopologicalSortNodeAlt::processing == node->currentState)
	{
		return false;
	}

	if (TopologicalSortNodeAlt::processed == node->currentState)
	{
		return true;
	}

	node->currentState = TopologicalSortNodeAlt::processing;

	for (auto child : node->outboundEdges)
	{
		if (!SortDependanciesAltDepthFirstSearchInternal(child, outputNodes))
		{
			return false;
		}
	}

	node->currentState = TopologicalSortNodeAlt::processed;
	outputNodes.insert(outputNodes.begin(), node->character);
	return true;
}

bool SortDependanciesAltDFS(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes)
{
	std::unordered_map<char, TopologicalSortNodeAlt*> graph;

	for (char inputNode : allInputNodes)
	{
		graph.insert(std::make_pair(inputNode, new TopologicalSortNodeAlt(inputNode)));
	}

	for (const std::pair<char, char>& link : nodeDependancies)
	{
		graph[link.first]->outboundEdges.push_back(graph[link.second]);
	}

	for (const std::pair<char, TopologicalSortNodeAlt*>& node : graph)
	{
		if (TopologicalSortNodeAlt::idle == node.second->currentState && !SortDependanciesAltDepthFirstSearchInternal(node.second, outputNodes))
		{
			break;
		}
	}

	for (auto node : graph)
	{
		delete node.second;
	}

	return allInputNodes.size() == outputNodes.size();
}

BinaryTreeNode* FindFirstCommonAnscesterInternal(BinaryTreeNode* root, int nodeOne, int nodeTwo, bool& foundOne, bool& foundTwo)
{
	if (root)
	{
		bool zeroFound = !foundOne && !foundTwo;
		if (root->left)
		{
			BinaryTreeNode* node = FindFirstCommonAnscesterInternal(root->left, nodeOne, nodeTwo, foundOne, foundTwo);
			if (node)
			{
				return node;
			}
		}

		bool oneFound = foundOne || foundTwo;

		if (root->right)
		{
			BinaryTreeNode* node = FindFirstCommonAnscesterInternal(root->right, nodeOne, nodeTwo, foundOne, foundTwo);
			if (node)
			{
				return node;
			}
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
	int shiftedDown = (number & 0xaaaaaaaa) >> 1;
	return shiftedUp | shiftedDown;
}

// NOTE: this code would draw the line from x1 to x2 INCLUSIVE (although the question was not clear about whether x2 is inclusive/ exclusive)
// NOTE: we assume the points are in the range of the array
void DrawLine(char screen[], int widthInBits, int x1Bit, int x2Bit, int y)
{
	if (0 == widthInBits || x1Bit > x2Bit || x1Bit < 0 || x1Bit >= widthInBits || x2Bit < 0 || x2Bit >= widthInBits)
	{
		return;
	}

	int startBit = y*widthInBits + x1Bit;
	int startByte = startBit / 8;
	int endBit = y*widthInBits + x2Bit;
	int endByte = endBit / 8;

	while (true)
	{
		int startBitOffset = startBit % 8;
		if (startByte == endByte)
		{
			int endBitOffset = endBit % 8;
			int numBits = (endBitOffset - startBitOffset) + 1; // NOTE: + 1 here to make sure the toBit is included  
			screen[startByte] |= (((1 << numBits) - 1) << startBitOffset);
			break;
		}
		else // different bytes
		{
			screen[startByte] |= (~0 << startBitOffset);
			++startByte;
			startBit = startByte * 8;
		}
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
	PrintAllStringPermutations(string);
}

std::vector<std::string> GeneratePermutationsInternal(const std::string& input, std::unordered_set<char>& used)
{
	std::vector<std::string> returnStrings;
	if (0 == input.size())
	{
		returnStrings.push_back("");
	}
	else if (1 == input.size())
	{
		if (used.end() == used.find(input[0])) // as this is the first characters, this if is not really required
		{
			char arr[] = "a";
			arr[0] = input[0];
			returnStrings.push_back(arr);
			used.insert(input[0]);
		}
	}
	else
	{
		std::vector<std::string> temp = GeneratePermutationsInternal(input.substr(1), used);
		if (used.end() == used.find(input[0]))
		{
			for (auto tempString : temp)
			{
				for (unsigned int pos = 0; pos <= tempString.size(); ++pos)
				{
					char arr[] = "a";
					arr[0] = input[0];
					std::string copy = tempString;
					copy.insert(pos, arr);
					returnStrings.push_back(copy);
				}
			}
			used.insert(input[0]);
		}
		else
		{
			returnStrings = temp;
		}
	}
	return returnStrings;
}

std::vector<std::string> GenerateAllPermutationsNoDups(const std::string& input)
{
	std::unordered_set<char> used;
	return GeneratePermutationsInternal(input, used);
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