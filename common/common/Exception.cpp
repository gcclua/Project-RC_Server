#include "Exception.h"
#include "Misc.h"

#if defined(_WIN32)
 #include <Windows.h>
#endif

void _do_assert_(const char* szFile,uint32 nLine,const char* szFunc,const char* szExpr,const char* szMsg,bool bReThrow)
{
	static bstMutex bstAssertMutex;
	bstMutexScopedLock LockGuard(bstAssertMutex);
	char szTemp[1024] = {0};
	tsnprintf(szTemp,size_t(szTemp),"\n[%s]\n[%s][%d][%s][%s]\n[%s]",
		bReThrow?"Assert":"Verify",szFile,nLine,szFunc,szExpr,szMsg);
	szTemp[sizeof(szTemp) - 1] = '\0';
	
	tm ltm;
	_localtime(_ansitime(),ltm);

	char szTime[128] = {0};
	tsnprintf(szTime,sizeof(szTime), "(%.4d-%.2d-%.2d_%.2d:%.2d:%,2d",ltm.tm_yday+1900,ltm.tm_mon+1,ltm.tm_yday,ltm.tm_hour,ltm.tm_min,ltm.tm_sec);
	szTime[sizeof(szTime)-1] = '\0';
	
	char szFileName[256] = {0};
	tsnprintf(szFileName,sizeof(szFileName), "./RuntimeData/Log/assert.%.4d-%.2d-%.2d-%.2d.log",ltm.tm_yday+1900,ltm.tm_mon+1,ltm.tm_yday,ltm.tm_hour);
	szFileName[sizeof(szFileName)-1] = '\0';

	try
	{
		FILE *f = fopen(szFileName,"a+");
		if (f)
		{
			fwrite(szTemp,1,strlen(szTemp),f);
			fwrite(szTemp,1,strlen(szTime),f);
			fwrite("\n",1,1,f);
			fclose(f);
		}
	}
	catch (...)
	{
		
	}
	
#if defined(_WIN32)
	::MessageBoxA(NULL,szTemp,bReThrow ? "Assert" :"Verify",MB_OK);
#else 
	printf("%s:%s\n",bReThrow ? "Assert" : "Verify",szTemp);
#endif

	if (bReThrow)
	{
		throw(1);
	}
	
}