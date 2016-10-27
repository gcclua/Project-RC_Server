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
		{ // �������� TT 3736
			if ( m_bIsInCombat == true && m_curAIType == Obj_Npc::AI_IDLE )
			{ // �������ս��״̬,��AI����IDLE,��������һ��AI_COMBAT
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
		//���� ��û��Ҫ����
		int nEnemyCount =GetEnemyCount();
		if (nEnemyCount<=0)
		{
			return;
		}
		//�����л�Ŀ�����ȴʱ��
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
		bool bIsChange =false;//����б��Ƿ��б仯��
		//��� �Ƿ���Ҫ�Ƴ�����б��е�Ŀ��
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
				//��ʱ�Ƴ�
				if (nEnemyId !=m_nCurSelectObjId && //���ǵ�ǰ���Ŀ��
					Clock::getCurrentSystemTime() -rEnemy.GetLastThreatTime() >EnemyUnitList_T::MAXTIME)
				{
					m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
					bIsChange =true;
					continue;
				}
				Obj_CharacterPtr EnemyObjPtr =rScene.GetCharacterByID(nEnemyId);
				if (EnemyObjPtr)
				{
					//Ŀ���Ѿ����� �Ƴ�
					if (false ==EnemyObjPtr->GetActive() || 
						false ==EnemyObjPtr->IsAlive())
					{
						m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
						bIsChange =true;
						continue;
					}
					
					ScenePos enemyPos =EnemyObjPtr->GetScenePos();
					float _distance =enemyPos.Distance(GetRelivePos());
					//����npc��Ѳ�߷�Χ �Ƴ�����б�
					if (_distance -m_fPathRadius >0)
					{
						m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
						bIsChange =true;
						continue;
					}
				}
				else//�Ҳ����� �Ƴ�
				{
					m_enemyInfo.GetEnemyList().RemoveEnemyByIndex(i);
					bIsChange =true;
					continue;
				}
			}
		}
		//����б�䶯�� ����Ƿ�Ϊ��
		if (bIsChange)
		{
			nEnemyCount =GetEnemyCount();
			 //�ж��б� Ϊ�� ����ս��״̬ �˳�ս��״̬  
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
		//������ѡ���߼� ��һ���л�Ŀ����ȴʱ��ļ��
		if (m_nCurSelectObjId !=invalid_id)
		{
			Obj_CharacterPtr CurSelObj =rScene.GetCharacterByID(m_nCurSelectObjId);
			if (CurSelObj)
			{
				//��ǰ��ѡ���Ŀ�� �� ��δ���л�Ŀ�����ȴʱ��Ļ� ���β��л�Ŀ��
				if ( CurSelObj->GetActive() 
					&& CurSelObj->IsAlive()
					&& CurSelObj->CanBeScout(*this) //Ŀ���ܱ���쵽
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
//�������Ŀ��ѡ�� ģʽ
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
					// �ж��Ƿ�ɼ�
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
								//�����г���BUFF ���л� Ŀ��
								bool bIsInTaunt =false;
								ImpactPtrList::iterator it;
								for (it=m_buffList.begin();it!=m_buffList.end();it++)
								{
									ImpactBaseLogicPtr _ImpactLogicPtr =*it;
									//��Ч
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
									//����ս��ҵĳ�޳�����ǰ���Ŀ��ĳ��10%����10%��ʱ��
									//����ҳ�Ϊ�����µĹ���Ŀ��		
									if (IsCloseCombat())
									{
										int nThreatRate =static_cast<int>(nCurObjThreat*0.1f);
										if (nDiffThreat >0 && nDiffThreat>=nThreatRate)
										{
											nSeleobjId =nEnemyId;
											break;
										}

									}
									//	��Զ����ҵĳ�޳�����ǰ���Ŀ��ĳ��30%����30%��ʱ
									//	����ҳ�Ϊ�����µĹ���Ŀ��		
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
//�ڶ����Ŀ��ѡ�� ģʽ
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
					// �ж��Ƿ�ɼ�
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
//������Ŀ��ѡ�� ģʽ
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
		//���ж� ��Ч�ĵж�Ŀ��ĸ���
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
					// �ж��Ƿ�ɼ�
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive()&&
						EnemyObjPtr->CanBeScout(*this))
					{
						nVaildCount++;
					}
				}
			}
		}
		//����Ч������ ���һ��
		int nRandNum =Random::Gen(1,nVaildCount+1);
		
		//�ҵ�������� ��Ч��
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
					// �ж��Ƿ�ɼ�
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


//��Զ���Ŀ��ѡ�� ģʽ
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
					//�ж��Ƿ�ɼ�
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
//������� ģʽ
int Obj_Npc::SelectMethod_Clear(int nParam1 /*=-1*/, int nParam2 /*=-1*/)
{
	__ENTER_FUNCTION
		if (GetEnemyCount() <=0)
		{
			return invalid_id;
		}
		//�������
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
		//���ж� ��Ч�ĵж�Ŀ��ĸ���
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
					// �ж��Ƿ�ɼ�
					if (EnemyObjPtr->GetActive() && 
						EnemyObjPtr->IsAlive()&&
						EnemyObjPtr->CanBeScout(*this))
					{
						nVaildCount++;
					}
				}
			}
		}
		//����Ч������ ���һ��
		int nRandNum =Random::Gen(1,nVaildCount+1);

		//�ҵ�������� ��Ч��
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
					// �ж��Ƿ�ɼ�
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
					//�ж��Ƿ�ɼ�
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
//��Ŀ�귢���˺�
bool Obj_Npc::OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		Obj_Character::OnSendDamageToUnit(rTarget,rDamage);
	return true;
	__LEAVE_FUNCTION
		return false;
}
//�����˺�
void Obj_Npc::OnReceiveDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		Obj_Character::OnReceiveDamage(rDamage);
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION
		//������ �Ͳ�Ҫ��AI�߼���
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
		//todo �л�AI״̬�����ж�
		//�л����ؼ�AI �ȴ���ƶ�
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
		//todo ����״̬�� �����Ѳ�� ���� �л��� Ѳ��AI
		if ( IsNeedPatrol() )
		{
			StopMove(true,true);
			SwitchAI(Obj_Npc::AI_PATROL);
			return;
		}
		//��������������Ĺ� ��ɨ�踽���Ƿ��п��Թ�����Ŀ��
		if (m_ForceType ==FORCETYPE_T::NPC_ATTACK ||
			m_ForceType ==FORCETYPE_T::HELP_NPC )
		{
			if (SelectCanAttackObj())
			{
				return;
			}
		}
		//����״̬�� ��������ƶ���������ƶ�����
		if (IsCanRandMove())
		{
			ProessRandMove();
		}
		
	__LEAVE_FUNCTION
}
void Obj_Npc::ChangeCurSelectObjId(int nId)
{
	//����ѡ����ȴʱ��
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
		//Ѱ�Ҿ�������Ĺ���
		int nSeleIndex =invalid_id;
		for (int i = 0; i < objCharList.Size(); i++)
		{
			if (objCharList[i].IsAlive()==false || objCharList[i].GetActive() ==false)
			{
				continue;
			}
			//�ǵж� �ɱ���쵽
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
			//�ҵ����Թ�����Ŀ���л�Ϊս��״̬
			ChangeCurSelectObjId(nSelObjId);
			
			//��Ŀ��������б�
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
		//�����ƶ���npc������ƶ�
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
		//npc 10%�ĸ���������ε�
		if (nRandNum<Obj_Npc::RANDMOVERATE)
		{
			int nRandX =Random::Gen(0,2001) -1000;
			int nRandZ =Random::Gen(0,2001) -1000;

			float fRandX =nRandX*m_fRandMoveDis/1000.0f;
			float fRandZ =nRandZ*m_fRandMoveDis/1000.0f;

			//�ڳ����㸽���ε�
			const ScenePos& BornPos =GetRelivePos();
			ScenePos _newScenePos;
			_newScenePos.m_fX =BornPos.m_fX+fRandX;
			_newScenePos.m_fZ =BornPos.m_fZ+fRandZ;
			//�ƶ����µ�����
			if (rScene.IsScenePosWalkAble(_newScenePos)) //Ŀ�ĵ��ǿ������ߵĵ���ƶ���ȥ
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
		//ѡ�����Լ��������û������npc��ȥ�ĵ�
		int nSelePointIndex =-1;
		for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
		{
			ScenePos targetPos;
			float dis = fAttackDis-0.1f; //����ƫ��
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
		//���û�п��õĵ� �㶼��ռ���� ��ѡ�����Լ�����ĵ�
		if (nSelePointIndex ==-1)
		{
			for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
			{
				ScenePos targetPos;
				float dis = fAttackDis-0.1f; //����ƫ��
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
		if (rScene.IsScenePosWalkAble(MinDisPos)==false) //���Ҫȥ�ĵ��ǲ����Դﵽ�ĵ�����Ŀ����ƶ�
		{
			MoveTo(rUnit.GetScenePos(),fAttackDis-0.1f);
		}
		else
		{
			MoveTo(MinDisPos);
		}
		rUnit.SetTrackPointFlag(nSelePointIndex,true);//��׷�ٵ�Ŀ�� �õ��Ѿ���ռ����
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
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		Scene& rScene =GetScene();
		//���������̫Զ��ս
		float fDisBorn =GetScenePos().Distance(GetRelivePos());
		if (fDisBorn -m_fPathRadius >=0)
		{
			LeaveCombat();
			return;
		}
		Obj_CharacterPtr CharPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
		if (!CharPtr)
		{
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		//Ŀ������ �л�ս��״̬
		if (CharPtr->CanBeScout(*this) ==false)
		{
			SwitchAI(Obj_Npc::AI_COMBAT);
			return;
		}
		//׷��ʱ�䳬�� �л�Ŀ���ʱ�� ���л�ս��״̬ ���Ƿ���Ҫ����ѡ�񹥻�Ŀ�� ��Ҫһֱ׷�Ų�����
		m_nTraceTime +=rTimeInfo.m_uTimeElapse;
		if(m_nTraceTime>=Obj_Npc::SWITCHTARGETTIME)
		{
			m_nTraceTime=0;
			SwitchAI(Obj_Npc::AI_COMBAT);
			return;
		}
		float fDiffDis =GetScenePos().Distance(CharPtr->GetScenePos()); //����׷��Ŀ��ľ���
		float fDiffLastTraceDis =m_lastTracePos.Distance(CharPtr->GetScenePos());//������һ�ε�׷��Ŀ��ľ���
		if (!IsMoving() && fDiffDis<=m_fTraceStopDis) //����Ŀ�ĵ� ͣ���� �лص�ս��AI
		{
			SwitchAI(Obj_Npc::AI_COMBAT);
			return;
		}
		if (!IsMoving() && fDiffDis>m_fTraceStopDis) //û���ƶ� �һ�û��Ŀ�ĵ�׷��
		{
			ProessTrace(*CharPtr,m_fTraceStopDis);
		}
		else if(fDiffLastTraceDis>0.1f && fDiffDis>m_fTraceStopDis)//����׷��Ŀ�궯�� �޸�׷������
		{
			if (m_nLastTraceTime==0 ||(int)Clock::getCurrentSystemTime() -m_nLastTraceTime>=300) //��Ҫ�䶯��̫Ƶ��
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
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		ScenePos SelfPos =GetScenePos();
		//���������̫Զ��ս
		float fDisBorn =SelfPos.Distance(GetRelivePos());
		if (fDisBorn -m_fPathRadius >=0)
		{
			LeaveCombat();
			return;
		}
		//ѡ���ܺ͹���Ŀ��
		int nSkillId =SelectSkillAndTarget();
		if (nSkillId ==invalid_id) //����û�����ͷŵļ���
		{
			return;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr TargetCharPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
		if (!TargetCharPtr)
		{
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		//Ŀ��������
		if (TargetCharPtr->CanBeScout(*this) ==false)
		{
			//�лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		ScenePos TargetPos =TargetCharPtr->GetScenePos();
		Table_SkillEx const* pSkillEx =GetTable_SkillExByID(nSkillId);
		if (pSkillEx ==null_ptr)
		{
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		Table_SkillBase const* pSkillBase =GetTable_SkillBaseByID(pSkillEx->GetBaseId());
		if (pSkillBase ==null_ptr)
		{
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		Table_SkillEx const& rSkillEx =*pSkillEx;
		Table_SkillBase const& rSkillBase =*pSkillBase;
		float fDiffDistance =SelfPos.Distance(TargetPos);
		//���벻�� ��׷��(���������õļ��� ����׷��)
		if(rSkillBase.GetSelLogic() !=TAEGETSEL_T::SELF)
		{
			if (fDiffDistance-rSkillEx.GetRadius() >0)
			{
				int nMoveSpeedAttr =GetCombatAttrByID(COMBATATTR_T::MOVESPEED);
				//�����ƶ���npc��׷��
				if (nMoveSpeedAttr >0)
				{
					//�л�׷��ģʽ
					m_fTraceStopDis =rSkillEx.GetRadius();
					SwitchAI(Obj_Npc::AI_TRACE);
				}
				return;
			}
		}
 		if (UseSkill(nSkillId,m_nCurSelectObjId))
 		{
			m_nLastAttackTime =(int)Clock::getCurrentSystemTime(); //��¼�¹���ʱ��
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
	//todo ��������������Ĺ� ��ɨ�踽���Ƿ��п��Թ�����Ŀ��

	//�鿴�Ƿ���Ѳ��·����
	if ( m_nCurPatrolStep < 0 )
	{
		return;
	}
	//�����ƶ��в��ý�������һ��״̬�������ƶ�״̬���ܻ�������ţ�
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
	//Ŀ����Ƿ�ﵽ
	if ( GetScenePos().DistanceSquare( destPos ) < 2 )
	{
		//������⶯��//////////////////////////////////////////////////////////////////////////
		//�ӳ�x�����
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
		//��Ч
		if ( pPoint->GetAction() == Obj_Npc::PATROL_EVENT_BUFF )
		{
			int nBuffID = pPoint->GetPbyIndex(Obj_Npc::PATROL_PARAM_BUFFID);
			SendImpactToUnit(*this, nBuffID, invalid_id);
		}
		//Ѱ����һ����,���߽�������//////////////////////////////////////////////////////////////////////////
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
			//��һ�����mark������ͬ
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
	//ָ��ǰĿ���
	else
	{
		MoveTo(destPos);
	}
	__LEAVE_FUNCTION
}
void Obj_Npc::Tick_AI_Follow(TimeInfo const& rTimeInfo)
{
	__ENTER_FUNCTION

	//���������� �����Ŀ���ƶ�
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
				//������� ���账��
				return;
			}
			if (IsMoving() == false)
			{
				//�������ƶ�
				MoveTo(destPos);
			}
		}
		else
		{
			//�Ҳ�������Ŀ�� �л�������״̬
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
		////////////////////NPC ����ս������///////////////////

		//�л�Ŀ�����ȴʱ������
		m_nSwitchTargetCooldown =0;
		//�л���ս��AI
		SwitchAI(Obj_Npc::AI_COMBAT);
		m_nEnterCombatTime = static_cast<uint32> (Clock::getCurrentSystemTime());

		if (m_ForceType == FORCETYPE_T::NPC_ATTACK || m_ForceType == FORCETYPE_T::NPC_NEUTRALITY)
		{
			m_nCureTime = 0;
			m_nIncHp = 0;
			m_nIncMp = 0;
		}
		//�����û����
		Obj_Character::EnterCombat();
		//������
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
		////////////////////NPC ��ս����///////////////////

		//�л�Ŀ�����ȴʱ������
		m_nSwitchTargetCooldown =0;
		//����б�����
		m_enemyInfo.CleanUp();
		//�����ǰĿ��
		ChangeCurSelectObjId(invalid_id);

		//�����û����
		Obj_Character::LeaveCombat();
		//������
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
		//����ȱʡ������ �Ƿ���������Ŀ�ѡ���� ������ɸѡ�����ü���
		bsarray<CanUseSkillSkillInfo, MAXOWNSKILL> CanSeleSkillInfo;
		int nVaildSkillNum =0;
		int nTotalWeight =0;
		if (rNpcSkillStrategy.GetIsHaveOptionalSkill() ==1)
		{
			for (int nSkillIndex =0;nSkillIndex<MAXOWNSKILL;nSkillIndex++)
			{
				if (nSkillIndex ==0) //��һ���ŵ���Ĭ�ϼ��� ����
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
					//��⼼���Ƿ�����ȴ
					if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
					{
						//�����Ƿ��п�ѡĿ��
						Table_NpcOptionalSkill const* pOptionalSkill =GetTable_NpcOptionalSkillByID(nSkillId);
						if (pOptionalSkill !=null_ptr)
						{
							Table_NpcOptionalSkill const& rOptionalSkill =*pOptionalSkill;
							int nTargetObjId =invalid_id;
							//�Ƿ���ϼ���ɸѡ����
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
										nTotalWeight +=rOptionalSkill.GetWeight();//Ȩ���ۼ�
										nVaildSkillNum++;
									}
								}
							}
						}

					}
				}
			}
		}
		//��������ѡ���� ��ѡ��Ĭ�ϼ���
		if (nVaildSkillNum <=0)
		{
			//Ĭ�ϼ��� ��һ������Ƶ������
			int nCurRunTime =(int)Clock::getCurrentSystemTime();
			if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
			{
				Table_SkillEx const* pSkillEx=GetTable_SkillExByID(rNpcSkillStrategy.GetDefaultSkillId());
				if (pSkillEx !=null_ptr)
				{
					Table_SkillEx const& rSkillEx =*pSkillEx;
					//��⼼���Ƿ�����ȴ
					if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
					{
						//�����Ƿ��п�ѡĿ��
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
			//�����ͷ� ��ȴʱ�䵽�˾��ͷŵļ���
			int nCanSeleIndex =-1;
			int nSelePriority =-1;
			for (int nIndex = 0; nIndex < nVaildSkillNum; nIndex++)
			{
				if (nIndex>=0 && nIndex<MAXOWNSKILL)
				{
					if(CanSeleSkillInfo[nIndex].m_nUseType ==SKILLUSE_CD)
					{
						//�ж������ȼ�
						if (CanSeleSkillInfo[nIndex].m_nPriority<nSelePriority || nSelePriority==-1)
						{
							nCanSeleIndex =nIndex;
							nSelePriority =CanSeleSkillInfo[nIndex].m_nPriority;
						}
					}
				}
			}
			//�������ͷŵļ��� ��ѡ�������ͷŵļ���
			if (nCanSeleIndex>=0 && nCanSeleIndex<MAXOWNSKILL)
			{
				nSeleSkillId =CanSeleSkillInfo[nCanSeleIndex].m_nSkillId;
				//����ѡ��Ŀ��
				ChangeCurSelectObjId(CanSeleSkillInfo[nCanSeleIndex].m_nSeleObjId);
			}
			//���ǰ��û������ѡ��ļ��� ����Ȩ��ѡ��
			if (nSeleSkillId ==invalid_id)
			{
				nTotalWeight +=rNpcSkillStrategy.GetDefaultSkillWeight();//����Ĭ�ϼ��ܵ�Ȩ�� Ҳ��Ĭ�ϼ���һ�α�ѡ��Ļ���
				//Ȩ�����
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
							//����ѡ��Ŀ��
							ChangeCurSelectObjId(CanSeleSkillInfo[nIndex].m_nSeleObjId);
							break;
						}
					}
				}
			}
			//Ȩ����� ��û�ڿ�ѡ������ѡ��һ������ ��ʹ��Ĭ�ϼ���
			if (nSeleSkillId ==invalid_id)
			{
				//Ĭ�ϼ��� ��һ������Ƶ������
				int nCurRunTime =(int)Clock::getCurrentSystemTime();
				if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
				{
					Table_SkillEx const* pSkillEx=GetTable_SkillExByID(rNpcSkillStrategy.GetDefaultSkillId());
					if (pSkillEx !=null_ptr)
					{
						Table_SkillEx const& rSkillEx =*pSkillEx;
						//��⼼���Ƿ�����ȴ
						if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
						{
							//�����Ƿ��п�ѡĿ��
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
			//ȡ��Scene
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

	//!!!!������
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
		//�ǵж� �ɱ���쵽
		if (GetRelationByForceType(objCharList[i])==(int)(RELATIONTYPE_T::ENEMY) && objCharList[i].CanBeScout(*this))
		{
			if ( objCharList[i].GetID() != m_nCurSelectObjId)
			{
				//�ҵ����Թ�����Ŀ���л�Ϊս��״̬
				ChangeCurSelectObjId(objCharList[i].GetID());
				OnThreat(objCharList[i],1);
				SwitchAI(Obj_Npc::AI_COMBAT);
				break;
			}
		}
	}

	
	__LEAVE_FUNCTION
}
