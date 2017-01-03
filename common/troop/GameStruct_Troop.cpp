#include "GameStruct_Troop.h"

BSARRAY_ASSIGN_IMPL(Troop,TROOP_QUEUE_MAX_COUNT)

Troop::Troop()
{
	CleanUp();
}
Troop::~Troop(void)
{

}

Troop& Troop::operator=(Troop const& rhs)
{
	m_Id      = rhs.m_Id;
	m_nType    = rhs.m_nType; 
	m_nLevel   = rhs.m_nLevel;
	m_nCount   = rhs.m_nCount;
	m_nMarchId = rhs.m_nMarchId;
	m_nHp      = rhs.m_nHp;
	m_nArrangeIndex = rhs.m_nArrangeIndex;
	m_nQueueIndex   = rhs.m_nQueueIndex;
	m_OwnSkillList.CopyFrom(rhs.m_OwnSkillList);
	m_CoolDownList = rhs.m_CoolDownList;
	return (*this);
}

void Troop::CleanUp()
{
	m_nType    = TROOPTYPE_INVILID; 
	m_nLevel   = 0;
	m_nCount   = 0;
	m_nMarchId = 0;
	m_nHp      = 0;
	m_nArrangeIndex = 0;
	m_nQueueIndex   = 0;
	m_Id = 0;
}

void Troop::SerializeToDB(DBTroop& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_nType    = m_nType; 
		rDest.m_nLevel   = m_nLevel;  
		rDest.m_nCount   = m_nCount;
		rDest.m_nMarchId = m_nMarchId;
		rDest.m_nHp      = m_nHp;
		rDest.m_nId      = m_Id;
		rDest.m_nArrangeIndex = m_nArrangeIndex;
		rDest.m_nQueueIndex   = m_nQueueIndex;
	__LEAVE_FUNCTION
}
void Troop::SerializeFromDB(const DBTroop& rSource)
{
	__ENTER_FUNCTION
		m_nType    = rSource.m_nType; 
		m_nLevel   = rSource.m_nLevel; 
		m_nCount   = rSource.m_nCount; 
		m_nMarchId = rSource.m_nMarchId;
		m_nHp      = rSource.m_nHp;
		m_nQueueIndex = rSource.m_nQueueIndex;
		m_nArrangeIndex = rSource.m_nArrangeIndex;
		m_Id       = rSource.m_nId;
	__LEAVE_FUNCTION
}

tint32 Troop::GetOwnSkill(tint32 index) const
{
	if( index>=0 && index<TROOP_OWNSKILL ) 
	{
		return m_OwnSkillList.GetValue(index);
	}
	return -1;
}

void Troop::SetOwnSkill(tint32 skillId, tint32 index)
{
	if (index >= 0 && index <= TROOP_OWNSKILL)
	{
		m_OwnSkillList.SetValue(skillId, index);
	}
}

void Troop::AddOwnSkill(tint32 skillId)
{
	m_OwnSkillList.AddValue(skillId);
}