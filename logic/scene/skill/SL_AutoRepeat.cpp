#include "SL_AutoRepeat.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(SL_AutoRepeat);
//开始生效
 void SL_AutoRepeat::StarEffect(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		//判断技能的有效性
		if (false ==IsValid() || false ==IsEffect())
		{
			return ;
		}
		if (false ==rSelf.IsSceneValid())
		{
			return ;
		}
		//自动连续技 向自己身上挂一个BUFF 定时向目标发送伤害
		OnEffectOnUnit(rSelf,rSelf);
	__LEAVE_FUNCTION
 }

//中断技能处理
 void SL_AutoRepeat::BreakSkill(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		if (false ==IsValid())
		{
			return ;
		}
		//连续技能被中断 消散身上的发伤害的BUFF
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
		 //死亡 终止技能
		 if (false ==rSelf.IsAlive() || rSelf.GetActive() ==false)
		 {
			 BreakSkill(rSelf);
			 return false;
		 }
		 //选中目标 消散或者死亡 则中断连续技
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
		 if (m_CurSkillInfo.m_nSkillDelayTime >0)//技能延迟生效
		 {
			 m_CurSkillInfo.m_nSkillDelayTime -=rTimeInfo.m_uTimeElapse;
			 return true;
		 }
		 if (false ==IsEffect())
		 {
			 m_bIsEffect =true;
			 OnTakeEffect(rSelf);//开始生效
		 }
		 return true; 
		 __LEAVE_FUNCTION
			 return false;
 }
