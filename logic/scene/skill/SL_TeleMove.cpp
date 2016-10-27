#include "SL_TeleMove.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"

POOLDEF_IMPL(SL_TeleMove);
SL_TeleMove::SL_TeleMove ()
{
	m_nNeedIncSpeed =0;
}
void SL_TeleMove::OnActivate(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		SkillBaseLogic::OnActivate(rSelf);
		
	__LEAVE_FUNCTION
}
//开始生效
void SL_TeleMove::StarEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		//先生效
		SkillBaseLogic::StarEffect(rSelf);
		

		//再后退
		if (IsValid() ==false)
		{
			return;
		}
		//以退为进特殊处理 给自己加一个防御BUFF
		//IsValid()  已经做过判空处理
		if(m_CurSkillInfo.m_pSkillBase->GetId() ==YTWJBASEID)
		{
			//写死第3个BUFF为加防御的BUFF
			int nFYBuffId =m_CurSkillInfo.m_pSkillEx->GetImpactbyIndex(2);
			if (nFYBuffId!=invalid_id)
			{
				rSelf.SendImpactToUnit(rSelf,nFYBuffId,m_CurSkillInfo.m_pSkillEx->GetSkillExID());
			}
		}
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		ScenePos selfPos=rSelf.GetScenePos();
		float fDis =(float)(rSkillEx.GetLogicParambyIndex(DISTANCE));
		int nTime =rSkillEx.GetLogicParambyIndex(TIME);
		int nAngle =rSkillEx.GetLogicParambyIndex(ANGLE);
		//移动到目标点
		ScenePos TargetPos;
		float fRad =rSelf.GetFaceDir()+nAngle/180.0f*_PI;
		TargetPos.m_fX =rSelf.GetScenePos().m_fX+cos(fRad)*fDis;
		TargetPos.m_fZ =rSelf.GetScenePos().m_fZ+sin(fRad)*fDis;
		ScenePos OldSelfPos =rSelf.GetScenePos();
		rSelf.TeleMoveTo(TargetPos);
		//修正真正的位移偏移
		fDis =OldSelfPos.Distance(rSelf.GetScenePos());
		//计算速度修正
		float fNeedSpeed =fDis*1.0f/nTime*1000*100;
		m_nNeedIncSpeed =(int)(fNeedSpeed-rSelf.GetMoveSpeed()*100);
		if (m_nNeedIncSpeed <0)
		{
			m_nNeedIncSpeed =0;
		}
		//置脏重算
		rSelf.MarkSkillRefixCalcDirty();
		//立即更新最新数据
		rSelf.CalculateFinalyAttr();
		//通知客户端移动到最新的位置
		rSelf.UpdateTeleMoveToClient(rSelf.GetScenePos(),false);
	__LEAVE_FUNCTION
}
//获取技能目标上限
int  SL_TeleMove::GetMaxTargetNum(void)//-1 表示无上限需求
{
	__ENTER_FUNCTION
		if (false ==IsValid())
		{
			return -1;
		}
		Table_SkillEx const& rSkillEx=*m_CurSkillInfo.m_pSkillEx;
		int nMaxTargetNum =rSkillEx.GetLogicParambyIndex(MAXTARGETNUM);
		return nMaxTargetNum;
	__LEAVE_FUNCTION
		return -1;
}

void SL_TeleMove::CombatAttrRefix(Obj_Character& rSelf,CombatAttr_Refix& SkillRefix) 
{
	__ENTER_FUNCTION
		if (IsValid() ==false)
		{
			return;
		}
		int nOldSpeed =SkillRefix.GetRefixValueByIndex(COMBATATTR_T::MOVESPEED);
		//加速
		SkillRefix.SetRefixValueByIndex(COMBATATTR_T::MOVESPEED,nOldSpeed+m_nNeedIncSpeed);
		__LEAVE_FUNCTION
}
void SL_TeleMove::SkillFinish(Obj_Character& rSelf,bool bIsBreak)
{
	__ENTER_FUNCTION
		//调用基类的处理
		SkillBaseLogic::SkillFinish(rSelf,bIsBreak);
		//置脏重算
		rSelf.MarkSkillRefixCalcDirty();
	__LEAVE_FUNCTION
}