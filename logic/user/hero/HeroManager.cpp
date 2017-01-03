
#include "../User.h"
#include "HeroManager.h"
#include "Table/Table_RoleBaseAttr.h"
#include "packet/Packet/PBMessage.pb.h"

/////////arrange function///////////////
HeroManager::HeroManager(User &rUser)
	: BaseManager(rUser)
{
	m_mapHero.clear();
}
HeroManager::~HeroManager(void)
{

}

void HeroManager::Init()
{

}

void HeroManager::OnLogin()
{
	for (HeroPtrMap::iterator it = m_mapHero.begin();it != m_mapHero.end();it++)
	{
		HeroPtr Ptr = it->second;
		AssertEx(Ptr,"");
		Ptr->OnLogin();
	}
}

void  HeroManager::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
	for (HeroPtrMap::iterator it = m_mapHero.begin();it != m_mapHero.end();it++)
	{
		HeroPtr Ptr = it->second;
		AssertEx(Ptr,"");
		Ptr->Tick(rTimeInfo);
	
	}
	__LEAVE_FUNCTION
}

void HeroManager::SerializeFromDB(const DBFullUserData& rSource)
{
	__ENTER_FUNCTION
		for (int i=0;i<HEROTYPE_MAX;i++)
		{
			if (rSource.m_HeroList[i].m_nType <= 0)
			{
				continue;
			}
			HeroPtr Ptr(new Hero());
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_HeroList[i]);
			AddHero(Ptr);
		}
		
	__LEAVE_FUNCTION
}
void HeroManager::SerializeToDB(DBFullUserData& rDesc)
{
	__ENTER_FUNCTION
		int nHeroIndex = 0;
		for (HeroPtrMap::iterator it = m_mapHero.begin();it != m_mapHero.end();it++)
		{
			HeroPtr Ptr = it->second;
			AssertEx(Ptr,"");

			Ptr->SerializeToDB(rDesc.m_HeroList[nHeroIndex]);
			nHeroIndex++;
		}
	__LEAVE_FUNCTION
}

void  HeroManager::FileData(GC_HeroList* pHeroList)
{
	__ENTER_FUNCTION
		for (HeroPtrMap::iterator it = m_mapHero.begin();it != m_mapHero.end();it++)
		{
			HeroPtr Ptr = it->second;
			AssertEx(Ptr,"");
			GC_HeroData* pHeroData = pHeroList->add_herolist();
			pHeroData->set_type(Ptr->GetType());
			pHeroData->set_level(Ptr->GetLevel());
			pHeroData->set_hp(Ptr->GetHp());
			pHeroData->set_mp(0);
			pHeroData->set_arrangeindex(Ptr->GetArrangeIndex());
			pHeroData->set_marchid(Ptr->GetMarchId());

			CooldownList_T CoolDownT = Ptr->GetCooldownList();
			for (int j=0;j<CoolDownT.GetListSize();j++)
			{
				CoolDown_Info rCoolDown = CoolDownT.GetCooldownByIndex(j);
				GC_CoolDownInfo* pCoolDown = pHeroData->add_cooldown();
				pCoolDown->set_cdtime(rCoolDown.m_nCDTime);
				pCoolDown->set_elapsed(rCoolDown.m_nCDTimeElapsed);
				pCoolDown->set_id(rCoolDown.m_nID);
			}
		}

	__LEAVE_FUNCTION
}

bool  HeroManager::AssignHeroToMarch(int64 nHeroId,int64 nMarchId)
{
	__ENTER_FUNCTION
	HeroPtr Ptr = GetHero(nHeroId);
	if (Ptr == null_ptr)
	{
		return false;
	}

	Ptr->SetMarchId(nMarchId);
	Ptr->SetStatus(HEROSTATUS_ASSIGN);
	return true;
	__LEAVE_FUNCTION
		return false;
}

bool HeroManager::CheckAssignHero(int64 nHeroId)
{
	__ENTER_FUNCTION
		HeroPtr Ptr = GetHero(nHeroId);
		if (Ptr == null_ptr)
		{
			return false;
		}

		if (Ptr->GetStatus() != HEROSTATUS_IDLE)
		{
			return false;
		}

		return true;

	__LEAVE_FUNCTION
		return false;
}

bool  HeroManager::AddHero(int nType,int nLevel)
{
	__ENTER_FUNCTION
		HeroPtr Ptr(new Hero());
		AssertEx(Ptr,"");
		Ptr->SetType(nType);
		Ptr->SetLevel(nLevel);
		InitHero(Ptr);
		return true;
	__LEAVE_FUNCTION
		return false;
}


HeroPtr  HeroManager::GetHero(int64 nHeroId)
{
	__ENTER_FUNCTION
		HeroPtrMap::iterator it = m_mapHero.find(nHeroId);
		if (it == m_mapHero.end())
		{
			return null_ptr;
		}
		return it->second;
	__LEAVE_FUNCTION
	return HeroPtr();
}

bool HeroManager::AddHero(HeroPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
	AssertEx(Ptr->GetUID()>0,"");
	if (m_mapHero.find(Ptr->GetUID()) != m_mapHero.end())
	{
		return false;
	}

	for (HeroPtrMap::iterator it = m_mapHero.begin(); it != m_mapHero.end();it++)
	{
		HeroPtr HPtr = it->second;
		AssertEx(HPtr,"");
		if (HPtr->GetType() == Ptr->GetType())
		{
			return false;
		}
	}

	m_mapHero.insert(std::make_pair(Ptr->GetUID(),Ptr));
	return true;
	__LEAVE_FUNCTION
		return false;
}

void  HeroManager::InitHero(HeroPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
	AssertEx(Ptr->GetType()>0,"");
	Table_RoleBaseAttr const* pTable =GetTable_RoleBaseAttrByID(Ptr->GetType());
	__LEAVE_FUNCTION
}

