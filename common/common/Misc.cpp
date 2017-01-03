#include "Misc.h"

#if defined(_WIN32)
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")
#else
#include <dirent.h>
#endif

void _localtime(const time_t &t1,tm &t2)
{
#if defined(_WIN32)
	tm* pt = localtime(&t1);
	if (pt !=0)
	{
		t2 = *pt;
	}
#else
	tm ltm;
	localtime_r(&t1,&ltm);
	memcpy(&t2,&ltm,sizeof(tm));
#endif
}
time_t _ansitime(void)
{
	time_t t;
	time(&t);
	return t;
}

void   _Sleep(uint32 nMilSec)\
{
#if defined(_WIN32)
	Sleep(nMilSec);
#else
	usleep(nMilSec*1000);
#endif
}

bool IsFileExists(const char* szFilePath)
{
	__ENTER_FUNCTION
		if (szFilePath != nullptr)
		{
			FILE *fp = fopen(szFilePath,"r");
			if (fp != null_ptr)
			{
				fclose(fp);
				return true;
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool IsFolderExists(const char* szFolderPath)
{
	__ENTER_FUNCTION
#if defined(_WIN32)
	return (::PathFileExists(szFolderPath)?true:false);
#else
	DIR* dir = opendir(szFolderPath);
	if (dir != null_ptr)
	{
		closedir(dir);
		return true;
	}
	else
	{
		return false;
	}
#endif
	__LEAVE_FUNCTION
		return false;
}
bool InitFolder(const char* szFolderPath)
{
	__ENTER_FUNCTION
		if (IsFolderExists(szFolderPath))
		{
			return true;
		}
		else
		{
	#if defined(_WIN32)
			if (_mkdir(szFolderPath) == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
	#else
	if (mkdir(szFolderPath,0755) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
#endif
		}
	__LEAVE_FUNCTION
		return false;
}

bool StrSafeCheck(const char* pIn,uint32 InLength)
{
	if(InLength==0 || !pIn)
	{
		return false;
	}
	for(tuint32 i = 0 ;i<InLength;i++)
	{
		switch(pIn[i]) 
		{
		case '\0':
			{
				return true;
				break;
			}
		case '\'':
		case '\"':
		case ')':
		case '(':
		case '=':
		case '%':
			{
				return false;
			}
		}
	}

	return true;
}
void ToUpper(const char* src,char* dst,int len)
{
	
}
const std::string gXorKey("1E95A51FD4C38CD");

void _XOR(char* pContent,uint32 nSize)
{
	AssertEx(pContent != null_ptr,"");
	AssertEx(nSize>0,"");
	uint32 nXorKeySize = static_cast<uint32>(gXorKey.length());
	AssertEx(nXorKeySize > 0,"");
	for (uint32 i=0;i < nSize;i++)
	{
		pContent[i] ^= gXorKey[i % nXorKeySize];
	}
}

void XorEncrypt(char* pContent,uint32 nSize)
{
	_XOR(pContent,nSize);
}
void XorDecrypt(char* pContent,uint32 nSize)
{
	_XOR(pContent,nSize);
}
