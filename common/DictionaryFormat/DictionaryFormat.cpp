#include "DictionaryFormat.h"
#include "stdarg.h"

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "d", pSrcStr, param1);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dd", pSrcStr, param1, param2);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ddd", pSrcStr, param1, param2, param3);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dddd", pSrcStr, param1, param2, param3, param4);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ddddd", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dddddd", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "s", pSrcStr, param1);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ss", pSrcStr, param1, param2);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sss", pSrcStr, param1, param2, param3);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssss", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sd", pSrcStr, param1, param2);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdd", pSrcStr, param1, param2, param3);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, const tchar* param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dss", pSrcStr, param1, param2, param3);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssds", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, const tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ddds", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sds", pSrcStr, param1, param2, param3);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, tint32 param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dsd", pSrcStr, param1, param2, param3);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddd", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdd", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, const tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdss", pSrcStr, param1, param2, param3, param4);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdsd", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssd", pSrcStr, param1, param2, param3, param4);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5, const tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssddds", pSrcStr, param1, param2, param3, param4, param5, param6);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdsdd", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, tint32 param5, tint32 param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdsddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdddd", pSrcStr, param1, param2, param3, param4, param5);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssss", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, tint32 param4, const  tchar* param5, const  tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdddss", pSrcStr, param1, param2, param3, param4, param5, param6);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, tint32 param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssd", pSrcStr, param1, param2, param3);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const  tchar* param2)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ds", pSrcStr, param1, param2);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, const  tchar* param3, const  tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ddss", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, tint32 param4, const  tchar* param5, const  tchar* param6, const  tchar* param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdddsss", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, tint32 param2, tint32 param3, const  tchar* param4, const  tchar* param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddss", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const  tchar* param2, tint32 param3, const  tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dsds", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, const  tchar* param3)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dds", pSrcStr, param1, param2, param3);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssss", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, const tchar* param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdds", pSrcStr, param1, param2, param3, param4);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdddd", pSrcStr, param1, param2, param3, param4, param5, param6);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssdd", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6, const tchar* param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddddds", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddddd", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdsddd", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, const tchar* param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdss", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6, const tchar* param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssssss", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5, const tchar* param6, tint32 param7, tint32 param8, tint32 param9, tint32 param10)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssddsdddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5, const tchar* param6, tint32 param7, tint32 param8, tint32 param9, tint32 param10, tint32 param11)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssddsddddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10, param11);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, const  tchar* param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssdsd", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, const  tchar* param5, tint32 param6, const  tchar* param7, tint32 param8, const  tchar* param9)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssdsdsds", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, const tchar* param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssds", pSrcStr, param1, param2, param3, param4, param5);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssd", pSrcStr, param1, param2, param3, param4, param5);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dsddd", pSrcStr, param1, param2, param3, param4, param5);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, tint32 param3, tint32 param4, const tchar* param5, const tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dsddss", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, tint32 param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssddd", pSrcStr, param1, param2, param3, param4, param5, param6);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6,const tchar* param7, const tchar* param8, const tchar* param9,const tchar* param10)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssssssss", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, tint32 param3, tint32 param4, const tchar* param5, tint32 param6,tint32 param7, tint32 param8, tint32 param9)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdddsdddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7, tint32 param8)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dddddddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, const tchar* param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdds", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdsdd", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdsdddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, const  tchar* param5, tint32 param6, tint32 param7, tint32 param8)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdsdsddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6,const tchar* param7, tint32 param8)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssssssd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2, const tchar* param3, tint32 param4, const tchar* param5, tint32 param6,const tchar* param7, tint32 param8)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdsdsdsd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, tint32 param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssddd", pSrcStr, param1, param2, param3, param4, param5);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, tint32 param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssssdd", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, tint32 param5, tint32 param6, const tchar* param7,const tchar* param8, tint32 param9, tint32 param10)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssddssdd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dssss", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdssss", pSrcStr, param1, param2, param3, param4, param5, param6);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, tint32 param5, const tchar* param6, const tchar* param7, const tchar* param8, tint32 param9, tint32 param10)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddddsssdd", pSrcStr, param1, param2, param3, param4, param5, param6,param7, param8, param9, param10);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, const tchar* param5, const tchar* param6, const tchar* param7, tint32 param8, tint32 param9)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdddsssdd", pSrcStr, param1, param2, param3, param4, param5, param6,param7, param8, param9);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, tint32 param5, const tchar* param6, const tchar* param7, const tchar* param8, const tchar* param9, const tchar* param10)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddddsssss", pSrcStr, param1, param2, param3, param4, param5, param6,param7, param8, param9, param10);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, tint32 param4, const tchar* param5, const tchar* param6, const tchar* param7, const tchar* param8, const tchar* param9)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sdddsssss", pSrcStr, param1, param2, param3, param4, param5, param6,param7, param8, param9);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, tint32 param2,  tint32 param3, const tchar* param4, tint32 param5, tint32 param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sddsddd", pSrcStr, param1, param2, param3, param4, param5, param6,param7);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, tint32 param4, tint32 param5, const tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ddddds", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2,  tint32 param3, tint32 param4, tint32 param5, const tchar* param6, const tchar* param7, tint32 param8, tint32 param9)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dddddssdd", pSrcStr, param1, param2, param3, param4, param5, param6,param7, param8, param9);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2,  tint32 param3, tint32 param4, const tchar* param5, const tchar* param6, const tchar* param7, tint32 param8, tint32 param9)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssddsssdd", pSrcStr, param1, param2, param3, param4, param5, param6,param7, param8, param9);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, tint32 param2, tint32 param3, const tchar* param4, const tchar* param5, const tchar* param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dddsss", pSrcStr, param1, param2, param3, param4, param5, param6);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, tint32 param5)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdsd", pSrcStr, param1, param2, param3, param4, param5);
}
tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "sssdddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, tint32 param3, tint32 param4, tint32 param5, tint32 param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssddddd", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, const  tchar* param5, const  tchar* param6, tint32 param7)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssssd", pSrcStr, param1, param2, param3, param4, param5, param6, param7);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, const  tchar* param5, const  tchar* param6, tint32 param7, const  tchar* param8, const  tchar* param9, tint32 param10)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssssdssd", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8, param9, param10);

}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, tint32 param1, const  tchar* param2, tint32 param3, tint32 param4)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "dsdd", pSrcStr, param1, param2, param3, param4);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const  tchar* param1, const  tchar* param2, const  tchar* param3, const  tchar* param4, tint32 param5, tint32 param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssdd", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary(tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, tint32 param3, const tchar* param4, const tchar * param5, const tchar * param6)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssdsss", pSrcStr, param1, param2, param3, param4, param5, param6);
}

