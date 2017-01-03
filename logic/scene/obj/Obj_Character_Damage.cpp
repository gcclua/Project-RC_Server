#include "Obj_Character.h"
#include "Scene/Impact/ImpactBaseLogic.h"
#include "Table/Table_Impact.h"
#include "Table/Table_SkillEx.h"
#include "Table/Table_SkillBase.h"
#include "../scene/Scene.h"
#include "Config.h"

void Obj_Character::OnReceiveDamage(DamagesInof_T & rDamage)
{
	__ENTER_FUNCTION
		if (false ==IsSceneValid())
		{
			return;
		}
		Scene& rScene =GetScene();
		Obj_CharacterPtr SenderPtr =rScene.GetCharacterByID(rDamage.GetSenderID());
		if (!SenderPtr)
		{
			return;
		}
		

		//伤害扣血处理
		OnTypeDamage(rDamage);
		//受击状态处理 掉血了才生效 已经死亡了 就不做受击状态处理了 直接走死亡
		if (IsDie() ==false && rDamage.IsHit() && rDamage.GetTotalDamage() >0)
		{
			{
				if ( rDamage.GetClientShowTimes() <= 1 )
				{
					BroadCastAnimState((int)ANIMATIONSTATE_T::STATE_HIT);
				}
				else
				{
					BroadCastAnimState((int)ANIMATIONSTATE_T::STATE_HIT,
						-1,
						-1,
						-1,
						-1,
						rDamage.GetClientShowTimes(),
						rDamage.GetClientShowInterval() );
				}
			}
		}
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				if (_ImpactLogicPtr->IsFadeoutWhenReceiveDamage() ||
					_ImpactLogicPtr->IsFadeoutWhenReceiveAttack())
				{
					_ImpactLogicPtr->OnFadeOut(*this);//受伤害或者攻击可以解除的BUFF(伙伴发出的无效) 
				}
				_ImpactLogicPtr->OnReceiveDamage(*this,rDamage);//受到伤害时做的处理
			}
		}
		//技能受到攻击的处理
		if (IsUsingSkill())
		{
			if (m_CurSkillLogicPtr)
			{
				m_CurSkillLogicPtr->OnBeAttacked(*this);
			}
		}
		//仇恨处理 增加的仇恨值=(对怪物的伤害*职业仇恨系数)+技能固有仇恨
		if (CanAcceptThreat())
		{
			//职业仇恨系数
			float fProfessionThreatRefix =1.0f;
			//技能仇恨修正值
			int nSkillThreatRefix =0;
			if (rDamage.GetSkillID() !=invalid_id)
			{
				Table_SkillEx const* pSkillEx =GetTable_SkillExByID(rDamage.GetSkillID());
				if (pSkillEx !=null_ptr)
				{
					nSkillThreatRefix =pSkillEx->GetRefixThreat();
				}
			}
			int nIncThreatNum =(int)(rDamage.GetNotypeDamage()*fProfessionThreatRefix+nSkillThreatRefix);
			OnThreat(*SenderPtr,nIncThreatNum);
		}
	__LEAVE_FUNCTION
}

//类型伤害处理
void Obj_Character::OnTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		RefixTypeDamage(rDamage);//伤害修正
		IgnoreTypeDamage(rDamage);//伤害免疫
		AbsorbAndReflexTypeDamage(rDamage);//伤害吸收和反射
		//转换成无类型伤害
		rDamage.TotalDamageToNotypeDamage();
		//无类型伤害处理
		OnNoTypeDamage(rDamage);
	__LEAVE_FUNCTION
}
//处理完类型伤害后  汇总成无类型伤害处理 最终的掉血
void Obj_Character::OnNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		//修改血量改变
		if (false == IsSceneValid())
		{
			return;
		}
		Scene& rScene = GetScene();
		Obj_CharacterPtr senderPtr = rScene.GetCharacterByID(rDamage.GetSenderID());
		if (!senderPtr)
		{
			return;
		}
		int nAddAnimState =-1;//附加的状态
		
		RefixNoTypeDamage(rDamage); //伤害修正
		IgnoreNoTypeDamage(rDamage);//伤害免疫
		AbsorbAndReflexNoTypeDamage(rDamage);//伤害吸收和反射
		int  nIncHp=0-rDamage.GetNotypeDamage()-rDamage.GetDecHp();
		//最后走到 扣血
		int nOldHp =GetCurHp();
		//IncreaseHp(nIncHp,*SenderPtr);
		//mwh-注意IncreaseHp返回的新的血量，因为世界BOSS的，要做特殊处理
		int nNewHp = IncreaseHp(nIncHp,*senderPtr);//GetCurHp();
		
	__LEAVE_FUNCTION
}

