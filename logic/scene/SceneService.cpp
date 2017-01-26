#include "SceneService.h"
#include "Scene/SceneClass/CopySceneClass.h"
#include "Scene/GameInterface_Scene.h"
#include "Scene/GameInterface_SceneActivation.h"
#include "Message/SceneMsg.h"
#include "sceneClass/MainSceneClass.h"
#include "service/MessageOp.h"
#include "Table/Table_SceneClass.h"
#include "Message/DBMsg.h"
#include "Config.h"


#define CHANGENAME_COOLDOWN (20)

SceneService::SceneService( void )
{
	m_nShutdownTime = 0;
}

SceneService::~SceneService( void )
{

}

int SceneService::GetServiceID( void )
{
	return ServiceID::SCENE;
}

void SceneService::Init( void )
{
	__ENTER_FUNCTION

	InvokerPtr ptr(new SceneInvoker(*this, "SceneInvoker"));
	AddInvoker(ptr);

	InitSceneClass();


	__LEAVE_FUNCTION
}


void SceneService::Openup(void)
{
	__ENTER_FUNCTION
		//OpenupOk();
		DBReqLoadMapMarchMsgPtr MsgPtr = POOLDEF_NEW(DBReqLoadMapMarchMsg);
	AssertEx(MsgPtr,"");
	SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);

	__LEAVE_FUNCTION
}

void SceneService::Shutdown(void)
{
	__ENTER_FUNCTION

	

	__LEAVE_FUNCTION
}

void SceneService::Tick( const TimeInfo &rTimeInfo )
{
	__ENTER_FUNCTION

	Service::Tick(rTimeInfo);

	Tick_UpdateAllSceneClass(rTimeInfo);

	Tick_LogSceneClassStat(rTimeInfo);

	Tick_OnlineLog(rTimeInfo);

	Tick_Shutdown(rTimeInfo);
	__LEAVE_FUNCTION
}

void SceneService::Tick_OnlineLog(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (rTimeInfo.m_bDiffMinute)
	{
		CacheLog(LOGDEF_INST(Scene), "cachedmsg size(%d)",
			static_cast<int>(m_CachedMsgList.size()));
	}

	__LEAVE_FUNCTION
}

