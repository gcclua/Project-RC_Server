#ifndef _LOG_H_
#define _LOG_H_

#include "Exception.h"
#include "FLString.h"

class LogFormatType
{
public:
	enum
	{
		NORMAL = 0,
		AUDIT,
		CMBI,
	};
};

template<tint32 _BufSize>
class LogSink
{
public:
	enum
	{
		LOGNAME_MAXSIZE = 64,
		TIMETAIL_MAXSIZE = 128,
		FILEPATH_MAXSIZE = 256,
		SINGLELOG_MAXSIZE = 4096,
		WORLDID_DEFAULT = 65535,
	};

public:
	typedef LogSink<_BufSize> _MyselfClass;

public:
	explicit LogSink<_BufSize>(const tchar* szLogName, tint32 nLogFormatType)
	{
		m_szLogName = szLogName;
		m_nLogFormatType = nLogFormatType;
		m_nWorldID = 1;
		RebuildFilePath();
	}
	~LogSink<_BufSize>(void)
	{
		Flush();
	}

public:
	void Init(tint32 nWorldID)
	{
		__ENTER_FUNCTION

		m_nWorldID = nWorldID;
		RebuildFilePath();

		__LEAVE_FUNCTION
	}

	void Log(const tchar* szLog, bool bFlush)
	{
		__ENTER_FUNCTION

		bstMutexScopedLock LockGuard(m_bstMutex);
		if (szLog != null_ptr)
		{
			if ((m_szBuf.GetLength() + SINGLELOG_MAXSIZE) >= _BufSize)
			{
				FlushWithoutLock();
			}

			tm ltm;
			_localtime(_ansitime(), ltm);

			tchar szTime[TIMETAIL_MAXSIZE] = {0};
			//////////////////////////////////////////////////////////////////////////
			switch (m_nLogFormatType)
			{
			case LogFormatType::NORMAL:
				{
					tsnprintf(szTime, sizeof(szTime),
						" (%.4d-%.2d-%.2d_%.2d:%.2d:%.2d)\n",
						ltm.tm_year+1900,
						ltm.tm_mon+1,
						ltm.tm_mday,
						ltm.tm_hour,
						ltm.tm_min,
						ltm.tm_sec);
				}
				break;
			case LogFormatType::AUDIT:
				{
					tsnprintf(szTime, sizeof(szTime),
						" \1 (%.4d-%.2d-%.2d_%.2d:%.2d:%.2d)\n",
						ltm.tm_year+1900,
						ltm.tm_mon+1,
						ltm.tm_mday,
						ltm.tm_hour,
						ltm.tm_min,
						ltm.tm_sec);
				}
				break;
			case LogFormatType::CMBI:
				{
					tsnprintf(szTime, sizeof(szTime),
						"%.4d-%.2d-%.2d %.2d:%.2d:%.2d\1",
						ltm.tm_year+1900,
						ltm.tm_mon+1,
						ltm.tm_mday,
						ltm.tm_hour,
						ltm.tm_min,
						ltm.tm_sec);
				}
				break;
			default:
				{
					AssertEx(false, "");
				}
				break;
			}
			//////////////////////////////////////////////////////////////////////////
			szTime[sizeof(szTime) - 1] = '\0';

			FLString<SINGLELOG_MAXSIZE> szTemp;
			//////////////////////////////////////////////////////////////////////////
			switch (m_nLogFormatType)
			{
			case LogFormatType::NORMAL:
			case LogFormatType::AUDIT:
				{
					szTemp += szLog;
					szTemp += szTime;
				}
				break;
			case LogFormatType::CMBI:
				{
					szTemp += szTime;
					szTemp += szLog;
					szTemp += "\n";
				}
				break;
			default:
				{
					AssertEx(false, "");
				}
				break;
			}
			//////////////////////////////////////////////////////////////////////////

			m_szBuf += szTemp;

			#if defined(__WINDOWS__)
			printf(szTemp.GetCText());
			#endif

			if (bFlush)
			{
				FlushWithoutLock();
			}
		}

		__LEAVE_FUNCTION
	}

	void Flush(void)
	{
		bstMutexScopedLock LockGuard(m_bstMutex);
		FlushWithoutLock();
	}

