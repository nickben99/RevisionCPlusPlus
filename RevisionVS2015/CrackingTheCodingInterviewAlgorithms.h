#ifndef _CrackingTheCodingInterviewAlgorithms_h_
#define _CrackingTheCodingInterviewAlgorithms_h_

#include <string>
#include <unordered_map>

// trie https://en.wikipedia.org/wiki/Trie
// https://www.topcoder.com/community/data-science/data-science-tutorials/using-tries/
class Trie
{
public:
	static Trie* Create();

	Trie(const std::string& prefixInput);
	~Trie();
	static int FindWords(const char* prefix, Trie* root, int numRequired, std::vector<std::string>& outWords); // find words with specified prefix

private:
	static void AddPrefixToTrie(const char* prefix, Trie* root);
	static Trie* FindNode(const char* prefix, Trie* root);

private:
	std::unordered_map<char, Trie*> children;
	bool isInDictionary = false;
	std::string prefix;
};

// nodeDependancies->right depends on nodeDependancies->left
bool TopologicalSort(const std::vector<char>& allInputNodes, const std::vector<std::pair<char, char>>& nodeDependancies, std::vector<char>& outputNodes);

#endif