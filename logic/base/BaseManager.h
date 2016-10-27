#ifndef _BASEMANAGER_H_
#define _BASEMANAGER_H_
#pragma once

class Player;
class DB_Player;

class BaseManager
{
public:
	BaseManager(Player *player)
	: m_pPlayer(player)
	{

	}
	virtual ~BaseManager(void){};

	virtual void	Init() = 0;
	virtual void	LoadDB(DB_Player *pdbPlayer) = 0;
	virtual void	SaveDB(DB_Player *pdbPlayer) = 0;

protected:
	Player              *m_pPlayer;
};

#endif
