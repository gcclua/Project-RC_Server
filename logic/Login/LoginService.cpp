#include "LoginService.h"
#include "Obj_Login.h"
#include "DBStruct/DBStruct.h"
#include "service/MessageOp.h"
#include "Message/DBMsg.h"
#include "Message/LoginMsg.h"
#include "Config.h"

LoginService::LoginService(uint32 port)
	: m_ServerSocket(port)
	,m_PlayerManager(*this)
{
	m_nCurPlayerCount = 0;
	m_nOLQueuingUpdateIndexTime = 0;
	m_nShutdownTime = 0;
	m_nRandomIndex = 0;
	m_RandomNamesMap.clear();
	m_RandomIndexMap.clear();
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

void LoginService::Openup(void)
{
	__ENTER_FUNCTION
		//DBReqLoadRandomNameMsgPtr MsgPtr = POOLDEF_NEW(DBReqLoadRandomNameMsg);
	//AssertEx(MsgPtr,"");
	//SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);
	OpenupOk();
	__LEAVE_FUNCTION
}

void LoginService::Shutdown(void)
{
	__ENTER_FUNCTION

		KickAllUser();

	m_nShutdownTime = 0;

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

				OLPlayPlayer(Ptr->GetObjUser().GetAccount(),Ptr->GetID(),Ptr->GetUserId());
				CacheLog(LOGDEF_INST(Login),
					"ol play player(%d)",
					Ptr->GetID());

				PCDOnPlayerEnterWorld(*Ptr);
				CacheLog(LOGDEF_INST(Login),
					"pcd player(%d) enter world",
					Ptr->GetID());

				PlayerEnterWorldMsgPtr MsgPtr = POOLDEF_NEW(PlayerEnterWorldMsg);
				AssertEx(MsgPtr, "");
				MsgPtr->m_PlayerPtr = Ptr;
				SendMessage2Srv(ServiceID::WORLDUSER, MsgPtr);
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

			CacheLog(LOGDEF_INST(ServerStatus), "LoginService::Tick_Shutdown, nLoginQueuing(%d), nLoginPlaying(%d), nScenePlaying(%d)",
				nLoginQueuing, nLoginPlaying, nGamePlaying);
			if (nLoginPlaying==0 && nLoginQueuing == 0 && nGamePlaying)
			{
				ShutdownOk();
				return;
			}
			
			m_nShutdownTime += rTimeInfo.m_uTimeElapse;
			if (m_nShutdownTime >= 60000)
			{
				ShutdownOk();
				return;
			}
		}
	__LEAVE_FUNCTION
}


