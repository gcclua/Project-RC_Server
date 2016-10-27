#ifndef _TRANSPORTMSG_H_
#define _TRANSPORTMSG_H_

#include "service/Message.h"
#include "scene/GameStruct_Scene.h"

MESSAGE_DEF_BEGIN(TransportToMarch)
	MessagePtr m_mp;
MESSAGE_DEF_END(TransportToMarch)

MESSAGE_DEF_BEGIN(TransportToAllScene)
	MessagePtr m_mp;
MESSAGE_DEF_END(TransportToAllScene)

MESSAGE_DEF_BEGIN(TransportToSceneClass)
	SceneClassID m_nClassID;
	MessagePtr m_mp;
MESSAGE_DEF_END(TransportToSceneClass)

MESSAGE_DEF_BEGIN(TransportToSceneInst)
	SceneID m_SceneID;
	MessagePtr m_mp;
MESSAGE_DEF_END(TransportToSceneInst)

MESSAGE_DEF_BEGIN(TransportToUser)
	MessagePtr m_mp;
MESSAGE_DEF_END(TransportToUser)

#endif
