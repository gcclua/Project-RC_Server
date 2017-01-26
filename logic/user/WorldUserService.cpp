#include "WorldUserService.h"
#include "DBStruct/DBStruct.h"
#include "service/MessageOp.h"
#include "Message/DBMsg.h"
#include "Message/WorldUserMsg.h"
#include "Message/SceneMsg.h"
#include "Message/CityMsg.h"


//MESSAGE_TRANSPORTTOUSER_IMPL(MarchRetNearListMsg);
MESSAGE_TRANSPORTTOUSER_IMPL(RetMarchMoveMsg)
MESSAGE_TRANSPORTTOUSER_IMPL(KickPlayerByGuidMsg);
//MESSAGE_TRANSPORTTOUSER_IMPL(RetMarchStartMsg)

WorldUserService::WorldUserService()
	: m_PlayerManager(*this)
{
	m_nCurPlayerCount = 0;
	m_nEnteringPlayerCount = 0;
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

	//保持m_PlayerManager的心跳在最后
	m_PlayerManager.Tick(rTimeInfo);
	__LEAVE_FUNCTION
}



void WorldUserService::Tick_User(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (GetStatus() != ServiceStatus::RUNNING)
		{
			return;
		}

		UserMap::iterator it = m_mapUser.begin();
		for (;it != m_mapUser.end();it++)
		{
			User& rUser = it->second;
			rUser.Tick(rTimeInfo);
		}


		__LEAVE_FUNCTION
}

void WorldUserService::SetCurPlayerCount(tint32 nCurPlayerCount)
{
	__ENTER_FUNCTION

		m_nCurPlayerCount = nCurPlayerCount;

	//SceneActivationInterface::UpdateSceneClassInstPlayerCount(GetSceneClassID(), GetSceneInstID(), m_nCurPlayerCount);

	__LEAVE_FUNCTION
}


void WorldUserService::Shutdown(void)
{
	__ENTER_FUNCTION
		
	__LEAVE_FUNCTION
}

User* WorldUserService::GetUserByGuid(int64 guid)
{
	__ENTER_FUNCTION

		UserMap::iterator it = m_mapUser.find(guid);
	if (it != m_mapUser.end())
	{
		return &(it->second);
	}

	return null_ptr;

	__LEAVE_FUNCTION
	return null_ptr;
}

void WorldUserService::HandleMessage(const RetObjListMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const UpdateMarchMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const RetBattleInfoMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const RetBattleStartMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}
void WorldUserService::HandleMessage(const RetBattleEndMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const RetMarchStartMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
		if (Ptr) 
		{ 
			Ptr->HandleMessage(rMsg); 
		}
		__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const ObjAttackTargetMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}
void WorldUserService::HandleMessage(const ObjHurtMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}
void WorldUserService::HandleMessage(const ObjTrackTargetMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const MarchRetFightMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage( const PlayerEnterWorldMsg &rMsg )
{
	__ENTER_FUNCTION

		User* Ptr = GetUserByGuid(rMsg.m_PlayerPtr->GetUserId());
	    if (Ptr != null_ptr)
		{
			return;
		}

		User &rUser = rMsg.m_PlayerPtr->GetObjUser();
		rMsg.m_PlayerPtr->SetStatus(PlayerStatus::GAME_PLAYERING);
		m_PlayerManager.Add(rMsg.m_PlayerPtr,PlayerManager::ADD_FOR_ENTREWORLD);
		DecEnteringPlayerCount();
		m_mapUser.insert(std::make_pair(rUser.GetGuid(),rUser));

	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const TrainTroopOverMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const RetUserSkillMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const RetArrangChangeMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const MarchRetNearListMsg &rMsg)
{
	__ENTER_FUNCTION
		User* Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr) 
	{ 
		Ptr->HandleMessage(rMsg); 
	}
	__LEAVE_FUNCTION
}

void WorldUserService::HandleMessage(const PlayerLeaveWorldMsg &rMsg)
{
	__ENTER_FUNCTION
		UserMap::iterator itFind = m_mapUser.find(rMsg.m_guid);
	if (itFind != m_mapUser.end())
	{
		//_erase(m_mapUser, itFind);
		m_mapUser.erase(itFind);
	}
	else
	{
		VerifyEx(false, "");
	}

	PlayerQuitGameMsgPtr MsgPtr = POOLDEF_NEW(PlayerQuitGameMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_PlayerPtr = rMsg.m_PlayerPtr;
	MsgPtr->m_nDelResult = rMsg.m_nDelResult;
	SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

	__LEAVE_FUNCTION
}

