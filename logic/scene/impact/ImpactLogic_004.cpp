#include "ImpactLogic_004.h"
#include "Scene/Obj/Obj_Character.h"
#include "Table/Table_Impact.h"

POOLDEF_IMPL(ImpactLogic_004);
void ImpactLogic_004::InitImpactDataInfo(ImpactStruct& rImpactStruct)
{
	__ENTER_FUNCTION
		//!!!�ȵ��û���� ��ʼ��
		ImpactBaseLogic::InitImpactDataInfo(rImpactStruct);

		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rLine =*(m_ImpactStruct.m_pImpactDataInfo);
		m_ImpactStruct.m_fContinuTime =rLine.GetParamValuebyIndex(CONTINUTIME)/1000.0f;
	__LEAVE_FUNCTION
}
//buff��ʼ��Ч
void ImpactLogic_004::StartEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		//�����������ȵ��û���� StartEffect
		ImpactBaseLogic::StartEffect(rSelf);
		//����ս������
		rSelf.MarkBuffRefixCalcDirty();
	__LEAVE_FUNCTION
}
//buff�Խ�ɫս�����Ե�����
 void  ImpactLogic_004::CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& buffCombatRefix)
{
	__ENTER_FUNCTION
		if (m_ImpactStruct.m_pImpactDataInfo ==null_ptr)
		{
			return;
		}
		Table_Impact const& rImpactData =*(m_ImpactStruct.m_pImpactDataInfo);
		//��δ��Ч�� 
		if (false ==IsEffect())
		{
			return;
		}
		//����1����
		int nAttrType1 =rImpactData.GetParamValuebyIndex(COMBATATTRTYPE1);
		if (nAttrType1>=0 && nAttrType1<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			int nRefixValue =rImpactData.GetParamValuebyIndex(TYPE1REFIXVALUE);
			float fRefixPer =rImpactData.GetParamValuebyIndex(TYPE1REFIXPER)/100.0f;
			int nOldRefixValue =buffCombatRefix.GetRefixValueByIndex(nAttrType1);
			float fOldRefixPer =buffCombatRefix.GetRefixPerByIndex(nAttrType1);
			int nNewRefixValue =nOldRefixValue+nRefixValue;
			float fNewRefixPer =fOldRefixPer+fRefixPer;
			buffCombatRefix.SetRefixValueByIndex(nAttrType1,nNewRefixValue);
			buffCombatRefix.SetRefixPerByIndex(nAttrType1,fNewRefixPer);
		}
		//����2����
		int nAttrType2 =rImpactData.GetParamValuebyIndex(COMBATATTRTYPE2);
		if (nAttrType2>=0 && nAttrType2<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			int nRefixValue =rImpactData.GetParamValuebyIndex(TYPE2REFIXVALUE);
			float fRefixPer =rImpactData.GetParamValuebyIndex(TYPE2REFIXPER)/100.0f;
			int nOldRefixValue =buffCombatRefix.GetRefixValueByIndex(nAttrType2);
			float fOldRefixPer =buffCombatRefix.GetRefixPerByIndex(nAttrType2);
			int nNewRefixValue =nOldRefixValue+nRefixValue;
			float fNewRefixPer =fOldRefixPer+fRefixPer;
			buffCombatRefix.SetRefixValueByIndex(nAttrType2,nNewRefixValue);
			buffCombatRefix.SetRefixPerByIndex(nAttrType2,fNewRefixPer);
		}
		//����3����
		int nAttrType3 =rImpactData.GetParamValuebyIndex(COMBATATTRTYPE3);
		if (nAttrType3>=0 && nAttrType3<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			int nRefixValue =rImpactData.GetParamValuebyIndex(TYPE3REFIXVALUE);
			float fRefixPer =rImpactData.GetParamValuebyIndex(TYPE3REFIXPER)/100.0f;
			int nOldRefixValue =buffCombatRefix.GetRefixValueByIndex(nAttrType3);
			float fOldRefixPer =buffCombatRefix.GetRefixPerByIndex(nAttrType3);
			int nNewRefixValue =nOldRefixValue+nRefixValue;
			float fNewRefixPer =fOldRefixPer+fRefixPer;
			buffCombatRefix.SetRefixValueByIndex(nAttrType3,nNewRefixValue);
			buffCombatRefix.SetRefixPerByIndex(nAttrType3,fNewRefixPer);
		}
		//����4����
		int nAttrType4 =rImpactData.GetParamValuebyIndex(COMBATATTRTYPE4);
		if (nAttrType4>=0 && nAttrType4<COMBATATTR_T::COMBATATTR_MAXNUM)
		{
			int nRefixValue =rImpactData.GetParamValuebyIndex(TYPE4REFIXVALUE);
			float fRefixPer =rImpactData.GetParamValuebyIndex(TYPE4REFIXPER)/100.0f;
			int nOldRefixValue =buffCombatRefix.GetRefixValueByIndex(nAttrType4);
			float fOldRefixPer =buffCombatRefix.GetRefixPerByIndex(nAttrType4);
			int nNewRefixValue =nOldRefixValue+nRefixValue;
			float fNewRefixPer =fOldRefixPer+fRefixPer;
			buffCombatRefix.SetRefixValueByIndex(nAttrType4,nNewRefixValue);
			buffCombatRefix.SetRefixPerByIndex(nAttrType4,fNewRefixPer);
		}
	__LEAVE_FUNCTION
}
 // Ч����ɢ
 void ImpactLogic_004::OnFadeOut(Obj_Character& rSelf)
 {
	 __ENTER_FUNCTION
		 //�����������ȵ��û���� OnFadeOut
		 ImpactBaseLogic::OnFadeOut(rSelf);

		 //����ս������
		 rSelf.MarkBuffRefixCalcDirty();
	__LEAVE_FUNCTION
 }