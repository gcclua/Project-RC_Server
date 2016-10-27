#include "ImpactLogic_005.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Obj/Obj_Npc.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_Impact.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(ImpactLogic_005);
void ImpactLogic_005::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		int nSkillId =m_ImpactStruct.m_nSkillId;

		int nHPRefixValue =rImpactData.GetParamValuebyIndex(HPREFIXVALUE);
		float fHPRefixPer =rImpactData.GetParamValuebyIndex(HPREFIXPER)/100.0f;

		int nMPRefixValue =rImpactData.GetParamValuebyIndex(MPREFIXVALUE);
		float fMPRefixPer =rImpactData.GetParamValuebyIndex(MPREFIXPER)/100.0f;

		int nXPRefixValue =rImpactData.GetParamValuebyIndex(XPREFIXVALUE);
		float fXPRefixPer =rImpactData.GetParamValuebyIndex(XPREFIXPER)/100.0f;

		float fHPRefixCurPer = rImpactData.GetParamValuebyIndex(HPREFIXCURPER) / 100.0f;
		//�����������ȵ��û���� StartEffect
		ImpactBaseLogic::StartEffect(rSelf);
		//�ȼ��������µ�����
		rSelf.CalculateFinalyAttr();
		if (nHPRefixValue !=0 ||
			rImpactData.GetParamValuebyIndex(HPREFIXPER) !=0 ||
			rImpactData.GetParamValuebyIndex(HPREFIXCURPER) != 0)
		{
			Obj_CharacterPtr SendPtr=GetImpactSender(rSelf);//ͳһʹ�ô˽ӿ�����ȡBUFF�����ߵ���Ϣ
			if (!SendPtr)
			{
				return;
			}
			int nMaxHP =rSelf.GetCombatAttrByID((int)(COMBATATTR_T::MAXHP));
			int nRefixCurHP = (int)(rSelf.GetCurHp() * fHPRefixCurPer); // ���ݵ�ǰѪ����������
			int nIncHp =(int)(nHPRefixValue+nMaxHP*fHPRefixPer + nRefixCurHP);
			rSelf.IncreaseHp(nIncHp,*SendPtr);
		}
	
		if (nXPRefixValue !=0 || rImpactData.GetParamValuebyIndex(XPREFIXPER) !=0)
		{
			int nMaxXP =rSelf.GetCombatAttrByID((int)(COMBATATTR_T::MAXXP));
			int nIncXp =(int)(nXPRefixValue+ nMaxXP*fXPRefixPer);
			rSelf.IncreaseXp(nIncXp);
		}
	__LEAVE_FUNCTION
}