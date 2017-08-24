// Revision.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <queue>
#include "MyVector.h"
#include "STLTests.h"
#include "CMatrix.h"
#include "CVector.h"
#include "CMatrix.h"
#include "CQuaternion.h"
#include "ProgrammingInterviewsBook.h"
#include "ImportantAlgorithms.h"
#include "DavidByttowAlgorithms.h"
#include "CrackingTheCodingInterviewQuestions.h"
#include "CrackingTheCodingInterviewAlgorithms.h"
#include "CrackingTheCodingInterviewCPlusPlus.h"
#include "2KSports.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <list>
#include <unordered_map>
#include <functional>
#include <fstream> // for std::ifstream

class testt
{
	public:
		float x, y, z;

	float test() {
        return x;
    }
};

class basey
{
	public:
		//float r;
		
};

class CVect : public basey
{
	public:
		virtual void c(){};
		float x;
};

class Abstract
{
	public:
		//virtual void c() = 0;
		virtual ~Abstract() = 0;
		float r;
		
};

struct MyBasicClass
{
	int t;
	MyBasicClass()
	{
		t = 1;
	}

	MyBasicClass(int in)
		: t(in)
	{
	}

	MyBasicClass(const MyBasicClass& rhs)
	{
		t = rhs.t;
	}

	void crash()
	{
		t = 77;
	}

	~MyBasicClass()
	{
		t = 0;
	}
};

void STDVectorTest()
{
	std::vector<MyBasicClass> basics;

	MyBasicClass bas;
	basics.push_back(bas);
}

void MyVectorTestMyPtr()
{
	MyVectorImplementation1<MyBasicClass*> basics;

	MyBasicClass bas;
	basics.push_back(&bas);
}

void MyVectorTestMy()
{
	MyVectorImplementation1<MyBasicClass> basics;

	MyBasicClass bas;
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);
	basics.push_back(bas);

	MyVectorImplementation2<MyBasicClass> myVectorOfSimpleClass;
	myVectorOfSimpleClass.push_back(MyBasicClass(0));
	myVectorOfSimpleClass.push_back(MyBasicClass(1));
	myVectorOfSimpleClass.push_back(MyBasicClass(2));
	myVectorOfSimpleClass.push_back(MyBasicClass(3));
	myVectorOfSimpleClass.push_back(MyBasicClass(4));

	myVectorOfSimpleClass.remove(1);
	MyBasicClass bas5(5);
	myVectorOfSimpleClass.push_back(bas5);
}

void vectorTests()
{
	STDVectorTest();
	MyVectorTestMyPtr();
	MyVectorTestMy();
}

enum testenum
{
	eone,
	etwo,
	ethree,
	efour,
	efive,
	emax
};

struct arr
{
	unsigned int ii[3];
};

struct foo
{
    //char c;//, d;
    //short s;
    //char p;
	arr rr;
	char p, a;
    int i; 
	char b;
	int g;
	char c;
	MyBasicClass cccc;

	void deleteMe()
	{
		i = i + 8;
		cccc.crash();
		delete this;
		cccc.crash();
		i = i + 8;
	};
};

//void LinkedListFlattening()
//{
//	LinkedList list;
//	LinkedListNode* pfive = list.Add(5);
//	list.Add(33);
//	list.Add(17);
//	LinkedListNode* ptwo = list.Add(2);
//	list.Add(1);
//
//	LinkedListNode* pSix = pfive->CreateChild(6);
//	LinkedListNode* ptwentyfive = pSix->Add(25);
//	LinkedListNode* psecondsix = pSix->Add(6);
//
//	ptwentyfive->CreateChild(8);
//
//	psecondsix->CreateChild(9)->CreateChild(7);
//
//	ptwo->CreateChild(2)->Add(7);
//	ptwo->mpChild->CreateChild(12)->Add(5);
//	ptwo->mpChild->mpChild->CreateChild(21)->Add(3);
//
//	list.Flatten(&list.mpHead, &list.mpEnd, list.mpHead);
//	list.print();
//
//	// first order // 5, 33, 17, 2, 1, 2, 7, 12, 5, 21, 3, 6, 25, 6, 9, 7, 8
//	// in order //    6, 8, 25, 7, 9, 6, 5, 33, 17, 21, 3, 12, 5, 2, 7, 2, 1
//	// post order //  8, 7, 9, 6, 25, 6, 3, 21, 5, 12, 7, 2, 1, 2, 117, 33, 5
//}

//class AStringBase
//{
//};

class AString // : public AStringBase
{
public:
	char mChars[10];

//private:
	operator const char*()
	{
		return mChars;
	}
};

void CastingTest()
{
	AString aa;
	const char* pp = (const char*)aa;
	pp = pp;
}

class basescope
{
public:
	int a;
};
class subby : public basescope
{
};

void ScopeTest()
{
	subby b;
	b.a = 9;
}

void STLTests()
{
	STLVectorTests();
	STLListTests();
	STLMapTests();
	STLStackTests();
	STLQueueTests();
	STLBitSetTests();
	STLUnorderedSetTests();
	STLUnorderedMapTests();
}

void afunction(int **x)

{
    *x=new int;
    **x=12;
}

class Foo
{
public:
    Foo()  { 
		std::cout << "Foo Constructor\n"; }
    ~Foo()  { 
		std::cout << "Foo Destructor\n"; }
};

class Bar
{
public:
    Bar()  { 
		std::cout << "Bar Constructor\n"; }
    ~Bar()  { 
		std::cout << "Bar Destructor\n"; }
};

template<class T>
class Tin : public Bar
{
public:
    Tin()  { 
		std::cout << "Tin Constructor\n"; }
    ~Tin()  { 
		std::cout << "Tin Destructor\n";  }
    Foo mFoo;
};

//struct A {A(){std::cout << "A Constructor\n";}; ~A(){std::cout << "A Destructor\n"; }};
//struct B : A {~B(){std::cout << "B Destructor\n"; }};
//struct C : B {~C(){std::cout << "C Destructor\n"; }};

//void Func()
//{
//	std::cout << "C\n"; 
//	std::cout << gg << "\n";
//	std::cout << ll << "\n";
//	std::cout << "C\n";
//	std::cout << "C\n";
//	std::cout << "C\n";
//	std::cout << "C\n";
//	static int gg = 9;
//	int ll = 3;
//	static A a;
//	std::cout << "HH\n";
//	std::cout << "HH\n";
//	std::cout << "HH\n";
//	std::cout << "HH\n";
//}

//static Tin<int> a_tin;

class A
{
public:
	void print(){std::cout << "A\n";};
	~A()
	{
		std::cout << "1\n";
	}
};

class B : public A
{
public:
	void print(){std::cout << "B\n";};
	~B()
	{
		std::cout << "2\n";
	}
};

//void PrimeNumberTesting()
//{
//	for(int i = 0; i < 200; ++i)
//	{
//		if (IsPrime(i))
//		{
//			std::cout << std::endl << i;	
//		}
//	}
//}

