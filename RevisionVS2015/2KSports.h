#ifndef _2KSports_h_
#define _2KSports_h_

struct Element2KInterview
{
	Element2KInterview* mpPrev;
	Element2KInterview* mpNext;
	void* mpData;
};

template<class T, int N> struct LinkedListNoMemAlloc2KInterview
{
	LinkedListNoMemAlloc2KInterview()
		: mHead(nullptr)
		, mNextFree(mElements)
	{
		for (int i = 0; i < N; ++i)
		{
			mElements[i].mpPrev = (0 == i) ? nullptr : &(mElements[i - 1]);
			mElements[i].mpNext = (N - 1 == i) ? nullptr : mElements + i + 1; // using differnet method of getting pointer, just for illustration
		}
	}

	// add new element after 'addAfter', or at the front if 'addAfter' is NULL
	T* Add(void* pData, T* addAfter)
	{
		if (!mNextFree)
		{
			return nullptr; // no free spots
		}

		T* newElement = mNextFree;
		mNextFree = mNextFree->mpNext;
		newElement->mpNext = newElement->mpPrev = nullptr;

		if (!addAfter || !mHead) // add at front (if !mHead then addAfter should be null)
		{
			newElement->mpNext = mHead;
			mHead = newElement;
		}
		else
		{
			newElement->mpNext = addAfter->mpNext;
			addAfter->mpNext = newElement;
			newElement->mpPrev = addAfter;
		}

		if (newElement->mpNext)
		{
			newElement->mpNext->mpPrev = newElement;
		}

		newElement->mpData = pData;
		return newElement;
	}

	void Remove(void*& outData, T* remove)
	{
		if (!remove || !mHead)
		{
			return;
		}

		if (mHead == remove)
		{
			mHead = remove->mpNext;
		}

		if (remove->mpPrev)
		{
			remove->mpPrev->mpNext = remove->mpNext;
		}

		if (remove->mpNext)
		{
			remove->mpNext->mpPrev = remove->mpPrev;
		}

		remove->mpNext = mNextFree;

		// this section is commented out as mpPrev is not used for elements on the free list (but leaving it it would not cause bugs)
		//remove->mpPrev = nullptr;
		//if (mNextFree)
		//{
		//	mNextFree->mpPrev = remove;
		//}

		outData = remove->mpData;
		remove->mpData = nullptr;

		mNextFree = remove;
	}

	T* GetHead()
	{
		return mHead;
	}

	T mElements[N];
	T* mHead;
	T* mNextFree;
};

template<typename T, int N> struct LinkedListStackNoMemAlloc2KInterview : private LinkedListNoMemAlloc2KInterview<T, N>
{
	T* Push(void* pData)
	{
		return Add(pData, nullptr);
	}

	void Pop(void*& outData)
	{
		Remove(outData, GetHead());
	}
};

#endif