void SceneService::Tick_Shutdown(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (GetStatus() == ServiceStatus::SHUTDOWN_PROCESS)
	{
		int nScenePlaying = static_cast<int>(m_MarchInfoMap.size());

		CacheLog(LOGDEF_INST(ServerStatus), "SceneService::Tick_Shutdown, nScenePlaying(%d)",
			nScenePlaying);

		if (nScenePlaying == 0)
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

void SceneService::LoadMarch(const DBMarchData& rData)
{
	__ENTER_FUNCTION
		if (rData.m_pData == null_ptr)
		{
			return;
		}

		//AssertEx(rData.m_Count < MAX_TILE_NUM,"");
		for (int i = 0; i< rData.m_Count; i++)
		{
			March rMarch;
			rMarch.SerializeFromDB(rData.m_pData[i]);
			MarchInfo ui;
			rMarch.FillMarchBaseInfo(ui.m_MarchBaseInfo);
			ui.m_MarchSceneInfo.m_nState = MarchSceneInfo::SCENEPLAYING;
			//tempTile->SerializeFromDB(rData.m_pData[i]);
			ui.m_MarchSceneInfo.m_SceneID = EnterTo(rMarch);
			AddMarchInfo(ui);

		}
		__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const DBRetLoadMapMarchMsg &rMsg)
{
	__ENTER_FUNCTION
	AssertEx(rMsg.m_nResult == DBMsgResult::RESULT_SUCCESS,"");
	AssertEx(rMsg.m_DataPtr,"");

	LoadMarch(*rMsg.m_DataPtr);
	OpenupOk();
	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const MarchReqFightMsg &rMsg)
{
	__ENTER_FUNCTION
		if (rMsg.m_nAtttackId == 0)
		{
			return;
		}

		if (rMsg.m_nDefenceId >0)
		{
			MarchInfoMap::iterator itAttacker = m_MarchInfoMap.find(rMsg.m_nAtttackId);
			if (itAttacker == m_MarchInfoMap.end())
			{
				return;
			}
			MarchInfo& rAttackMachInfo = itAttacker->second;

			// 检测是不是自己发的报，避免外挂
			if (rMsg.m_ReceiverGuid != rAttackMachInfo.m_MarchBaseInfo.m_OwnGuid)
			{
				return;
			}

			MarchInfoMap::iterator itDefencer = m_MarchInfoMap.find(rMsg.m_nDefenceId);
			if (itDefencer == m_MarchInfoMap.end())
			{
				return;
			}

			MarchInfo& rDefenceMachInfo = itDefencer->second;

			if (rAttackMachInfo.m_MarchSceneInfo.m_nState != MarchSceneInfo::SCENEPLAYING)
			{
				return;
			}
			
			// 不能自己攻击自己
			if (rDefenceMachInfo.m_MarchBaseInfo.m_OwnGuid == rAttackMachInfo.m_MarchBaseInfo.m_OwnGuid)
			{
				return;
			}

			if (rDefenceMachInfo.m_MarchSceneInfo.m_nState != MarchSceneInfo::SCENEPLAYING)
			{
				return;
			}

			if ((*itDefencer).second.m_MarchSceneInfo.m_SceneID.m_nInstID != (*itAttacker).second.m_MarchSceneInfo.m_SceneID.m_nInstID)
			{
				return;
			}

			MarchOpenCopySceneMsgPtr MsgPtr= POOLDEF_NEW(MarchOpenCopySceneMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_nAtttackId  = rMsg.m_nAtttackId;
			MsgPtr->m_DestSceneID = rMsg.m_DestSceneID;
			MsgPtr->m_nDefenceId  = rMsg.m_nDefenceId;
			MsgPtr->m_nType       = rMsg.m_nType;
			
			SceneID rScene(1,rMsg.m_nSceneId);
			SendMessage2March(rMsg.m_nAtttackId,MsgPtr);
		}

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const MarchReqChangeSceneMsg &rMsg)
{
	__ENTER_FUNCTION

		int64 guid = rMsg.m_guid;
		SceneID curSceneID = rMsg.m_CurSceneID;
		SceneID destSceneID = rMsg.m_DestSceneID;

		if (guid == invalid_guid64)
		{
			return;
		}

		SceneClassPtrMap::iterator itCur = m_SceneClassPtrMap.find(curSceneID.m_nClassID);
		if (itCur == m_SceneClassPtrMap.end())
		{
			return;
		}
		AssertEx((*itCur).second, "");
		if (!((*itCur).second->ChangeFromCheck(curSceneID, guid)))
		{
			return;
		}

		SceneClassPtrMap::iterator itDest = m_SceneClassPtrMap.find(destSceneID.m_nClassID);
		if (itDest == m_SceneClassPtrMap.end())
		{
			return;
		}
		AssertEx(itDest->second, "");
		SceneClass &scnClass = *itDest->second;
		if (!scnClass.ChangeToCheck(destSceneID, guid))
		{
			if (scnClass.GetSceneType() == SceneType::MAIN)
			{
				if (destSceneID.m_nInstID > invalid_id)
				{
					SceneInterface::SendNoticeToUser(guid, "#{2351}");
				}
			}
			return;
		}

		UpdateMarchInfo(guid, MarchSceneInfo::SCENECHANGING);
		MarchAcceptChangeSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchAcceptChangeSceneMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_guid = guid;
		MsgPtr->m_DestSceneID = destSceneID;
		SendMessage2Scene(curSceneID, MsgPtr);

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const MarchChangeSceneMsg &rMsg)
{
	__ENTER_FUNCTION

	MarchInfo ui;
	March rMarch = rMsg.m_March;
	rMarch.FillMarchBaseInfo(ui.m_MarchBaseInfo);
	ui.m_MarchSceneInfo.m_nState = MarchSceneInfo::SCENEPLAYING;
	ui.m_MarchSceneInfo.m_SceneID = ChangeTo(rMsg.m_March, rMsg.m_DestSceneID);
	UpdateMarchInfo(ui);
	DistributeCachedMsg(ui.m_MarchBaseInfo.m_Guid);

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const MarchEnterSceneMsg& rMsg )
{
	__ENTER_FUNCTION

	MarchInfo ui;
	March rMarch = rMsg.m_March;
	rMarch.FillMarchBaseInfo(ui.m_MarchBaseInfo);
	ui.m_MarchSceneInfo.m_nState = MarchSceneInfo::SCENEPLAYING;
	ui.m_MarchSceneInfo.m_SceneID = EnterTo(rMsg.m_March);

	AddMarchInfo(ui);


	__LEAVE_FUNCTION
}


void SceneService::HandleMessage(const MarchLeaveSceneMsg &rMsg)
{
	__ENTER_FUNCTION

	DelMarchInfo(rMsg.m_guid);

	//SendMessage2Srv(ServiceID::WORLDUSER, &rMsg);

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const UpdateMarchBaseInfoMsg& rMsg)
{
	__ENTER_FUNCTION

	UpdateMarchInfo(rMsg.m_BaseInfo);

	__LEAVE_FUNCTION
}

SceneID SceneService::EnterTo(const March& rMarch)
{
	__ENTER_FUNCTION
		SceneClassID nOriginalSceneClassID = _GameConfig().m_nDefaultSceneId;

		SceneClassPtrMap::iterator it = m_SceneClassPtrMap.find(nOriginalSceneClassID);
		if (it != m_SceneClassPtrMap.end())
		{
			AssertEx(it->second, "");
			SceneClass::EnterResult ret = it->second->EnterTo(rMarch);
			if (ret.first)
			{
				return ret.second;
			}
		}
	return SceneID(invalid_id, invalid_id);

	__LEAVE_FUNCTION
	return SceneID(invalid_id, invalid_id);
}

SceneID SceneService::EnterToDefaultScene(const March& rMarch)
{
	__ENTER_FUNCTION

		SceneClassPtrMap::iterator it = m_SceneClassPtrMap.find(_GameConfig().m_nDefaultSceneId);
	AssertEx(it != m_SceneClassPtrMap.end(), "");
	AssertEx(it->second, "");

	SceneClass::ChangeResult Ret = it->second->EnterTo(rMarch);
	AssertEx(Ret.first, "");
	return Ret.second;

	__LEAVE_FUNCTION
		return SceneID(invalid_id, invalid_id);
}

SceneID SceneService::ChangeTo(const March& rMarch, const SceneID &rsid)
{
	__ENTER_FUNCTION

	SceneClassPtrMap::iterator it = m_SceneClassPtrMap.find(rsid.m_nClassID);
	if (it == m_SceneClassPtrMap.end())
	{
		return SceneID(invalid_id, invalid_id);
	}
	AssertEx(it->second, "");

	SceneClass &scnClass = *it->second;
	SceneClass::ChangeResult ret = scnClass.ChangeTo(rMarch, rsid.m_nInstID);
	if (ret.first)
	{
		return ret.second;
	}

	ret = scnClass.ChangeTo(rMarch);
	if (ret.first)
	{
		return ret.second;
	}

	return SceneID(invalid_id, invalid_id);

	__LEAVE_FUNCTION
	return SceneID(invalid_id, invalid_id);
}


void SceneService::InitSceneClass( void )
{
	__ENTER_FUNCTION

	int nSceneClassCount = GetTable_SceneClassCount();
	for (int i = 0; i < nSceneClassCount; i++)
	{
		const Table_SceneClass *pLine = GetTable_SceneClassByIndex(i);
		if (pLine != null_ptr)
		{
			const Table_SceneClass &rLine = *pLine;
			if (rLine.GetType() == invalid_id)
			{
				//纯客户端场景
				continue;
			}

			switch (rLine.GetType())
			{
			case SceneType::MAIN:
				{
					SceneActivationInterface::UpdateSceneClass(rLine.GetSceneID());

					MainSceneClassPtr Ptr = POOLDEF_NEW(MainSceneClass);
					AssertEx(Ptr, "");
					Ptr->SetSceneType(SceneType::MAIN);
					Ptr->SetSceneClassID(rLine.GetSceneID());
					Ptr->InitSceneObstacle(rLine.GetLength(), rLine.GetWidth(), rLine.GetObstacle());
					Ptr->EnlargeScene();

					SceneClassPtr sp = boost::static_pointer_cast<SceneClass, MainSceneClass>(Ptr);
					m_SceneClassPtrMap.insert(std::make_pair(rLine.GetSceneID(), sp));
				}
				break;
			case SceneType::COPY:
				{
					SceneActivationInterface::UpdateSceneClass(rLine.GetSceneID());

					CopySceneClassPtr Ptr = POOLDEF_NEW(CopySceneClass);
					AssertEx(Ptr, "");
					Ptr->SetSceneType(SceneType::COPY);
					Ptr->SetSceneClassID(rLine.GetSceneID());
					Ptr->InitSceneObstacle(rLine.GetLength(), rLine.GetWidth(), rLine.GetObstacle());

					SceneClassPtr sp = boost::static_pointer_cast<SceneClass, CopySceneClass>(Ptr);
					m_SceneClassPtrMap.insert(std::make_pair(rLine.GetSceneID(), sp));
				}
				break;
			default:
				{
					AssertEx(false, "");
				}
				break;
			}
		}
	}

	__LEAVE_FUNCTION
}

void SceneService::Tick_UpdateAllSceneClass(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	for (SceneClassPtrMap::iterator it = m_SceneClassPtrMap.begin(); it != m_SceneClassPtrMap.end(); it++)
	{
		for (int j = 0; j < 128; j++)
		{
			InvokerPtr InvPtr = it->second->FetchSceneInvoker();
			if (InvPtr)
			{
				AddInvoker(InvPtr);
			}
			else
			{
				break;
			}
		}
	}

	__LEAVE_FUNCTION
}

void SceneService::Tick_LogSceneClassStat(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (rTimeInfo.m_bDiffMinute)
	{
		CacheLog(LOGDEF_INST(Scene), "logsceneclassstat, begin");

		for (SceneClassPtrMap::iterator it = m_SceneClassPtrMap.begin(); it != m_SceneClassPtrMap.end(); it++)
		{
			AssertEx(it->second, "");
			CacheLog(LOGDEF_INST(Scene), "%d:%d", it->second->GetSceneClassID(), it->second->GetSceneInstCount());
		}

		CacheLog(LOGDEF_INST(Scene), "logsceneclassstat, end");
	}

	__LEAVE_FUNCTION
}

void SceneService::AddMarchInfo(const MarchInfo &rInfo)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rInfo.m_MarchBaseInfo.m_Guid);
	if (itFind == m_MarchInfoMap.end())
	{
		m_MarchInfoMap.insert(std::make_pair(rInfo.m_MarchBaseInfo.m_Guid, rInfo));
	}
	else
	{
		VerifyEx(false, "");
	}

	__LEAVE_FUNCTION
}

void SceneService::DelMarchInfo(const int64 &rGuid)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rGuid);
	if (itFind != m_MarchInfoMap.end())
	{
		m_MarchInfoMap.erase(itFind);
	}
	else
	{
		VerifyEx(false, "");
	}

	__LEAVE_FUNCTION
}

