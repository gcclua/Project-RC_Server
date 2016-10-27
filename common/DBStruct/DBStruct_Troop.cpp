#include "DBStruct_Troop.h"

void DBTroop::CleanUp( )
{
	__ENTER_FUNCTION
		m_nType    = 0; //µØ¿éID
		m_nLevel   = 0;
		m_nCount   = 0;
		m_nBuildId = 0;
		m_nHp      = 0;
		m_nArrangeIndex = 0;
		m_nQueueIndex   = 0;
	__LEAVE_FUNCTION
}
void DBTroop::CopyFrom(const DBTroop& rSource)
{
	__ENTER_FUNCTION
		m_nType    = rSource.m_nType; //µØ¿éID
		m_nLevel   = rSource.m_nLevel;
		m_nCount   = rSource.m_nCount;
		m_nBuildId = rSource.m_nBuildId;
		m_nHp      = rSource.m_nHp;
		m_nArrangeIndex = rSource.m_nArrangeIndex;
		m_nQueueIndex   = rSource.m_nQueueIndex;
	__LEAVE_FUNCTION
}
