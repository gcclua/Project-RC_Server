
#ifndef _MISC_H_
#define _MISC_H_

#include "BaseType.h"
#include "BaseLib.h"
#include "Exception.h"


void _localtime(const time_t &t1,tm &t2);
time_t _ansitime(void);
void   _Sleep(uint32 nMilSec);

bool IsFileExists(const char* szFilePath);
bool IsFolderExists(const char* szFolderPath);
bool InitFolder(const char* szFolderPath);

bool StrSafeCheck(const char* pIn,uint32 InLength);
void ToUpper(const char* src,char* dst,int len);

void XorEncrypt(char* pContent,uint32 nSize);
void XorDecrypt(char* pContent,uint32 nSize);


#endif