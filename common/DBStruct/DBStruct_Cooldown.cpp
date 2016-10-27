////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：9:18 2014-03-03
//             说明：说明：冷却列表数据存储
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "DBStruct_Cooldown.h"

void DBCoolDown_Info::CleanUp()
{
	__ENTER_FUNCTION
	m_nID = invalid_id;//冷却ID
	m_nCDTimeElapsed = 0;//冷却流逝时间 毫秒
	__LEAVE_FUNCTION
}

void DBCoolDown_Info::CopyFrom(const DBCoolDown_Info& rSour)
{
	__ENTER_FUNCTION
	m_nID = rSour.m_nID;//冷却ID
	m_nCDTimeElapsed = rSour.m_nCDTimeElapsed;//冷却流逝时间 毫秒
	__LEAVE_FUNCTION
}
