#include "SkillBaseLogic.h"
#include "Scene/Obj/Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"


POOLDEF_IMPL(SkillBaseLogic);
bool SkillBaseLogic::IsValid()
{
	__ENTER_FUNCTION
		if (false ==m_CurSkillInfo.IsValid() || false==m_bIsActive)
		{
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}
SkillBaseLogic::SkillBaseLogic()
{
	m_bIsActive =false;
	m_bIsEffect =false;
};


void SkillBaseLogic::OnActivate(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		m_bIsEffect =false;//δ��Ч
		m_bIsActive =true;//�Ѽ���
	__LEAVE_FUNCTION
}
void SkillBaseLogic::SkillFinish(Obj_Character& rSelf,bool bIsBreak)
{
	__ENTER_FUNCTION
		if (IsValid() ==false)
		{
			return ;
		}
		Table_SkillEx const& skillEx =*m_CurSkillInfo.m_pSkillEx;
		int nNextSkillId =skillEx.GetNextSkillId(); //��һ��

		m_bIsActive =false;
		m_bIsEffect =false;
		
		m_CurSkillInfo.Cleanup();

		rSelf.OnSkillFinish();

		//�������ͻ���
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		
		
		//������Ǳ��ж�&&��ǰ�Ĺֻ�û������ �л��������� 

		SwitchNextSkill(rSelf,nNextSkillId);

	__LEAVE_FUNCTION
	
}
void SkillBaseLogic::SwitchNextSkill(Obj_Character& rSelf,int nNextSkillId)
{
	__ENTER_FUNCTION
		//�Ѿ�����
		if (false ==rSelf.IsAlive() || false==rSelf.GetActive())
		{
			return ;
		}
		//�������

		if (false==rSelf.IsSceneValid())
		{
			return ;
		}
		Scene& rScene =rSelf.GetScene();
		Obj_CharacterPtr SelObj =rScene.GetCharacterByID(rSelf.GetCurSelectObjId());
		if (!SelObj)
		{
			return ;
		}
		//Ŀ���Ѿ�����
		if (false ==SelObj->IsAlive()|| false ==SelObj->GetActive())
		{
			return;
		}

		int realSkillId = invalid_id;
		for (int tmpi = 0; tmpi < MAXOWNSKILL; ++tmpi)
		{ // ������ҵ����м���,�ҵ�baseid��ͬ�ļ���
			int tmp_skillid = rSelf.GetOwnSkillByIndex(tmpi);
			Table_SkillEx const * pSkillEx = GetTable_SkillExByID(tmp_skillid);
			if ( pSkillEx == null_ptr )
				continue;
			if ( pSkillEx->GetBaseId() == nNextSkillId )
			{
				realSkillId = tmp_skillid;
				break;
			}
		}

		//ʹ�ü���
		SkillInfo_T tmpSkillInfo;
		tmpSkillInfo.m_nSkillId =realSkillId;// nNextSkillId;
		tmpSkillInfo.m_nTargetId =rSelf.GetCurSelectObjId();
		Table_SkillEx const* pSkillEx =GetTable_SkillExByID(realSkillId); //nNextSkillId
		if (pSkillEx ==null_ptr)
		{
			return ;
		}
		int nBaseSkillId =pSkillEx->GetBaseId();
		Table_SkillBase const* pSkillBase =GetTable_SkillBaseByID(nBaseSkillId);	
		if (pSkillBase ==null_ptr)
		{
			return;
		}
		tmpSkillInfo.m_pSkillEx =pSkillEx;
		tmpSkillInfo.m_pSkillBase =pSkillBase;
		tmpSkillInfo.m_nSkillDelayTime =pSkillEx->GetSkillDelayTime();
		tmpSkillInfo.m_nSkillRemainTime =pSkillEx->GetSkillContinueTime();
		rSelf.UseSkill(tmpSkillInfo);
	__LEAVE_FUNCTION

}
void SkillBaseLogic::BreakSkill(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (IsValid())
		{
			SkillFinish(rSelf,true);
		}
	__LEAVE_FUNCTION
}
void SkillBaseLogic::BeforLevelScene(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		//�뿪����ǰ �жϼ���
		if (IsValid())
		{
			BreakSkill(rSelf);
		}
	__LEAVE_FUNCTION
}
//�ܵ������Ĵ���
void SkillBaseLogic::OnBeAttacked(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (IsValid() ==false)
		{
			return;
		}
		//����ܵ�������� ���� (IsValid �Ѿ������пմ���)
		if (m_CurSkillInfo.m_pSkillBase->GetIsBreakBeAttacked() ==1)
		{
			BreakSkill(rSelf);
		}
	__LEAVE_FUNCTION
}
bool SkillBaseLogic::Tick(Obj_Character& rSelf,const TimeInfo& rTimeInfo)
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

		do 
		{
			if ( m_CurSkillInfo.m_pSkillBase == null_ptr )
				break;
			Table_SkillBase const& rSkillBase =*m_CurSkillInfo.m_pSkillBase;
			if ( rSkillBase.GetIsTargetDieBreak() != 1 )
				break; // ������ܲ�����ҪĿ�������жϵĻ�,����
			if ( rSelf.IsSceneValid() == false )
				break;
			Scene & rScene = rSelf.GetScene();
			Obj_CharacterPtr SelObjPtr = rScene.GetCharacterByID(rSelf.GetCurSelectObjId());
			if ( !SelObjPtr )
				break;
			if ( SelObjPtr->GetActive() == false || SelObjPtr->IsAlive() == false )
			{
				BreakSkill(rSelf);
				return false;
			}
		} while (0);
		return true; 
	__LEAVE_FUNCTION
		return false;
}