void MathTesting()
{
	float oneInput[] = { 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 0, 1, 0, 2, 2 };
	CMatrix one(oneInput);
	float twoInput[] = { 6, 5, 8, 7, 5, 7, 8, 5, 6, 3, 4, 5, 9,	0, 3, 1 };
	CMatrix two(twoInput);

	CMatrix resultOneMultTwo = one * two;
	CMatrix resultTwoMultOne = two * one;

	std::cout << resultOneMultTwo.elements[0];
	std::cout << resultTwoMultOne.elements[0];
}

void PrintLinkedList(ElementFlatten* pStart)
{
	std::queue<ElementFlatten*> levels[2];
	int currentLevel = 0;
	levels[currentLevel].push(pStart);
	
	while (!levels[currentLevel].empty())
	{
		std::cout << std::endl;
		while (!levels[currentLevel].empty())
		{
			ElementFlatten* pCurr = levels[currentLevel].front();
			levels[currentLevel].pop();

			while (pCurr)
			{
				std::cout << pCurr->value;
				if (pCurr->next != 0)
				{
					std::cout << "-";
				}

				if (pCurr->child && pCurr->child->prev == 0)
				{
					levels[ (currentLevel+1)%2 ].push(pCurr->child);
				}
				pCurr = pCurr->next;
			}
			std::cout << "  ";
		}
		currentLevel = ++currentLevel%2;
	}
}

void CreateUnflatennedLinkedList(ElementFlatten*& pStart, ElementFlatten*& pEnd)
{
	pStart = new ElementFlatten(5);
	pStart->Add(33);
	pStart->Add(17);
	ElementFlatten* ptwo = pStart->Add(2);
	pEnd = pStart->Add(1);

	ElementFlatten* pSix = pStart->CreateChild(6);
	ElementFlatten* ptwentyfive = pSix->Add(25);
	ElementFlatten* psecondsix = pSix->Add(6);

	ptwentyfive->CreateChild(8);

	psecondsix->CreateChild(9)->CreateChild(7);

	ptwo->CreateChild(2)->Add(7);
	ptwo->child->CreateChild(12)->Add(5);
	ptwo->child->child->CreateChild(21)->Add(3);
}
//
//const int N = 100;
//int adjacency[N][N];
//int currentScores[N];
//int currentLongestPath;
//int count = 0;
//
//void FanOut(int* inCurrentScores, int inIndex, bool* inVisited, int inPathScore)
//{
//	count++;
//	if (inPathScore < inCurrentScores[inIndex])
//	{
//		inCurrentScores[inIndex] = inPathScore;		
//	}
//
//	bool newVisited[N];
//	for (int index = 0; index < N; ++index)
//	{
//		if (index == inIndex || inVisited[index])
//		{
//			newVisited[index] = true;
//		}
//		else
//		{
//			newVisited[index] = false;
//		}
//	}
//
//	for (int index = 0; index < N; ++index)
//	{		
//		int minIndex = inIndex < index ? inIndex : index;
//		int maxIndex = inIndex > index ? inIndex : index;
//
//		int moveVal = adjacency[minIndex][maxIndex];
//		if (!newVisited[index] && moveVal != -1)
//			FanOut(inCurrentScores, index, newVisited, inPathScore + moveVal);
//	}
//}
//
//struct PathNode
//{
//	int index;
//	int weight;
//};
//
//static const int kMaxElements = 100;
//
//struct MinHeap
//{	
//	int numElements;
//	PathNode elements[kMaxElements];
//};
//
//void InitOpenList(MinHeap& openList)
//{
//	openList.numElements = 0;
//	for (int index = 0; index < kMaxElements; ++index)
//	{
//		openList.elements[index].index = -1;
//		openList.elements[index].weight = -1;
//	}
//}
//
//void BubbleDown(MinHeap& openList, int index)
//{
//	if (index >= 0 && index < openList.numElements)
//	{
//		int childIndexLeft = (index*2)+1;
//		int childIndexRight = childIndexLeft + 1;
//
//		while (childIndexLeft < openList.numElements)
//		{
//			int smallestChild = childIndexRight;
//			if (childIndexRight >= openList.numElements)
//			{
//				smallestChild = childIndexLeft;
//			}
//			else if (openList.elements[childIndexLeft].weight < openList.elements[childIndexRight].weight)
//			{
//				smallestChild = childIndexLeft;
//			}
//
//			if (openList.elements[smallestChild].weight < openList.elements[index].weight)
//			{
//				PathNode temp = openList.elements[index];
//				openList.elements[index] = openList.elements[smallestChild];
//				openList.elements[smallestChild] = temp;
//			}
//			else
//			{
//				break;
//			}
//
//			index = smallestChild;			
//			childIndexLeft = (index*2)+1;
//			childIndexRight = childIndexLeft + 1;
//		}
//	}
//}
//
//void BubbleUp(MinHeap& openList, int index)
//{
//	if (index < openList.numElements)
//	{
//		int parentIndex = (index-1)/2;
//
//		while (index > 0 && openList.elements[index].weight < openList.elements[parentIndex].weight)
//		{
//			PathNode temp = openList.elements[index];
//			openList.elements[index] = openList.elements[parentIndex];
//			openList.elements[parentIndex] = temp;
//
//			index = parentIndex;
//			parentIndex = (index-1)/2;
//		}
//	}
//}
//
//void AddToOpenList(MinHeap& openList, PathNode& node)
//{
//	if (openList.numElements < kMaxElements)
//	{
//		openList.elements[openList.numElements++] = node;
//		BubbleUp(openList, openList.numElements-1);
//	}
//}
//
//int FindNode(MinHeap& openList, PathNode& node)
//{
//	for (int index = 0; index < openList.numElements; ++index)
//	{
//		if (openList.elements[index].index == node.index)
//		{
//			return index;
//		}
//	}
//	return -1;
//}
//
//void ChangeNodeWeight(MinHeap& openList, int index, int newWeight)
//{
//	if (index >= 0 && index < openList.numElements && newWeight != openList.elements[index].weight)
//	{
//		if (newWeight < openList.elements[index].weight) // bubble up
//		{
//			openList.elements[index].weight = newWeight;
//			BubbleUp(openList, index);
//		}
//		else // bubble down
//		{
//			openList.elements[index].weight = newWeight;
//			BubbleDown(openList, index);
//		}
//	}
//}
//
//void PopFromOpenList(MinHeap& openList, PathNode& outNode)
//{
//	if (openList.numElements > 0)
//	{
//		outNode = openList.elements[0];
//		openList.elements[0] = openList.elements[--openList.numElements];
//		BubbleDown(openList, 0);
//	}
//}
//
//struct ClosedList
//{
//	int numElements;
//	PathNode elements[kMaxElements];
//};
//
//void InitClosedList(ClosedList& closedList)
//{
//	closedList.numElements = 0;
//	for (int index = 0; index < kMaxElements; ++index)
//	{
//		closedList.elements[index].index = -1;
//		closedList.elements[index].weight = -1;
//	}
//}
//
//void AddToClosedList(ClosedList& closedList, PathNode& node)
//{
//	if (closedList.numElements < kMaxElements)
//	{
//		closedList.elements[closedList.numElements++] = node;
//	}
//}
//
//bool IsOnClosedList(ClosedList& closedList, PathNode& node)
//{
//	for (int index = 0; index < closedList.numElements; ++index)
//	{
//		if (closedList.elements[index].index == node.index)
//		{
//			return true;
//		}
//	}
//	return false;
//}
//
//void FindShortestPath()
//{
//	bool visited[N];
//	for (int row = 0; row < N; ++row)
//	{
//		for (int col = 0; col < N; ++col)
//		{
//			adjacency[row][col] = -2;
//			//adjacency[row][col] = 1;
//			if (col > row)
//			{
//				adjacency[row][col] = 1 + (rand() % 100);
//			}
//		}
//		currentScores[row] = INT_MAX;
//		visited[row] = false;
//	}
//	visited[0] = true;
//	currentScores[0] = 0;
//	count = 0;
//
//	//adjacency[0][1] = 50;
//	//adjacency[0][2] = 30;	adjacency[1][2] = 5;	
//	//adjacency[0][3] = 100;	adjacency[1][3] = 20;	adjacency[2][3] = 50;
//	//adjacency[0][4] = 10;	adjacency[1][4] = -1;	adjacency[2][4] = -1;	adjacency[3][4] = 10;
//
//	static bool isDjikstra = true;
//	if (isDjikstra)
//	{ // Djakstra
//		MinHeap openList;
//		InitOpenList(openList);
//		ClosedList closedList;
//		InitClosedList(closedList);
//
//		PathNode node;
//		node.index = 0;
//		node.weight = 0;
//		AddToClosedList(closedList, node);
//		for (int index = 1; index < N; ++index)
//		{		
//			if (adjacency[0][index] != -1)
//			{
//				PathNode node;
//				node.index = index;
//				node.weight = adjacency[0][index];
//				AddToOpenList(openList, node);
//			}
//		}
//
//		while (openList.numElements > 0)
//		{
//			PathNode lowestNode; 
//			PopFromOpenList(openList, lowestNode);
//			AddToClosedList(closedList, lowestNode);
//
//			for (int index = 0; index < N; ++index)
//			{		
//				int minIndex = lowestNode.index < index ? lowestNode.index : index;
//				int maxIndex = lowestNode.index > index ? lowestNode.index : index;
//
//				PathNode potentialNode;
//				potentialNode.index = index;				
//				if (IsOnClosedList(closedList, potentialNode))
//				{
//					continue;
//				}
//
//				int openIndex = FindNode(openList, potentialNode);
//
//				int moveVal = adjacency[minIndex][maxIndex];
//				if (moveVal >= 0)
//				{
//					if (openIndex != -1)
//					{
//						if ( openList.elements[openIndex].weight > (lowestNode.weight + moveVal) )
//						{
//							ChangeNodeWeight(openList, openIndex, lowestNode.weight + moveVal);
//						}
//					}
//					else
//					{
//						potentialNode.weight = (lowestNode.weight + moveVal);
//						AddToOpenList(openList, potentialNode);
//					}
//				}
//			}
//		}
//		
//		if (closedList.numElements == N)
//		{
//			int highest = -INT_MAX;
//			for (int index = 1; index < N; ++index)
//			{		
//				if (closedList.elements[index].weight > highest)
//				{
//					highest = closedList.elements[index].weight;
//				}
//			}
//			highest = highest;
//		}
//		else
//		{
//			// no solution
//		}
//	}
//	else
//	{
//		for (int index = 1; index < N; ++index)
//		{		
//			if (adjacency[0][index] != -1)
//				FanOut(currentScores, index, visited, adjacency[0][index]);
//		}
//
//		int highest = -INT_MAX;
//		for (int index = 0; index < N; ++index)
//		{
//			if (currentScores[index] > highest)
//			{
//				highest = currentScores[index]; 
//			}
//		}
//		highest = highest;
//	}
//}