tchar* DictionaryFormat::FormatDictionary( tchar * pDestStr, tint32 nMaxSize, tchar * pSrcStr, const tchar* param1, const tchar* param2, const tchar* param3, const tchar* param4, const tchar* param5, const tchar* param6, const tchar* param7, const tchar* param8)
{
	return FormatDictionaryWithVarParam(pDestStr, nMaxSize, "ssssssss", pSrcStr, param1, param2, param3, param4, param5, param6, param7, param8);
}

/*************************************************************************************************************************
*生成格式"#{31170}*ab*cd" 其中31170是字典号,*是分割符,“ab”是第一个变量，“cd”是第二个变量
*调用格式：FormatDictionaryWithVarParam(pDestStr,nMaxSize, "sss", "#{11686}", "abc", "de", "fg");
*pDestStr:目标字符串,*****************长度为MAX_FORMAT_STRING_LENGTH
*nMaxSize:目标字符串长度
*fmt：参数格式；  d:表示整形参数; s:表示字符串参数
*pSrcStr：字典；
*...：可变参数
*************************************************************************************************************************/
tchar * DictionaryFormat::FormatDictionaryWithVarParam(tchar * pDestStr, tint32 nMaxSize, const tchar * fmt, tchar * pSrcStr, ...)
{
	__ENTER_FUNCTION

	if (pDestStr == NULL || fmt == NULL || pSrcStr == NULL )
	{
		return "";
	}
	tint32 nLenSrcStr = static_cast<tint32>(strlen(pSrcStr));
	//#{*}至少有4个字符
	if (nLenSrcStr < 4 || nLenSrcStr > MAX_FORMAT_PARAM_LENGTH)
	{
		return "";
	}

	//必须是字典的格式
	if (pSrcStr[0] != '#' || pSrcStr[1] != '{' || pSrcStr[nLenSrcStr-1] != '}')
	{
		return "";
	}

	tchar szBuff[MAX_FORMAT_STRING_LENGTH] = {0};
	va_list argptr;
	va_start(argptr, pSrcStr);

	tint32 narg = 0;
	for (narg = 0; *fmt && narg<10; narg++,fmt++)
	{
		switch (*fmt)
		{
		case 'd':
			{
				//整形参数，长度用字符形式表示
				tint32 iNum = va_arg(argptr, tint32);
				tchar strNum[16] = {0};
				tsnprintf(strNum, 16, "%d", iNum);
				tchar tmp[MAX_FORMAT_PARAM_LENGTH] ={0};
				tsnprintf(tmp, MAX_FORMAT_PARAM_LENGTH, "*%s", strNum);
				strcat(szBuff, tmp);
			}
			break;
		case 's':
			{
				//字符串参数，长度用字符形式表示
				const tchar *msg = va_arg(argptr, tchar*);
				if (msg == NULL)
				{
					break;
				}

				tint32 len = static_cast<tint32>(strlen(msg));
				if (len > 512)
				{
					//CacheLog( LOGDEF_INST(Error), "FormatDictionary param%d too long(%d), Dic=%s,param=%s", narg, len, pSrcStr, msg);
				}
				tchar tmp[MAX_FORMAT_PARAM_LENGTH] ={0};
				tsnprintf(tmp, MAX_FORMAT_PARAM_LENGTH, "*%s", msg);
				strcat(szBuff, tmp);
			}
			break;
		default:
			break;
		}
	}
	va_end(argptr); 
	//字符串超长
	//最后拼接的字符串需要加上字典长度nLenSrcStr、参数长度1和'*'1
	if((strlen(szBuff) + nLenSrcStr + 2) > (MAX_FORMAT_STRING_LENGTH-1))
	{
		//CacheLog( LOGDEF_INST(Error), "FormatDictionary szBuff too long(%d), Dic=%s,szBuff=%s", (strlen(szBuff) + nLenSrcStr + 2), pSrcStr, szBuff);
		return "";
	}

	//拼接最终的字符串
	tchar szResult[MAX_FORMAT_STRING_LENGTH] = {0};
	strncpy(szResult, pSrcStr, nLenSrcStr);
	strcat(szResult, szBuff);
	strcat(szResult, "\0");

	tint32 nLenResult = static_cast<tint32>(strlen(szResult));
	if (nLenResult >= MAX_FORMAT_STRING_LENGTH || nLenResult >= nMaxSize)
	{
		//CacheLog( LOGDEF_INST(Error), "FormatDictionary Result too long(%d), Dic=%s,result=%s", nLenResult, pSrcStr, szResult);
		return "";
	}

	//将拼接好的字符串拷贝到目标字符串中
	memcpy(pDestStr, szResult, nLenResult);
	pDestStr[nLenResult] = '\0';
	return pDestStr;

	__LEAVE_FUNCTION
	
	return "";
}