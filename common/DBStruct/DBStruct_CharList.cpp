////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：17:58 2014-02-18
//             说明：角色列表结构
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_CharList.h"

void DBCharData::CleanUp()
{
	__ENTER_FUNCTION
	m_Guid = invalid_guid64;
	
	memset(m_CharName,0,sizeof(m_CharName));
	__LEAVE_FUNCTION
}

void DBCharData::CopyFrom(const DBCharData& rSour)
{
	__ENTER_FUNCTION
	m_Guid  = rSour.m_Guid;
	
	memset(m_CharName,0,sizeof(m_CharName));
	tsnprintfex(m_CharName, sizeof(m_CharName), "%s",rSour.m_CharName);
	__LEAVE_FUNCTION
}

void DBCharDataList::CleanUp()
{
	__ENTER_FUNCTION
		m_CharNum = 0;
	for (tint32 i = 0; i < DB_CHAR_NUMBER; i++)
	{
		m_CharDataList[i].CleanUp();
	}
	__LEAVE_FUNCTION
}

void DBCharDataList::CopyFrom(const DBCharDataList& rSour)
{
	__ENTER_FUNCTION
		m_CharNum = rSour.m_CharNum;
	for (tint32 i = 0; i < DB_CHAR_NUMBER; i++)
	{
		m_CharDataList[i].CopyFrom(rSour.m_CharDataList[i]);
	}
	__LEAVE_FUNCTION
}