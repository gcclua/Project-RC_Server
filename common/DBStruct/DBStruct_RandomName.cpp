////////////////////////////////////////////////////////////////////////////////////////
//时间：2014年7月2日11:40:55
//说明：随机名字表
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_RandomName.h"

void DBRandomName::CleanUp()
{
	__ENTER_FUNCTION
	memset(m_szName,0,sizeof(m_szName));
	__LEAVE_FUNCTION
}

void DBRandomName::CopyFrom(const DBRandomName& rSour)
{
	__ENTER_FUNCTION
	memset(m_szName,0,sizeof(m_szName));
	tsnprintfex(m_szName, sizeof(m_szName), "%s",rSour.m_szName);
	__LEAVE_FUNCTION
}

void DBRandomNameList::CleanUp()
{
	__ENTER_FUNCTION
	for (tint32 i = 0; i < RANDOM_NAME_BUFFER_MAX; i++)
	{
		m_RandomNameList[i].CleanUp();
	}
	__LEAVE_FUNCTION
}

void DBRandomNameList::CopyFrom(const DBRandomNameList& rSour)
{
	__ENTER_FUNCTION
	for (tint32 i = 0; i < RANDOM_NAME_BUFFER_MAX; i++)
	{
		m_RandomNameList[i].CopyFrom(rSour.m_RandomNameList[i]);
	}
	__LEAVE_FUNCTION
}