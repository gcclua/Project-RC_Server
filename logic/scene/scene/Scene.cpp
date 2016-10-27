#include "Scene.h"
#include "Service/MessageOp.h"
#include "Message/ChatMsg.h"
#include "Packet/Packet/GC_CHAT_PAK.h"
#include "Packet/Packet/GC_NOTICE_PAK.h"
#include "Table/Table_SceneClass.h"
#include "DictionaryFormat/DictionaryFormat.h"
#include "Scene/GameInterface_SceneActivation.h"
#include "Common/Pool.h"

Scene::Scene( void )
{
	m_nClassID = invalid_id;
	m_nInstID = invalid_id;

	m_nCurPlayerCount = 0;
	m_nEnteringPlayerCount = 0;

	m_nMaxPlayerCountA = 0;
	m_nMaxPlayerCountB = 0;

	m_nObjIDAlloc = SCENEOBJIDMIN;

	m_pSceneObstacle = null_ptr;
}

Scene::~Scene( void )
{

}

void Scene::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	ServiceCell::Tick(rTimeInfo);
	Tick_Obj(rTimeInfo);
	
	__LEAVE_FUNCTION
}

void Scene::Tick_Obj(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	Tick_AddObjs();
	Tick_RunObjs(rTimeInfo);
	Tick_DelObjs();

	__LEAVE_FUNCTION
}

void Scene::Tick_AddObjs(void)
{
	__ENTER_FUNCTION

	int nCount = static_cast<int>(m_AddingCacheObjPtrVec.size());
	for (int i = 0; i < nCount; i++)
	{
		_AddNonUserObjImmediate(m_AddingCacheObjPtrVec[i]);
	}
	m_AddingCacheObjPtrVec.clear();

	__LEAVE_FUNCTION
}

void Scene::Tick_DelObjs(void)
{
	__ENTER_FUNCTION

	for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); )
	{
		ObjPtr Ptr = it->second;
		AssertEx(Ptr, "");
		if (Ptr->GetActive())
		{
			it++;
		}
		else
		{
			it = _DelNonUserObjImmediate(it);
		}
	}

	__LEAVE_FUNCTION
}

void Scene::Tick_RunObjs(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION

	for (ObjPtrMap::iterator it = m_ObjPtrMap.begin(); it != m_ObjPtrMap.end(); it++)
	{
		ObjPtr Ptr = it->second;
		AssertEx(Ptr, "");
		if (Ptr->GetActive())
		{
			Ptr->Tick(rTimeInfo);
		}
	}

	__LEAVE_FUNCTION
}

void Scene::SetCurPlayerCount(int nCurPlayerCount)
{
	__ENTER_FUNCTION

	m_nCurPlayerCount = nCurPlayerCount;

	SceneActivationInterface::UpdateSceneClassInstPlayerCount(GetSceneClassID(), GetSceneInstID(), m_nCurPlayerCount);

	__LEAVE_FUNCTION
}

void Scene::HandleMessage(const MarchEnterSceneMsg &rMsg)
{
	__ENTER_FUNCTION


	DecEnteringPlayerCount();

	__LEAVE_FUNCTION
}

void Scene::Initialize(void)
{
	__ENTER_FUNCTION

	NpcInit();
	OnSceneCreate();
	__LEAVE_FUNCTION
}


bool Scene::FindPath(const ScenePos &rPosStart, const ScenePos &rPosEnd, PathCont &rPathCont)
{
	__ENTER_FUNCTION

	if (rPosStart.Distance(rPosEnd) >= 0.1f)
	{
		rPathCont.CleanUp();
		rPathCont.PushBack(PathNode(rPosStart, rPosEnd));
		return true;
	}
	else
	{
		return false;
	}

	__LEAVE_FUNCTION
	return false;
}

bool Scene::FindStraight(const ScenePos &rPosStart, const ScenePos &rPosEnd, ScenePos &rPosEndRefixed)
{
	__ENTER_FUNCTION

	float nTotalDistance = rPosStart.Distance(rPosEnd);
	if (nTotalDistance >= 0.1f)
	{
		rPosEndRefixed = rPosStart;

		const SceneObstacle &rSceneObstacle = GetSceneObstacle();
		float fDirection = CalcDirection(rPosStart, rPosEnd);

		for (int i = 0; i < 128; i++)
		{
			float nCurDistance = static_cast<float>(i * 0.5f);
			if (nCurDistance < nTotalDistance)
			{
				ScenePos StepPos;
				StepPos.m_fX = rPosStart.m_fX + nCurDistance * ::cos(fDirection);
				StepPos.m_fZ = rPosStart.m_fZ + nCurDistance * ::sin(fDirection);
				if (rSceneObstacle.GetObstacleValue(StepPos) == ObstacleValue::WALKABLE)
				{
					rPosEndRefixed = StepPos;
					continue;
				}
				else
				{
					break;
				}
			}
			else
			{
				if (rSceneObstacle.GetObstacleValue(rPosEnd) == ObstacleValue::WALKABLE)
				{
					rPosEndRefixed = rPosEnd;
					break;
				}
				else
				{
					break;
				}
			}
		}

		return true;
	}
	else
	{
		rPosEndRefixed = rPosStart;
		return false;
	}

	__LEAVE_FUNCTION
	return false;
}

bool Scene::FindDest(const ScenePos& rPosStart, const ScenePos &rPosEnd, ScenePos &rPosEndRefixed)
{
	__ENTER_FUNCTION
	float fTotalDistance = rPosStart.Distance(rPosEnd);
	if (fTotalDistance >= 0.1f)
	{
		const SceneObstacle &rSceneObstacle = GetSceneObstacle();
		if (rSceneObstacle.GetObstacleValue(rPosStart) == ObstacleValue::WALKABLE &&
			rSceneObstacle.GetObstacleValue(rPosEnd) == ObstacleValue::WALKABLE)
		{
			rPosEndRefixed = rPosEnd;
			return true;
		}

		float fDirection = CalcDirection(rPosStart, rPosEnd);
		//如果做不了，进行一个递减，保证玩家可以使用轻功
		for (float fDis = fTotalDistance; fDis > 0.1f; fDis -= 0.5f)
		{
			ScenePos StepPos;
			StepPos.m_fX = rPosStart.m_fX + fDis * ::cos(fDirection);
			StepPos.m_fZ = rPosStart.m_fZ + fDis * ::sin(fDirection);
			if (rSceneObstacle.GetObstacleValue(StepPos) == ObstacleValue::WALKABLE)
			{
				rPosEndRefixed = StepPos;
				return true;
			}
		}
	}
	__LEAVE_FUNCTION
	return false;
}

bool Scene::IsScenePosWalkAble( const ScenePos &rScenePos)//坐标点是否是可以行走的点
{
	__ENTER_FUNCTION
	const SceneObstacle &rSceneObstacle = GetSceneObstacle();
	if (rSceneObstacle.GetObstacleValue(rScenePos) == ObstacleValue::WALKABLE)
	{
		return true;
	}
	return false;
	__LEAVE_FUNCTION
	return false;
}

