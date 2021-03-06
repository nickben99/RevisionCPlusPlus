#include "ProgrammingInterviewsBook.h"
#include <stack>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <math.h>
#include <algorithm> // std::max

// chapter 4 - linked lists --------------------------------------------------------------------------------------------

void CreateStackLinkedList( Element** stackHead )
{
	if (stackHead) {
		*stackHead = nullptr;
	}
}

void DeleteStackLinkedList( Element** stackHead )
{
	if (stackHead)
	{
		while (*stackHead)
		{
			Element* pNext = (*stackHead)->next;
			delete *stackHead;
			*stackHead = pNext;
		}
	}
}

bool PushStackLinkedList( Element** stackHead, void* data )
{
	if (!stackHead) {
		return false;
	}

	Element* pNewElem = new Element();
	if (!pNewElem)
	{
		return false;
	}
	pNewElem->next = *stackHead;
	pNewElem->data = data;
	*stackHead = pNewElem;
	return true;
}

bool PopStackLinkedList( Element** stackHead, void** data )
{
	if (!stackHead || !*stackHead)
	{
		return false;
	}

	Element* pToDelete = *stackHead;
	*stackHead = (*stackHead)->next;

	*data = pToDelete->data;
	delete pToDelete;
	return true;
}

// NOTE: if removing one element SPECIFICALLY from the middle of the list (not head or end), and you pass in the Element* to delete, you can 
// copy the data from the next to the prev iterativly until you get to the final element, which you delete (this removes the need to iterate 
// the list from the begining)
void RemoveAllMatchingData(Element** head, Element** end, void* data)
{
	if (!head)
	{
		return;
	}

	Element* prev = nullptr;
	Element* iter = *head;
	while (iter)
	{
		Element* next = iter->next;
		if (data == iter->data)
		{
			if (prev)
			{
				prev->next = next;
			}
			else // no previous, so this must be the head
			{
				*head = next;
			}
			////////////////// NOTE!!!: if just removing one element, handle the *end here, and return after the delete iter
			delete iter;
		}
		else
		{
			prev = iter;
		}
		iter = next;
	}
	*end = prev;
}

bool InsertAfter_LinkedList(Element* after, void* data, Element** head, Element** end)
{
	if (!head || !end)
	{
		return false;
	}

	Element* newElem = new Element();
	if (!newElem)
	{
		return false;
	}
	newElem->data = data;

	if (nullptr == after) // this also covers the list empty case, as then after has to be null
	{
		newElem->next = *head;
		*head = newElem;
		if (nullptr == *end) // this would mean the list was previously empty
		{
			*end = *head;
		}
		return true;
	}
	
	Element* iter = *head;

	// IMPORTANT!!! the only reason for the while loop is to check that 'after' is in the linked list. if we assume it is in the 
	// linked list we do not need the while loop to find the element, as we already have it
	while (iter) 
	{
		if ( iter == after ) // only the portion inside this 'if' would be required if we assume 'after' is in the linked list
		{
			newElem->next = after->next;
			after->next = newElem;

			if (after == *end)
			{
				*end = after->next;
			}
			return true;
		}
		iter = iter->next;
	}
	delete newElem;
	return false;
}

bool RemoveHead_LinkedList(Element** head)
{
	if (!head || !*head)
	{
		return false;
	}

	Element* temp = *head;
	*head = (*head)->next;
	delete temp;
	return true;
}

void RemoveElementFromMiddle_LinkedList(Element* deleteMe)
{
	if (deleteMe && deleteMe->next) // must be true as we are deleting from the middle (not head or end)
	{
		Element* next = deleteMe->next;
		deleteMe->data = next->data;
		deleteMe->next = next->next;
		delete next;
	}
}

bool GetNthToLastElement_LinkedList(Element** out, Element** head, int n)
{
	if (!head || !*head)
	{
		return false;
	}
	Element* curr = *head;
	for (int index = 0; index < n; ++index)
	{
		curr = curr->next;
		if (!curr)
		{
			return false;
		}
	}

	*out = *head;
	while (curr->next)
	{
		curr = curr->next;
		*out = (*out)->next;
	}
	return true;
/* INFO!!! alternative implementation using just one loop (but total number iterations is unchanged)
	if (!head || !*head)
	{
		return false;
	}
	Element* curr = *head;
	*out = *head;
	int index = 0;
	while (curr)
	{
		if (curr->next) 
		{
			if (index >= n) 
			{
				*out = (*out)->next;
			} 
			else 
			{
				++index;
			}
		}
		curr = curr->next;
	}
	return index >= n;
*/
}

