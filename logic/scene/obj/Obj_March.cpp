#include "Obj_March.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Scene/CopyScene.h"
#include "Scene/Scene/MainScene.h"
#include "player/Player.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"
#include "Table/Table_SceneClass.h"
#include "Config.h"

POOLDEF_IMPL(Obj_March);

Obj_March::Obj_March( )
{
	
}

Obj_March::~Obj_March( void )

{

}

void Obj_March::OnEnterScene(void)
{
	__ENTER_FUNCTION
	Obj_Character::OnEnterScene();

	CleanUpView();

	SetScenePos(GetChangeScenePos());

	__LEAVE_FUNCTION
}

void Obj_March::OnLeaveScene(void)
{
	__ENTER_FUNCTION
		Obj_Character::OnLeaveScene();
	__LEAVE_FUNCTION
}

void Obj_March::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_PROTECT

		Obj_Character::Tick(rTimeInfo);
		
		Tick_General(rTimeInfo);
		
	__LEAVE_PROTECT
}

void Obj_March::OnLogin(void)
{
	__ENTER_FUNCTION

	__LEAVE_FUNCTION
}
void Obj_March::OnLogout(void)
{
	__ENTER_FUNCTION

	__LEAVE_FUNCTION
}

void Obj_March::Tick_General(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		__LEAVE_FUNCTION
}

void Obj_March::FillMarchBaseInfo(MarchBaseInfo &rInfo)
{
	__ENTER_FUNCTION

		rInfo.m_Guid = GetGuid();
	rInfo.m_szName = GetName();
	rInfo.m_nLevel = GetLevel();
	rInfo.m_OwnGuid = 0;

	__LEAVE_FUNCTION
}

void Obj_March::UpdateMarchBaseInfoToSceneService()
{
	__ENTER_FUNCTION

		UpdateMarchBaseInfoMsgPtr msgPtr = POOLDEF_NEW(UpdateMarchBaseInfoMsg);
		AssertEx(msgPtr, "");
		FillMarchBaseInfo(msgPtr->m_BaseInfo);
		SendMessage2Srv(ServiceID::SCENE, msgPtr);

	__LEAVE_FUNCTION
}

void Obj_March::SetUserBitLocked(USER_BITLOCKTYPE bltType,tuint32 nContinuTime)
{
	m_BitLock.MarkBit(bltType);
	if (bltType>=0 && bltType<USER_BITLOCK_NUM)
	{
		m_UserBitLockInfo[bltType].m_nStartLoackTime =gTimeManager.RunTime();
		m_UserBitLockInfo[bltType].m_nContinuedTime =nContinuTime;
	}
}

SceneID Obj_March::GetLastSceneID(void) const
{
	if (IsSceneValid())
	{
		return SceneID(GetSceneClassID(), GetSceneInstID());
	}

	return m_LastSceneID;
}

void Obj_March::SetLastSceneID(const SceneID &rSceneID)
{
	m_LastSceneID = rSceneID;
}

ScenePos Obj_March::GetLastScenePos(void) const
{
	if (IsSceneValid())
	{
		return GetScenePos();
	}

	return m_LastScenePos;
}

void Obj_March::SetLastScenePos(const ScenePos &rScenePos)
{
	m_LastScenePos = rScenePos;
}

void Obj_March::UpdateLastSceneIDAndScenePos(void)
{
	if (IsSceneValid())
	{
		SetLastSceneID(SceneID(GetSceneClassID(), GetSceneInstID()));
		SetLastScenePos(GetScenePos());
	}
}

SceneID Obj_March::GetLastNoneCopySceneID(void) const
{
	if (IsSceneValid())
	{
		if (!GetScene().IsCopyScene())
		{
			return SceneID(GetSceneClassID(), GetSceneInstID());
		}
	}

	return m_LastNoneCopySceneID;
}

void Obj_March::SetLastNoneCopySceneID(const SceneID &rSceneID)
{
	m_LastNoneCopySceneID = rSceneID;
}

ScenePos Obj_March::GetLastNoneCopyScenePos(void) const
{
	if (IsSceneValid())
	{
		if (!GetScene().IsCopyScene())
		{
			return GetScenePos();
		}
	}

	return m_LastNoneCopyScenePos;
}

