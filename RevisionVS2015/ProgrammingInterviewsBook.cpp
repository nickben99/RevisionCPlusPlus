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
	*stackHead = nullptr;
}

void DeleteStackLinkedList( Element** stackHead )
{
	while ( *stackHead )
	{
		Element* pNext = (*stackHead)->next;
		delete *stackHead;
		*stackHead = pNext;
	}
}

bool PushStackLinkedList( Element** stackHead, void* data )
{
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

// NOTE: if removing one element SPECIFICALLY from the middle of the list (not head or end), you can copy the data from the next to the prev
// iterativly until you get to the final element, which you delete (this removes the need to iterate the list from the begining)
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
		Element* temp = iter->next;
		if (data == iter->data)
		{
			if (prev)
			{
				prev->next = temp;
			}
			else // no previous, so this must be the head
			{
				*head = temp;
			}
			////////////////// NOTE!!!: if just removing one element, handle the *end here, and return after the delete iter
			delete iter;
		}
		else
		{
			prev = iter;
		}
		iter = temp;
	}
	*end = prev;
}

bool InsertAfter_LinkedList(Element* after, void* data, Element** stackHead, Element** stackEnd)
{
	if (!stackHead || !stackEnd)
	{
		return false;
	}

	Element* newElem = new Element();
	if (!newElem)
	{
		return false;
	}
	newElem->data = data;

	if (nullptr == after) // could also check if (nullptr == *stackHead), but if the stack is empty, after must be null
	{
		newElem->next = *stackHead;
		*stackHead = newElem;
		if (nullptr == *stackEnd) // this would mean the list was previously empty
		{
			*stackEnd = *stackHead;
		}
		return true;
	}
	
	Element* iter = *stackHead;

	// IMPORTANT!!! the only reason for the while loop is to check that 'after' is in the linked list. if we assume it is in the 
	// linked list we do not need the while loop to find the element, as we already have it
	while (iter) 
	{
		if ( iter == after ) // only the porion inside this 'if' would be required if we assume 'after' is in the linked list
		{
			newElem->next = after->next;
			after->next = newElem;

			if (after == *stackEnd)
			{
				*stackEnd = after->next;
			}
			return true;
		}
		iter = iter->next;
	}
	delete newElem;
	return false;
}

bool RemoveHead_LinkedList(Element** stackHead)
{
	if (!stackHead || !*stackHead)
	{
		return false;
	}

	Element* temp = *stackHead;
	*stackHead = (*stackHead)->next;
	delete temp;
	return true;
}

bool GetNthToLastElement_LinkedList(Element** out, Element** stackHead, int N)
{
	if (!stackHead || !*stackHead)
	{
		return false;
	}
	Element* curr = *stackHead;
	for (int index = 0; index < N; ++index)
	{
		curr = curr->next;
		if (!curr)
		{
			return false;
		}
	}

	*out = *stackHead;
	while (curr->next)
	{
		curr = curr->next;
		*out = (*out)->next;
	}
	return true;
}

void Flatten_LinkedList(ElementFlatten** stackHead, ElementFlatten** stackEnd)
{
	if (!stackHead || !stackEnd || !*stackHead || !*stackEnd)
	{
		return;
	}

	ElementFlatten* curr = *stackHead;
	while (curr)
	{
		if (curr->child)
		{
			(*stackEnd)->next = curr->child;
			curr->child->prev = (*stackEnd);
			while ((*stackEnd)->next)
			{
				*stackEnd = (*stackEnd)->next;
			}
			// curr->child = NULL; // we DON'T do this so that we can Unflatten the linked list if required
		}
		curr = curr->next;
	}
}

// this is the method presented in the book, but it seems very bad, sections will be traversed multiple times
// see Unflatten_LinkedList1 for better implementation
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