void Flatten_LinkedList(ElementFlatten** head, ElementFlatten** end)
{
	if (!head || !end || !*head || !*end)
	{
		return;
	}
	
	for (ElementFlatten* curr = *head; curr; curr = curr->next)
	{
		if (curr->child)
		{
			(*end)->next = curr->child;
			curr->child->prev = *end;
			while ((*end)->next)
			{
				*end = (*end)->next;
			}
			// curr->child = NULL; // we DON'T do this so that we can Unflatten the linked list if required
		}		
	}
}

// this is the method presented in the book, but it seems very bad, sections will be traversed multiple times
// see Unflatten_LinkedListBetter for better implementation
void Unflatten_LinkedListInternal(ElementFlatten* element)
{
	while (element)
	{
		if (element->child)
		{
			if (element->child->prev)
			{
				element->child->prev->next = nullptr;
				element->child->prev = nullptr;
			}
			Unflatten_LinkedListInternal(element->child);
		}
		element = element->next;
	}
}

// NOTE!!!!: this is the method presented in the book, but it seems very bad, sections will be traversed multiple times
// see Unflatten_LinkedListBetter for better implementation
void Unflatten_LinkedList(ElementFlatten** stackHead, ElementFlatten** stackEnd)
{
	if (!stackHead || !stackEnd || !*stackHead || !*stackEnd)
	{
		return;
	}

	Unflatten_LinkedListInternal(*stackHead);

	*stackEnd = *stackHead;
	while ((*stackEnd)->next)
	{
		*stackEnd = (*stackEnd)->next;
	}
}

// alt method - this is not the method presented in the book, but this seems to work as far as I can tell, and is far better
void Unflatten_LinkedListBetter(ElementFlatten** head, ElementFlatten** end)
{
	if (!head || !end || !*head || !*end)
	{
		return;
	}

    ElementFlatten* track = *end;
    while (track)
    {
        if (track->child)
        {
            *end = track->child->prev;
            track->child->prev = nullptr;
            (*end)->next = nullptr;
        }
        track = track->prev;
    }
}

// implementation in book looks to have a bug, 
// this implementation is similar to here: http://www.geeksforgeeks.org/write-a-c-function-to-detect-loop-in-a-linked-list/
bool IsCyclic_LinkedList(Element* head)
{
	Element* slow = head;
	Element* fast = head;

	while (fast && fast->next) 
	{
		slow = slow->next;          // 1 hop
		fast = fast->next->next;     // 2 hops 

		if (slow == fast)  // fast caught up to slow, so there is a loop
		{
			return true;
		}
	}
	return false;  // fast reached null, so the list terminates
}

// chapter 5 - trees and graphs -------------------------------------------------------------------------------------------

// pre order is check order: current node, left node, right node
// in order is check order: leftnode, current node, right node
// post order is check order: leftnode, right node, current node
BinaryTreeNode* BinaryTreePreOrderSearchRecursive(BinaryTreeNode* root, int val)
{
	if (root)
	{
		if (root->val == val)
		{
			return root;
		}

		BinaryTreeNode* left = BinaryTreePreOrderSearchRecursive(root->left, val);
		if (left)
		{
			return left;
		}

		return BinaryTreePreOrderSearchRecursive(root->right, val);
	}
	return nullptr;
}

// pre order is check order: current node, left node, right node
// in order is check order: leftnode, current node, right node
// post order is check order: leftnode, right node, current node
BinaryTreeNode* BinaryTreePreOrderSearchIterative(BinaryTreeNode* root, int val)
{
	if (root)
	{
		std::stack<BinaryTreeNode*> nodesToSearch;
		nodesToSearch.push(root);

		while (!nodesToSearch.empty())
		{
			BinaryTreeNode* pNode = nodesToSearch.top();
			nodesToSearch.pop();

			if (pNode->val == val)
			{
				return pNode;
			}

			if (pNode->right)
			{
				nodesToSearch.push(pNode->right);
			}

			if (pNode->left)
			{
				nodesToSearch.push(pNode->left);
			}
		}
	}
	return nullptr;
}

