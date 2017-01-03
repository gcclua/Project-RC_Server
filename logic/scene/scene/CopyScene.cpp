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
BSARRAY_ASSIGN_IMPL(tint32,MAX_ARRANGE_COUNT);
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

void CopyScene::Tick_Logic(const TimeInfo & rTimeInfo)
{
	__ENTER_FUNCTION
	switch (m_nStatus)
	{
	case STATUS_READY:
		{

		}
		break;
	case STATUS_LINE:
		{
			tint32 nNow = (tint32)gTimeManager.GetANSITime();
			if (nNow - m_nStartTime >= COPYWAITLINETIME)
			{
				m_nStatus = STATUS_SELECTTARGET;
			}
		}
		break;
	case STATUS_SELECTTARGET:
		{
			SetAttackMarchLine();
			SetDefenceMarchLine();
			m_nStatus = STATUS_MARCH;
		}
		break;
	case STATUS_MARCH:
		{

		}
		break;
	case STATUS_COMBAT:
		{

		}
		break;
	default:
			break;
	}
	__LEAVE_FUNCTION
}

void CopyScene::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Scene::Tick(rTimeInfo);
	Tick_Close(rTimeInfo);
	Tick_Logic(rTimeInfo);

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
	m_nTimeClose = 20000;
	CleanUpObjList();
	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(GetSceneClassID());
	AssertEx(pSceneClass, "");
	const Table_CopyScene *pCopyScene = GetTable_CopySceneByID(pSceneClass->GetCopySceneID());
	AssertEx(pCopyScene, "");
	m_nWaitCloseTime = pCopyScene->GetWaitTime();
	m_nHeartbeatTime = pCopyScene->GetHeartbeatTime();

	m_nDifficulty = CopySceneDifficulty::DEFAULT;
	m_nStartTime = (tint32)gTimeManager.GetANSITime();
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
		Ptr->DelFromScene();
	}

	__LEAVE_FUNCTION
}


bool CopyScene::IsCanEnterByGuid(const int64 &rGuid)
{
	return true;
}

void CopyScene::InitAttackObj(const March& rMarch)
{
	__ENTER_FUNCTION
		m_AttackMarch = rMarch;
		Table_SceneClass const* pSceneInfo =GetTable_SceneClassByID(GetSceneClassID());
		AssertEx(pSceneInfo,"");
		Hero rHero = rMarch.GetHero();
		if (rHero.GetUID()>0)
		{
			int  nArrangeIndex = rHero.GetArrangeIndex();
			AssertEx(nArrangeIndex > 0,"");

			ScenePos rHeroPos;
			rHeroPos.m_nX  = pSceneInfo->GetAttackPosXbyIndex(nArrangeIndex);
			rHeroPos.m_nZ   = pSceneInfo->GetAttackPosZbyIndex(nArrangeIndex);

			Obj_HeroPtr pHero =	CreateHeroObj(rMarch.GetHero(),rHeroPos,FORCETYPE_T::NPC_ATTACK);
			AssertEx(pHero,"");
		}


		TroopList_T rMarchTroopList = rMarch.GetTroopList();

		int nSize = rMarchTroopList.GetListSize();

		for (int i=0;i<nSize;i++)
		{
			Troop rTroop = rMarchTroopList.GetTroopByIndex(i);
			int  nArrangeIndex = rTroop.GetArrangeIndex();
			AssertEx(nArrangeIndex > 0,"");
			ScenePos rTroopPos;
			rTroopPos.m_nX  = pSceneInfo->GetAttackPosXbyIndex(nArrangeIndex);
			rTroopPos.m_nZ   = pSceneInfo->GetAttackPosZbyIndex(nArrangeIndex);
			Obj_TroopPtr pTroop = CreateTroopObj(rTroop,rTroopPos,FORCETYPE_T::NPC_ATTACK);
			AssertEx(pTroop,"");
		}
		if (rMarch.GetFightId()>0)
		{
			AskJoinCopySceneMsgPtr MsgPtr = POOLDEF_NEW(AskJoinCopySceneMsg);
			AssertEx(MsgPtr, "");
			MsgPtr->m_DestSceneID = SceneID(GetSceneClassID(), GetSceneInstID());
			MsgPtr->m_nCopySceneDifficulty = GetCopySceneDifficulty();
			MsgPtr->m_CopyScenelevel = GetLevel();
			MsgPtr->m_nAttackId      = rMarch.GetMarchId();
			MsgPtr->m_nDefenceId     = rMarch.GetFightId();
			SendMessage2March(rMarch.GetFightId(),MsgPtr);
			m_nStatus = STATUS_READY;
		}
		else
		{
			m_nStatus = STATUS_LINE;
		}
	__LEAVE_FUNCTION
}

