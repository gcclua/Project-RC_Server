
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
		//��ǰ����ʹ�ü��� ���ܲ����ƶ��ͷ��Ҳ��ܱ��ƶ����
		if (IsUsingSkill())
		{
			//IsValid �Ѿ������пղ���
			AssertEx(m_CurSkillLogicPtr, "");
			Table_SkillBase const& rSkillBase =*m_CurSkillLogicPtr->GetCurSkillInfo().m_pSkillBase;
			if (rSkillBase.GetIsMove() !=1 && rSkillBase.GetIsMoveBreak() !=1)
			{
				return false;
			}
		}
		//�Ƿ��н�ֹ�ƶ���BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr ImpactLogicPtr =*it;
			if (ImpactLogicPtr)
			{
				ImpactStruct const& _impactStruct =ImpactLogicPtr->GetImpatInfo();
				//!!!��Ч��BUFF��������
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
		//����ʹ�ü���  ����ܱ��ƶ���ϵļ���
		if (IsUsingSkill())
		{
			AssertEx(m_CurSkillLogicPtr, "");
			//IsValid �Ѿ������пղ���
			Table_SkillBase const& _skillBase =*(m_CurSkillLogicPtr->GetCurSkillInfo().m_pSkillBase);
			if (_skillBase.GetIsMoveBreak() ==1)
			{
				m_CurSkillLogicPtr->BreakSkill(*this);
			}
		}
		//�Ƿ�����Ҫ�ƶ���ɢ��BUFF
		ImpactPtrList::iterator it;
		for (it=m_buffList.begin();it!=m_buffList.end();it++)
		{
			ImpactBaseLogicPtr _ImpactLogicPtr =*it;
			//��Ч
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
	//�ƶ�ǰ ��Ҫ����һЩ�������
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