	void RebuildFilePath(void)
	{
		__ENTER_FUNCTION

		bstMutexScopedLock LockGuard(m_bstMutex);
		tm ltm;
		_localtime(_ansitime(), ltm);

		tchar szFilePath[FILEPATH_MAXSIZE] = {0};
		//////////////////////////////////////////////////////////////////////////
		switch (m_nLogFormatType)
		{
		case LogFormatType::NORMAL:
		case LogFormatType::AUDIT:
			{
				tsnprintf(szFilePath, sizeof(szFilePath),
					"./RuntimeData/%d/Log/%s.%.4d-%.2d-%.2d-%.2d.log",
					m_nWorldID,
					m_szLogName.GetCText(),
					ltm.tm_year+1900,
					ltm.tm_mon+1,
					ltm.tm_mday,
					ltm.tm_hour);
			}
			break;
		case LogFormatType::CMBI:
			{
				tsnprintf(szFilePath, sizeof(szFilePath),
					"./RuntimeData/%d/Log/%s.log.%.4d-%.2d-%.2d-%.2d",
					m_nWorldID,
					m_szLogName.GetCText(),
					ltm.tm_year+1900,
					ltm.tm_mon+1,
					ltm.tm_mday,
					ltm.tm_hour);
			}
			break;
		default:
			{
				AssertEx(false, "");
			}
			break;
		}
		//////////////////////////////////////////////////////////////////////////
		szFilePath[sizeof(szFilePath) - 1] = '\0';
		m_szFilePath = szFilePath;

		__LEAVE_FUNCTION
	}

private:
	void FlushWithoutLock(void)
	{
		__ENTER_PROTECT

		if (m_szBuf.GetLength() > 0)
		{
			FILE *f = fopen(m_szFilePath.GetCText(), "a+");
			if(f)
			{
				fwrite(m_szBuf.GetCText(), 1, m_szBuf.GetLength(), f);
				fclose(f);
			}
			m_szBuf.CleanUp();
		}

		__LEAVE_PROTECT
	}

private:
	bstMutex m_bstMutex;

	tint32 m_nWorldID;
	FLString<LOGNAME_MAXSIZE> m_szLogName;
	FLString<FILEPATH_MAXSIZE> m_szFilePath;
	FLString<_BufSize> m_szBuf;

	tint32 m_nLogFormatType;
};

namespace StringFormatUtility
{
	template<typename T>
	inline bool BasicValue2String(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T t)
	{
		if(pos >= size - 1)
		{
			return false;
		}
			
		tint32 r = tsnprintf(dest + pos, size - pos, fmt, t);
		if(r >= 0 && pos + r < size)
		{
			pos += r;
		}
		else
		{
			pos = size - 1;
		}
		return (r >= 0 ? true : false);
	}

	template<typename T>
	struct _impl_for_format_check
	{
		enum
		{
			value = 0
		};
		static inline bool format(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T t, tint32 argIndex)
		{
			tint32 len = (tint32)::strlen(fmt);
			if(len <= 0)
			{
				return BasicValue2String(dest, pos, size, " @format:%d,unexpected_value ", argIndex);
			}
			else if(fmt[len - 1] == 's' || fmt[len - 1] == 'S' || fmt[len - 1] == 'n' || fmt[len - 1] == 'p')
			{
				return BasicValue2String(dest, pos, size, " @format:%d,value_as_pointer ", argIndex);
			}
			else
			{
				return BasicValue2String(dest, pos, size, fmt, t);
			}
		}
	};

	template<typename T>
	struct _impl_for_format_check<T*>
	{
		enum
		{
			value = 1
		};
		static inline bool format(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T *t, tint32 argIndex)
		{
			tint32 len = (tint32)::strlen(fmt);
			if(len <= 0)
			{
				return BasicValue2String(dest, pos, size, " @format:%d,unexpected_pointer ", argIndex);
			}
			else if(fmt[len - 1] != 's' && fmt[len - 1] != 'S' && fmt[len - 1] != 'n' && fmt[len - 1] != 'p')
			{
				return BasicValue2String(dest, pos, size, " @format:%d,pointer_as_value ", argIndex);
			}
			else
			{
				return BasicValue2String(dest, pos, size, fmt, t);
			}
		}
	};

	template<typename T>
	inline bool GeneralValue2String(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T t, tint32 argIndex)
	{
		return _impl_for_format_check<T>::format(dest, pos, size, fmt, t, argIndex);
	}

	template<typename T,tint32 k>
	struct _impl_for_64
	{
		static inline bool format(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T t, tint32 argIndex)
		{
			return GeneralValue2String(dest, pos, size, fmt, t, argIndex);
		}
	};

