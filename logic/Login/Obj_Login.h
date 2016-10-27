
#ifndef _OBJ_LOGIN_H_
#define _OBJ_LOGIN_H_

#include "Base.h"
#include "Service/TimeInfo.h"
#include "DBStruct/DBStruct_User.h"
#include "scene/GameDefine_Scene.h"

class Player;
class Packet;

class CG_LOGIN;


class Obj_Login
{
public:
	Obj_Login(Player &Player);
	virtual ~Obj_Login(void){};

public:
	const ACCOUNTNAME GetAccount() const {return m_szAccount;}

private:

	Player &m_rPlayer;

private:

	ACCOUNTNAME  m_szAccount;

private:
	DBFullUserData m_charData;

public:
	tuint32 HandlePacket(::CG_LOGIN &rPacket);

};



#endif