BinaryTreeNode* BinaryTreeInOrderSearchIterative(BinaryTreeNode* root, int val)
{
	if (root)
	{
		std::unordered_set<BinaryTreeNode*> searched;
		std::stack<BinaryTreeNode*> nodesToSearch;
		nodesToSearch.push(root);

		while (!nodesToSearch.empty())
		{
			BinaryTreeNode* pNode = nodesToSearch.top();
			if (pNode->left && searched.end() == searched.find(pNode->left))
			{
				nodesToSearch.push(pNode->left);
			}
			else
			{
				nodesToSearch.pop();
				searched.insert(pNode);
				if (root->val == val)
				{
					return pNode;
				}
				
				if (pNode->right)
				{
					nodesToSearch.push(pNode->right);
				}
			}
		}
	}
	return nullptr;
}

BinaryTreeNode* BinaryTreePostOrderSearchIterative(BinaryTreeNode* root, int val)
{
	if (root)
	{
		std::unordered_set<BinaryTreeNode*> searched;
		std::stack<BinaryTreeNode*> nodesToSearch;
		nodesToSearch.push(root);

		while (!nodesToSearch.empty())
		{
			BinaryTreeNode* pNode = nodesToSearch.top();

			bool childrenSearched = true;
			if (pNode->right && searched.end() == searched.find(pNode->right))
			{
				nodesToSearch.push(pNode->right);
				childrenSearched = false;
			}

			if (pNode->left && searched.end() == searched.find(pNode->left))
			{
				nodesToSearch.push(pNode->left);
				childrenSearched = false;
			}

			if (childrenSearched)
			{
				nodesToSearch.pop();
				searched.insert(pNode);
				if (root->val == val)
				{
					return pNode;
				}
			}
		}
	}
	return nullptr;
}

BinaryTreeNode* BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(BinaryTreeNode* root, int valOne, int valTwo)
{
	if (!root)
	{
		return nullptr;
	}

	if (valOne < root->val && valTwo < root->val)
	{
		return BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(root->left, valOne, valTwo);
	}
	else if (valOne > root->val && valTwo > root->val)
	{
		return BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(root->right, valOne, valTwo);
	}
	return root;
}

BinaryTreeNode* BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesIterative(BinaryTreeNode* root, int valOne, int valTwo)
{
	while (root)
	{
		if (valOne < root->val && valTwo < root->val)
		{
			root = root->left;
		}
		else if (valOne > root->val && valTwo > root->val)
		{
			root = root->right;
		}
		else
		{
			return root;
		}
	}
	return nullptr;
}

// chapter 6 - arrays and strings -------------------------------------------------------------------------------------------

char FindFirstNonRepeatedCharacter(const char* pString)
{
	std::unordered_map<char, int> amountUsed; // could also use int amountUsed[CHAR_MAX + 1]; memset(amountUsed, 0, sizeof(int)*(CHAR_MAX + 1));
	for (const char* pIter = pString; '\0' != *pIter; ++pIter)
	{	
		auto amountUsedIter = amountUsed.find(*pIter); // would not be required with int amountUsed[CHAR_MAX + 1];
		if (amountUsed.end() == amountUsedIter) // doesn't exist
		{
			amountUsed[*pIter] = 1;
		}
		else
		{
			++amountUsedIter->second;
		}
	}

	for (const char* pIter = pString; '\0' != *pIter; ++pIter)
	{
		if (amountUsed[*pIter] < 2)
		{
			return *pIter;
		}
	}
	return '\0';
}

void removeChars(std::string& str, const std::string& remove)
{
	bool toRemove[CHAR_MAX + 1];
	memset(toRemove, 0, sizeof(bool)*(CHAR_MAX + 1));
	for (const char* charPtr = remove.c_str(); *charPtr != '\0'; ++charPtr)
	{
		toRemove[*charPtr] = true;
	}

	int targetCounter = 0;
	for (int sourceCounter = 0; sourceCounter < str.length(); ++sourceCounter)
	{
		str[targetCounter] = str[sourceCounter];		
		if (!toRemove[str[sourceCounter]])
		{
			++targetCounter;
		}
	}
	str.resize(targetCounter);
}

void ReverseStringInternal(char* pStringStart, char* pStringEnd); // prototype
void ReverseString(char* pString)
{
	char* pLastStringChar = pString; // alternately:  pString+std::max<int>(0, (const int)strlen(pString) - 1);
	while (*pLastStringChar)
	{
		++pLastStringChar;
	}
	--pLastStringChar;

	ReverseStringInternal(pString, pLastStringChar);
}

void ReverseStringInternal(char* pStringStart, char* pStringEnd)
{
	for (; pStringEnd > pStringStart; --pStringEnd, ++pStringStart)
	{
		char temp = *pStringStart;
		*pStringStart = *pStringEnd;
		*pStringEnd = temp;		
	}
}

