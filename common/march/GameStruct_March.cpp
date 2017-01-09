#include "GameStruct_March.h"
#include "Table/Table_Troop.h"
#include "Table/Table_RoleBaseAttr.h"

March::March()
{
	CleanUp();
}
March::~March()
{

}

void March::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		__LEAVE_FUNCTION
}

void March::OnLogin()
{
	__ENTER_FUNCTION

		__LEAVE_FUNCTION
}

void March::FillMarchBaseInfo(MarchBaseInfo &rInfo)
{
	__ENTER_FUNCTION

		rInfo.m_Guid = m_nMarchId;
		rInfo.m_szName = m_Hero.GetName();
		rInfo.m_nLevel = m_Hero.GetLevel();
		rInfo.m_OwnGuid = m_nPlayerId;

	__LEAVE_FUNCTION
}

March& March::operator=(March const& rhs)
{
	m_Hero = rhs.m_Hero;
	m_TroopList = rhs.m_TroopList;
	m_pos = rhs.GetPos();
	m_nBeginTime = rhs.m_nBeginTime;
	
	m_nEndTime   = rhs.m_nEndTime;
	m_nMarchId   = rhs.m_nMarchId;
	m_nPlayerId  = rhs.m_nPlayerId;
	m_nCityId    = rhs.m_nCityId;
	m_nStatus    = rhs.m_nStatus;
	m_nFightId   = rhs.m_nFightId;
	m_nBuildId   = rhs.m_nBuildId;
	m_nForce     = rhs.m_nForce;
	return (*this);
}

void March::CleanUp()
{
	m_pos.CleanUp();
	m_nBeginTime = 0; // 出发时间
	m_nEndTime = 0;   // 返回时间
	m_nMarchId = 0;   // 唯一标示
	m_nPlayerId = 0;;  // 玩家ID
	m_nCityId = 0;    // 城市ID
	m_nStatus = MARCHSTATUS_INVALID;    // 状态
	m_nFightId = 0;
	m_nBuildId = invalid_guid64;
	m_nForce   = invalid_id;
	//m_mapArrange.clear();
	m_TroopList.CleanUp();
	m_Hero.CleanUp();
	m_TroopMarchMap.clear();
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

		m_TroopMarchMap.insert(std::make_pair(rTroop.GetId(),rTroop.GetMarchId()) );
	}
	m_pos        = rSource.m_pos;
	m_nBeginTime = rSource.m_nBeginTime;
	m_nEndTime   = rSource.m_nEndTime;
	m_nMarchId   = rSource.m_nMarchId;
	m_nPlayerId  = rSource.m_nPlayerId;
	m_nCityId    = rSource.m_nCityId;
	m_nStatus    = rSource.m_nStatus;
	m_nBuildId   = rSource.m_nBuildId;
}

Troop March::GetQueueTroop(int nIndex)
{
	AssertEx(nIndex>=0 && nIndex<TROOP_QUEUE_MAX_COUNT,"");
	return m_TroopList.GetTroopByIndex(nIndex);
}

bool  March::SwapQueueForArrange(int nArrange1,int nArrange2)
{
	__ENTER_FUNCTION
		AssertEx(nArrange1>=0 && nArrange1<TROOP_QUEUE_MAX_COUNT,"");
		AssertEx(nArrange2>=0 && nArrange2<TROOP_QUEUE_MAX_COUNT,"");
		if (nArrange1 == nArrange2)
		{
			return false;
		}

		return	m_TroopList.SwapQueueForArrange(nArrange1,nArrange2);

	__LEAVE_FUNCTION
		return false;
}

bool March::AddTroop(int64 nTroopId,int nTroopType,int nHp)
{
	__ENTER_FUNCTION
		 Troop rTroop = m_TroopList.GetTroopById(nTroopId);
		 if (rTroop.GetId() != nTroopId)
		 {
			 return false;
		 }
	    
		 int nType = rTroop.GetType();

		 if (nType == TROOPTYPE_INVILID)
		 {
			 rTroop.SetType(nTroopType);
			 nType = nTroopType;
		 }
		 else if (nTroopType != nType)
		 {
			 return false;
		 }

		 Table_Troop const * pTroopTable = GetTable_TroopByID(nType);
		 AssertEx(pTroopTable,"");
		 int nLevel = rTroop.GetLevel();
		 Table_RoleBaseAttr const * pRoleBase = GetTable_RoleBaseAttrByID(pTroopTable->GetDataIDbyIndex(nLevel));
		 AssertEx(pRoleBase,"");
		 if (TROOP_QUEUE_MAX_SIGCOUNT* pRoleBase->GetMaxHP() <rTroop.GetHp()+nHp)
		 {
			 return false;
		 }

		 rTroop.SetHp(nHp);

		__LEAVE_FUNCTION
		return false;
}

int64  March::GetHeroId()
{
	__ENTER_FUNCTION
	return m_Hero.GetUID();
	__LEAVE_FUNCTION
		return invalid_guid64;
}

void March::SetHeroHp(int nHp)
{
	__ENTER_FUNCTION
		m_Hero.SetHp(nHp);
	__LEAVE_FUNCTION
}
void March::SetTroopHp(int nArrangeIndex,int nHp)
{
	__ENTER_FUNCTION
	m_TroopList.SetTroopHp(nArrangeIndex,nHp);
	__LEAVE_FUNCTION
}
