#include "DBStruct_March.h"
#include "march/GameDefine_March.h"

void DBMarch::CleanUp( )
{
	__ENTER_FUNCTION
		m_Hero.CleanUp();
		for (int i=0;i<TROOP_QUEUE_MAX_COUNT;i++)
		{
			m_TroopList[i].CleanUp();
		}
		m_pos.CleanUp();
		m_nBeginTime = 0; // 出发时间
		m_nEndTime = 0;   // 返回时间
		m_nMarchId = 0;   // 唯一标示
		m_nPlayerId = 0;;  // 玩家ID
		m_nCityId = 0;    // 城市ID
		m_nStatus = MARCHSTATUS_PROCESS;    // 状态
	__LEAVE_FUNCTION
}
void DBMarch::CopyFrom(const DBMarch& rSource)
{
	__ENTER_FUNCTION
		
		m_Hero.CopyFrom(rSource.m_Hero);

		for (int i=0;i<TROOPTYPE_MAX;i++)
		{
			m_TroopList[i].CopyFrom(rSource.m_TroopList[i]);
		}

		m_pos        = rSource.m_pos;
		m_nBeginTime = rSource.m_nBeginTime;
		m_nEndTime   = rSource.m_nEndTime;
		m_nMarchId   = rSource.m_nMarchId;
		m_nPlayerId  = rSource.m_nPlayerId;
		m_nCityId    = rSource.m_nCityId;
		m_nStatus    = rSource.m_nStatus;

	__LEAVE_FUNCTION
}

