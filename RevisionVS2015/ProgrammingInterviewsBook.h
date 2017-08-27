#ifndef _ProgrammingInterviewsBook_h_
#define _ProgrammingInterviewsBook_h_

// Programmming Interviews Exposed (see book in my Kindle library)

#include <string>

// chapter 4 - linked lists --------------------------------------------------------------------------------------------

struct Element { Element* next; void* data; };

void CreateStackLinkedList( Element** stackHead ); // write the create function for a stack implemented using a linked list
void DeleteStackLinkedList( Element** stackHead ); // write the delete function for a stack implemented using a linked list
bool PushStackLinkedList( Element** stackHead, void* data ); // write the push function for a stack implemented using a linked list
bool PopStackLinkedList( Element** stackHead, void** data ); // write the pop function for a stack implemented using a linked list

void RemoveAllMatchingData(Element** head, Element** end, void* data); // remove all from the linked list which have the matching data
bool InsertAfter_LinkedList(Element* after, void* data, Element** stackHead, Element** stackEnd);
bool RemoveHead_LinkedList(Element** head);
bool GetNthToLastElement_LinkedList(Element** out, Element** head, int n);

// see chapter 4, figure 4-3, kindle location 1125 (approx)
struct ElementFlatten
{
	ElementFlatten(int val) : next(nullptr), prev(nullptr), child(nullptr), value(val) {}
	ElementFlatten* Add(int val) // NOTE: this function is just used to construct the data structure (not involved in questions below)
	{
		ElementFlatten* pCurr = this;		
		while (pCurr->next)
		{ 
			pCurr = pCurr->next; 
		}

		pCurr->next = new ElementFlatten(val); 
		pCurr->next->prev = pCurr;
		return pCurr->next;
	}

	ElementFlatten* CreateChild(int val) // NOTE: this function is just used to construct the data structure (not involved in questions below)
	{ 
		child = new ElementFlatten(val); 
		return child; 
	}

	ElementFlatten* next; 
	ElementFlatten* prev;
	ElementFlatten* child;
	int value;
};

void Flatten_LinkedList(ElementFlatten** head, ElementFlatten** end);
void Unflatten_LinkedList(ElementFlatten** head, ElementFlatten** end);

bool IsCyclic_LinkedList(Element* pHead);

// chapter 5 - trees and graphs -------------------------------------------------------------------------------------------

struct BinaryTreeNode 
{ 
	int val; BinaryTreeNode* left = nullptr; BinaryTreeNode* right = nullptr;
};

BinaryTreeNode* BinaryTreePreOrderSearchRecursive(BinaryTreeNode* root, int val); // do pre order search of nodes (not a binary search tree)
BinaryTreeNode* BinaryTreePreOrderSearchIterative(BinaryTreeNode* root, int val); // do pre order search of nodes (not a binary search tree)
BinaryTreeNode* BinaryTreeInOrderSearchIterative(BinaryTreeNode* root, int val); // do in order search of nodes (not a binary search tree)
BinaryTreeNode* BinaryTreePostOrderSearchIterative(BinaryTreeNode* root, int val); // do post order search of nodes (not a binary search tree)
BinaryTreeNode* BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(BinaryTreeNode* root, int valOne, int valTwo);
BinaryTreeNode* BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesIterative(BinaryTreeNode* root, int valOne, int valTwo);

// chapter 6 - arrays and strings -------------------------------------------------------------------------------------------

char FindFirstNonRepeatedCharacter(const char* pString);
void removeChars(std::string& str, const std::string& remove);
void ReverseString(char* pString);
void ReverseWords(char* pString);
int StringToInt(const char* string); // in reality in C++ std::stoi() would be used for this:http://www.cplusplus.com/reference/string/stoi/
std::string IntToString(int val);

// chapter 7 recursion --------------------------------------------------------------------------------------------------
int binarySearchRecursive(char* arrayOfValues, int lowerIndex, int upperIndex, char targetValue); // the chars in arrayOfValues are ordered smallest to largest
int binarySearchIterative(char* arrayOfValues, int lowerIndex, int upperIndex, char targetValue);
void PrintAllStringPermutations(const char* pString); // this may be badly named, we don't care about order, repeating is not allowed, have every different order
void PrintAllStringCombinations(const char* pString); // this may be badly named, we DO care about order, repeating is not allowed
void PrintAllStringCombinationsAlt(const char* pString); // NOTE: BETTER VERSION, solves same problem as above, but this version works for any number of characters
void GenerateTelephoneWords(const char* pPhoneNum); // generate all the different possible telephone words for the telephone number
void GenerateTelephoneWordsNonRecurse(const char* pPhoneNum);

// chaper 11 other programming topics ----------------------------------------------------------------------------------

void drawEighthOfCircle(int radius);
struct Rectangle {int xLeft, yTop, xRight, yBottom;};
bool RectangleOverlap(const Rectangle& rectOne, const Rectangle& rectTwo);
bool IsMachineLittleEndian();
template<class T> int CountOnesInInt(T input); // templatized on type of int, count the 1's in the binary representation
int CountOnesInCharBig01Amortized(char input);

#endif