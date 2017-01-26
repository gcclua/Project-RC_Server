#include "Scene.h"
#include "Scene/GameInterface_Scene.h"
#include "Message/ChatMsg.h"
#include "Message/SceneMsg.h"
#include "Message/DBMsg.h"
#include "service/MessageOp.h"

//////////////////////////////////////////////////////////////////////////
//��Ҫ����ת����March�����Message����

//MESSAGE_TRANSPORTTOMARCH_IMPL(MarchReqNearListMsg);
MESSAGE_TRANSPORTTOMARCH_IMPL(MarchMoveMsg);
//MESSAGE_TRANSPORTTOMARCH_GUID_IMPL(MarchOpenCopySceneMsg);
//MESSAGE_TRANSPORTTOMARCH_GUID_IMPL(AskJoinCopySceneMsg);


void Scene::HandleMessage(const MarchOpenCopySceneMsg &rMsg)
{
	__ENTER_FUNCTION
	Obj_MarchPtr Ptr = GetMarchByGuid(rMsg.m_ReceiverGuid); 
		if (Ptr && Ptr->GetPlayerId()>0 ) 
		{ 
		Ptr->HandleMessage(rMsg); 
		} 
	__LEAVE_FUNCTION
}

void Scene::HandleMessage(const ReqMarchSetPosMsg &rMsg)
{
	__ENTER_FUNCTION
		Obj_MarchPtr Ptr = GetMarchByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr && Ptr->GetPlayerId()>0 ) 
	{ 
		Ptr->HandleMessage(rMsg); 
	} 
	__LEAVE_FUNCTION
}

void Scene::HandleMessage(const AskJoinCopySceneMsg &rMsg)
{
	__ENTER_FUNCTION
	Obj_MarchPtr Ptr = GetMarchByGuid(rMsg.m_ReceiverGuid); 
	if (Ptr && Ptr->GetPlayerId()>0 ) 
	{ 
		Ptr->HandleMessage(rMsg); 
	} 
__LEAVE_FUNCTION
}

void Scene::HandleMessage(const MarchReqNearListMsg &rMsg)
{
	__ENTER_FUNCTION
		//ɨ�����ǰ�����������
		MarchRefCont Cont;
		Scan_March_All(Cont);

	//�޳��Լ�
	//Cont.RemoveByPred(Pred_ObjIDEqual(GetID()));

	if (Cont.Size() > 0)
	{
		//��෢��20����ҵ���Ϣ
		if (Cont.Size() > 20)
		{
			Cont.ReduceSize(20);
		}

		MarchRetNearListMsgPtr MsgPtr = POOLDEF_NEW(MarchRetNearListMsg);
		AssertEx(MsgPtr,"");
		//MsgPtr->m_nObjId = GetID();
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
			MsgPtr->m_BaseMarchVec[i].m_fPosX  = rMarch.GetScenePos().m_fX;
			MsgPtr->m_BaseMarchVec[i].m_fPosZ  = rMarch.GetScenePos().m_fZ;
			nRealCount ++;
		}

		SendMessage2User(rMsg.m_ReceiverGuid,MsgPtr);
	}
	__LEAVE_FUNCTION
}


