#ifndef _CrackingTheCodingInterviewCPlusPlus_h_
#define _CrackingTheCodingInterviewCPlusPlus_h_

#include <string>
#include <fstream>

void PrintEndOfInputFile(const char* fileName, int numLinesToPrint)
{
	std::string* lastLinesOfFile = new std::string[numLinesToPrint];
	if (lastLinesOfFile)
	{
		std::ifstream ifs(fileName, std::ifstream::in);

		int nextIndex = 0;
		int size = 0;

		while (ifs.good())
		{
			std::getline(ifs, lastLinesOfFile[nextIndex]);
			nextIndex = (++nextIndex) % numLinesToPrint;
			size = std::min(numLinesToPrint, ++size);
		}
		ifs.close();

		int startIndex = (size < numLinesToPrint) ? 0 : nextIndex;
		for (int print = 0; print < size; ++print)
		{
			std::cout << std::endl << lastLinesOfFile[(startIndex + print) % size];
		}
		delete[] lastLinesOfFile;
	}
}

#endif