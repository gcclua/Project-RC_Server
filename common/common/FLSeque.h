#ifndef _FLSEQUE_H_
#define _FLSEQUE_H_

#include "BaseType.h"
#include "BaseLib.h"

template<typename _ElemType,
		 typename _ElemTraits,
		 int _ElemSize>
class FLSeque
{
public:
	typedef FLSeque<_ElemType, _ElemTraits, _ElemSize> _MyselfClass;

public:
	FLSeque<_ElemType, _ElemTraits, _ElemSize>(void)
	{
		_MyselfClass::CleanUp();
	}
	~FLSeque<_ElemType, _ElemTraits, _ElemSize>(void)
	{
	}

public:
	void CleanUp(void)
	{
		m_nValidSize = 0;
		_ElemTraits::CleanUpElems(m_Elems, _ElemSize);
	}

public:
	int Size(void)		const {return m_nValidSize;}
	int MaxSize(void)	const {return _ElemSize;}
	bool Empty(void)		const {return (m_nValidSize <= 0);}
	bool Full(void)			const {return (m_nValidSize >= _ElemSize);}

public:
	bool Append(const _ElemType &rElem)
	{
		return _MyselfClass::Append(&rElem, 1);
	}
	bool Append(const _ElemType *pElems, int nSize)
	{
		bool bResult = false;
		if (pElems != null_ptr && nSize > 0)
		{
			if ((m_nValidSize >= 0) && (m_nValidSize < _ElemSize))
			{
				int nIndex = 0;
				for (; ((m_nValidSize < _ElemSize) && (nIndex < nSize));)
				{
					m_Elems[m_nValidSize++] = pElems[nIndex++];
				}
				bResult = (nIndex == nSize);
			}
		}
		_MyselfClass::Seal();
		return bResult;
	}

	bool Remove(int nDst)
	{
		return _MyselfClass::Remove(nDst, 1);
	}
	bool Remove(int nDst, int nSize)
	{
		bool bResult = false;
		if ((m_nValidSize >= 0) && (m_nValidSize <= _ElemSize))
		{
			if ((nDst >= 0) && (nSize >= 1))
			{
				if ((nDst + nSize) <= m_nValidSize)
				{
					for (int nIndex = nDst; (nIndex + nSize) < m_nValidSize; nIndex++)
					{
						m_Elems[nIndex] = m_Elems[nIndex + nSize];
					}
					m_nValidSize -= nSize;
					bResult = true;
				}
			}
		}
		_MyselfClass::Seal();
		return bResult;
	}

	const _ElemType *Get(void) const
	{
		return m_Elems;
	}
	const _ElemType *Get(int nIndex) const
	{
		if ((m_nValidSize >= 0) && (m_nValidSize <= _ElemSize))
		{
			if ((nIndex + 1) >= 1 && (nIndex + 1) <= m_nValidSize)
			{
				return (&(m_Elems[nIndex]));
			}
		}
		return null_ptr;
	}

	const _ElemType & operator[](int i) const
	{
		AssertEx(m_nValidSize >= 0 && m_nValidSize <= _ElemSize, "");
		AssertEx(i >= 0 && i < m_nValidSize, "");
		return m_Elems[i];
	}

	_ElemType & operator[](int i)
	{
		AssertEx(m_nValidSize >= 0 && m_nValidSize <= _ElemSize, "");
		AssertEx(i >= 0 && i < m_nValidSize, "");
		return m_Elems[i];
	}

private:
	void Seal(void)
	{
		if (_ElemTraits::ShouldSeal())
		{
			if (_MyselfClass::Full())
			{
				m_nValidSize = _ElemSize - 1;
			}

			const int nValidSize = _MyselfClass::Size();
			const int nMaxSize = _MyselfClass::MaxSize();
			if (nValidSize >= 0 && nValidSize < nMaxSize)
			{
				_ElemTraits::CleanUpElem(m_Elems[nValidSize]);
			}
		}
	}

private:
	int m_nValidSize;
	_ElemType m_Elems[_ElemSize];
};

#endif
