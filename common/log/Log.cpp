#include "Log.h"
#include "LogDefine.h"

static const tchar* format_string = "cCdiouxXeEfgGaAnpsS";

StringParser::StringParser(tchar* buf, tint32 size, const tchar* fmt)
	: m_pBuffer(buf), m_BufLen(size),m_pFmt(fmt)
{
	m_FmtLen = (tint32)strlen(fmt);
	m_BufPos = 0;
	m_FmtPos = 0;
	m_FmtIndex = 0;
}

const tchar* StringParser::ParseToNextFormat(void)
{
	__ENTER_FUNCTION
		tint32 len = m_FmtLen;
		for (tint32 i=m_FmtPos; i < len; ++i)
		{
			if (m_pFmt[i] == '%')
			{
				if (i+1 < len && m_pFmt[i + 1] == '%')
				{
					++i;
					if (m_BufPos < m_BufLen - 1)
					{
						m_pBuffer[m_BufPos] = m_pFmt[i];
						++m_BufPos;
					}
					else
					{
						break;
					}
				}
				else
				{
					++m_FmtIndex;
					for (tint32 j=i; j<len;++j)
					{
						m_TempFmt[j-i] = m_pFmt[j];
						const tchar* p = strchr(format_string,m_pFmt[j]);
						if (p != null_ptr)
						{
							m_FmtPos = j + 1;
							m_TempFmt[j-i+1]=0;
							return m_TempFmt;
						}
					}
					break;
				}
			}
			else
			{
				if (m_BufPos < m_BufLen - 1)
				{
					m_pBuffer[m_BufPos] = m_pFmt[i];
					++m_BufPos;
				}
				else
				{
					break;
				}
			}
		}
		m_FmtPos = len;
		return null_ptr;
	__LEAVE_FUNCTION
		return null_ptr;
}

void StringParser::ParseToEnd(void)
{
	__ENTER_FUNCTION
		tint32 len = m_FmtLen;
	for (tint32 i = m_FmtPos; i < len; i++)
	{
		if (m_pFmt[i] == '%')
		{
			if (i+1<len && m_pFmt[i+1] == '%')
			{
				++i;
				if (m_BufPos < m_BufLen -1)
				{
					m_pBuffer[m_BufPos] = m_pFmt[i];
					++m_BufPos;
				}
				else
				{
					break;
				}
			}
			else
			{
				++m_FmtIndex;
				for (tint32 j=i;j<len; ++j)
				{
					const tchar* p = strchr(format_string,m_pFmt[j]);
					if (p != null_ptr)
					{
						if (false == StringFormatUtility::BasicValue2String(m_pBuffer,m_BufPos,m_BufLen,"@format:%d,unexpected_format ",m_FmtIndex - 1))
						{
							m_FmtPos = len;
							return;
						}
						i=j;
						break;
					}
				}
			}
		}
		else
		{
			if (m_BufPos < m_BufLen - 1)
			{
				m_pBuffer[m_BufPos] = m_pFmt[i];
				++m_BufPos;
			}
			else
			{
				break;
			}
		}
	}

	m_FmtPos = len;
	if (m_BufPos < m_BufLen - 1)
	{
		m_pBuffer[m_BufPos] = '\0';
	}
	else if (m_BufLen > 0)
	{
		m_pBuffer[m_BufLen-1] = '\0';
	}

	__LEAVE_FUNCTION
}