#include "GameStruct_Hero.h"

Hero::Hero()
{
	CleanUp();
}
Hero::~Hero(void)
{

}

Hero& Hero::operator=(Hero const& rhs)
{
	m_nType    = rhs.m_nType; 
	m_nLevel   = rhs.m_nLevel;
	m_nQuality = rhs.m_nQuality;
	m_nCityID  = rhs.m_nCityID;
	m_nExp     = rhs.m_nExp;
	return *this;
}

void Hero::CleanUp()
{
	m_nType    = 0; 
	m_nLevel   = 0;
	m_nQuality = 0;
	m_nCityID  = 0;
	m_nExp     = 0;
}

void Hero::SerializeToDB(DBHero& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_nType    = m_nType; 
		rDest.m_nLevel   = m_nLevel;  
		rDest.m_nQuality = m_nQuality;  
		rDest.m_nCityID  = m_nCityID;
		rDest.m_nExp     = m_nExp;
	__LEAVE_FUNCTION
}
void Hero::SerializeFromDB(const DBHero& rSource)
{
	__ENTER_FUNCTION
		m_nType    = rSource.m_nType; 
		m_nLevel   = rSource.m_nLevel; 
		m_nQuality = rSource.m_nQuality;
		m_nCityID  = rSource.m_nCityID;
		m_nExp     = rSource.m_nExp;
	__LEAVE_FUNCTION
}

int64 Hero::AddExp(int64 nAdd)
{
	__ENTER_FUNCTION
		AssertEx(nAdd>0,"");
		m_nExp += nAdd;
		return m_nExp;
	__LEAVE_FUNCTION
		return 0;
}