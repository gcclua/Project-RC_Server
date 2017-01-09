
#include "Obj_Character.h"
#include "Scene/Scene/Scene.h"
#include "Table/Table_SkillBase.h"
#include "packet/Packet/CG_MOVE_PAK.h"

#include "Message/SceneMsg.h"
#include "service/MessageOp.h"

float Obj_Character::GetMoveSpeed(void)
{
	return (static_cast<float>(GetCombatAttrByID(COMBATATTR_T::MOVESPEED)) / 100.0f);
}

bool Obj_Character::IsMoving(void) const
{
	return (!m_PathCont.Empty());
}

bool Obj_Character::IsCanMove()
{
	__ENTER_FUNCTION
		//当前正在使用技能 技能不能移动释放且不能被移动打断
		if (IsUsingSkill())
		{
			//IsValid 已经做了判空操作
			AssertEx(m_CurSkillLogicPtr, "");
			Table_SkillBase const& rSkillBase =*m_CurSkillLogicPtr->GetCurSkillInfo().m_pSkillBase;
			if (rSkillBase.GetIsMove() !=1 && rSkillBase.GetIsMoveBreak() !=1)
			{
				return false;
			}
		}
		//是否有禁止移动的BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				ImpactStruct const& _impactStruct =ImpactLogicPtr->GetImpatInfo();
				//!!!生效的BUFF才起作用
				if (ImpactLogicPtr->IsActive() && ImpactLogicPtr->IsEffect())
				{
					if(ImpactLogicPtr->IsMoveDisabled())
					{
						return false;
					}
				}
			}
		}
		return true;
	__LEAVE_FUNCTION
		return false;
}
void Obj_Character::BeforeMoveTo()
{
	__ENTER_FUNCTION
		//正在使用技能  打断能被移动打断的技能
		if (IsUsingSkill())
		{
			AssertEx(m_CurSkillLogicPtr, "");
			//IsValid 已经做了判空操作
			Table_SkillBase const& _skillBase =*(m_CurSkillLogicPtr->GetCurSkillInfo().m_pSkillBase);
			if (_skillBase.GetIsMoveBreak() ==1)
			{
				m_CurSkillLogicPtr->BreakSkill(*this);
			}
		}
		//是否有需要移动消散的BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//有效
			if (_ImpactLogicPtr &&_ImpactLogicPtr->IsActive()&& _ImpactLogicPtr->IsEffect())
			{
				if (_ImpactLogicPtr->IsFadeoutOnMoveTo())
				{
					_ImpactLogicPtr->OnFadeOut(*this);
				}
			}
		}
	__LEAVE_FUNCTION
}
void Obj_Character::MoveTo(const ScenePos &rPos, float fStopRange/* = 0.01f*/)
{
	__ENTER_FUNCTION

	if (IsCanMove() ==false)
	{
		return;
	}
	//移动前 需要做的一些处理操作
	BeforeMoveTo();
	bool bMoving1 = IsMoving();

	StopMove(true, false);
	m_TargetPos = rPos;
	m_fStopRange = fStopRange;

	if (IsSceneValid())
	{
		PathCont pc;
		if (GetScene().FindPath(GetScenePos(), rPos, pc))
		{
			m_PathCont += pc;
		}
	}
	bool bMoving2 = IsMoving();
	if (bMoving1 && !bMoving2)
	{
		OnEndMove();
	}
	if (!bMoving1 && bMoving2)
	{
		OnStartMove();
	}
	CleanUpAllTrackPointFlag();
	__LEAVE_FUNCTION
}

void Obj_Character::StopMove(bool bNotifyClient, bool bNotifyEvent)
{
	__ENTER_FUNCTION

	if (IsMoving())
	{
		AssertEx(!m_PathCont.Empty(), "");

		if (bNotifyClient && IsSceneValid())
		{
			MarchStopMsgPtr MsgPtr = POOLDEF_NEW(MarchStopMsg);
			MsgPtr->m_nX = GetScenePos().m_nX;
			MsgPtr->m_nZ = GetScenePos().m_nZ;
			MsgPtr->m_nSerial = m_PathCont[0].m_nSerial;
			MsgPtr->m_nObjId = GetID();
			MsgPtr->m_nSceneId = GetSceneInstID();
			GetScene().BroadCast_InSight_Include(MsgPtr, GetID());
		}

		m_PathCont.CleanUp();

		if (bNotifyEvent)
		{

			OnEndMove();
		}
	}

	__LEAVE_FUNCTION
}

void Obj_Character::OnStartMove(void)
{
	m_fDistanceCompensate = 0.0f;
}

void Obj_Character::OnEndMove(void)
{
	m_fDistanceCompensate = 0.0f;
}

