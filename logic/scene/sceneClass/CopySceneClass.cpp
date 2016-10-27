#include "CopySceneClass.h"
#include "Message/SceneMsg.h"
#include "Scene/GameInterface_SceneActivation.h"

POOLDEF_IMPL(CopySceneClass);
CopySceneClass::CopySceneClass( void )
{

}

CopySceneClass::~CopySceneClass( void )
{

}

SceneClass::EnterResult CopySceneClass::EnterTo(Obj_MarchPtr Ptr, int nSceneInst)
{
	__ENTER_FUNCTION

	if (nSceneInst > invalid_id && nSceneInst < (int)m_ScenePtrVec.size())
	{
		AssertEx(m_ScenePtrVec[nSceneInst], "");
		if (m_ScenePtrVec[nSceneInst]->GetActive())
		{
			if (m_ScenePtrVec[nSceneInst]->IsCanEnterByGuid(Ptr->GetMarchId()))
			{
				MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
				AssertEx(MsgPtr, "");
				MsgPtr->m_bFirstEnter = true;
				MsgPtr->m_MarchPtr = Ptr;
				SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

				return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));
			}
		}
	}

	//进入指定的场景实例失败，返回false，上层会继续处理
	return std::make_pair(false, SceneID(invalid_id, invalid_id));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::EnterResult CopySceneClass::EnterTo(Obj_MarchPtr Ptr)
{
	__ENTER_FUNCTION

	return std::make_pair(false, SceneID(invalid_id, invalid_id));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::EnterResult CopySceneClass::FirstEnterTo(Obj_MarchPtr Ptr)
{
	__ENTER_FUNCTION

	int nSceneInst = ReusingScene();
	if (nSceneInst <= invalid_id)
	{
		nSceneInst = EnlargeScene();
	}

	AssertEx(nSceneInst > invalid_id, "");
	AssertEx(nSceneInst < (int)m_ScenePtrVec.size(), "");

	AssertEx(m_ScenePtrVec[nSceneInst], "");
	m_ScenePtrVec[nSceneInst]->SetActive();

	MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_bFirstEnter = true;
	MsgPtr->m_MarchPtr = Ptr;
	SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

	return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::ChangeResult CopySceneClass::ChangeTo(Obj_MarchPtr Ptr, int nSceneInst)
{
	__ENTER_FUNCTION

	if (nSceneInst > invalid_id && nSceneInst < (int)m_ScenePtrVec.size())
	{
		AssertEx(m_ScenePtrVec[nSceneInst], "");
		if (m_ScenePtrVec[nSceneInst]->GetActive())
		{
			if (m_ScenePtrVec[nSceneInst]->IsCanEnterByGuid(Ptr->GetMarchId()))
			{
				MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
				AssertEx(MsgPtr, "");
				MsgPtr->m_bFirstEnter = false;
				MsgPtr->m_MarchPtr = Ptr;
				SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

				return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));
			}
		}
	}

	//进入指定的场景实例失败，返回false，上层会继续处理
	return std::make_pair(false, SceneID(invalid_id, invalid_id));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::ChangeResult CopySceneClass::ChangeTo(Obj_MarchPtr Ptr)
{
	__ENTER_FUNCTION

	int nSceneInst = ReusingScene();
	if (nSceneInst <= invalid_id)
	{
		nSceneInst = EnlargeScene();
	}

	AssertEx(nSceneInst > invalid_id, "");
	AssertEx(nSceneInst < (int)m_ScenePtrVec.size(), "");

	AssertEx(m_ScenePtrVec[nSceneInst], "");
	m_ScenePtrVec[nSceneInst]->SetActive();

	MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_bFirstEnter = false;
	MsgPtr->m_MarchPtr = Ptr;
	SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

	return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

bool CopySceneClass::ChangeFromCheck(const SceneID &rsid, const int64 &rGuid)
{
	__ENTER_FUNCTION

	return ((rsid.m_nClassID == m_nClassID) &&
		(rsid.m_nInstID >= 0) &&
		(rsid.m_nInstID < (int)m_ScenePtrVec.size()));

	__LEAVE_FUNCTION
	return false;
}

bool CopySceneClass::ChangeToCheck(const SceneID &rsid, const int64 &rGuid)
{
	__ENTER_FUNCTION

	if (rsid.m_nClassID == m_nClassID)
	{
		if (rsid.m_nInstID > invalid_id)
		{
			if (rsid.m_nInstID >= 0 &&
				rsid.m_nInstID < (int)m_ScenePtrVec.size())
			{
				AssertEx(m_ScenePtrVec[rsid.m_nInstID], "");
				if (m_ScenePtrVec[rsid.m_nInstID]->GetActive())
				{
					if (m_ScenePtrVec[rsid.m_nInstID]->IsCanEnterByGuid(rGuid))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}

	__LEAVE_FUNCTION
	return false;
}

int CopySceneClass::RemainCapacityA(SceneInstID nSceneInst)
{
	return 0;
}

int CopySceneClass::RemainCapacityB(SceneInstID nSceneInst)
{
	return 0;
}

int CopySceneClass::ReusingScene(void)
{
	__ENTER_FUNCTION

	for (int i = 0; i < (int)m_ScenePtrVec.size(); i++)
	{
		AssertEx(m_ScenePtrVec[i], "");
		if (!m_ScenePtrVec[i]->GetActive())
		{
			return i;
		}
	}
	return invalid_id;

	__LEAVE_FUNCTION
	return invalid_id;
}

int CopySceneClass::EnlargeScene(void)
{
	__ENTER_FUNCTION

	SceneClassID nClassID = GetSceneClassID();
	SceneInstID nInstID = static_cast<SceneInstID>(m_ScenePtrVec.size());
	int nInstCount = static_cast<int>(m_ScenePtrVec.size() + 1);

	CopyScenePtr ssp = POOLDEF_NEW(CopyScene);
	AssertEx(ssp, "");
	ssp->SetSceneClassID(nClassID);
	ssp->SetSceneInstID(nInstID);
	ssp->SetMaxPlayerCountA(GetMaxPlayerCountA());
	ssp->SetMaxPlayerCountB(GetMaxPlayerCountB());
	ssp->SetSceneObstacle(&m_SceneObstacle);

	ScenePtr sp = boost::static_pointer_cast<Scene, CopyScene>(ssp);
	AssertEx(sp, "");
	m_ScenePtrVec.push_back(sp);

	InvokerPtr InvPtr = sp->InitMyself();
	AddSceneInvoker(InvPtr);

	SceneActivationInterface::UpdateSceneClassInstCount(GetSceneClassID(), GetSceneInstCount());

	return nInstID;

	__LEAVE_FUNCTION
	return invalid_id;
}
