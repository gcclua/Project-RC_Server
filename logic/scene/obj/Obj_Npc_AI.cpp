#include "Obj_Npc.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Table/Table_PatrolPoint.h"
#include "Scene/Scene/CopyScene.h"
#include "Message/SceneMsg.h"
#include "Service/MessageOp.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "Scene/GameInterface_Scene.h"



bool Obj_Npc::OnThreat(Obj_Character& rAttacker,int nIncThreatNum)
{
	__ENTER_FUNCTION
		bool bRet= Obj_Character::OnThreat(rAttacker,nIncThreatNum);
		if (bRet ==false)
		{
			return false;
		}
		else if ( bRet == true )
		{ // 特例代码 TT 3736
			if ( m_bIsInCombat == true && m_curAIType == Obj_Npc::AI_IDLE )
			{ // 如果处在战斗状态,而AI又是IDLE,则重新切一次AI_COMBAT
				SwitchAI(Obj_Npc::AI_COMBAT);
			}
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

void  Obj_Npc::Tick_EnemyList(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		//空了 就没必要走了
		int nEnemyCount =GetEnemyCount();
		if (nEnemyCount<=0)
		{
			return;
		}
		
		EnemyUnitList_T const& rEnemyList =m_enemyInfo.GetEnemyList();
		const int nListSize =rEnemyList.GetSize();
		if (false ==IsSceneValid())
		{
			return;
		}
		Scene& rScene =GetScene();
		bool bIsChange =false;//仇恨列表是否有变化了
		//检测 是否需要移除仇恨列表中的目标
		for (int i=0;i<nListSize;i++)
		{
			if (false ==rEnemyList.IsUnitVaild(i))
			{
				continue;
			}

			EnemyUnit_T const& rEnemy =rEnemyList.GetUnitByIndex(i);
			if (rEnemy.isValid())
			{
				int nEnemyId =rEnemy.GetObjID();
				if (rEnemy.GetThreat()<=0)
				{
					continue;
				}
				//超时移除
				if (nEnemyId !=m_nCurSelectObjId && //不是当前针对目标
					gTimeManager.RunTime() -rEnemy.GetLastThreatTime() >EnemyUnitList_T::MAXTIME)
				{
					m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
					bIsChange =true;
					continue;
				}
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					//目标已经死亡 移除
					if (false ==EnemyObjPtr->GetActive() || 
						false ==EnemyObjPtr->IsAlive())
					{
						m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
						bIsChange =true;
						continue;
					}
					
				}
				else//找不到了 移除
				{
					m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
					bIsChange =true;
					continue;
				}
			}
		}
		//仇恨列表变动后 检测是否为空
		if (bIsChange)
		{
			nEnemyCount =GetEnemyCount();
			 //敌对列表 为空 且在战斗状态 退出战斗状态  
			if (nEnemyCount<=0 && m_bIsInCombat)
			{
				LeaveCombat();
			}
		}
		__LEAVE_FUNCTION
}

int Obj_Npc::SelectNewTarget(int SelMethod)
{
	__ENTER_FUNCTION
		if (false ==IsSceneValid())
		{
			return invalid_id;
		}
		Scene& rScene =GetScene();
		//正常的选择逻辑 加一个切换目标冷却时间的检测
		if (m_nCurSelectObjId !=invalid_id)
		{
			Obj_CharacterPtr CurSelObj =rScene.GetCharacterByID(m_nCurSelectObjId);
			if (CurSelObj)
			{
				//当前有选择的目标 且 还未到切换目标的冷却时间的话 本次不切换目标
				if ( CurSelObj->GetActive() 
					&& CurSelObj->IsAlive()
					&& CurSelObj->CanBeScout(*this)) //目标能被侦察到
				{
					return m_nCurSelectObjId;
				}
			}
		}

		int nSeleObjId =invalid_id;
		switch (SelMethod)
		{
		case Obj_Npc::METHOD_NORMAL:
			nSeleObjId =SelectMethod_Sencond();
			break;
		case Obj_Npc::METHOD_NEAREST:
			nSeleObjId =SelectNearestTarget();
			break;
		default:
			break;
		}
		return nSeleObjId;
	__LEAVE_FUNCTION
		return invalid_id;
}
//第二仇恨目标选择 模式
int Obj_Npc::SelectMethod_Sencond()
{
	__ENTER_FUNCTION
		if (GetEnemyCount() <=0)
		{
			return invalid_id;
		}
		if (false ==IsSceneValid())
		{
			return invalid_id;
		}
		Scene& rScene =GetScene();
		EnemyUnitList_T const& rEnemyList =m_enemyInfo.GetEnemyList();

		const int nListSize =rEnemyList.GetSize();
		int nSelObjId =invalid_id;
		for (int i=0;i<nListSize;i++)
		{
			if (false ==rEnemyList.IsUnitVaild(i))
			{
				continue;
			}

			EnemyUnit_T const& rEnemy =rEnemyList.GetUnitByIndex(i);
			if (rEnemy.isValid())
			{
				int nEnemyId =rEnemy.GetObjID();
				int nEnemyThreat =rEnemy.GetThreat();
				if (nEnemyThreat<=0)
				{
					continue;
				}
				Obj_NpcPtr EnemyObjPtr =rScene.GetNpcByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					// 跟策划沟通，近战兵种不会改目标，所以近战目标一旦攻击了自己，就会一直在身边，所以总是在仇敌列表里选近战目标是没问题的
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive() &&
						EnemyObjPtr->CanBeScout(*this)&&
						EnemyObjPtr->GetAttackDisType() == 0)
					{
							nSelObjId =rEnemy.GetObjID();
							break;
					}
				}
			}
		}
		return nSelObjId;
	__LEAVE_FUNCTION
		return invalid_id;

}

