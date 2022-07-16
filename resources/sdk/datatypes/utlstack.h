#pragma once
#include "utlmemory.h"

template <class T, class M = CUtlMemory<T>>
class CUtlStack
{
public:
	T &operator[](int i)
	{
		return pMemory[i];
	}

	const T &operator[](int i) const
	{
		return pMemory[i];
	}

	T &Element(int i)
	{
		return pMemory[i];
	}

	const T &Element(int i) const
	{
		return pMemory[i];
	}

	T *Base()
	{
		return pMemory.Base();
	}

	const T *Base() const
	{
		return pMemory.Base();
	}

	T &Top()
	{
		return Element(iSize - 1);
	}

	const T &Top() const
	{
		return Element(iSize - 1);
	}

	int Count() const
	{
		return iSize;
	}

private:
	M pMemory;
	int iSize;
	T *pElements;
};