void ReverseWords(char* pString)
{
	int len = (int)strlen(pString);
	ReverseStringInternal(pString, pString + (len-1));
	
	char* wordStart = pString;
	for (int i = 0; i < len; ++i)
	{
		if (pString[i] == ' ' || i == len - 1)
		{
			char* wordEnd = pString[i] == ' ' ? pString + i - 1 : pString + i; // handles space character vs last character in string
			ReverseStringInternal(wordStart, wordEnd);
			wordStart = pString + i + 1;
		}	
	}
}

int StringToInt(const char* string)
{
	if (!string || '\0' == *string)
	{
		return 0;
	}

	bool wasPositive = true;
	if ('-' == *string)
	{
		wasPositive = false;
		++string;
	}

	int returnNumber = 0;
	for(; '\0' != *string; ++string)
	{
		returnNumber *= 10;
		if (*string >= '0' && *string <= '9')
		{
			returnNumber += *string - '0';
		}
		else
		{
			return 0;
		}		
	}
	return wasPositive ? returnNumber : -returnNumber;
}

std::string IntToString(int val)
{
	bool wasLessThanZero = val < 0;
	if ( val < 0 ) {
		val *= -1; // this is so that val%10 (in do loop below) always returns a positive number, a negative number would cause a bug when doing char('0' + figure)
	}

	std::string numString; // if you want to use a char array, then below loop must be done twice, first time just to get char array length
	do
	{
		int figure = val%10;
		// NOTE: could do an insert(numString.begin(), char('0' + figure)) here to avoid the string reverse at the bottom of this function (but MUCH less efficiant)
		numString.push_back(char('0' + figure)); // push_back() is O(1) amortized
		val/=10;
	}while (0 != val);

	if (wasLessThanZero)
	{	// NOTE: could do a insert(numString.begin(), "-") here to avoid the string reverse at the bottom of this function (but MUCH less efficient)
		numString.push_back('-'); 
	}
	
	// reversing the string here. NOTE: could've avoided this string reverse if insert(numString.begin(), char) was done previously in this 
	// function (but would make algorithm MUCH less efficient, as every insert() is O(n) requiring all current elements to be shifted down to make space)
	std::reverse(numString.begin(), numString.end());
	return numString;
}

// chapter 7 recursion --------------------------------------------------------------------------------------------------

int binarySearchRecursive(char* arrayOfValues, int lowerIndex, int upperIndex, char targetValue)
{
	if (lowerIndex > upperIndex)
	{
		return -1;
	}

	int centralIndex = lowerIndex + (upperIndex-lowerIndex)/2;
	char centralVal = arrayOfValues[centralIndex];
	if ( centralVal == targetValue )
	{
		return centralIndex;
	}
	if ( targetValue > centralVal )
	{
		return binarySearchRecursive(arrayOfValues, centralIndex + 1, upperIndex, targetValue);
	}
	// lower
	return binarySearchRecursive(arrayOfValues, lowerIndex, centralIndex - 1, targetValue);
}

int binarySearchIterative(char* arrayOfValues, int lowerIndex, int upperIndex, char targetValue)
{
	while (lowerIndex <= upperIndex)
	{
		int centralIndex = lowerIndex + (upperIndex - lowerIndex)/2;
		int centralVal = arrayOfValues[centralIndex];
		if ( centralVal == targetValue)
		{
			return centralIndex;
		}
		if (targetValue > centralVal )
		{
			lowerIndex = centralIndex + 1;
		}
		else // lower
		{
			upperIndex = centralIndex - 1;
		}
	}		
	return -1;		
}

void PrintAllStringPermutations(std::unordered_map<char, int>& used, size_t inputLen, size_t caret, char* curr)
{
	if (caret >= inputLen)
	{
		std::cout << std::endl << curr;
	}
	else
	{
		for (std::unordered_map<char, int>::iterator iter = used.begin(); iter != used.end(); ++iter)
		{
			if (iter->second > 0)
			{
				--iter->second;
				curr[caret] = iter->first;
				PrintAllStringPermutations(used, inputLen, caret + 1, curr);
				++iter->second;
			}
		}
	}
}

void PrintAllStringPermutations(const std::string& input)
{
	if (input.length() > 0)
	{
		// unordered_map is used in-case input has duplicate characters, to avoid duplicate printed strings
		// if we don't care about duplicate output, then an array of bools equal in length to input to mark used indecis would work
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
			PrintAllStringPermutations(used, input.length(), 0, curr);
			delete[] curr;
		}
	}
}

