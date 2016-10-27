
#ifndef _GAMEPLAYERMANAGER_H_
#define _GAMEPLAYERMANAGER_H_

#include "PlayerManager.h"

class LoginService;


class GamePlayerManager : public PlayerManager
{
public:
	explicit GamePlayerManager(LoginService &rLoginService);
	 ~GamePlayerManager(void);

private:
	LoginService &m_rLoginService;
public:
	virtual void ProcessTicks(const TimeInfo &rTimeInfo);

protected:
	virtual void OnAddPlayer(PlayerPtr Ptr,int nResult);
	virtual void OnDelPlayer(PlayerPtr Ptr,int nResult);

public:
	PlayerPtr GetPlayerByID(int64 nID);
	PlayerPtr PopPlayerByStatusFOrEnterWorld(void);
};



#endif