void CopyScene::SetAttackMarchLine()
{
	__ENTER_FUNCTION
		for (tint32 i=0;i<MAX_ARRANGE_COUNT;i++)
		{
			if (m_lstAttack[i] != invalid_id)
			{
				Obj_NpcPtr Ptr = GetNpcByID(m_lstAttack[i]);
				Ptr->SelectTargetForMarch(true);
				continue;
	
			}
		}


		
	__LEAVE_FUNCTION
}
void CopyScene::SetDefenceMarchLine()
{
	__ENTER_FUNCTION
		for (tint32 i=0;i<MAX_ARRANGE_COUNT;i++)
		{
			if (m_lstDefence[i] != invalid_id)
			{
				Obj_NpcPtr Ptr = GetNpcByID(m_lstDefence[i]);
				Ptr->SelectTargetForMarch(true);
			}
		}
	__LEAVE_FUNCTION
}

void CopyScene::StartAttachMarch()
{
	__ENTER_FUNCTION
		for (tint32 i=0;i<MAX_ARRANGE_COUNT;i++)
		{
			if (m_lstAttack[i] != invalid_id)
			{
				Obj_NpcPtr Ptr = GetNpcByID(m_lstAttack[i]);
				Ptr->StartMarch();
				continue;

			}
		}
	__LEAVE_FUNCTION
}
void CopyScene::StartDefenceMarch()
{
	__ENTER_FUNCTION
	for (tint32 i=0;i<MAX_ARRANGE_COUNT;i++)
	{
		if (m_lstDefence[i] != invalid_id)
		{
			Obj_NpcPtr Ptr = GetNpcByID(m_lstDefence[i]);
			Ptr->StartMarch();
		}
	}
	__LEAVE_FUNCTION
}

tint32 CopyScene::GetSceneArrangeSelectTarget(tint32 nArrangeId,bool bAttack)
{
	__ENTER_FUNCTION
		tint32 nTargetId = invalid_id;
		if (bAttack)
		{
			return m_lstAttack[nArrangeId];
		}
		else
		{
			return m_lstDefence[nArrangeId];
		}
		return invalid_id;
	__LEAVE_FUNCTION
		return invalid_id;
}

