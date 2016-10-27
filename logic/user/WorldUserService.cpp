#include "WorldUserService.h"
#include "DBStruct/DBStruct.h"
#include "GameServerConfig.h"
#include "service/MessageOp.h"
#include "Message/DBMsg.h"
#include "Message/WorldUserMsg.h"
#include "Message/SceneMsg.h"


MESSAGE_TRANSPORTTOUSER_IMPL(MarchRetNearListMsg);

WorldUserService::WorldUserService()
{

}

WorldUserService::~WorldUserService(void)
{

}

void WorldUserService::Init(void)
{
	__ENTER_FUNCTION

		InvokerPtr ptr(new WorldUserInvoker(*this,"WorldUserService"));
	AddInvoker(ptr);

	__LEAVE_FUNCTION
}

void WorldUserService::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
	Service::Tick(rTimeInfo);

	Tick_User(rTimeInfo);

	__LEAVE_FUNCTION
}



void WorldUserService::Tick_User(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (GetStatus() != ServiceStatus::RUNNING)
		{
			return;
		}

		UserPtrMap::iterator it = m_mapUser.begin();
		for (;it != m_mapUser.end();it++)
		{
			UserPtr Ptr = it->second;
			AssertEx(Ptr,"");
			Ptr->Tick(rTimeInfo);
		}


		__LEAVE_FUNCTION
}


void WorldUserService::Shutdown(void)
{
	__ENTER_FUNCTION
		
	__LEAVE_FUNCTION
}

UserPtr WorldUserService::GetUserByGuid(int64 guid)
{
	__ENTER_FUNCTION

		UserPtrMap::iterator it = m_mapUser.find(guid);
	UserPtr Ptr = null_ptr;
	if (it != m_mapUser.end())
	{
		Ptr = it->second;
	}

	return Ptr;

	__LEAVE_FUNCTION
		return UserPtr();
}