void Print(Element* pCurr)
{
	for( ; pCurr; pCurr = pCurr->next)
	{
		int* p = (int*)pCurr->data;
		std::cout << *p;		
	}
}

extern void Unflatten_LinkedListBetter(ElementFlatten** head, ElementFlatten** end);

void ProgrammingInterviewsBook()
{
// chapter 4 - linked lists --------------------------------------------------------------------------------------------

	Element *head = NULL;
	CreateStackLinkedList( &head );	

	int ints[] = {0, 1, 2, 3, 4, 5};	
	PushStackLinkedList( &head, (void*)&ints[0] );
	PushStackLinkedList( &head, (void*)&ints[1] );
	PushStackLinkedList( &head, (void*)&ints[2] );
	PushStackLinkedList( &head, (void*)&ints[3] );
	PushStackLinkedList( &head, (void*)&ints[4] );
	PushStackLinkedList( &head, (void*)&ints[5] );

	std::cout << std::endl; Print(head);

	void* data = NULL;
	PopStackLinkedList( &head, &data );
	std::cout << std::endl;	Print(head);

	Element* end = head->next->next->next->next;
	RemoveAllMatchingData(&head, &end, head->next->data);
	std::cout << std::endl;	Print(head);
	InsertAfter_LinkedList(head, (void*)&ints[3], &head, &end);
	std::cout << std::endl;	Print(head);
	RemoveHead_LinkedList(NULL);
	RemoveHead_LinkedList(&head);
	std::cout << std::endl;	Print(head);
	Element* nthtolast = NULL;
	GetNthToLastElement_LinkedList(&nthtolast, &head, 2);
	DeleteStackLinkedList( &head );

	ElementFlatten *pStart, *pEnd;
	CreateUnflatennedLinkedList(pStart, pEnd);
	std::cout << std::endl << std::endl << "Original List";
	PrintLinkedList(pStart);
	Flatten_LinkedList(&pStart, &pEnd);
	std::cout << std::endl << std::endl << "Flatenned List";
	PrintLinkedList(pStart);
	Unflatten_LinkedList(&pStart, &pEnd);
	//Unflatten_LinkedListBetter(&pStart, &pEnd);
	std::cout << std::endl << std::endl << "Unflatenned List";
	PrintLinkedList(pStart);

	IsCyclic_LinkedList(head);

// chapter 5 - trees and graphs -------------------------------------------------------------------------------------------

	BinaryTreeNode* root = 0;
	BinaryTreePreOrderSearch(root, 0);
	BinaryTreePreOrderSearchIterative(root, 0);
	BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicatesRecurse(root, 2, 7);
	BinarySearchTreeFindLowestCommonAncesterInTreeNoDuplicates(root, 2, 7);

// chapter 6 arrays and strings ------------------------------------------------------------------------------------------

	std::cout << std::endl << "'" << FindFirstNonRepeatedCharacter("teeter") << "'";
	std::cout << std::endl << "'" << FindFirstNonRepeatedCharacter("teeterr") << "'";

	std::string temp;
	removeChars(temp, "");

	std::string toRemove("rinnteete");	
	removeChars(toRemove, "te");
	std::cout << std::endl << std::endl << "-" << toRemove;
	toRemove = "teeterinn";
	removeChars(toRemove, "te");
	std::cout << std::endl << "-" << toRemove;
	toRemove = "e";
	removeChars(toRemove, "e");
	std::cout << std::endl << "-" << toRemove;
	toRemove = "eb";
	removeChars(toRemove, "b");
	std::cout << std::endl << "-" << toRemove;
	
	char words[] = "here are some, words.";
	ReverseWords(words);
	std::cout << std::endl << std::endl << words;

	int val = StringToInt("-1233");
	std::cout << std::endl << std::endl << IntToString(val);

	val = StringToInt("1233");
	std::cout << std::endl << std::endl << IntToString(val);

// chapter 7 recursion --------------------------------------------------------------------------------------------------
	char array[] = {0, 1, 2, 3, 4, 5, 6, 7};
	std::cout << std::endl << binarySearchRecursive(array, 0, 6, 7);
	std::cout << std::endl << binarySearchRecursive(array, 0, 6, 2);
	std::cout << std::endl << binarySearchIterative(array, 0, 6, 7);
	std::cout << std::endl << binarySearchIterative(array, 0, 6, 2);
	std::cout << std::endl;
	PrintAllStringPermutations("abcd");
	std::cout << std::endl << "PrintAllStringCombinations(\"1234\")" << std::endl;
	PrintAllStringCombinations("1234");
	std::cout << std::endl << std::endl << "PrintAllStringCombinationsAlt(\"1234\")" << std::endl;
	PrintAllStringCombinationsAlt("1234");
	std::cout << std::endl << "PrintAllStringCombinations(\"1\")" << std::endl;
	PrintAllStringCombinations("1");
	std::cout << std::endl << "PrintAllStringCombinationsAlt(\"1\")" << std::endl;
	PrintAllStringCombinationsAlt("1");
	std::cout << std::endl << "GenerateTelephoneWords()";
	GenerateTelephoneWords("617-5");
	std::cout << std::endl << std::endl << "GenerateTelephoneWordsNonRecurse()";
	GenerateTelephoneWordsNonRecurse("617-5");

// chapter 11 other programming topics ---------------------------------------------------------------------------------
	std::cout << std::endl << std::endl;
	drawEighthOfCircle(100);
	RectangleOverlap(Rectangle(), Rectangle());
	IsMachineLittleEndian();
	std::cout << std::endl << std::endl << "CountOnesInInt(-13) " << CountOnesInInt<char>(-13); // need the cast to make the function link
	std::cout << std::endl << "CountOnesInCharBig01Amortized(-13) " << CountOnesInCharBig01Amortized(-13);
	std::cout << std::endl << "CountOnesInCharBig01Amortized(-1) " << CountOnesInCharBig01Amortized(-1);
}

