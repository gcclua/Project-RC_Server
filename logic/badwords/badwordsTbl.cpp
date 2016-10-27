#include "badwordsTbl.h"
#include "../common/DBC.h"
#include "../common/string-util.h"
badwordsTbl badwordsTbl::m_tblbadwords;
const char* badwordsTbl::szConfigFile = "Config/badwords.txt";
badwordsTbl::badwordsTbl(void)
{
}

badwordsTbl::~badwordsTbl(void)
{
	ClearTbl();
}

void badwordsTbl::LoadTbl()
{
	ClearTbl();

	DBCFile fileDBC(0);
	fileDBC.OpenFromTXT(szConfigFile);
	int nRow = fileDBC.GetRecordsNum();
	for (int i = 0; i < nRow; i++)
	{
		string temp = "";

		gb2312ToUtf8(fileDBC.Search_Posistion(i,1)->pString,temp);
		m_mapbadwordsBase.insert(make_pair(temp, 0));

	}
}

void badwordsTbl::ClearTbl()
{
	m_mapbadwordsBase.clear();
}

bool badwordsTbl::GetbadwordsBase(const string& str)
{
	hash_map<string,int>::iterator iter = m_mapbadwordsBase.find(str);
	if (iter == m_mapbadwordsBase.end())
		return false;

	return true;
}

