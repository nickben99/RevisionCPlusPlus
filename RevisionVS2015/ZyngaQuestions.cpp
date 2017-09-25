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
	std::unordered_map<std::string, int> visited[maxSearch];

	search[fromSearch].push(from);
	visited[fromSearch].insert(std::make_pair(from, 0));

	search[toSearch].push(to);
	visited[toSearch].insert(std::make_pair(to, 0));

	while (!search[fromSearch].empty() && !search[toSearch].empty())
	{
		for (int i = 0; i < maxSearch; ++i)
		{
			std::string curr = search[i].front();
			search[i].pop();

			auto foundInOther = visited[(i + 1) % maxSearch].find(curr);
			if (visited[(i + 1) % maxSearch].end() != foundInOther) {
				res = visited[i][curr] + foundInOther->second;
				return true;
			}

			GetAllChildren(curr, dict, [&](const std::string& child)->void {
				if (visited[i].end() == visited[i].find(child)) {
					visited[i].insert(std::make_pair(child, visited[i][curr] + 1));
					search[i].push(child);
				}
			});
		}
	}
	return false;
}

//-------------FindNumChangesBetweenWordsAStar()-------------------------------------------------------------------------------------------------------------------

struct Node
{
	Node(const std::string& inWord, int inSteps, int inHeuristic)
		: word(inWord)
		, steps(inSteps)
		, heuristic(inHeuristic)
	{}

	int steps = 0;
	int heuristic = 0;

	int TotalCost()
	{
		return steps + heuristic;
	}

	std::string word;
};

struct MinHeap
{
	Node** heap = nullptr;

	void Add(int, Node*) {};
	bool IsEmpty() { return true; }
	Node* PopLowestTotalCost() { return nullptr; }
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
	std::unordered_map<std::string, Node*> nodes; // this acts like a closed list, it stops nodes being added to the open list more than once

	Node* startNode = new Node(from, 0, CalculateHammingDistanceHeuristic(from.c_str(), to.c_str(), wordLength));
	openList.Add(startNode->TotalCost(), startNode);
	nodes[from] = startNode;

	bool found = false;
	while (!openList.IsEmpty())
	{
		Node* lowest = openList.PopLowestTotalCost();
		if (lowest->word == to)
		{
			numChanges = lowest->steps;
			found = true;
			break;
		}

		GetAllChildren(lowest->word, dict, [&](const std::string& child) {
			auto iter = nodes.find(child);
			// it has never been added to open list (no need to look for quicker paths to nodes already on the open list, as each edge has equal cost of 1)
			if (nodes.end() == iter) 
			{
				Node* newNode = new Node(from, lowest->steps + 1, CalculateHammingDistanceHeuristic(child.c_str(), to.c_str(), wordLength));
				openList.Add(newNode->TotalCost(), newNode);
				nodes[child] = newNode;
			}
		});
	}
	for (auto i : nodes) { delete i.second; }
	return found;
}