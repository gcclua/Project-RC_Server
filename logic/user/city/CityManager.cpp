
#include "../User.h"
#include "CityManager.h"


/////////arrange function///////////////
CityManager::CityManager(User &rUser)
	: BaseManager(rUser)
{
	
}
CityManager::~CityManager(void)
{

}

void CityManager::Init()
{

}

void CityManager::OnLogin()
{

}

void  CityManager::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
	m_CityPtr->Tick(rTimeInfo);
	__LEAVE_FUNCTION
}

void CityManager::SerializeFromDB(const DBFullUserData& rSource)
{
	__ENTER_FUNCTION
		m_CityPtr->SerializeFromDB(rSource.m_City);
	__LEAVE_FUNCTION
}
void CityManager::SerializeToDB(DBFullUserData& rDesc)
{
	__ENTER_FUNCTION
		m_CityPtr->SerializeToDB(rDesc.m_City);
	__LEAVE_FUNCTION
}