void SkillBaseLogic::OnTakeEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		//�жϼ��ܵ���Ч��
		if (false ==IsValid() || false ==IsEffect())
		{
			return ;
		}
		if (OnBeforeEffect(rSelf))
		{
			StarEffect(rSelf);//��Ŀ����Ч
		}
	__LEAVE_FUNCTION
}
bool SkillBaseLogic::OnBeforeEffect(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (false ==IsValid() || false ==IsEffect())
		{
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}
//��ʼ��Ч
void SkillBaseLogic::StarEffect(Obj_Character& rSelf)
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
		Table_SkillBase const& rSkillBase =*m_CurSkillInfo.m_pSkillBase; 

		int nSelLogic =rSkillBase.GetSelLogic();
		switch (nSelLogic)
		{
		case TAEGETSEL_T::SINGLE: //���� ǰ���Ѿ���֤���˺Ϸ���
			{
				int nTargetId =m_CurSkillInfo.m_nTargetId;
				Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(nTargetId);
				if (TargetPtr)
				{
					OnEffectOnUnit(rSelf,*TargetPtr);
				}
			}
			break;
		case TAEGETSEL_T::SELF://����
			{
				OnEffectOnUnit(rSelf,rSelf);
			}
			break;
		case TAEGETSEL_T::AROUNDSELF://Ⱥ��
			ScanEffectTargetList(rSelf);
			break;
		default:
			break;
		}
	__LEAVE_FUNCTION
}
void SkillBaseLogic::ScanEffectTargetList(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (false ==rSelf.IsSceneValid() || false ==IsValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		//IsValid �Ѿ������пղ���
		Table_SkillBase const& rSkillBase=*m_CurSkillInfo.m_pSkillBase;
		Table_SkillEx const& rSkillEx=*m_CurSkillInfo.m_pSkillEx;
		ScenePos selfPos =rSelf.GetScenePos();
		float fScanDis =rSkillEx.GetRadius();
		CharacterRefCont objCharList;
		rScene.Scan_Character_Circle(objCharList,selfPos,fScanDis);
		int nMaxTargetNum =GetMaxTargetNum();
		int nSeleNum =0;
		for (int i = 0; i < objCharList.Size(); i++)
		{
			//-1 ��ʾ������
			if (nSeleNum>=nMaxTargetNum && nMaxTargetNum!=-1)
			{
				break;
			}
			if (E_Skill_Tar_Effect !=rSelf.Skill_IsWantedUnit(rSkillBase,rSkillEx,objCharList[i]))//������Ҫ��Ŀ��
			{
				continue;
			}
			OnEffectOnUnit(rSelf,objCharList[i]);
			nSeleNum++;
		}
		__LEAVE_FUNCTION
}

void SkillBaseLogic::OnEffectOnUnit(Obj_Character& rSelf, Obj_Character& rUnit)
{
	__ENTER_FUNCTION
		if (false ==IsValid() || false==m_bIsEffect)
		{
			return;
		}
		//����buff
		//IsValid �Ѿ������пղ���
		Table_SkillBase const& rSkillBase =*m_CurSkillInfo.m_pSkillBase;
		Table_SkillEx const& rSkillEx =*m_CurSkillInfo.m_pSkillEx;
		int nImpactCout =rSkillEx.getImpactCount();
		for (int i=0;i<nImpactCout;i++)
		{
			int nImpactId =rSkillEx.GetImpactbyIndex(i);
			if (nImpactId !=invalid_id)
			{
				rSelf.SendImpactToUnit(rUnit,nImpactId,m_CurSkillInfo.m_nSkillId);
			}
		}
	__LEAVE_FUNCTION
}