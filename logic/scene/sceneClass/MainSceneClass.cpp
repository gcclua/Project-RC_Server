#include "MainSceneClass.h"
#include "Message/SceneMsg.h"
#include "Scene/GameInterface_SceneActivation.h"

POOLDEF_IMPL(MainSceneClass);
MainSceneClass::MainSceneClass( void )
{

}

MainSceneClass::~MainSceneClass( void )
{

}

SceneClass::EnterResult MainSceneClass::EnterTo(const March& rMarch, tint32 nSceneInst)
{
	__ENTER_FUNCTION

	if (nSceneInst > invalid_id &&
		nSceneInst < (tint32)m_ScenePtrVec.size())
	{
		AssertEx(m_ScenePtrVec[nSceneInst], "");

		MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_bFirstEnter = true;
		MsgPtr->m_March = rMarch;
		SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

		return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));
	}

	//进入指定的场景实例失败，返回false，上层会继续处理
	return std::make_pair(false, SceneID(invalid_id, invalid_id));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::EnterResult MainSceneClass::EnterTo(const March& rMarch)
{
	__ENTER_FUNCTION

	tint32 nSceneInst = ReusingScene();
	if (nSceneInst <= invalid_id)
	{
		nSceneInst = EnlargeScene();
	}

	AssertEx(nSceneInst > invalid_id, "");
	AssertEx(nSceneInst < (tint32)m_ScenePtrVec.size(), "");

	MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_bFirstEnter = true;
	MsgPtr->m_March = rMarch;
	SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

	return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::EnterResult MainSceneClass::FirstEnterTo(const March& rMarch)
{
	__ENTER_FUNCTION

	AssertEx(false, "");
	return std::make_pair(false, SceneID(invalid_id, invalid_id));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::ChangeResult MainSceneClass::ChangeTo(const March& rMarch, tint32 nSceneInst)
{
	__ENTER_FUNCTION

	if (nSceneInst > invalid_id &&
		nSceneInst < (tint32)m_ScenePtrVec.size())
	{
		AssertEx(m_ScenePtrVec[nSceneInst], "");

		MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_bFirstEnter = false;
		MsgPtr->m_March = rMarch;
		SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

		return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));
	}

	//进入指定的场景实例失败，返回false，上层会继续处理
	return std::make_pair(false, SceneID(invalid_id, invalid_id));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

SceneClass::ChangeResult MainSceneClass::ChangeTo(const March& rMarch)
{
	__ENTER_FUNCTION

	tint32 nSceneInst = ReusingScene();
	if (nSceneInst <= invalid_id)
	{
		nSceneInst = EnlargeScene();
	}

	AssertEx(nSceneInst > invalid_id, "");
	AssertEx(nSceneInst < (tint32)m_ScenePtrVec.size(), "");

	MarchEnterSceneMsgPtr MsgPtr = POOLDEF_NEW(MarchEnterSceneMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_bFirstEnter = false;
	MsgPtr->m_March = rMarch;
	SendMarchEnterSceneMessage(nSceneInst, MsgPtr);

	return std::make_pair(true, SceneID(GetSceneClassID(), nSceneInst));

	__LEAVE_FUNCTION
	return std::make_pair(false, SceneID(invalid_id, invalid_id));
}

bool MainSceneClass::ChangeFromCheck(const SceneID &rsid, const int64 &rGuid)
{
	__ENTER_FUNCTION

	return ((rsid.m_nClassID == m_nClassID) &&
		(rsid.m_nInstID >= 0) &&
		(rsid.m_nInstID < (tint32)m_ScenePtrVec.size()));

	__LEAVE_FUNCTION
	return false;
}

bool MainSceneClass::ChangeToCheck(const SceneID &rsid, const int64 &rGuid)
{
	__ENTER_FUNCTION

	if (rsid.m_nClassID == m_nClassID)
	{
		if (rsid.m_nInstID > invalid_id)
		{
			if (rsid.m_nInstID >= 0 &&
				rsid.m_nInstID < (tint32)m_ScenePtrVec.size())
			{
				AssertEx(m_ScenePtrVec[rsid.m_nInstID], "");
				return true;
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


tint32 MainSceneClass::ReusingScene(void)
{
	__ENTER_FUNCTION

	return 0;

	__LEAVE_FUNCTION
	return invalid_id;
}

tint32 MainSceneClass::EnlargeScene(void)
{
	__ENTER_FUNCTION

	SceneClassID nClassID = GetSceneClassID();
	SceneInstID nInstID = static_cast<SceneInstID>(m_ScenePtrVec.size());
	tint32 nInstCount = static_cast<tint32>(m_ScenePtrVec.size() + 1);

	MainScenePtr ssp = POOLDEF_NEW(MainScene);
	AssertEx(ssp, "");
	ssp->SetSceneClassID(nClassID);
	ssp->SetSceneInstID(nInstID);
	ssp->SetSceneObstacle(&m_SceneObstacle);

	ScenePtr sp = boost::static_pointer_cast<Scene, MainScene>(ssp);
	AssertEx(sp, "");
	m_ScenePtrVec.push_back(sp);

	InvokerPtr InvPtr = sp->InitMyself();
	AddSceneInvoker(InvPtr);

	SceneActivationInterface::UpdateSceneClassInstCount(GetSceneClassID(), GetSceneInstCount());

	return nInstID;

	__LEAVE_FUNCTION
	return invalid_id;
}
