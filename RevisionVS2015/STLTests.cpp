#include "STLTests.h"
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

void STLVectorTests()
{
	std::cout << std::endl << std::endl << "STLVectorTests() - Start";
	std::vector<int> ints;
	std::cout << std::endl << "After init: " << ints.size();
	ints.reserve(10);
	std::cout << std::endl << "After reserve 10: " << ints.size();
	ints.resize(10);
	std::cout << std::endl << "After resize 10: " << ints.size();
	ints.push_back(4);
	std::cout << std::endl << "After ints.push_back(4): " << ints.size();
	
	std::cout << std::endl << "ints[10]: " << ints[10];
	
	std::vector<int>::const_iterator iter = ints.begin() + 10;
	std::cout << std::endl << "*iter: " << *iter;

	std::cout << std::endl << "STLVectorTests() - End";

	std::cout << std::endl << std::endl << "STLVectorTests() - Start 2nd Test";
	
	std::vector<int> presetints(3, 67);
	std::cout << std::endl << "after std::vector<int> presetints(3, 67) : " << presetints.size();
	std::cout << std::endl << "Displaying all values: ";
	for (std::vector<int>::const_iterator i = presetints.begin(); i != presetints.end(); ++i)
	{
		std::cout << std::endl << "value " << i-presetints.begin() << ": " << *i;
	}

	presetints.erase(presetints.begin());
	std::cout << std::endl << "Displaying all values (after presetints.erase(presetints.begin())): ";
	for (std::vector<int>::const_iterator i = presetints.begin(); i != presetints.end(); ++i)
	{
		std::cout << std::endl << "value " << i - presetints.begin() << ": " << *i;
	}

	presetints.insert(presetints.end(), 70);
	//presetints.insert(70); doesn't compile, no std::vector::insert() function takes one parameter
	//presetints.push_front(70); // doesn't compile
	std::cout << std::endl << "Displaying all values (after presetints.insert(presetints.end(), 70)): ";
	for (std::vector<int>::const_iterator i = presetints.begin(); i != presetints.end(); ++i)
	{
		std::cout << std::endl << "value " << i - presetints.begin() << ": " << *i;
	}

	//presetints.erase(presetints.end()); // will cause vector out of range error

	std::vector<int> initiallySizedInts(5);
	std::cout << std::endl << "after std::vector<int> initiallySizedInts(5): " << initiallySizedInts.size();

	std::cout << std::endl << "STLVectorTests() - End 2nd Test";
}

void STLListTests()
{
	std::cout << std::endl << std::endl << "STLListTests() - Start";
	std::list<int> ints;
	std::cout << std::endl << "After init: " << ints.size();
	//ints.reserve(); // doesn't exist for std::list
	ints.resize(4);
	std::cout << std::endl << "After resize 4: " << ints.size();
	//std::cout << std::endl << "ints[0]: " << ints[0]; // !!!!!! doesn't compile as index operator doesn't exist for std::list
	ints.push_back(9);
	std::cout << std::endl << "After ints.push_back(9): " << ints.size();

	ints.push_front(3);
	std::cout << std::endl << "After ints.push_front(3): " << ints.size();

	ints.insert(++ints.begin(), 10);
	std::cout << std::endl << "after ints.insert(++ints.begin(), 10); : " << std::endl;
	for (int i : ints)
	{
		std::cout << ' ' << i;
	}
												
	ints.insert(++ints.begin(), 2, 20);        
	std::cout << std::endl << "after ints.insert(++ints.begin(), 2, 20); : " << std::endl;
	for (int i : ints)
	{
		std::cout << ' ' << i;
	}
	
	std::cout << std::endl << "Displaying all values: ";
	for (std::list<int>::const_iterator i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << " " << *i;
	}
	
	// ints.insert(5); // !!!!!! won't compile, no std::list.insert() takes just one parameter

	std::cout << std::endl << "Displaying all values  (auto iterator): ";
	for (auto i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << " " << *i;
	}
	
	std::cout << std::endl << "STLListTests() - End";
}

void STLMapTests()
{
	std::cout << std::endl << std::endl << "STLMapTests() - Start";
	std::map<int, int> ints;
	std::cout << std::endl << "After init: " << ints.size();
	ints.insert(std::make_pair(4,3));
	std::cout << std::endl << "After ints.insert(std::make_pair(4, 3)): " << ints.size();	
	std::cout << std::endl << "ints[4]: " << ints[4];
	ints.insert(std::make_pair(4,6));
	std::cout << std::endl << "After ints.insert(std::make_pair(4, 6)): " << ints.size();	
	std::cout << std::endl << "ints[4]: " << ints[4];
	ints[4]=6;
	std::cout << std::endl << "After ints[4]=6: " << ints.size();	
	std::cout << std::endl << "ints[4]: " << ints[4];
	ints[2]=8;
	std::cout << std::endl << "After ints[2]=8: " << ints.size();	
	std::cout << std::endl << "ints[2]: " << ints[2];
	ints[2]=3;
	std::cout << std::endl << "After ints[2]=3: " << ints.size();	
	std::cout << std::endl << "ints[2]: " << ints[2];
	
	std::map<int, int>::iterator found = ints.find(2);
	if (found != ints.end())
	{
		std::cout << std::endl << "found->first: " << found->first;
		std::cout << std::endl << "found->second: " << found->second;
		std::cout << std::endl << "ints.find(2)->second: " << ints.find(2)->second;
	}

	std::cout << std::endl << "Displaying all values: ";
	for (std::map<int, int>::const_iterator i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << i->first << " " << i->second;
	}

	ints.erase(ints.begin());
	std::cout << std::endl << "Displaying all values (ints.erase(ints.begin())): ";
	for (auto i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << i->first << " " << i->second;
	}
	
	std::cout << std::endl << "STLMapTests() - End";
}

