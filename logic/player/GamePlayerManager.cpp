#include "GamePlayerManager.h"
#include "service/Service.h"
#include "Login/LoginService.h"

GamePlayerManager::GamePlayerManager(LoginService &rLoginService)
	:m_rLoginService(rLoginService)
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
				bool bRet = Ptr->Tick_InLogin(rTimeInfo);
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

PlayerPtr GamePlayerManager::GetPlayerByID(int64 nID)
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
		m_rLoginService.SetCurPlayerCount(static_cast<int>(m_PlayerList.size()));
	CACHE_LOG("Player","login playermanager add player("<<Ptr->GetID()<<"),result("<<nResult<<")");
	__LEAVE_FUNCTION
}

void GamePlayerManager::OnDelPlayer(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_rLoginService.SetCurPlayerCount(static_cast<int>(m_PlayerList.size()));
	bool bDelOnlineStatus = false;
	switch (Ptr->GetStatus())
	{
	case PlayerStatus::EMPTY:
		{
			bDelOnlineStatus = false;
		}
		break;
	case PlayerStatus::CONNECTED:
		{
			bDelOnlineStatus = false;
		}
		break;
	case PlayerStatus::LOGIN_READYENTERWORLD:
		{
			bDelOnlineStatus = true;
		}
		break;
	case PlayerStatus::GAME_ENTERINGWORLD:
		{
			bDelOnlineStatus = false;
		}
		break;
	case PlayerStatus::GAME_PLAYERING:
		{
			bDelOnlineStatus = false;
		}
		break;
	}

	if (bDelOnlineStatus && nResult != DEL_FOR_ENTERWORLD)
	{


		CACHE_LOG("Player","ol del player("<<Ptr->GetID()<<") source(playermanager)");
	}

	CACHE_LOG("Player","login playermanager del player("<<Ptr->GetID()<<") result("<<nResult<<")");

	__LEAVE_FUNCTION
}

