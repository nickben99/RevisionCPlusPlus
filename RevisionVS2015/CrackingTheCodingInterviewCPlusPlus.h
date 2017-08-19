#ifndef _CrackingTheCodingInterviewCPlusPlus_h_
#define _CrackingTheCodingInterviewCPlusPlus_h_

#include <string>
#include <fstream>

// Question 12.1
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

// Question 12.8
struct CCINode {
	CCINode* left = nullptr;
	CCINode* right = nullptr;
	void* data = nullptr;
};

typedef std::unordered_map<CCINode*, CCINode*> NodesVisited;

void CopyCCINodeInternal(CCINode*, CCINode*&, NodesVisited&);
CCINode* CopyCCINode(CCINode* original) {
	NodesVisited visited;
	CCINode* theCopy = nullptr;
	if (original) {
		CopyCCINodeInternal(original, theCopy, visited);
	}
	return theCopy;
}

void CopyCCINodeInternal(CCINode* original, CCINode*& newNode, NodesVisited& visited)
{
	if (original)
	{
		auto existingCopy = visited.find(original);
		if (visited.end() != existingCopy) // copy already made
		{
			newNode = existingCopy->second;
		}
		else
		{
			newNode = new CCINode();
			if (newNode)
			{
				visited.insert(std::make_pair(original, newNode));
				newNode->left = nullptr; //no need for this, as done in class
				newNode->right = nullptr;
				newNode->data = original->data;

				CopyCCINodeInternal(original->left, newNode->left, visited);
				CopyCCINodeInternal(original->right, newNode->right, visited);
			}
		}
	}
}

// Question 12.9
template<class T> class SmartPointer
{
public:
	SmartPointer(T* inPtr)
		: ptr(inPtr)
	{
		if (ptr) { // an assert could also be acceptable here
			count = new int(1);
		}
	}

	SmartPointer(const SmartPointer& sPtr)
		: ptr(sPtr.ptr)
		, count(sPtr.count)
	{
		if (count) { // count will be null if ptr is null
			++*count;
		}
	}

	SmartPointer& operator=(const SmartPointer& sPtr)
	{
		if (this->ptr != sPtr.ptr)
		{
			DecrementRef();

			ptr = sPtr.ptr;
			count = sPtr.count;
			if (count) { // count will be null if ptr is null
				++*count;
			}
		}
		return *this;
	}

	~SmartPointer()
	{
		DecrementRef();
	}

	// allows smartPtrInst->FunctionOnT() see drill down explanation here: https://stackoverflow.com/questions/8777845/overloading-member-access-operators-c
	T* operator->() const
	{
		return Get();
	}

	T* Get() const
	{
		return ptr;
	}

private:
	void DecrementRef()
	{
		if (ptr && 0 == --*count)
		{
			delete ptr;
			delete count;

			ptr = nullptr;
			count = nullptr;
		}
	}

	T* ptr = nullptr;
	int* count = nullptr;
};

// Question 12.10
void* AlignedMalloc(int size, int alignment)
{
	int beginPointerSize = sizeof(void*);
	int padding = alignment - 1; // worst case scenario, is allocation being 1 byte passed alignment boundary, so pad with (alignment - 1)
	char* allocated = (char*)malloc(size + beginPointerSize + padding);
	if (!allocated) {
		return nullptr;
	}
	char* aligned = allocated + beginPointerSize;

	unsigned int remainder = (unsigned int)aligned % alignment;
	if (remainder != 0) {
		aligned += (alignment - remainder);
	}
	((void**)aligned)[-1] = allocated;
	return (void*)aligned;
}

void AlignedFree(void* freeMe)
{
	if (freeMe) {
		free(((void**)freeMe)[-1]);
	}
}

// Question 12.11
int** My2DAlloc(int rows, int cols)
{
	int headerSize = rows * sizeof(int*);
	int rowSize = cols * sizeof(int);
	int bufferSize = rows*rowSize;
	int** allocated = (int**)malloc(headerSize + bufferSize);

	int* buffer = (int*)allocated + rows;
	for (int row = 0; row < rows; ++row) {
		allocated[row] = buffer + row*cols;
	}
	return allocated;
}

#endif