void CopyScene::InitDefenceObj(const March& rMarch)
{
	__ENTER_FUNCTION
		m_DefenceMarch = rMarch;
		Table_SceneClass const* pSceneInfo =GetTable_SceneClassByID(GetSceneClassID());
	AssertEx(pSceneInfo,"");
	Hero rHero = rMarch.GetHero();
	if (rHero.GetUID()>0)
	{
		int  nArrangeIndex = rHero.GetArrangeIndex();
		AssertEx(nArrangeIndex > 0,"");

		ScenePos rHeroPos;
		rHeroPos.m_nX  = pSceneInfo->GetDefencePosXbyIndex(nArrangeIndex);
		rHeroPos.m_nZ  = pSceneInfo->GetDefencePosZbyIndex(nArrangeIndex);

		Obj_HeroPtr pHero =	CreateHeroObj(rMarch.GetHero(),rHeroPos,FORCETYPE_T::NPC_DEFENCE);
		AssertEx(pHero,"");
	}


	TroopList_T rMarchTroopList = rMarch.GetTroopList();

	int nSize = rMarchTroopList.GetListSize();

	for (int i=0;i<nSize;i++)
	{
		Troop rTroop = rMarchTroopList.GetTroopByIndex(i);
		int  nArrangeIndex = rTroop.GetArrangeIndex();
		AssertEx(nArrangeIndex > 0,"");
		ScenePos rTroopPos;
		rTroopPos.m_nX  = pSceneInfo->GetDefencePosXbyIndex(nArrangeIndex);
		rTroopPos.m_nZ  = pSceneInfo->GetDefencePosZbyIndex(nArrangeIndex);
		Obj_TroopPtr pTroop = CreateTroopObj(rTroop,rTroopPos,FORCETYPE_T::NPC_DEFENCE);
		AssertEx(pTroop,"");
	}
	m_nStatus = STATUS_LINE;
		__LEAVE_FUNCTION
}

void CopyScene::InitMarchObj(const March& rMarch)
{
	__ENTER_FUNCTION
	if (rMarch.GetMarchId() > 0)
	{
		if (rMarch.GetForce() == MARCHFORCE_ATTACK)
		{
			InitAttackObj(rMarch);
		
		}
		else
		{
			InitDefenceObj(rMarch);
		}
	}
	__LEAVE_FUNCTION
}

void CopyScene::CleanUpObjList(void)
{
	for (tint32 i = 0; i < MAX_ARRANGE_COUNT; i++)
	{
		m_lstAttack[i] = invalid_id;
		m_lstDefence[i] = invalid_id;
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
				CleanUpObjList();
			}
			if (m_nTimeClose <= 0)
			{
				////CacheLog(LOGDEF_INST(CopyScene), "Tick_Close:Close(), nSceneClassID=%d, nSceneInstID=%d", GetSceneClassID(), GetSceneInstID());
				Close();
			}
		}
		//����ʱ�䵽�˹ر�����
		if (m_nExistTime >= 0 )
		{
			m_nExistTime -= rTimeInfo.m_uTimeElapse;
			if (m_nExistTime <= 0 )
			{
				//ɨ�����ǰ�����������
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
			else if (m_nExistTime / 1000 <= 10 && m_nExistTime / 1000 > 0 && (m_nExistTime+rTimeInfo.m_uTimeElapse)/1000 != m_nExistTime / 1000)	//ʮ��󵹼�ʱ
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

	CleanUpObjList();
	m_nDifficulty = nDifficulty;
	m_nStartTime = (tint32)gTimeManager.GetANSITime();
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
	CleanUpObjList();
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
			int nRule = pCopyScene->GetRulebyIndex(m_nDifficulty -1);

			const Table_CopySceneRule *pCopySceneRule = GetTable_CopySceneRuleByID(nRule);
			if (pCopySceneRule != null_ptr)
			{
				return (pCopySceneRule->GetExistTime()*1000);
			}
		}
	}

	return (600 * 1000);

	__LEAVE_FUNCTION
	return (600 * 1000);
}

void CopyScene::HandleMessage(const UserSkillMsg &rMsg)
{
	__ENTER_FUNCTION
		Obj_CharacterPtr Ptr = GetCharacterByID(rMsg.m_nSenderId);
		if (Ptr == null_ptr)
		{
			return;
		}
		Ptr->UseSkill(rMsg.m_nSkillId,rMsg.m_nTargetId);
	__LEAVE_FUNCTION
}