void ImportantAlgorithms()
{
	// ------------------- linked list ---------------------------
	int ints[] = {0, 1, 2, 3, 4, 5};
	LinkedListElement* pHead = NULL;
	
	LinkedListAddToEnd( &pHead, (void*)&ints[0] );
	LinkedListAddToEnd( &pHead, (void*)&ints[1] );
	LinkedListAddToEnd( &pHead, (void*)&ints[2] );
	LinkedListAddToEnd( &pHead, (void*)&ints[3] );
	LinkedListAddToEnd( &pHead, (void*)&ints[4] );
	LinkedListAddToEnd( &pHead, (void*)&ints[5] );

	std::cout << std::endl;	
	LinkedListElement* pCurr = pHead;
	for( ; pCurr; pCurr = pCurr->next)
	{
		int* p = (int*)pCurr->data;
		std::cout << *p;		
	}
	LinkedListReverse( &pHead );
	std::cout << std::endl;	
	pCurr = pHead;
	for( ; pCurr; pCurr = pCurr->next)
	{
		int* p = (int*)pCurr->data;
		std::cout << *p;		
	}	

	DoubleLinkedListElement* pDoubleHead = NULL;
	DoubleLinkedListElement* pDoubleEnd = NULL;
	LinkedListAddToEnd(&pDoubleHead, &pDoubleEnd, (void*)&ints[4]);
	LinkedListAddToEnd(&pDoubleHead, &pDoubleEnd, (void*)&ints[5]);

	std::cout << std::endl;
	DoubleLinkedListElement* pDoubleCurr = pDoubleHead;
	for( ; pDoubleCurr; pDoubleCurr = pDoubleCurr->next)
	{
		int* p = (int*)pDoubleCurr->data; std::cout << *p;		
	}
	std::cout << std::endl;
	pDoubleCurr = pDoubleEnd;
	for( ; pDoubleCurr; pDoubleCurr = pDoubleCurr->prev)
	{
		int* p = (int*)pDoubleCurr->data; std::cout << *p;		
	}
	LinkedListStackPush(&pDoubleHead, &pDoubleEnd, (void*)&ints[3]);
	
	std::cout << std::endl;
	pDoubleCurr = pDoubleHead;
	for( ; pDoubleCurr; pDoubleCurr = pDoubleCurr->next)
	{
		int* p = (int*)pDoubleCurr->data; std::cout << *p;		
	}
	std::cout << std::endl;
	pDoubleCurr = pDoubleEnd;
	for( ; pDoubleCurr; pDoubleCurr = pDoubleCurr->prev)
	{
		int* p = (int*)pDoubleCurr->data; std::cout << *p;		
	}

	void* out = NULL;
	LinkedListStackPop(&pDoubleHead, &pDoubleEnd, out);
	
	std::cout << std::endl;
	pDoubleCurr = pDoubleHead;
	for( ; pDoubleCurr; pDoubleCurr = pDoubleCurr->next)
	{
		int* p = (int*)pDoubleCurr->data; std::cout << *p;		
	}
	std::cout << std::endl;
	pDoubleCurr = pDoubleEnd;
	for( ; pDoubleCurr; pDoubleCurr = pDoubleCurr->prev)
	{
		int* p = (int*)pDoubleCurr->data; std::cout << *p;		
	}

	// ---------------- sorting ------------------------------------------------------------------

	int deck[52];
	for (int count = 0; count < 52; ++count) { deck[count] = count; };
	Shuffle(deck, 52);

	// --------------- string functions --------------------------------------------------------

	char myString[] = "abcdefghi";
	ReverseStringRecursive(myString);
	std::cout << std::endl << "ReverseStringRecursive(myString) : " << myString;

	std::cout << std::endl << std::endl << "BinaryNumberToInt: " << BinaryNumberToUnsignedInt("1001");
	std::cout << std::endl << "BinaryNumberToInt: " << BinaryNumberToUnsignedInt("11011");
	std::cout << std::endl << "BinaryNumberToInt: " << BinaryNumberToUnsignedInt("1000");

	std::cout << std::endl;
	std::cout << std::endl << "SumBinaryNumbers: " << SumBinaryNumbers("1", "1000");
	std::cout << std::endl << "SumBinaryNumbers: " << BinaryStringToUnsignedInt(SumBinaryNumbers(UnsignedIntToBinaryString(1), UnsignedIntToBinaryString(8)).c_str());

	std::cout << std::endl;
	std::cout << std::endl << "SumBinaryNumbers: " << SumBinaryNumbers("1010", "11100");
	std::cout << std::endl << "SumBinaryNumbers: " << BinaryStringToUnsignedInt(SumBinaryNumbers(UnsignedIntToBinaryString(10), UnsignedIntToBinaryString(28)).c_str());

	std::cout << std::endl;
	std::cout << std::endl << "SumBinaryNumbers: " << SumBinaryNumbers("1111010", "1111000");
	std::cout << std::endl << "SumBinaryNumbers: " << BinaryStringToUnsignedInt(SumBinaryNumbers(UnsignedIntToBinaryString(122), UnsignedIntToBinaryString(120)).c_str());

	// ---------------tree functions--------------------------------------------------------------
	BinaryTreeNode* pRoot = NULL;
	BinarySearchTreeAddNoDuplicatesRecurse(&pRoot, 1);
	BinarySearchTreeAddNoDuplicatesRecurse(&pRoot, 0);
	BinarySearchTreeAddNoDuplicatesRecurse(&pRoot, 2);
	BinarySearchTreeAddNoDuplicatesRecurse(&pRoot, 3);

	BinarySearchTreeRemove(&pRoot, 2);
	BinarySearchTreeRemove(&pRoot, 1);

	BinaryTreeNode* maxDepth = new BinaryTreeNode();
	maxDepth->left = new BinaryTreeNode();
	maxDepth->left->left = new BinaryTreeNode();

	maxDepth->right = new BinaryTreeNode();
	maxDepth->right->right = new BinaryTreeNode();
	maxDepth->right->right->right = new BinaryTreeNode();
	maxDepth->right->right->right->right = new BinaryTreeNode();

	std::cout << std::endl << "BinaryTreeMaxDepth(maxDepth) : " << BinaryTreeMaxDepth(maxDepth);

	//--------------------- general -------------------

	std::cout << std::endl << std::endl << "Prime";
	std::vector<int> primes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107 };
	for (int prime : primes) {
		std::cout << std::endl << "IsPrime: " << prime << " " << (IsPrime(prime) ? "true" : "false");
	}

	std::cout << std::endl << std::endl << "Not Prime";
	std::vector<int> notPrimes = { 0, 1, 9, 15, 21, 25, 33, 49, 69, 81 };
	for (int prime : notPrimes) {
		std::cout << std::endl << "IsPrime: " << prime << " " << (IsPrime(prime) ? "true" : "false");
	}

	std::cout << std::endl << "FibonacciRecursive(0): " << FibonacciRecursive(0);
	std::cout << std::endl << "FibonacciRecursive(1): " << FibonacciRecursive(1);
	std::cout << std::endl << "FibonacciRecursive(2): " << FibonacciRecursive(2);
	std::cout << std::endl << "FibonacciRecursive(3): " << FibonacciRecursive(3);
	std::cout << std::endl << "FibonacciRecursive(4): " << FibonacciRecursive(4);
	std::cout << std::endl << "FibonacciRecursive(5): " << FibonacciRecursive(5);
	std::cout << std::endl << "FibonacciRecursive(6): " << FibonacciRecursive(6);

	std::cout << std::endl << std::endl << "FibonacciIterative(0): " << FibonacciIterative(0);
	std::cout << std::endl << "FibonacciIterative(1): " << FibonacciIterative(1);
	std::cout << std::endl << "FibonacciIterative(2): " << FibonacciIterative(2);
	std::cout << std::endl << "FibonacciIterative(3): " << FibonacciIterative(3);
	std::cout << std::endl << "FibonacciIterative(4): " << FibonacciIterative(4);
	std::cout << std::endl << "FibonacciIterative(5): " << FibonacciIterative(5);
	std::cout << std::endl << "FibonacciIterative(6): " << FibonacciIterative(6);

	std::cout << std::endl;
	int nums[] = {0, 1, 1, 2, 2, 2, 2};
	int numsLength = 7;
	RemoveDuplicatesFromSortedArray(nums, numsLength);

	int nums2[] = { 0, 1, 1, 2, 1, 2 };
	int numsLength2 = 6;
	RemoveDuplicatesFromSortedArray(nums2, numsLength2);

	{
		int numsNth[] = { 0, 1, 1, 2, 1, 2 };
		int numsLengthNth = 6;
		RemoveDuplicatesFromArrayPreserveNth(numsNth, numsLengthNth, 0);
		std::cout << std::endl << "RemoveDuplicatesFromArrayPreserveNth(numsNth, numsLengthNth, 0) : ";
		for (int i = 0; i < numsLengthNth; ++i) { std::cout << " " << numsNth[i]; }
	}

	{
		int numsNth[] = { 0, 1, 1, 2, 1, 2 };
		int numsLengthNth = 6;
		RemoveDuplicatesFromArrayPreserveNth(numsNth, numsLengthNth, 2);
		std::cout << std::endl << "RemoveDuplicatesFromArrayPreserveNth(numsNth, numsLengthNth, 2) : ";
		for (int i = 0; i < numsLengthNth; ++i) { std::cout << " " << numsNth[i]; }
	}

	int numsCE[] = { 0, 1, 1, 2, 2, 2, 2 };
	int numsLengthCE = 7;
	int nums2CE[] = { 0, 1, 1, 2, 1, 2 };
	int numsLength2CE = 6;
	RemoveCommonElementsFromArrays(numsCE, numsLengthCE, nums2CE, numsLength2CE);

	{
		int numsN[] = { 0, 1, 4, 5, 7, 8, 9 };
		int nums2N[] = { 5, 6, 7 };
		int NthSmallestElement = 0;
		bool result = GetNthSmallestElementFromUnionOfSortedNoDuplicatesArrays(NthSmallestElement, 5, numsN, sizeof(numsN)/sizeof(numsN[0]), nums2N, sizeof(nums2N) / sizeof(nums2N[0]));
		std::cout << std::endl << "GetNthElementFromUnionOfSortedNoDuplicatesArrays() : " << result << " : " << NthSmallestElement;
	}

	{
		int numsN[] = { 0, 1, 4, 4, 4, 8, 9 };
		int nums2N[] = { 4, 6, 7 };
		int NthSmallestElement = 0;
		bool result = GetNthSmallestElementFromUnionOfSortedArrays(NthSmallestElement, 3, numsN, sizeof(numsN) / sizeof(numsN[0]), nums2N, sizeof(nums2N) / sizeof(nums2N[0]));
		std::cout << std::endl << "GetNthElementFromUnionOfSortedArrays() : " << result << " : " << NthSmallestElement;
	}

	int numsCEFSE[] = { 0, 1, 3, 7, 7, 8, 9, 10 };
	int numsLengthCEFSE = 8;
	int nums2CEFSE[] = { 1, 6, 7, 8, 10 };
	int numsLength2CEFSE = 5;
	RemoveCommonElementsFromSortedArrays(numsCEFSE, numsLengthCEFSE, nums2CEFSE, numsLength2CEFSE);
	std::cout << std::endl << "Following RemoveCommonElementsFromSortedArrays() : { ";
	for (int i = 0; i < numsLengthCEFSE; ++i) { std::cout << " " << numsCEFSE[i]; }
	std::cout << "} { ";
	for (int i = 0; i < numsLength2CEFSE; ++i) { std::cout << " " << nums2CEFSE[i]; }
	std::cout << "}";

	int numbers[] = {1, 1, 3, 4, 5, 6};
	int numbersLength = 6;
	const char* stringNumbers[] = { "1", "0", "3", "4", "50", "6", "2", "67" };
	int stringNumbersLength = 8;
	RemoveCommonIntegers(numbers, stringNumbers, numbersLength, stringNumbersLength);

	std::unordered_set<std::string> dictionary = { "GEEKS", "FOR", "QUIZ", "SEE", "GO" };
	char boggle[] = {	'G','I','Z',
						'U','E','K',
						'Q','S','E' };
	std::unordered_set<std::string> found;
	boggle::Boggle(dictionary, boggle, 3, found);
	
	char matrix[] = {	0, 0, 0, 0, 1, 0, 1,
						0, 0, 1, 0, 0, 1, 1,
						0, 0, 0, 0, 0, 0, 1,
						1, 0, 0, 0, 0, 0, 1,
						0, 0, 0, 0, 0, 1, 1,
						0, 0, 1, 0, 0, 0, 1};
	std::cout << "FindLargestEncompassingRectangleOfZeros(); " << findLargestEncompassingRectangle::FindLargestEncompassingRectangleOfZeros(matrix, 6, 7);

	int minusOne = -1;
	std::cout << std::endl << "IntToBinaryString(minusOne) : (length: " << IntToBinaryString(minusOne).size() << ") : " << IntToBinaryString(minusOne);


	std::cout << std::endl << "HexStringToUnsignedInt(\"1a\") : " << HexStringToUnsignedInt("1a");
}

