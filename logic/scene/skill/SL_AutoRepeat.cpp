#include "SL_AutoRepeat.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(SL_AutoRepeat);
//��ʼ��Ч
 void SL_AutoRepeat::StarEffect(Obj_Character& rSelf)
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
		//�Զ������� ���Լ����Ϲ�һ��BUFF ��ʱ��Ŀ�귢���˺�
		OnEffectOnUnit(rSelf,rSelf);
	__LEAVE_FUNCTION
 }

//�жϼ��ܴ���
 void SL_AutoRepeat::BreakSkill(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		if (false ==IsValid())
		{
			return ;
		}
		//�������ܱ��ж� ��ɢ���ϵķ��˺���BUFF
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		for (int i=0;i<rSkillEx.getImpactCount();i++)
		{
			if (rSkillEx.GetImpactbyIndex(i) !=invalid_id)
			{
				rSelf.RemoveImpactById(rSkillEx.GetImpactbyIndex(i));
			}
		}
		SkillFinish(rSelf,true);
	__LEAVE_FUNCTION
 }
 bool SL_AutoRepeat::Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo)
 {
	 __ENTER_FUNCTION

		 if (false ==IsValid())
		 {
			 return false;
		 }
		 if (m_CurSkillInfo.m_nSkillRemainTime <=0)
		 {
			 SkillFinish(rSelf,false);
			 return false;
		 }
		 //���� ��ֹ����
		 if (false ==rSelf.IsAlive() || rSelf.GetActive() ==false)
		 {
			 BreakSkill(rSelf);
			 return false;
		 }
		 //ѡ��Ŀ�� ��ɢ�������� ���ж�������
		 if (rSelf.IsSceneValid())
		 {
			 Scene& rScene =rSelf.GetScene();
			 Obj_CharacterPtr SelObjPtr =rScene.GetCharacterByID(rSelf.GetCurSelectObjId());
			 if (SelObjPtr)
			 {
				 if (SelObjPtr->GetActive() ==false || SelObjPtr->IsAlive() ==false)
				 {
					 BreakSkill(rSelf);
					 return false;
				 }
			 }
			 else
			 {
				 BreakSkill(rSelf);
				 return false;
			 }
		 }
		 m_CurSkillInfo.m_nSkillRemainTime -=rTimeInfo.m_uTimeElapse;
		 if (m_CurSkillInfo.m_nSkillDelayTime >0)//�����ӳ���Ч
		 {
			 m_CurSkillInfo.m_nSkillDelayTime -=rTimeInfo.m_uTimeElapse;
			 return true;
		 }
		 if (false ==IsEffect())
		 {
			 m_bIsEffect =true;
			 OnTakeEffect(rSelf);//��ʼ��Ч
		 }
		 return true; 
		 __LEAVE_FUNCTION
			 return false;
 }
