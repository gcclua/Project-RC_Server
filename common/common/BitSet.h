#ifndef _BITSET_H_
#define _BITSET_H_

#include "BaseType.h"
#include "BaseLib.h"

template<int _BitSize>
class BitSet
{
public:
	typedef BitSet<_BitSize> _MyselfClass;

public:
	enum CONST_VALUE
	{
		BIT_SIZE	= _BitSize,				//bit总数
		BYTE_SIZE	= (BIT_SIZE + 7) / 8,	//Byte总数
	};

public:
	BitSet<_BitSize>(void)
	{
		_MyselfClass::ClearAllBits();
	}
	~BitSet<_BitSize>(void)
	{

	}

public:
	BitSet<_BitSize>(const BitSet<_BitSize> &r)
	{
		memcpy(m_BitBuffer, r.m_BitBuffer, BYTE_SIZE);
		m_nMarkedBitCount = r.m_nMarkedBitCount;
	}
	BitSet<_BitSize> & operator=(const BitSet<_BitSize> &r)
	{
		memcpy(m_BitBuffer, r.m_BitBuffer, BYTE_SIZE);
		m_nMarkedBitCount = r.m_nMarkedBitCount;
		return *this;
	}

public:
	void MarkAllBits(void)
	{
		memset(m_BitBuffer, 0xff, BYTE_SIZE);
		m_nMarkedBitCount = BIT_SIZE;
	}
	void ClearAllBits(void)
	{
		memset(m_BitBuffer, 0x00, BYTE_SIZE);
		m_nMarkedBitCount = 0;
	}
	void MarkBit(int nIdx)
	{
		_MyselfClass::SetBit(nIdx, true);
	}
	void ClearBit(int nIdx)
	{
		_MyselfClass::SetBit(nIdx, false);
	}
	bool GetBit(int nIdx) const
	{
		if(0 <= nIdx && BIT_SIZE > nIdx)
		{
			return ((m_BitBuffer[nIdx>>3] & (1<<(nIdx & 0x7))) ? true : false);
		}
		return false;
	}
	void SetBit(int nIdx, bool bValue)
	{
		bool bOriginalValue = _MyselfClass::GetBit(nIdx);

		if(0 <= nIdx && BIT_SIZE > nIdx)
		{
			if(bValue)
			{
				m_BitBuffer[nIdx>>3] |= 0x01<<(nIdx%8);
				if (!bOriginalValue)
				{
					m_nMarkedBitCount++;
				}
			}
			else
			{
				m_BitBuffer[nIdx>>3] &= ~(0x01<<(nIdx%8));
				if (bOriginalValue)
				{
					m_nMarkedBitCount--;
				}
			}
		}
	}

public:
	static int GetByteSize(void)
	{
		return BYTE_SIZE;
	}
	static int GetBitSize(void)
	{
		return BIT_SIZE;
	}

public:
	const byte * GetBitBuffer(void) const
	{
		return m_BitBuffer;
	}
	void SetBitBuffer(const byte *pBytes, int nSize)
	{
		if (pBytes != null_ptr && nSize == BYTE_SIZE)
		{
			memcpy(m_BitBuffer, pBytes, BYTE_SIZE);
			_MyselfClass::CalcMarkedBitCount();
		}
	}
protected:
	void CalcMarkedBitCount(void)
	{
		m_nMarkedBitCount = 0;
		for (int i = 0; i < BIT_SIZE; i++)
		{
			if (_MyselfClass::GetBit(i))
			{
				m_nMarkedBitCount++;
			}
		}
	}

public:
	int GetMarkedBitCount(void) const
	{
		return m_nMarkedBitCount;
	}
	int GetClearedBitCount(void) const
	{
		return ((int)BIT_SIZE - m_nMarkedBitCount);
	}

private:
	byte	m_BitBuffer[BYTE_SIZE];
	int	m_nMarkedBitCount;
};

#endif
