#include "LoginService.h"
#include "Obj_Login.h"
#include "DBStruct/DBStruct.h"
#include "GameServerConfig.h"
#include "service/MessageOp.h"
#include "Message/DBMsg.h"
#include "Message/LoginMsg.h"
#include "SysLog.h"

LoginService::LoginService(uint32 port)
	: m_ServerSocket(port)
	,m_PlayerManager(*this)
{
	m_nCurPlayerCount = 0;
	m_nOLQueuingUpdateIndexTime = 0;
}

LoginService::~LoginService(void)
{

}

void LoginService::Init(void)
{
	__ENTER_FUNCTION
		
		InvokerPtr ptr(new LoginInvoker(*this,"LoginInvoker"));
		AddInvoker(ptr);

		m_ServerSocket.setNonBlocking();

		AssertEx(m_ServerSocket.getSOCKET() != INVALID_SOCKET,"");

		m_PlayerManager.Init();

	__LEAVE_FUNCTION
}

void LoginService::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
	Service::Tick(rTimeInfo);

	Tick_Accept(rTimeInfo);

	Tick_Transport(rTimeInfo);

	Tick_OLQueuing(rTimeInfo);

	Tick_OLQueuingUpdateIndex(rTimeInfo);

	Tick_PCD(rTimeInfo);

	TickShutDown(rTimeInfo);
	m_PlayerManager.Tick(rTimeInfo);
	__LEAVE_FUNCTION
}

void LoginService::Tick_Transport(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		for (int i=0;i<32;i++)
		{
			PlayerPtr Ptr = m_PlayerManager.PopPlayerByStatusFOrEnterWorld();
			if (Ptr)
			{
				Ptr->SetStatus(PlayerStatus::GAME_ENTERINGWORLD);

				OLPlayPlayer(Ptr->GetObjUser().GetName(),Ptr->GetID());
				CACHE_LOG("login","ol,play player "<<Ptr->GetID());

				PCDOnPlayerEnterWorld(*Ptr);
				CACHE_LOG("login","pcd player "<<Ptr->GetID()<<" enter world");
			}
		}
	__LEAVE_FUNCTION
}

void LoginService::TickShutDown(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (GetStatus() == ServiceStatus::SHUTDOWN_PROCESS)
		{
			int nLoginQueuing = static_cast<int>(m_OlLoginQueuingPlayerList.size());
			int nLoginPlaying = static_cast<int>(m_OLLoginPlayingPlayerMap.size());
			int nGamePlaying  = static_cast<int>(m_OLGamePlayingPlayerMap.size());

			CACHE_LOG("ServerStatus","LoginService::Tick_ShutDown, nLoginQueuing("<<nLoginQueuing<<"),nLoginPlaying("<<nLoginPlaying<<")"<<",nGamePlaying("<<nGamePlaying<<")");
			if (nLoginPlaying==0 && nLoginQueuing == 0 && nGamePlaying)
			{
				ShutdownOk();
				return;
			}
			
			m_nShutDownTime += rTimeInfo.m_uTimeElapse;
			if (m_nShutDownTime >= 60000)
			{
				ShutdownOk();
				return;
			}
		}
	__LEAVE_FUNCTION
}

