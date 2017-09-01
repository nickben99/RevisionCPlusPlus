#include "CrackingTheCodingInterviewAlgorithms.h"
#include <queue>
#include <fstream>

// trie -----------------------------------------------------

Trie::Trie(const std::string& prefixInput)
	: prefix(prefixInput)
{

}

Trie::~Trie()
{
	for (std::pair<const char, Trie*> child : children)
	{
		delete child.second;
	}
}

int Trie::FindWords(const char* prefix, Trie* root, int numRequired, std::vector<std::string>& outWords)
{
	Trie* node = FindNode(prefix, root);
	int outWordsSize = 0;
	if (node)
	{
		std::queue<Trie*> breadthFirstSearchQueue;		
		breadthFirstSearchQueue.push(node);

		while (!breadthFirstSearchQueue.empty())
		{
			Trie* trie = breadthFirstSearchQueue.front();
			breadthFirstSearchQueue.pop();

			if (trie->isInDictionary)
			{
				outWords.push_back(trie->prefix);
				if (++outWordsSize >= numRequired)
				{
					return outWordsSize;
				}
			}

			for (std::pair<const char, Trie*> child : trie->children)
			{
				breadthFirstSearchQueue.push(child.second);
			}
		}
	}
	return outWordsSize;
}

Trie* Trie::Create()
{
	std::ifstream ifs("englishDictionary.txt", std::ifstream::in);

	Trie* myTrie = new Trie("");

	std::string word;
	while (ifs.good())
	{
		ifs >> word;
		AddPrefixToTrie(word.c_str(), myTrie);
	}

	ifs.close();

	return myTrie;
}

Trie* Trie::FindNode(const char* prefix, Trie* root)
{
	if (!root)
	{
		return nullptr;
	}

	for (; '\0' != *prefix; ++prefix)
	{
		auto iter = root->children.find(*prefix);
		if (root->children.end() != iter) // it's in there
		{
			root = iter->second;
		}
		else
		{
			break; // word prefix does not exist
		}
	}
	return root;
}

void Trie::AddPrefixToTrie(const char* prefix, Trie* root)
{
	if (!root)
	{
		return;
	}

	for (; '\0' != *prefix; ++prefix)
	{
		auto iter = root->children.find(*prefix);
		if (root->children.end() != iter) // it's in there already
		{
			root = iter->second;
		}
		else
		{
			Trie* newNode = new Trie(root->prefix + *prefix);
			root->children.insert(std::make_pair(*prefix, newNode));
			root = newNode;
		}
	}
	root->isInDictionary = true;
}

// topological sort --------------------------------------------------------------------------------
struct TopologicalSortNode
{
	TopologicalSortNode(char inChar)
		: character(inChar)
	{}

	char character;
	int numInboundEdges = 0;
	std::vector<TopologicalSortNode*> outboundEdges;
};

bool TopologicalSort(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes)
{
	std::unordered_map<char, TopologicalSortNode*> graph;

	for (auto inputNode : allInputNodes)
	{
		graph.insert(std::make_pair(inputNode, new TopologicalSortNode(inputNode)));
	}

	for (auto link : nodeDependancies)
	{
		++graph[link.second]->numInboundEdges;
		graph[link.first]->outboundEdges.push_back(graph[link.second]);
	}

	std::queue<TopologicalSortNode*> processNext;
	for (auto node : graph)
	{
		if (0 == node.second->numInboundEdges)
		{
			processNext.push(node.second);
		}
	}

	while (!processNext.empty())
	{
		TopologicalSortNode* next = processNext.front();
		processNext.pop();

		for (auto node : next->outboundEdges)
		{
			--node->numInboundEdges;
			if (0 == node->numInboundEdges)
			{
				processNext.push(node);
			}
		}
		outputNodes.push_back(next->character);
	}

	for (auto node : graph)
	{
		delete node.second;
	}

	return allInputNodes.size() == outputNodes.size();
}