void CrackingTheCodingInterviewQuestions()
{
	// technical questions --------------------------------------------------------------

	// chapter 1, arrays and strings, p88
	std::string str = "jjaaaaffdeggyyyyyyuu";
	std::string prevString = str;
	CompressString(str);
	std::cout << std::endl << "CompressString(): " << prevString << " : " << str;

	// chapter 3 stacks and queues

	StackWithMinElement<20> linkedListStackNoMem;
	int zero = 0;
	int one = 1;
	int two = 2;
	int three = 3;
	linkedListStackNoMem.Push((void*)(&zero));
	linkedListStackNoMem.Push((void*)(&one));
	linkedListStackNoMem.Push((void*)(&two));
	linkedListStackNoMem.Push((void*)(&three));

	// chapter 4 trees and graphs -----------------------------------------------------------------------------------------

	{
		std::vector<char> allInputNodes = { 'a', 'b', 'c', 'd', 'e', 'f' };
		std::vector<std::pair<char, char>> dep;

		dep.push_back(std::make_pair('a', 'd'));
		dep.push_back(std::make_pair('f', 'b'));
		dep.push_back(std::make_pair('b', 'd'));
		dep.push_back(std::make_pair('f', 'a'));
		dep.push_back(std::make_pair('d', 'c'));

		std::vector<char> outputNodes;
		SortDependancies(allInputNodes, dep, outputNodes);
		std::cout << std::endl << "SortDependancies() : ";
		for (auto character : outputNodes) { std::cout << " " << character; }

		outputNodes.clear();

		SortDependanciesAltDFS(allInputNodes, dep, outputNodes);
		std::cout << std::endl << "SortDependanciesAltDFS() : ";
		for (auto character : outputNodes) { std::cout << " " << character; }
	}

	{
		// create a binary tree
		//                               50
		//                     33                       78
		//                2          1           67            77
		//           99     65   56     10    88    90      4      49
		BinaryTreeNode* root = new BinaryTreeNode();
		std::queue<BinaryTreeNode**> nodes;
		nodes.push(&root);
		int numbers[] = { 50, 33, 78, 2, 1, 67, 77, 99, 65, 56, 10, 88, 90, 4, 49 };
		for (int num : numbers)
		{
			BinaryTreeNode** node = nodes.front(); nodes.pop();
			if (!*node) { *node = new BinaryTreeNode(); }
			(*node)->val = num;
			nodes.push(&(*node)->left);
			nodes.push(&(*node)->right);
		}
		BinaryTreeNode* found = FindFirstCommonAnscester(root, 56, 88);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 56, 88) : " << (found ? IntToString(found->val) : "not found");		
		found = FindFirstCommonAnscester(root, 65, 10);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 65, 10) : " << (found ? IntToString(found->val) : "not found");
		found = FindFirstCommonAnscester(root, 100000, 10);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 100000, 10) : " << (found ? IntToString(found->val) : "not found");
		found = FindFirstCommonAnscester(root, 33, 49);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 33, 49) : " << (found ? IntToString(found->val) : "not found");
		found = FindFirstCommonAnscester(root, 99, 65);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 99, 65) : " << (found ? IntToString(found->val) : "not found");
		found = FindFirstCommonAnscester(root, 67, 68);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 67, 68) : " << (found ? IntToString(found->val) : "not found");
		found = FindFirstCommonAnscester(root, 67, 88);
		std::cout << std::endl << "FindFirstCommonAnscester(root, 67, 88) : " << (found ? IntToString(found->val) : "not found");

		std::queue<BinaryTreeNode*> deleteQueue;
		deleteQueue.push(root);
		while (!deleteQueue.empty())
		{
			BinaryTreeNode* deleteMe = deleteQueue.front();
			deleteQueue.pop();
			if (deleteMe->left)
			{
				deleteQueue.push(deleteMe->left);
			}
			if (deleteMe->right)
			{
				deleteQueue.push(deleteMe->right);
			}
			delete deleteMe;
		}
	}

	// chapter 5 bit manipulation ------------------------------------------

	float num = 0.5400f;
	std::cout << std::endl << "PrintBinary(num) : " << PrintBinary(num);

	int numToSwap = 0x66;
	std::cout << std::endl << "PairwiseSwap(0x66) : ";
	std::cout << std::endl << IntToBinaryString(numToSwap);
	std::cout << std::endl << IntToBinaryString(PairwiseSwap(numToSwap));

	char pixels[12]; // 4bytes * 3 bytes
	memset(pixels, 0, sizeof(char) * 12);
	std::cout << std::endl << "DrawLine(pixels, 4 * 8, 12, 17, 1) BEFORE : " << std::endl;

	std::function<void (void)> PrintFunc = [&]() 
	{
		for (int byte = 0; byte < 12; ++byte)
		{
			for (int bit = 0; bit < 8; ++bit)
			{
				std::cout << (((1 << bit) & pixels[byte]) ? "1" : "0");
			}
			std::cout << " ";

			if (0 == ((byte + 1) % 4))
			{
				std::cout << std::endl;
			}
		}
	};
	PrintFunc();
	DrawLine(pixels, 4 * 8, 12, 17, 1);
	std::cout << std::endl << "DrawLine(pixels, 4 * 8, 12, 17, 1) AFTER : " << std::endl;
	PrintFunc();

	// chapter 7

	CircularArray<int, 3> myArray;
	myArray.Add(1);
	myArray.Add(2);
	myArray.Add(3);
	myArray.Add(4);

	for (int val : myArray)
	{
		std::cout << val << " ";
	}

	std::cout << std::endl;
	for (CircularArray<int, 3>::Iterator<int> iter = myArray.begin(); iter != myArray.end(); ++iter)
	{
		int val = *iter;
		std::cout << val << " ";
	}

	// chapter 8 recursion and dynamic programming --------------------------------

	std::vector<int> input = { 1, 2, 3, 4 };
	std::vector<std::vector<int>> output;
	GenerateAllSubSets(input, output);

	std::cout << std::endl << "GenerateAllSubSets()";
	for (unsigned int set = 0; set < output.size(); ++set)
	{
		std::cout << std::endl << set << ". ";
		for (auto element : output[set])
		{
			std::cout << element << " ";
		}
	}

	std::cout << std::endl << std::endl << "RecursiveUnsignedIntMultiply(2, 4) : " << RecursiveUnsignedIntMultiply(2, 4);
	std::cout << std::endl << "RecursiveUnsignedIntMultiply(3, 4) : " << RecursiveUnsignedIntMultiply(3, 4);
	std::cout << std::endl << "RecursiveUnsignedIntMultiply(1, 4) : " << RecursiveUnsignedIntMultiply(1, 4);
	std::cout << std::endl << "RecursiveUnsignedIntMultiply(5, 6) : " << RecursiveUnsignedIntMultiply(5, 6);

	std::cout << std::endl << "PrintAllPermutations(\"abd\") : ";
	PrintAllPermutations("abd");

	std::cout << std::endl << "GenerateAllPermutationsNoDups(\"abbd\") : ";
	std::vector<std::string> perms = GenerateAllPermutationsNoDups("abbd");
	for (const std::string& permStr : perms) { std::cout << std::endl << permStr;}

	//std::cout << std::endl << "GenerateAllPermutationsNoDupsAlt(\"abbd\") : ";
	//perms = GenerateAllPermutationsNoDupsAlt("abbd");
	//for (const std::string& permStr : perms) { std::cout << std::endl << permStr; }

	std::cout << std::endl << "GenerateParens(1) : ";
	std::unordered_set<std::string> parens = GenerateParens(1);
	for (const std::string& parenStr : parens) { std::cout << std::endl << parenStr; }

	std::cout << std::endl << "GenerateParens(2) : ";
	parens = GenerateParens(2);
	for (const std::string& parenStr : parens) { std::cout << std::endl << parenStr;}

	std::cout << std::endl << "GenerateParens(3) : ";
	parens = GenerateParens(3);
	for (const std::string& parenStr : parens) { std::cout << std::endl << parenStr; }

	// chapter 10 sorting and searching ------------------------------------------------------

	vector_no_size<int> no_size;
	no_size.push_back(23);
	no_size.push_back(54);
	no_size.push_back(67);
	no_size.push_back(68);
	no_size.push_back(70);
	no_size.push_back(90);
	int foundIndex = 0;
	SortedSearchNoSize(no_size, 68, foundIndex);
	std::cout << std::endl << std::endl << "SortedSearchNoSize() : " << foundIndex;

	{
		int array[]{ 4, 4, 4, 4, 2, 2, 2, 2 };
		PeaksAndValleys(array, 8);
		for (int val : array) { std::cout << val << " "; }

		int array1[]{ 4, 5, 6, 7, 1, 2, 3, 8 };
		PeaksAndValleys(array1, 8);
		for (int val : array1) { std::cout << val << " "; }
	}

	// chapter 12 ------------------------------------------------------------------------
	SmartPointer<char> sPtr(new char(1));
	SmartPointer<char> sPtr2(sPtr);

	SmartPointer<char> sPtr3(new char(2));
	sPtr3 = sPtr2;

	SmartPointer<CCINode> sNodePtr(new CCINode());
	sNodePtr->left = nullptr;

	void* allocated = AlignedMalloc(20, 43);
	AlignedFree(allocated);
}

