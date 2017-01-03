#include "Obj.h"
#include "Scene/Scene/Scene.h"
#include "Scene/Scene/CopyScene.h"
#include "Message/SceneMsg.h"

Obj::Obj( void )
{
	m_bActive = true;
	m_nID = invalid_id;
	m_pScene = null_ptr;
	m_nStealthLev = 0;
	m_nScout = 0;
}

Obj::~Obj( void )
{

}

void Obj::OnEnterScene(void)
{

}

void Obj::OnLeaveScene(void)
{

}

void Obj::Tick(const TimeInfo &rTimeInfo)
{

}

bool Obj::CanBeView(Obj_Npc & rNpc)
{
	return CanBeScout(rNpc);
}

bool Obj::CanBeView(Obj_March &rMarch)
{
	return CanBeScout(rMarch);
}

bool Obj::CanBeScout(Obj &rObj)
{
	return ((rObj.GetID() ==GetID())||(rObj.GetScout() >= m_nStealthLev));
}

void Obj::SetScenePos(ScenePos Pos)
{
	__ENTER_FUNCTION

	m_ScenePos = Pos;
	OnScenePosChanged();

	__LEAVE_FUNCTION
}

void Obj::ForceSetScenePos(ScenePos Pos)
{
	__ENTER_FUNCTION

	SetScenePos(Pos);

	// ·¢°ü
	if (IsSceneValid())
	{
		Force_SetPosMsgPtr MsgPtr = POOLDEF_NEW(Force_SetPosMsg);

		AssertEx(MsgPtr,"");
		MsgPtr->m_nObjId = GetID();
		MsgPtr->m_nPosX = m_ScenePos.m_nX ;
		MsgPtr->m_nPoxZ = m_ScenePos.m_nZ;
		MsgPtr->m_nSceneId = GetSceneInstID();
		GetScene().BroadCast(MsgPtr);
	}

	__LEAVE_FUNCTION
}

SceneClassID Obj::GetSceneClassID(void) const
{
	__ENTER_FUNCTION

	if (IsSceneValid())
	{
		return GetScene().GetSceneClassID();
	}
	else
	{
		return invalid_id;
	}

	__LEAVE_FUNCTION
	return invalid_id;
}

SceneInstID Obj::GetSceneInstID(void) const
{
	__ENTER_FUNCTION

	if (IsSceneValid())
	{
		return GetScene().GetSceneInstID();
	}
	else
	{
		return invalid_id;
	}

	__LEAVE_FUNCTION
	return invalid_id;
}

bool Obj::IsInCopyScene(void) const
{
	__ENTER_FUNCTION

	if (IsSceneValid())
	{
		return GetScene().IsCopyScene();
	}
	else
	{
		return false;
	}

	__LEAVE_FUNCTION
	return false;
}

bool Obj::IsSceneValid(void) const
{
	return (m_pScene != null_ptr);
}

Scene & Obj::GetScene(void) const
{
	AssertEx(m_pScene != null_ptr, "");
	return *m_pScene;
}

void Obj::SetScene(Scene *pScene)
{
	m_pScene = pScene;
}
CopyScene* Obj::GetCopyScene(void) const
{
	if (!IsSceneValid())
	{
		return null_ptr;
	}
	if (!GetScene().IsCopyScene())
	{
		return null_ptr;
	}
	return static_cast<CopyScene*>(m_pScene);
}


bool Obj::IsCharacter(void)
{
	switch (GetObjType())
	{
	case ObjType::HERO:
	case ObjType::NPC:
	case ObjType::TROOP:
		{
			return true;
		}
		break;
	default:
		{
			return false;
		}
		break;
	}
}

bool Obj::IsMarch(void)
{
	return (GetObjType() == ObjType::MARCH);
}

bool Obj::IsNpc(void)
{
	switch (GetObjType())
	{
	case ObjType::HERO:
	case ObjType::NPC:
	case ObjType::TROOP:
		{
			return true;
		}
		break;
	default:
		{
			return false;
		}
		break;
	}
}

bool Obj::IsHero(void)
{
	return (GetObjType() == ObjType::HERO);
}
bool Obj::IsSoldier(void)
{
	return (GetObjType() == ObjType::TROOP);
}

bool Obj::IsSnareObj(void)
{
	return (GetObjType() == ObjType::SNAREOBJ);
}



