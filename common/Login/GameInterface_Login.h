#ifndef _GAMEINTERFACE_LOGIN_H_
#define _GAMEINTERFACE_LOGIN_H_

#include "Base.h"
#include "Scene/GameDefine_Scene.h"

class LoginInterface
{
public:
	static void KickPlayerByAccount(const ACCOUNTNAME &rAccount, tint32 nReason);
	static void ModifyVipCost(int64 rGuid, tint32 nVipCost);
};

#endif
