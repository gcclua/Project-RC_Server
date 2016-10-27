#include "SL_EffectToSelf.h"
#include "Scene/Obj/Obj_Character.h"
#include "Table/Table_SkillEx.h"
#include "Scene/Scene/Scene.h"
POOLDEF_IMPL(SL_EffectToSelf);
//��ʼ��Ч
 void SL_EffectToSelf::StarEffect(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		//�жϼ��ܵ���Ч��
		if (false ==IsValid() || false ==IsEffect())
		{
			return ;
		}
		if (false ==rSelf.IsSceneValid())
		{
			return ;
		}
		//ʹ�ü��ܺ� ���Լ����ϼ�BUFF�����ɷ�Ч����BUFF
		OnEffectOnUnit(rSelf,rSelf);
			
	__LEAVE_FUNCTION
 }

//�жϼ��ܴ���
 void SL_EffectToSelf::BreakSkill(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		if (false ==IsValid())
		{
			return ;
		}
		//���ܱ��ж� ��ɢ���ܼ������ϵķ��˺���BUFF
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		for (tint32 i=0;i<rSkillEx.getImpactCount();i++)
		{
			if (rSkillEx.GetImpactbyIndex(i) !=invalid_id)
			{
				rSelf.RemoveImpactById(rSkillEx.GetImpactbyIndex(i));
			}
		}
		SkillFinish(rSelf,true);
	__LEAVE_FUNCTION
 }
 