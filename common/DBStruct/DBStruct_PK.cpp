////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：17:38 2014-01-01
//             说明：PK相关数据存储结构
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_PK.h"

void DBPKAttackerInfo::CleanUp()
{
	__ENTER_FUNCTION
	m_AttackerGUID = invalid_guid64;
	m_nAttackTime = 0;//留在列表的剩余时间 单位毫秒
	__LEAVE_FUNCTION
}

void DBPKAttackerInfo::CopyFrom(const DBPKAttackerInfo& rSour)
{
	__ENTER_FUNCTION
	m_AttackerGUID = rSour.m_AttackerGUID;
	m_nAttackTime  = rSour.m_nAttackTime;//留在列表的剩余时间 单位毫秒
	__LEAVE_FUNCTION
}

void DBPKAttackerList::CleanUp()
{
	__ENTER_FUNCTION
	for (int i=0;i<PKAttackerList::MAX_LIST_SIZE;i++)
	{
		m_AttackerList[i].CleanUp();
	}
	__LEAVE_FUNCTION
}

void DBPKAttackerList::CopyFrom(const DBPKAttackerList& rSour)
{
	__ENTER_FUNCTION
	for (int i=0;i<PKAttackerList::MAX_LIST_SIZE;i++)
	{
		m_AttackerList[i].CopyFrom(rSour.m_AttackerList[i]);
	}
	__LEAVE_FUNCTION
}
