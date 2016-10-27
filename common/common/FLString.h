#ifndef _FLSTRING_H_
#define _FLSTRING_H_

#include "FLSeque.h"

class FLStringTraits
{
public:
	static void CleanUpElems(char *lpElems, int nSize)
	{
		if (lpElems != null_ptr && nSize >= 1)
		{
			memset(lpElems, 0, nSize);
		}
	}

	static void CleanUpElem(char &rElem)
	{
		rElem = '\0';
	}

	static bool ShouldSeal(void)
	{
		return true;
	}
};

template<int _ElemSize>
class FLString
	: public FLSeque<char, FLStringTraits, _ElemSize>
{
public:
	typedef FLSeque<char, FLStringTraits, _ElemSize> _BaseClass;
	typedef FLString<_ElemSize> _MyselfClass;

public:
	FLString<_ElemSize>(void) : _BaseClass()
	{
	}
	~FLString<_ElemSize>(void)
	{
	}

public:
	explicit FLString<_ElemSize>(const char* szText) : _BaseClass()
	{
		*this = szText;
	}
	FLString<_ElemSize>(const _MyselfClass &rSrc) : _BaseClass()
	{
		*this = rSrc;
	}
	template<int _Size>
	FLString<_ElemSize>(const FLString<_Size> &rSrc) : _BaseClass()
	{
		*this = rSrc;
	}

	explicit FLString<_ElemSize>(int16 nValue) : _BaseClass()
	{
		*this = nValue;
	}
	explicit FLString<_ElemSize>(int8 nValue) : _BaseClass()
	{
		*this = nValue;
	}
	explicit FLString<_ElemSize>(int nValue) : _BaseClass()
	{
		*this = nValue;
	}

	explicit FLString<_ElemSize>(uint8 nValue) : _BaseClass()
	{
		*this = nValue;
	}
	explicit FLString<_ElemSize>(uint16 nValue) : _BaseClass()
	{
		*this = nValue;
	}
	explicit FLString<_ElemSize>(uint32 nValue) : _BaseClass()
	{
		*this = nValue;
	}

public:
	const char* GetCText(void)		const {return _BaseClass::Get();}
	int GetLength(void)		const {return _BaseClass::Size();}
	int GetMaxLength(void)	const {return _BaseClass::MaxSize();}

	uint32 GetCRC(void) const
	{
		uint32 nRet = 0xFFFFFFFF;

		const char* szContent = _MyselfClass::GetCText();
		if (szContent != null_ptr)
		{
			for (int i = 0; i < _MyselfClass::GetLength(); i++)
			{
				nRet = nRet * 33 + static_cast<uint32>(szContent[i]);
			}
		}

		return nRet;
	}

public:
	_MyselfClass& operator = (const char* szText)
	{
		_BaseClass::CleanUp();
		return (*this += szText);
	}
	_MyselfClass& operator += (const char* szText)
	{
		if (szText != null_ptr)
		{
			const int nLen = static_cast<int>(strlen(szText));
			if (nLen > 0)
			{
				_BaseClass::Append(szText, nLen);
			}
		}
		return *this;
	}
	bool operator == (const char* szText) const
	{
		if (szText != null_ptr)
		{
			const int nLen = static_cast<int>(strlen(szText));
			if (_MyselfClass::GetLength() == nLen)
			{
				if (strcmp(_MyselfClass::GetCText(), szText) == 0)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool operator != (const char* szText) const
	{
		return !(*this == szText);
	}

public:
	_MyselfClass& operator = (const _MyselfClass &rSrc)
	{
		return (*this = rSrc.GetCText());
	}
	_MyselfClass& operator += (const _MyselfClass &rSrc)
	{
		return (*this += rSrc.GetCText());
	}
	bool operator == (const _MyselfClass &rSrc) const
	{
		return (*this == rSrc.GetCText());
	}
	bool operator != (const _MyselfClass &rSrc) const
	{
		return (*this != rSrc.GetCText());
	}
	bool operator < (const _MyselfClass &rSrc) const
	{
		return (::strcmp((*this).GetCText(), rSrc.GetCText()) < 0);
	}

public:
	template<int _Size>
	_MyselfClass& operator = (const FLString<_Size> &rSrc)
	{
		return (*this = rSrc.GetCText());
	}
	template<int _Size>
	_MyselfClass& operator += (const FLString<_Size> &rSrc)
	{
		return (*this += rSrc.GetCText());
	}
	template<int _Size>
	bool operator == (const FLString<_Size> &rSrc) const
	{
		return (*this == rSrc.GetCText());
	}
	template<int _Size>
	bool operator != (const FLString<_Size> &rSrc) const
	{
		return (*this != rSrc.GetCText());
	}

public:
	_MyselfClass& operator = (int8 nValue)
	{
		return (*this = static_cast<int>(nValue));
	}
	_MyselfClass& operator = (int16 nValue)
	{
		return (*this = static_cast<int>(nValue));
	}
	_MyselfClass& operator = (int nValue)
	{
		char szBuffer[64];
		memset(szBuffer, 0, sizeof(szBuffer));
		tsnprintf(szBuffer, sizeof(szBuffer), "%d", nValue);
		szBuffer[sizeof(szBuffer) - 1] = '\0';
		return (*this = szBuffer);
	}

	_MyselfClass& operator = (uint8 nValue)
	{
		return (*this = static_cast<uint32>(nValue));
	}
	_MyselfClass& operator = (uint16 nValue)
	{
		return (*this = static_cast<uint32>(nValue));
	}
	_MyselfClass& operator = (uint32 nValue)
	{
		char szBuffer[64];
		memset(szBuffer, 0, sizeof(szBuffer));
		tsnprintf(szBuffer, sizeof(szBuffer), "%u", nValue);
		szBuffer[sizeof(szBuffer) - 1] = '\0';
		return (*this = szBuffer);
	}

public:
	int8 GetAsInt8(void) const
	{
		return static_cast<int8>(_MyselfClass::GetAsInt32());
	}
	int16 GetAsInt16(void) const
	{
		return static_cast<int16>(_MyselfClass::GetAsInt32());
	}
	int GetAsInt32(void) const
	{
		int nValue = 0;
		sscanf(_MyselfClass::GetCText(), "%d", &nValue);
		return nValue;
	}

	uint8 GetAsUInt8(void) const
	{
		return static_cast<uint8>(_MyselfClass::GetAsUInt32());
	}
	uint16 GetAsUInt16(void) const
	{
		return static_cast<uint16>(_MyselfClass::GetAsUInt32());
	}
	uint32 GetAsUInt32(void) const
	{
		uint32 nValue = 0;
		sscanf(_MyselfClass::GetCText(), "%u", &nValue);
		return nValue;
	}
};

#endif
