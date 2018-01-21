#include <iostream>
#include <memory.h>

#include "MemoryPoolMgr.h"
#include "MemoryPool.h"

using namespace std;

MemoryPoolMgr::MemoryPoolMgr()
{
	for (int i = 0; i < BLOCK_TYPES; i++)
	{
		m_pMPools[i] = new MemoryPool(SUB_POOL_SIZE[i], SUB_POOL_AMOUNT[i], GROW_SCALE);
	}
}

MemoryPoolMgr::~MemoryPoolMgr()
{
	for (int i = 0; i < BLOCK_TYPES; i++)
	{
		delete m_pMPools[i];
	}
}

void* MemoryPoolMgr::Alloc(int nSize)
{
	for(int i = 0; i < BLOCK_TYPES; i++)
	{
		if (nSize <= SUB_POOL_SIZE[i])
		{
			return m_pMPools[i]->Apply();
		}
	}
}

void MemoryPoolMgr::Free(void* pFree, int nSize)
{
	for (int i = 0; i < BLOCK_TYPES; i++)
	{
		if (nSize <= SUB_POOL_SIZE[i])
		{
			return m_pMPools[i]->Free(pFree);
		}
	}
}