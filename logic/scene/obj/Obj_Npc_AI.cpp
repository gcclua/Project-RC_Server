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
		//更新切换目标的冷却时间
		m_nSwitchTargetCooldown -=rTimeInfo.m_uTimeElapse;
		if (m_nSwitchTargetCooldown <=0)
		{
			m_nSwitchTargetCooldown =0;
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
					Clock::getCurrentSystemTime() -rEnemy.GetLastThreatTime() >EnemyUnitList_T::MAXTIME)
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
					
					ScenePos enemyPos =EnemyObjPtr->GetScenePos();
					float _distance =enemyPos.Distance(GetRelivePos());
					//超出npc的巡逻范围 移除仇恨列表
					if (_distance -m_fPathRadius >0)
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

int Obj_Npc::SelectNewTarget(int SelMethod,int nParam1, int nParam2)
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
					&& CurSelObj->CanBeScout(*this) //目标能被侦察到
					&& m_nSwitchTargetCooldown >0
					&& SelMethod ==Obj_Npc::METHOD_NORMAL)
				{
					return m_nCurSelectObjId;
				}
			}
		}
		if (GetEnemyCount() <=0)
		{
			return invalid_id ;
		}
		int nSeleObjId =invalid_id;
		switch (SelMethod)
		{
		case Obj_Npc::METHOD_NORMAL:
			nSeleObjId =SelectMethod_Normal(nParam1,nParam2);
			break;
		case Obj_Npc::METHOD_SECOND:
			nSeleObjId =SelectMethod_Sencond(nParam1,nParam2);
			break;
		case Obj_Npc::METHOD_RAND:
			nSeleObjId =SelectMethod_Rand(nParam1,nParam2);
			break;
		case Obj_Npc::METHOD_FURTHEST:
			nSeleObjId =SelectMethod_Furthest(nParam1,nParam2);
			break;
		case Obj_Npc::METHOD_CLEAR:
			nSeleObjId =SelectMethod_Clear(nParam1,nParam2);
			break;
		case Obj_Npc::METHOD_IMPACT:
			nSeleObjId =SelectMethod_Impact(nParam1,nParam2);
			break;
		default:
			break;
		}
		return nSeleObjId;
	__LEAVE_FUNCTION
		return invalid_id;
}
//正常仇恨目标选择 模式
int Obj_Npc::SelectMethod_Normal(int nParam1 /*=-1*/, int nParam2 /*=-1*/ )
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
		
		int nSeleobjId =m_nCurSelectObjId;
		const int nListSize =rEnemyList.GetSize();
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
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					if (EnemyObjPtr->GetActive() &&
						EnemyObjPtr->IsAlive() &&
						EnemyObjPtr->CanBeScout(*this))
					{
						Obj_CharacterPtr CurSelObj =rScene.GetCharacterByID(m_nCurSelectObjId);
						if (CurSelObj)
						{
							if (CurSelObj->GetActive() 
								&& CurSelObj->IsAlive()
								&& CurSelObj->CanBeScout(*this))
							{
								//身上有嘲讽BUFF 不切换 目标
								bool bIsInTaunt =false;
								ImpactPtrList::iterator it;
								for (it=m_buffList.begin();it!=m_buffList.end();it++)
								{
									ImpactBaseLogicPtr _ImpactLogicPtr =*it;
									//有效
									if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
									{
										if (_ImpactLogicPtr->IsTaunt())
										{
											bIsInTaunt =true;
											break;
										}
									}
								}
								if (bIsInTaunt)
								{
									nSeleobjId =m_nCurSelectObjId;
									break;
								}
								else
								{
									int nCurObjThreat =GetUnitThreat(*CurSelObj);
									int nEnemyThreat =rEnemy.GetThreat();
									int nDiffThreat =nEnemyThreat -nCurObjThreat;
									//当近战玩家的仇恨超过当前仇恨目标的仇恨10%（含10%）时，
									//此玩家成为怪物新的攻击目标		
									if (IsCloseCombat())
									{
										int nThreatRate =static_cast<int>(nCurObjThreat*0.1f);
										if (nDiffThreat >0 && nDiffThreat>=nThreatRate)
										{
											nSeleobjId =nEnemyId;
											break;
										}

									}
									//	当远程玩家的仇恨超过当前仇恨目标的仇恨30%（含30%）时
									//	此玩家成为怪物新的攻击目标		
									else if (IsLongCombat())
									{
										int nThreatRate =static_cast<int>(nCurObjThreat*0.3f);
										if (nDiffThreat >0 && nDiffThreat>=nThreatRate)
										{
											nSeleobjId =nEnemyId;
											break;
										}
									}
								}
							}
							else
							{
								nSeleobjId =nEnemyId;
								break;
							}
						}
						else
						{
							nSeleobjId =nEnemyId;
							break;
						}
					}
				}
			}
		}
		return nSeleobjId;
	__LEAVE_FUNCTION
		return invalid_id;
}
//第二仇恨目标选择 模式
int Obj_Npc::SelectMethod_Sencond(int nParam1 /*=-1*/, int nParam2 /*=-1*/)
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
		int nMaxThreat =0;
		int nSecondThreat =0;
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
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive() &&
						EnemyObjPtr->CanBeScout(*this))
					{
						if (nEnemyThreat >=nMaxThreat)
						{
							nMaxThreat =nEnemyThreat;
						}
						else if (nEnemyThreat >nSecondThreat)
						{
							nSecondThreat =nEnemyThreat;
							nSelObjId =rEnemy.GetObjID();
						}
					}
				}
			}
		}
		return nSelObjId;
	__LEAVE_FUNCTION
		return invalid_id;

}
//随机仇恨目标选择 模式
int Obj_Npc::SelectMethod_Rand(int nParam1 /*=-1*/, int nParam2 /*=-1*/)
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
		//先判断 有效的敌对目标的个数
		int nVaildCount =0;
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
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive()&&
						EnemyObjPtr->CanBeScout(*this))
					{
						nVaildCount++;
					}
				}
			}
		}
		//从有效的里面 随机一下
		int nRandNum =Random::Gen(1,nVaildCount+1);
		
		//找到随机到的 有效的
		int nNewVaildCount =0;
		int nSelObjId =invalid_id;
		for (int nIndex=0;nIndex<nListSize;nIndex++)
		{
			if (false ==rEnemyList.IsUnitVaild(nIndex))
			{
				continue;
			}

			EnemyUnit_T const& rEnemy =rEnemyList.GetUnitByIndex(nIndex);
			if (rEnemy.isValid())
			{
				int nEnemyId =rEnemy.GetObjID();
				if (rEnemy.GetThreat()<=0)
				{
					continue;
				}
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive() &&
						EnemyObjPtr->CanBeScout(*this))
					{
						nNewVaildCount++;
						if (nNewVaildCount ==nRandNum)
						{
							nSelObjId =nEnemyId;
							break;
						}

					}
				}
			}
		}
		return nSelObjId;
	__LEAVE_FUNCTION
		return invalid_id;
}