int Obj_Npc::SelectNearestTarget()
{
	__ENTER_FUNCTION
		Scene& rScene = GetScene();
		NpcRefCont cont;
		rScene.Scan_Npc_All(cont);
		float fMinDistance = 100000.f;
		int   nSelObj = invalid_id;
		ScenePos curPos = GetScenePos();
		for (tint32 i = 0; i < cont.Size(); i++)
		{
			Obj_Npc &rNPC = cont[i];

			if (rNPC.GetForceType() != GetForceType())
			{
				float fDistance = curPos.Distance(rNPC.GetScenePos());
				if (fDistance<fMinDistance)
				{
					nSelObj = rNPC.GetID();
					fMinDistance = fDistance;
				}
			}
		}

		return nSelObj;

	__LEAVE_FUNCTION
		return invalid_id;
}


int Obj_Npc::SelectMethod_March()
{
	__ENTER_FUNCTION
	Scene& rScene = GetScene();
	NpcRefCont cont;
	rScene.Scan_Npc_Circle(cont,GetScenePos(),m_fAlertRadius);
	for (tint32 i = 0; i < cont.Size(); i++)
	{
		Obj_Npc &rNPC = cont[i];
		if (rNPC.CanBeView(*this))
		{
			for (int i=0; i<m_vecMarchTarget.size();i++)
			{
				if (m_vecMarchTarget[i] == rNPC.GetID())
				{
					m_nCurSelectObjId = rNPC.GetID();
					EnterTrace();
					break;
				}
			}

		}
	}
	__LEAVE_FUNCTION
	return invalid_id;
}

//向目标发送伤害
bool Obj_Npc::OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		Obj_Character::OnSendDamageToUnit(rTarget,rDamage);
	return true;
	__LEAVE_FUNCTION
		return false;
}
//接受伤害
void Obj_Npc::OnReceiveDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		Obj_Character::OnReceiveDamage(rDamage);
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
		//死亡了 就不要走AI逻辑了
		if (IsDie())
		{
			return;
		}
		switch (m_curAIType)
		{
		case Obj_Npc::AI_IDLE:
			Tick_AI_Idle(rTimeInfo);
			break;
		case Obj_Npc::AI_MARCH:
			Tick_AI_March(rTimeInfo);
			break;
		case Obj_Npc::AI_COMBAT:
			Tick_AI_Combat(rTimeInfo);
			break;
		case Obj_Npc::AI_TRACE:
			Tick_AI_Trace(rTimeInfo);
			break;
		default:
			break;
		}
	__LEAVE_FUNCTION
}

