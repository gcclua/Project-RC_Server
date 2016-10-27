#include "GameStruct_Skill.h"
#include "DBStruct/DBStruct_Cooldown.h"
#include "Service/TimeInfo.h"

void CoolDown_Info::Tick(TimeInfo const&rTimeInfo)
{
	__ENTER_FUNCTION
	if (m_nID<0)
	{
		return;
	}
	if (m_nCDTime<=m_nCDTimeElapsed)
	{
		return;
	}
	m_nCDTimeElapsed +=rTimeInfo.m_uTimeElapse;
	if (m_nCDTimeElapsed>m_nCDTime ||m_nCDTimeElapsed<0)//时间到了 或者 时间过得太多了 
	{
		m_nCDTimeElapsed =m_nCDTime;
	}
	__LEAVE_FUNCTION
}

bool CoolDown_Info::SerializeToDB(DBCoolDown_Info& rDest) const
{
	__ENTER_FUNCTION
	rDest.m_nID = m_nID;
	rDest.m_nCDTimeElapsed = m_nCDTimeElapsed;
	return true;
	__LEAVE_FUNCTION
		return false;
}

bool CoolDown_Info::SerializeFromDB(const DBCoolDown_Info& rDest)
{
	__ENTER_FUNCTION
	
	m_nID = rDest.m_nID;
	m_nCDTimeElapsed = rDest.m_nCDTimeElapsed;
	return true;
	__LEAVE_FUNCTION
	return false;
}
