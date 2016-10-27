#include "Scene.h"
#include "Message/SceneMsg.h"
#include "service/MessageOp.h"

void Scene::BroadCast(MessagePtr MsgPtr)
{
	__ENTER_FUNCTION

	MarchRefCont Cont;
	Scan_March_All(Cont);
	for (int i = 0; i < Cont.Size(); i++)
	{
		SendMessage2User(Cont[i].GetPlayerId(),MsgPtr);
	}

	__LEAVE_FUNCTION
}

void Scene::BroadCast_Except(MessagePtr MsgPtr, int nObjID)
{
	__ENTER_FUNCTION

	MarchRefCont Cont;
	Scan_March_All(Cont);
	for (int i = 0; i < Cont.Size(); i++)
	{
		if (Cont[i].GetID() != nObjID)
		{
			SendMessage2User(Cont[i].GetPlayerId(),MsgPtr);
		}
	}

	__LEAVE_FUNCTION
}

void Scene::BroadCast_InSight_Include(MessagePtr MsgPtr, int nObjID)
{
	__ENTER_FUNCTION
		AssertEx(MsgPtr,"");
	MarchRefCont Cont;
	Scan_March_All(Cont);
	for (int i = 0; i < Cont.Size(); i++)
	{
		if (Cont[i].IsInSight(nObjID))
		{
			SendMessage2User(Cont[i].GetPlayerId(),MsgPtr);
		}
	}

	__LEAVE_FUNCTION
}

void Scene::BroadCast_InSight_Except(MessagePtr MsgPtr, int nObjID)
{
	__ENTER_FUNCTION
		AssertEx(MsgPtr,"");
	MarchRefCont Cont;
	Scan_March_All(Cont);
	for (int i = 0; i < Cont.Size(); i++)
	{
		if (Cont[i].GetID() != nObjID)
		{
			if (Cont[i].IsInSight(nObjID))
			{
				SendMessage2User(Cont[i].GetPlayerId(),MsgPtr);
			}
		}
	}

	__LEAVE_FUNCTION
}
