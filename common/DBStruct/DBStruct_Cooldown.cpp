////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺9:18 2014-03-03
//             ˵����˵������ȴ�б����ݴ洢
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_Cooldown.h"

void DBCoolDown_Info::CleanUp()
{
	__ENTER_FUNCTION
	m_nID = invalid_id;//��ȴID
	m_nCDTimeElapsed = 0;//��ȴ����ʱ�� ����
	__LEAVE_FUNCTION
}

void DBCoolDown_Info::CopyFrom(const DBCoolDown_Info& rSour)
{
	__ENTER_FUNCTION
	m_nID = rSour.m_nID;//��ȴID
	m_nCDTimeElapsed = rSour.m_nCDTimeElapsed;//��ȴ����ʱ�� ����
	__LEAVE_FUNCTION
}
