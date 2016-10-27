
#ifndef _BASEUTILITY_H_
#define _BASEUTILITY_H_

#include "BaseType.h"
#include "BaseLib.h"
#include "Exception.h"


template<typename _ElemType>
class tslist
{
private:
	typedef std::list<_ElemType> _ElemList;
private:
	_ElemList m_ElemList;
	mutable bstMutex m_Mutex;

public:
	void push_back(const _ElemType &rElem)
	{
		bstMutexScopedLock LockGuard(m_Mutex);
		m_ElemList.push_back(rElem);
	}

	_ElemType pop_front(void)
	{
		bstMutexScopedLock LockGuard(m_Mutex);
		_ElemType elem;
		if (!m_ElemList.empty())
		{
			elem = m_ElemList.front();
			m_ElemList.pop_front();
		}
		return elem;
	}

	bool empty(void) const
	{
		bstMutexScopedLock LockGuard(m_Mutex);
		return m_ElemList.empty();
	}
};

//boundary safe vector
template<typename _ElemType>
class bsvector
	: public std::vector<_ElemType>
{
public:
	typedef std::vector<_ElemType> _BaseClass;
	typedef bsvector<_ElemType>    _MyselfClass;
	typedef _ElemType&             _ElemRef;
	typedef const _ElemType&       _ConstElemRef;
	typedef typename _BaseClass::size_type size_type;

public:
	bsvector<_ElemType>(void) : _BaseClass(){}
	bsvector<_ElemType>(const _MyselfClass &rSrc) :_BaseClass(static_cast<const _BaseClass&>(rSrc)){}
	~bsvector<_ElemType>(void){};

	_MyselfClass& operator = (const _MyselfClass &rSrc)
	{
		_BaseClass::operator=(static_cast<const _BaseClass&>(rSrc));
		return (*this);
	}

public:
	_ElemRef operator[](size_type _i)
	{
		AssertEx(_i>=0 && _i<_BaseClass().size(),"bsvector");
		return _BaseClass::operator[](_i);
	}

	_ConstElemRef operator[](size_type _i) const
	{
		AssertEx(_i>=0 && _i<_BaseClass().size(),"bsvector");
		return _BaseClass::operator[](_i);
	}
};


//boundary safe array
template<typename _ElemType,int _ElemSize>
class bsarray
{
public:
	typedef bsarray<_ElemType,_ElemSize> _MyselfClass;
	typedef _ElemType&             _ElemRef;
	typedef const _ElemType&       _ConstElemRef;
	typedef _ElemType*             _ElemPtr;
	typedef const _ElemType*       _ConstElemPtr;

public:
	bsarray<_ElemType, _ElemSize>(void) {}
	~bsarray<_ElemType, _ElemSize>(void) {}

public:
	/*
		Assign功能没有默认实现
	*/
	bsarray<_ElemType, _ElemSize>(const _MyselfClass &rSrc);
	_MyselfClass& operator =(const _MyselfClass &rSrc);

public:
	operator _ElemPtr(void);
	operator _ConstElemPtr(void) const;

public:
	int ElemSize(void) const {return _ElemSize;}
	int ByteSize(void) const {return sizeof(m_Elems);}

public:
	_ElemRef operator[](int _i)
	{
		AssertEx(_i>=0 && _i<_ElemSize,"bsarray");
		return m_Elems[_i];
	}

	_ConstElemRef operator[](int _i) const
	{
		AssertEx(_i>=0 && _i<_ElemSize,"bsarray");
		return m_Elems[_i];
	}

private:
	_ElemType m_Elems[_ElemSize];
};

#define  BSARRAY_ASSIGN_DECL(__TYPE,__SIZE) \
template<> \
	bsarray<__TYPE,__SIZE>::bsarray(const bsarray<__TYPE,__SIZE> &rSrc); \
template<> \
	bsarray<__TYPE,__SIZE>& bsarray<__TYPE,__SIZE>::operator = (const bsarray<__TYPE,__SIZE>&rSrc);

#define BSARRAY_ASSIGN_IMPL(__TYPE,__SIZE) \
template<> \
bsarray<__TYPE,__SIZE>::bsarray(const bsarray<__TYPE,__SIZE> &rSrc) \
{\
	for (int i = 0; i<__SIZE; i++) \
{\
	(*this)[i] = rSrc[i]; \
}\
}\
template<> \
bsarray<__TYPE,__SIZE>& bsarray<__TYPE,__SIZE>::operator =(const bsarray<__TYPE,__SIZE> &rSrc) \
{\
	if (this != &rSrc) \
	{ \
		for (int i = 0; i<__SIZE; i++) \
		{\
			(*this)[i] = rSrc[i]; \
		}\
	} \
	return *this; \
}

BSARRAY_ASSIGN_DECL(short, 10);
BSARRAY_ASSIGN_DECL(int, 2);
BSARRAY_ASSIGN_DECL(int, 6);
BSARRAY_ASSIGN_DECL(int, 8);
BSARRAY_ASSIGN_DECL(int, 15);
BSARRAY_ASSIGN_DECL(int, 17);
BSARRAY_ASSIGN_DECL(int, 30);
BSARRAY_ASSIGN_DECL(float, 17);

template<typename T,int nSize>
class Container_T
{
public:
	enum CONSTANT_VALUE
	{
		LIST_SIZE = nSize;
	};
public:
	int GetSize(void ) const {return LIST_SIZE;}

public:
	Container_T(void) {}
	~Container_T(){}

	Container_T& operator=(Container_T const& rhs)
	{
		for (int nIndex =0;LIST_SIZE>nIndex;++nIndex)
		{
			m_aList[nIndex] = rhs.m_aList[nIndex];
		}
		
	}

	void CleanUp(void)
	{
		for (int nIndex =0;LIST_SIZE>nIndex;++nIndex)
		{
			m_aList[nIndex].CleanUp();
		}
	}

	T const* GetSlot(int nIndex) const
	{
		if (0<=nIndex && LIST_SIZE>nIndex)
		{
			return &(m_aList[nIndex]);
		}
		return null_ptr;
	}

	T* GetSlot(int nIndex)
	{
		if (0<=nIndex && LIST_SIZE>nIndex)
		{
			return &(m_aList[nIndex]);
		}
		return null_ptr;
	}

	void SetSlot(int nIndex,T const& rData)
	{
		if (0<=nIndex && LIST_SIZE>nIndex)
		{
			m_aList[nIndex] = rData;
		}
	}

private:
	T m_aList[LIST_SIZE];
};

#endif