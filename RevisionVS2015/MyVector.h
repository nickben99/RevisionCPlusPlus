#ifndef _MyVector_h_
#define _MyVector_h_

// this class is only partially implemented, it uses std::allocator with allocate(), construct(), destroy(), and deallocate() which is the C++ way to do things
// further down this file MyVectorImplementation1 uses old C style malloc(), memmove, and realloc, which should not be used with C++ classes
template<class T> class MyVectorImplementation2
{
private:
	static const unsigned int startingSize = 2;
	T* data = nullptr;
	unsigned int currentSize = 0;
	unsigned int capacity = 0;
	std::allocator<T> myAllocator;

public:
	~MyVectorImplementation2()
	{
		for (unsigned int dataIter = 0; dataIter < currentSize; ++dataIter)
		{
			myAllocator.destroy(data + dataIter);
		}
		myAllocator.deallocate(data, capacity);
	}

	bool push_back(const T& newElement)
	{
		if (currentSize >= capacity)
		{
			T* oldData = data;
			capacity = data ? capacity * 2 : startingSize;
			data = myAllocator.allocate(capacity);
			if (data)
			{				
				if (oldData)
				{
					for (unsigned int dataIter = 0; dataIter < currentSize; ++dataIter)
					{
						myAllocator.construct(data + dataIter, oldData[dataIter]);
					}
					myAllocator.deallocate(oldData, currentSize); // currentSize will be equal to oldData capacity at this point
				}				
			}
			else // error
			{
				data = oldData;
				return false;
			}
		}

		if (data && currentSize < capacity)
		{
			myAllocator.construct(data + currentSize++, newElement);
			return true;
		}
		return false;
	}

	bool remove(unsigned int index)
	{
		if (index < currentSize)
		{
			myAllocator.destroy(data + index);
			for (unsigned int moveDown = index; moveDown + 1 < currentSize; ++moveDown)
			{
				data[moveDown] = data[moveDown + 1];
			}
			--currentSize;
			return true;
		}
		return false;
	}
};

// MyVectorImplementation1 is problematic, it uses old C style malloc(), memmove, and realloc, which should not be used with C++ classes
template <class T> class MyVectorImplementation1
{
public:
	MyVectorImplementation1()
		: mpData(NULL)
		, mCurrLen(0)
		, mMaxLen(8)
	{

	}

	~MyVectorImplementation1()
	{
		if (mpData)
		{
			for(int i = 0; i < mCurrLen; ++i)
			{
				mpData[i].~T();
			}
			free(mpData);
		}
	}

	bool push_back(const T& newVal)
	{
		T* reallocated = mpData;
		if (nullptr == mpData || mCurrLen >= mMaxLen)
		{
			mMaxLen = (mpData) ? mMaxLen << 1 : mMaxLen;
			reallocated = (T*)realloc(mpData, mMaxLen * sizeof(T));
		}

		if (nullptr == reallocated)	
		{
			return false;
		}
		mpData = reallocated;
		::new ( &mpData[mCurrLen] ) T(newVal);
		++mCurrLen;
		return true;
	}

	bool remove(int index)
	{
		if (index >= 0 && index < mCurrLen)
		{
			mpData[index].~T();
			memmove( &mpData[index], &mpData[index + 1], sizeof(T) * ( mMaxLen - (index + 1) ) );
			--mCurrLen;
			return true;
		}
		return false;
	}

private:
	T* mpData;
	int mCurrLen;
	int mMaxLen;
};

#endif