//类型伤害修正
void Obj_Character::RefixTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF伤害修正
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->OnTypeDamage(*this,RefixDamageInfo,rDamage);
			}
		}
		int nNewPhyDamage =_MAX(rDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS)+RefixDamageInfo.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS),0);
		rDamage.SetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS,nNewPhyDamage);
	__LEAVE_FUNCTION
}
//无类型伤害修正
void Obj_Character::RefixNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		float fMultiNoTypeDecPer =1.0f;//buff累乘伤害减免的百分比
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF伤害修正
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->OnNoTypeDamage(*this,RefixDamageInfo,rDamage);
				if (_ImpactLogicPtr->IsDecNoTypedDamagebyMulti())
				{
					float fTmpPer =_ImpactLogicPtr->GetDecNoTypedDamagebyMulti();
					if (fTmpPer>0)
					{
						fMultiNoTypeDecPer=fMultiNoTypeDecPer*(1-fTmpPer);
					}
				}
			}
		}

		fMultiNoTypeDecPer =_MIN(fMultiNoTypeDecPer,1);
		int nRefixNoTypeDamge =rDamage.GetNotypeDamage()+RefixDamageInfo.GetNotypeDamage()-(int)(rDamage.GetNotypeDamage()*(1-fMultiNoTypeDecPer));
		int nNewNoTypeDamage =_MAX(nRefixNoTypeDamge,0);
		rDamage.SetNotypeDamage(nNewNoTypeDamage);
	__LEAVE_FUNCTION
}
// 修正发送伤害的全部伤害
void Obj_Character::RefixSendAllDamage(Obj_Character& rTarget, DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION;
	DamagesInof_T RefixDamageInfo;
	ImpactPtrList::iterator it;
	// 修正
	for ( it = m_buffList.begin(); it != m_buffList.end(); it++ )
	{
		ImpactBaseLogicPtr _ImpactLogicPtr =*it;
		// 有效
		if ( _ImpactLogicPtr && _ImpactLogicPtr->IsActive() && _ImpactLogicPtr->IsEffect() )
		{
			_ImpactLogicPtr->RefixSendAllDamage( *this, rTarget, RefixDamageInfo, rDamage );
		}
	}
	int nNewPhyDamage = _MAX( rDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS) + RefixDamageInfo.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS), 0 );
	int nNoTypeDamage = _MAX( rDamage.GetNotypeDamage() + RefixDamageInfo.GetNotypeDamage(), 0 );
	rDamage.SetTypeDamageByType( DamagesInof_T::DAMAGE_PHYSICS, nNewPhyDamage );
	rDamage.SetNotypeDamage( nNoTypeDamage );
	__LEAVE_FUNCTION;
}
//类型伤害免疫
void Obj_Character::IgnoreTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		ImpactPtrList::iterator it;
		//BUFF伤害免疫
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->IgnoreTypedDamage(*this,rDamage);
			}
		}
	__LEAVE_FUNCTION
}
//无类型伤害免疫
void Obj_Character::IgnoreNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		ImpactPtrList::iterator it;
		//BUFF伤害免疫
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				
				_ImpactLogicPtr->IgnoreNoTypeDamage(*this,rDamage);
			}
		}
	__LEAVE_FUNCTION
}
//类型伤害吸收和反射
void Obj_Character::AbsorbAndReflexTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF伤害吸收和反射
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				
				_ImpactLogicPtr->AbsorbAndReflexTypedDamage(*this,RefixDamageInfo,rDamage);
			}
		}
		int nNewPhyDamage =_MAX(rDamage.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS)-RefixDamageInfo.GetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS),0);
		rDamage.SetTypeDamageByType(DamagesInof_T::DAMAGE_PHYSICS,nNewPhyDamage);
	__LEAVE_FUNCTION
}
//无类型伤害吸收和反射
void Obj_Character::AbsorbAndReflexNoTypeDamage(DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		DamagesInof_T RefixDamageInfo;
		ImpactPtrList::iterator it;
		//BUFF伤害吸收和反射
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				_ImpactLogicPtr->AbsorbAndReflexNoTypeDamage(*this,RefixDamageInfo,rDamage);
			}
		}
		int nNewNoTypeDamage =_MAX(rDamage.GetNotypeDamage()-RefixDamageInfo.GetNotypeDamage(),0);
		rDamage.SetNotypeDamage(nNewNoTypeDamage);
	__LEAVE_FUNCTION
}