int  LoginService::OLCheckPlayer(const ACCOUNTNAME & szAccount) const
{
	__ENTER_FUNCTION
		int nRet = 0;
		for (OLLoginQueuingPlayerList::const_iterator it = m_OlLoginQueuingPlayerList.begin();
			it != m_OlLoginQueuingPlayerList.end();it++)
		{
			if ((*it).m_szAccount == szAccount)
			{
				nRet++;
			}
		}
		if (m_OLLoginPlayingPlayerMap.find(szAccount) != m_OLLoginPlayingPlayerMap.end())
		{
			nRet++;
		}
		if (m_OLGamePlayingPlayerMap.find(szAccount) != m_OLGamePlayingPlayerMap.end())
		{
			nRet++;
		}
		return nRet;
	__LEAVE_FUNCTION
		return 0;
}
bool LoginService::OLIsHavePlayer(const ACCOUNTNAME & szAccount) const
{
	__ENTER_FUNCTION
		return (OLCheckPlayer(szAccount)>0);
	__LEAVE_FUNCTION
		return false;
}
bool LoginService::OLQueuePlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID,int nQueuingLevel)
{
	__ENTER_FUNCTION
		AssertEx(OLCheckPlayer(szAccount) == 0,"");
		m_OlLoginQueuingPlayerList.push_back(PlayerQueuingData(szAccount,nPlayerID,nQueuingLevel,0));
	__LEAVE_FUNCTION
		return false;
}
void LoginService::OLQueuePlayerUpdateRechargeValue(const ACCOUNTNAME & szAccount,int64 nPlayerID,int nRechargeValue)
{
	__ENTER_FUNCTION
		for (OLLoginQueuingPlayerList::iterator it = m_OlLoginQueuingPlayerList.begin();
			it != m_OlLoginQueuingPlayerList.end();it++)
		{
			if ((*it).m_nPlayerID == nPlayerID)
			{
				(*it).m_nRechargeValue = nRechargeValue;
				return;
			}
		}
		__LEAVE_FUNCTION

}
void LoginService::OLLoginPlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID)
{
	__ENTER_FUNCTION
		AssertEx(OLCheckPlayer(szAccount) == 1,"");
	for (OLLoginQueuingPlayerList::iterator it = m_OlLoginQueuingPlayerList.begin();
		it != m_OlLoginQueuingPlayerList.end();it++)
	{
		if ((*it).m_nPlayerID == nPlayerID)
		{
			m_OlLoginQueuingPlayerList.erase(it);
			m_OLLoginPlayingPlayerMap.insert(std::make_pair(szAccount,nPlayerID));
			return;
		}
	}
	AssertEx(false,"");
	__LEAVE_FUNCTION
}
void LoginService::OLReLoginPlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID)
{
	__ENTER_FUNCTION
	AssertEx(OLCheckPlayer(szAccount) == 1,"");
	
	OLGamePlayingPlayerMap::iterator it = m_OLGamePlayingPlayerMap.find(szAccount);
	if (it != m_OLGamePlayingPlayerMap.end())
	{
		m_OLGamePlayingPlayerMap.erase(it);
		m_OLLoginPlayingPlayerMap.insert(std::make_pair(szAccount,nPlayerID));
	}

	AssertEx(false,"");
	__LEAVE_FUNCTION
}
void LoginService::OLPlayPlayer(const ACCOUNTNAME & szAccount,int64 nPlayerID)
{
	__ENTER_FUNCTION
		AssertEx(OLCheckPlayer(szAccount) == 1,"");

	OLLoginPlayingPlayerMap::iterator it = m_OLLoginPlayingPlayerMap.find(szAccount);
	if (it != m_OLLoginPlayingPlayerMap.end())
	{
		m_OLLoginPlayingPlayerMap.erase(it);
		m_OLGamePlayingPlayerMap.insert(std::make_pair(szAccount,nPlayerID));
	}

	AssertEx(false,"");
		
	__LEAVE_FUNCTION
}
void LoginService::OLDelPlayer(const ACCOUNTNAME & szAccount)
{
	__ENTER_FUNCTION
		AssertEx(OLCheckPlayer(szAccount) <= 1,"");
		for (OLLoginQueuingPlayerList::iterator it = m_OlLoginQueuingPlayerList.begin();
			it != m_OlLoginQueuingPlayerList.end(); it++)
		{
			if ((*it).m_szAccount == szAccount)
			{
				m_OlLoginQueuingPlayerList.erase(it);
				return;
			}
		}

		if (m_OLLoginPlayingPlayerMap.erase(szAccount)>0)
		{
			return;
		}
		if (m_OLGamePlayingPlayerMap.erase(szAccount)>0)
		{
			return;
		}

	__LEAVE_FUNCTION
}

void LoginService::Tick_OLQueuing(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		for (int i = 0; i < 4; i++)
		{
			if (!OlQueuFinishOne())
			{
				break;
			}
		}
		
	__LEAVE_FUNCTION
}

void LoginService::Tick_OLQueuingUpdateIndex(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		m_nOLQueuingUpdateIndexTime += rTimeInfo.m_uTimeElapse;
		if (m_nOLQueuingUpdateIndexTime >= 4000)
		{
			m_nOLQueuingUpdateIndexTime = 0;

			m_OlLoginQueuingPlayerList.sort();

			int nIndex = 0;
			for (OLLoginQueuingPlayerList::iterator it = m_OlLoginQueuingPlayerList.begin();
				it != m_OlLoginQueuingPlayerList.end(); it++,nIndex++)
			{
				PlayerPtr Ptr = m_PlayerManager.GetPlayerByID((*it).m_nPlayerID);
				if (Ptr)
				{
					
				}
			}
		}
	__LEAVE_FUNCTION
}

