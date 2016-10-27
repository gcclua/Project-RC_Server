
#include "../User.h"
#include "HeroManager.h"


/////////arrange function///////////////
HeroManager::HeroManager(User &rUser)
	: BaseManager(rUser)
{
	
}
HeroManager::~HeroManager(void)
{

}

void HeroManager::Init()
{

}

void HeroManager::OnLogin()
{

}

void  HeroManager::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION

	__LEAVE_FUNCTION
}

void HeroManager::SerializeFromDB(const DBFullUserData& rSource)
{
	__ENTER_FUNCTION
		for (HeroPtrMap::iterator it = m_MapHero.begin();it != m_MapHero.end();it++)
		{
			HeroPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_Hero);
		}
	__LEAVE_FUNCTION
}
void HeroManager::SerializeToDB(DBFullUserData& rDesc)
{
	__ENTER_FUNCTION
		for (HeroPtrMap::iterator it = m_MapHero.begin();it != m_MapHero.end();it++)
		{
			HeroPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->SerializeToDB(rDesc.m_Hero);
		}
	__LEAVE_FUNCTION
}