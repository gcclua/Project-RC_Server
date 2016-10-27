#include "SceneService.h"
#include "Scene/SceneClass/CopySceneClass.h"
#include "Scene/GameInterface_Scene.h"
#include "Scene/GameInterface_SceneActivation.h"
#include "Message/SceneMsg.h"
#include "sceneClass/MainSceneClass.h"
#include "service/MessageOp.h"
#include "Table/Table_SceneClass.h"


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

	Tick_ChangeNameCoolDown(rTimeInfo);


	__LEAVE_FUNCTION
}

void SceneService::Tick_OnlineLog(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (rTimeInfo.m_bDiffMinute)
	{
		//AuditLog(LOGDEF_INST(Audit_Online), "ScenePlaying", invalid_int64,
			//"Count=%d", static_cast<int>(m_MarchInfoMap.size()));
		//CacheLog(LOGDEF_INST(Scene), "cachedmsg size(%d)",
			//static_cast<int>(m_CachedMsgList.size()));
	}

	__LEAVE_FUNCTION
}

void SceneService::Tick_Shutdown(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (GetStatus() == ServiceStatus::SHUTDOWN_PROCESS)
	{
		int nScenePlaying = static_cast<int>(m_MarchInfoMap.size());

		//CacheLog(LOGDEF_INST(ServerStatus), "SceneService::Tick_Shutdown, nScenePlaying(%d)",
			//nScenePlaying);

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


void SceneService::HandleMessage( const MarchEnterSceneMsg &rMsg )
{
	__ENTER_FUNCTION

	MarchInfo ui;
	rMsg.m_MarchPtr->FillMarchBaseInfo(ui.m_MarchBaseInfo);
	ui.m_MarchSceneInfo.m_nState = MarchSceneInfo::SCENEPLAYING;
	ui.m_MarchSceneInfo.m_SceneID = EnterTo(rMsg.m_MarchPtr);

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

SceneID SceneService::EnterTo(Obj_MarchPtr ptr)
{
	__ENTER_FUNCTION
		if (!ptr)
		{
			return SceneID();
		}
	return SceneID(invalid_id, invalid_id);

	__LEAVE_FUNCTION
	return SceneID(invalid_id, invalid_id);
}

SceneID SceneService::ChangeTo(Obj_MarchPtr ptr, const SceneID &rsid)
{
	__ENTER_FUNCTION

	SceneClassPtrMap::iterator it = m_SceneClassPtrMap.find(rsid.m_nClassID);
	if (it == m_SceneClassPtrMap.end())
	{
		return SceneID(invalid_id, invalid_id);
	}
	AssertEx(it->second, "");

	SceneClass &scnClass = *it->second;
	SceneClass::ChangeResult ret = scnClass.ChangeTo(ptr, rsid.m_nInstID);
	if (ret.first)
	{
		return ret.second;
	}

	ret = scnClass.ChangeTo(ptr);
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
				//´¿¿Í»§¶Ë³¡¾°
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
					Ptr->SetMaxPlayerCountA(rLine.GetPlayersMaxA());
					Ptr->SetMaxPlayerCountB(rLine.GetPlayersMaxB());
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
					Ptr->SetMaxPlayerCountA(rLine.GetPlayersMaxA());
					Ptr->SetMaxPlayerCountB(rLine.GetPlayersMaxB());
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
		//CacheLog(LOGDEF_INST(Scene), "logsceneclassstat, begin");

		for (SceneClassPtrMap::iterator it = m_SceneClassPtrMap.begin(); it != m_SceneClassPtrMap.end(); it++)
		{
			AssertEx(it->second, "");
			//CacheLog(LOGDEF_INST(Scene), "%d:%d", it->second->GetSceneClassID(), it->second->GetSceneInstCount());
		}

		//CacheLog(LOGDEF_INST(Scene), "logsceneclassstat, end");
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
		VerifyEx(false, "");
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
				//CacheLog(LOGDEF_INST(Scene), "cachedmsg send to user(%08X,%08X) count(%d)",
					//guid.GetHigh32Value(), guid.GetLow32Value(), nSendCount);
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
