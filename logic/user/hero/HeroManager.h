#ifndef _HEROMANAGER_H_
#define _HEROMANAGER_H_

#pragma once

#include "../BaseManager.h"
#include "service/TimeInfo.h"
#include "hero/GameStruct_Hero.h"


class HeroManager : public BaseManager
{
public:
	HeroManager(User &rUser);
	virtual ~HeroManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	void		OnLogin();

protected:

	HeroPtrMap     m_MapHero;
};


#endif