	template<typename T>
	struct _impl_for_64<T,8>
	{
		static inline bool format(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T t, tint32 argIndex)
		{
			if(pos >= size - 1)
			{
				return false;
			}

			tuint64 val;
			memcpy(&val, &t, sizeof(val));

			tint32 r = 0;
			tint32 len = static_cast<tint32>(strlen(fmt));
			if(len <= 0)
			{
				return BasicValue2String(dest, pos, size, " @format:%d,unexpected_value ", argIndex);
			}
			else if(fmt[len - 1] == 's' || fmt[len - 1] == 'S' || fmt[len - 1] == 'n' || fmt[len - 1] == 'p')
			{
				return BasicValue2String(dest, pos, size, " @format:%d,value_as_pointer ", argIndex);
			}
			else if(fmt[len - 1] == 'x' || fmt[len - 1] == 'X')
			{
				r = tsnprintf(dest + pos, size - pos, "%16.16llX", val);	
			}
			else if(fmt[len - 1] == 'u')
			{
				r = tsnprintf(dest + pos, size - pos, "%llu", val);
			}
			else if(fmt[len - 1] == 'o')
			{
				r = tsnprintf(dest + pos, size - pos, "%llo", val);
			}
			else if(fmt[len - 1] == 'i')
			{
				r = tsnprintf(dest + pos, size - pos, "%lli", val);
			}
			else
			{
				r = tsnprintf(dest + pos, size - pos, "%lld", (tint64)val);
			}
			if(r >= 0 && pos + r < size)
			{
				pos += r;
			}
			else
			{
				pos = size - 1;
			}
			return (r >= 0 ? true : false);
		}
	};

	template<typename T>
	struct _impl_for_64<T*,8>
	{
		static inline bool format(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T *t, tint32 argIndex)
		{
			return GeneralValue2String(dest, pos, size, fmt, t, argIndex);
		}
	};

	template<>
	struct _impl_for_64<tfloat64,8>
	{
		static inline bool format(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, tfloat64 t, tint32 argIndex)
		{
			tint32 len = static_cast<tint32>(strlen(fmt));
			if(len <= 0)
			{
				return BasicValue2String(dest, pos, size, " @format:%d,unexpected_value ", argIndex);
			}
			else if(fmt[len - 1] == 'f' || fmt[len - 1] == 'e' || fmt[len - 1] == 'E' || fmt[len - 1] == 'g' || fmt[len - 1] == 'G' || fmt[len - 1] == 'a' || fmt[len - 1] == 'A')
			{
				return BasicValue2String(dest, pos, size, fmt, t);
			}
			else
			{
				return BasicValue2String(dest, pos, size, "%f", t);
			}
		}
	};

	template<typename T>
	inline bool Value2String(tchar* dest, tint32 &pos, tint32 size, const tchar* fmt, T t, tint32 argIndex)
	{
		return _impl_for_64<T,sizeof(T)>::format(dest, pos, size, fmt, t, argIndex);
	}
}

