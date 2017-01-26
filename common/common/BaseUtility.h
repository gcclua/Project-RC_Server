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
	_ElemList m_ElemList;	//��stl��
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
	typedef std::vector<_ElemType>	_BaseClass;
	typedef bsvector<_ElemType>		_MyselfClass;

	typedef _ElemType&			_ElemRef;
	typedef const _ElemType&	_ConstElemRef;

	typedef typename _BaseClass::size_type	size_type;

public:
	bsvector<_ElemType>(void) : _BaseClass() {}
	bsvector<_ElemType>(const _MyselfClass &rSrc) : _BaseClass(static_cast<const _BaseClass&>(rSrc)) {}
	~bsvector<_ElemType>(void) {}
	_MyselfClass& operator = (const _MyselfClass &rSrc)
	{
		_BaseClass::operator=(static_cast<const _BaseClass&>(rSrc));
		return (*this);
	}

public:
	_ElemRef operator[](size_type _i)
	{
		AssertEx(_i >= 0 && _i < _BaseClass::size(), "bsvector");
		return _BaseClass::operator[](_i);
	}
	_ConstElemRef operator[](size_type _i) const
	{
		AssertEx(_i >= 0 && _i < _BaseClass::size(), "bsvector");
		return _BaseClass::operator[](_i);
	}
};

//boundary safe array
template<typename _ElemType, tint32 _ElemSize>
class bsarray
{
public:
	typedef bsarray<_ElemType, _ElemSize> _MyselfClass;

	typedef _ElemType&			_ElemRef;
	typedef const _ElemType&	_ConstElemRef;

	typedef _ElemType*			_ElemPtr;
	typedef const _ElemType*	_ConstElemPtr;

public:
	bsarray<_ElemType, _ElemSize>(void) {}
	~bsarray<_ElemType, _ElemSize>(void) {}

public:
	/*
	Assign����û��Ĭ��ʵ�֣�ԭ�����£�
	1.Ϊ�˺�ԭ����������Ա���һ�£�ԭ������û�д����
	2.ʹ�ô�ģ����ĵط���ǳ��࣬�ṩĬ��Assign���ܴ��ڷ���
	3.ĳ������ȷ��ʹ��Assign���ܵģ�ȷ��û�з��պ�ʹ��BSARRAY_ASSIGN_DECL��BSARRAY_ASSIGN_IMPL������ػ�
	*/
	bsarray<_ElemType, _ElemSize>(const _MyselfClass &rSrc);
	_MyselfClass& operator = (const _MyselfClass &rSrc);

public:
	/*
	��ʽת��Ϊԭ������Ĺ��ܣ�Ĭ�ϲ��ṩ���Է�ֹת����ʧȥ��������ʹ��bsarray&�ķ�ʽ����_ElemType*��ʽ
	*/
	operator _ElemPtr(void);
	operator _ConstElemPtr(void) const;

public:
	tint32 ElemSize(void) const {return _ElemSize;}			//Ԫ������
	tint32 ByteSize(void) const {return sizeof(m_Elems);}	//�������ֽ���

public:
	_ElemRef operator[](tint32 _i)
	{
		AssertEx(_i >= 0 && _i < _ElemSize, "bsarray");
		return m_Elems[_i];
	}
	_ConstElemRef operator[](tint32 _i) const
	{
		AssertEx(_i >= 0 && _i < _ElemSize, "bsarray");
		return m_Elems[_i];
	}

private:
	_ElemType m_Elems[_ElemSize];
};

#define BSARRAY_ASSIGN_DECL(__TYPE, __SIZE) \
template<> \
bsarray<__TYPE, __SIZE>::bsarray(const bsarray<__TYPE, __SIZE> &rSrc); \
template<> \
bsarray<__TYPE, __SIZE>& bsarray<__TYPE, __SIZE>::operator = (const bsarray<__TYPE, __SIZE> &rSrc);

#define BSARRAY_ASSIGN_IMPL(__TYPE, __SIZE) \
template<> \
bsarray<__TYPE, __SIZE>::bsarray(const bsarray<__TYPE, __SIZE> &rSrc) \
{ \
	for (tint32 i = 0; i < __SIZE; i++) \
	{ \
		(*this)[i] = rSrc[i]; \
	} \
} \
template<> \
bsarray<__TYPE, __SIZE>& bsarray<__TYPE, __SIZE>::operator = (const bsarray<__TYPE, __SIZE> &rSrc) \
{ \
	if (this != &rSrc) \
	{ \
		for (tint32 i = 0; i < __SIZE; i++) \
		{ \
			(*this)[i] = rSrc[i]; \
		} \
	} \
	return *this; \
}

