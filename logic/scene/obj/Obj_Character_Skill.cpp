#include "Obj_Character.h"
#include "scene/Skill/SL_AutoRepeat.h"
#include "scene/Skill/SL_GongSu.h"
#include "scene/Skill/SL_ShunFa.h"
#include "scene/Skill/SL_EffectToSelf.h"
#include "scene/skill/SL_ChongFeng.h"
#include "scene/Skill/SL_TeleMove.h"
#include "scene/skill/SL_ZhiXian.h"
#include "scene/skill/SL_Snare.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_SkillBase.h"
#include "Obj_March.h"
#include "Table/Table_SceneClass.h"
#include "../scene/Scene.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"

bool Obj_Character::IsHaveSkill(int nSkillId)
{
	__ENTER_FUNCTION
		if (nSkillId ==invalid_id)
		{
			return false;
		}
		for (int i = 0; i < MAXOWNSKILL; i++)
		{
			if (m_OwnSkillList[i] ==nSkillId)
			{
				return true;
			}
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Character::IsUsingSkill()
{
	__ENTER_FUNCTION
		if (m_CurSkillLogicPtr && m_CurSkillLogicPtr->IsValid())
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
int Obj_Character::GetSkillIndexById(int nSkillId)
{
	__ENTER_FUNCTION
		if (nSkillId ==invalid_id)
		{
			return -1;
		}
		for (int _nIndex = 0; _nIndex < MAXOWNSKILL; _nIndex++)
		{
			if (m_OwnSkillList[_nIndex] ==nSkillId)
			{
				return _nIndex;
			}
		}
		return -1;
	__LEAVE_FUNCTION
		return -1;
}

bool Obj_Character::SetOwnSkill(int nSkillId,int nSkillIndex)
{
	__ENTER_FUNCTION
		if (nSkillId ==invalid_id)
		{
			return false;
		}
		if (nSkillIndex <0 || nSkillIndex>=MAXOWNSKILL)
		{
			return false;
		}
		//是否在技能表中
		Table_SkillEx const* pSkillEx =GetTable_SkillExByID(nSkillId);
		if (pSkillEx ==null_ptr)
		{
			return false;
		}
		m_OwnSkillList[nSkillIndex] =nSkillId;
		return true;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Character::DeleteSkill(int nSkillIndex)
{
	__ENTER_FUNCTION
	
	if (nSkillIndex >= 0 && nSkillIndex < MAXOWNSKILL)
	{
		m_OwnSkillList[nSkillIndex] = invalid_id;
		return true;
	}
	return false;

	__LEAVE_FUNCTION
	return false;
}


void Obj_Character::Tick_Skill(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (IsUsingSkill()) //当前使用技能的心跳
		{
			AssertEx(m_CurSkillLogicPtr, "");
			m_CurSkillLogicPtr->Tick(*this,rTimeInfo);
		}
	__LEAVE_FUNCTION
}
//使用技能
bool Obj_Character::UseSkill(int nSkillId, int nTargetId)
{
	__ENTER_FUNCTION
		Table_SkillEx const* pSkillEx = GetTable_SkillExByID(nSkillId);
		if (pSkillEx == null_ptr)
		{
			return false;
		}
		int nBaseSkillId = pSkillEx->GetBaseId();
		Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(nBaseSkillId);
		if (pSkillBase == null_ptr)
		{
			return false;
		}
		SkillInfo_T tmpSkillInfo;
		tmpSkillInfo.m_nSkillId = nSkillId;
		tmpSkillInfo.m_nTargetId = nTargetId;
		tmpSkillInfo.m_pSkillEx = pSkillEx;
		tmpSkillInfo.m_pSkillBase = pSkillBase;
		tmpSkillInfo.m_nSkillDelayTime = pSkillEx->GetSkillDelayTime();
		tmpSkillInfo.m_nSkillRemainTime = pSkillEx->GetSkillContinueTime();
		bool bRet = UseSkill(tmpSkillInfo);
		return bRet;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Character::UseSkill(SkillInfo_T& skillInfo)
{
	__ENTER_FUNCTION
		//检测 技能信息是否有效
		if (false == skillInfo.IsValid())
		{
			return false;
		}
		bool bRet = CanActivateSkill(skillInfo);
		if (false == bRet)
		{
			return false;
		}

		ActivateSkill(skillInfo);
		return bRet;
	__LEAVE_FUNCTION
	return false;
}

//技能使用检测
bool Obj_Character::CanActivateSkill(SkillInfo_T& skillInfo) 
{
	__ENTER_FUNCTION
		//检测 技能信息是否有效
		if (false ==skillInfo.IsValid())
		{
			return false;
		}
		if (false ==IsSceneValid())
		{
			return false;
		}

		//各种检查
		//IsValid 已经做了判空操作
		const Table_SkillBase& rSkillBase =*skillInfo.m_pSkillBase;
		const Table_SkillEx& rSkillEx =*skillInfo.m_pSkillEx;

		if (false ==SelfCheck_Activate(rSkillBase,rSkillEx)|| 
			false ==SkillCheck(rSkillBase,rSkillEx) ||
			false ==TargetCheck_Activate(rSkillBase,rSkillEx,skillInfo.m_nTargetId)||
			false ==CooldownCheck(rSkillBase,rSkillEx))//||
			//false == TargetCheck_DominateTheWorld(rSkillBase,rSkillEx,skillInfo.m_nTargetId))
		{
			return false;
		}

		//检测消耗
		if (false ==CanDeplete(rSkillBase,rSkillEx))
		{
			return false;
		}

		return true;
	__LEAVE_FUNCTION
	return false;
}
//技能使用前操作
void Obj_Character::BeforActiveSkill(SkillInfo_T& skillInfo) 
{
	__ENTER_FUNCTION
		if (m_CurSkillLogicPtr )
		{
			m_CurSkillLogicPtr->OnBeforeActivate(*this);
		}
	__LEAVE_FUNCTION
}
//技能结束后的回调(包括被打断)
void  Obj_Character::OnSkillFinish()
{
	__ENTER_FUNCTION
		m_nLastUseSkillTime =0;
	__LEAVE_FUNCTION
}
void Obj_Character::ActivateSkill(SkillInfo_T& skillInfo)
{
	__ENTER_FUNCTION
		//检测 技能信息是否有效
		if (false ==skillInfo.IsValid())
		{
			return ;
		}
		if (false ==IsSceneValid())
		{
			return;
		}
		Scene& rScene =GetScene();

		//各种检查

		//IsValid 已经做了判空操作
		const Table_SkillBase& rSkillBase =*skillInfo.m_pSkillBase;
		const Table_SkillEx& rSkillEx =*skillInfo.m_pSkillEx;
		//正在使用技能 打断 前面已经做过了 是否能打断的判断
		if (IsUsingSkill())
		{
			AssertEx(m_CurSkillLogicPtr, "");
			m_CurSkillLogicPtr->BreakSkill(*this);
		}
		//开始激活技能
		m_CurSkillLogicPtr=CreateSkillInstanceById(rSkillEx.GetSkillLogic());
		if (m_CurSkillLogicPtr)
		{
			m_CurSkillLogicPtr->InitCurSkillInfo(skillInfo);
			BeforActiveSkill(skillInfo);
		
			//非连续技 加入公共CD 
			if (IsNpc() && (rSkillBase.GetSkillClass()&SKILLCLASS::AUTOREPEAT)==0)
			{
				if (false ==AddCoolDownToList(SKILLPUBLICCD))
				{
					return;
				}
			}
			//朝向攻击目标
			if (skillInfo.m_nTargetId!= invalid_id && skillInfo.m_nTargetId!=GetID())
			{
				FaceTo(skillInfo.m_nTargetId);
			}
			//停止移动
			/*if (IsMoving())
			{
				StopMove(true,true);
			}*/
			//记录下使用技能的时间
			m_nLastUseSkillTime = gTimeManager.RunTime();
			// 发包给客户端 可以走技能了
			RetUserSkillMsgPtr MsgPtr = POOLDEF_NEW(RetUserSkillMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_nSkillId = skillInfo.m_nSkillId;
			MsgPtr->m_nSenderId = GetID();
			MsgPtr->m_nTargetId = skillInfo.m_nTargetId;
			MsgPtr->m_nSceneId  = GetSceneInstID();
			//广播
			
			SendMessage2User(GetPlayerId(),MsgPtr);	

			Obj_CharacterPtr pTarget = GetScene().GetCharacterByID(skillInfo.m_nTargetId);
			if (pTarget != null_ptr)
			{
				RetUserSkillMsgPtr TMsgPtr = POOLDEF_NEW(RetUserSkillMsg);
				AssertEx(TMsgPtr,"");
				TMsgPtr->m_nSkillId = skillInfo.m_nSkillId;
				TMsgPtr->m_nSenderId = GetID();
				TMsgPtr->m_nTargetId = skillInfo.m_nTargetId;
				TMsgPtr->m_nSceneId  = GetSceneInstID();
				SendMessage2User(pTarget->GetPlayerId(),TMsgPtr);	
			}

			
			m_CurSkillLogicPtr->OnActivate(*this);
		}

	__LEAVE_FUNCTION
}

//冷却时间 检测
bool Obj_Character::CooldownCheck(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx) 
{
	__ENTER_FUNCTION
		// 玩家 验证公共CD
		if (IsMarch() && IsCoolDowning(SKILLPUBLICCD))
		{
			//Obj_March& rMarch = dynamic_cast<Obj_March&>(*this);
			//rMarch.SendNotice("#{1245}");
			return false;
		}
		
		if (IsCoolDowning((int16)rSkillEx.GetCDTimeId()))
		{
			//if (IsMarch())
			//{
			//	Obj_March& rMarch = dynamic_cast<Obj_March&>(*this);
			//	rMarch.SendNotice("#{1245}");
			//}
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;

}
//技能本身 检测
bool Obj_Character::SkillCheck(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx) 
{
	__ENTER_FUNCTION
		if (IsSceneValid() ==false)
		{
			return false;
		}
		Scene& rScene =GetScene();
		//是被动技能
		if ((rSkillBase.GetSkillClass()&SKILLCLASS::PASSIVITY)!=0)
		{
			return false;
		}

		//在使用技能
		if (IsUsingSkill())
		{
			AssertEx(m_CurSkillLogicPtr, "");
			int nCurSkillId =m_CurSkillLogicPtr->GetCurSkillInfo().m_nSkillId;
			Table_SkillEx const* pCurSkillEx =GetTable_SkillExByID(nCurSkillId);
			if (pCurSkillEx ==null_ptr)
			{
				return false;
			}
			Table_SkillBase const* pCurSkillBase =GetTable_SkillBaseByID(pCurSkillEx->GetBaseId());
			if (pCurSkillBase ==null_ptr)
			{
				return false;
			}
			//如果当前技能不能被别的技能打断则使用失败
			if (pCurSkillBase->GetIsSkillBreak() !=1 || m_CurSkillLogicPtr->IsEffect() ==false)
			{
				return false;
			}
			//上一个连续技正在使用 则不允许马上又用连续技
			if ((rSkillBase.GetSkillClass()&SKILLCLASS::AUTOREPEAT)!=0 && 
				(pCurSkillBase->GetSkillClass()&SKILLCLASS::AUTOREPEAT)!=0)
			{
				return false;
			}
		}
		//正在移动 想放出会被移动打断
		//是否拥有该技能
		if (IsHaveSkill(rSkillEx.GetSkillExID()) ==false)
		{
			return false;
		}
		//是否用禁用技能的BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				//!!!生效的BUFF才起作用
				if (ImpactLogicPtr->IsActive() && ImpactLogicPtr->IsEffect())
				{
					if(ImpactLogicPtr->IsSkillDisabled())
					{
						SendNotice("#{1249}");
						return false;
					}
				}
			}
		}
		return true;
	__LEAVE_FUNCTION
		return false;

}
//自身检测
bool Obj_Character::SelfCheck_Activate(Table_SkillBase const&  rSkillBase,Table_SkillEx const& rSkillEx) 
{
	__ENTER_FUNCTION
		if (false ==IsAlive() || false ==GetActive())
		{
			return false;
		}
		return true;
	__LEAVE_FUNCTION
		return false;

}

// 目标检测
bool Obj_Character::TargetCheck_Activate(Table_SkillBase const&  rSkillBase, Table_SkillEx const& rSkillEx, int nTargetId)
{
	__ENTER_FUNCTION
		if (false ==IsSceneValid())
		{
			return false;
		}
		Scene& rScene =GetScene();
		//单攻和普攻校验技能
		if (rSkillBase.GetSelLogic() == TAEGETSEL_T::SINGLE || 
		   (rSkillBase.GetSkillClass() & SKILLCLASS::AUTOREPEAT) != 0)
		{
			Obj_CharacterPtr targetPtr = rScene.GetCharacterByID(nTargetId);
			if (!targetPtr)
			{
				return false;
			}
			//目标隐身不可见
			if (targetPtr->CanBeScout(*this) ==false)
			{
				return false;
			}
			ESkillTarCheckRet bRet = Skill_IsWantedUnit(rSkillBase, rSkillEx, *targetPtr);
			//玩家 
			if (bRet != E_Skill_Tar_Effect && IsNpc())
			{
				Obj_Npc& rNpc = dynamic_cast<Obj_Npc&>(*this);
				
				if (E_Skill_Tar_Dis_Err == bRet)
				{
					RetUserSkillMsgPtr MsgPtr = POOLDEF_NEW(RetUserSkillMsg);
					AssertEx(MsgPtr,"");
					MsgPtr->m_nSkillId = rSkillEx.GetSkillExID();
					MsgPtr->m_nSenderId = GetID();
					MsgPtr->m_nTargetId = targetPtr->GetID();
					MsgPtr->m_nSkillFailType = SKILLFAILTYPE::DISTANCE;
					MsgPtr->m_nSceneId  = GetSceneInstID();
					SendMessage2User(rNpc.GetPlayerId(),MsgPtr);

				}
			}
			return (bRet==E_Skill_Tar_Effect);
		}
		
		return true;
	__LEAVE_FUNCTION
		return false;

}


//是否是技能所针对的目标
ESkillTarCheckRet Obj_Character::Skill_IsWantedUnit(Table_SkillBase const&  rSkillBase,Table_SkillEx const& rSkillEx,Obj_Character& rUnit) 
{
	__ENTER_FUNCTION
		
		if (false ==IsSceneValid())
		{
			return E_Skill_Tar_Invalid;
		}

		//todo 判断可见
		if (false == rUnit.GetActive() || false == rUnit.IsAlive())
		{
			return E_Skill_Tar_Invalid;
		}
		//目标类型检测
		int nTargetType = rSkillBase.GetTargetType();
		if (IsWantedTypeUnit(nTargetType, rUnit) == false)
		{
			return E_Skill_Tar_Type_Err;
		}
		//距离检测
		float fSkillRadius = rSkillEx.GetRadius();
		ScenePos selfPos = GetScenePos();
		ScenePos targetPos = rUnit.GetScenePos();
		float fDiffDis = selfPos.Distance(targetPos);
		if (fDiffDis - fSkillRadius >2) //!!这里做下容错 超过2的距离 再判断失败
		{
			return E_Skill_Tar_Dis_Err;
		}

		return E_Skill_Tar_Effect;
	__LEAVE_FUNCTION
		return E_Skill_Tar_Invalid;
}
void Obj_Character::BreakCurSkill()
{
	__ENTER_FUNCTION
		if (IsUsingSkill())
		{
			AssertEx(m_CurSkillLogicPtr, "");
			m_CurSkillLogicPtr->BreakSkill(*this);
		}
	__LEAVE_FUNCTION
}
int Obj_Character::GetOwnSkillByIndex(int nIndex) const
{
	__ENTER_FUNCTION
		if (nIndex >=0 && nIndex<MAXOWNSKILL)
		{
			return m_OwnSkillList[nIndex];
		}
		return invalid_id;
	__LEAVE_FUNCTION
		return invalid_id;
}
SkillBaseLogicPtr Obj_Character::CreateSkillInstanceById(int nLogicId)
{
	SkillBaseLogicPtr BaseLogic;
	switch (nLogicId)
	{
	case SkillBaseLogic::SL_SHUFA:
		{
			SL_ShunFaPtr Instance= POOLDEF_NEW(SL_ShunFa);
			AssertEx(Instance, "");
			BaseLogic =boost::static_pointer_cast<SkillBaseLogic,SL_ShunFa>(Instance);
		}
		break;
	case SkillBaseLogic::SL_CHONGFENG:
		{
			SL_ChongFengPtr Instance= POOLDEF_NEW(SL_ChongFeng);
			AssertEx(Instance, "");
			BaseLogic =boost::static_pointer_cast<SkillBaseLogic,SL_ChongFeng>(Instance);
		}
		break;
	case SkillBaseLogic::SL_ZHIXIAN:
		{
			SL_ZhiXianPtr Instance= POOLDEF_NEW(SL_ZhiXian);
			AssertEx(Instance, "");
			BaseLogic =boost::static_pointer_cast<SkillBaseLogic,SL_ZhiXian>(Instance);
		}
		break;
	case SkillBaseLogic::SL_EFFECTTOSELF:
		{
			SL_EffectToSelfPtr Instance= POOLDEF_NEW(SL_EffectToSelf);
			AssertEx(Instance, "");
			BaseLogic =boost::static_pointer_cast<SkillBaseLogic,SL_EffectToSelf>(Instance);
		}
		break;
	case SkillBaseLogic::SL_SNARE:
		{
			SL_SnarePtr Instance= POOLDEF_NEW(SL_Snare);
			AssertEx(Instance, "");
			BaseLogic =boost::static_pointer_cast<SkillBaseLogic,SL_Snare>(Instance);
		}
		break;
	case SkillBaseLogic::SL_TELEMOVE:
		{
			SL_TeleMovePtr Instance= POOLDEF_NEW(SL_TeleMove);
			AssertEx(Instance, "");
			BaseLogic =boost::static_pointer_cast<SkillBaseLogic,SL_TeleMove>(Instance);
		}
		break;
	default:
		break;
	}
	return BaseLogic;
}

bool Obj_Character::CanDeplete(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx)
{
	__ENTER_FUNCTION
		//检测是否 需要的消耗满足
		int nDelType = rSkillEx.GetDelType();
		int nDelValue =rSkillEx.GetDelNum();
	
		return IsDepleteEnough(nDelType,nDelValue);
		
	__LEAVE_FUNCTION
		return false;
}
void Obj_Character::SkillGain(Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx)
{
	__ENTER_FUNCTION
		/*int nDelCount =rSkillEx.getGainsNumCount();
		for (int i=0;i<nDelCount;i++)
		{
			int nGainType =rSkillEx.GetGainsTypebyIndex(i);
			int nGainValue =rSkillEx.GetGainsNumbyIndex(i);
			if (nGainType !=-1)
			{
				switch (nGainType)
				{
				case SKILLDELANDGAINTYPE::HPVALUE ://HP的数值
					{
						if (nGainValue>0)
						{
							IncreaseHp(nGainValue,*this);
						}
					}
					break;
				case SKILLDELANDGAINTYPE::HPPER ://HP的百分比
					{
						int nMaxHp =GetCombatAttrByID(COMBATATTR_T::MAXHP);
						int nNewHp =(int)(nMaxHp*nGainValue/100.0f);
						if (nNewHp >=0)
						{
							IncreaseHp(nNewHp,*this);
						}
					}
					break;
				case SKILLDELANDGAINTYPE::XPVALUE : //XP数值
					{
						if (nGainValue> 0)
						{
							IncreaseXp(nGainValue);
						}
					}
					break;
				case SKILLDELANDGAINTYPE::XPPER : //XP百分比
					{
						int nMaxXp =GetCombatAttrByID(COMBATATTR_T::MAXXP);
						int nNewXp =(int)(nMaxXp*nGainValue/100.0f);
						if (nNewXp >=0)
						{
							IncreaseXp(nNewXp);
						}
					}
					break;
				default:
					break;
				}
			}
	
		}*/
	

	__LEAVE_FUNCTION
		
}
bool Obj_Character::IsDepleteEnough(int nSKillDelType,int nSkillDelValue)
{
	__ENTER_FUNCTION
		bool isEnough = false;
		switch (nSKillDelType)
		{
		case SKILLDELANDGAINTYPE::HPVALUE ://HP的数值
			{
				int nNewHp =m_nCurHp - nSkillDelValue;
				if (nNewHp<= 0)
				{
					SendNotice("#{1247}");
				}
			}
			break;
		case SKILLDELANDGAINTYPE::HPPER ://HP的百分比
			{
				int nMaxHp =GetCombatAttrByID(COMBATATTR_T::TOTALMAXHP);
				int nNewHp =(int)(m_nCurHp -nMaxHp*nSkillDelValue/100.0f);
				if (nNewHp <=0)
				{
					SendNotice("#{1247}");
					return false;
				}
					
			}
			break;
	
		case SKILLDELANDGAINTYPE::XPVALUE : //XP数值
			{
				int nNewXp =m_nCurXp - nSkillDelValue;
				if (nNewXp< 0)
				{
					SendNotice("#{1244}");
					return false;
				}
			}
			break;
		case SKILLDELANDGAINTYPE::XPPER : //XP百分比
			{
				int nMaxXp =GetCombatAttrByID(COMBATATTR_T::MAXXP);
				int nNewXp =(int)(m_nCurXp -nMaxXp*nSkillDelValue/100.0f);
				if (nNewXp <0)
				{
					SendNotice("#{1244}");
					return false;
				}
			}
			break;
		default:
			return true;
			break;
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Character::SkillDeplete(int nSKillDelType,int nSkillDelValue,Table_SkillBase const& rSkillBase,Table_SkillEx const& rSkillEx)
{
	__ENTER_FUNCTION
		bool isCanDel = false;
		switch (nSKillDelType)
		{
		case SKILLDELANDGAINTYPE::HPVALUE://HP的数值
			{
				int nNewHp =m_nCurHp - nSkillDelValue;
				if (nNewHp>= 0)
				{
					IncreaseHp(-nSkillDelValue,*this);
					isCanDel = true;
				}

			}

			break;
		case SKILLDELANDGAINTYPE::HPPER://HP的百分比
			{
				int nMaxHp =GetCombatAttrByID(COMBATATTR_T::TOTALMAXHP);
				int nNeedHp =(int)(nMaxHp*nSkillDelValue/100.0f);
				int nNewHp =m_nCurHp-nNeedHp;
				if (nNewHp >=0)
				{
					IncreaseHp(-nNeedHp,*this);
					isCanDel = true;
				}
			}
			break;
		case SKILLDELANDGAINTYPE::XPVALUE: //XP数值
			{
				int nNewXp =m_nCurXp - nSkillDelValue;
				if (nNewXp>= 0)
				{
					IncreaseXp(-nSkillDelValue);
					isCanDel = true;
				}
			}
			break;
		case SKILLDELANDGAINTYPE::XPPER: //XP百分比
			{
				int nMaxXp =GetCombatAttrByID(COMBATATTR_T::MAXXP);
				int nNeedXP =(int)(nMaxXp*nSkillDelValue/100.0f);
				int nNewXp =m_nCurXp-nNeedXP;
				if (nNewXp >=0)
				{
					IncreaseXp(-nNeedXP);
					isCanDel = true;
				}
			}
			break;
			
		default:
			isCanDel = true;
			break;
		}
		return isCanDel;
	__LEAVE_FUNCTION
		return false;
}

void Obj_Character::SendPassiveSkillBuff(int nSkillId)
{
	__ENTER_FUNCTION
	
	if (nSkillId == invalid_id)
	{
		return;
	}

	Table_SkillEx const* pSkillEx = GetTable_SkillExByID(nSkillId);
	if (pSkillEx == null_ptr)
	{
		return;
	}

	Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
	if (pSkillBase == null_ptr)
	{
		return;
	}

	if ((pSkillBase->GetSkillClass() & SKILLCLASS::PASSIVITY) != 0)
	{
		for (int i=0; i < pSkillEx->getImpactCount(); i++)
		{
			int nImpackId = pSkillEx->GetImpactbyIndex(i);
			if (nImpackId != invalid_id)
			{
				SendImpactToUnit(*this, nImpackId, nSkillId);
			}
		}
	}

	__LEAVE_FUNCTION
}

void Obj_Character::ClearPassiveSkillBuff(int nSkillId)
{
	__ENTER_FUNCTION

	if (nSkillId == invalid_id)
	{
		return;
	}

	Table_SkillEx const* pSkillEx = GetTable_SkillExByID(nSkillId);
	if (pSkillEx == null_ptr)
	{
		return;
	}

	Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
	if (pSkillBase == null_ptr)
	{
		return;
	}

	if ((pSkillBase->GetSkillClass() & SKILLCLASS::PASSIVITY) != 0)
	{
		for (int i=0; i < pSkillEx->getImpactCount(); i++)
		{
			int nImpaclId = pSkillEx->GetImpactbyIndex(i);
			if (nImpaclId != invalid_id)
			{
				RemoveImpactById(nImpaclId);
			}
		}
	}

	__LEAVE_FUNCTION
}

bool Obj_Character::IsPassiveSkill(int nSkillId)
{
	__ENTER_FUNCTION
	
	if (nSkillId == invalid_id)
	{
		return false;
	}

	Table_SkillEx const* pSkillEx = GetTable_SkillExByID(nSkillId);
	if (pSkillEx == null_ptr)
	{
		return false;
	}

	Table_SkillBase const* pSkillBase = GetTable_SkillBaseByID(pSkillEx->GetBaseId());
	if (pSkillBase == null_ptr)
	{
		return false;
	}

	if ((pSkillBase->GetSkillClass() & SKILLCLASS::PASSIVITY) != 0)
	{
		return true;
	}
	return false;

	__LEAVE_FUNCTION
	return false;
}
