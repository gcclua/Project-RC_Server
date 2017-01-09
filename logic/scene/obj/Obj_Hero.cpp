#include "Obj_Hero.h"
#include "Table/Table_CoolDownTime.h"
#include "Table/Table_RoleBaseAttr.h"
//#include "Scene/Scene/Scene.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "Table/Table_Hero.h"
#include "Table/Table_RoleBaseAttr.h"
#include "Table/Table_ArrangeSelectTarget.h"

POOLDEF_IMPL(Obj_Hero);

Obj_Hero::Obj_Hero( void )
{
	
	m_nType    = 0;    //Ӣ������
	m_nLevel   = 0;   //�ȼ�
	m_nQuality = 0; // Ʒ��
}

Obj_Hero::~Obj_Hero( void )
{

}

void Obj_Hero::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Npc::OnEnterScene();

	__LEAVE_FUNCTION
}

void Obj_Hero::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Npc::OnLeaveScene();

	__LEAVE_FUNCTION
}

void Obj_Hero::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

	Obj_Npc::Tick(rTimeInfo);

	__LEAVE_PROTECT
}

bool Obj_Hero::CanBeView(Obj_Character &rObj)
{
	return true;
}

void Obj_Hero::CalculateInitalAttr(void)
{
	__ENTER_FUNCTION
		//!!!���¼���ǰ ������
		m_InitialAttr.CleanUp();

	Table_Hero const* pHero = GetTable_HeroByID(m_nType);
	if (pHero == null_ptr)
	{
		return ;
	}

	Table_RoleBaseAttr const * pRoleBase = GetTable_RoleBaseAttrByID(pHero->GetDataIDbyIndex(GetLevel()-1));
	if (pRoleBase == null_ptr)
	{
		return;
	}

	//��ʼ�� ����ս������ֵ
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::MAXHP, pRoleBase->GetMaxHP());
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::MAXXP, pRoleBase->GetMaxXP());
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::ATTACK,pRoleBase->GetAttack());
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::DEFENCE, pRoleBase->GetDefense());
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::HIT, pRoleBase->GetHit());
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::ATTACKSPEED, pRoleBase->GetAttackTime());
	m_InitialAttr.SetCombatAttrByIndex(COMBATATTR_T::MOVESPEED, pRoleBase->GetMoveSpeed());

	__LEAVE_FUNCTION
}

void Obj_Hero::CalculateFinalyAttr()
{
	__ENTER_FUNCTION
		bool isNeedCalculate = false;
	if (m_InitialAttr.IsCalculationFlagDirty())
	{
		CalculateInitalAttr();
		//������ɺ� �������
		m_InitialAttr.CleanAllCalculationDirtyFlag();
		isNeedCalculate = true;
	}
	if (m_SkillCombatRefix.IsCalculationFlagDirty())
	{
		CalculateSkillRefix();
		//������ɺ� �������
		m_SkillCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate = true;
	}
	if (m_BuffCombatRefix.IsCalculationFlagDirty())
	{
		CalculateBuffRefix();
		//������ɺ� �������
		m_BuffCombatRefix.CleanAllCalculationDirtyFlag();
		isNeedCalculate = true;
	}

	//���¼��� ���յ�ս������ֵ
	if (isNeedCalculate)
	{
		m_FinalyAttr =m_InitialAttr*(m_SkillCombatRefix+m_BuffCombatRefix);

		//��ǰѪ �� XP ��������ʱ ��������ǰֵΪ����ֵ 
		tint32 nMaxHp =GetCombatAttrByID((tint32)COMBATATTR_T::MAXHP);
		tint32 nMaxXp =GetCombatAttrByID((tint32)COMBATATTR_T::MAXXP);

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

//��ȡ����ս��������ֵ
tint32 Obj_Hero::GetCombatAttrByID(tint32 AttrId)
{
	__ENTER_FUNCTION

		return m_FinalyAttr.GetCombatAttrByIndex(AttrId);
	__LEAVE_FUNCTION
		return 0;
}