#define ParserRepeatArg1_1(X) X##1
#define ParserRepeatArg1_2(X) ParserRepeatArg1_1(X),X##2
#define ParserRepeatArg1_3(X) ParserRepeatArg1_2(X),X##3
#define ParserRepeatArg1_4(X) ParserRepeatArg1_3(X),X##4
#define ParserRepeatArg1_5(X) ParserRepeatArg1_4(X),X##5
#define ParserRepeatArg1_6(X) ParserRepeatArg1_5(X),X##6
#define ParserRepeatArg1_7(X) ParserRepeatArg1_6(X),X##7
#define ParserRepeatArg1_8(X) ParserRepeatArg1_7(X),X##8
#define ParserRepeatArg1_9(X) ParserRepeatArg1_8(X),X##9
#define ParserRepeatArg1_10(X) ParserRepeatArg1_9(X),X##10
#define ParserRepeatArg1_11(X) ParserRepeatArg1_10(X),X##11
#define ParserRepeatArg1_12(X) ParserRepeatArg1_11(X),X##12
#define ParserRepeatArg1_13(X) ParserRepeatArg1_12(X),X##13
#define ParserRepeatArg1_14(X) ParserRepeatArg1_13(X),X##14
#define ParserRepeatArg1_15(X) ParserRepeatArg1_14(X),X##15
#define ParserRepeatArg1_16(X) ParserRepeatArg1_15(X),X##16
#define ParserRepeatArg1_17(X) ParserRepeatArg1_16(X),X##17
#define ParserRepeatArg1_18(X) ParserRepeatArg1_17(X),X##18
#define ParserRepeatArg1_19(X) ParserRepeatArg1_18(X),X##19
#define ParserRepeatArg1_20(X) ParserRepeatArg1_19(X),X##20
#define ParserRepeatArg1_21(X) ParserRepeatArg1_20(X),X##21
#define ParserRepeatArg1_22(X) ParserRepeatArg1_21(X),X##22
#define ParserRepeatArg1_23(X) ParserRepeatArg1_22(X),X##23
#define ParserRepeatArg1_24(X) ParserRepeatArg1_23(X),X##24
#define ParserRepeatArg1_25(X) ParserRepeatArg1_24(X),X##25
#define ParserRepeatArg1_26(X) ParserRepeatArg1_25(X),X##26
#define ParserRepeatArg1_27(X) ParserRepeatArg1_26(X),X##27
#define ParserRepeatArg1_28(X) ParserRepeatArg1_27(X),X##28
#define ParserRepeatArg1_29(X) ParserRepeatArg1_28(X),X##29
#define ParserRepeatArg1_30(X) ParserRepeatArg1_29(X),X##30
#define ParserRepeatArg1_31(X) ParserRepeatArg1_30(X),X##31
#define ParserRepeatArg1_32(X) ParserRepeatArg1_31(X),X##32
#define ParserRepeatArg1_33(X) ParserRepeatArg1_32(X),X##33
#define ParserRepeatArg1_34(X) ParserRepeatArg1_33(X),X##34
#define ParserRepeatArg1_35(X) ParserRepeatArg1_34(X),X##35
#define ParserRepeatArg1_36(X) ParserRepeatArg1_35(X),X##36
#define ParserRepeatArg1_37(X) ParserRepeatArg1_36(X),X##37
#define ParserRepeatArg1_38(X) ParserRepeatArg1_37(X),X##38
#define ParserRepeatArg1_39(X) ParserRepeatArg1_38(X),X##39
#define ParserRepeatArg1_40(X) ParserRepeatArg1_39(X),X##40
#define ParserRepeatArg1_41(X) ParserRepeatArg1_40(X),X##41
#define ParserRepeatArg1_42(X) ParserRepeatArg1_41(X),X##42
#define ParserRepeatArg1_43(X) ParserRepeatArg1_42(X),X##43
#define ParserRepeatArg1_44(X) ParserRepeatArg1_43(X),X##44
#define ParserRepeatArg1_45(X) ParserRepeatArg1_44(X),X##45

