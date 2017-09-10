#ifndef _ZyngaQuestions_h_
#define _ZyngaQuestions_h_

#include <string>
#include <unordered_set>

bool FindNumChangesBetweenWordsBidirectionalBreadthFirstSearch(const std::string& from, const std::string& to, 
	const std::unordered_set<std::string>& dict, int& res);

// this answer uses an a* search (suggested here: http://stackoverflow.com/questions/1521958/shortest-path-to-transform-one-word-into-another?lq=1), it considers 
// each one letter different string to be a linked node. After researching it would appear that an average breadth first search would also get to the 
// correct answer, but could take longer.
bool FindNumChangesBetweenWordsAStar(const std::string& from, const std::string& to, const std::unordered_set<std::string>& dict, int& numChanges);

#endif