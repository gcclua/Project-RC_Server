#include "DBStruct_Hero.h"

void DBHero::CleanUp( )
{
	__ENTER_FUNCTION
		m_nType    = 0; //
		m_nLevel   = 0;
		m_nQuality = 0;
		m_nCityID  = 0;
		m_nExp     = 0;
	__LEAVE_FUNCTION
}
void DBHero::CopyFrom(const DBHero& rSource)
{
	__ENTER_FUNCTION
		m_nType    = rSource.m_nType; //µØ¿éID
		m_nLevel   = rSource.m_nLevel; 
		m_nQuality = rSource.m_nQuality;
		m_nCityID  = rSource.m_nCityID;
		m_nExp     = 0;
	__LEAVE_FUNCTION
}