#define ParserRepeatArg2_1(X,Y) X##1 Y##1
#define ParserRepeatArg2_2(X,Y) ParserRepeatArg2_1(X,Y),X##2 Y##2
#define ParserRepeatArg2_3(X,Y) ParserRepeatArg2_2(X,Y),X##3 Y##3
#define ParserRepeatArg2_4(X,Y) ParserRepeatArg2_3(X,Y),X##4 Y##4
#define ParserRepeatArg2_5(X,Y) ParserRepeatArg2_4(X,Y),X##5 Y##5
#define ParserRepeatArg2_6(X,Y) ParserRepeatArg2_5(X,Y),X##6 Y##6
#define ParserRepeatArg2_7(X,Y) ParserRepeatArg2_6(X,Y),X##7 Y##7
#define ParserRepeatArg2_8(X,Y) ParserRepeatArg2_7(X,Y),X##8 Y##8
#define ParserRepeatArg2_9(X,Y) ParserRepeatArg2_8(X,Y),X##9 Y##9
#define ParserRepeatArg2_10(X,Y) ParserRepeatArg2_9(X,Y),X##10 Y##10
#define ParserRepeatArg2_11(X,Y) ParserRepeatArg2_10(X,Y),X##11 Y##11
#define ParserRepeatArg2_12(X,Y) ParserRepeatArg2_11(X,Y),X##12 Y##12
#define ParserRepeatArg2_13(X,Y) ParserRepeatArg2_12(X,Y),X##13 Y##13
#define ParserRepeatArg2_14(X,Y) ParserRepeatArg2_13(X,Y),X##14 Y##14
#define ParserRepeatArg2_15(X,Y) ParserRepeatArg2_14(X,Y),X##15 Y##15
#define ParserRepeatArg2_16(X,Y) ParserRepeatArg2_15(X,Y),X##16 Y##16
#define ParserRepeatArg2_17(X,Y) ParserRepeatArg2_16(X,Y),X##17 Y##17
#define ParserRepeatArg2_18(X,Y) ParserRepeatArg2_17(X,Y),X##18 Y##18
#define ParserRepeatArg2_19(X,Y) ParserRepeatArg2_18(X,Y),X##19 Y##19
#define ParserRepeatArg2_20(X,Y) ParserRepeatArg2_19(X,Y),X##20 Y##20
#define ParserRepeatArg2_21(X,Y) ParserRepeatArg2_20(X,Y),X##21 Y##21
#define ParserRepeatArg2_22(X,Y) ParserRepeatArg2_21(X,Y),X##22 Y##22
#define ParserRepeatArg2_23(X,Y) ParserRepeatArg2_22(X,Y),X##23 Y##23
#define ParserRepeatArg2_24(X,Y) ParserRepeatArg2_23(X,Y),X##24 Y##24
#define ParserRepeatArg2_25(X,Y) ParserRepeatArg2_24(X,Y),X##25 Y##25
#define ParserRepeatArg2_26(X,Y) ParserRepeatArg2_25(X,Y),X##26 Y##26
#define ParserRepeatArg2_27(X,Y) ParserRepeatArg2_26(X,Y),X##27 Y##27
#define ParserRepeatArg2_28(X,Y) ParserRepeatArg2_27(X,Y),X##28 Y##28
#define ParserRepeatArg2_29(X,Y) ParserRepeatArg2_28(X,Y),X##29 Y##29
#define ParserRepeatArg2_30(X,Y) ParserRepeatArg2_29(X,Y),X##30 Y##30
#define ParserRepeatArg2_31(X,Y) ParserRepeatArg2_30(X,Y),X##31 Y##31
#define ParserRepeatArg2_32(X,Y) ParserRepeatArg2_31(X,Y),X##32 Y##32
#define ParserRepeatArg2_33(X,Y) ParserRepeatArg2_32(X,Y),X##33 Y##33
#define ParserRepeatArg2_34(X,Y) ParserRepeatArg2_33(X,Y),X##34 Y##34
#define ParserRepeatArg2_35(X,Y) ParserRepeatArg2_34(X,Y),X##35 Y##35
#define ParserRepeatArg2_36(X,Y) ParserRepeatArg2_35(X,Y),X##36 Y##36
#define ParserRepeatArg2_37(X,Y) ParserRepeatArg2_36(X,Y),X##37 Y##37
#define ParserRepeatArg2_38(X,Y) ParserRepeatArg2_37(X,Y),X##38 Y##38
#define ParserRepeatArg2_39(X,Y) ParserRepeatArg2_38(X,Y),X##39 Y##39
#define ParserRepeatArg2_40(X,Y) ParserRepeatArg2_39(X,Y),X##40 Y##40
#define ParserRepeatArg2_41(X,Y) ParserRepeatArg2_40(X,Y),X##41 Y##41
#define ParserRepeatArg2_42(X,Y) ParserRepeatArg2_41(X,Y),X##42 Y##42
#define ParserRepeatArg2_43(X,Y) ParserRepeatArg2_42(X,Y),X##43 Y##43
#define ParserRepeatArg2_44(X,Y) ParserRepeatArg2_43(X,Y),X##44 Y##44
#define ParserRepeatArg2_45(X,Y) ParserRepeatArg2_44(X,Y),X##45 Y##45

