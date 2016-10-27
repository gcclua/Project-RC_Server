#include "GameStruct_Troop.h"

Troop::Troop()
{
	CleanUp();
}
Troop::~Troop(void)
{

}

Troop& Troop::operator=(Troop const& rhs)
{
	m_nType    = rhs.m_nType; 
	m_nLevel   = rhs.m_nLevel;
	m_nCount   = rhs.m_nCount;
	m_nBuildID = rhs.m_nBuildID;
	m_nHp      = rhs.m_nHp;
	m_nArrangeIndex = rhs.m_nArrangeIndex;
	m_nQueueIndex   = rhs.m_nQueueIndex;
	return (*this);
}

void Troop::CleanUp()
{
	m_nType    = 0; 
	m_nLevel   = 0;
	m_nCount   = 0;
	m_nBuildID = 0;
	m_nHp      = 0;
	m_nArrangeIndex = 0;
	m_nQueueIndex   = 0;
}

void Troop::SerializeToDB(DBTroop& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_nType    = m_nType; 
		rDest.m_nLevel   = m_nLevel;  
		rDest.m_nCount   = m_nCount;
		rDest.m_nBuildId = m_nBuildID;
	__LEAVE_FUNCTION
}
void Troop::SerializeFromDB(const DBTroop& rSource)
{
	__ENTER_FUNCTION
		m_nType    = rSource.m_nType; 
		m_nLevel   = rSource.m_nLevel; 
		m_nCount   = rSource.m_nCount; 
		m_nBuildID = rSource.m_nBuildId;
	__LEAVE_FUNCTION
}