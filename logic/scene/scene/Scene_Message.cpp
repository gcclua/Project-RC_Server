#include "Scene.h"
#include "Scene/GameInterface_Scene.h"
#include "Message/ChatMsg.h"
#include "Message/SceneMsg.h"
#include "Message/DBMsg.h"

//////////////////////////////////////////////////////////////////////////
//需要场景转发给March的相关Message定义

MESSAGE_TRANSPORTTOMARCH_IMPL(MarchReqNearListMsg);
MESSAGE_TRANSPORTTOMARCH_IMPL(MarchMoveMsg);
//MESSAGE_TRANSPORTTOMARCH_GUID_IMPL(MarchOpenCopySceneMsg);
//MESSAGE_TRANSPORTTOMARCH_GUID_IMPL(AskJoinCopySceneMsg);


void Scene::HandleMessage(const MarchOpenCopySceneMsg &rMsg)
{
	Obj_MarchPtr Ptr = GetMarchByGuid(rMsg.m_ReceiverGuid); 
		if (Ptr && Ptr->GetPlayerId()>0 && Ptr->GetPlayerId()==rMsg.m_ReceiverGuid) 
		{ 
		Ptr->HandleMessage(rMsg); 
		} 
}

void Scene::HandleMessage(const AskJoinCopySceneMsg &rMsg)
{
	Obj_MarchPtr Ptr = GetMarchByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr && Ptr->GetPlayerId()>0 && Ptr->GetPlayerId()==rMsg.m_ReceiverGuid) 
	{ 
		Ptr->HandleMessage(rMsg); 
	} 
}


