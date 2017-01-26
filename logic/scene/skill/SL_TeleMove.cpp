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
//��ʼ��Ч
void SL_TeleMove::StarEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		//����Ч
		SkillBaseLogic::StarEffect(rSelf);
		

		//�ٺ���
		if (IsValid() ==false)
		{
			return;
		}
		//����Ϊ�����⴦�� ���Լ���һ������BUFF
		//IsValid()  �Ѿ������пմ���
		if(m_CurSkillInfo.m_pSkillBase->GetId() ==YTWJBASEID)
		{
			//д����3��BUFFΪ�ӷ�����BUFF
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
		//�ƶ���Ŀ���
		ScenePos TargetPos;
		float fRad =rSelf.GetFaceDir()+nAngle/180.0f*_PI;
		TargetPos.m_fX =rSelf.GetScenePos().m_fX+cos(fRad)*fDis;
		TargetPos.m_fZ =rSelf.GetScenePos().m_fZ+sin(fRad)*fDis;
		ScenePos OldSelfPos =rSelf.GetScenePos();
		rSelf.TeleMoveTo(TargetPos);
		//����������λ��ƫ��
		fDis =OldSelfPos.Distance(rSelf.GetScenePos());
		//�����ٶ�����
		float fNeedSpeed =fDis*1.0f/nTime*1000*100;
		m_nNeedIncSpeed =(int)(fNeedSpeed-rSelf.GetMoveSpeed()*100);
		if (m_nNeedIncSpeed <0)
		{
			m_nNeedIncSpeed =0;
		}
		//��������
		rSelf.MarkSkillRefixCalcDirty();
		//����������������
		rSelf.CalculateFinalyAttr();
		//֪ͨ�ͻ����ƶ������µ�λ��
		rSelf.UpdateTeleMoveToClient(rSelf.GetScenePos(),false);
	__LEAVE_FUNCTION
}
//��ȡ����Ŀ������
int  SL_TeleMove::GetMaxTargetNum(void)//-1 ��ʾ����������
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
		//����
		SkillRefix.SetRefixValueByIndex(COMBATATTR_T::MOVESPEED,nOldSpeed+m_nNeedIncSpeed);
		__LEAVE_FUNCTION
}
void SL_TeleMove::SkillFinish(Obj_Character& rSelf,bool bIsBreak)
{
	__ENTER_FUNCTION
		//���û���Ĵ���
		SkillBaseLogic::SkillFinish(rSelf,bIsBreak);
		//��������
		rSelf.MarkSkillRefixCalcDirty();
	__LEAVE_FUNCTION
}