//最远仇恨目标选择 模式
int Obj_Npc::SelectMethod_Furthest(int nParam1 /*=-1*/, int nParam2 /*=-1*/)
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
		ScenePos selfPos =GetScenePos();
		const int nListSize =rEnemyList.GetSize();
		float fMaxDistance =0.0f;
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
				if (rEnemy.GetThreat()<=0)
				{
					continue;
				}
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					//判断是否可见
					if (EnemyObjPtr->GetActive() &&
						EnemyObjPtr->IsAlive()&&
						EnemyObjPtr->CanBeScout(*this))
					{
						ScenePos EnemyPos =EnemyObjPtr->GetScenePos();
						float fDistance =selfPos.Distance(EnemyPos);
						if (fDistance -fMaxDistance >0)
						{
							fMaxDistance =fDistance;
							nSelObjId =EnemyObjPtr->GetID();
						}
					}
				}
			}
		}
		return nSelObjId;
	__LEAVE_FUNCTION
		return invalid_id;
}
//仇恨清零 模式
int Obj_Npc::SelectMethod_Clear(int nParam1 /*=-1*/, int nParam2 /*=-1*/)
{
	__ENTER_FUNCTION
		if (GetEnemyCount() <=0)
		{
			return invalid_id;
		}
		//仇恨清零
		int nClearCount =ClearFullThreat();
		if (nClearCount <=0)
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
		//先判断 有效的敌对目标的个数
		int nVaildCount =0;
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
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive()&&
						EnemyObjPtr->CanBeScout(*this))
					{
						nVaildCount++;
					}
				}
			}
		}
		//从有效的里面 随机一下
		int nRandNum =Random::Gen(1,nVaildCount+1);

		//找到随机到的 有效的
		int nNewVaildCount =0;
		int nSelObjId =invalid_id;
		for (int nIndex=0;nIndex<nListSize;nIndex++)
		{
			if (false ==rEnemyList.IsUnitVaild(nIndex))
			{
				continue;
			}

			EnemyUnit_T const& rEnemy =rEnemyList.GetUnitByIndex(nIndex);
			if (rEnemy.isValid())
			{
				int nEnemyId =rEnemy.GetObjID();
				if (rEnemy.GetThreat()<=0)
				{
					continue;
				}
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					// 判断是否可见
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive() &&
						EnemyObjPtr->CanBeScout(*this))
					{
						nNewVaildCount++;
						if (nNewVaildCount ==nRandNum)
						{
							nSelObjId =nEnemyId;
							break;
						}

					}
				}
			}
		}
		return nSelObjId;
	__LEAVE_FUNCTION
		return invalid_id;
}
int Obj_Npc::SelectMethod_Impact(int nParam1 /*=-1*/, int nParam2 /*=-1*/)
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
		int nNeedImpactId =nParam1;
		if (nNeedImpactId <=invalid_id)
		{
			return invalid_id;
		}
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
				if (rEnemy.GetThreat()<=0)
				{
					continue;
				}
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					//判断是否可见
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive() &&
						EnemyObjPtr->CanBeScout(*this)&&
						EnemyObjPtr->IsHaveImpact(nNeedImpactId)
						)
					{
						nSelObjId =nEnemyId;
						break;
					}
				}
			}
		}
		
		return nSelObjId;
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
		case Obj_Npc::AI_PATROL:
			Tick_AI_Patrol(rTimeInfo);
			break;
		case Obj_Npc::AI_COMBAT:
			Tick_AI_Combat(rTimeInfo);
			break;
		case Obj_Npc::AI_FOLLOW:
			Tick_AI_Follow(rTimeInfo);
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
		if ( IsNeedPatrol() )
		{
			StopMove(true,true);
			SwitchAI(Obj_Npc::AI_PATROL);
			return;
		}
		//如果是主动攻击的怪 这扫描附件是否有可以攻击的目标
		if (m_ForceType ==FORCETYPE_T::NPC_ATTACK ||
			m_ForceType ==FORCETYPE_T::HELP_NPC )
		{
			if (SelectCanAttackObj())
			{
				return;
			}
		}
		//待机状态下 可以随机移动的做随机移动处理
		if (IsCanRandMove())
		{
			ProessRandMove();
		}
		
	__LEAVE_FUNCTION
}
void Obj_Npc::ChangeCurSelectObjId(int nId)
{
	//重置选择冷却时间
	if (nId !=m_nCurSelectObjId)
	{
		ResetSwitchTargetCooldown();
	}
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
			SwitchAI(Obj_Npc::AI_COMBAT);
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
void Obj_Npc::ProessRandMove(void)
{
	__ENTER_FUNCTION
		if (IsMoving())
		{
			return;
		}
		if (IsSceneValid() == false)
		{
			return;
		}
		Scene& rScene =GetScene();
		int nMoveSpeedAttr =GetCombatAttrByID(COMBATATTR_T::MOVESPEED);
		//不能移动的npc不随机移动
		if (nMoveSpeedAttr <=0)
		{
			return;
		}
		int nCurRunTime = (int)(Clock::getCurrentSystemTime());
		int nDiffTime =nCurRunTime -m_nLastRandMoveTime;
		if (nDiffTime <Obj_Npc::RANDMOVEINTERVALTIME)
		{
			return;
		}
		
		int nRandNum =Random::Gen(0,100);
		//npc 10%的概率在随机游荡
		if (nRandNum<Obj_Npc::RANDMOVERATE)
		{
			int nRandX =Random::Gen(0,2001) -1000;
			int nRandZ =Random::Gen(0,2001) -1000;

			float fRandX =nRandX*m_fRandMoveDis/1000.0f;
			float fRandZ =nRandZ*m_fRandMoveDis/1000.0f;

			//在出生点附近游荡
			const ScenePos& BornPos =GetRelivePos();
			ScenePos _newScenePos;
			_newScenePos.m_fX =BornPos.m_fX+fRandX;
			_newScenePos.m_fZ =BornPos.m_fZ+fRandZ;
			//移动到新的坐标
			if (rScene.IsScenePosWalkAble(_newScenePos)) //目的点是可以行走的点才移动过去
			{
				MoveTo(_newScenePos);
			}

			m_nLastRandMoveTime =nCurRunTime;
		}
	__LEAVE_FUNCTION
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
		m_nLastTraceTime = (int)Clock::getCurrentSystemTime();
		m_lastTracePos =UnitfPos;
		ScenePos MinDisPos;
		float fMinDis =999999.0f;
		//选择离自己最近的且没有其他npc过去的点
		int nSelePointIndex =-1;
		for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
		{
			ScenePos targetPos;
			float dis = fAttackDis-0.1f; //做个偏移
			targetPos.m_fX = UnitfPos.m_fX + dis * cos(_PI * Pos[nPointIndex]/ 6);
			targetPos.m_fZ = UnitfPos.m_fZ + dis * sin(_PI * Pos[nPointIndex]/ 6);
			float fDis =GetScenePos().Distance(targetPos);
			if ((fDis -fMinDis <0) && rUnit.IsTrackPointUsed(nPointIndex) ==false)
			{
				fMinDis =fDis;
				MinDisPos =targetPos;
				nSelePointIndex =nPointIndex;
			}
		}
		//如果没有可用的点 点都被占光了 则选择离自己最近的点
		if (nSelePointIndex ==-1)
		{
			for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
			{
				ScenePos targetPos;
				float dis = fAttackDis-0.1f; //做个偏移
				targetPos.m_fX = UnitfPos.m_fX + dis * cos(_PI * Pos[nPointIndex]/ 6);
				targetPos.m_fZ = UnitfPos.m_fZ + dis * sin(_PI * Pos[nPointIndex]/ 6);
				float fDis =GetScenePos().Distance(targetPos);
				if (fDis -fMinDis <0)
				{
					fMinDis =fDis;
					MinDisPos =targetPos;
					nSelePointIndex =nPointIndex;
				}
			}
		}
		if (rScene.IsScenePosWalkAble(MinDisPos)==false) //如果要去的点是不可以达到的点则向目标点移动
		{
			MoveTo(rUnit.GetScenePos(),fAttackDis-0.1f);
		}
		else
		{
			MoveTo(MinDisPos);
		}
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
		Scene& rScene =GetScene();
		//距离出生点太远脱战
		float fDisBorn =GetScenePos().Distance(GetRelivePos());
		if (fDisBorn -m_fPathRadius >=0)
		{
			LeaveCombat();
			return;
		}
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
			SwitchAI(Obj_Npc::AI_COMBAT);
			return;
		}
		//追踪时间超过 切换目标的时间 则切回战斗状态 看是否需要重新选择攻击目标 不要一直追着不放了
		m_nTraceTime +=rTimeInfo.m_uTimeElapse;
		if(m_nTraceTime>=Obj_Npc::SWITCHTARGETTIME)
		{
			m_nTraceTime=0;
			SwitchAI(Obj_Npc::AI_COMBAT);
			return;
		}
		float fDiffDis =GetScenePos().Distance(CharPtr->GetScenePos()); //距离追击目标的距离
		float fDiffLastTraceDis =m_lastTracePos.Distance(CharPtr->GetScenePos());//距离上一次的追踪目标的距离
		if (!IsMoving() && fDiffDis<=m_fTraceStopDis) //到达目的地 停下来 切回到战斗AI
		{
			SwitchAI(Obj_Npc::AI_COMBAT);
			return;
		}
		if (!IsMoving() && fDiffDis>m_fTraceStopDis) //没在移动 且还没到目的点追击
		{
			ProessTrace(*CharPtr,m_fTraceStopDis);
		}
		else if(fDiffLastTraceDis>0.1f && fDiffDis>m_fTraceStopDis)//发现追击目标动了 修改追击方向
		{
			if (m_nLastTraceTime==0 ||(int)Clock::getCurrentSystemTime() -m_nLastTraceTime>=300) //不要变动的太频繁
			{
				if (IsMoving())
				{
					StopMove(true,true);
				}
				ProessTrace(*CharPtr,m_fTraceStopDis);
			}
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
		//距离出生点太远脱战
		float fDisBorn =SelfPos.Distance(GetRelivePos());
		if (fDisBorn -m_fPathRadius >=0)
		{
			LeaveCombat();
			return;
		}
		//选择技能和攻击目标
		int nSkillId =SelectSkillAndTarget();
		if (nSkillId ==invalid_id) //本次没有能释放的技能
		{
			return;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr TargetCharPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
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
		if(rSkillBase.GetSelLogic() !=TAEGETSEL_T::SELF)
		{
			if (fDiffDistance-rSkillEx.GetRadius() >0)
			{
				int nMoveSpeedAttr =GetCombatAttrByID(COMBATATTR_T::MOVESPEED);
				//不能移动的npc不追踪
				if (nMoveSpeedAttr >0)
				{
					//切换追击模式
					m_fTraceStopDis =rSkillEx.GetRadius();
					SwitchAI(Obj_Npc::AI_TRACE);
				}
				return;
			}
		}
 		if (UseSkill(nSkillId,m_nCurSelectObjId))
 		{
			m_nLastAttackTime =(int)Clock::getCurrentSystemTime(); //记录下攻击时间
 		}
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI_Patrol(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
	if (false ==GetActive() || false ==IsAlive())
	{
		return;
	}
	//todo 如果是主动攻击的怪 这扫描附件是否有可以攻击的目标

	//查看是否有巡逻路径点
	if ( m_nCurPatrolStep < 0 )
	{
		return;
	}
	//正在移动中不用矫正（上一个状态遗留的移动状态可能会造成困扰）
	if ( IsMoving() )
	{
		return;
	}
	const Table_PatrolPoint* pPoint = GetTable_PatrolPointByID(m_nCurPatrolStep);
	if ( pPoint == null_ptr )
	{
		return;
	}
	ScenePos destPos((float)pPoint->GetPosx(), (float)pPoint->GetPosz());
	//目标点是否达到
	if ( GetScenePos().DistanceSquare( destPos ) < 2 )
	{
		//到点额外动作//////////////////////////////////////////////////////////////////////////
		//延迟x秒继续
		if ( pPoint->GetAction() == Obj_Npc::PATROL_EVENT_SLEEP)
		{			
			if ( m_nPatrolCountDown < pPoint->GetPbyIndex(Obj_Npc::PATROL_PARAM_SLEEPTIME) )
			{
				if ( rTimeInfo.m_bDiffSecond )
				{
					m_nPatrolCountDown++;			
				}
				return;
			}			
			//clear
			m_nPatrolCountDown = 0;
		}
		//特效
		if ( pPoint->GetAction() == Obj_Npc::PATROL_EVENT_BUFF )
		{
			int nBuffID = pPoint->GetPbyIndex(Obj_Npc::PATROL_PARAM_BUFFID);
			SendImpactToUnit(*this, nBuffID, invalid_id);
		}
		//寻找下一个点,或者结束操作//////////////////////////////////////////////////////////////////////////
		if ( pPoint->GetNextIndex() == Obj_Npc::PATROL_OVER )
		{
			m_nCurPatrolStep = invalid_id;
		}
		else if ( pPoint->GetNextIndex() == Obj_Npc::PATROL_OVER_DELETE )
		{
			DelFromScene();
		}
		else
		{
			//下一个点的mark必须相同
			const Table_PatrolPoint* pNext = GetTable_PatrolPointByID( pPoint->GetNextIndex() );
			if ( pNext && pNext->GetMark() == pPoint->GetMark() )
			{
				m_nCurPatrolStep = pPoint->GetNextIndex();
				MoveTo(ScenePos((float)pNext->GetPosx(), (float)pNext->GetPosz()));
			}
			else
			{
				m_nCurPatrolStep = invalid_id;
			}
		}
	}
	//指向当前目标点
	else
	{
		MoveTo(destPos);
	}
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI_Follow(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION

	//如果距离过大 向跟随目标移动
	if (IsSceneValid())
	{
		Scene& rScene = GetScene();
		Obj_CharacterPtr characterPtr = rScene.GetCharacterByID(m_FollowTargetObjId);
		if (characterPtr)
		{
			ScenePos destPos = characterPtr->GetFollowPos();
			ScenePos npcPos = GetScenePos();
			float fDistance = npcPos.Distance(destPos);
			if (fDistance < 0.1f)
			{
				//距离过近 无需处理
				return;
			}
			if (IsMoving() == false)
			{
				//向跟随点移动
				MoveTo(destPos);
			}
		}
		else
		{
			//找不到跟随目标 切换到待机状态
			SwitchAI(Obj_Npc::AI_IDLE);
		}
	}

	__LEAVE_FUNCTION
}
void  Obj_Npc::EnterCombat(void)
{
	__ENTER_FUNCTION
		if (m_bIsInCombat ==true)
		{
			return;
		}
		m_bIsJustEnterCombat = true;
		////////////////////NPC 进入战斗处理///////////////////

		//切换目标的冷却时间清零
		m_nSwitchTargetCooldown =0;
		//切换到战斗AI
		SwitchAI(Obj_Npc::AI_COMBAT);
		m_nEnterCombatTime = static_cast<uint32> (Clock::getCurrentSystemTime());

		if (m_ForceType == FORCETYPE_T::NPC_ATTACK || m_ForceType == FORCETYPE_T::NPC_NEUTRALITY)
		{
			m_nCureTime = 0;
			m_nIncHp = 0;
			m_nIncMp = 0;
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

		//切换目标的冷却时间清零
		m_nSwitchTargetCooldown =0;
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
int Obj_Npc::SelectSkillAndTarget(void)
{
	__ENTER_FUNCTION
		if (IsSceneValid() ==false)
		{
			return invalid_id;
		}
		Scene& rScene =GetScene();
		int nSeleSkillId =invalid_id;
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
		//除了缺省技能外 是否存在其他的可选技能 存在则筛选出可用技能
		bsarray<CanUseSkillSkillInfo, MAXOWNSKILL> CanSeleSkillInfo;
		int nVaildSkillNum =0;
		int nTotalWeight =0;
		if (rNpcSkillStrategy.GetIsHaveOptionalSkill() ==1)
		{
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
					Table_SkillEx const& rSkillEx =*pSkillEx;
					//检测技能是否在冷却
					if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
					{
						//技能是否有可选目标
						Table_NpcOptionalSkill const* pOptionalSkill =GetTable_NpcOptionalSkillByID(nSkillId);
						if (pOptionalSkill !=null_ptr)
						{
							Table_NpcOptionalSkill const& rOptionalSkill =*pOptionalSkill;
							int nTargetObjId =invalid_id;
							//是否符合技能筛选条件
							bool bContinue =false;
							if (rOptionalSkill.GetActivateLogic()==Obj_Npc::SKILL_NOCHECK)
							{
								bContinue =true;
							}
							else
							{
								switch (rOptionalSkill.GetActivateLogic())
								{
								case Obj_Npc::SKILL_ATTACKTIME:
									bContinue =IsCanSelectSkill_AttackTime();
									break;
								case Obj_Npc::SKILL_HPLESSTHEN:
									bContinue =IsCanSelectSkill_HpLessThen(rOptionalSkill);
									break;
								case Obj_Npc::SKILL_TARGETHPLESSTHEN:
									nTargetObjId =SelectNewTarget(rOptionalSkill.GetSeleTargetLogic(),rOptionalSkill.GetSelectParambyIndex(0),rOptionalSkill.GetSelectParambyIndex(1));
									bContinue =IsCanSelectSkill_TargetHpLessThen(rOptionalSkill,nTargetObjId);
									break;
								case Obj_Npc::SKILL_HAVEIMPACT:
									bContinue =IsCanSelectSkill_HaveImpact(rOptionalSkill);
									break;
								case Obj_Npc::SKILL_TARGETHAVEIMPACT:
									nTargetObjId =SelectNewTarget(rOptionalSkill.GetSeleTargetLogic(),rOptionalSkill.GetSelectParambyIndex(0),rOptionalSkill.GetSelectParambyIndex(1));
									bContinue =IsCanSelectSkill_TargetHaveImpact(rOptionalSkill,nTargetObjId);
									break;
								case Obj_Npc::SKILL_COMBATTIME:
									bContinue =IsCanSelectSkill_CombatTime(rOptionalSkill);
									break;
								case Obj_Npc::SKILL_SCRIPTCHECK:
									bContinue =IsCanSelectSkill_ScriptCheck(rOptionalSkill,nSkillId);
									break;
								default:
									break;
								}
							}
							if (bContinue)
							{
								if (nTargetObjId ==invalid_id)
								{
									nTargetObjId =SelectNewTarget(rOptionalSkill.GetSeleTargetLogic(),rOptionalSkill.GetSelectParambyIndex(0),rOptionalSkill.GetSelectParambyIndex(1));
								}
								if (nTargetObjId !=invalid_id)
								{
									if (nVaildSkillNum >=0 && nVaildSkillNum<MAXOWNSKILL)
									{
										CanSeleSkillInfo[nVaildSkillNum].m_nSkillId =rOptionalSkill.GetSkillId();
										CanSeleSkillInfo[nVaildSkillNum].m_SeleTargetLogic =rOptionalSkill.GetSeleTargetLogic();
										CanSeleSkillInfo[nVaildSkillNum].m_SelectParam1 =rOptionalSkill.GetSelectParambyIndex(0);
										CanSeleSkillInfo[nVaildSkillNum].m_nSelectParam2 =rOptionalSkill.GetSelectParambyIndex(1);
										CanSeleSkillInfo[nVaildSkillNum].m_nUseType =rOptionalSkill.GetUseType();
										CanSeleSkillInfo[nVaildSkillNum].m_nWeight =rOptionalSkill.GetWeight();
										CanSeleSkillInfo[nVaildSkillNum].m_nActivateLogic =rOptionalSkill.GetActivateLogic();
										CanSeleSkillInfo[nVaildSkillNum].m_nActivateParam1 =rOptionalSkill.GetActivateParambyIndex(0);
										CanSeleSkillInfo[nVaildSkillNum].m_nActivateParam2 =rOptionalSkill.GetActivateParambyIndex(1);
										CanSeleSkillInfo[nVaildSkillNum].m_nSeleObjId =nTargetObjId;
										CanSeleSkillInfo[nVaildSkillNum].m_nPriority =rOptionalSkill.GetSkillPriority();
										nTotalWeight +=rOptionalSkill.GetWeight();//权重累加
										nVaildSkillNum++;
									}
								}
							}
						}

					}
				}
			}
		}
		//无其他可选技能 则选择默认技能
		if (nVaildSkillNum <=0)
		{
			//默认技能 加一个攻击频率限制
			int nCurRunTime =(int)Clock::getCurrentSystemTime();
			if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
			{
				Table_SkillEx const* pSkillEx=GetTable_SkillExByID(rNpcSkillStrategy.GetDefaultSkillId());
				if (pSkillEx !=null_ptr)
				{
					Table_SkillEx const& rSkillEx =*pSkillEx;
					//检测技能是否在冷却
					if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
					{
						//技能是否有可选目标
						int nSeleObjId =SelectNewTarget(METHOD_NORMAL,-1,-1);
						if (nSeleObjId !=invalid_id)
						{
							Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(nSeleObjId);
							if (TargetPtr)
							{
								ChangeCurSelectObjId(nSeleObjId);
								nSeleSkillId = rNpcSkillStrategy.GetDefaultSkillId();
							}
						}
					}
				}
			}
		}
		else
		{
			//优先释放 冷却时间到了就释放的技能
			int nCanSeleIndex =-1;
			int nSelePriority =-1;
			for (int nIndex = 0; nIndex < nVaildSkillNum; nIndex++)
			{
				if (nIndex>=0 && nIndex<MAXOWNSKILL)
				{
					if(CanSeleSkillInfo[nIndex].m_nUseType ==SKILLUSE_CD)
					{
						//判断下优先级
						if (CanSeleSkillInfo[nIndex].m_nPriority<nSelePriority || nSelePriority==-1)
						{
							nCanSeleIndex =nIndex;
							nSelePriority =CanSeleSkillInfo[nIndex].m_nPriority;
						}
					}
				}
			}
			//有优先释放的技能 则选择优先释放的技能
			if (nCanSeleIndex>=0 && nCanSeleIndex<MAXOWNSKILL)
			{
				nSeleSkillId =CanSeleSkillInfo[nCanSeleIndex].m_nSkillId;
				//设置选择目标
				ChangeCurSelectObjId(CanSeleSkillInfo[nCanSeleIndex].m_nSeleObjId);
			}
			//如果前面没有优先选择的技能 则走权重选择
			if (nSeleSkillId ==invalid_id)
			{
				nTotalWeight +=rNpcSkillStrategy.GetDefaultSkillWeight();//加入默认技能的权重 也给默认技能一次被选择的机会
				//权重随机
				int nRandWeight =Random::Gen(0,nTotalWeight);
				int nTmpWeight =0;
				for (int nIndex = 0; nIndex < nVaildSkillNum; nIndex++)
				{
					if (nIndex>=0 && nIndex<MAXOWNSKILL)
					{
						nTmpWeight+=CanSeleSkillInfo[nIndex].m_nWeight;
						if(nRandWeight<nTmpWeight)
						{
							nSeleSkillId =CanSeleSkillInfo[nIndex].m_nSkillId;
							//设置选择目标
							ChangeCurSelectObjId(CanSeleSkillInfo[nIndex].m_nSeleObjId);
							break;
						}
					}
				}
			}
			//权重随机 还没在可选技能里选到一个技能 则使用默认技能
			if (nSeleSkillId ==invalid_id)
			{
				//默认技能 加一个攻击频率限制
				int nCurRunTime =(int)Clock::getCurrentSystemTime();
				if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
				{
					Table_SkillEx const* pSkillEx=GetTable_SkillExByID(rNpcSkillStrategy.GetDefaultSkillId());
					if (pSkillEx !=null_ptr)
					{
						Table_SkillEx const& rSkillEx =*pSkillEx;
						//检测技能是否在冷却
						if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
						{
							//技能是否有可选目标
							int nSeleObjId =SelectNewTarget(METHOD_NORMAL,-1,-1);
							if (nSeleObjId !=invalid_id)
							{
								Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(nSeleObjId);
								if (TargetPtr)
								{
									ChangeCurSelectObjId(nSeleObjId);
									nSeleSkillId = rNpcSkillStrategy.GetDefaultSkillId();
								}
							}
						}
					}
				}
			}
		}
		return nSeleSkillId;
	__LEAVE_FUNCTION
		return invalid_id;
}
bool Obj_Npc::IsCanSelectSkill_HpLessThen(Table_NpcOptionalSkill const& rNpcOptionalSkill)
{
	__ENTER_FUNCTION
		int nMaxHp =GetCombatAttrByID(COMBATATTR_T::MAXHP);
		int nCheckHp =(int)(nMaxHp*(rNpcOptionalSkill.GetActivateParambyIndex(0)/100.0f));
		if (GetCurHp()<nCheckHp)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Npc::IsCanSelectSkill_TargetHpLessThen(Table_NpcOptionalSkill const& rNpcOptionalSkill,int TargetId)
{
	__ENTER_FUNCTION
		if (TargetId ==invalid_id)
		{
			return false;
		}
		if (IsSceneValid() ==false)
		{
			return false;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(TargetId);
		if (TargetPtr)
		{
			int nMaxHp =TargetPtr->GetCombatAttrByID(COMBATATTR_T::MAXHP);
			int nCheckHp =(int)(nMaxHp*(rNpcOptionalSkill.GetActivateParambyIndex(0)/100.0f));
			if (TargetPtr->GetCurHp()<nCheckHp)
			{
				return true;
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool  Obj_Npc::IsCanSelectSkill_AttackTime()
{
	__ENTER_FUNCTION
		int nCurRunTime = (int)(Clock::getCurrentSystemTime());
		if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Npc::IsCanSelectSkill_HaveImpact(Table_NpcOptionalSkill const& rNpcOptionalSkill)
{
	__ENTER_FUNCTION
		int nImpactId =rNpcOptionalSkill.GetActivateParambyIndex(0);
		if (nImpactId <=invalid_id)
		{
			return false;
		}
		if (IsHaveImpact(nImpactId))
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
	 return false;
}
bool Obj_Npc::IsCanSelectSkill_TargetHaveImpact(Table_NpcOptionalSkill const& rNpcOptionalSkill,int TargetId)
{
	__ENTER_FUNCTION
		if (TargetId ==invalid_id)
		{
			return false;
		}
		int nImpactId =rNpcOptionalSkill.GetActivateParambyIndex(0);
		if (nImpactId <=invalid_id)
		{
			return false;
		}
		if (IsSceneValid() ==false)
		{
			return false;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(TargetId);
		if (TargetPtr)
		{
			if (TargetPtr->IsHaveImpact(nImpactId))
			{
				return true;
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Npc::IsCanSelectSkill_CombatTime(Table_NpcOptionalSkill const& rNpcOptionalSkill)
{
	__ENTER_FUNCTION
		if (m_bIsInCombat)
		{
			int nCombatTime = (int)(Clock::getCurrentSystemTime()-m_nEnterCombatTime);
			if (nCombatTime >=rNpcOptionalSkill.GetActivateParambyIndex(0))
			{
				return true;
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Npc::IsCanSelectSkill_ScriptCheck(Table_NpcOptionalSkill const& rNpcOptionalSkill,int const nCheckSkillId)
{
	__ENTER_FUNCTION
		bool bRet =Script_CheckUseSkill(nCheckSkillId);
		return bRet;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Npc::Script_CheckUseSkill(int nSkillId)
{
	__ENTER_FUNCTION
		if (IsSceneValid())
		{
			//取得Scene
			Scene& rScene = GetScene();
			bool bRet =rScene.OnScriptCheckUseSkill(GetID(),nSkillId);
			return bRet;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
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

void Obj_Npc::StartPatrol(Obj_Character& rChar, int nStartID)
{
	__ENTER_FUNCTION
	const Table_PatrolPoint* pStep = GetTable_PatrolPointByID(nStartID);
	if ( pStep )
	{
		m_nCurPatrolStep = nStartID;
	}
	//Log
	__LEAVE_FUNCTION
}

bool Obj_Npc::IsNeedPatrol()
{
	__ENTER_FUNCTION
	if ( m_nCurPatrolStep >= 0 )
	{
		return true;
	}
	__LEAVE_FUNCTION
	return false;
}


void Obj_Npc::FindUserTarget()
{
	__ENTER_FUNCTION
	if (m_nCurSelectObjId == invalid_id)
	{
		return ;
	}
	Scene& rScene = GetScene();
	if ( !rScene.IsManorScene())
	{
		return ;
	}
	Obj_CharacterPtr TargetCharPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
	if (!TargetCharPtr)
	{
		return ;
	}

	ScenePos selfPos = GetScenePos();
	CharacterRefCont objCharList;
	rScene.Scan_Character_Circle(objCharList, selfPos, m_fAlertRadius);
	for (int i = 0; i < objCharList.Size(); i++)
	{
		if (objCharList[i].IsAlive()==false || objCharList[i].GetActive() ==false)
		{
			continue;
		}
		//是敌对 可被侦察到
		if (GetRelationByForceType(objCharList[i])==(int)(RELATIONTYPE_T::ENEMY) && objCharList[i].CanBeScout(*this))
		{
			if ( objCharList[i].GetID() != m_nCurSelectObjId)
			{
				//找到可以攻击的目标切换为战斗状态
				ChangeCurSelectObjId(objCharList[i].GetID());
				OnThreat(objCharList[i],1);
				SwitchAI(Obj_Npc::AI_COMBAT);
				break;
			}
		}
	}

	
	__LEAVE_FUNCTION
}
