#include "CopyScene.h"
#include "Table/Table_CopyScene.h"
#include "Message/SceneMsg.h"
#include "Service/MessageOp.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "Scene/GameInterface_Scene.h"
#include "service/ServiceDefine.h"
#include "Table/Table_CopyScene.h"
#include "Table/Table_SceneClass.h"
#include "Table/Table_CopySceneRule.h"
#include "DictionaryFormat/DictionaryFormat.h"

POOLDEF_IMPL(CopyScene);
CopyScene::CopyScene( void )
{

}

CopyScene::~CopyScene( void )
{

}

int CopyScene::GetRunState(void)
{
	switch (gServiceManager.GetStatus())
	{
	case ServiceManagerStatus::EMPTY:
		{
			AssertEx(false, "");
			return ServiceRunState::PAUSE;
		}
		break;
	case ServiceManagerStatus::OPENUP:
		{
			return ServiceRunState::PAUSE;
		}
		break;
	case ServiceManagerStatus::RUNNING:
	case ServiceManagerStatus::SHUTDOWN:
	case ServiceManagerStatus::FINALSAVE:
		{
			return ((GetActive()) ? ServiceRunState::NORMAL : ServiceRunState::SLOWLY);
		}
		break;
	default:
		{
			AssertEx(false, "");
			return ServiceRunState::PAUSE;
		}
		break;
	}
}

void CopyScene::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Scene::Tick(rTimeInfo);
	Tick_Close(rTimeInfo);

	__LEAVE_FUNCTION
}

InvokerPtr CopyScene::InitMyself(void)
{
	Initialize();

	char szInvokerName[64] = {0};
	sprintf_s(szInvokerName, sizeof(szInvokerName), "GeneralCopySceneInvoker(%d,%d)", GetSceneClassID(), GetSceneInstID());
	InvokerPtr Ptr(new GeneralCopySceneInvoker(*this, szInvokerName));
	return Ptr;
}

void CopyScene::Initialize(void)
{
	__ENTER_FUNCTION

	Scene::Initialize();

	m_nStatus = STATUS_CLOSED;
	CleanUpPlayersGuid();
	m_nTimeClose = 20000;

	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(GetSceneClassID());
	AssertEx(pSceneClass, "");
	const Table_CopyScene *pCopyScene = GetTable_CopySceneByID(pSceneClass->GetCopySceneID());
	AssertEx(pCopyScene, "");
	m_nDemandMin = pCopyScene->GetPlayersDemandMin();
	m_nDemandMax = pCopyScene->GetPlayersDemandMax();
	m_nWaitCloseTime = pCopyScene->GetWaitTime();
	m_nHeartbeatTime = pCopyScene->GetHeartbeatTime();

	m_nDifficulty = CopySceneDifficulty::DEFAULT;
	m_nPlayType = CopyScenePlayType::NONE;
	m_nScore = 0;
	m_nCarom = 0;
	m_nStartTime = static_cast<int>(Clock::getCurrentSystemTime());
	m_nStar = 0;
	m_DieCount = 0;
	m_nResult = CopySceneResult::RESULT_INVALID;
	m_nTier = 1;
	m_nLevel = 1;
	m_nExistTime = 600 * 1000;

	__LEAVE_FUNCTION
}

bool CopyScene::GetActive(void) const
{
	return !(m_nStatus == STATUS_CLOSED);
}

void CopyScene::SetActive(void)
{
	m_nTimeClose = m_nWaitCloseTime;
	m_nStatus = STATUS_READY;
}

void CopyScene::OnObjEnter(int nID)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}

	__LEAVE_FUNCTION
}

void CopyScene::OnObjLeave(int nID)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}

	__LEAVE_FUNCTION
}

void CopyScene::OnObjEnterCombat(int nID)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}

	__LEAVE_FUNCTION
}

void CopyScene::OnObjLeaveCombat(int nID)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}

	__LEAVE_FUNCTION
}

void CopyScene::OnObjDie(int nID,int nKillerId)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}

	__LEAVE_FUNCTION
}

bool CopyScene::OnObjBeforeHPChange(int nID, int nHP, int& nSpecialHP)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}
	return true;

	__LEAVE_FUNCTION
	return true;
}

bool CopyScene::OnObjBeforeMPChange(int nID, int nMP, int& nSpecialMP)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}
	return true;

	__LEAVE_FUNCTION
	return true;
}

void CopyScene::OnClientObjEnterOK(int nID)
{
	__ENTER_FUNCTION

	ObjPtr Ptr = GetObjByID(nID);
	if (Ptr)
	{
		
	}

	__LEAVE_FUNCTION
}

bool CopyScene::IsCanEnterByGuid(const int64 &rGuid)
{
	for (int i = 0; i < COPYSCENEMAXPLAYERCOUNT; i++)
	{
		if (m_PlayersGuid[i] == rGuid)
		{
			return true;
		}
	}
	return false;
}


void CopyScene::CleanUpPlayersGuid(void)
{
	for (int i = 0; i < COPYSCENEMAXPLAYERCOUNT; i++)
	{
		m_PlayersGuid[i] = invalid_guid64;
	}
}