// NOTE: this algorithm will only work if strings are less than 8*sizeof(size_t) characters long. it is big O((2^len)*len)
void PrintAllStringCombinations(const char* pString)
{
	size_t len = pString ? (size_t)strlen(pString) : 0;
	if (len > 0 && len < 8*sizeof(size_t))
	{
		size_t numCombos = 1LL << len; // LL allows a 64 bit shift (long long is 64 bits, long is 32 bits)
		for (size_t combo = 0; combo < numCombos; ++combo)
		{
			std::cout << std::endl << combo << ". ";
			for (size_t pos = 0; pos < len; ++pos)
			{
				if ((1LL << pos) & combo)
				{
					std::cout << pString[pos];
				}
			}
		}
	}
}

void PrintAllStringCombinationsAltInternal(const char*, char*, int, int, int, int&);
void PrintAllStringCombinationsAlt(const char* pOriginalString) // NOTE: this algo is better, will work regarldless of character length, and is big O(2^len)
{
	int len = (int)strlen(pOriginalString);
	char* currentString = new char[len + 1];
	memset(currentString, '\0', sizeof(char) * (len + 1));
	int count = 0;
	PrintAllStringCombinationsAltInternal(pOriginalString, currentString, 0, 0, len, count);
	delete[] currentString;
}

void PrintAllStringCombinationsAltInternal(const char* pOriginalString, char* currentString, int position, int insertionPoint, int length, int& count)
{
	if (position >= length) {
		std::cout << std::endl << count++ << ". " << currentString;
	}
	else
	{
		PrintAllStringCombinationsAltInternal(pOriginalString, currentString, position + 1, insertionPoint, length, count);
		currentString[insertionPoint] = pOriginalString[position];
		PrintAllStringCombinationsAltInternal(pOriginalString, currentString, position + 1, insertionPoint + 1, length, count);
		currentString[insertionPoint] = '\0';		
	}
}

char getChar( int telephoneKey, int place )
{
	static const char character[][3] = // alt decleration: static const char character[10][3] = 
	{
		{'0', '0', '0'},
		{'1', '1', '1'},
		{'A', 'B', 'C'},
		{'D', 'E', 'F'},
		{'G', 'H', 'I'},
		{'J', 'K', 'L'},
		{'M', 'N', 'O'},
		{'P', 'R', 'S'},
		{'T', 'U', 'V'},
		{'W', 'X', 'Y'}
	};
	return character[telephoneKey][place];
}

void GenerateTelephoneWordsInternal(const char* pNum, int numLen, int pos, char* pCurrString, int& count)
{
	if (pos >= numLen)
	{
		std::cout << std::endl << count++ << ". " << pCurrString;
		return;
	}
	char character = pNum[pos];
	if ('0' == character || '1' == character || '-' == character)
	{
		pCurrString[pos] = character;
		GenerateTelephoneWordsInternal(pNum, numLen, pos+1, pCurrString, count);
	}
	else
	{
		const int kNumCharsPerButton = 3;
		for (int index = 0; index < kNumCharsPerButton; ++index)
		{
			pCurrString[pos] = getChar( character-'0', index );
			GenerateTelephoneWordsInternal(pNum, numLen, pos+1, pCurrString, count);
		}
	}
}

void GenerateTelephoneWords(const char* pNum)
{
	if (pNum) {
		int len = (int)strlen(pNum);
		char* pCurrString = new char[len + 1];
		if (pCurrString) {
			memset(pCurrString, 0, len + 1);
			int count = 0;
			GenerateTelephoneWordsInternal(pNum, len, 0, pCurrString, count);
			delete[] pCurrString;
		}
	}
}

void GenerateTelephoneWordsIterative(const char* pPhoneNum)
{
	int len = (int)strlen(pPhoneNum);
	char* pCurrString = new char[len+1];
	memset(pCurrString, 0, sizeof(char)*(len+1));

	for (int iter = 0; iter < len; ++iter)
	{
		pCurrString[iter] = ('-' != pPhoneNum[iter]) ? getChar(pPhoneNum[iter] - '0', 0) : '-';
	}

	int count = 0;
	int pos = len-1;
	while (pos > -1)
	{
		std::cout << std::endl << count++ << ". " << pCurrString;

		for (pos = len-1; pos > -1; --pos)
		{
			if ('-' != pCurrString[pos])
			{
				if (pCurrString[pos] == getChar(pPhoneNum[pos] - '0', 2)) // for 0 and 1 this will always be true
				{
					pCurrString[pos] = getChar(pPhoneNum[pos] - '0', 0);
				}
				else if (pCurrString[pos] == getChar(pPhoneNum[pos] - '0', 0))
				{
					pCurrString[pos] = getChar(pPhoneNum[pos] - '0', 1);
					break;
				}
				else if (pCurrString[pos] == getChar(pPhoneNum[pos] - '0', 1))
				{
					pCurrString[pos] = getChar(pPhoneNum[pos] - '0', 2);
					break;
				}
			}
		}
	}
	delete[] pCurrString;
}