BSARRAY_ASSIGN_DECL(tint16, 10);
BSARRAY_ASSIGN_DECL(tint32, 2);
BSARRAY_ASSIGN_DECL(tint32, 6);
BSARRAY_ASSIGN_DECL(tint32, 8);
BSARRAY_ASSIGN_DECL(tint32, 9);
BSARRAY_ASSIGN_DECL(tint32, 15);
BSARRAY_ASSIGN_DECL(tint32, 17);
BSARRAY_ASSIGN_DECL(tint32, 30);
BSARRAY_ASSIGN_DECL(tfloat32, 9);
BSARRAY_ASSIGN_DECL(tint16, 5);
BSARRAY_ASSIGN_DECL(tint32, 3);
BSARRAY_ASSIGN_DECL(tint32, 10);

//����ģ��	
template<typename T, tint32 nSize>
class Container_T
{
public:
	enum CONSTANT_VALUE
	{
		LIST_SIZE = nSize,
	};
public:
	//ȡ������С
	tint32 GetSize(void) const {return LIST_SIZE;};
public:
	Container_T(void) {Cleanup();};
	~Container_T(void) {};
	Container_T& operator=(Container_T const& rhs)
	{
		for(tint32 nIndex=0; LIST_SIZE>nIndex; ++nIndex)
		{
			m_aList[nIndex] = rhs.m_aList[nIndex];
		}
		return *this;
	}
	void Cleanup(void)
	{
		for(tint32 nIndex=0; LIST_SIZE>nIndex; ++nIndex)
		{
			m_aList[nIndex].Cleanup();
		}
	}
	T const* GetSlot(tint32 nIndex) const
	{
		if(0<=nIndex && LIST_SIZE>nIndex)
		{
			return &(m_aList[nIndex]);
		}
		return null_ptr;
	}
	T* GetSlot(tint32 nIndex)
	{
		if(0<=nIndex && LIST_SIZE>nIndex)
		{
			return &(m_aList[nIndex]);
		}
		return null_ptr;
	}
	void SetSlot(tint32 nIndex, T const& rData)
	{
		if(0<=nIndex && LIST_SIZE>nIndex)
		{
			m_aList[nIndex] = rData;
		}
	}
protected:
private:
private:
	T m_aList[LIST_SIZE];
};

//�����ڲ�����index ֻ����add remove����������
template<tint32 nSize>
class IDContainer_T
{
public:
	enum CONSTANT_VALUE
	{
		LIST_SIZE = nSize,
	};
	tint32 GetSize() const {return LIST_SIZE;}
public:
	IDContainer_T(){CleanUp();}
	~IDContainer_T(){}
	IDContainer_T(const IDContainer_T& rhs){CleanUp(); CopyFrom(rhs);}
	IDContainer_T& operator=(const IDContainer_T& rhs){if(this != &rhs){ CopyFrom(rhs); } return *this;}
	void CleanUp()
	{
		for (tint32 index=0; index<LIST_SIZE; index++)
		{
			m_Value[index] = -1;
		}
	}
	void CopyFrom(const IDContainer_T& rhs)
	{
		for (tint32 index=0; index<LIST_SIZE; index++)
		{
			m_Value[index] = rhs.m_Value[index];
		}
	}
public:
	tint32 GetValue(tint32 index) const
	{
		if (index >= 0 && index < LIST_SIZE)
		{
			return m_Value[index];
		}
		return -1;
	}
	void SetValue(tint32 nValue, tint32 index)
	{
		if (index >= 0 && index < LIST_SIZE)
		{
			m_Value[index] = nValue;
		}
	}
public:
	bool AddValue(tint32 nValue)
	{
		for (tint32 index=0; index<LIST_SIZE; index++)
		{
			if (m_Value[index] == -1 &&index!=3)
			{
				m_Value[index] = nValue;
				return true;
			}
		}
		return false;
	}
	bool RemoveValue(tint32 nValue)
	{
		for (tint32 index=0; index<LIST_SIZE; index++)
		{
			if (m_Value[index] == nValue)
			{
				m_Value[index] = -1;
				return true;
			}
		}
		return false;
	}
	bool IsValueExist(tint32 nValue) const
	{
		for (tint32 index=0; index<LIST_SIZE; index++)
		{
			if (m_Value[index] == nValue)
			{
				return true;
			}
		}
		return false;
	}
	bool IsFull() const
	{
		for (tint32 index=0; index<LIST_SIZE; index++)
		{
			if (m_Value[index] == -1)
			{
				return false;
			}
		}
		return true;
	}
public:
	tint32 m_Value[LIST_SIZE];
};

#endif
