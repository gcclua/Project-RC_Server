#include "LoginPlayerManager.h"
#include "service/Service.h"
#include "Login/LoginService.h"

LoginPlayerManager::LoginPlayerManager(LoginService &rLoginService)
	:m_rLoginService(rLoginService)
{
	
}

LoginPlayerManager::~LoginPlayerManager(void)
{

}

void LoginPlayerManager::ProcessTicks(const TimeInfo &rTimeInfo)
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

PlayerPtr LoginPlayerManager::GetPlayerByID(int nID)
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
PlayerPtr LoginPlayerManager::PopPlayerByStatusFOrEnterWorld(void)
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

void LoginPlayerManager::OnAddPlayer(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_rLoginService.SetCurPlayerCount(static_cast<int>(m_PlayerList.size()));
		CacheLog(LOGDEF_INST(Player), "login playermanager add player(%d), result(%d)",
		Ptr->GetID(), nResult);
	__LEAVE_FUNCTION
}

void LoginPlayerManager::OnDelPlayer(PlayerPtr Ptr,int nResult)
{
	__ENTER_FUNCTION
		m_rLoginService.SetCurPlayerCount(static_cast<tint32>(m_PlayerList.size()));

	bool bDelOnlineStatus = false;

	switch (Ptr->GetStatus())
	{
	case PlayerStatus::EMPTY:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::CONNECTED:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::LOGIN_VALIDATING:
		bDelOnlineStatus = false;
		break;
	case PlayerStatus::LOGIN_VALIDATE_OK:
		bDelOnlineStatus = false;
		break;
	case PlayerStatus::LOGIN_VALIDATE_FAILED:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::LOGIN_ACCOUNTSTATECHECKING:
		bDelOnlineStatus = false;
		break;
	case PlayerStatus::LOGIN_ACCOUNTSTATECHECK_OK:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_ACCOUNTSTATECHECK_FAILED:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::LOGIN_QUEUING:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_QUEUE_FINISH:
		bDelOnlineStatus = true;
		break;

	case PlayerStatus::LOGIN_QUERYING_CHARLIST:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_QUERY_CHARLIST_OK:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_QUERY_CHARLIST_FAILED:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::LOGIN_READYTONEXT:
		bDelOnlineStatus = true;
		break;

	case PlayerStatus::LOGIN_CREATING_CHAR:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_CREATE_CHAR_OK:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_CREATE_CHAR_FAILED:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::LOGIN_LOADING_CHAR:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_LOAD_CHAR_OK:
		bDelOnlineStatus = true;
		break;
	case PlayerStatus::LOGIN_LOAD_CHAR_FAILED:
		bDelOnlineStatus = false;
		break;

	case PlayerStatus::LOGIN_READYENTERWORLD:
		bDelOnlineStatus = true;
		break;
	}

		if (bDelOnlineStatus && nResult != DEL_FOR_ENTERWORLD)
		{
			m_rLoginService.OLDelPlayer(Ptr->GetObjLogin().GetAccount());
			CacheLog(LOGDEF_INST(Login),
				"ol del player(%d) source(playermanager)",
				Ptr->GetID());
		}

		CacheLog(LOGDEF_INST(Player), "login playermanager del player(%d), result(%d)",
			Ptr->GetID(), nResult);

	__LEAVE_FUNCTION
}

