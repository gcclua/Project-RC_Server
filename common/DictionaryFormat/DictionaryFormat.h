#ifndef _DICTIONARYFORMAT_
#define _DICTIONARYFORMAT_

#include "Base.h"

#define MAX_FORMAT_PARAM_LENGTH	512
#define MAX_FORMAT_STRING_LENGTH 2048

class DictionaryFormat
{
public:
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6, const tchar* param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr,const  tchar* param1, tint32 param2, tint32 param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, const tchar* param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, tint32 param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, const tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, const tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5, const tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, tint32 param3, const  tchar* param4, tint32 param5, tint32 param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, tint32 param4, const  tchar* param5, const  tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, tint32 param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const  tchar* param2);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, const  tchar* param3, const  tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, tint32 param4, const  tchar* param5, const  tchar* param6, const  tchar* param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, const  tchar* param4, const  tchar* param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const  tchar* param2, tint32 param3, const  tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, const  tchar* param3);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, const tchar* param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6, const tchar* param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, const tchar* param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5, const tchar* param6, tint32 param7, tint32 param8, tint32 param9, tint32 param10);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, const  tchar* param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, const  tchar* param5, tint32 param6, const  tchar* param7, tint32 param8, const  tchar* param9);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, const tchar* param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, tint32 param3, tint32 param4, const tchar* param5, const tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6,const tchar* param7, const tchar* param8, const tchar* param9,const tchar* param10);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, const tchar* param5, tint32 param6,tint32 param7, tint32 param8, tint32 param9);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7, tint32 param8);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, const tchar* param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, const  tchar* param5, tint32 param6, tint32 param7, tint32 param8);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6,const tchar* param7, tint32 param8);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, const tchar* param5, tint32 param6,const tchar* param7, tint32 param8);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, tint32 param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, tint32 param5, const tchar* param6, const tchar* param7, const tchar* param8, tint32 param9, tint32 param10);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, const tchar* param5, const tchar* param6, const tchar* param7, tint32 param8, tint32 param9);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, tint32 param5, const tchar* param6, const tchar* param7, const tchar* param8, const tchar* param9, const tchar* param10);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, const tchar* param5, const tchar* param6, const tchar* param7, const tchar* param8, const tchar* param9);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, const tchar* param4, tint32 param5, tint32 param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, const tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2,  tint32 param3, tint32 param4, tint32 param5, const tchar* param6, const tchar* param7, tint32 param8, tint32 param9);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2,  tint32 param3, tint32 param4, const tchar* param5, const tchar* param6, const tchar* param7, tint32 param8, tint32 param9);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, const tchar* param4, const tchar* param5, const tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, tint32 param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5, const tchar* param6, tint32 param7, tint32 param8, tint32 param9, tint32 param10, tint32 param11);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, tint32 param5, tint32 param6, const tchar* param7,const tchar* param8, tint32 param9, tint32 param10);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, const  tchar* param5, const  tchar* param6, tint32 param7);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, const  tchar* param5, const  tchar* param6, tint32 param7, const  tchar* param8, const  tchar* param9, tint32 param10);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const  tchar* param2, tint32 param3, tint32 param4);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, tint32 param5, tint32 param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, tint32 param3, const  tchar* param4, const  tchar* param5, const  tchar* param6);
	static tchar* FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, const  tchar* param5, const  tchar* param6, const  tchar* param7, const  tchar* param8);
private:	
	static tchar * FormatDictionaryWithVarParam(tchar * pDestStr, tint32 nMaxSize, const tchar * fmt, tchar * pSrcStr, ...);
};

#endif
