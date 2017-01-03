
#ifndef _LOGINPLAYERMANAGER_H_
#define _LOGINPLAYERMANAGER_H_

#include "PlayerManager.h"

class LoginService;


class LoginPlayerManager : public PlayerManager
{
public:
	explicit LoginPlayerManager(LoginService &rLoginService);
	 ~LoginPlayerManager(void);

private:
	LoginService &m_rLoginService;
public:
	virtual void ProcessTicks(const TimeInfo &rTimeInfo);

protected:
	virtual void OnAddPlayer(PlayerPtr Ptr,int nResult);
	virtual void OnDelPlayer(PlayerPtr Ptr,int nResult);

public:
	PlayerPtr GetPlayerByID(int nID);
	PlayerPtr PopPlayerByStatusFOrEnterWorld(void);
};



#endif