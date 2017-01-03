
#ifndef _MESSAGEOP_H_
#define _MESSAGEOP_H_

#include "Base.h"
#include "ServiceDefine.h"
#include "BaseService.h"
#include "Message.h"
#include "ServiceManager.h"
#include "scene/GameStruct_Scene.h"
#include "Message/TransportMsg.h"
#include "Message/WorldUserMsg.h"

//����Ϣ���͸�һ�������ʵ��
template<typename _MessagePtrT>
void SendMessage2Srv(BaseService &rService,_MessagePtrT &rPtr)
{
	AssertEx(rPtr,"");
	AssertEx((rPtr->m_nCount)++ ==0,"");
	ConstMessagePtr csp = boost::static_pointer_cast<const Message, typename _MessagePtrT::element_type>(rPtr);
	rService.ReceiveMessage(csp);
	rPtr.reset();
}

template<typename _MessagePtrT>
void SendMessage2Srv(int nServiceID,_MessagePtrT &rPtr)
{
	AssertEx(rPtr,"");
	AssertEx((rPtr->m_nCount)++ ==0,"");
	ConstMessagePtr csp = boost::static_pointer_cast<const Message, typename _MessagePtrT::element_type>(rPtr);
	gServiceManager.ReceiveMessage(nServiceID,csp);
	rPtr.reset();
}

//����Ϣ���͸�һ����int64��ʶ��March
template<typename _MessagePtrT>
void SendMessage2March(int64 guid, _MessagePtrT &rPtr)
{
	AssertEx(rPtr, "");
	AssertEx((rPtr->m_nCount)++ == 0, "");

	MessagePtr sp = boost::static_pointer_cast<Message, typename _MessagePtrT::element_type>(rPtr);
	sp->m_ReceiverGuid = guid;
	TransportToMarchPtr MsgPtr = POOLDEF_NEW(TransportToMarch);
	AssertEx(MsgPtr, "");
	MsgPtr->m_mp = sp;
	SendMessage2Srv(ServiceID::SCENE, MsgPtr);

	rPtr.reset();
}
//����Ϣ���͸�һ����int64��ʶ�����
template<typename _MessagePtrT>
void SendMessage2User(int64 guid, _MessagePtrT &rPtr)
{
	AssertEx(rPtr, "");
	AssertEx((rPtr->m_nCount)++ == 0, "");
	rPtr->m_ReceiverGuid = guid;
	ConstMessagePtr csp = boost::static_pointer_cast<const Message, typename _MessagePtrT::element_type>(rPtr);
	gServiceManager.ReceiveMessage(ServiceID::WORLDUSER,csp);
	rPtr.reset();
}

//����Ϣ���͸����е���Ϸ����
template<typename _MessagePtrT>
void SendMessage2Scene(_MessagePtrT &rPtr)
{
	AssertEx(rPtr, "");
	AssertEx((rPtr->m_nCount)++ == 0, "");

	MessagePtr sp = boost::static_pointer_cast<Message, typename _MessagePtrT::element_type>(rPtr);
	TransportToAllScenePtr MsgPtr = POOLDEF_NEW(TransportToAllScene);
	AssertEx(MsgPtr, "");
	MsgPtr->m_mp = sp;
	SendMessage2Srv(ServiceID::SCENE, MsgPtr);

	rPtr.reset();
}

//����Ϣ���͸�һ����SceneClassID��ʶ�ĳ���������ʵ��
template<typename _MessagePtrT>
void SendMessage2Scene(SceneClassID nClassID, _MessagePtrT &rPtr)
{
	AssertEx(rPtr, "");
	AssertEx((rPtr->m_nCount)++ == 0, "");

	MessagePtr sp = boost::static_pointer_cast<Message, typename _MessagePtrT::element_type>(rPtr);
	TransportToSceneClassPtr MsgPtr = POOLDEF_NEW(TransportToSceneClass);
	AssertEx(MsgPtr, "");
	MsgPtr->m_nClassID = nClassID;
	MsgPtr->m_mp = sp;
	SendMessage2Srv(ServiceID::SCENE, MsgPtr);

	rPtr.reset();
}

//����Ϣ���͸�һ����SceneID��ʶ�ĳ���ʵ��
template<typename _MessagePtrT>
void SendMessage2Scene(SceneID sceneid, _MessagePtrT &rPtr)
{
	AssertEx(rPtr, "");
	AssertEx((rPtr->m_nCount)++ == 0, "");

	MessagePtr sp = boost::static_pointer_cast<Message, typename _MessagePtrT::element_type>(rPtr);
	TransportToSceneInstPtr MsgPtr = POOLDEF_NEW(TransportToSceneInst);
	AssertEx(MsgPtr, "");
	MsgPtr->m_SceneID = sceneid;
	MsgPtr->m_mp = sp;
	SendMessage2Srv(ServiceID::SCENE, MsgPtr);

	rPtr.reset();
}

#endif