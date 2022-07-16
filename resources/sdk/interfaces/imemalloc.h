#pragma once

using MemAllocFailHandler_t = std::size_t(__cdecl *)(std::size_t);

class IMemAlloc
{
public:
	virtual void *Alloc(std::size_t nSize) = 0;
	virtual void *Realloc(void *pMemory, std::size_t nSize) = 0;
	virtual void Free(void *pMemory) = 0;
	virtual void *Expand(void *pMemory, std::size_t nSize) = 0;

	virtual void *Alloc(std::size_t nSize, const char *szFileName, int nLine) = 0;
	virtual void *Realloc(void *pMemory, std::size_t nSize, const char *szFileName, int nLine) = 0;
	virtual void Free(void *pMemory, const char *szFileName, int nLine) = 0;
	virtual void *Expand(void *pMemory, std::size_t nSize, const char *szFileName, int nLine) = 0;

	virtual std::size_t GetSize(void *pMemory) = 0;
};
