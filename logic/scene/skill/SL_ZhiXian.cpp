#include "SL_ZhiXian.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_SkillBase.h"

POOLDEF_IMPL(SL_ZhiXian);

void SL_ZhiXian::StarEffect(Obj_Character& rSelf)
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
		Table_SkillBase const& rSkillBase =*m_CurSkillInfo.m_pSkillBase; 
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;

		tint32 nTargetId =m_CurSkillInfo.m_nTargetId;
		//先向选择目标发送伤害
		Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(nTargetId);
		if (!TargetPtr)
		{
			return;
		}
		
		OnEffectOnUnit(rSelf,*TargetPtr);
		
		//有概率打出直线攻击
		tint32 nRandNum =Random::Gen(0,100);
		tint32 nSkillRate =rSkillEx.GetLogicParambyIndex(ZHIXIANRATE);
		if (nRandNum<nSkillRate)
		{
			tint32 nScope =rSkillEx.GetLogicParambyIndex(ZHIXIANSCOPE);
			CharacterRefCont objCharList;
			tfloat32 fDirection =rSelf.GetFaceDir();
			tfloat32 fLength =(tfloat32)(rSkillEx.GetLogicParambyIndex(ZHIXIANLENGTH));
			tfloat32 fScope=nScope/2.0f;
			tint32 nMaxNum =rSkillEx.GetLogicParambyIndex(MAXTARGETNUM);
			tint32 nSelNum =0;
			//!!!!注：以当前选择的目标为中心 选择
			rScene.Scan_Character_Ray(objCharList,TargetPtr->GetScenePos(),fDirection,fLength,fScope);
			for (tint32 i = 0; i < objCharList.Size(); i++)
			{
				if (nSelNum >=nMaxNum && nMaxNum!=-1) //-1表示无上限
				{
					break;
				}
				//过滤掉已经选择的目标
				if(objCharList[i].GetID() ==TargetPtr->GetID())
				{
					continue;
				}
				if (E_Skill_Tar_Effect == rSelf.Skill_IsWantedUnit(rSkillBase,rSkillEx,objCharList[i]))
				{
					OnEffectOnUnit(rSelf,objCharList[i]);
					nSelNum++;
				}
			}
		}
	__LEAVE_FUNCTION
}