void CopyScene::HandleMessage(const ReqBattleInfoMsg &rMsg)
{
	__ENTER_FUNCTION
		if (GetSceneInstID() != rMsg.m_nSceneId)
		{
			return;
		}

		RetBattleInfoMsgPtr MsgPtr = POOLDEF_NEW(RetBattleInfoMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_nSceneId = rMsg.m_nSceneId;
		for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); it++)
		{
			ObjPtr Ptr = it->second;
			AssertEx(Ptr, "");
			if (Ptr->IsCharacter())
			{
				Obj_NpcPtr PtrRet = boost::static_pointer_cast<Obj_Npc, Obj>(Ptr);
				SceneObj rObj ;
				rObj.m_objId = PtrRet->GetID();
				rObj.m_dataId = PtrRet->GetDataID();
				for (int i = 0; i < MAXOWNSKILL; i++)
				{
					int SkillId = PtrRet->GetOwnSkillByIndex(i);
					if (SkillId != invalid_id)
					{
						rObj.m_skillLst.push_back(SkillId);
					}
				}
				rObj.m_camp = PtrRet->GetForceType();
				rObj.m_maxHp   = PtrRet->GetCombatAttrByID((int)(COMBATATTR_T::MAXHP));
				rObj.m_attack  = PtrRet->GetCombatAttrByID(COMBATATTR_T::ATTACK);
				rObj.m_defence = PtrRet->GetCombatAttrByID(COMBATATTR_T::DEFENCE);
				rObj.m_level   = PtrRet->GetLevel();
				rObj.m_posX    = PtrRet->GetScenePos().m_nX;
				rObj.m_posZ    = PtrRet->GetScenePos().m_nZ;
				rObj.m_arrangeIndex = PtrRet->GetArrangeIndex();
				rObj.m_hp      = PtrRet->GetCurHp();
				rObj.m_xp      = PtrRet->GetCurXP();
			}
		}

		SendMessage2User(rMsg.m_ReceiverGuid,MsgPtr);


	__LEAVE_FUNCTION
}

void CopyScene::HandleMessage(const ReqObjListMsg &rMsg)
{
	__ENTER_FUNCTION
		if (GetSceneInstID() != rMsg.m_nSceneId)
		{
			return;
		}

		RetObjListMsgPtr MsgPtr = POOLDEF_NEW(RetObjListMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_nSceneId = rMsg.m_nSceneId;
		for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); it++)
		{
			ObjPtr Ptr = it->second;
			AssertEx(Ptr, "");
			if (Ptr->IsCharacter())
			{
				Obj_NpcPtr PtrRet = boost::static_pointer_cast<Obj_Npc, Obj>(Ptr);
				ObjInfo rObj ;
				rObj.m_objId   = PtrRet->GetID();
				rObj.m_posX    = PtrRet->GetScenePos().m_nX;
				rObj.m_posZ    = PtrRet->GetScenePos().m_nZ;
				rObj.m_hp      = PtrRet->GetCurHp();
			}
		}

		SendMessage2User(rMsg.m_ReceiverGuid,MsgPtr);


		__LEAVE_FUNCTION
}

void CopyScene::HandleMessage(const MarchEnterSceneMsg &rMsg)
{
	__ENTER_FUNCTION

	InitMarchObj(rMsg.m_March);

	__LEAVE_FUNCTION
}

void CopyScene::HandleMessage(const ReqSetRobotOpenMsg& rMsg)
{
	__ENTER_FUNCTION

		NpcRefCont Cont;
		Scan_Npc_All(Cont);
		for (int i=0;i<Cont.Size();i++)
		{
			Obj_Npc &rNpc = Cont[i];
			if (rNpc.GetPlayerId() != rMsg.m_ReceiverGuid)
			{
				continue;
			}
			rNpc.SetRobot(rMsg.m_bOpen);
		}
		RetSetRobotOpenMsgPtr MsgPtr = POOLDEF_NEW(RetSetRobotOpenMsg);
		MsgPtr->m_nSceneId = GetSceneInstID();
		MsgPtr->m_nRet     = 0;

		SendMessage2User(rMsg.m_ReceiverGuid,MsgPtr);

	__LEAVE_FUNCTION
}

int CopyScene::GetCopySceneLevel( )
{
	__ENTER_FUNCTION

	return GetLevel();
	__LEAVE_FUNCTION
	return 1;
}



