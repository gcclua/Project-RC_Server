#include "Obj_Npc.h"
#include "Table/Table_CoolDownTime.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Scene/Scene/Scene.h"
#include "ServerConfig.h"
#include "DictionaryFormat/DictionaryFormat.h"

POOLDEF_IMPL(Obj_Npc);

Obj_Npc::Obj_Npc( void )
{
	m_nLastRandMoveTime =0;
	m_fPathRadius =0.0f;//Ѳ�߷�Χ
	m_fAlertRadius =0.0f;//���䷶Χ
	m_bIsRandMove =false;//�Ƿ�����ε�
	m_fRandMoveDis =0.0f;//����ε���Χ
	m_nSwitchTargetCooldown =0;
	m_curAIType =Obj_Npc::AI_IDLE;
	m_nNpcType =NPC_TYPE::INVAILD;//npc����
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
	m_bIsJustEnterCombat = false;


	m_nModelVisualID = invalid_id;		// ģ��ID
	m_nWeaponDataID = invalid_id;			// ����ID
	m_nKylinValue = 0;

	m_nPatrolCountDown = 0;
	m_nCurPatrolStep = invalid_id;

	m_nCureTime = 0;
	m_nIncHp = 0;
	m_nIncMp = 0;

	m_nSceneNpcID = invalid_id;
	m_nMutexID	= invalid_id;

}

Obj_Npc::~Obj_Npc( void )
{

}

void Obj_Npc::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Character::OnEnterScene();
	SetCurHp(GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXHP)));

	__LEAVE_FUNCTION
}

void Obj_Npc::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Character::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Npc::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

	Obj_Character::Tick(rTimeInfo);
	//AI����

	Tick_AI(rTimeInfo);
	Tick_DeadStatus(rTimeInfo);

	// �Զ��ظ�
	Tick_AutoCure(rTimeInfo);

	__LEAVE_PROTECT
}

//int Obj_Npc::GetForceType(void) const
//{
//	return m_ForceType;
//}


bool Obj_Npc::CanBeView(Obj_March &rMarch)
{
	if (Obj_Character::CanBeView(rMarch))
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
		int nMaxHp =GetCombatAttrByID((int)COMBATATTR_T::MAXHP);
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

int Obj_Npc::GetNpcForceType(Obj_Character &rObj) const
{
	__ENTER_FUNCTION
	
	return GetForceType();
	__LEAVE_FUNCTION
	return GetForceType();
}