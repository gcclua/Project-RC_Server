#include "IniFile.h"
#include "Exception.h"

IniFile::IniFile(void)
{
	memset(m_szFileName,0,sizeof(m_szFileName));
	m_nFileSize = 0;
	m_szFileData = null_ptr;
	m_nIndexNum  = 0;
	m_pIndexList = null_ptr;
}

IniFile::~IniFile(void)
{
	SAFE_DELETE_ARRAY(m_pIndexList);
	SAFE_DELETE_ARRAY(m_szFileData);
}

bool IniFile::ReadInt(const tchar* index, const tchar* name, tint32& rResult)
{
	__ENTER_FUNCTION
		tint32 n = FindIndex(index);
		if (n == -1)
		{
			return false;
		}

		tint32 m = FindData(n,name);
		if (m == -1)
		{
			return false;
		}

		tchar szBuff[256];
		if (false == ReadText(m,szBuff,sizeof(szBuff)))
		{
			return false;
		}

		rResult = atoi(szBuff);
		return true;

	__LEAVE_FUNCTION
	return false;
}
bool IniFile::ReadUInt(const tchar* index, const tchar* name, tuint32& rResult)
{
	__ENTER_FUNCTION
		tint32 n = FindIndex(index);
	if (n == -1)
	{
		return false;
	}

	tint32 m = FindData(n,name);
	if (m == -1)
	{
		return false;
	}

	tchar szBuff[256];
	if (false == ReadText(m,szBuff,sizeof(szBuff)))
	{
		return false;
	}

	sscanf(szBuff,"%u",&rResult);
	return true;
	__LEAVE_FUNCTION
	return false;
}
bool IniFile::ReadFloat(const tchar* index, const tchar* name, tfloat32& rResult)
{
	__ENTER_FUNCTION
		tint32 n = FindIndex(index);
	if (n == -1)
	{
		return false;
	}

	tint32 m = FindData(n,name);
	if (m == -1)
	{
		return false;
	}

	tchar szBuff[256];
	if (false == ReadText(m,szBuff,sizeof(szBuff)))
	{
		return false;
	}

	rResult = (tfloat32)atof(szBuff);
	return true;
		__LEAVE_FUNCTION
		return false;
}