void CrackingTheCodingInterviewAlgorithms()
{
	//{
	//	// Trie
	//	Trie* myTrie = Trie::Create();
	//	if (myTrie)
	//	{
	//		const char* inputWords[] = { "ben", "bo", "deee" };

	//		for (int input = 0; input < sizeof(inputWords) / sizeof(inputWords[0]); ++input)
	//		{
	//			std::vector<std::string> outWords;
	//			int numSuggestions = Trie::FindWords(inputWords[input], myTrie, 3, outWords);
	//			std::cout << std::endl << "Num suggestions for " << inputWords[input] << " : " << numSuggestions;
	//			for (int suggestion = 0; suggestion < numSuggestions; ++suggestion)
	//			{
	//				std::cout << std::endl << suggestion << " : " << outWords[suggestion];
	//			}
	//		}
	//		delete myTrie;
	//	}
	//}
}

struct HashtableIdentifier
{
	int num = 0;
	HashtableIdentifier(int input)
		: num(input)
	{}

	bool operator==(const HashtableIdentifier& rhs) const
	{
		return num == rhs.num;
	}

	int ToHash() const
	{
		return num;
	}
};

void DavidByttowAlgorithms()
{
	bloom::BloomFilter<int, 30> myBloomFilter;
	int a = 9;
	myBloomFilter.Add(a);
	myBloomFilter.Exists(a);

	{
		// quicksort
		int arrayToBeSorted[] = { 6,10,13,5,8,3,2,25,4,11 };
		int arrayStartIndex = 0;
		int arrayEndIndex = (sizeof(arrayToBeSorted) / sizeof(arrayToBeSorted[0])) - 1;

		std::cout << std::endl << "======QuickSort Original=======" << std::endl;
		for (auto e : arrayToBeSorted)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		quicksort::QuickSort(arrayToBeSorted, arrayStartIndex, arrayEndIndex);

		std::cout << "======QuickSort Sorted=======" << std::endl;
		for (const int& e : arrayToBeSorted) // would also compile ====>> (int e : arrayToBeSorted)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	{
		// mergesort
		int arrayToBeSorted[] = { 6,10,13,5,8,3,2,25,4,11 };
		int arrayLength = (sizeof(arrayToBeSorted) / sizeof(arrayToBeSorted[0]));

		std::cout << std::endl << "======MergeSort Original=======" << std::endl;
		for (auto e : arrayToBeSorted)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		mergesort::MergeSort(arrayToBeSorted, arrayLength);

		std::cout << "======MergeSort Sorted=======" << std::endl;
		for (const int& e : arrayToBeSorted) // would also compile ====>> (int e : arrayToBeSorted)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	{
		// bucketsort
		int arrayToBeSorted[] = { 6,10,13,5,8,3,2,25,4,11 }; // NOTE: not a great bucket sort input
		int arrayLength = (sizeof(arrayToBeSorted) / sizeof(arrayToBeSorted[0]));

		std::cout << std::endl << "======BucketSort Original=======" << std::endl;
		for (auto e : arrayToBeSorted)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;

		bucketsort::BucketSort(arrayToBeSorted, arrayLength, 2, 25, 5);

		std::cout << "======BucketSort Sorted=======" << std::endl;
		for (const int& e : arrayToBeSorted) // would also compile ====>> (int e : arrayToBeSorted)
		{
			std::cout << e << " ";
		}
		std::cout << std::endl;
	}

	{
		// Hashtable
		Hashtable<HashtableIdentifier, float, 100> myHashtable;
		myHashtable.Add(HashtableIdentifier(45), 4.5f);
		myHashtable.Add(HashtableIdentifier(23), 2.3f);
		myHashtable.Add(HashtableIdentifier(23), 2.4f);
		myHashtable.Add(HashtableIdentifier(223), 2.5f);
		myHashtable.Add(HashtableIdentifier(89), 8.9f);
		myHashtable.Add(HashtableIdentifier(189), 18.9f);

		myHashtable.Remove(HashtableIdentifier(89));

		std::cout << std::endl << "Hashtable<HashtableIdentifier, float, 100>";
		std::cout << std::endl << (myHashtable.Find(45) ? *myHashtable.Find(45) : -1);
		std::cout << std::endl << (myHashtable.Find(23) ? *myHashtable.Find(23) : -1);
		
		std::cout << std::endl << (myHashtable.Find(223) ? *myHashtable.Find(223) : -1);
		std::cout << std::endl << (myHashtable.Find(89) ? *myHashtable.Find(89) : -1);
		std::cout << std::endl << (myHashtable.Find(189) ? *myHashtable.Find(189) : -1);
	}
}

