#include "Pool.h"
#define POOLMAXCOUNT 1024

IPool::IPool(const char* szPoolName)
{
	AssertEx(szPoolName,"");
	m_szName = szPoolName;
	m_nSize = 0;
	m_nAllocCount = 0;
}

IPool::~IPool()
{

}

void PoolEnumerator::Instance(int nIndex,int nType,IPool *& rPool)
{
	static IPool* s_IPools[POOLMAXCOUNT] = {null_ptr};
	if (nIndex >=0 && nIndex<POOLMAXCOUNT)
	{
		if (nType == INSTANCE_GET)
		{
			rPool = s_IPools[nIndex];
		}
		else if (nType == INSTANCE_SET)
		{
			s_IPools[nIndex] = rPool;
		}
	}
}
void PoolEnumerator::Index(int nType,int &rValue)
{
	static int s_nAllocIndex =0;
	if (nType == INDEX_ALLOC)
	{
		rValue = s_nAllocIndex++;
		if (s_nAllocIndex >= POOLMAXCOUNT)
		{
			s_nAllocIndex = POOLMAXCOUNT - 1;
		}
	}
	else if (nType == INDEX_COUNT)
	{
		rValue = s_nAllocIndex;
	}
}
