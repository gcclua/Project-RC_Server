////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺17:38 2014-01-01
//             ˵����PK������ݴ洢�ṹ
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_PK.h"

void DBPKAttackerInfo::CleanUp()
{
	__ENTER_FUNCTION
	m_AttackerGUID = invalid_guid64;
	m_nAttackTime = 0;//�����б��ʣ��ʱ�� ��λ����
	__LEAVE_FUNCTION
}

void DBPKAttackerInfo::CopyFrom(const DBPKAttackerInfo& rSour)
{
	__ENTER_FUNCTION
	m_AttackerGUID = rSour.m_AttackerGUID;
	m_nAttackTime  = rSour.m_nAttackTime;//�����б��ʣ��ʱ�� ��λ����
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
