#include "GameStruct_March.h"

March::March()
{
	CleanUp();
}
March::~March()
{

}

void March::CleanUp()
{
	m_pos.CleanUp();
	m_nBeginTime = 0; // ����ʱ��
	m_nEndTime = 0;   // ����ʱ��
	m_nMarchId = 0;   // Ψһ��ʾ
	m_nPlayerId = 0;;  // ���ID
	m_nCityId = 0;    // ����ID
	m_nStatus = MARCHSTATUS_PROCESS;    // ״̬
}

void March::SerializeToDB(DBMarch& rDest) const
{
	m_Hero.SerializeToDB(rDest.m_Hero);
	for(int i=0;i<m_TroopList.GetListSize();i++)
	{
		m_TroopList.GetTroopByIndex(i).SerializeToDB(rDest.m_TroopList[i]);
	}

	rDest.m_pos        = m_pos;
	rDest.m_nBeginTime = m_nBeginTime;
	rDest.m_nEndTime   = m_nEndTime;
	rDest.m_nMarchId   = m_nMarchId;
	rDest.m_nPlayerId  = m_nPlayerId;
	rDest.m_nCityId    = m_nCityId;
	rDest.m_nStatus    = m_nStatus;
}
void March::SerializeFromDB(const DBMarch& rSource)
{
	m_Hero.SerializeFromDB(rSource.m_Hero);
	for (int i=0;i<TROOP_QUEUE_MAX_COUNT;i++)
	{
		Troop rTroop;
		rTroop.SerializeFromDB(rSource.m_TroopList[i]);
		m_TroopList.SetTroop(rTroop.GetQueueIndex(),rTroop);
	}
	m_pos        = rSource.m_pos;
	m_nBeginTime = rSource.m_nBeginTime;
	m_nEndTime   = rSource.m_nEndTime;
	m_nMarchId   = rSource.m_nMarchId;
	m_nPlayerId  = rSource.m_nPlayerId;
	m_nCityId    = rSource.m_nCityId;
	m_nStatus    = rSource.m_nStatus;
}

Troop March::GetQueueTroop(int nIndex)
{
	AssertEx(nIndex>=0 && nIndex<TROOP_QUEUE_MAX_COUNT,"");
	return m_TroopList.GetTroopByIndex(nIndex);
}