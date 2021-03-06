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

		int counter = 0;
		while (ifs.good())
		{
			std::getline(ifs, lastLinesOfFile[counter++ % numLinesToPrint]);
		}
		ifs.close();

		int start = std::max(0, counter - numLinesToPrint);
		for (int printer = start; printer < counter; ++printer)
		{
			std::cout << std::endl << lastLinesOfFile[printer % numLinesToPrint];
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
	CCINode* theCopy = nullptr;
	if (original) {
		NodesVisited visited;
		CopyCCINodeInternal(original, theCopy, visited);
	}
	return theCopy;
}

void CopyCCINodeInternal(CCINode* original, CCINode*& newNode, NodesVisited& visited)
{
	newNode = nullptr;
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
				newNode->left = newNode->right = nullptr; //no need for this, as done in class
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
			ReleaseRef();

			ptr = sPtr.ptr;
			count = sPtr.count;
			if (count) { // count will be null if ptr is null
				++*count;
			}
		}
		// NOTE: could add else case here which asserts if count pointers are not also equal, 
		// as having the same pointers but different count pointers will result in ptr eventually getting deleted while it still might be needed
		return *this;
	}

	~SmartPointer()
	{
		ReleaseRef();
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
	void ReleaseRef()
	{
		if (ptr && 0 == --*count)
		{
			delete ptr;
			delete count;
		}
		ptr = nullptr;
		count = nullptr;
	}

	T* ptr = nullptr;
	int* count = nullptr;
};

// Question 12.10
void* AlignedMalloc(int size, size_t alignment)
{
	size_t beginPointerSize = sizeof(void*);
	size_t padding = alignment - 1; // worst case scenario, is allocation being 1 byte passed alignment boundary, so pad with (alignment - 1)
	void* allocated = malloc(size + beginPointerSize + padding);
	if (!allocated) {
		return nullptr;
	}

	void* alignedReturn = nullptr;
	static bool alwaysPowerOf2Method = false;
	if (!alwaysPowerOf2Method)
	{
		alignedReturn = (char*)allocated + beginPointerSize;
		size_t remainder = (size_t)alignedReturn % alignment;
		if (remainder != 0) {
			alignedReturn = (char*)alignedReturn + (alignment - remainder);
		}
	}
	else
	{	// NOTE: if alignment is always a power of 2, the following two lines could be used in place of the above five lines to calculate alignedReturn
		size_t possibleAligned = (size_t)allocated + beginPointerSize + padding;
		alignedReturn = (void*)(possibleAligned & ~padding); // results in all bits less significant being removed
	}

	((void**)alignedReturn)[-1] = allocated;
	return alignedReturn;
}

void AlignedFree(void* freeMe)
{
	if (freeMe) {
		void* allocated = ((void**)freeMe)[-1];
		free(allocated);
	}
}

// Question 12.11
int** My2DAlloc(int rows, int cols)
{
	int headerSize = rows * sizeof(int*);
	int bufferSize = rows * cols * sizeof(int);
	int** allocated = (int**)malloc(headerSize + bufferSize);

	int* buffer = (int*)(allocated + rows);
	for (int row = 0; row < rows; ++row) {
		allocated[row] = buffer + row*cols;
	}
	return allocated;
}

#endif