MarchSceneInfo* SceneService::GetMarchSceneInfo(const int64 &rGuid)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rGuid);
	if (itFind != m_MarchInfoMap.end())
	{
		return &((*itFind).second.m_MarchSceneInfo);
	}
	else
	{
		return null_ptr;
	}

	__LEAVE_FUNCTION
	return null_ptr;
}

MarchBaseInfo* SceneService::GetMarchBaseInfo(const int64 &rGuid)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rGuid);
	if (itFind != m_MarchInfoMap.end())
	{
		return &((*itFind).second.m_MarchBaseInfo);
	}

	return null_ptr;

	__LEAVE_FUNCTION
	return null_ptr;
}

void SceneService::UpdateMarchInfo(const int64 &rGuid, int nState)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rGuid);
	if (itFind != m_MarchInfoMap.end())
	{
		(*itFind).second.m_MarchSceneInfo.m_nState = nState;
	}
	else
	{
		VerifyEx(false, "");
	}

	__LEAVE_FUNCTION
}

void SceneService::UpdateMarchInfo(const MarchInfo &rInfo)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rInfo.m_MarchBaseInfo.m_Guid);
	if (itFind != m_MarchInfoMap.end())
	{
		(*itFind).second = rInfo;
	}
	else
	{
		AddMarchInfo(rInfo);
	}

	__LEAVE_FUNCTION
}

