#include "SL_EffectToSelf.h"
#include "Scene/Obj/Obj_Character.h"
#include "Table/Table_SkillEx.h"
#include "Scene/Scene/Scene.h"
POOLDEF_IMPL(SL_EffectToSelf);
//开始生效
 void SL_EffectToSelf::StarEffect(Obj_Character& rSelf)
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
		//使用技能后 往自己身上加BUFF用来派发效果子BUFF
		OnEffectOnUnit(rSelf,rSelf);
			
	__LEAVE_FUNCTION
 }

//中断技能处理
 void SL_EffectToSelf::BreakSkill(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		if (false ==IsValid())
		{
			return ;
		}
		//技能被中断 消散技能加在身上的发伤害的BUFF
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
 