
#ifndef _GAMEPLAYERMANAGER_H_
#define _GAMEPLAYERMANAGER_H_

#include "PlayerManager.h"

class WorldUserService;


class GamePlayerManager : public PlayerManager
{
public:
	explicit GamePlayerManager(WorldUserService &rWorldService);
	 ~GamePlayerManager(void);

private:
	WorldUserService &m_rWorldService;
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