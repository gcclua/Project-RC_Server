#include "SL_ChongFeng.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(SL_ChongFeng);
SL_ChongFeng::SL_ChongFeng ()
{
	m_nNeedIncSpeed =0;
}

void SL_ChongFeng::OnActivate(Obj_Character& rSelf)
 {
	__ENTER_FUNCTION
		SkillBaseLogic::OnActivate(rSelf);
 		if (false ==rSelf.IsSceneValid())
 		{
 			return;
 		}
		if (IsValid() ==false)
		{
			return;
		}
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		Scene& rScene =rSelf.GetScene();
 		Obj_CharacterPtr SelePtr =rScene.GetCharacterByID(rSelf.GetCurSelectObjId());
 		if (SelePtr)
 		{
			ScenePos selfPos=rSelf.GetScenePos();
			ScenePos tarCharPos =SelePtr->GetScenePos();
			tint32 nStopDis =rSkillEx.GetLogicParambyIndex(STOPDIS);
			tfloat32 fDis =selfPos.Distance(tarCharPos)-nStopDis;
			tint32 fChongFengSpeed =rSkillEx.GetLogicParambyIndex(SPEED);
			m_nNeedIncSpeed =(tint32)(fChongFengSpeed-rSelf.GetMoveSpeed()*100);
			if (m_nNeedIncSpeed <0)
			{
				m_nNeedIncSpeed =0;
			}
			//置脏重算
			rSelf.MarkSkillRefixCalcDirty();
			//立即更新最新数据
			rSelf.CalculateFinalyAttr();
			//移动到目标点
	
			ScenePos TargetPos;
			TargetPos.m_fX = rSelf.GetScenePos().m_fX+cos(rSelf.GetFaceDir())*fDis;
			TargetPos.m_fZ = rSelf.GetScenePos().m_fZ+sin(rSelf.GetFaceDir())*fDis;
			rSelf.TeleMoveTo(TargetPos);
			//通知客户端移动到最新的位置
			rSelf.UpdateTeleMoveToClient(rSelf.GetScenePos(),false);
		}
	__LEAVE_FUNCTION
 }

 void SL_ChongFeng::CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix) 
 {
	__ENTER_FUNCTION
		if (IsValid() ==false)
		{
			return;
		}
		tint32 nOldSpeed =SkillRefix.GetRefixValueByIndex(COMBATATTR_T::MOVESPEED);
		//加速
		SkillRefix.SetRefixValueByIndex(COMBATATTR_T::MOVESPEED,nOldSpeed+m_nNeedIncSpeed);
	__LEAVE_FUNCTION
 }
 void SL_ChongFeng::SkillFinish(Obj_Character& rSelf,bool bIsBreak)
 {
	 __ENTER_FUNCTION
		//调用基类的处理
		SkillBaseLogic::SkillFinish(rSelf,bIsBreak);
		//置脏重算
		rSelf.MarkSkillRefixCalcDirty();
	 __LEAVE_FUNCTION
 }