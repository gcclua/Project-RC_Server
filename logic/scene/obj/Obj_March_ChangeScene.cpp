#include "Obj_March.h"
#include "Config.h"
#include "Message/SceneMsg.h"
#include "Scene/Scene/Scene.h"
#include "Service/MessageOp.h"
#include "Table/Table_SceneClass.h"
#include "Table/Table_SceneNpc.h"
#include "Table/Table_SkillBase.h"
#include "Table/Table_SkillEx.h"

void Obj_March::ChangeScene(const SceneID &rsid, const ScenePos &rpos)
{
	__ENTER_FUNCTION

	//ÇÐ»»³¡¾°¼Ó1500ºÁÃëCD
	bool bLockRet = IsUserBitLocked(USER_BITLOCK_CHANGESCENE);
	if ( !bLockRet)
	{
		SetUserBitLocked(USER_BITLOCK_CHANGESCENE,1500);
		DoChangeScene(rsid,rpos);
	}

	__LEAVE_FUNCTION
}
void Obj_March::DoChangeScene(const SceneID &rsid, const ScenePos &rpos)
{
	__ENTER_FUNCTION
	if (!IsSceneValid())
	{
		return;
	}
	

	Scene &rScene = GetScene();
	
	SetChangeScenePos(rpos);

	MarchReqChangeSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchReqChangeSceneMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_guid = GetGuid();
	MsgPtr->m_CurSceneID = SceneID(rScene.GetSceneClassID(), rScene.GetSceneInstID());
	MsgPtr->m_DestSceneID = rsid;
	SendMessage2Srv(ServiceID::SCENE, MsgPtr);

	__LEAVE_FUNCTION
}

void Obj_March::ChangeScene_General(tint32 nSceneClassID)
{
	__ENTER_FUNCTION

	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(nSceneClassID);
	if (pSceneClass == null_ptr)
	{
		return;
	}
	const Table_SceneClass &rSceneClass = *pSceneClass;
	if ((rSceneClass.GetType() != SceneType::MAIN))
	{
		return;
	}

	ChangeScene(SceneID(nSceneClassID, invalid_id));

	__LEAVE_FUNCTION
}

void Obj_March::ChangeScene_General(const tint32 nSceneClassID,const ScenePos& rPos)
{
__ENTER_FUNCTION
	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(nSceneClassID);
	if (pSceneClass == null_ptr)
	{
		return;
	}
	const Table_SceneClass &rSceneClass = *pSceneClass;
	if ((rSceneClass.GetType() != SceneType::MAIN) )
	{
		return;
	}

	ChangeScene(SceneID(nSceneClassID, invalid_id), rPos);

__LEAVE_FUNCTION
}

void Obj_March::ChangeScene_OpenCopyScene(tint32 nSceneClassID)
{
	__ENTER_FUNCTION
	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(nSceneClassID);
	if (pSceneClass == null_ptr)
	{
		return;
	}
	const Table_SceneClass &rSceneClass = *pSceneClass;
	if (rSceneClass.GetType() != SceneType::COPY)
	{
		return;
	}

	ChangeScene(SceneID(nSceneClassID, invalid_id));

	__LEAVE_FUNCTION
}

void Obj_March::ChangeScene_JoinCopyScene(const SceneID &rsid)
{
	__ENTER_FUNCTION


	const Table_SceneClass *pSceneClass = GetTable_SceneClassByID(rsid.m_nClassID);
	if (pSceneClass == null_ptr)
	{
		return;
	}
	const Table_SceneClass &rSceneClass = *pSceneClass;
	if (rSceneClass.GetType() != SceneType::COPY)
	{
		return;
	}

	ChangeScene(rsid);

	__LEAVE_FUNCTION
}

void Obj_March::ChangeScene_ExitCopyScene(void)
{
	__ENTER_FUNCTION

	if (IsInCopyScene())
	{
		SceneID scnId = GetLastNoneCopySceneID();
		ChangeScene(scnId, GetLastNoneCopyScenePos());
	}

	__LEAVE_FUNCTION
}

ScenePos Obj_March::GetChangeScenePos(void) const
{
	return m_ChangeScenePos;
}

void Obj_March::SetChangeScenePos(const ScenePos &rPos)
{
	m_ChangeScenePos = rPos;
}

void Obj_March::UpdateChangeScenePosOnLogin(void)
{
	__ENTER_FUNCTION

	if (IsSceneValid())
	{
		tint32 nSceneClassID = GetSceneClassID();
		if (nSceneClassID == m_LastSceneID.m_nClassID)
		{
			SetChangeScenePos(m_LastScenePos);
			return;
		}
		if (nSceneClassID == m_LastNoneCopySceneID.m_nClassID)
		{
			SetChangeScenePos(m_LastNoneCopyScenePos);
			return;
		}
	}

	__LEAVE_FUNCTION
}
