#include "ZyngaQuestions.h"

#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <queue>

bool IsInDictionary(const std::string&) // not implemented
{
	return true;
}

void GetAllChildren(std::string& root, const std::function<void (const::std::string&)>& func)
{
	const int NumAlphabetLetters = 26;
	char alphabetLetters[] = "abcdefghijklmnopqrstuvwxyz";
	for (unsigned int pos = 0; pos < root.size(); ++pos)
	{
		char saved = root[pos];
		for (int letter = 0; letter < NumAlphabetLetters; ++letter)
		{
			if (alphabetLetters[letter] != saved)
			{
				root[pos] = alphabetLetters[letter];
				if (IsInDictionary(root))
				{
					func(root);
				}				
			}
		}
		root[pos] = saved;
	}
}

bool FindNumChangesBetweenWordsBreadthFirstSearch(const std::string& from, const std::string& to, int& result)
{
	std::unordered_set<std::string> alreadyAdded;
	std::queue<std::string> theQueue;

	theQueue.push(from);
	alreadyAdded.insert(from);

	int currentLayerSize = 1;
	int nextLayerSize = 0;

	int currentLayerCounter = 0;
	int layer = 0;

	while (!theQueue.empty())
	{
		std::string front = theQueue.front();
		theQueue.pop();

		if (front == to)
		{
			result = layer;
			return true;
		}

		GetAllChildren(front, [&](const std::string& child)
		{
			if (alreadyAdded.end() == alreadyAdded.find(child))
			{
				++nextLayerSize;
				theQueue.push(child);
				alreadyAdded.insert(child);
			}
		});

		if (++currentLayerCounter >= currentLayerSize)
		{
			currentLayerSize = nextLayerSize;
			nextLayerSize = 0;
			++layer;
			currentLayerCounter = 0;
		}
	}
	return false;
}

//-------------FindNumChangesBetweenWordsAStar()-------------------------------------------------------------------------------------------------------------------

struct Node
{
	int steps = 0;
	int heuristic = 0;

	int TotalCost()
	{
		return steps + heuristic;
	}

	std::string word;
	int openListIndex = -1;
};

struct MinHeap
{
	std::unordered_map<std::string, Node*> nodes;
	Node** heap = nullptr;

	void Add(int, Node*) {};
	bool IsEmpty() { return true; }
	Node* PopLowestTotalCost() { return nullptr; }
	Node* Contains(const std::string& str) { return nodes[str]; } // <<<< in reality, do nodes.find() to avoid crash
	void ReSort(int, int) {};
};

// hamming distance calulates how many differences there are between two strings of equal length
// see https://en.wikipedia.org/wiki/Hamming_distance
int CalculateHammingDistanceHeuristic(const char* from, const char* to, int length)
{
	int numChangesRequired = 0;
	for (int pos = 0; pos < length; ++pos)
	{
		if (from[pos] != to[pos])
		{
			++numChangesRequired;
		}
	}
	return numChangesRequired;
}

bool FindNumChangesBetweenWordsAStar(const std::string& from, const std::string& to, int& numChanges)
{	
	unsigned int wordLength = from.length();
	if (wordLength != to.length())
	{
		return false; // words must be the same length
	}

	MinHeap openList;
	std::unordered_set<std::string> closedList;

	Node* startNode = new Node();
	startNode->word = from;
	startNode->heuristic = CalculateHammingDistanceHeuristic(from.c_str(), to.c_str(), wordLength);

	openList.Add(startNode->TotalCost(), startNode);

	while (!openList.IsEmpty())
	{
		Node* parent = openList.PopLowestTotalCost();
		closedList.insert(parent->word);

		if (parent->word == to)
		{
			numChanges = parent->steps;
			return true;
		}

		GetAllChildren(parent->word, [&](const std::string& child)
		{
			if (closedList.end() == closedList.find(child))
			{
				int newSteps = parent->steps + 1;
				Node* openListNode = openList.Contains(child);
				if (openListNode)
				{
					if (newSteps < openListNode->steps)
					{
						openListNode->steps = newSteps;
						openList.ReSort(openListNode->TotalCost(), openListNode->openListIndex);
					}
				}
				else
				{
					Node* newNode = new Node();
					newNode->word = from;
					openListNode->steps = newSteps;
					newNode->heuristic = CalculateHammingDistanceHeuristic(child.c_str(), to.c_str(), wordLength);
					openList.Add(startNode->TotalCost(), newNode);
				}
			}
		});
		delete parent;
	}
	return false;
}