void Obj_March::SetLastNoneCopyScenePos(const ScenePos &rScenePos)
{
	m_LastNoneCopyScenePos = rScenePos;
}

void Obj_March::UpdateLastNoneCopySceneIDAndScenePos(void)
{
	if (IsSceneValid())
	{
		if (!GetScene().IsCopyScene())
		{
			SetLastNoneCopySceneID(SceneID(GetSceneClassID(), GetSceneInstID()));
			SetLastNoneCopyScenePos(GetScenePos());
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//处理附近玩家列表部分	-Begin
//////////////////////////////////////////////////////////////////////////
void Obj_March::HandleMessage(const MarchReqNearListMsg &rMsg)
{
	__ENTER_FUNCTION
		SendSceneMarchListToClient(rMsg);

	__LEAVE_FUNCTION
}



void Obj_March::HandleMessage(const MarchMoveMsg &rMsg)
{
	__ENTER_FUNCTION
		//不能移动
		tint32 nCount = rMsg.m_nPosCount;
		
		for (tint32 i = 0; i < nCount; i++)
		{
			MoveAppend(ScenePos(rMsg.m_nPosX[i], rMsg.m_nPoxZ[i]));
		}
		CleanUpAllTrackPointFlag();

	__LEAVE_FUNCTION
}

void Obj_March::MoveAppend(const ScenePos &rPos)
{
	__ENTER_FUNCTION

		if (!IsMoving())
		{
			m_PathCont.PushBack(PathNode(GetScenePos(), rPos));
			OnStartMove();
		}
		else
		{
			tint32 nSize = m_PathCont.Size();
			AssertEx(nSize >= 1 && nSize <= m_PathCont.MaxSize(), "");
			m_PathCont.PushBack(PathNode(m_PathCont[nSize - 1].m_EndPos, rPos));
		}

		__LEAVE_FUNCTION
}

void Obj_March::Tick_Moving(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		BroadcastMoveStatus();
	Moving(rTimeInfo);

	__LEAVE_FUNCTION
}

void Obj_March::OnScenePosChanged(void)
{
	__ENTER_FUNCTION

	

	__LEAVE_FUNCTION
}


void Obj_March::SendSceneMarchListToClient(const MarchReqNearListMsg &rMsg)
{
	__ENTER_FUNCTION

		if (!IsSceneValid())
		{
			return;
		}
		Scene &rScene = GetScene();

		//扫描出当前场景所有玩家
		MarchRefCont Cont;
		rScene.Scan_March_All(Cont);

		//剔除自己
		Cont.RemoveByPred(Pred_ObjIDEqual(GetID()));

		if (Cont.Size() > 0)
		{
			//最多发送20个玩家的信息
			if (Cont.Size() > 20)
			{
				std::nth_element(Cont.begin(), Cont.begin() + 19, Cont.end(), Pred_ObjDistanceLess(GetScenePos()));	//【stl】
				Cont.ReduceSize(20);
			}

			MarchRetNearListMsgPtr MsgPtr = POOLDEF_NEW(MarchRetNearListMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_nObjId = GetID();
			MsgPtr->m_ReceiverGuid = rMsg.m_ReceiverGuid;
			MsgPtr->m_BaseMarchVec.resize(Cont.Size());
			MsgPtr->m_nSceneId = GetSceneInstID();
			tint32 nRealCount = 0;
			for (tint32 i = 0; i < Cont.Size(); i++)
			{
				Obj_March &rMarch = Cont[i];
				MsgPtr->m_BaseMarchVec[i].m_Guid = rMarch.GetMarchId();
				MsgPtr->m_BaseMarchVec[i].m_szName = rMarch.GetName().GetCText();
				MsgPtr->m_BaseMarchVec[i].m_nLevel = rMarch.GetLevel();
				nRealCount ++;
			}
			
			SendMessage2User(rMsg.m_ReceiverGuid,MsgPtr);
		}

		__LEAVE_FUNCTION
}

void Obj_March::Tick_View(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

		m_TickViewInterval -= rTimeInfo.m_uTimeElapse;
	if (m_TickViewInterval > 0)
	{
		return;
	}
	m_TickViewInterval = TICK_VIEW_TICK_INTERVAL;

	if (!IsSceneValid())
	{
		return;
	}
	Scene &rScene = GetScene();

	const Table_SceneClass * pSceneClass = GetTable_SceneClassByID(rScene.GetSceneClassID());
	if ( pSceneClass == null_ptr )
	{ // 指针无效
		return;
	}
	const Table_SceneClass & rSceneClass = *pSceneClass;

	//重置
	for (ViewObjIDMap::iterator it = m_ViewObjIDMap.begin(); it != m_ViewObjIDMap.end(); it++)
	{
		it->second = false;
	}

	//扫描周围的Obj
	ObjRefCont BaseViewObjCont;
	rScene.Scan_All_Circle(
		BaseViewObjCont,
		GetScenePos(),
		(tfloat32)rSceneClass.GetPlayerViewRadius()); // _GameConfig().m_fPlayerViewRadius
	for (tint32 i = 0; i < BaseViewObjCont.Size(); i++)
	{
		Obj &rObj = BaseViewObjCont[i];
		if (rObj.CanBeView(*this))
		{
			ViewObjIDMap::iterator itFind = m_ViewObjIDMap.find(rObj.GetID());
			if (itFind != m_ViewObjIDMap.end())
			{
				//此Obj已经在视野里了
				itFind->second = true;
			}
			else
			{
				//首次看到这个Obj
				m_ViewObjIDMap.insert(std::make_pair(rObj.GetID(), true));
				OnInSight(rObj);
			}
		}
	}

	//扫描视野边缘Obj
	ObjRefCont EdgeViewObjCont;
	rScene.Scan_All_Ring(
		EdgeViewObjCont,
		GetScenePos(),
		(tfloat32)rSceneClass.GetPlayerViewRadius(), // _GameConfig().m_fPlayerViewRadius
		(tfloat32)rSceneClass.GetPlayerViewRadius() + _GameConfig().m_fPlayerViewEdgeInc); // _GameConfig().m_fPlayerViewRadius
	for (tint32 i = 0; i < EdgeViewObjCont.Size(); i++)
	{
		Obj &rObj = EdgeViewObjCont[i];
		if (rObj.CanBeView(*this))
		{
			ViewObjIDMap::iterator itFind = m_ViewObjIDMap.find(rObj.GetID());
			if (itFind != m_ViewObjIDMap.end())
			{
				itFind->second = true;
			}
		}
	}

	//移除不在当前视野中的Obj
	for (ViewObjIDMap::iterator it = m_ViewObjIDMap.begin(); it != m_ViewObjIDMap.end(); )
	{
		if (it->second)
		{
			//此Obj在视野中
			it++;
		}
		else
		{
			//此Obj已不在视野中
			tint32 nObjID = it->first;
			it = _erase(m_ViewObjIDMap, it);
			OnOutSight(nObjID);
		}
	}

	__LEAVE_FUNCTION
}


bool Obj_March::IsInSight(tint32 nObjID)
{
	return (m_ViewObjIDMap.find(nObjID) != m_ViewObjIDMap.end());
}

void Obj_March::OnInSight(Obj &rObj)
{
	__ENTER_FUNCTION

		if (GetID() != rObj.GetID())
		{
			rObj.SendMoveStatus(*this);
		}

		__LEAVE_FUNCTION
}

void Obj_March::OnOutSight(tint32 nObjID)
{
	__ENTER_FUNCTION

		if (GetID() != nObjID)
		{
			Del_MarchMsgPtr MsgPtr = POOLDEF_NEW(Del_MarchMsg);
			AssertEx(MsgPtr,"");
			MsgPtr->m_nObjId = nObjID;
			MsgPtr->m_nSceneId = GetSceneInstID();
			MsgPtr->m_nMarchObjId = GetID();
			SendMessage2User(GetPlayerId(),MsgPtr);
		}

		__LEAVE_FUNCTION
}

void Obj_March::ForceInSight(Obj &rObj)
{
	__ENTER_FUNCTION

		if (!IsInSight(rObj.GetID()))
		{
			m_ViewObjIDMap.insert(std::make_pair(rObj.GetID(), true));
			rObj.SendMoveStatus(*this);
		}

		__LEAVE_FUNCTION
}

void Obj_March::CleanUpView(void)
{
	__ENTER_FUNCTION

		m_ViewObjIDMap.clear();

	__LEAVE_FUNCTION
}