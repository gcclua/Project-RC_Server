#include "Obj_Npc.h"
#include "Table/Table_CoolDownTime.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Scene/Scene/Scene.h"
#include "ServerConfig.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "Table/Table_ArrangeSelectTarget.h"
#include "Scene/Scene/CopyScene.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_SkillBase.h"

POOLDEF_IMPL(Obj_Npc);

Obj_Npc::Obj_Npc( void )
{
	m_fAlertRadius =0.0f;//���䷶Χ
	m_curAIType =Obj_Npc::AI_IDLE;
	m_bDeadBody = false;
	m_nDeadBodyTime = 0;
	m_nCorpseTime =0;//ʬ��ͣ��ʱ��

	m_nLastAttackTime =0;//�ϴι�����ʱ��
	m_nAttackTime =0;//������Ƶ��
	m_fTraceStopDis =0.0f;
	m_nLastTraceTime =0;
	m_nTraceTime =0;
	m_nAttackDisType =-1;//������������ ��ս����Զ��
	m_nSkillStrategyId =-1;
	m_nXpSpeed = 0;


	m_nModelVisualID = invalid_id;		// ģ��ID
	m_nWeaponDataID = invalid_id;			// ����ID
	m_nKylinValue = 0;

	m_nSceneNpcID = invalid_id;
	m_nMutexID	= invalid_id;

	m_bRobot = true;

	m_nArrangeIndex = 0; // ���ε�λ��
	m_vecMarchTarget.clear();

}

Obj_Npc::~Obj_Npc( void )
{

}

void Obj_Npc::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Character::OnEnterScene();
	//SetCurHp(GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXHP)));

	__LEAVE_FUNCTION
}

void Obj_Npc::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Character::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Npc::OnEndMove(void)
{
	__ENTER_FUNCTION
	Obj_Character::OnEndMove();
	if (m_curAIType == AI_MARCH
		|| m_curAIType == AI_COMBAT)
	{
		int nSelObj = SelectNearestTarget();
		if (nSelObj != invalid_id)
		{
			m_nCurSelectObjId = nSelObj;
			EnterTrace();
		}
	}
	
	__LEAVE_FUNCTION
}

void Obj_Npc::Tick_Moving(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		//Stopping();
		//Moving(rTimeInfo);

	__LEAVE_FUNCTION
}

void Obj_Npc::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

	Obj_Character::Tick(rTimeInfo);
	//AI����

	Tick_AI(rTimeInfo);
	Tick_DeadStatus(rTimeInfo);

	__LEAVE_PROTECT
}

//int Obj_Npc::GetForceType(void) const
//{
//	return m_ForceType;
//}


bool Obj_Npc::CanBeView(Obj_Npc &rNpc)
{
	if (Obj_Character::CanBeView(rNpc))
	{
		if (IsDie())
		{
			return false;
		}

		return true;
	}
	else
	{
		return false;
	}
}

void Obj_Npc::BeginDeadStatus_DeadBody(void)
{
	m_bDeadBody = true;
	m_nDeadBodyTime = m_nCorpseTime;
}

void Obj_Npc::BeginDeadStatus_Disappear(void)
{
	m_bDeadBody = false;
	m_nDeadBodyTime = 0;
}

void Obj_Npc::Tick_DeadStatus(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (IsDie())
	{
		if (m_bDeadBody)
		{
			m_nDeadBodyTime -= rTimeInfo.m_uTimeElapse;
			if (m_nDeadBodyTime <= 0)
			{
				DelFromScene();
			}
		}
	}

	__LEAVE_FUNCTION
}

//��ȡ����ս��������ֵ
int Obj_Npc::GetCombatAttrByID(int AttrId)
{
	__ENTER_FUNCTION

		return m_FinalyAttr.GetCombatAttrByIndex(AttrId);
		__LEAVE_FUNCTION
			return 0;
}
void Obj_Npc::CalculateInitalAttr(void)
{
	__ENTER_FUNCTION
		//!!!���¼���ǰ ������
		m_InitialAttr.CleanUp();
		// mwh- dataid ��һ������index 
		Table_RoleBaseAttr const* pTable =GetTable_RoleBaseAttrByID(GetDataID());
		if (pTable ==null_ptr)
		{
			return;
		}
		Table_RoleBaseAttr const& rTable =*pTable;

		//��ʼ�� ����ս������ֵ
		
 		m_InitialAttr.SetCombatAttrByIndex((int)(COMBATATTR_T::MAXHP),rTable.GetMaxHP());
 		m_InitialAttr.SetCombatAttrByIndex((int)(COMBATATTR_T::ATTACK),rTable.GetAttack());
 		m_InitialAttr.SetCombatAttrByIndex((int)(COMBATATTR_T::DEFENCE),rTable.GetDefense());
 		m_InitialAttr.SetCombatAttrByIndex((int)(COMBATATTR_T::HIT),rTable.GetHit());
 		m_InitialAttr.SetCombatAttrByIndex((int)(COMBATATTR_T::MOVESPEED),rTable.GetMoveSpeed());
		m_InitialAttr.SetCombatAttrByIndex((int)(COMBATATTR_T::TOTALMAXHP),rTable.GetMaxHP());
	__LEAVE_FUNCTION
}

