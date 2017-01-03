
#ifndef _GAMEDEFINE_USER_H_
#define _GAMEDEFINE_USER_H_

#include "Base.h"

enum EMANAGER_TYPE
{
	EMANAGERTYPE_MIN,
	EMANAGERTYPE_CITY = EMANAGERTYPE_MIN,
	EMANAGERTYPE_INVENTORY,
	EMANAGERTYPE_MARCH,
	EMANAGERTYPE_HERO,
	EMANAGERTYPE_MAX,
};

//////////////////////////////////////////////////////////////////////////
//消息由场景转到玩家
#define MESSAGE_TRANSPORTTOUSER_DECL(MSGTYPE) \
	virtual void HandleMessage(const MSGTYPE &rMsg);
#define MESSAGE_TRANSPORTTOUSER_IMPL(MSGTYPE) \
	void WorldUserService::HandleMessage(const MSGTYPE &rMsg) \
{ \
	UserPtr Ptr = GetUserByGuid(rMsg.m_ReceiverGuid); \
	if (Ptr) \
{ \
	Ptr->HandleMessage(rMsg); \
	} \
	}

#endif