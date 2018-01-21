#ifndef _MEMORYBLOCK_H_
#define _MEMORYBLOCK_H_

#include <windows.h>

struct MemoryNode
{
	void *data;
	MemoryNode* pNext;
};

class MemoryPool
{
public:
	MemoryPool(int nUnitSize, int nUnitAmount, float fGrowScale);

	~MemoryPool();

	void* Apply();

	void Free(void* pFree);

	MemoryNode* ExtendNodes(int nAmount, int nSize);

	//void* operator new(size_t size, int nUnitSize, int nUnitAmont);

	//void operator delete(void* pBlock);

private:
	int m_nUnitSize;
	int m_nUnitAmount;
	float m_fGrowScale;
	int m_nNodeInUse;
	MemoryNode *m_pApplyHead;  // cur applied head node pointer
	MemoryNode *m_pFreeHead;  // cur avaliable head node pointer
};

#endif