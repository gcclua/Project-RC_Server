#include "Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Message/SceneMsg.h"

void Obj_Character::SetForceType(int nType) 
{
	m_ForceType =nType;
	m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::FORCETYPE,true);
}

void Obj_Character::SetStealthLev(int val)
{
	__ENTER_FUNCTION
		Obj_Action::SetStealthLev(val);
		m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::STEALTHLEV,true);
	__LEAVE_FUNCTION
}
void Obj_Character::SetCurHp(int nCurHp)
{
	__ENTER_FUNCTION
		if (nCurHp<0)
		{
			nCurHp =0;
		}
		int nMaxHp =GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXHP));
		if (nCurHp >=nMaxHp)
		{
			nCurHp =nMaxHp;
		}
		if (m_nCurHp !=nCurHp)
		{
			m_AttrSyncDirtyFlag.SetBit(BaseAttrSyncDirty_T::CURHP, true);
		}
		m_nCurHp =nCurHp;
	__LEAVE_FUNCTION
}

void Obj_Character::SetMaxHp(int nMaxHp)
{
	__ENTER_FUNCTION
		if ( nMaxHp <= 0)
		{
			return ;
		}

		m_FinalyAttr.SetCombatAttrByIndex((int)COMBATATTR_T::MAXHP, nMaxHp);

	__LEAVE_FUNCTION
}

int Obj_Character::IncreaseHp( int nHP, Obj_Character& rSourceObj)
{
	__ENTER_FUNCTION
		
		int nCurHp = GetCurHp();
		int nOldCurHpBak = nCurHp;
		
		if (rSourceObj.IsDie())
		{
			return 0;
		}

		int nNewHp = nCurHp + nHP;

		SetCurHp(nNewHp);

		nCurHp = GetCurHp();
		if (nCurHp <= 0 && IsDie() == false) 
		{
			OnDie(rSourceObj);
		}

		return nCurHp;
	__LEAVE_FUNCTION
		return 0;

}

void  Obj_Character::SetCurXp(int nCurXp)
{
	__ENTER_FUNCTION
		//没达到XP 学习的等级 不增加XP能量
		if (m_nLevel <MINXPSKILLSTUDYLEV)
		{
			return;
		}
		if (nCurXp <0)
		{
			nCurXp =0;
		}
		int nMaxXp =GetCombatAttrByID(static_cast<int>(COMBATATTR_T::MAXXP));
		if (nCurXp >=nMaxXp)
		{
			nCurXp =nMaxXp;
		}
		if (m_nCurXp !=nCurXp)
		{
			m_AttrSyncDirtyFlag.SetBit(BaseAttrSyncDirty_T::CURXP, true);
		}
		m_nCurXp =nCurXp;
	__LEAVE_FUNCTION
		

}

void Obj_Character::SetName(const CHARNAME& NewName)
{
	__ENTER_FUNCTION
		m_Name =NewName;
		m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::NAME,true);
	__LEAVE_FUNCTION
}

void Obj_Character::SetName(const char* strName)
{
	__ENTER_FUNCTION

	if (strName != null_ptr)
	{
		m_Name = strName;
		m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::NAME,true);
	}

	__LEAVE_FUNCTION
}

int Obj_Character::IncreaseXp( int nXp)
{
	__ENTER_FUNCTION
		//没达到XP 学习的等级 不增加XP能量
		if (m_nLevel <MINXPSKILLSTUDYLEV)
		{
			return 0;
		}
		int nCurXp = GetCurXP();
		if(nXp == 0)
		{
			return nCurXp;
		}

		int nNewXp = nCurXp + nXp;

		SetCurXp(nNewXp);

		nCurXp = GetCurXP();
		return nCurXp;
	__LEAVE_FUNCTION
		return 0;

}

void  Obj_Character::SetLevel(int nCurLev)
{
	__ENTER_FUNCTION
		if (nCurLev <1)
		{
			nCurLev =1;
		}

		m_nLevel =nCurLev;

		m_AttrSyncDirtyFlag.SetBit(BaseAttrSyncDirty_T::LEVEL, true);
		
	__LEAVE_FUNCTION
}