// chaper 11 other programming topics ----------------------------------------------------------------------------------

void DrawLine(int xFromCoord, int yFromCoord, int xToCoord, int yToCoord)
{
	std::cout << std::endl << "xFromCoord: " << xFromCoord << ", yFromCoord: " << yFromCoord << ", xToCoord: " << xToCoord << ", yToCoord: " << yToCoord;
}

void drawEighthOfCircle(int radius)
{
	const float kPI = 3.142f; // PI is half a circle
	const float kEighthOfCircleAngle = kPI*0.25f; // eighth of a circle is a quarter of half a circle
	const int kNumSteps = 20;

	int prevX = 0;
	int prevY = radius;

	for (int count = 1; count <= kNumSteps; ++count)
	{
		float angle = ((float)count/kNumSteps)*kEighthOfCircleAngle;
		int x = (int)(std::sin(angle)*radius); // sine is -1 to 1, this assumes radius is large (much higher than 1), else result after int casting will always be zero
		int y = (int)(std::cos(angle)*radius); // cos is -1 to 1, this assumes radius is large (much higher than 1), else result after int casting will always be zero		
		DrawLine(prevX, prevY, x, y);
		prevX = x;
		prevY = y;
	}
}

bool RectangleOverlap(const Rectangle& rectOne, const Rectangle& rectTwo)
{
	return (rectTwo.xLeft <= rectOne.xRight &&
			rectTwo.xRight >= rectOne.xLeft && 
			rectTwo.yBottom <= rectOne.yTop && 
			rectTwo.yTop >= rectOne.yBottom);
}

bool IsMachineLittleEndian()
{
	unsigned int one = 1;
	unsigned char* pPointer = (unsigned char*)&one; // get pointer to byte at lowest memory address
	bool isLittle = *pPointer == 1; // if little endian, then the LSB (least significant byte) will be at the lowest
										// memory address. big endian will have LSB at highest mem address
	return isLittle;
}

// templatized for type of int
template<class T> int CountOnesInInt(T input)
{
	int numBits = sizeof(T)*8;

	int count = 0;
	for (int bit = 0; bit < numBits; ++bit) 
	{
		if ( (1 << bit) & input )
		{
			++count;
		}
	}
	return count;
}

// doing this function for counting a char's bits set to 1, as doing this with an int would not compile as onesCountCached 
// is too big, gives error: total size of array must not exceed 0x7fffffff bytes
// NOTE: Also see below: int CountOnesInIntBig01Amortized() as an alternative which will work for all types of ints
int CountOnesInCharBig01Amortized(char input)
{
	static char onesCountCached[UCHAR_MAX + 1] = { -1 };	// each element is a char, as 8 will be highest value
															// UCHAR_MAX + 1, as -128 to 127 gives 256 entries (UCHAR_MAX == 255) 
	if (-1 == onesCountCached[0]) // not been initialized
	{
		for (char count = CHAR_MIN; ; ++count)
		{
			onesCountCached[count - CHAR_MIN] = (char)CountOnesInInt(count); // the returned amount will never be greater than 8 for a char
			if (CHAR_MAX == count)
			{
				break;
			}
		}
	}
	return onesCountCached[input - CHAR_MIN];
}

// this version uses a std::unordered_map and caches values as they are requested, rather than all upfront
template<class T> int CountOnesInIntBig01Amortized(T input)
{
	// NOTE: each instantiated version of this function for each data type will have an individual version of this map (as is always the case for
	// static variables in templated functions, not just because the static variable itself also takes template arguments in this case)
	static std::unordered_map<T, int> onesCountCached; // int is probably too big, unsigned char would give us max 255, and a long long is only 64 bits
	auto iter = onesCountCached.find(input);
	if (onesCountCached.end() == iter) {
		int result = CountOnesInInt(input);
		iter = onesCountCached.insert(std::make_pair(input, result)).first; // result can't be higher than 8
	}
	return iter->second;
}