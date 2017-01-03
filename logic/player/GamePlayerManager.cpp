#include "GamePlayerManager.h"
#include "service/Service.h"
#include "user/WorldUserService.h"
#include "Message/WorldUserMsg.h"
#include "service/MessageOp.h"

GamePlayerManager::GamePlayerManager(WorldUserService &rWorldService)
	:m_rWorldService(rWorldService)
{

}

GamePlayerManager::~GamePlayerManager(void)
{

}

void GamePlayerManager::ProcessTicks(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (m_PlayerList.empty())
		{
			return;
		}
		for (PlayerPtrList::iterator it = m_PlayerList.begin(); it != m_PlayerList.end();)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			__ENTER_PROTECT_EX
				bool bRet = Ptr->Tick_InGame(rTimeInfo);
			if (!bRet)
			{
				it = Del(Ptr,DEL_FOR_LOGINTICK1);
				continue;
			}
			__CATCH_PROTECT_EX
				it = Del(Ptr,DEL_FOR_LOGINTICK2);
			continue;
			__LEAVE_PROTECT_EX
				it++;
		}
		__LEAVE_FUNCTION

}

PlayerPtr GamePlayerManager::GetPlayerByID(int nID)
{
	__ENTER_FUNCTION
		for (PlayerPtrList::iterator it = m_PlayerList.begin();it != m_PlayerList.end(); it++)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			if (Ptr->GetID() == nID)
			{
				return Ptr;
			}
		}
		return null_ptr;
		__LEAVE_FUNCTION
			return null_ptr;
}
PlayerPtr GamePlayerManager::PopPlayerByStatusFOrEnterWorld(void)
{
	__ENTER_FUNCTION
		for (PlayerPtrList::iterator it = m_PlayerList.begin();it != m_PlayerList.end(); it++)
		{
			PlayerPtr Ptr = (*it);
			AssertEx(Ptr,"");
			if (Ptr->GetStatus() == PlayerStatus::LOGIN_READYENTERWORLD)
			{
				Del(Ptr,DEL_FOR_ENTERWORLD);
				return Ptr;
			}
		}
		return null_ptr;
		__LEAVE_FUNCTION
			return null_ptr;
}

void GamePlayerManager::OnAddPlayer(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_rWorldService.SetCurPlayerCount(static_cast<int>(m_PlayerList.size()));

	CacheLog(LOGDEF_INST(Player), "login playermanager add player(%d),result(%d)",
		Ptr->GetID(), nResult);

	__LEAVE_FUNCTION
}

void GamePlayerManager::OnDelPlayer(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_rWorldService.SetCurPlayerCount(static_cast<int>(m_PlayerList.size()));

	bool bLastLeave = (nResult != DEL_FOR_ENTERWORLD);


	Ptr->PrintLastPacketLog("scene del player");

	CacheLog(LOGDEF_INST(Player), " playermanager del player(%d), result(%d)",
		Ptr->GetID(), nResult);

	if (bLastLeave)
	{
		PlayerLeaveWorldMsgPtr MsgPtr = POOLDEF_NEW(PlayerLeaveWorldMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_guid = Ptr->GetObjUser().GetGuid();
		MsgPtr->m_PlayerPtr = Ptr;
		MsgPtr->m_nDelResult = nResult;
		SendMessage2Srv(ServiceID::WORLDUSER, MsgPtr);
	}

	__LEAVE_FUNCTION
}

