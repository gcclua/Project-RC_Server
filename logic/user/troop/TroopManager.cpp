
#include "../User.h"
#include "TroopManager.h"


/////////arrange function///////////////
TroopManager::TroopManager(User &rUser)
	: BaseManager(rUser)
{
	
}
TroopManager::~TroopManager(void)
{

}

void TroopManager::Init()
{

}

void TroopManager::OnLogin()
{

}

void  TroopManager::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION

	__LEAVE_FUNCTION
}

void TroopManager::SerializeFromDB(const DBFullUserData& rSource)
{
	__ENTER_FUNCTION
		for (TroopPtrMap::iterator it = m_MapTroop.begin();it != m_MapTroop.end();it++)
		{
			TroopPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_Troop);
		}
	__LEAVE_FUNCTION
}
void TroopManager::SerializeToDB(DBFullUserData& rDesc)
{
	__ENTER_FUNCTION
		for (TroopPtrMap::iterator it = m_MapTroop.begin();it != m_MapTroop.end();it++)
		{
			TroopPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->SerializeToDB(rDesc.m_Troop);
		}
	__LEAVE_FUNCTION
}