void LoginService::KickAllUser(void)
{
	__ENTER_FUNCTION

		m_PlayerManager.DelAll();

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
bool LoginService::OLQueuePlayer(const ACCOUNTNAME & szAccount,int nPlayerID,int nQueuingLevel)
{
	__ENTER_FUNCTION
		AssertEx(OLCheckPlayer(szAccount) == 0,"");
		m_OlLoginQueuingPlayerList.push_back(PlayerQueuingData(szAccount,nPlayerID,nQueuingLevel,0));
		return true;
	__LEAVE_FUNCTION
		return false;
}
void LoginService::OLQueuePlayerUpdateRechargeValue(const ACCOUNTNAME & szAccount,int nPlayerID,int nRechargeValue)
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
void LoginService::OLLoginPlayer(const ACCOUNTNAME & szAccount,int nPlayerID)
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
void LoginService::OLReLoginPlayer(const ACCOUNTNAME & szAccount,int nPlayerID)
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
void LoginService::OLPlayPlayer(const ACCOUNTNAME & szAccount,int nPlayerID,int64 userId)
{
	__ENTER_FUNCTION
		AssertEx(OLCheckPlayer(szAccount) == 1,"");

	OLLoginPlayingPlayerMap::iterator it = m_OLLoginPlayingPlayerMap.find(szAccount);
	if (it != m_OLLoginPlayingPlayerMap.end())
	{
		AssertEx((*it).second == nPlayerID, "");
		m_OLLoginPlayingPlayerMap.erase(it);
		m_OLGamePlayingPlayerMap.insert(std::make_pair(szAccount,userId));
		return;
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
		CacheLog(LOGDEF_INST(Login),
			"ol login player(%d)",
			Info.m_nPlayerID);

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

	OLGamePlayingPlayerMap::iterator itGamePlaying = m_OLGamePlayingPlayerMap.find(szAccount);
	if (itGamePlaying != m_OLGamePlayingPlayerMap.end())
	{
		SceneInterface::KickPlayerByGuid((*itGamePlaying).second, nReason);
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
			VerifyEx((*it).second.m_bFinalSaveProcess == true,"");

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
		PCDMap::iterator it = m_PCDMap.find(rPlayer.GetUserId());
		if (it != m_PCDMap.end())
		{
			VerifyEx((*it).second.m_bOnline == false,"");
			VerifyEx((*it).second.m_bFinalSaveProcess == true,"");
			(*it).second.m_bOnline = true;
			(*it).second.m_bFinalSaveProcess = false;
			(*it).second.m_bFinalSaveOk = false;
			(*it).second.m_bFinalSaveTime = 0;
			rPlayer.GetObjUser().SerializeToDB((*it).second.m_DBFullUserData);
		}
		else
		{
			std::pair<PCDMap::iterator,bool> InsertRet = m_PCDMap.insert(std::make_pair(rPlayer.GetUserId(),PlayerCacheData()));
			VerifyEx(InsertRet.second == true,"");
			(*InsertRet.first).second.m_bOnline = true;
			(*InsertRet.first).second.m_bFinalSaveProcess = false;
			(*InsertRet.first).second.m_bFinalSaveOk = false;
			(*InsertRet.first).second.m_bFinalSaveTime = 0;
			rPlayer.GetObjUser().SerializeToDB((*InsertRet.first).second.m_DBFullUserData);
		}
	__LEAVE_FUNCTION
}
void LoginService::PCDOnPlayerLeaveWorld(Player &rPlayer)
{
	__ENTER_FUNCTION
		PCDMap::iterator it = m_PCDMap.find(rPlayer.GetUserId());
	if (it != m_PCDMap.end())
	{
		VerifyEx((*it).second.m_bOnline == true,"");
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

		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);
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

		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);

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
		VerifyEx((*it).second.m_bFinalSaveProcess == false,"");

		(*it).second.m_DBFullUserData.CopyFrom(rUserData);
	

		DBSaveUserMsgPtr MsgPtr= POOLDEF_NEW(DBSaveUserMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_bFinalSave = false;
		MsgPtr->m_bImmediateSave = bImmediateSave;
		MsgPtr->m_UserGuid = guid;
		MsgPtr->m_UserData.CopyFrom((*it).second.m_DBFullUserData);

		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);
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

		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);

	}
	__LEAVE_FUNCTION
}
bool LoginService::PDCOnPlayerDataSaveRet(int64 guid,int nResult, bool bFinalSave)
{
	__ENTER_FUNCTION
		if (nResult == DBMsgResult::RESULT_SUCCESS)
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
			PCDRemove(rTimeInfo.m_nAnsiTime,_GameConfig().m_nPlayerCachedDataTimeout);
			int  nLoginGamePlayeringCount = static_cast<int> (m_OLGamePlayingPlayerMap.size());
			int  nLoginPlayerCacheDataCount = static_cast<int> (m_PCDMap.size());
			int nExceptionCount = _GameConfig().m_nPlayerCachedDataTimeout*10;
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

		int nAcceptPerTick = _GameConfig().m_nAcceptPlayerPerTick;

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
	FD_SET(ServerSocketID, &set);

	timeval timev;
	timev.tv_sec = 0;
	timev.tv_usec = 0;

	tint32 nRet = select(static_cast<tint32>(ServerSocketID + 1), &set, null_ptr, null_ptr, &timev);
	if (nRet > SOCKET_ERROR)
	{
		if (FD_ISSET(ServerSocketID, &set))
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
		AssertEx(Ptr, "");

		bool bRet = m_ServerSocket.accept(&(Ptr->GetSocket()));
		AssertEx(bRet, "");

		SOCKET fd = Ptr->GetSocket().getSOCKET();
		AssertEx(fd != INVALID_SOCKET, "");

		bRet = Ptr->GetSocket().setNonBlocking();
		AssertEx(bRet, "");

		bRet = Ptr->GetSocket().getSockError();
		AssertEx(!bRet, "");

		bRet = Ptr->GetSocket().setLinger(0);
		AssertEx(bRet, "");

		Ptr->SetStatus(PlayerStatus::CONNECTED);
		m_PlayerManager.Add(Ptr, PlayerManager::ADD_FOR_NEWPLAYER);
		CacheLog(LOGDEF_INST(Login),
			"player(%d) connected",
			Ptr->GetID());

		return true;

	__LEAVE_PROTECT
		return false;
}


void LoginService::GetRandomNames(bsarray<CHARNAME, RANDOM_NAME_SEND_COUNT> &aNames, tint8 length)
{
	__ENTER_FUNCTION	
		//万一哪天不够了，还是要从头开始发
		if ( m_nRandomIndex > (tint32)(m_RandomNamesMap.size()) )
		{
			m_nRandomIndex = 0;
		}
		tint32 nSearchIndex = m_nRandomIndex;	
		tint32 nIndex = 0;	
		for ( RandomNamesMap::iterator ite = m_RandomNamesMap.begin(); ite != m_RandomNamesMap.end(); ++ite )
		{
			//忽略索引之前的内容
			if ( nIndex < nSearchIndex )
			{
				nIndex++;
				continue;
			}
			//从索引处开始取Length个
			if ( (nIndex - nSearchIndex) >= 0 && ((nIndex - nSearchIndex) < aNames.ElemSize() && (nIndex - nSearchIndex) < length) )
			{
				aNames[nIndex - nSearchIndex] = ite->second;
				nIndex ++;
			}
			else
			{
				break;
			}
		}
		//每次索取之后，索引往后递加，防止每次取得相同范围
		m_nRandomIndex += RANDOM_NAME_SEND_COUNT;
		if ( m_nRandomIndex >= RANDOM_NAME_SEARCH_MAX )
		{
			m_nRandomIndex = 0;
		}
		__LEAVE_FUNCTION
}
void LoginService::RemoveNameFromSet(const tchar* szName)
{
	__ENTER_FUNCTION
		if ( szName )
		{
			CHARNAME charname(szName);
			RandomIndexMap::const_iterator ite = m_RandomIndexMap.find(charname);
			if ( ite != m_RandomIndexMap.end() )
			{
				tint32 nIndex = ite->second;
				m_RandomNamesMap.erase(nIndex);
			}
		}
		__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const DBRetAskCharListMsg &rMsg)
{
	__ENTER_FUNCTION

		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID(rMsg.m_nPlayerID);
	if (Ptr)
	{
		Ptr->GetObjLogin().OnCharListRet(rMsg.m_Result, rMsg.m_CharDataList);
	}
	else
	{
		CacheLog(LOGDEF_INST(Login),
			"loginservice miss player(%d) on handlemessage(DBRetAskCharListMsg)",
			rMsg.m_nPlayerID);
	}

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const QueueFinishMsg &rMsg)
{
	__ENTER_FUNCTION

		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID(rMsg.m_nPlayerID);
	if (Ptr)
	{
		Ptr->GetObjLogin().OnQueueFinish();
	}
	else
	{
		CacheLog(LOGDEF_INST(Login),
			"loginservice miss player(%d) on handlemessage(QueueFinishMsg)",
			rMsg.m_nPlayerID);
	}

	__LEAVE_FUNCTION
}


void LoginService::HandleMessage(const SavePlayerDataMsg &rMsg)
{
	__ENTER_FUNCTION

		PCDOnPlayerDataUpdate(rMsg.m_Guid, rMsg.m_UserData, rMsg.m_bImmediateSave);

		CacheLog(LOGDEF_INST(Login),
		"pcd user(%08X) data update immediate(%s)",
		rMsg.m_Guid,
		rMsg.m_bImmediateSave ? "true" : "false");

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const PlayerQuitGameMsg &rMsg)
{
	__ENTER_FUNCTION
		OLDelPlayer(rMsg.m_PlayerPtr->GetObjLogin().GetAccount());
		PCDOnPlayerLeaveWorld(*(rMsg.m_PlayerPtr));
	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const KickPlayerByAccountMsg &rMsg)
{
	__ENTER_FUNCTION

		OLKickPlayerByAccount(rMsg.m_szAccount, rMsg.m_nReason);

	CacheLog(LOGDEF_INST(Login),
		"ol kick player by account(%s), reason(%d)",
		rMsg.m_szAccount.GetCText(), rMsg.m_nReason);

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const AccountStateCheckMsg &rMsg)
{
	__ENTER_FUNCTION

		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID(rMsg.m_nPlayerID);
	if (Ptr)
	{
		bool bCheckOK = !OLIsHavePlayer(Ptr->GetObjLogin().GetAccount());
		if (bCheckOK)
		{
			bool bQueueOK = OLQueuePlayer(
				Ptr->GetObjLogin().GetAccount(),
				Ptr->GetID(),
				Ptr->GetObjLogin().GetQueuingLevel());
			if (bQueueOK)
			{
				CacheLog(LOGDEF_INST(Login),
					"ol queue player(%d) ok",
					Ptr->GetID());

				Ptr->GetObjLogin().OnAccountStateCheckRet(true, true);
			}
			else
			{
				CacheLog(LOGDEF_INST(Login),
					"ol queue player(%d) failed",
					Ptr->GetID());

				Ptr->GetObjLogin().OnAccountStateCheckRet(true, false);
			}
		}
		else
		{
			OLKickPlayerByAccount(Ptr->GetObjLogin().GetAccount(),1);
			Ptr->GetObjLogin().OnAccountStateCheckRet(false, false);
		}
	}
	else
	{
		CacheLog(LOGDEF_INST(Login),
			"loginservice miss player(%d) on handlemessage(AccountStateCheckMsg)",
			rMsg.m_nPlayerID);
	}

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const AccountOfflineMsg &rMsg)
{
	__ENTER_FUNCTION

		OLDelPlayer(rMsg.m_szAccount);

	CacheLog(LOGDEF_INST(Login),
		"ol del player(%d) source(msg)",
		rMsg.m_nPlayerID);

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const DBRetCreateCharMsg &rMsg)
{
	__ENTER_FUNCTION

		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID(rMsg.m_nPlayerID);
	if (Ptr)
	{
		Ptr->GetObjLogin().OnCreateCharRet(rMsg.m_Result, rMsg.m_UserData);
	}
	else
	{
		CacheLog(LOGDEF_INST(Login),
			"loginservice miss player(%d) on handlemessage(DBRetCreateCharMsg)",
			rMsg.m_nPlayerID);
	}

	RemoveNameFromSet(rMsg.m_UserData.m_User.m_CharName);

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const DBRetReqLoadRandomNameMsg &rMsg)
{
	__ENTER_FUNCTION

		if ( rMsg.m_Result == DBMsgResult::RESULT_SUCCESS )
		{
			CHARNAME charname;
			for (tint32 nIndex = 0; nIndex < RANDOM_NAME_BUFFER_MAX; ++ nIndex)
			{
				if ( rMsg.m_Data.m_RandomNameList[nIndex].m_szName )
				{
					charname = rMsg.m_Data.m_RandomNameList[nIndex].m_szName;
					m_RandomIndexMap.insert(RandomIndexPair(charname,nIndex));
					m_RandomNamesMap.insert(RandomNamesPair(nIndex,charname));
				}
			}
			OpenupOk();
		}
		else
		{
			CacheLog(LOGDEF_INST(Login),"loginservice bad result on handlemessage(DBRetReqLoadRandomNameMsg)");
		}
		__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const DBLoadUserMsg &rMsg)
{
	__ENTER_FUNCTION

		if (PCDIsHave(rMsg.m_UserGuid))
		{
			DBRetLoadUserMsgPtr MsgPtr = POOLDEF_NEW(DBRetLoadUserMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_AccountName = rMsg.m_AccName;
			MsgPtr->m_nResult = DBMsgResult::RESULT_SUCCESS;
			MsgPtr->m_nPlayerID = rMsg.m_nPlayerID;
			AssertEx(PCDLoad(rMsg.m_UserGuid, MsgPtr->m_UserData), "");
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

			CacheLog(LOGDEF_INST(Login),
				"pcd load player(%d) dbfulluserdata from logincache",
				rMsg.m_UserGuid);
		}
		else
		{
			DBLoadUserMsgPtr MsgPtr = POOLDEF_NEW(DBLoadUserMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_UserGuid	= rMsg.m_UserGuid;
			MsgPtr->m_AccName   = rMsg.m_AccName;
			MsgPtr->m_nPlayerID = rMsg.m_nPlayerID;
			SendMessage2Srv(ServiceID::DBAGENT, MsgPtr);

			CacheLog(LOGDEF_INST(Login),
				"pcd load player(%d) dbfulluserdata from dbagent",
				rMsg.m_UserGuid);
		}

		__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const DBRetLoadUserMsg &rMsg)
{
	__ENTER_FUNCTION

		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID(rMsg.m_nPlayerID);
	if (Ptr)
	{

			Ptr->GetObjLogin().OnLoadCharRet(rMsg.m_nResult, rMsg.m_UserData, false, 0);
	}
	else
	{
		CacheLog(LOGDEF_INST(Login),
			"loginservice miss player(%d) on handlemessage(DBRetLoadUserMsg)",
			rMsg.m_UserData.m_User.m_Guid);
	}

	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const RetIdleTileMsg &rMsg)
{
	__ENTER_FUNCTION
		PlayerPtr Ptr = m_PlayerManager.GetPlayerByID(rMsg.m_nPlayerID);
	if (Ptr)
	{

		Ptr->GetObjUser().InitAsCreateNewChar(rMsg.m_tileId,rMsg.m_posX,rMsg.m_posY);
	}
	else
	{
		CacheLog(LOGDEF_INST(Login),
			"loginservice miss player(%d) on handlemessage(ReqIdleTileMsg)",
			rMsg.m_userId);
	}
	__LEAVE_FUNCTION
}

void LoginService::HandleMessage(const DBRetCreateCityMsg &rMsg)
{
	__ENTER_FUNCTION
		DBLoadUserMsgPtr MsgPtr = POOLDEF_NEW(DBLoadUserMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_UserGuid	  = rMsg.m_Data.m_UserId;
		MsgPtr->m_nPlayerID   = rMsg.m_nPlayerID;
		//MsgPtr->m_AccName = m_szAccount;
		SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
	__LEAVE_FUNCTION
}