void Obj_Npc::CalculateFinalyAttr()
{
	__ENTER_FUNCTION
	bool isNeedCalculate=false;
	if (m_InitialAttr.IsCalculationFlagDirty())
	{
		CalculateInitalAttr();
		//������ɺ� �������
		m_InitialAttr.CleanAllCalculationDirtyFlag();
		
		isNeedCalculate=true;
	}
	if (m_SkillCombatRefix.IsCalculationFlagDirty())
	{
		CalculateSkillRefix();
		//������ɺ� �������
		m_SkillCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate=true;
	}
	if (m_BuffCombatRefix.IsCalculationFlagDirty())
	{
		CalculateBuffRefix();
		//������ɺ� �������
		m_BuffCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate=true;
	}

	//���¼��� ���յ�ս������ֵ
	if (isNeedCalculate)
	{
		m_FinalyAttr =m_InitialAttr*(m_SkillCombatRefix+m_BuffCombatRefix);
		//��ǰѪ �� XP ��������ʱ ��������ǰֵΪ����ֵ 
		int nMaxHp =GetCombatAttrByID((int)COMBATATTR_T::TOTALMAXHP);
		int nMaxXp =GetCombatAttrByID((int)COMBATATTR_T::MAXXP);

		if (GetCurHp() >nMaxHp)
		{
			SetCurHp(nMaxHp);
		}
		if (GetCurXP() >nMaxXp)
		{
			SetCurXp(nMaxXp);
		}
	}
	__LEAVE_FUNCTION
}

int Obj_Npc::GetNpcForceType() const
{
	__ENTER_FUNCTION
	
	return GetForceType();
	__LEAVE_FUNCTION
	return GetForceType();
}

void Obj_Npc::MoveAppend(const ScenePos &rPos)
{
	__ENTER_FUNCTION


		if (!IsMoving())
		{
			m_PathCont.PushBack(PathNode(GetScenePos(), rPos));
			OnStartMove();
		}
		else
		{
			tint32 nSize = m_PathCont.Size();
			AssertEx(nSize >= 1 && nSize <= m_PathCont.MaxSize(), "");
			m_PathCont.PushBack(PathNode(m_PathCont[nSize - 1].m_EndPos, rPos));
		}

		__LEAVE_FUNCTION
}

void   Obj_Npc::InitPassiveSkill()
{
	//��½ʱ ���ϱ�������buff
	for (tint32 index=0; index<MAXOWNSKILL; index++)
	{
		tint32 nSkillId = m_OwnSkillList[index];
		if (nSkillId != invalid_id)
		{
			Table_SkillEx const* pSkillEx = GetTable_SkillExByID(nSkillId);
			if (pSkillEx == null_ptr)
			{
				continue;
			}

			Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
			if (pSkillBase == null_ptr)
			{
				continue;
			}

			//��������
			if ((pSkillBase->GetSkillClass() & SKILLCLASS::PASSIVITY) != 0)
			{
				tint32 nImpactNum = pSkillEx->getImpactCount();
				for (tint32 i = 0; i < nImpactNum; i++)
				{
					tint32 nImpackId = pSkillEx->GetImpactbyIndex(i);
					if (nImpackId != invalid_id)
					{
						SendImpactToUnit(*this, nImpackId, nSkillId);
					}
				}
			}
		}
	}
}

void  Obj_Npc::SelectTargetForMarch(bool bAttack)
{
	__ENTER_FUNCTION
		Scene& rScene = GetScene();
	if (false == rScene.IsCopyScene())
	{
		return;
	}
	CopyScene& rCopyScene = dynamic_cast<CopyScene&>(rScene);
	tint32 nCount = GetTable_ArrangeSelectTargetCount();
	Table_ArrangeSelectTarget const * pCurTable = null_ptr;
	// ���Ҷ�Ӧ�������ļ�
	for (tint32 i=0;i<nCount;i++)
	{
		Table_ArrangeSelectTarget const * pTable = GetTable_ArrangeSelectTargetByIndex(i);
		if (pTable != null_ptr)
		{
			if (pTable->GetSceneClass() == rScene.GetSceneClassID() 
				&& pTable->GetArrangeIndex() == GetArrangeIndex()
				&& pTable->GetForce() == (int)bAttack)
			{
				pCurTable = pTable;
				break;
			}
		}

	}
	AssertEx(pCurTable,"");
	AssertEx(pCurTable->getMarchLineXCount() == pCurTable->getMarchLineZCount(),"");
	tint32 nMarchLine = pCurTable->getMarchLineXCount();
	for (tint32 i=0;i<nMarchLine;i++)
	{
		ScenePos tmPos;
		tmPos.m_fX = pCurTable->GetMarchLineXbyIndex(i);
		tmPos.m_fZ = pCurTable->GetMarchLineZbyIndex(i);
		if (tmPos.m_fX >0.f  && tmPos.m_fZ >0.f)
		{
			MoveAppend(tmPos);
		}
		
	}
	// �Ӷ�Ӧ��������Ѱ�������ȹ����ļ���
	m_vecMarchTarget.clear();
	for (tint32 i=0; i< MAX_ATTACK_SET; i++)
	{
		for (int j=0;j<MAX_ARRANGE_COUNT;j++)
		{
			// ѡ������˳���ҵ��Է��Ѿ��������λ��
			if (pCurTable->GetTargetPosbyIndex(j) == i)
			{
				tint32 nTargetID = rCopyScene.GetSceneArrangeSelectTarget(j,bAttack);
				if (nTargetID != invalid_id)
				{
					m_vecMarchTarget.push_back(nTargetID);
				}
			}

			
		}
		if (m_vecMarchTarget.size()>0)
		{
			break;
		}
		// �����������ϵ�ɨ��뾶+����ɨ��뾶����Ŀ��
		if (m_vecMarchTarget.size() == 0)
		{
			SetAlertRadius(GetAlertRadius()+pCurTable->GetSelectRadiusbyIndex(i));
		}
	}

	InitPassiveSkill();

	__LEAVE_FUNCTION
}