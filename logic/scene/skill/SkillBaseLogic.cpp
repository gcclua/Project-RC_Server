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
		m_bIsEffect =false;//未生效
		m_bIsActive =true;//已激活
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
		int nNextSkillId =skillEx.GetNextSkillId(); //下一招

		m_bIsActive =false;
		m_bIsEffect =false;
		
		m_CurSkillInfo.Cleanup();

		rSelf.OnSkillFinish();

		//发包给客户端
		if (false ==rSelf.IsSceneValid())
		{
			return;
		}
		Scene& rScene =rSelf.GetScene();
		
		
		//如果不是被中断&&当前的怪还没被打死 切换到连续技 

		SwitchNextSkill(rSelf,nNextSkillId);

	__LEAVE_FUNCTION
	
}
void SkillBaseLogic::SwitchNextSkill(Obj_Character& rSelf,int nNextSkillId)
{
	__ENTER_FUNCTION
		//已经死了
		if (false ==rSelf.IsAlive() || false==rSelf.GetActive())
		{
			return ;
		}
		//不是玩家

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
		//目标已经死了
		if (false ==SelObj->IsAlive()|| false ==SelObj->GetActive())
		{
			return;
		}

		int realSkillId = invalid_id;
		for (int tmpi = 0; tmpi < MAXOWNSKILL; ++tmpi)
		{ // 遍历玩家的所有技能,找到baseid相同的技能
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

		//使用技能
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
		//离开场景前 中断技能
		if (IsValid())
		{
			BreakSkill(rSelf);
		}
	__LEAVE_FUNCTION
}
//受到攻击的处理
void SkillBaseLogic::OnBeAttacked(Obj_Character& rSelf)
{
	__ENTER_FUNCTION
		if (IsValid() ==false)
		{
			return;
		}
		//如果受到攻击打断 则打断 (IsValid 已经做了判空处理)
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
		//死亡 终止技能
		if (false ==rSelf.IsAlive() || rSelf.GetActive() ==false)
		{
			BreakSkill(rSelf);
			return false;
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

		do 
		{
			if ( m_CurSkillInfo.m_pSkillBase == null_ptr )
				break;
			Table_SkillBase const& rSkillBase =*m_CurSkillInfo.m_pSkillBase;
			if ( rSkillBase.GetIsTargetDieBreak() != 1 )
				break; // 如果技能并不需要目标死亡中断的话,跳出
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
		//判断技能的有效性
		if (false ==IsValid() || false ==IsEffect())
		{
			return ;
		}
		if (OnBeforeEffect(rSelf))
		{
			StarEffect(rSelf);//对目标生效
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
//开始生效
void SkillBaseLogic::StarEffect(Obj_Character& rSelf)
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

		int nSelLogic =rSkillBase.GetSelLogic();
		switch (nSelLogic)
		{
		case TAEGETSEL_T::SINGLE: //单体 前面已经验证过了合法性
			{
				int nTargetId =m_CurSkillInfo.m_nTargetId;
				Obj_CharacterPtr TargetPtr =rScene.GetCharacterByID(nTargetId);
				if (TargetPtr)
				{
					OnEffectOnUnit(rSelf,*TargetPtr);
				}
			}
			break;
		case TAEGETSEL_T::SELF://自身
			{
				OnEffectOnUnit(rSelf,rSelf);
			}
			break;
		case TAEGETSEL_T::AROUNDSELF://群体
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
		//IsValid 已经做了判空操作
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
			//-1 表示无上限
			if (nSeleNum>=nMaxTargetNum && nMaxTargetNum!=-1)
			{
				break;
			}
			if (E_Skill_Tar_Effect !=rSelf.Skill_IsWantedUnit(rSkillBase,rSkillEx,objCharList[i]))//不是需要的目标
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
		//发送buff
		//IsValid 已经做了判空操作
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