#define DEF_PARSER_FORMAT_IMPL(X,decX) \
template<ParserRepeatArg1_##X(typename P)> \
inline void _Format(ParserRepeatArg2_##X(P,p)) \
{ \
	_Format(ParserRepeatArg1_##decX(p)); \
	const tchar* fmt = ParseToNextFormat(); \
	if(fmt != null_ptr) \
	{ \
		StringFormatUtility::Value2String(m_pBuffer, m_BufPos, m_BufLen, fmt, p##X, decX); \
	} \
	else \
	{ \
		StringFormatUtility::Value2String(m_pBuffer, m_BufPos, m_BufLen, "", p##X, decX); \
	} \
}

#define DEF_PARSER_FORMAT(X) \
template<ParserRepeatArg1_##X(typename P)> \
inline void Format(ParserRepeatArg2_##X(P,p)) \
{\
	_Format(ParserRepeatArg1_##X(p)); \
	ParseToEnd(); \
}

class StringParser
{	
public:
	inline void	Format(void)
	{
		ParseToEnd();
	}
	DEF_PARSER_FORMAT(1);
	DEF_PARSER_FORMAT(2);
	DEF_PARSER_FORMAT(3);
	DEF_PARSER_FORMAT(4);
	DEF_PARSER_FORMAT(5);
	DEF_PARSER_FORMAT(6);
	DEF_PARSER_FORMAT(7);
	DEF_PARSER_FORMAT(8);
	DEF_PARSER_FORMAT(9);
	DEF_PARSER_FORMAT(10);
	DEF_PARSER_FORMAT(11);
	DEF_PARSER_FORMAT(12);
	DEF_PARSER_FORMAT(13);
	DEF_PARSER_FORMAT(14);
	DEF_PARSER_FORMAT(15);
	DEF_PARSER_FORMAT(16);
	DEF_PARSER_FORMAT(17);
	DEF_PARSER_FORMAT(18);
	DEF_PARSER_FORMAT(19);
	DEF_PARSER_FORMAT(20);
	DEF_PARSER_FORMAT(21);
	DEF_PARSER_FORMAT(22);
	DEF_PARSER_FORMAT(23);
	DEF_PARSER_FORMAT(24);
	DEF_PARSER_FORMAT(25);
	DEF_PARSER_FORMAT(26);
	DEF_PARSER_FORMAT(27);
	DEF_PARSER_FORMAT(28);
	DEF_PARSER_FORMAT(29);
	DEF_PARSER_FORMAT(30);
	DEF_PARSER_FORMAT(31);
	DEF_PARSER_FORMAT(32);
	DEF_PARSER_FORMAT(33);
	DEF_PARSER_FORMAT(34);
	DEF_PARSER_FORMAT(35);
	DEF_PARSER_FORMAT(36);
	DEF_PARSER_FORMAT(37);
	DEF_PARSER_FORMAT(38);
	DEF_PARSER_FORMAT(39);
	DEF_PARSER_FORMAT(40);
	DEF_PARSER_FORMAT(41);
	DEF_PARSER_FORMAT(42);
	DEF_PARSER_FORMAT(43);
	DEF_PARSER_FORMAT(44);
	DEF_PARSER_FORMAT(45);

public:
	StringParser(tchar* buf, tint32 size, const tchar* fmt);
	inline tint32 GetLength(void) const
	{
		return m_BufPos;
	}

private:
	template<typename P1>
	inline void	_Format(P1 p1)
	{
		const tchar* fmt = ParseToNextFormat();
		if(fmt != null_ptr)
		{
			StringFormatUtility::Value2String(m_pBuffer, m_BufPos, m_BufLen, fmt, p1, 0);
		}
		else
		{
			StringFormatUtility::Value2String(m_pBuffer, m_BufPos, m_BufLen, "", p1, 0);
		}
	};
	DEF_PARSER_FORMAT_IMPL(2,1);
	DEF_PARSER_FORMAT_IMPL(3,2);
	DEF_PARSER_FORMAT_IMPL(4,3);
	DEF_PARSER_FORMAT_IMPL(5,4);
	DEF_PARSER_FORMAT_IMPL(6,5);
	DEF_PARSER_FORMAT_IMPL(7,6);
	DEF_PARSER_FORMAT_IMPL(8,7);
	DEF_PARSER_FORMAT_IMPL(9,8);
	DEF_PARSER_FORMAT_IMPL(10,9);
	DEF_PARSER_FORMAT_IMPL(11,10);
	DEF_PARSER_FORMAT_IMPL(12,11);
	DEF_PARSER_FORMAT_IMPL(13,12);
	DEF_PARSER_FORMAT_IMPL(14,13);
	DEF_PARSER_FORMAT_IMPL(15,14);
	DEF_PARSER_FORMAT_IMPL(16,15);
	DEF_PARSER_FORMAT_IMPL(17,16);
	DEF_PARSER_FORMAT_IMPL(18,17);
	DEF_PARSER_FORMAT_IMPL(19,18);
	DEF_PARSER_FORMAT_IMPL(20,19);
	DEF_PARSER_FORMAT_IMPL(21,20);
	DEF_PARSER_FORMAT_IMPL(22,21);
	DEF_PARSER_FORMAT_IMPL(23,22);
	DEF_PARSER_FORMAT_IMPL(24,23);
	DEF_PARSER_FORMAT_IMPL(25,24);
	DEF_PARSER_FORMAT_IMPL(26,25);
	DEF_PARSER_FORMAT_IMPL(27,26);
	DEF_PARSER_FORMAT_IMPL(28,27);
	DEF_PARSER_FORMAT_IMPL(29,28);
	DEF_PARSER_FORMAT_IMPL(30,29);
	DEF_PARSER_FORMAT_IMPL(31,30);
	DEF_PARSER_FORMAT_IMPL(32,31);
	DEF_PARSER_FORMAT_IMPL(33,32);
	DEF_PARSER_FORMAT_IMPL(34,33);
	DEF_PARSER_FORMAT_IMPL(35,34);
	DEF_PARSER_FORMAT_IMPL(36,35);
	DEF_PARSER_FORMAT_IMPL(37,36);
	DEF_PARSER_FORMAT_IMPL(38,37);
	DEF_PARSER_FORMAT_IMPL(39,38);
	DEF_PARSER_FORMAT_IMPL(40,39);
	DEF_PARSER_FORMAT_IMPL(41,40);
	DEF_PARSER_FORMAT_IMPL(42,41);
	DEF_PARSER_FORMAT_IMPL(43,42);
	DEF_PARSER_FORMAT_IMPL(44,43);
	DEF_PARSER_FORMAT_IMPL(45,44);

private:
	const tchar* ParseToNextFormat(void);
	void ParseToEnd(void);

private:
	tchar* m_pBuffer;
	const tchar* m_pFmt;
	tchar m_TempFmt[4096];
	tint32 m_BufPos;
	tint32 m_FmtPos;
	tint32 m_FmtIndex;
	tint32 m_BufLen;
	tint32 m_FmtLen;
};

template<typename _LogSink>
inline void CacheLog(_LogSink &rLogSink, const tchar* szLog)
{
	rLogSink.Log(szLog, false);
}

#define DEF_CACHELOG(X) \
template<typename _LogSink, ParserRepeatArg1_##X(typename P)> \
inline void CacheLog(_LogSink &rLogSink, const tchar* szLog, ParserRepeatArg2_##X(P,p)) \
{ \
	tchar szBuff[4096] = {0}; \
	StringParser log(szBuff, sizeof(szBuff), szLog); \
	log.Format(ParserRepeatArg1_##X(p)); \
	szBuff[sizeof(szBuff) - 1] = '\0'; \
	rLogSink.Log(szBuff, false); \
}

DEF_CACHELOG(1);
DEF_CACHELOG(2);
DEF_CACHELOG(3);
DEF_CACHELOG(4);
DEF_CACHELOG(5);
DEF_CACHELOG(6);
DEF_CACHELOG(7);
DEF_CACHELOG(8);
DEF_CACHELOG(9);
DEF_CACHELOG(10);
DEF_CACHELOG(11);
DEF_CACHELOG(12);
DEF_CACHELOG(13);
DEF_CACHELOG(14);
DEF_CACHELOG(15);
DEF_CACHELOG(16);
DEF_CACHELOG(17);
DEF_CACHELOG(18);
DEF_CACHELOG(19);
DEF_CACHELOG(20);
DEF_CACHELOG(21);
DEF_CACHELOG(22);
DEF_CACHELOG(23);
DEF_CACHELOG(24);
DEF_CACHELOG(25);
DEF_CACHELOG(26);
DEF_CACHELOG(27);
DEF_CACHELOG(28);
DEF_CACHELOG(29);
DEF_CACHELOG(30);
DEF_CACHELOG(31);
DEF_CACHELOG(32);
DEF_CACHELOG(33);
DEF_CACHELOG(34);
DEF_CACHELOG(35);
DEF_CACHELOG(36);
DEF_CACHELOG(37);
DEF_CACHELOG(38);
DEF_CACHELOG(39);
DEF_CACHELOG(40);
DEF_CACHELOG(41);
DEF_CACHELOG(42);
DEF_CACHELOG(43);
DEF_CACHELOG(44);
DEF_CACHELOG(45);

template<typename _LogSink>
inline void DiskLog(_LogSink &rLogSink, const tchar* szLog)
{
	rLogSink.Log(szLog, true);
}

#define DEF_DISKLOG(X) \
template<typename _LogSink, ParserRepeatArg1_##X(typename P)> \
inline void DiskLog(_LogSink &rLogSink, const tchar* szLog, ParserRepeatArg2_##X(P,p)) \
{ \
	tchar szBuff[4096] = {0}; \
	StringParser log(szBuff, sizeof(szBuff), szLog); \
	log.Format(ParserRepeatArg1_##X(p)); \
	szBuff[sizeof(szBuff) - 1] = '\0'; \
	rLogSink.Log(szBuff, true); \
}

DEF_DISKLOG(1);
DEF_DISKLOG(2);
DEF_DISKLOG(3);
DEF_DISKLOG(4);
DEF_DISKLOG(5);
DEF_DISKLOG(6);
DEF_DISKLOG(7);
DEF_DISKLOG(8);
DEF_DISKLOG(9);
DEF_DISKLOG(10);
DEF_DISKLOG(11);
DEF_DISKLOG(12);
DEF_DISKLOG(13);
DEF_DISKLOG(14);
DEF_DISKLOG(15);
DEF_DISKLOG(16);
DEF_DISKLOG(17);
DEF_DISKLOG(18);
DEF_DISKLOG(19);
DEF_DISKLOG(20);
DEF_DISKLOG(21);
DEF_DISKLOG(22);
DEF_DISKLOG(23);
DEF_DISKLOG(24);
DEF_DISKLOG(25);
DEF_DISKLOG(26);
DEF_DISKLOG(27);
DEF_DISKLOG(28);
DEF_DISKLOG(29);
DEF_DISKLOG(30);
DEF_DISKLOG(31);
DEF_DISKLOG(32);
DEF_DISKLOG(33);
DEF_DISKLOG(34);
DEF_DISKLOG(35);
DEF_DISKLOG(36);
DEF_DISKLOG(37);
DEF_DISKLOG(38);
DEF_DISKLOG(39);
DEF_DISKLOG(40);
DEF_DISKLOG(41);
DEF_DISKLOG(42);
DEF_DISKLOG(43);
DEF_DISKLOG(44);
DEF_DISKLOG(45);

#define LOGDEF_INST(LOGTYPE) \
	g##LOGTYPE##LogSink
#define LOGDEF_DECL(LOGTYPE) \
	extern LogSink<32768> LOGDEF_INST(LOGTYPE)
#define LOGDEF_IMPL(LOGTYPE, LOGFORMATTYPE) \
	LogSink<32768> LOGDEF_INST(LOGTYPE)(#LOGTYPE, LOGFORMATTYPE)
#define LOGDEF_INIT(LOGTYPE, WORLDID) \
	LOGDEF_INST(LOGTYPE).Init(WORLDID)
#define LOGDEF_FLUSH(LOGTYPE) \
	LOGDEF_INST(LOGTYPE).Flush()
#define LOGDEF_REBUILDPATH(LOGTYPE) \
	LOGDEF_INST(LOGTYPE).RebuildFilePath()

inline tint32 tsnprintfex(tchar* buf, size_t size, const tchar* msg)
{
	if(buf == null_ptr || msg == null_ptr || size < 1)
	{
		return 0;
	}
	StringParser fmt(buf, (tint32)size, msg);
	fmt.Format();
	buf[size - 1] = '\0';
	return fmt.GetLength();
}

#define DEF_SNPRINTF(X)	\
template<ParserRepeatArg1_##X(typename P)> \
inline tint32 tsnprintfex(tchar* buf, size_t size, const tchar* msg, ParserRepeatArg2_##X(P,p)) \
{ \
	if(buf == null_ptr || msg == null_ptr || size < 1) \
	{ \
		return 0; \
	} \
	StringParser fmt(buf, (tint32)size, msg); \
	fmt.Format(ParserRepeatArg1_##X(p)); \
	buf[size - 1] = '\0'; \
	return fmt.GetLength(); \
}

DEF_SNPRINTF(1)
DEF_SNPRINTF(2)
DEF_SNPRINTF(3)
DEF_SNPRINTF(4)
DEF_SNPRINTF(5)
DEF_SNPRINTF(6)
DEF_SNPRINTF(7)
DEF_SNPRINTF(8)
DEF_SNPRINTF(9)
DEF_SNPRINTF(10)
DEF_SNPRINTF(11)
DEF_SNPRINTF(12)
DEF_SNPRINTF(13)
DEF_SNPRINTF(14)
DEF_SNPRINTF(15)
DEF_SNPRINTF(16)
DEF_SNPRINTF(17)
DEF_SNPRINTF(18)
DEF_SNPRINTF(19)
DEF_SNPRINTF(20)
DEF_SNPRINTF(21)
DEF_SNPRINTF(22)
DEF_SNPRINTF(23)
DEF_SNPRINTF(24)
DEF_SNPRINTF(25)
DEF_SNPRINTF(26)
DEF_SNPRINTF(27)
DEF_SNPRINTF(28)
DEF_SNPRINTF(29)
DEF_SNPRINTF(30)
DEF_SNPRINTF(31)
DEF_SNPRINTF(32)
DEF_SNPRINTF(33)
DEF_SNPRINTF(34)
DEF_SNPRINTF(35)
DEF_SNPRINTF(36)
DEF_SNPRINTF(37)
DEF_SNPRINTF(38)
DEF_SNPRINTF(39)
DEF_SNPRINTF(40)
DEF_SNPRINTF(41)
DEF_SNPRINTF(42)
DEF_SNPRINTF(43)
DEF_SNPRINTF(44)
DEF_SNPRINTF(45)

//////////////////////////////////////////////////////////////////////////
LOGDEF_DECL(ServerStatus);
LOGDEF_DECL(Efficiency);
LOGDEF_DECL(CpuMem);

#endif
