#include "Obj_March.h"
#include "Config.h"

#include "Service/MessageOp.h"
#include "Scene/Scene/CopyScene.h"
#include "Scene/GameInterface_Scene.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "Message/SceneMsg.h"
#include "Table/Table_SceneClass.h"
#include "Table/Table_CopyScene.h"
#include "Table/Table_CopySceneRule.h"



#define SAODANGQUAN_DATAID 62  //扫荡券

//tuint32 Obj_March::HandlePacket(::CG_OPEN_COPYSCENE &rPacket)
void Obj_March::HandleMessage(const MarchOpenCopySceneMsg &rMsg)
	
{
	__ENTER_FUNCTION

	tint32 nSceneClassID = rMsg.m_nType;
	bool IsSingle = rMsg.m_nType == 1? true:false;
	tint32 nDifficult = CopySceneDifficulty::LEVEL1;
	m_rMarch.SetFightId(rMsg.m_nDefenceId);
	m_rMarch.SetForce(MARCHFORCE_ATTACK);
	// 多人副本 加个操作锁
	if (IsSingle == false)
	{
		bool bRet =IsUserBitLocked(USER_BITLOCK_COPYSCENE_OPEN);
		if (bRet)
		{
			SendNotice("#{2215}");
			return;
		}
		SetUserBitLocked(USER_BITLOCK_COPYSCENE_OPEN,3000);
	}

	if (false ==IsSceneValid())
	{
		return;
	}


	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(nSceneClassID);
	if (pSceneClass)
	{
		//检查单人和多人副本
		OpenCopyScene(nSceneClassID, nDifficult, IsSingle);
	}

	__LEAVE_FUNCTION

}

void Obj_March::HandleMessage(const MarchLeaveFightMsg &rMsg)
{
	__ENTER_FUNCTION
		if (IsInCopyScene())
		{
			ChangeScene_ExitCopyScene();
		}	
		__LEAVE_FUNCTION
}


void Obj_March::HandleMessage(const AskJoinCopySceneMsg &rMsg)
{
	__ENTER_FUNCTION

	m_rMarch.SetForce(MARCHFORCE_DEFENCE);
		ChangeScene_JoinCopyScene(rMsg.m_DestSceneID);

		// 记录日志
		AuditLog(LOGDEF_INST(Audit_CopyScene),"OCS", GetGuid(), m_rMarch.GetWorldId(), "SID=%d \1 DY=%d \1 SE=%d \1 L=%d \1 IOCS=%d",
			rMsg.m_DestSceneID.m_nClassID,
			rMsg.m_nCopySceneDifficulty,
			2,
			rMsg.m_CopyScenelevel,
			0);

	__LEAVE_FUNCTION
}

void Obj_March::OpenCopyScene(tint32 nSceneClassID, tint32 nDifficulty,bool IsSingle,tint32 nEnterType)
{
	__ENTER_FUNCTION
		
	if (CanOpenCopyScene(nSceneClassID, nDifficulty, IsSingle, nEnterType))
	{
		OpenSingleCopyScene(nSceneClassID,nDifficulty);
	}
	__LEAVE_FUNCTION
}

bool Obj_March::CanOpenCopyScene(tint32 nSceneClassID,tint32 nDifficulty,bool IsSingle,tint32 nEnterType)
{
	__ENTER_FUNCTION


		return CanOpenSingleCopyScene(nSceneClassID,nDifficulty,nEnterType);	
		__LEAVE_FUNCTION
			return false;
}

void Obj_March::OpenSingleCopyScene(tint32 nSceneClassID, tint32 nDifficulty)
{
	__ENTER_FUNCTION
		m_nCopySceneClassID = nSceneClassID;
	m_nCopySceneDifficulty = nDifficulty;

	ChangeScene_OpenCopyScene(nSceneClassID);
	__LEAVE_FUNCTION
}

bool Obj_March::CanOpenSingleCopyScene(tint32 nSceneClassID, tint32 nDifficulty,tint32 nEnterType)
{
	__ENTER_FUNCTION
		
		const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(nSceneClassID);
		if (pSceneClass == null_ptr)
		{
			return false;
		}
		const Table_SceneClass &rSceneClass = *pSceneClass;
		if (rSceneClass.GetType() != SceneType::COPY)
		{
			return false;
		}
		tint32 nCopySceneID = rSceneClass.GetCopySceneID();
		if (nCopySceneID <= invalid_id)
		{
			return false;
		}

		const Table_CopyScene *pCopyScene = GetTable_CopySceneByID(nCopySceneID);		
		if (pCopyScene == null_ptr)
		{
			return false;
		}
		const Table_CopyScene &rCopyScene = *pCopyScene;
		
		//判断副本规则

		tint32 nRule = rCopyScene.GetRulebyIndex(nDifficulty -1);
		if (nRule != -1)
		{
			const Table_CopySceneRule *pCopySceneRule = GetTable_CopySceneRuleByID(nRule);
			if (pCopySceneRule)
			{
				tint32 nStartTime = pCopySceneRule->GetStartTime();
				tint32 nEndTime = pCopySceneRule->GetEndTime();

				if (nStartTime != invalid_id && nEndTime != invalid_id)
				{
					tint32 nCurrentTime = gTimeManager.GetHour() * 100 + gTimeManager.GetMinute();
					if (nCurrentTime < nStartTime || nCurrentTime > nEndTime)
					{
						SendNotice("#{1350}");
						return false;	
					}	
				}
				if (pCopySceneRule->GetLevel()!= invalid_id && pCopySceneRule->GetLevel() > GetLevel())
				{
					tchar szNotice[256];
					tchar* str = DictionaryFormat::FormatDictionary(szNotice,sizeof(szNotice),"#{1351}",pCopySceneRule->GetLevel());	
					SendNotice(str);
					return false;
				}

			}
		}
		return true;
		__LEAVE_FUNCTION
			return false;
}