void Obj_Character::SendMoveStatus(Obj_March &rMarch)
{
	__ENTER_FUNCTION

	int nbs = m_PathCont.BroadcastedSize();
	if (nbs > 0)
	{
		RetMarchMoveMsgPtr MsgPtr = POOLDEF_NEW(RetMarchMoveMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_nObjId = GetID();
		MsgPtr->m_nPosCount = nbs;
		MsgPtr->m_nSceneId  = GetSceneInstID();

		int nSize = m_PathCont.Size();
		for (int i = 0; i < nSize; i++)
		{
			const PathNode &rPathNode = m_PathCont[i];
			MsgPtr->m_nSerial.push_back(rPathNode.m_nSerial);
			MsgPtr->m_nPosX.push_back(rPathNode.m_EndPos.m_nX );
			MsgPtr->m_nPosX.push_back(rPathNode.m_EndPos.m_nZ );
		}

		AssertEx(MsgPtr->m_nPosCount == MsgPtr->m_nSerial.size(), "");

		SendMessage2User(rMarch.GetPlayerId(),MsgPtr);
	}

	__LEAVE_FUNCTION
}

void Obj_Character::BroadcastMoveStatus(void)
{
	__ENTER_FUNCTION

	if (!IsSceneValid())
	{
		return;
	}
	Scene &rScene = GetScene();

	tint32 nubs = m_PathCont.UnBroadcastedSize();
	if (nubs > 0)
	{
		RetMarchMoveMsgPtr MsgPtr = POOLDEF_NEW(RetMarchMoveMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_nObjId = GetID();
		MsgPtr->m_nPosCount = nubs;
		MsgPtr->m_nSceneId  = GetSceneInstID();

		int nSize = m_PathCont.Size();
		for (int i = 0; i < nSize; i++)
		{
			const PathNode &rPathNode = m_PathCont[i];
		
			MsgPtr->m_nSerial.push_back(rPathNode.m_nSerial);
			MsgPtr->m_nPosX.push_back(rPathNode.m_EndPos.m_nX );
			MsgPtr->m_nPosX.push_back(rPathNode.m_EndPos.m_nZ );
		}

		AssertEx(MsgPtr->m_nPosCount == MsgPtr->m_nSerial.size(), "");
		rScene.BroadCast_InSight_Except(MsgPtr, GetID());
	}


	__LEAVE_FUNCTION
}

void Obj_Character::Tick_Moving(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	BroadcastMoveStatus();
	Stopping();
	Moving(rTimeInfo);

	__LEAVE_FUNCTION
}

void Obj_Character::Moving(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	if (m_PathCont.Empty())
	{
		return;
	}

	ScenePos CurPos = GetScenePos();
	ScenePos TarPos = m_PathCont[0].m_EndPos;

	float fDirection = CalcDirection(CurPos, TarPos);
	SetFaceDir(fDirection);

	float fMoveSpeed = GetMoveSpeed();
	float fMoveDistance = fMoveSpeed * (static_cast<float>(rTimeInfo.m_uTimeElapse) / 1000.0f);
	fMoveDistance += m_fDistanceCompensate;
	float fLackDistance = CurPos.Distance(TarPos);
	if (fMoveDistance >= fLackDistance)
	{
		SetScenePos(TarPos);
		m_fDistanceCompensate = fMoveDistance - fLackDistance;

		m_PathCont.PopFront();
		if (m_PathCont.Empty())
		{
			
			OnEndMove();
		}
	}
	else
	{
		ScenePos NewPos;
		NewPos.m_nX = (int)(CurPos.m_nX + fMoveDistance * ::cos(fDirection));
		NewPos.m_nZ = (int)(CurPos.m_nZ + fMoveDistance * ::sin(fDirection));
		SetScenePos(NewPos);
		m_fDistanceCompensate = 0.0f;
	}

	__LEAVE_FUNCTION
}

void Obj_Character::Stopping(void)
{
	__ENTER_FUNCTION

	if (m_PathCont.Empty())
	{
		return;
	}

	if (GetScenePos().Distance(m_TargetPos) <= m_fStopRange)
	{
		StopMove(true, true);
	}

	__LEAVE_FUNCTION
}

void Obj_Character::TeleMoveTo(const ScenePos &targetrPos)
{
	__ENTER_FUNCTION

	CleanUpAllTrackPointFlag();

	StopMove(true, true);

	if (IsSceneValid())
	{
		ScenePos RetPos;
		if (GetScene().FindStraight(GetScenePos(), targetrPos, RetPos))
		{
			SetScenePos(RetPos);
		}
	}

	__LEAVE_FUNCTION
}

void Obj_Character::UpdateTeleMoveToClient(const ScenePos &targetrPos,bool isNeedChangeFacaTo,int nAnimalId/*=-1*/)
{
	if (IsSceneValid() ==false)
	{
		return ;
	}
	Scene& rScene =GetScene();
	RetMarchTeleMoveMsgPtr MsgPtr = POOLDEF_NEW(RetMarchTeleMoveMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nObjId = GetID();
	MsgPtr->m_nPosX  = targetrPos.m_nX;
	MsgPtr->m_nPoxZ  = targetrPos.m_nZ;
	MsgPtr->m_nSceneId = GetSceneInstID();
	
	rScene.BroadCast_InSight_Include(MsgPtr,GetID());
}

void Obj_Character::DelFromScene(void) 
{
	__ENTER_FUNCTION
	SetActive(false);
	__LEAVE_FUNCTION
}