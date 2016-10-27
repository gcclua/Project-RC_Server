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
		//�жϼ��ܵ���Ч��
		if (false ==IsValid() || false ==IsEffect())
		{
			return ;
		}
		if (false ==rSelf.IsSceneValid())
		{
			return ;
		}
		Scene& rScene =rSelf.GetScene();
		//IsValid �Ѿ������пղ���
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		tint32 nSnareId =rSkillEx.GetLogicParambyIndex(SNAREID);
		tint32 nPosSelType =rSkillEx.GetLogicParambyIndex(SNAREPOSTYPE);
		ScenePos SnarePos;
		if (nPosSelType ==POS_SELF)
		{
			SnarePos=rSelf.GetScenePos();
			//�ڽ��� ��һ��
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
				//��Ŀ����� ��һ��
				Obj_SnarePtr _snarePtr =rScene.CreateSnareObj(nSnareId,rSelf.GetID(),SnarePos);
				if (_snarePtr !=null_ptr)
				{
					m_SnareObjId =_snarePtr->GetID();
				}
			}
		}
	__LEAVE_FUNCTION
}
//���ܽ�������
void SL_Snare::SkillFinish(Obj_Character& rSelf,bool bIsBreak)
{
	__ENTER_FUNCTION
		//���ܽ���ʱ �Ƿ���Ҫɾ������
		if (IsValid())
		{
			if (rSelf.IsSceneValid())
			{
				//IsValid �Ѿ������пղ���
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
		//���û���Ĵ���
		SkillBaseLogic::SkillFinish(rSelf,bIsBreak);
	__LEAVE_FUNCTION
}