
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

//将消息发送给一个服务的实例
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

//将消息发送给一个用int64标识的March
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
//将消息发送给一个用int64标识的玩家
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

//将消息发送给所有的游戏场景
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

//将消息发送给一个用SceneClassID标识的场景的所有实例
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

//将消息发送给一个用SceneID标识的场景实例
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