#include "SL_Snare.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(SL_Snare);

SL_Snare::SL_Snare ()
{
	m_SnareObjId =invalid_id;
};
void SL_Snare::StarEffect(Obj_Character& rSelf)
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
		Scene& rScene =rSelf.GetScene();
		//IsValid 已经做了判空操作
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		tint32 nSnareId =rSkillEx.GetLogicParambyIndex(SNAREID);
		tint32 nPosSelType =rSkillEx.GetLogicParambyIndex(SNAREPOSTYPE);
		ScenePos SnarePos;
		if (nPosSelType ==POS_SELF)
		{
			SnarePos=rSelf.GetScenePos();
			//在脚下 种一个
			Obj_SnarePtr _snarePtr =rScene.CreateSnareObj(nSnareId,rSelf.GetID(),SnarePos);
			if (_snarePtr !=null_ptr)
			{
				m_SnareObjId =_snarePtr->GetID();
			}
		}
		else
		{
			Obj_CharacterPtr targetPtr =rScene.GetCharacterByID(rSelf.GetCurSelectObjId());
			if (targetPtr !=null_ptr)
			{
				SnarePos=targetPtr->GetScenePos();
				//在目标脚下 种一个
				Obj_SnarePtr _snarePtr =rScene.CreateSnareObj(nSnareId,rSelf.GetID(),SnarePos);
				if (_snarePtr !=null_ptr)
				{
					m_SnareObjId =_snarePtr->GetID();
				}
			}
		}
	__LEAVE_FUNCTION
}
//技能结束处理
void SL_Snare::SkillFinish(Obj_Character& rSelf,bool bIsBreak)
{
	__ENTER_FUNCTION
		//技能结束时 是否需要删除陷阱
		if (IsValid())
		{
			if (rSelf.IsSceneValid())
			{
				//IsValid 已经做了判空操作
				Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
				Scene& rScene =rSelf.GetScene();
				tint32 nIsDel =rSkillEx.GetLogicParambyIndex(SNAREDELTYPE);
				if (nIsDel ==1 )
				{
					Obj_SnarePtr _snarePtr =rScene.GetSnareObjByID(m_SnareObjId);
					if (_snarePtr !=null_ptr)
					{
						_snarePtr->DelFromScene();
					}
				}
			}
		}
		//调用基类的处理
		SkillBaseLogic::SkillFinish(rSelf,bIsBreak);
	__LEAVE_FUNCTION
}