void CPlusPlus11Tests()
{
	char s[] = "Hello World!";
	int Uppercase = 0; //modified by the lambda
	std::for_each(s, s + sizeof(s), [&Uppercase](char c) {
		if (isupper(c))
			Uppercase++;
	});
	std::cout << std::endl << Uppercase << " uppercase letters in: " << s << std::endl;
}

struct offsettest
{
	int one;
	bool two;
	char four;
	int three;
	
	int five;
};

int BinarySearchHigher(int* pArray, int lower, int upper, int target)
{
	if (lower > upper){
		return -1;
	}
	if (pArray[lower] > pArray[upper]){
		return -1;
	}
	if (target < pArray[lower]) {
		return lower;
	}
	if (lower+1 == upper && target >= pArray[lower] && target < pArray[upper]){
		return upper;
	}

	int centralIndex = lower + (upper-lower)/2;
	int centralVal = pArray[centralIndex];
	if (target >= centralVal)
	{
		return BinarySearchHigher(pArray, centralIndex+1, upper, target);
	}
	else
	{
		return BinarySearchHigher(pArray, lower, centralIndex-1, target);
	}
}

void VariousTests()
{
	testenum ee = testenum::eone;
	ee = testenum::efour;
	ee = (testenum)1000;

	Tin<char> b_tin;
	Foo a_foo;


	A a;
	B b;
	A* pA = new B();
	B* pB = new B();

	pA->print();

	delete pA;
	delete pB;

	float orig = 10.0f;
	float* pOrig = &orig;
	float** ppOrig = &pOrig;
	**ppOrig = 0.1f;

	foo food;
	std::cout << std::endl << " align foo: " << sizeof(foo);
	std::cout << std::endl << " align arr: " << sizeof(arr);
	std::cout << std::endl << offsetof(foo, p);
	std::cout << std::endl << "sizeof(bool): " << sizeof(bool);


	int ax = 0x4, bx = 0xB;
	printf("\n%X\n", ax + bx);

	if (ax != 0 || bx != 0)
	{
		printf("vagina");
	}

	if (ax | bx)
	{
		printf("vagina");
	}

	CVect rr;// = new CVect();
	rr.x = 7;
	CVect crap[4];
	*((int*)(&(rr))) = 0;
	CVect gg;
	rr = gg;
	std::cout << std::endl << *((int*)(&(rr))) << " " << (int)*(&(rr.x));

	unsigned int identityMatInt[16] =
	{
		1, 16, 256, 2 << 15,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	identityMatInt[12] = (int)3.0f;

	int f = 9;
	int g = f++ + 2;
	std::cout << std::endl << g;
	std::cout << std::endl << f;

	g = 6 / 3 * 4;
	g = 6 % 3 * 4;

	float identityMat[16] =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	identityMat[0] = 1.0f;
}

void CrackingTheCodingInterviewCPlusPlus()
{
	std::cout << std::endl << std::endl;
	PrintEndOfInputFile("input.txt", 3);
	std::cout << std::endl;
	PrintEndOfInputFile("input.txt", 7);
	std::cout << std::endl;
	PrintEndOfInputFile("input.txt", 9);

	CCINode* node = new CCINode();
	node->left = new CCINode();
	node->right = new CCINode();
	node->right->left = node;

	CCINode* theCopy = CopyCCINode(node);

	delete node->left;
	delete node->right;
	delete node;

	delete theCopy->left;
	delete theCopy->right;
	delete theCopy;
}

void TwoKSports() {
	LinkedListStackNoMemAlloc2KInterview<Element2KInterview, 5> linkedListStackNoMem;
	int zero = 0;
	int one = 1;
	int two = 2;
	int three = 3;
	linkedListStackNoMem.Push((void*)(&zero));
	linkedListStackNoMem.Push((void*)(&one));
	linkedListStackNoMem.Push((void*)(&two));
	linkedListStackNoMem.Push((void*)(&three));

	void* zeroPointer = NULL;
	void* onePointer = NULL;
	void* twoPointer = NULL;
	void* threePointer = NULL;
	linkedListStackNoMem.Pop(threePointer);
	linkedListStackNoMem.Pop(twoPointer);
	linkedListStackNoMem.Pop(onePointer);
	linkedListStackNoMem.Pop(zeroPointer);

	std::cout << std::endl << *(int*)zeroPointer << " " << *(int*)onePointer << " " << *(int*)twoPointer << " " << *(int*)threePointer;
}

//int _tmain(int argc, _TCHAR* argv[])
int main(int, char*)
{
	/* initialize random seed: */
	srand ((unsigned)time(NULL));

	STLTests();
	ProgrammingInterviewsBook();
	ImportantAlgorithms();	
	CrackingTheCodingInterviewQuestions();
	CrackingTheCodingInterviewAlgorithms();
	DavidByttowAlgorithms();
	CPlusPlus11Tests();
	VariousTests();
	MathTesting();
	vectorTests();
	CrackingTheCodingInterviewCPlusPlus();
	TwoKSports();

	std::cout << std::endl << "Press Enter To End..."<< std::endl;	

	getchar();

	return 0;
}