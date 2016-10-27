#ifndef _TROOPMANAGER_H_
#define _TROOPMANAGER_H_

#pragma once

#include "../BaseManager.h"
#include "service/TimeInfo.h"
#include "troop/GameStruct_Troop.h"


class TroopManager : public BaseManager
{
public:
	TroopManager(User &rUser);
	virtual ~TroopManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	void		OnLogin();

protected:

	TroopPtrMap     m_MapTroop;
};


#endif