bool Obj_Npc::SwitchAI(int AIType)
{
	__ENTER_FUNCTION
		//todo 切换AI状态其他判断
		//切换到回家AI 先打断移动
		m_curAIType =AIType;
		if (m_curAIType ==Obj_Npc::AI_TRACE)
		{
			m_nTraceTime =0;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}

void Obj_Npc::Tick_AI_Idle(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
		//todo 待机状态下 如果有巡逻 需求 切换到 巡逻AI
		
		
	__LEAVE_FUNCTION
}
void Obj_Npc::ChangeCurSelectObjId(int nId)
{
	//重置选择冷却时间
	m_nCurSelectObjId =nId;
	
}

bool Obj_Npc::SelectCanAttackObj()
{
	__ENTER_FUNCTION
		if (false ==IsSceneValid())
		{
			return false;
		}
		Scene& rScene =GetScene();
		ScenePos selfPos =GetScenePos();
		CharacterRefCont objCharList;
		float fMinDis =m_fAlertRadius;
		int nSelObjId =invalid_id;
		rScene.Scan_Character_Circle(objCharList,selfPos,m_fAlertRadius);
		//寻找距离最近的攻击
		int nSeleIndex =invalid_id;
		for (int i = 0; i < objCharList.Size(); i++)
		{
			if (objCharList[i].IsAlive()==false || objCharList[i].GetActive() ==false)
			{
				continue;
			}
			//是敌对 可被侦察到
			if (GetRelationByForceType(objCharList[i])==(int)(RELATIONTYPE_T::ENEMY)&&
				objCharList[i].CanBeScout(*this))
			{
				float fDis =selfPos.Distance(objCharList[i].GetScenePos());
				if (fDis -fMinDis <=0)
				{
					fMinDis =fDis;
					nSelObjId =objCharList[i].GetID();
					nSeleIndex =i;
				}
			}
		}
		if (nSelObjId !=invalid_id)
		{
			//找到可以攻击的目标切换为战斗状态
			ChangeCurSelectObjId(nSelObjId);
			
			//将目标加入仇恨列表
			if (nSeleIndex>=0 && nSeleIndex<objCharList.Size())
			{
				OnThreat(objCharList[nSeleIndex],1);
			}
			EnterCombat();
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
void Obj_Npc::ProessTrace(Obj_Character& rUnit,float fAttackDis)
{
	__ENTER_FUNCTION
		if (IsSceneValid() == false)
		{
			return;
		}
		Scene& rScene =GetScene();
		//int Pos[MAXTRACEPOINTNUM]={0,3,6,9,1,4,7,10,2,5,8,11};
		int Pos[MAXTRACEPOINTNUM]={0,1,2,3,4,5,6,7,8,9,10,11};
		
		ScenePos UnitfPos =rUnit.GetScenePos();
		m_nLastTraceTime = gTimeManager.RunTime();
		m_lastTracePos =UnitfPos;
		ScenePos MinDisPos;
		float fMinDis =999999.0f;
		//选择离自己最近的且没有其他npc过去的点
		int nSelePointIndex =-1;
		for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
		{
			ScenePos targetPos;
			float dis = fAttackDis-0.1f; //做个偏移
			targetPos.m_fX = UnitfPos.m_fX + dis * cos(GetFaceDir()+_PI * Pos[nPointIndex]/ 6);
			targetPos.m_fZ = UnitfPos.m_fZ + dis * sin(GetFaceDir()+_PI * Pos[nPointIndex]/ 6);
			float fDis =GetScenePos().Distance(targetPos);
			if ((fDis -fMinDis <0) && rUnit.IsTrackPointUsed(nPointIndex) ==false)
			{
				fMinDis =fDis;
				MinDisPos =targetPos;
				nSelePointIndex =nPointIndex;
			}
		}
		//如果没有可用的点 点都被占光了 则选择离自己最近的点
		/*if (nSelePointIndex ==-1)
		{
			for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
			{
				ScenePos targetPos;
				float dis = fAttackDis-0.1f; //做个偏移
				targetPos.m_fX = UnitfPos.m_fX + dis * cos(_PI * Pos[nPointIndex]/ 6);
				targetPos.m_fZ = UnitfPos.m_fZ + dis * sin(_PI * Pos[nPointIndex]/ 6);
				float fDis =GetScenePos().Distance(targetPos);
				if (fDis - fMinDis <0)
				{
					fMinDis =fDis;
					MinDisPos =targetPos;
					nSelePointIndex =nPointIndex;
				}
			}
		}*/

		MoveTo(MinDisPos,fAttackDis-0.1f);
		/*if (rScene.IsScenePosWalkAble(MinDisPos)==false) //如果要去的点是不可以达到的点则向目标点移动
		{
			MoveTo(rUnit.GetScenePos(),fAttackDis-0.1f);
		}
		else
		{
			MoveTo(MinDisPos);
		}*/
		rUnit.SetTrackPointFlag(nSelePointIndex,true);//被追踪的目标 该点已经被占用了
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI_Trace(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
		if (false ==GetActive() ||
			false ==IsAlive())
		{
			return;
		}
		if (false ==IsSceneValid())
		{
			//出异常了 切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}

		Moving(rTimeInfo);

		Scene& rScene =GetScene();
		
		Obj_CharacterPtr CharPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
		if (!CharPtr)
		{
			//出异常了 切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		//目标隐身 切回战斗状态
		if (CharPtr->CanBeScout(*this) ==false)
		{
			EnterCombat();
			return;
		}
		//追踪时间超过 切换目标的时间 则切回战斗状态 看是否需要重新选择攻击目标 不要一直追着不放了
		m_nTraceTime +=rTimeInfo.m_uTimeElapse;

		float fDiffDis =GetScenePos().Distance(CharPtr->GetScenePos()); //距离追击目标的距离
		float fDiffLastTraceDis =m_lastTracePos.Distance(CharPtr->GetScenePos());//距离上一次的追踪目标的距离
		if (fDiffDis<=m_fTraceStopDis) //到达目的地 停下来 切回到战斗AI
		{
			EnterCombat();
			return;
		}

		if (!IsMoving() && fDiffDis>m_fTraceStopDis) //没在移动 且还没到目的点追击
		{
			//ProessTrace(*CharPtr,m_fTraceStopDis);
			//m_lastTracePos =CharPtr->GetScenePos();
			//MoveTo(CharPtr->GetScenePos(),m_fTraceStopDis);
			ProessTrace(*CharPtr,m_fTraceStopDis);
		}
		else if(fDiffLastTraceDis>0.1f && fDiffDis>m_fTraceStopDis)//发现追击目标动了 修改追击方向
		{
			if (m_nLastTraceTime==0 ||gTimeManager.RunTime() -m_nLastTraceTime>=300) //不要变动的太频繁
			{
				if (IsMoving())
				{
					StopMove(true,true);
				}
				//m_lastTracePos =CharPtr->GetScenePos();
				//MoveTo(CharPtr->GetScenePos(),m_fTraceStopDis);
				ProessTrace(*CharPtr,m_fTraceStopDis);
			}
		}

		int nSkillId = SelectSkillAndTargetInTrace();
		if (UseSkill(nSkillId,m_nCurSelectObjId))
		{
			
		}
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI_Combat(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
		if (false ==GetActive() ||
			false ==IsAlive())
		{
			return;
		}
		if (false ==IsSceneValid())
		{
			//出异常了 切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		ScenePos SelfPos =GetScenePos();
	
		//选择技能和攻击目标
		int nSkillId = invalid_id;
		int nSelTargetId = invalid_id;
		SelectSkillAndTarget(nSkillId,nSelTargetId);
		if (nSkillId ==invalid_id) //本次没有能释放的技能
		{
			return;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr TargetCharPtr =rScene.GetCharacterByID(nSelTargetId);
		if (!TargetCharPtr)
		{
			//出异常了 切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		//目标隐身了
		if (TargetCharPtr->CanBeScout(*this) ==false)
		{
			//切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		ScenePos TargetPos =TargetCharPtr->GetScenePos();
		Table_SkillEx const* pSkillEx =GetTable_SkillExByID(nSkillId);
		if (pSkillEx ==null_ptr)
		{
			//出异常了 切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		Table_SkillBase const* pSkillBase =GetTable_SkillBaseByID(pSkillEx->GetBaseId());
		if (pSkillBase ==null_ptr)
		{
			//出异常了 切回待机AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		Table_SkillEx const& rSkillEx =*pSkillEx;
		Table_SkillBase const& rSkillBase =*pSkillBase;
		float fDiffDistance =SelfPos.Distance(TargetPos);
		//距离不够 先追踪(对自身作用的技能 无须追踪)
		if(rSkillBase.GetSelLogic() !=TAEGETSEL_T::SELF && rSkillBase.GetSkillClass() == SKILLCLASS::AUTOREPEAT )
		{
			if (fDiffDistance-rSkillEx.GetRadius() >0)
			{
				int nMoveSpeedAttr =GetCombatAttrByID(COMBATATTR_T::MOVESPEED);
				//不能移动的npc不追踪
				if (nMoveSpeedAttr >0)
				{
					EnterTrace();
				}
				return;
			}
		}
 		if (UseSkill(nSkillId,nSelTargetId))
 		{
			// 判断要不要修改当前目标
			m_nLastAttackTime =gTimeManager.RunTime(); //记录下攻击时间
 		}
	__LEAVE_FUNCTION
}

void Obj_Npc::EnterMarch()
{
	__ENTER_FUNCTION
		SwitchAI(AI_MARCH);
	__LEAVE_FUNCTION
}

void Obj_Npc::EnterTrace()
{
	__ENTER_FUNCTION
		//切换追击模式
		Table_SkillEx const* pSkillEx =GetTable_SkillExByID(m_OwnSkillList[0]);
	if (pSkillEx ==null_ptr)
	{
		//出异常了 切回待机AI
		SwitchAI(Obj_Npc::AI_IDLE);
		return;
	}
	
	m_fTraceStopDis =pSkillEx->GetRadius();
	StopMove(false,true);
	SwitchAI(Obj_Npc::AI_TRACE);
	if (m_nCurSelectObjId>0)
	{
		if (GetPlayerId()>0)
		{
			ObjTrackTargetMsgPtr MsgPtr = POOLDEF_NEW(ObjTrackTargetMsg);
			MsgPtr->m_nSceneId = GetSceneInstID();
			MsgPtr->m_nObjId   = GetID();
			MsgPtr->m_nTargetId = m_nCurSelectObjId;
			SendMessage2User(GetPlayerId(),MsgPtr);
		}
		


		Obj_CharacterPtr pTarget = GetScene().GetCharacterByID(m_nCurSelectObjId);
		if (pTarget != null_ptr && pTarget->GetPlayerId()>0)
		{
			ObjTrackTargetMsgPtr TMsgPtr = POOLDEF_NEW(ObjTrackTargetMsg);
			TMsgPtr->m_nSceneId = GetSceneInstID();
			TMsgPtr->m_nObjId   = GetID();
			TMsgPtr->m_nTargetId = m_nCurSelectObjId;
			SendMessage2User(pTarget->GetPlayerId(),TMsgPtr);
		}
	}
	
	
	__LEAVE_FUNCTION
}

void Obj_Npc::Tick_AI_March(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
	if (false ==GetActive() || false ==IsAlive())
	{
		return;
	}

	Moving(rTimeInfo);

	// 近战反攻
	tint32 nSeleObjId =SelectMethod_Sencond();
	if (nSeleObjId != invalid_id)
	{
		m_nCurSelectObjId = nSeleObjId;
		EnterTrace();
		return;
	}
	
	SelectMethod_March();


	__LEAVE_FUNCTION
}

void  Obj_Npc::EnterCombat(void)
{
	__ENTER_FUNCTION
		if (m_bIsInCombat ==true)
		{
			return;
		}
		////////////////////NPC 进入战斗处理///////////////////

		//切换到战斗AI
		SwitchAI(Obj_Npc::AI_COMBAT);
		if (m_nCurSelectObjId>0)
		{
			if (GetPlayerId()>0)
			{
				ObjAttackTargetMsgPtr MsgPtr = POOLDEF_NEW(ObjAttackTargetMsg);
				MsgPtr->m_nSceneId = GetSceneInstID();
				MsgPtr->m_nObjId   = GetID();
				int n = MsgPtr->m_nObjId;
				MsgPtr->m_nTargetId = m_nCurSelectObjId;
				SendMessage2User(GetPlayerId(),MsgPtr);
			}
			

			Obj_CharacterPtr pTarget = GetScene().GetCharacterByID(m_nCurSelectObjId);
			if (pTarget != null_ptr && pTarget->GetPlayerId()>0)
			{
				ObjAttackTargetMsgPtr TMsgPtr = POOLDEF_NEW(ObjAttackTargetMsg);
				TMsgPtr->m_nSceneId = GetSceneInstID();
				TMsgPtr->m_nObjId   = GetID();
				int n = TMsgPtr->m_nObjId;
				TMsgPtr->m_nTargetId = m_nCurSelectObjId;
				SendMessage2User(pTarget->GetPlayerId(),TMsgPtr);
			}
		}
		

		//最后调用基类的
		Obj_Character::EnterCombat();
		//最后调用
		OnEnterCombat();
	__LEAVE_FUNCTION
}

void  Obj_Npc::LeaveCombat(void)
{
	__ENTER_FUNCTION
		
		if (m_bIsInCombat ==false)
		{
			return;
		}
		////////////////////NPC 脱战处理///////////////////

		//仇恨列表清零
		m_enemyInfo.CleanUp();
		//清掉当前目标
		ChangeCurSelectObjId(invalid_id);

		//最后调用基类的
		Obj_Character::LeaveCombat();
		//最后调用
		OnLeaveCombat();

	__LEAVE_FUNCTION
}

int Obj_Npc::SelectNewSkillTarget(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx)
{
	__ENTER_FUNCTION
		if (IsSceneValid() ==false)
		{
			return invalid_id;
		}

		Scene& rScene =GetScene();
		//单攻和普攻校验技能
		if (rSkillBase.GetSelLogic() == TAEGETSEL_T::SINGLE || 
			(rSkillBase.GetSkillClass() & SKILLCLASS::AUTOREPEAT) != 0)
		{
			ScenePos selfPos =GetScenePos();
			NpcRefCont objCharList;
			float fMinDis =m_fAlertRadius;
			int nSelObjId =invalid_id;
			rScene.Scan_Npc_All(objCharList);
			for (int i=0;i<objCharList.Size();i++)
			{
				Obj_Npc &rNpc = objCharList[i];
				ESkillTarCheckRet bRet = Skill_IsWantedUnit(rSkillBase, rSkillEx, rNpc);
				if  (bRet==E_Skill_Tar_Effect)
				{
					return rNpc.GetID();
				}
			}
		}

		return invalid_id;
	__LEAVE_FUNCTION
		return invalid_id;
}

int Obj_Npc::SelectSkillAndTargetInTrace()
{
	__ENTER_FUNCTION
		if (IsSceneValid() ==false)
		{
			return invalid_id;
		}
		Scene& rScene =GetScene();
		int nSelSkillId =invalid_id;
		if (GetSkillStrategyId() ==invalid_id)
		{
			return invalid_id;
		}
		Table_NpcSkillStrategy const* pNpcSkillStrategy =GetTable_NpcSkillStrategyByIndex(GetSkillStrategyId());
		if (pNpcSkillStrategy ==null_ptr)
		{
			return invalid_id;
		}
		Table_NpcSkillStrategy const& rNpcSkillStrategy =*pNpcSkillStrategy;

		for (int nSkillIndex =0;nSkillIndex<MAXOWNSKILL;nSkillIndex++)
		{
			if (nSkillIndex ==0) //第一个放的是默认技能 跳过
			{
				continue; 
			}
			if (m_OwnSkillList[nSkillIndex] ==invalid_id)
			{
				continue;
			}
			int nSkillId =m_OwnSkillList[nSkillIndex];
			Table_SkillEx const* pSkillEx=GetTable_SkillExByID(nSkillId);

			if (pSkillEx !=null_ptr)
			{
				Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
				if (pSkillBase == null_ptr)
				{
					continue;
				}
		
				// 冲锋技能
				if ((pSkillBase->GetSkillClass() & SKILLCLASS::CHONGFENG) == 1)
				{
					continue;
				}

				Table_SkillEx const& rSkillEx =*pSkillEx;

				//检测技能是否在冷却
				if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
				{
					//检测消耗
					if (false ==CanDeplete(*pSkillBase,*pSkillEx))
					{
						continue;
					}
					//距离检测
					Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
					float fSkillRadius = rSkillEx.GetRadius();
					ScenePos selfPos = GetScenePos();
					ScenePos targetPos = TargetPtr->GetScenePos();
					float fDiffDis = selfPos.Distance(targetPos);
					if (fDiffDis - fSkillRadius >2) //!!这里做下容错 超过2的距离 再判断失败
					{
						continue;
					}
					return nSkillId;
				}
			}
		}
		return invalid_id;
	__LEAVE_FUNCTION
		return invalid_id;
}

void Obj_Npc::SelectSkillAndTarget(int& nSelSkillId,int& nSelObjectId)
{
	__ENTER_FUNCTION
		nSelSkillId = invalid_id;
		nSelObjectId = invalid_id;
		if (IsSceneValid() ==false)
		{
			return;
		}
		Scene& rScene =GetScene();
		if (GetSkillStrategyId() ==invalid_id)
		{
			return;
		}
		
		for (int nSkillIndex =0;nSkillIndex<MAXOWNSKILL;nSkillIndex++)
		{
			if (nSkillIndex ==0) //第一个放的是默认技能 跳过
			{
				continue; 
			}
			if (m_OwnSkillList[nSkillIndex] ==invalid_id)
			{
				continue;
			}
			int nSkillId =m_OwnSkillList[nSkillIndex];
			Table_SkillEx const* pSkillEx=GetTable_SkillExByID(nSkillId);

			if (pSkillEx !=null_ptr)
			{
				Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
				if (pSkillBase == null_ptr)
				{
					continue;
				}
				//自动技能
				if ((pSkillBase->GetSkillClass() & SKILLCLASS::PASSIVITY) == 1)
				{
					continue;
				}

				if (!m_bRobot && (pSkillBase->GetSkillClass() & SKILLCLASS::INITIATIVE) == 1)
				{
					continue;
				}

				Table_SkillEx const& rSkillEx =*pSkillEx;
					
				//检测技能是否在冷却
				if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
				{
					//检测消耗
					if (false ==CanDeplete(*pSkillBase,*pSkillEx))
					{
						continue;
					}
					nSelObjectId = SelectNewSkillTarget(*pSkillBase,*pSkillEx);
					//技能是否有可选目标
					if (nSelObjectId != invalid_id)
					{
						nSelSkillId = nSkillId;
						break;
					}
				}
			}
		}
		//无其他可选技能 则选择默认技能
		if (nSelSkillId ==invalid_id)
		{
			//默认技能 加一个攻击频率限制
			int nCurRunTime =gTimeManager.RunTime();;
			if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
			{
				Table_SkillEx const* pSkillEx=GetTable_SkillExByID(m_OwnSkillList[0]);
				if (pSkillEx !=null_ptr)
				{
					Table_SkillEx const& rSkillEx =*pSkillEx;
					//检测技能是否在冷却
					if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
					{
						//技能是否有可选目标
						nSelObjectId =SelectNewTarget(METHOD_NEAREST);
						if (nSelObjectId !=invalid_id)
						{
							Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(nSelObjectId);
							if (TargetPtr)
							{
								ChangeCurSelectObjId(nSelObjectId);
								nSelSkillId = m_OwnSkillList[0];
							}
						}
					}
				}
			}
		}
		
	__LEAVE_FUNCTION
}


void Obj_Npc::OnDie(Obj_Character& rKiller)
{
	__ENTER_FUNCTION
	Obj_Character::OnDie(rKiller);

	//!!!!最后调用
	if (IsSceneValid())
	{
		GetScene().OnObjDie(GetID(),rKiller.GetID());
	}

	BeginDeadStatus_DeadBody();
	
	
	__LEAVE_FUNCTION
}