void Obj_Character::SetDie(bool bDie)
{	
// 	if (bDie == true)
// 	{
// 		SetCurHp(0);
// 	}	
	m_bDie = bDie;	
	m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::DIEFLAG,true);	//更新标记

}
bool Obj_Character::IsAlive(void) const
{
	if (m_bDie)
	{
		return false;
	}
	return true;
}
bool Obj_Character::IsDie()
{
// 	if (m_bDie && GetCurHp() > 0)
// 	{
// 		SetCurHp(0);
// 	}
	return m_bDie;
}

void Obj_Character::OnDie(Obj_Character& rKiller)
{
	__ENTER_FUNCTION
	//关闭目前一切操作
	if (IsUsingSkill()) 
	{
		AssertEx(m_CurSkillLogicPtr, "");
		m_CurSkillLogicPtr->BreakSkill(*this);
	}
	StopMove(true,true);
	
	//更新obj死亡状态
	SetDie(true);
	//死亡给 BUFF 一次处理机会
	ImpactPtrList::iterator it;
	for (it=m_buffList.begin();it!=m_buffList.end();it++)
	{
		//有效
		ImpactBaseLogicPtr _ImpactLogicPtr =*it;
		if (_ImpactLogicPtr && _ImpactLogicPtr->IsActive() && _ImpactLogicPtr->IsEffect())
		{
			_ImpactLogicPtr->OnDie(*this);
		}
	}
	__LEAVE_FUNCTION
}
bool Obj_Character::OnSendDamageToUnit(Obj_Character&rTarget,DamagesInof_T& rDamage)
{
	__ENTER_FUNCTION
		//发出伤害 将攻击对象加入威胁度列表
		OnThreat(rTarget,1);//加一点仇恨 强制让攻击目标进入自己的仇恨列表 
		// 发出的伤害要根据玩家效果做一些修正
		RefixSendAllDamage( rTarget, rDamage );

		rTarget.OnReceiveDamage(rDamage);
		//发出伤害可以解除的BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				if (_ImpactLogicPtr->IsFadeoutWhenSendDamage() ||
					_ImpactLogicPtr->IsFadeoutWhenSendAttack())
				{
					_ImpactLogicPtr->OnFadeOut(*this);
				}
				else
				{
					_ImpactLogicPtr->OnSendDamgeFinish( *this, rTarget, rDamage );
				}
			}
		}
		ResetEscape();
		return true;
	__LEAVE_FUNCTION
		return false;

}

void Obj_Character::Tick_Damage(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (IsInCombat())
	{
		if (m_EscapeCountDown > 0)
		{
			m_EscapeCountDown -= rTimeInfo.m_uTimeElapse;
		}
	}
	__LEAVE_FUNCTION
}

bool Obj_Character::IsInEscape()
{
	__ENTER_FUNCTION
	if (IsInCombat())
	{
		return m_EscapeCountDown<=0;
	}
	return false;
	__LEAVE_FUNCTION
	return false;
}

void Obj_Character::ResetEscape()
{
	__ENTER_FUNCTION
	m_EscapeCountDown = _GameConfig().m_EscapeCountdown;
	__LEAVE_FUNCTION
}