void SceneService::UpdateMarchInfo(const MarchBaseInfo &rBaseInfo)
{
	__ENTER_FUNCTION

	MarchInfoMap::iterator itFind = m_MarchInfoMap.find(rBaseInfo.m_Guid);
	if (itFind != m_MarchInfoMap.end())
	{
		(*itFind).second.m_MarchBaseInfo = rBaseInfo;
	}
	else
	{
		VerifyEx(false, "");
	}

	__LEAVE_FUNCTION
}

int SceneService::SearchMarchBaseInfo(const CHARNAME &szName, bsarray<MarchBaseInfo, MAX_FIND_MARCH_NUM> &rFindResult)
{
	__ENTER_FUNCTION

	int nSearch = 0;
	for (MarchInfoMap::iterator it = m_MarchInfoMap.begin();
		it != m_MarchInfoMap.end() && nSearch < rFindResult.ElemSize();
		it++)
	{
		if (strstr(it->second.m_MarchBaseInfo.m_szName.GetCText(), szName.GetCText()) != null_ptr)
		{
			rFindResult[nSearch++] = it->second.m_MarchBaseInfo;
		}
	}
	return nSearch;

	__LEAVE_FUNCTION
	return 0;
}


void SceneService::PushCachedMsg(int64 guid, MessagePtr Ptr)
{
	__ENTER_FUNCTION

	m_CachedMsgList.push_back(std::make_pair(guid, Ptr));

	__LEAVE_FUNCTION
}

