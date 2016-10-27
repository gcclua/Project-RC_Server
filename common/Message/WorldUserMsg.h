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
MESSAGE_DEF_END(PlayerLeaveWorldMsg)



#endif
