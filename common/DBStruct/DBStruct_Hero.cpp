#include "DBStruct_Hero.h"
#include "hero/GameDefine_Hero.h"
#include "GuidDefine.h"

void DBHero::CleanUp( )
{
	__ENTER_FUNCTION
		m_nType    = 0; //
		m_nLevel   = 0;
		m_nQuality = 0;
		m_nCityID  = 0;
		m_nExp     = 0;
		m_nStatus  = HEROSTATUS_IDLE;
		m_nMarchId = 0;
		m_nHp      = 0;
		m_nArrangeIndex = 0;
		m_nQueueIndex = 0;
		m_nHeroId  = 0;
	__LEAVE_FUNCTION
}
void DBHero::CopyFrom(const DBHero& rSource)
{
	__ENTER_FUNCTION
		m_nType    = rSource.m_nType; //µØ¿éID
		m_nLevel   = rSource.m_nLevel; 
		m_nQuality = rSource.m_nQuality;
		m_nCityID  = rSource.m_nCityID;
		m_nExp     = rSource.m_nExp;
		m_nStatus  = rSource.m_nStatus;
		m_nMarchId = rSource.m_nMarchId;
		m_nHp      = rSource.m_nHp;
		m_nQueueIndex   = rSource.m_nQueueIndex;
		m_nArrangeIndex = rSource.m_nArrangeIndex;
		m_nHeroId  = rSource.m_nHeroId;
	__LEAVE_FUNCTION
}

void DBHero::InitHero(int nHeroType,int64 nCityId)
{
	CleanUp();
	m_nType = nHeroType;
	m_nCityID = nCityId;
	m_nHeroId = GUIDDEF_GEN(Hero);
}