bool IniFile::ReadText(const tchar* index, const tchar* name, tchar* str, tint32 size)
{
	__ENTER_FUNCTION
		str[0] = '\0';
		tint32 n = FindIndex(index);
		if (n == -1)
		{
			return false;
		}

		tint32 m = FindData(n,name);
		if (m == -1)
		{
			return false;
		}

		if (false == ReadText(m,str,size))
		{
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

bool IniFile::Open(const tchar* filename)
{
	__ENTER_FUNCTION
	strncpy(m_szFileName,filename,sizeof(m_szFileName)-1);

	FILE * fp;
	fp = fopen(filename,"rb");
	if (fp == 0)
	{
		m_nFileSize = -1;
	}
	else
	{
		fseek(fp,0L,SEEK_END);
		m_nFileSize = ftell(fp);
		fclose(fp);
	}

	if (m_nFileSize > 0)
	{
		SAFE_DELETE_ARRAY(m_szFileData);
		m_szFileData = new tchar[m_nFileSize];
		
		memset(m_szFileData, 0, m_nFileSize);

		FILE* fptr;
		fptr = fopen(filename,"rb");
		if (fptr)
		{
			fread(m_szFileData,m_nFileSize,1,fptr);
			fclose(fptr);

			InitIndex();

			return true;
		}
	}
	return false;
	__LEAVE_FUNCTION
	return false;

}

void IniFile::InitIndex(void)
{
	__ENTER_FUNCTION
		m_nIndexNum = 0;
		
		for (tint32 i = 0; i<m_nFileSize;i++)
		{
			if (m_szFileData[i] == '[')
			{
				if (i == 0 || m_szFileData[i-1] == '\n')
				{
					m_nIndexNum++;
				}
			}
		}

		if (m_nIndexNum > 0)
		{
			SAFE_DELETE_ARRAY(m_pIndexList);
			m_pIndexList = new tint32[m_nIndexNum];
			memset(m_pIndexList,-1,sizeof(tint32) * m_nIndexNum);
		}

		for (tint32 i=0,n=0; i < m_nFileSize; i++)
		{
			if (m_szFileData[i] == '[')
			{
				if (i==0 || m_szFileData[i-1] == '\n')
				{
					m_pIndexList[n++] = i+1;
				}
			}
		}

	__LEAVE_FUNCTION
}

tint32 IniFile::FindIndex(const tchar* string)
{
	__ENTER_FUNCTION
		tchar szBuff[256];
	for (tint32 i = 0; i < m_nIndexNum; i++)
	{
		if (true == ReadText(m_pIndexList[i],szBuff,sizeof(szBuff)))
		{
			if (0 == strncmp(string,szBuff,sizeof(szBuff)))
			{
				return m_pIndexList[i];
			}
		}
	}
	return -1;
	__LEAVE_FUNCTION
		return -1;
}

tint32 IniFile::FindData(tint32 index, const tchar* string)
{
	__ENTER_FUNCTION
		tint32 p = index;
		while (true)
		{
			p = GotoNextLine(p);
			if (p==-1)
			{
				return -1;
			}

			tchar szName[512];
			if (false == ReadDataName(p,szName,sizeof(szName)))
			{
				return -1;
			}

			if (p >= m_nFileSize)
			{
				return -1;
			}

			if (szName[0] == '[')
			{
				return -1;
			}
			if (0 == strncmp(string,szName,sizeof(szName)))
			{
				return p;
			}
		}
		return -1;
	__LEAVE_FUNCTION
		return -1;
}

tint32 IniFile::GotoNextLine(tint32 p)
{
	__ENTER_FUNCTION
	if (0 > p)
	{
		return -1;
	}
	tint32 i;
	 for ( i=p;i < m_nFileSize;i++)
	 {
		 if (m_szFileData[i] == '\n')
		 {
			 return (i+1);
		 }
	 }
	 return i;
	 __LEAVE_FUNCTION
		 return -1;
}

bool IniFile::ReadDataName(tint32 &p, tchar* szBuffer, tint32 nBufferSize)
{
	__ENTER_FUNCTION
		memset(szBuffer,'\0', sizeof(tchar) * nBufferSize);
		for (tint32 i=p,m=0; i < m_nFileSize; i++)
		{
			tchar chr = m_szFileData[i];
			if (chr == '\r')
			{
				p = i+1;
				szBuffer[nBufferSize - 1] = '\0';
				return true;
			}

			if (chr == '=' || chr == ';')
			{
				p = i + 1;
				szBuffer[nBufferSize - 1] = '\0';
				return true;
			}

			szBuffer[m++] = chr;
		}
		return true;
	__LEAVE_FUNCTION
	return true;
}

bool IniFile::ReadText(tint32 p, tchar* pBuffer, tint32 nBufferSize)
{
	__ENTER_FUNCTION
		memset(pBuffer,0,nBufferSize);
		
		tint32 nLineNum = GotoNextLine(p)-p+1;
		if (nLineNum == -1)
		{
			return false;
		}

		tint32 nSize = 0;
		if (nBufferSize > m_nFileSize - p)
		{
			nSize = m_nFileSize - p;
		}
		else
		{
			nSize = nBufferSize;
		}

		for (tint32 i = 0,n = p,m = 0;i<nSize;i++)
		{
			tchar chr = m_szFileData[n];
			
			if (chr == ';' || chr == '\r' || chr == '\t' || chr == ']')
			{
				bool bFind = false;
				if (chr == ']')
				{
					if ((m - 1) >= 0)
					{
						if (pBuffer[m-1] < 0)
						{
							bFind = true;
						}
					}
				}
				
				if (bFind == false)
				{
					pBuffer[nBufferSize - 1] = '\0';
					return true;
				}
			}

			pBuffer[m++] = chr;
			n++;
		}
		pBuffer[nBufferSize - 1] = '\0';
		return true;
	__LEAVE_FUNCTION
	return false;
}