#ifndef _MEMORYPOOL_H_
#define _MEMORYPOOL_H_

const int BLOCK_TYPES = 7;
const int SUB_POOL_SIZE[BLOCK_TYPES] = {
	128, 256, 512, 1024, 2048, 4096, 8192
};

const int SUB_POOL_AMOUNT[BLOCK_TYPES] = {
	512, 256, 128, 64, 32, 16, 8
};
const float GROW_SCALE = 0.3;

class MemoryPool;

class MemoryPoolMgr
{
public:
	MemoryPoolMgr();

	~MemoryPoolMgr();

	void* Alloc(int nSize);

	void Free(void* pFree, int nSize);
private:
	MemoryPool* m_pMPools[BLOCK_TYPES];
};

#endif