void STLStackTests()
{
}

void STLQueueTests()
{
}

void STLBitSetTests()
{
	std::cout << std::endl << std::endl << "STLMapTests() - Start";
	std::bitset<20> preAllocated20;
	std::cout << std::endl << "std::bitset<20> preAllocated20 " << preAllocated20;
	std::cout << std::endl << "preAllocated20.count() " << preAllocated20.count();
	std::cout << std::endl << "preAllocated20.to_ulong() " << preAllocated20.to_ulong();
	preAllocated20[6] = true;
	std::cout << std::endl << "after preAllocated20[6] = true : " << preAllocated20.count();
	std::cout << std::endl << "after preAllocated20[6] = true : " << preAllocated20;
	std::cout << std::endl << "preAllocated20.to_ulong() " << preAllocated20.to_ulong();
	preAllocated20.flip();
	std::cout << std::endl << "after preAllocated20.flip() : " << preAllocated20.count();
	std::cout << std::endl << "after preAllocated20.flip() : " << preAllocated20;

	std::cout << std::endl << "STLMapTests() - End";
}

void STLUnorderedSetTests()
{
	std::cout << std::endl << std::endl << "STLUnorderedSetTests() - Start";
	std::unordered_set<int> ints;
	std::cout << std::endl << "After init: " << ints.size();
	ints.insert(4);
	std::cout << std::endl << "After ints.insert(4): " << ints.size();
	ints.insert(4);
	std::cout << std::endl << "After ints.insert(4): " << ints.size();
	ints.insert(2);
	std::cout << std::endl << "After ints.insert(2): " << ints.size();
	ints.insert(17);
	std::cout << std::endl << "After ints.insert(17): " << ints.size();
	ints.insert(17);
	std::cout << std::endl << "After ints.insert(17): " << ints.size();

	std::unordered_set<int>::iterator found = ints.find(2);
	if (found != ints.end())
	{
		std::cout << std::endl << "found: " << *found;
		std::cout << std::endl << "*ints.find(2): " << *ints.find(2);
	}

	std::cout << std::endl << "Displaying all values: ";
	for (std::unordered_set<int>::const_iterator i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << *i;
	}

	ints.erase(17);
	std::cout << std::endl << "After ints.erase(17): " << ints.size();

	ints.erase(ints.begin());
	std::cout << std::endl << "After ints.erase(ints.begin()): " << ints.size();

	std::cout << std::endl << "STLUnorderedSetTests() - End";
}

void STLUnorderedMapTests()
{
	std::cout << std::endl << std::endl << "STLUnorderedMapTests() - Start";
	std::unordered_map<int, int> ints;
	std::cout << std::endl << "After init: " << ints.size();
	ints.insert(std::make_pair(4, 3));
	std::cout << std::endl << "After ints.insert(std::make_pair(4, 3)): " << ints.size();
	std::cout << std::endl << "ints[4]: " << ints[4];
	ints.insert(std::make_pair(4, 6));
	std::cout << std::endl << "After ints.insert(std::make_pair(4, 6)): " << ints.size();
	std::cout << std::endl << "ints[4]: " << ints[4];
	ints[4] = 6;
	std::cout << std::endl << "After ints[4]=6: " << ints.size();
	std::cout << std::endl << "ints[4]: " << ints[4];
	ints[2] = 8;
	std::cout << std::endl << "After ints[2]=8: " << ints.size();
	std::cout << std::endl << "ints[2]: " << ints[2];
	ints[2] = 3;
	std::cout << std::endl << "After ints[2]=3: " << ints.size();
	std::cout << std::endl << "ints[2]: " << ints[2];

	std::unordered_map<int, int>::iterator found = ints.find(2);
	if (found != ints.end())
	{
		std::cout << std::endl << "found->first: " << found->first;
		std::cout << std::endl << "found->second: " << found->second;
		std::cout << std::endl << "ints.find(2)->second: " << ints.find(2)->second;
	}

	std::cout << std::endl << "Displaying all values: ";
	for (std::unordered_map<int, int>::const_iterator i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << i->first << " " << i->second;
	}

	ints.erase(ints.begin());
	std::cout << std::endl << "Displaying all values (ints.erase(ints.begin())): ";
	for (auto i = ints.begin(); i != ints.end(); ++i)
	{
		std::cout << std::endl << i->first << " " << i->second;
	}

	std::cout << std::endl << "STLUnorderedMapTests() - End";
}