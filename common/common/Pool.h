
#ifndef _POOL_H_
#define _POOL_H_

#include <new>
#include "BaseUtility.h"
#include "BaseType.h"
#include "Exception.h"

class IPool
{
public:
	IPool(const char* szPoolName);

	~IPool();

private:
	IPool(const IPool &);
	IPool& operator=(const IPool &);
public:
	std::string m_szName;
	int    m_nSize;
	int    m_nAllocCount;
public:

	virtual void Recycle__(void) {}
};

class PoolEnumerator
{
public:
	enum 
	{
		INDEX_ALLOC = 0,
		INDEX_COUNT,
	};

	static void Index(int nType,int &rValue);

public:
	enum 
	{
		INSTANCE_GET = 0,
		INSTANCE_SET,
	};
	static void Instance(int nIndex,int nType,IPool *& rPool);
};

template<typename _ElemType,
	int _RecycleInterval = 64,
	int _AllocateInterval =1>
class Pool :public IPool
{
public:
	typedef boost::shared_ptr<_ElemType> _ElemPtr;
	typedef std::pair<_ElemPtr,bool>     _ElemUnit;

private:
	typedef bsvector<_ElemUnit> _ElemCont;
	typedef std::list<int>      _ElemRef;

private:
	bstMutex m_bstMutex;
	_ElemCont m_ElemCont;
	_ElemRef  m_ElemRef;
	int       m_nLastRecycle;

public:
	Pool<_ElemType,_RecycleInterval,_AllocateInterval>(const char *szPoolName)
		: IPool(szPoolName)
	{
		m_nLastRecycle = 0;
		int nIndex = 0;
		PoolEnumerator::Index(PoolEnumerator::INDEX_ALLOC,nIndex);
		IPool *pThis = this;
		PoolEnumerator::Instance(nIndex,PoolEnumerator::INSTANCE_SET,pThis);
	}
	~Pool<_ElemType,_RecycleInterval,_AllocateInterval>(void)
	{

	}
public:
	_ElemPtr New(void)
	{
		__ENTER_PROTECT
			bstMutexScopedLock LockGuard(m_bstMutex);
		if (m_ElemRef.empty())
		{
			Recycle();
		}
		if (m_ElemRef.empty())
		{
			Allocate();
		}

		AssertEx(!m_ElemRef.empty(),"Pool,no more elem!");
		const int nIndex = m_ElemRef.front();
		m_ElemRef.pop_front();
		AssertEx(nIndex>=0 && nIndex<(int)m_ElemCont.size(),"Pool,index out of range");
		AssertEx(m_ElemCont[nIndex].first.unique(),"Pool,elemunit is not unique");
		AssertEx(m_ElemCont[nIndex].second,"Pool,elemunit is not ready");

		m_ElemCont[nIndex].second = false;

		m_nAllocCount++;
		_ElemPtr elemPtr = m_ElemCont[nIndex].first;
		return elemPtr;

		__LEAVE_PROTECT
			_ElemPtr RetPtr(new _ElemType());
		return RetPtr;
	}
private:
	void Recycle(void)
	{
		__ENTER_PROTECT
			AssertEx(m_ElemRef.empty(),"Pool,elem is not empty while call Recycle");
		const int nElemContSize = (int)m_ElemCont.size();
		for (int i = 0; i < nElemContSize;i++)
		{
			AssertEx(m_nLastRecycle >=0,"Pool,m_nLastRecycle error 0");
			AssertEx(m_nLastRecycle < nElemContSize,"Pool,m_nLastRecycle error 1");

			if (m_ElemCont[m_nLastRecycle].first.unique())
			{
				m_ElemCont[m_nLastRecycle].first->_ElemType::~_ElemType();
				new(m_ElemCont[m_nLastRecycle].first.get()) _ElemType();
				m_ElemRef.push_back(m_nLastRecycle);
				m_ElemCont[m_nLastRecycle].second = true;

				m_nLastRecycle = (m_nLastRecycle+1) % nElemContSize;
				if (m_ElemRef.size()>= _AllocateInterval)
				{
					break;
				}
			}
			else
			{
				m_nLastRecycle = (m_nLastRecycle+1) % nElemContSize;
			}
		}
		__LEAVE_PROTECT
	}
private:
	void Allocate(void)
	{
		__ENTER_PROTECT
			AssertEx(m_ElemRef.empty(),"Pool,elem is not empty while call Allocate");
		for (int i = 0;i < _AllocateInterval; i++)
		{
			_ElemPtr elemPtr(new _ElemType());
			m_ElemCont.push_back(std::make_pair(elemPtr,true));
			m_ElemRef.push_back((int)m_ElemCont.size()-1);

		}
		m_nSize = static_cast<int>(m_ElemCont.size());
		__LEAVE_PROTECT
	}
public:
	virtual void Recycle__(void)
	{
		__ENTER_PROTECT
			bstMutexScopedLock LockGuard(m_bstMutex);
		const int nElemContSize = (int)m_ElemCont.size();
		for (int i=0;i<nElemContSize;i++)
		{
			if (!m_ElemCont[i].first.unique())
			{
				m_ElemCont[i].first->_ElemType::~_ElemType();
				new(m_ElemCont[i].first.get()) _ElemType();
				m_ElemRef.push_back(i);
				m_ElemCont[i].second = true;
			}
		}
		__LEAVE_PROTECT
	}
private:
	void CheckMyself(void) const 
	{
		__ENTER_PROTECT
			for (int i=0;i<(int)m_ElemCont.size();i++)
			{
				if (m_ElemCont[i].second)
				{
					AssertEx(std::find(m_ElemRef.begin(),m_ElemRef.end(),i) != m_ElemRef.end(),"Pool,CheckMyself,0!");
					AssertEx(m_ElemCont[i].first.unique(),"Pool,CheckMyself,1!");
				}
				else
				{
					AssertEx(std::find(m_ElemRef.begin(),m_ElemRef.end(),i) == m_ElemRef.end(),"Pool,CheckMyself,2!");
				}
			}

			for (_ElemRef::const_iterator it = m_ElemRef.begin(); it != m_ElemRef.end();it++)
			{
				AssertEx((*it)>=0 && (*it) < (int)m_ElemCont.size(),"Pool,CheckMyself ,3!");
				AssertEx(m_ElemCont[(*it)].first.unique(),"Pool,CheckMyself,4!");
				AssertEx(m_ElemCont[(*it)].second,"Pool,CheckMyself,5!");
			}

			AssertEx(m_nLastRecycle >=0,"Pool,CheckMyself,6!");
			__LEAVE_PROTECT
	}

};



#define  POOLDEF_INST(POOLTYPE) \
	g##POOLTYPE##POOL
#define  POOLDEF_DECL(POOLTYPE) \
	extern Pool<POOLTYPE> POOLDEF_INST(POOLTYPE); \
	typedef Pool<POOLTYPE>::_ElemPtr POOLTYPE##Ptr;

#define POOLDEF_IMPL(POOLTYPE) \
	Pool<POOLTYPE> POOLDEF_INST(POOLTYPE)(#POOLTYPE)
#define POOLDEF_NEW(POOLTYPE) \
	POOLDEF_INST(POOLTYPE).New()
#endif