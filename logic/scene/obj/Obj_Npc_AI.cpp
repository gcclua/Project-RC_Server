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
					gTimeManager.RunTime() -rEnemy.GetLastThreatTime() >EnemyUnitList_T::MAXTIME)
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

int Obj_Npc::SelectNewTarget(int SelMethod)
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
					&& CurSelObj->CanBeScout(*this)) //Ŀ���ܱ���쵽
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
//�ڶ����Ŀ��ѡ�� ģʽ
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
					// �ж��Ƿ�ɼ�
					// ���߻���ͨ����ս���ֲ����Ŀ�꣬���Խ�սĿ��һ���������Լ����ͻ�һֱ����ߣ����������ڳ���б���ѡ��սĿ����û�����
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
		
		
	__LEAVE_FUNCTION
}
void Obj_Npc::ChangeCurSelectObjId(int nId)
{
	//����ѡ����ȴʱ��
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
		//ѡ�����Լ��������û������npc��ȥ�ĵ�
		int nSelePointIndex =-1;
		for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
		{
			ScenePos targetPos;
			float dis = fAttackDis-0.1f; //����ƫ��
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
		//���û�п��õĵ� �㶼��ռ���� ��ѡ�����Լ�����ĵ�
		/*if (nSelePointIndex ==-1)
		{
			for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
			{
				ScenePos targetPos;
				float dis = fAttackDis-0.1f; //����ƫ��
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
		/*if (rScene.IsScenePosWalkAble(MinDisPos)==false) //���Ҫȥ�ĵ��ǲ����Դﵽ�ĵ�����Ŀ����ƶ�
		{
			MoveTo(rUnit.GetScenePos(),fAttackDis-0.1f);
		}
		else
		{
			MoveTo(MinDisPos);
		}*/
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

		Moving(rTimeInfo);

		Scene& rScene =GetScene();
		
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
			EnterCombat();
			return;
		}
		//׷��ʱ�䳬�� �л�Ŀ���ʱ�� ���л�ս��״̬ ���Ƿ���Ҫ����ѡ�񹥻�Ŀ�� ��Ҫһֱ׷�Ų�����
		m_nTraceTime +=rTimeInfo.m_uTimeElapse;

		float fDiffDis =GetScenePos().Distance(CharPtr->GetScenePos()); //����׷��Ŀ��ľ���
		float fDiffLastTraceDis =m_lastTracePos.Distance(CharPtr->GetScenePos());//������һ�ε�׷��Ŀ��ľ���
		if (fDiffDis<=m_fTraceStopDis) //����Ŀ�ĵ� ͣ���� �лص�ս��AI
		{
			EnterCombat();
			return;
		}

		if (!IsMoving() && fDiffDis>m_fTraceStopDis) //û���ƶ� �һ�û��Ŀ�ĵ�׷��
		{
			//ProessTrace(*CharPtr,m_fTraceStopDis);
			//m_lastTracePos =CharPtr->GetScenePos();
			//MoveTo(CharPtr->GetScenePos(),m_fTraceStopDis);
			ProessTrace(*CharPtr,m_fTraceStopDis);
		}
		else if(fDiffLastTraceDis>0.1f && fDiffDis>m_fTraceStopDis)//����׷��Ŀ�궯�� �޸�׷������
		{
			if (m_nLastTraceTime==0 ||gTimeManager.RunTime() -m_nLastTraceTime>=300) //��Ҫ�䶯��̫Ƶ��
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
			//���쳣�� �лش���AI
			SwitchAI(Obj_Npc::AI_IDLE);
			return;
		}
		ScenePos SelfPos =GetScenePos();
	
		//ѡ���ܺ͹���Ŀ��
		int nSkillId = invalid_id;
		int nSelTargetId = invalid_id;
		SelectSkillAndTarget(nSkillId,nSelTargetId);
		if (nSkillId ==invalid_id) //����û�����ͷŵļ���
		{
			return;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr TargetCharPtr =rScene.GetCharacterByID(nSelTargetId);
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
		if(rSkillBase.GetSelLogic() !=TAEGETSEL_T::SELF && rSkillBase.GetSkillClass() == SKILLCLASS::AUTOREPEAT )
		{
			if (fDiffDistance-rSkillEx.GetRadius() >0)
			{
				int nMoveSpeedAttr =GetCombatAttrByID(COMBATATTR_T::MOVESPEED);
				//�����ƶ���npc��׷��
				if (nMoveSpeedAttr >0)
				{
					EnterTrace();
				}
				return;
			}
		}
 		if (UseSkill(nSkillId,nSelTargetId))
 		{
			// �ж�Ҫ��Ҫ�޸ĵ�ǰĿ��
			m_nLastAttackTime =gTimeManager.RunTime(); //��¼�¹���ʱ��
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
		//�л�׷��ģʽ
		Table_SkillEx const* pSkillEx =GetTable_SkillExByID(m_OwnSkillList[0]);
	if (pSkillEx ==null_ptr)
	{
		//���쳣�� �лش���AI
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

	// ��ս����
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
		////////////////////NPC ����ս������///////////////////

		//�л���ս��AI
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

int Obj_Npc::SelectNewSkillTarget(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx)
{
	__ENTER_FUNCTION
		if (IsSceneValid() ==false)
		{
			return invalid_id;
		}

		Scene& rScene =GetScene();
		//�������չ�У�鼼��
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
				Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
				if (pSkillBase == null_ptr)
				{
					continue;
				}
		
				// ��漼��
				if ((pSkillBase->GetSkillClass() & SKILLCLASS::CHONGFENG) == 1)
				{
					continue;
				}

				Table_SkillEx const& rSkillEx =*pSkillEx;

				//��⼼���Ƿ�����ȴ
				if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
				{
					//�������
					if (false ==CanDeplete(*pSkillBase,*pSkillEx))
					{
						continue;
					}
					//������
					Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(m_nCurSelectObjId);
					float fSkillRadius = rSkillEx.GetRadius();
					ScenePos selfPos = GetScenePos();
					ScenePos targetPos = TargetPtr->GetScenePos();
					float fDiffDis = selfPos.Distance(targetPos);
					if (fDiffDis - fSkillRadius >2) //!!���������ݴ� ����2�ľ��� ���ж�ʧ��
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
				Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
				if (pSkillBase == null_ptr)
				{
					continue;
				}
				//�Զ�����
				if ((pSkillBase->GetSkillClass() & SKILLCLASS::PASSIVITY) == 1)
				{
					continue;
				}

				if (!m_bRobot && (pSkillBase->GetSkillClass() & SKILLCLASS::INITIATIVE) == 1)
				{
					continue;
				}

				Table_SkillEx const& rSkillEx =*pSkillEx;
					
				//��⼼���Ƿ�����ȴ
				if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
				{
					//�������
					if (false ==CanDeplete(*pSkillBase,*pSkillEx))
					{
						continue;
					}
					nSelObjectId = SelectNewSkillTarget(*pSkillBase,*pSkillEx);
					//�����Ƿ��п�ѡĿ��
					if (nSelObjectId != invalid_id)
					{
						nSelSkillId = nSkillId;
						break;
					}
				}
			}
		}
		//��������ѡ���� ��ѡ��Ĭ�ϼ���
		if (nSelSkillId ==invalid_id)
		{
			//Ĭ�ϼ��� ��һ������Ƶ������
			int nCurRunTime =gTimeManager.RunTime();;
			if (nCurRunTime -m_nLastAttackTime >m_nAttackTime)
			{
				Table_SkillEx const* pSkillEx=GetTable_SkillExByID(m_OwnSkillList[0]);
				if (pSkillEx !=null_ptr)
				{
					Table_SkillEx const& rSkillEx =*pSkillEx;
					//��⼼���Ƿ�����ȴ
					if (IsCoolDowning(rSkillEx.GetCDTimeId())==false)
					{
						//�����Ƿ��п�ѡĿ��
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

	//!!!!������
	if (IsSceneValid())
	{
		GetScene().OnObjDie(GetID(),rKiller.GetID());
	}

	BeginDeadStatus_DeadBody();
	
	
	__LEAVE_FUNCTION
}