// this is the method presented in the book, but it seems very bad, sections will be traversed multiple times
// see Unflatten_LinkedList1 for better implementation
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
void Unflatten_LinkedList1(ElementFlatten** head, ElementFlatten** end)
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
BinaryTreeNode* BinaryTreePreOrderSearch(BinaryTreeNode* root, int val)
{
	if (root)
	{
		if (root->val == val)
		{
			return root;
		}

		BinaryTreeNode* left = BinaryTreePreOrderSearch(root->left, val);
		if (left)
		{
			return left;
		}

		return BinaryTreePreOrderSearch(root->right, val);
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
			if (pNode->left && searched.end() == searched.find(pNode->left))
			{
				nodesToSearch.push(pNode->left);
				childrenSearched = false;
			}
			
			if (pNode->right && searched.end() == searched.find(pNode->right))
			{
				nodesToSearch.push(pNode->right);
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

	if (valOne <= root->val && valTwo <= root->val)
	{
		return BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(root->left, valOne, valTwo);
	}
	else if (valOne > root->val && valTwo > root->val)
	{
		return BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(root->right, valOne, valTwo);
	}
	return root;
}

BinaryTreeNode* BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicates(BinaryTreeNode* root, int valOne, int valTwo)
{
	while (root)
	{
		if (valOne <= root->val && valTwo <= root->val)
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
	const char* pIter = pString;
	while (*pIter)
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
		++pIter;
	}

	pIter = pString;
	while (*pIter)
	{
		if (amountUsed[*pIter] < 2)
		{
			return *pIter;
		}
		++pIter;
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

	const char* sourceCounter = str.c_str();
	int targetCounter = 0;
	while (*sourceCounter != '\0')
	{
		str[targetCounter] = *sourceCounter;		
		if (!toRemove[ *sourceCounter ])
		{
			++targetCounter;
		}
		++sourceCounter;
	}
	str.resize(targetCounter);
}

void ReverseStringInternal(char* pStringStart, char* pStringEnd); // prototype
void ReverseString(char* pString)
{
	char* pLastStringChar = pString + std::max<int>(0, strlen(pString) - 1);
	ReverseStringInternal(pString, pLastStringChar);
}

void ReverseStringInternal(char* pStringStart, char* pStringEnd)
{
	while (pStringEnd > pStringStart)
	{
		char temp = *pStringStart;
		*pStringStart = *pStringEnd;
		*pStringEnd = temp;

		--pStringEnd;
		++pStringStart;
	}
}

void ReverseWords(char* pString)
{
	int len = strlen(pString);
	ReverseStringInternal(pString, pString + (len-1));
	
	for (int i = 0; i < len; ++i)
	{
		if (pString[i] != ' ')
		{
			int startIndex = i;
			while (i < len && pString[i] != ' ')
			{
				++i;
			}
			ReverseStringInternal(pString + startIndex, pString + i-1);
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

	if (!wasPositive)
	{
		returnNumber = -returnNumber;
	}
	return returnNumber;
}

std::string IntToString(int val)
{
	bool wasLessThanZero = false;
	if ( val < 0 )
	{
		val *= -1;
		wasLessThanZero = true;
	}

	std::string numString; // if you want to use a char array, then below loop must be done twice, first time just to get char array length
	do
	{
		int figure = val%10;
		numString.push_back(char('0' + figure)); // NOTE: could do an insert(0, "0") here to avoid the string reverse at the bottom of this function
		val/=10;
	}while (0 != val);

	if (wasLessThanZero)
	{
		numString.push_back('-'); // NOTE: could do a insert(0, "0") here to avoid the string reverse at the bottom of this function
	}
	
	// reversing the string here. // NOTE: could've avoided this string reverse if insert(0, "0") was done previosuly in this function
	int start = 0, end = numString.length()-1;
	while (end > start)
	{
		char temp = numString[start];
		numString[start] = numString[end];
		numString[end] = temp;
		++start;
		--end;
	}
	return numString;
}

// chapter 7 recursion --------------------------------------------------------------------------------------------------

int binarySearchRecursive(char* arrayOfValues, int lowerIndex, int upperIndex, char targetValue)
{
	if (lowerIndex > upperIndex)
	{
		return -1;
	}
	if (arrayOfValues[lowerIndex] > arrayOfValues[upperIndex])
	{
		return -1;
	}
	if (lowerIndex == upperIndex && arrayOfValues[lowerIndex] != targetValue)
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
	while (lowerIndex <= upperIndex && arrayOfValues[lowerIndex] <= arrayOfValues[upperIndex])
	{
		if (lowerIndex == upperIndex && arrayOfValues[lowerIndex] != targetValue)
		{
			return -1;
		}

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

void PrintAllStringPermutations(const char* pOriginalString, int len, char* pCurrentString, int position, bool* pUsed)
{
	for (int index = 0; index < len; ++index)
	{
		if (true == pUsed[index])
		{
			continue;
		}
		pCurrentString[position] = pOriginalString[index];
		pUsed[index] = true; // if pOriginalString was none const, we could do without pUsed, and null out spots in pOriginalString here temporarilly
		if (position+1 < len)
		{
			PrintAllStringPermutations(pOriginalString, len, pCurrentString, position+1, pUsed);
		}
		else
		{
			std::cout << std::endl << pCurrentString;
		}
		pUsed[index] = false;
		// pCurrentString[position] = ' \0'; // NOTE: this is not required as all printed strings are the same length so all pCurrentString slots will always be occuppied
	}	
}

void PrintAllStringPermutations(const char* pString)
{
	int len = strlen(pString); // alternately without using api functions: const char* pIter = pString; while ('\0' != *pIter) { ++pIter;}; len = pIter-pString;
	bool* pUsed = new bool[len]; // could do without this if pString was none const (could just temporarilly null out chars which are being used)
	memset(pUsed, 0, sizeof(bool)*len); 
	char* pCurrentString = new char[len+1]; // NOTE: +1 to add '\0' t end of char array
	memset(pCurrentString, 0, len+1); 
	PrintAllStringPermutations(pString, len, pCurrentString, 0, pUsed);
}

void PrintAllStringCombinations(const char* pString) // NOTE: this algorithm will only work if strings are less than 32 characters long
{
	int len = strlen(pString);
	if (len >= 0)
	{
		unsigned int numCombos = 1 << len;
		for (unsigned int combo = 0; combo < numCombos; ++combo)
		{
			std::cout << std::endl << combo << ". ";
			for (int pos = 0; pos < len; ++pos)
			{
				if ((1 << pos) & combo)
				{
					std::cout << pString[pos];
				}
			}
		}
	}
}

void PrintAllStringCombinationsAltInternal(const char*, char*, int, int, int, int&);
void PrintAllStringCombinationsAlt(const char* pOriginalString) // NOTE: this algorithm will work regarldless of character length
{
	int len = strlen(pOriginalString);
	char* currentString = new char[len + 1];
	memset(currentString, 0, sizeof(char) * (len + 1));
	int count = 0;
	PrintAllStringCombinationsAltInternal(pOriginalString, currentString, 0, 0, len, count);
}

void PrintAllStringCombinationsAltInternal(const char* pOriginalString, char* currentString, int position, int insertionPoint, int length, int& count)
{
	currentString[insertionPoint] = pOriginalString[position];
	if (position + 1 < length)
	{		
		PrintAllStringCombinationsAltInternal(pOriginalString, currentString, position + 1, insertionPoint + 1, length, count);
		PrintAllStringCombinationsAltInternal(pOriginalString, currentString, position + 1, insertionPoint, length, count);
		currentString[insertionPoint] = '\0';
	}
	else
	{	
		currentString[insertionPoint + 1] = '\0';
		std::cout << std::endl << count++ << ". " << currentString;
		currentString[insertionPoint] = '\0';
		std::cout << std::endl << count++ << ". " << currentString;
	}
}

char getChar( int telephoneKey, int place )
{
	static const char character[10][3] = 
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

void GenerateTelephoneWords(const char* pNum, int numLen, int pos, char* pCurrString, int& count)
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
		GenerateTelephoneWords(pNum, numLen, pos+1, pCurrString, count);
	}
	else
	{
		const int kNumCharsPerButton = 3;
		for (int index = 0; index < kNumCharsPerButton; ++index)
		{
			pCurrString[pos] = getChar( character-'0', index );
			GenerateTelephoneWords(pNum, numLen, pos+1, pCurrString, count);
		}
	}
}

void GenerateTelephoneWords(const char* pNum)
{
	int len = strlen(pNum);
	char* pCurrString = new char[len+1];
	memset(pCurrString, 0, len+1);
	int count = 0;
	GenerateTelephoneWords(pNum, len, 0, pCurrString, count);
}

void GenerateTelephoneWordsNonRecurse(const char* pPhoneNum)
{
	int len = strlen(pPhoneNum);
	char* pCurrString = new char[len+1];
	memset(pCurrString, 0, sizeof(char)*(len+1));

	int pos = 0;
	for (pos = 0; pos < len; ++pos)
	{
		if (pPhoneNum[pos] == '-')
		{
			pCurrString[pos] = '-';
		}
		else
		{
			pCurrString[pos] = getChar(pPhoneNum[pos]-'0', 0);
		}
	}

	int count = 0;
	pos = len-1;
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
}

// chaper 11 other programming topics ----------------------------------------------------------------------------------

void setPixel(int xCoord, int yCoord)
{
	std::cout << std::endl << "xPos: " << xCoord << " yPos: " << yCoord;
}

void drawEighthOfCircle(int radius)
{
	const float kPI = 3.142f; // PI is half a circle
	const float kEighthOfCircleAngle = kPI*0.25f; // eighth of a circle is a quarter of half a circle
	const int kNumSteps = 20;

	for (int count = 0; count <= kNumSteps; ++count)
	{
		float angle = ((float)count/kNumSteps)*kEighthOfCircleAngle;
		int y = (int)(std::cos(angle)*radius); // cos is -1 to 1, this assumes radius is large (much higher than 1), else result after int casting will always be zero
		int x = (int)(std::sin(angle)*radius); // sine is -1 to 1, this assumes radius is large (much higher than 1), else result after int casting will always be zero
		setPixel(x, y);
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
	char* pPointer = (char*)&one; // get pointer to byte at lowest memory address
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

// doing this function for counting a char's bits set to 1, as doing this with an int would not compile as onesInInt 
// is too big, gives error: total size of array must not exceed 0x7fffffff bytes
int CountOnesInCharBig01Amortized(char input)
{
	static int onesInInt[UCHAR_MAX + 1] = { -1 };
	if (-1 == onesInInt[0]) // not been initialized
	{
		for (char count = CHAR_MIN; ; ++count)
		{
			onesInInt[count - CHAR_MIN] = CountOnesInInt(count); // the returned amount will never be greater than 8 for a char
			if (CHAR_MAX == count)
			{
				break;
			}
		}
	}
	return onesInInt[input - CHAR_MIN];
}