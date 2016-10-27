#include "Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_CoolDownTime.h"
#include "service/MessageOp.h"
#include "Message/SceneMsg.h"

Obj_Character::Obj_Character( void )
{
	m_nCurSelectObjId = invalid_id;
	m_nDataID = invalid_id;

	m_nCurHp =0;
	m_nCurXp =0;
	m_nLevel =0;

	m_Name ="";
	m_ForceType =FORCETYPE_T::TYPE_INVAILD;


	//同步属性包的脏标的
	 m_AttrSyncDirtyFlag.ClearAllBits();
	
	 m_bDie = false;
	

	 // 是否处于战斗状态
	 m_bIsInCombat =false;

	 for (int i = 0; i < MAXOWNSKILL; i++)
	 {
		 m_OwnSkillList[i] =invalid_id;
	 }
	 m_nLastUseSkillTime =0;
	 m_fFaceDir = 0.0f;

	 m_fDistanceCompensate = 0.0f;

	 m_fStopRange = 0.01f;
	for (int nPointIndex =0;nPointIndex<MAXTRACEPOINTNUM;nPointIndex++)
	{
		m_IsTrackPointUsed[nPointIndex] =false;
	}
	
	//make sure clean  
	
	m_nLastBroadcastHitTime =0;
	m_EscapeCountDown = 0;
	m_bIsBreedingClick = false;
}

Obj_Character::~Obj_Character( void )
{

}

void Obj_Character::OnEnterScene(void)
{
	__ENTER_FUNCTION

	Obj_Action::OnEnterScene();
	CalculateFinalyAttr();
	StopMove(false, true);

	__LEAVE_FUNCTION
}

void Obj_Character::OnLeaveScene(void)
{
	__ENTER_FUNCTION

	Obj_Action::OnLeaveScene();
	//正在使用技能 给技能一次处理机会
	if (IsUsingSkill())
	{
		AssertEx(m_CurSkillLogicPtr, "");
		m_CurSkillLogicPtr->BeforLevelScene(*this);
	}
	//给BUFF 一次处理机会
	for (ImpactPtrList::iterator it = m_buffList.begin(); it != m_buffList.end(); ++it)
	{
		//有效
		ImpactBaseLogicPtr _ImpactLogicPtr =*it;
		if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive())
		{
			_ImpactLogicPtr->BeforeLeaveScene(*this);
		}
	}
	__LEAVE_FUNCTION
}
void Obj_Character::FaceTo(ScenePos facePos)
{
	__ENTER_FUNCTION

	SetFaceDir(CalcDirection(GetScenePos(), facePos));

	__LEAVE_FUNCTION
}
void Obj_Character::FaceTo(int faceObjId)
{
	__ENTER_FUNCTION

	if (IsSceneValid())
	{
		ObjPtr objPtr = GetScene().GetObjByID(faceObjId);
		if (objPtr)
		{
			FaceTo(objPtr->GetScenePos());
		}
	}

	__LEAVE_FUNCTION
}
void Obj_Character::SetFaceDir(float fFaceDir)
{
	m_fFaceDir = fFaceDir;
	//m_AttrBroadCastDirtyFlag.SetBit(BaseAttrBroadDirty_T::FACEDIR,true);
}

void Obj_Character::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Obj_Action::Tick(rTimeInfo);

	//技能心跳
	Tick_Skill(rTimeInfo);
	//BUFF心跳
	Tick_Impact(rTimeInfo);
	//冷却时间心跳
	Tick_CooldownList(rTimeInfo);
	//战斗属性计算
	Tick_CalculateCombatAttr();

	//仇恨列表心跳
	Tick_EnemyList(rTimeInfo);
	//移动心跳
	Tick_Moving(rTimeInfo);
	//伤害心跳
	Tick_Damage(rTimeInfo);

	__LEAVE_FUNCTION
}

void Obj_Character::Tick_CooldownList(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION

		m_CoolDownList.Tick(rTimeInfo);
	__LEAVE_FUNCTION
}
bool Obj_Character::UpdateCooldownList(int16 nID, int nTotalTime,int nElapsed)
{
	__ENTER_FUNCTION
		if (nID >=0)
		{
			bool bRet =m_CoolDownList.UpdateCooldown(nID,nTotalTime,nElapsed);
			return bRet;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}
bool Obj_Character::AddCoolDownToList(int16 nCoolDownId)
{
	__ENTER_FUNCTION
		if (nCoolDownId ==invalid_id)
		{
			return true;
		}
		const Table_CoolDownTime* CDTable =GetTable_CoolDownTimeByID(nCoolDownId);
		if (CDTable !=null_ptr)
		{
			bool bRet =UpdateCooldownList((int16)CDTable->GetId(),CDTable->GetCDTime(),0);
			return bRet;
		}
		return false;
	__LEAVE_FUNCTION
		return false;

}


void Obj_Character::SendNotice( const tchar* szNotice ,bool IsFilterRepeat)
{
	__ENTER_FUNCTION

		if (szNotice != null_ptr && szNotice[0])
		{
			NoticeMsgPtr MsgPtr = POOLDEF_NEW(NoticeMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_szNotice = szNotice;
			MsgPtr->m_nIsFilterRepeat = IsFilterRepeat;
			SendMessage2User(GetPlayerId(),MsgPtr);
		}

		__LEAVE_FUNCTION
}
