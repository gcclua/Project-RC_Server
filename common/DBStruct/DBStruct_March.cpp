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
		m_nBeginTime = 0; // ����ʱ��
		m_nEndTime = 0;   // ����ʱ��
		m_nMarchId = 0;   // Ψһ��ʾ
		m_nPlayerId = 0;;  // ���ID
		m_nCityId = 0;    // ����ID
		m_nStatus = MARCHSTATUS_PROCESS;    // ״̬
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

