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
	m_nStatus  = rhs.m_nStatus;
	m_OwnSkillList.CopyFrom(rhs.m_OwnSkillList);
	m_CoolDownList = rhs.m_CoolDownList;
	m_nMarchId  = rhs.m_nMarchId;
	m_nID       = rhs.m_nID;
	return *this;
}

void Hero::CleanUp()
{
	m_nType    = 0; 
	m_nLevel   = 0;
	m_nQuality = 0;
	m_nCityID  = 0;
	m_nExp     = 0;
	m_nStatus  = HEROSTATUS_IDLE;
	m_OwnSkillList.CleanUp();
	m_CoolDownList.CleanUp();
	m_nMarchId = 0;
	m_nID      = 0;
}

void Hero::SerializeToDB(DBHero& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_nType    = m_nType; 
		rDest.m_nLevel   = m_nLevel;  
		rDest.m_nQuality = m_nQuality;  
		rDest.m_nCityID  = m_nCityID;
		rDest.m_nExp     = m_nExp;
		rDest.m_nStatus  = m_nStatus;
		rDest.m_nMarchId = m_nMarchId;
		rDest.m_nHeroId  = m_nID;
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
		m_nStatus  = rSource.m_nStatus;
		m_nMarchId = rSource.m_nMarchId;
		m_nID      = rSource.m_nHeroId;
	__LEAVE_FUNCTION
}

void Hero::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
	__LEAVE_FUNCTION
}

void Hero::OnLogin()
{
	__ENTER_FUNCTION

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

tint32 Hero::GetOwnSkill(tint32 index) const
{
	if( index>=0 && index<HERO_OWNSKILL ) 
	{
		return m_OwnSkillList.GetValue(index);
	}
	return -1;
}

void Hero::SetOwnSkill(tint32 skillId, tint32 index)
{
	if (index >= 0 && index <= HERO_OWNSKILL)
	{
		m_OwnSkillList.SetValue(skillId, index);
	}
}

void Hero::AddOwnSkill(tint32 skillId)
{
	m_OwnSkillList.AddValue(skillId);
}