void SceneService::DistributeCachedMsg(int64 guid)
{
	__ENTER_FUNCTION

	MarchSceneInfo *pusi = GetMarchSceneInfo(guid);
	if (pusi != null_ptr)
	{
		MarchSceneInfo &rusi = *pusi;
		if (rusi.m_nState == MarchSceneInfo::SCENEPLAYING)
		{
			int nSendCount = 0;
			for (CachedMsgList::iterator it = m_CachedMsgList.begin(); it != m_CachedMsgList.end();)
			{
				if (it->first == guid)
				{
					SendMessage(rusi.m_SceneID, it->second);
					it = m_CachedMsgList.erase(it);
					nSendCount++;
				}
				else
				{
					it++;
				}
			}
			if (nSendCount > 0)
			{
				CacheLog(LOGDEF_INST(Scene), "cachedmsg send to user(%08X) count(%d)",
					guid, nSendCount);
			}
		}
		else if (rusi.m_nState == MarchSceneInfo::SCENECHANGING)
		{
			VerifyEx(false, "");
		}
		else
		{
			VerifyEx(false, "");
		}
	}

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const TransportToMarch &rMsg)
{
	__ENTER_FUNCTION

		AssertEx(rMsg.m_mp, "");

	MarchSceneInfo *pusi = GetMarchSceneInfo(rMsg.m_mp->m_ReceiverGuid);
	if (pusi != null_ptr)
	{
		MarchSceneInfo &rusi = *pusi;
		if (rusi.m_nState == MarchSceneInfo::SCENEPLAYING)
		{
			SendMessage(rusi.m_SceneID, rMsg.m_mp);
		}
		else if (rusi.m_nState == MarchSceneInfo::SCENECHANGING)
		{
			PushCachedMsg(rMsg.m_mp->m_ReceiverGuid, rMsg.m_mp);
		}
		else
		{
			VerifyEx(false, "");
		}
	}

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const TransportToAllScene &rMsg)
{
	__ENTER_FUNCTION

		BroadcastMessage(rMsg.m_mp);

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const TransportToSceneClass &rMsg)
{
	__ENTER_FUNCTION

		SendMessage(rMsg.m_nClassID, rMsg.m_mp);

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const TransportToSceneInst &rMsg)
{
	__ENTER_FUNCTION

		SendMessage(rMsg.m_SceneID, rMsg.m_mp);

	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const ReqMarchStartMsg &rMsg)
{
	__ENTER_FUNCTION
		
		ScenePos rPos = rMsg.m_Pos;
		March    rMarch = rMsg.m_March;

		

		MarchInfo ui;
		rMarch.FillMarchBaseInfo(ui.m_MarchBaseInfo);
		ui.m_MarchSceneInfo.m_nState = MarchSceneInfo::SCENEPLAYING;
		//tempTile->SerializeFromDB(rData.m_pData[i]);
		ui.m_MarchSceneInfo.m_SceneID = EnterToDefaultScene(rMarch);
		AddMarchInfo(ui);


	__LEAVE_FUNCTION
}

void SceneService::HandleMessage(const MarchLeaveBattleMsg &rMsg)
{
	__ENTER_FUNCTION
		March rMarch = rMsg.m_March;

	MarchInfo ui;
	rMarch.FillMarchBaseInfo(ui.m_MarchBaseInfo);
	ui.m_MarchSceneInfo.m_nState = MarchSceneInfo::SCENEPLAYING;
	//tempTile->SerializeFromDB(rData.m_pData[i]);
	ui.m_MarchSceneInfo.m_SceneID = EnterToDefaultScene(rMarch);
	UpdateMarchInfo(ui);

	__LEAVE_FUNCTION
}