void Obj_Character::CalculateSkillRefix(void)
{
	__ENTER_FUNCTION
		//!!!重新计算前 先清零
		m_SkillCombatRefix.CleanUp();
		if (IsUsingSkill())
		{
			AssertEx(m_CurSkillLogicPtr, "");
			m_CurSkillLogicPtr->CombatAttrRefix(*this,m_SkillCombatRefix);
		}
	__LEAVE_FUNCTION
}
void Obj_Character::CalculateBuffRefix()
{
	// 计算buff加成影响
	__ENTER_FUNCTION
		//!!!重新计算前 先清零
		m_BuffCombatRefix.CleanUp();
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				
				//!!!生效的BUFF才起作用
				if (ImpactLogicPtr->IsActive() && ImpactLogicPtr->IsEffect())
				{
					ImpactLogicPtr->CombatAttrRefix(*this,m_BuffCombatRefix);
				}
			}
		}
	__LEAVE_FUNCTION
}
void Obj_Character::MarkCombatAttrCalcDirty(void)
{
	__ENTER_FUNCTION
		//所有战斗属性相关置脏 重算
		MarkInitalAttrCalcDirty();
		MarkBuffRefixCalcDirty();
		MarkSkillRefixCalcDirty();
		MarkLevelRefixCalcDirty();
	__LEAVE_FUNCTION
}

tint32 Obj_Character::GetRelationByForceType(Obj_Character& rUnit) 
{
	__ENTER_FUNCTION
		if (GetForceType() == rUnit.GetForceType())
		{
			return RELATIONTYPE_T::FRIEND;
		}
		return RELATIONTYPE_T::ENEMY;
	__LEAVE_FUNCTION
		return RELATIONTYPE_T::INVAILD_TYPE;
}

bool Obj_Character::IsWantedTypeUnit(int nWantedType,Obj_Character& rTargetUnit)
{
	__ENTER_FUNCTION
		if (false ==IsSceneValid())
		{
			return false;
		}
		if (false ==rTargetUnit.GetActive() ||false ==rTargetUnit.IsAlive())
		{
			return false;
		}
		//目标类型检测
		bool isWantType =false;
		//自己
		if (nWantedType & TAEGETTYPE_T::SELF)
		{
			if (GetID() ==rTargetUnit.GetID())
			{
				isWantType =true;
			}
		}

		//敌人
		if (nWantedType & TAEGETTYPE_T::ENEMY)
		{
			if (GetRelationByForceType(rTargetUnit) ==RELATIONTYPE_T::ENEMY ||
				GetRelationByForceType(rTargetUnit) ==RELATIONTYPE_T::NEUTRAL)
			{
				isWantType =true;
			}
		}
		//友方
		if (nWantedType & TAEGETTYPE_T::FRIND)
		{
			if (GetRelationByForceType(rTargetUnit) ==RELATIONTYPE_T::FRIEND)
			{
				isWantType =true;
			}
		}

		if (true ==isWantType)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
void Obj_Character::Tick_CalculateCombatAttr()
{
	__ENTER_FUNCTION
		CalculateFinalyAttr();
	__LEAVE_FUNCTION
}

void Obj_Character::BroadCastAnimState(int AnimState,
									   int verOff/*=-1*/,
									   int horOff/*=-1*/,
									   int lastTime/*=-1*/,
									   int resortTime/*=-1*/,
									   int hitTimes/* =-1 */,
									   int hitInterval/* =-1 */)
{
	__ENTER_FUNCTION
		//广播动作变化
		if (false ==IsSceneValid())
		{
			return;
		}
		Scene& rScene =GetScene();
		//受击状态的广播 加一个0.5s的广播冷却
		if( AnimState ==(int)ANIMATIONSTATE_T::STATE_HIT ||
			AnimState ==(int)ANIMATIONSTATE_T::STATE_HITBYFEIYUN||
			AnimState ==(int)ANIMATIONSTATE_T::STATE_HITBYSHENFENG||
			AnimState ==(int)ANIMATIONSTATE_T::STATE_HITBYDUANQING||
			AnimState ==(int)ANIMATIONSTATE_T::STATE_HITBYMENGWU)
		{
			int nDiffTime =(int)(gTimeManager.RunTime()-m_nLastBroadcastHitTime);
			if (nDiffTime <500)
			{
				return;
			}
			m_nLastBroadcastHitTime =gTimeManager.RunTime();
		}

		Update_Animation_StatePtr MsgPtr = POOLDEF_NEW(Update_Animation_State);
		MsgPtr->m_nObjId = GetID();
		MsgPtr->m_nAnimationState = AnimState;
		MsgPtr->m_nVerticalOffDis = verOff;
		MsgPtr->m_nHorizontalOffDis = horOff;
		MsgPtr->m_nStateLastTime = lastTime;
		MsgPtr->m_nStateResortTime = resortTime;
		MsgPtr->m_nHitTimes        = hitTimes;
		MsgPtr->m_nHitInterval     = hitInterval;
		MsgPtr->m_nSceneId         = GetSceneInstID();

		rScene.BroadCast_InSight_Include(MsgPtr,GetID());
		
	__LEAVE_FUNCTION
}