void CopyScene::Tick_Close(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (GetActive())
	{
		if (GetCurPlayerCount() > 0)
		{
			m_nTimeClose = m_nWaitCloseTime;
		}
		else
		{
			m_nTimeClose -= rTimeInfo.m_uTimeElapse;
			if (m_nTimeClose <= 2000)
			{
				CleanUpPlayersGuid();
			}
			if (m_nTimeClose <= 0)
			{
				////CacheLog(LOGDEF_INST(CopyScene), "Tick_Close:Close(), nSceneClassID=%d, nSceneInstID=%d", GetSceneClassID(), GetSceneInstID());
				Close();
			}
		}
		//副本时间到了关闭踢人
		if (m_nExistTime >= 0 )
		{
			m_nExistTime -= rTimeInfo.m_uTimeElapse;
			if (m_nExistTime <= 0 )
			{
				//扫描出当前场景所有玩家
				ObjRefCont Cont;
				Scan_All_All(Cont);
				for (int i = 0; i < Cont.Size(); i++)
				{
					//Obj_User &rUser = Cont[i];
// 					//CacheLog(LOGDEF_INST(CopyScene), "Tick_Close:Close(), nSceneClassID=%d, nSceneInstID=%d, Guid=[%08X%08X], ", 
// 						GetSceneClassID(), GetSceneInstID(),
// 						rUser.GetGuid().GetHigh32Value(),
// 						rUser.GetGuid().GetLow32Value());
					//rUser.ChangeScene_ExitCopyScene();
				}
			}
			else if (m_nExistTime / 1000 <= 10 && m_nExistTime / 1000 > 0 && (m_nExistTime+rTimeInfo.m_uTimeElapse)/1000 != m_nExistTime / 1000)	//十秒后倒计时
			{
				
				char szNotice[256];
				char* str = DictionaryFormat::FormatDictionary(szNotice,sizeof(szNotice),"#{2032}",m_nExistTime / 1000);	
				SceneInterface::BroadcastNoticeToSceneInst(SceneID(GetSceneClassID(), GetSceneInstID()),str);

			}
		}		
	}

	__LEAVE_FUNCTION
}

void CopyScene::Open(int nPlayType, int nDifficulty, int nLevel)
{
	__ENTER_FUNCTION

	m_nStatus = STATUS_OPENED;
	CleanUpPlayersGuid();


	m_nDifficulty = nDifficulty;
	m_nPlayType = nPlayType;
	m_nScore = 0;
	m_nCarom = 0;
	m_nStartTime = (int)Clock::getCurrentSystemTime();
	m_nStar = 0;
	m_DieCount = 0;
	m_nResult = CopySceneResult::RESULT_INVALID;
	m_nTier = 1;
	m_nLevel = nLevel;
	m_nExistTime = CalcExistTime();


	__LEAVE_FUNCTION
}

void CopyScene::Close(void)
{
	__ENTER_FUNCTION

	m_nStatus = STATUS_CLOSED;
	CleanUpPlayersGuid();
	DelAllNonUserObj();
	Tick_DelObjs();
	VerifyEx(m_ObjPtrMap.empty(), "");

	__LEAVE_FUNCTION
}

int CopyScene::CalcExistTime(void)
{
	__ENTER_FUNCTION

	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(GetSceneClassID());
	if (pSceneClass != null_ptr)
	{
		const Table_CopyScene *pCopyScene = GetTable_CopySceneByID(pSceneClass->GetCopySceneID());
		if (pCopyScene != null_ptr)
		{
			int nRule =
				((m_nPlayType == CopyScenePlayType::SINGLE) ?
				(pCopyScene->GetRulebyIndex(m_nDifficulty -1)) : (pCopyScene->GetRuleTeambyIndex(m_nDifficulty -1)));

			const Table_CopySceneRule *pCopySceneRule = GetTable_CopySceneRuleByID(nRule);
			if (pCopySceneRule != null_ptr)
			{
				return (pCopySceneRule->GetExistTime()*1000);
			}
			else
			{
				return (pCopyScene->GetExistTime()*1000);
			}
		}
	}

	return (600 * 1000);

	__LEAVE_FUNCTION
	return (600 * 1000);
}


void CopyScene::HandleMessage(const MarchEnterSceneMsg &rMsg)
{
	__ENTER_FUNCTION

	if (m_nStatus != STATUS_OPENED)
	{
		
		int nLevel = GetCopySceneLevel();
		Open(1,1,nLevel);
		
		for (int i = 0; i < COPYSCENEMAXPLAYERCOUNT; i++)
		{
			if (i == 0)
			{
				m_PlayersGuid[i] = rMsg.m_MarchPtr->GetMarchId();
			}
			else
			{
				m_PlayersGuid[i] = invalid_guid64;
			}
		}
		
	}

	Scene::HandleMessage(rMsg);

	__LEAVE_FUNCTION
}
int CopyScene::GetCopySceneLevel( )
{
	__ENTER_FUNCTION
	
		int nLevel = MAX_CHARACTER_LEVEL;

	return nLevel;
	__LEAVE_FUNCTION
	return 1;
}

void CopyScene::OnObjTeleportChangeScene( int nID )
{
	
}


