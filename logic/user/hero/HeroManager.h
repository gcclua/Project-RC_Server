#ifndef _HEROMANAGER_H_
#define _HEROMANAGER_H_

#pragma once

#include "../BaseManager.h"
#include "service/TimeInfo.h"
#include "hero/GameStruct_Hero.h"

class GC_HeroList;


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

public:
	// 检测hero是否可以任命到兵营或者防守
	bool       CheckAssignHero(int64 nHeroId);
	bool       AssignHeroToMarch(int64 nHeroId,int64 nMarchId);

	bool       CheckAssignHero(int64 nMarchId,int64 nHeroId);

	// 取消英雄任命
	bool       UnAssignHero(int64 nHeroId);

public:
	void    FileData(GC_HeroList* pHeroList);

public:
	bool        AddHero(int nType,int nLevel);
	HeroPtr     GetHero(int64 nHeroId);

private:
	void        InitHero(HeroPtr Ptr);
	bool        AddHero(HeroPtr Ptr);
	

protected:

	HeroPtrMap     m_mapHero;
};

#endif
