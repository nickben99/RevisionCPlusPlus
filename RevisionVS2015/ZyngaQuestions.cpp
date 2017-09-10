#include "ZyngaQuestions.h"

#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <queue>

void GetAllChildren(std::string& root, const std::unordered_set<std::string>& dict, const std::function<void (const::std::string&)>& func)
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
				if (dict.end() != dict.find(root))
				{
					func(root);
				}				
			}
		}
		root[pos] = saved;
	}
}

bool FindNumChangesBetweenWordsBidirectionalBreadthFirstSearch(const std::string& from, const std::string& to, 
	const std::unordered_set<std::string>& dict, int& res)
{
	enum { fromSearch = 0, toSearch, maxSearch };
	std::queue<std::string> search[maxSearch];
	std::unordered_map<std::string, std::string> visited[maxSearch];

	search[fromSearch].push(from);
	visited[fromSearch].insert(std::make_pair(from, ""));

	search[toSearch].push(to);
	visited[toSearch].insert(std::make_pair(to, ""));

	int currentLayerSize[maxSearch] = { 1, 1 };
	int nextLayerSize[maxSearch] = { 0, 0 };

	int currentLayerCounter[maxSearch] = { 0, 0 };
	int layer[maxSearch] = { 0, 0 };

	while (!search[fromSearch].empty() && !search[toSearch].empty())
	{
		for (int i = 0; i < maxSearch; ++i)
		{
			std::string curr = search[i].front();
			search[i].pop();

			if (visited[(i + 1) % maxSearch].end() != visited[(i + 1) % maxSearch].find(curr)) {
				res = layer[fromSearch] + layer[toSearch];
				return true;
			}

			GetAllChildren(curr, dict, [&](const std::string& child)->void {
				if (visited[i].end() == visited[i].find(child)) {
					++nextLayerSize[i];
					visited[i].insert(std::make_pair(child, curr));
					search[i].push(child);
				}
			});

			if (++currentLayerCounter[i] >= currentLayerSize[i])
			{
				currentLayerSize[i] = nextLayerSize[i];
				nextLayerSize[i] = 0;
				++layer[i];
				currentLayerCounter[i] = 0;
			}
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

bool FindNumChangesBetweenWordsAStar(const std::string& from, const std::string& to, const std::unordered_set<std::string>& dict, int& numChanges)
{	
	unsigned int wordLength = (unsigned int)from.length();
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

		GetAllChildren(parent->word, dict, [&](const std::string& child)
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