bool LoginService::OlQueuFinishOne(void)
{
	__ENTER_FUNCTION
	if (!m_OlLoginQueuingPlayerList.empty())
	{
		PlayerQueuingData Info = m_OlLoginQueuingPlayerList.front();
		OLLoginPlayer(Info.m_szAccount,Info.m_nPlayerID);
		CACHE_LOG("Login","ol login player("<<Info.m_nPlayerID<<")");

		QueueFinishMsgPtr MsgPtr = POOLDEF_NEW(QueueFinishMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_szAccount = Info.m_szAccount;
		MsgPtr->m_nPlayerID = Info.m_nPlayerID;
		SendMessage2Srv(ServiceID::LOGIN,MsgPtr);

		return true;
	}
	else
	{
		return false;
	}
	__LEAVE_FUNCTION
		return false;
}

void LoginService::OLKickPlayerByAccount(const ACCOUNTNAME& szAccount,int nReason)
{
	__ENTER_FUNCTION
	AssertEx(OLCheckPlayer(szAccount) <= 1,"");
	for (OLLoginQueuingPlayerList::iterator it = m_OlLoginQueuingPlayerList.begin();
		it != m_OlLoginQueuingPlayerList.end(); it++)
	{
		if ((*it).m_szAccount == szAccount)
		{
			PlayerPtr Ptr = m_PlayerManager.GetPlayerByID((*it).m_nPlayerID);
			if (Ptr)
			{
				Ptr->KickMe(nReason);
			}
			return;
		}
	}

	OLLoginPlayingPlayerMap::iterator itLogin = m_OLLoginPlayingPlayerMap.find(szAccount);
	if (itLogin != m_OLLoginPlayingPlayerMap.end())
	{
		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID((*itLogin).second);
		if (Ptr)
		{
			Ptr->KickMe(nReason);
		}
		return;
	}

	__LEAVE_FUNCTION
}

bool LoginService::PCDIsHave(int64 guid) const
{
	__ENTER_FUNCTION
		return (m_PCDMap.find(guid) != m_PCDMap.end());
	__LEAVE_FUNCTION
		return false;
}
bool LoginService::PCDLoad(int64 guid,DBFullUserData &rUserData) const
{
	__ENTER_FUNCTION
		PCDMap::const_iterator it = m_PCDMap.find(guid);
		if (it != m_PCDMap.end())
		{
			VerifyEx((*it).second.m_bOnline == false,"");
			VerifyEx((*it).second.m_bFinalSaveProcess == false,"");

			rUserData.CopyFrom((*it).second.m_DBFullUserData);
			return true;
		}
		else
		{
			return false;
		}
	__LEAVE_FUNCTION
		return false;
}
void LoginService::PCDOnPlayerEnterWorld(Player &rPlayer)
{
	__ENTER_FUNCTION
		PCDMap::iterator it = m_PCDMap.find(rPlayer.GetID());
		if (it != m_PCDMap.end())
		{
			VerifyEx((*it).second.m_bOnline == false,"");
			VerifyEx((*it).second.m_bFinalSaveProcess == false,"");
			(*it).second.m_bOnline = true;
			(*it).second.m_bFinalSaveProcess = false;
			(*it).second.m_bFinalSaveOk = false;
			(*it).second.m_bFinalSaveTime = 0;
			rPlayer.GetObjUser().SerializeToDB((*it).second.m_DBFullUserData);
		}
		else
		{
			std::pair<PCDMap::iterator,bool> InsertRet = m_PCDMap.insert(std::make_pair(rPlayer.GetID(),PlayerCacheData()));
			VerifyEx(InsertRet.second == true,"");
			(*InsertRet.first).second.m_bOnline = true;
			(*InsertRet.first).second.m_bFinalSaveProcess = false;
			(*InsertRet.first).second.m_bFinalSaveOk = false;
			(*InsertRet.first).second.m_bFinalSaveTime = 0;
			rPlayer.GetObjUser().SerializeToDB((*it).second.m_DBFullUserData);
		}
	__LEAVE_FUNCTION
}
void LoginService::PCDOnPlayerLeaveWorld(Player &rPlayer)
{
	__ENTER_FUNCTION
		PCDMap::iterator it = m_PCDMap.find(rPlayer.GetID());
	if (it != m_PCDMap.end())
	{
		VerifyEx((*it).second.m_bOnline == false,"");
		VerifyEx((*it).second.m_bFinalSaveProcess == false,"");
		(*it).second.m_bOnline = false;
		(*it).second.m_bFinalSaveProcess = true;
		(*it).second.m_bFinalSaveOk = false;
		(*it).second.m_bFinalSaveTime = 0;
		rPlayer.GetObjUser().SerializeToDB((*it).second.m_DBFullUserData);

		DBSaveUserMsgPtr MsgPtr= POOLDEF_NEW(DBSaveUserMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_bFinalSave = true;
		MsgPtr->m_bImmediateSave = true;
		MsgPtr->m_UserGuid = rPlayer.GetID();
		MsgPtr->m_UserData.CopyFrom((*it).second.m_DBFullUserData);

		SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);
	}
	else
	{
		VerifyEx(false,"");

		DBSaveUserMsgPtr MsgPtr= POOLDEF_NEW(DBSaveUserMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_bFinalSave = true;
		MsgPtr->m_bImmediateSave = true;
		MsgPtr->m_UserGuid = rPlayer.GetID();
		rPlayer.GetObjUser().SerializeToDB(MsgPtr->m_UserData);

		SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);

	}
	__LEAVE_FUNCTION
}
void LoginService::PCDOnPlayerDataUpdate(int64 guid,const DBFullUserData &rUserData,bool bImmediateSave)
{
	__ENTER_FUNCTION
		PCDMap::iterator it = m_PCDMap.find(guid);
	if (it != m_PCDMap.end())
	{
		VerifyEx((*it).second.m_bOnline == true,"");
		VerifyEx((*it).second.m_bFinalSaveProcess == true,"");

		(*it).second.m_DBFullUserData.CopyFrom(rUserData);
	

		DBSaveUserMsgPtr MsgPtr= POOLDEF_NEW(DBSaveUserMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_bFinalSave = false;
		MsgPtr->m_bImmediateSave = bImmediateSave;
		MsgPtr->m_UserGuid = guid;
		MsgPtr->m_UserData.CopyFrom((*it).second.m_DBFullUserData);

		SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);
	}
	else
	{
		VerifyEx(false,"");

		DBSaveUserMsgPtr MsgPtr= POOLDEF_NEW(DBSaveUserMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_bFinalSave = false;
		MsgPtr->m_bImmediateSave = bImmediateSave;
		MsgPtr->m_UserGuid = guid;
		MsgPtr->m_UserData.CopyFrom(rUserData);

		SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);

	}
	__LEAVE_FUNCTION
}
bool LoginService::PDCOnPlayerDataSaveRet(int64 guid,int nResult, bool bFinalSave)
{
	__ENTER_FUNCTION
		if (nResult == DBMsgResult::RESULT_SUCESS)
		{
			if (bFinalSave)
			{
				PCDMap::iterator it = m_PCDMap.find(guid);
				if (it != m_PCDMap.end())
				{
					if ((*it).second.m_bFinalSaveProcess)
					{
						(*it).second.m_bFinalSaveOk = true;
						(*it).second.m_bFinalSaveTime = _ansitime();
						return true;
					}
				}
				else
				{
					VerifyEx(false,"");
				}
			}
		}
		else
		{
			VerifyEx(false,"");
		}
		return false;
		__LEAVE_FUNCTION
			return false;
}
void LoginService::PCDRemove(time_t nAnsiTime,time_t nOverTime)
{
	__ENTER_FUNCTION

		for (PCDMap::iterator it = m_PCDMap.begin(); it != m_PCDMap.end();)
		{
			PlayerCacheData &rpcd = (*it).second;
			if(rpcd.m_bOnline)
			{
				if (rpcd.m_bFinalSaveProcess && rpcd.m_bFinalSaveOk)
				{
					AssertEx(rpcd.m_bFinalSaveTime > 0,"");
					if ((nAnsiTime - rpcd.m_bFinalSaveTime) >= nOverTime)
					{
						it = m_PCDMap.erase(it);
						continue;
					}
				}
			}
			it++;
			continue;
		}

	__LEAVE_FUNCTION
}
void LoginService::Tick_PCD(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (rTimeInfo.m_bDiffSecond)
		{
			PCDRemove(rTimeInfo.m_nAnsiTime,GameServerConfig::Instance().PlayerCacheDataTimeOut());
			int  nLoginGamePlayeringCount = static_cast<int> (m_OLGamePlayingPlayerMap.size());
			int  nLoginPlayerCacheDataCount = static_cast<int> (m_PCDMap.size());
			int nExceptionCount = GameServerConfig::Instance().PlayerCacheDataTimeOut()*10;
			if (nLoginPlayerCacheDataCount > (nLoginGamePlayeringCount + nExceptionCount))
			{
				PCDRemove(rTimeInfo.m_nAnsiTime,0);
			}
		}
	__LEAVE_FUNCTION
}


void LoginService::Tick_Accept(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT
		if (GetStatus() != ServiceStatus::RUNNING)
		{
			return;
		}

		int nAcceptPerTick = GameServerConfig::Instance().AcceptPlayerPerTick();

		if (nAcceptPerTick < ACCEPT_TICK_MIN)
		{
			nAcceptPerTick = ACCEPT_TICK_MIN;
		}

		if (nAcceptPerTick > ACCEPT_TICK_MAX)
		{
			nAcceptPerTick = ACCEPT_TICK_MAX;
		}

		for (int i=0; i< nAcceptPerTick;i++)
		{
			if (IsHaveNewPlayer())
			{
				if (AcceptNewPlayer())
				{
					continue;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}

	__LEAVE_PROTECT
}
#if defined(__USE_SELECT__)
bool LoginService::IsHaveNewPlayer(void)
{
	__ENTER_PROTECT

		SOCKET ServerSocketID = m_ServerSocket.getSOCKET();
	    fd_set set;
		FD_ZERO(&set);
		FD_SET(ServerSocketID,&set);


		timeval timev;
		timev.tv_sec = 0;
		timev.tv_usec = 0;

		int nRet = select(static_cast<int>(ServerSocketID+1),&set,null_ptr,null_ptr,&timev);
		if (nRet > SOCKET_ERROR)
		{
			if (FD_ISSET(ServerSocketID,&set))
			{
				return true;
			}
		}

		return false;
	__LEAVE_PROTECT
		return false;
}
#endif

#if defined(__USE_POOL)
bool LoginService::IsHaveNewPlayer(void)
{
	__ENTER_PROTECT

		pollfd pfds[1];
	pfds[0]= m_ServerSocket.getSOCKET();
	pfds[0].events = POLLIN;
	pfds[0].revents = 0;
	
	int nRet = poll(pfds,1,0);
	if (nRet> SOCKET_ERROR)
	{
		if (pfds[0].revents & POLLIN)
		{
			return true;
		}
	}

	return false;

	__LEAVE_PROTECT
		return false;
}
#endif
bool LoginService::AcceptNewPlayer(void)
{
	__ENTER_PROTECT
		PlayerPtr Ptr = POOLDEF_NEW(Player);
		AssertEx(Ptr,"");

		bool bRet = m_ServerSocket.accept(&(Ptr->GetSocket()));
		AssertEx(bRet,"");

		SOCKET fd = Ptr->GetSocket().getSOCKET();
		AssertEx(fd != INVALID_SOCKET, "");

		bRet = Ptr->GetSocket().setNonBlocking();
		AssertEx(bRet,"");

		bRet = Ptr->GetSocket().getSockError();
		AssertEx(bRet,"");

		bRet = Ptr->GetSocket().setLinger(0);
		AssertEx(bRet,"");

		Ptr->SetStatus(PlayerStatus::CONNECTED);
		m_PlayerManager.Add(Ptr,PlayerManager::ADD_FOR_NEWPLAYER);

		CACHE_LOG("Login","player("<<Ptr->GetID()<<") connected");

		return true;

	__LEAVE_PROTECT
		return false;
}


void LoginService::HandleMessage(const SavePlayerDataMsg &rMsg)
{
	__ENTER_FUNCTION

		PCDOnPlayerDataUpdate(rMsg.m_Guid, rMsg.m_UserData, rMsg.m_bImmediateSave);
		string simmediate = rMsg.m_bImmediateSave ? "true" : "false";
		CACHE_LOG("Login","pcd user("<<rMsg.m_Guid<<"data update immediate"<<simmediate)

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const PlayerLeaveWorldMsg &rMsg)
{

}