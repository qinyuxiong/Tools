#include "MemoryPool.h"
#include <iostream>
using namespace std;

MemoryPool::MemoryPool(int nUnitSize, int nUnitAmount, float fGrowScale) :
	m_nUnitSize(nUnitSize),
	m_fGrowScale(fGrowScale),
	m_nNodeInUse(0)
{
	m_pApplyHead = NULL;
	m_nUnitAmount = 0;
	m_pFreeHead = ExtendNodes(m_nUnitAmount, m_nUnitSize);
}

MemoryPool::~MemoryPool()
{
	delete []m_pFreeHead;
	m_pFreeHead = NULL;

	delete []m_pApplyHead;
	m_pApplyHead = NULL;
}

void* MemoryPool::Apply()
{
	if (m_pFreeHead != NULL)
	{
		MemoryNode *pResult = m_pFreeHead;
		m_pFreeHead = m_pFreeHead->pNext;
		pResult->pNext = m_pApplyHead;
		m_pApplyHead = pResult;
		m_nNodeInUse += 1;
		return pResult->data;
	}
	else
	{
		// have no free node, expand link-list
		m_pFreeHead = ExtendNodes(m_nUnitAmount * m_fGrowScale, m_nUnitSize);
		return Apply();
	}
}

void MemoryPool::Free(void* pFree)
{
	if ((char*)m_pApplyHead->data <= pFree && pFree < ((char*)(m_pApplyHead->data) + m_nUnitSize))
	{
		MemoryNode* pIndex = m_pApplyHead;
		m_pApplyHead = m_pApplyHead->pNext;
		pIndex->pNext = m_pFreeHead;
		m_pFreeHead = pIndex;
	}
	else
	{
		if (m_pApplyHead->pNext != NULL)
		{
			MemoryNode* pPreNode = m_pApplyHead;
			MemoryNode* pNode = m_pApplyHead->pNext;
			while ((char*)pNode->data > pFree || pFree >= ((char*)(pNode->data) + m_nUnitSize) && pNode->pNext != NULL)
			{
				pPreNode = pNode;
				pNode = pNode->pNext;
			}
			pPreNode->pNext = pNode->pNext;
			pNode->pNext = m_pFreeHead;
			m_pFreeHead = pNode;
		}
		else
		{
			cout << "fatal error, pointer exceed memory node";
			exit(0);
			return;
		}
	}

}
	

MemoryNode* MemoryPool::ExtendNodes(int nAmount, int nSize)
{
	MemoryNode *pNewNode = new MemoryNode[nAmount];
	char *pNewMemory = (char*)::operator new(nAmount * nSize);
	if (pNewNode == NULL || pNewMemory == NULL)
		exit(0);

	m_nUnitAmount += nAmount;
	int i;
	for (i = 0; i < nAmount; i++)
	{
		pNewNode[i].data = pNewMemory;

		if (i > 0)
			pNewNode[i - 1].pNext = &pNewNode[i];

		pNewMemory += nSize;
	}
	pNewNode[i].pNext = NULL;
	return pNewNode;
}
/*
void* MemoryPool::operator new(size_t size, int nUnitSize, int nUnitAmont)
{
	return ::operator new(sizeof(MemoryBlock) + nUnitSize * nUnitAmont);
}

void MemoryPool::operator delete(void* pBlock)
{
	::operator delete(pBlock);
}*/