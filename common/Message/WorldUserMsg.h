#ifndef _WORLDUSERMSG_H_
#define _WORLDUSERMSG_H_

#include "service/Message.h"
#include "Player/Player.h"
#include "Scene/GameInterface_Scene.h"

MESSAGE_DEF_BEGIN(PlayerEnterWorldMsg)
	PlayerPtr m_PlayerPtr;
MESSAGE_DEF_END(PlayerEnterWorldMsg)

MESSAGE_DEF_BEGIN(PlayerLeaveWorldMsg)
	PlayerPtr m_PlayerPtr;
	int m_nDelResult;
	int64 m_guid;
MESSAGE_DEF_END(PlayerLeaveWorldMsg)


MESSAGE_DEF_BEGIN(PlayerQuitGameMsg)
	PlayerPtr m_PlayerPtr;
tint32 m_nDelResult;
MESSAGE_DEF_END(PlayerQuitGameMsg)

#endif
