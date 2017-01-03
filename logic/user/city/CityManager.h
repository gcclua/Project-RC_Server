#ifndef _CITYMANAGER_H_
#define _CITYMANAGER_H_

#pragma once

#include "../BaseManager.h"

#include "city/GameStruct_City.h"

#include "Scene/GameStruct_Scene.h"

class GC_CityData;

class CityManager : public BaseManager
{
public:
	CityManager(User &rUser);
	virtual ~CityManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	// 登录检验
	void		OnLogin();

public:
	 ScenePos      GetPos();

public:
	// 检测某个兵营或者城墙能否驻扎英雄
	//bool       CheckAssignHero(int64 nBuildId);
	// 将一个英雄驻扎到兵营或者城墙
	//void       AssignHeroToBuild(int64 nBuildId,int64 nHeroId);

	// 从城市中派遣一队兵到大地图
	bool       CheckSendMarchIntoMap(int64 nBuildId);

	// 获得整个队伍信息
	//TroopList_T GetTroopList(int64 nBuildId);

public:
	void    FileData(GC_CityData* pCityData);


protected:

	CityPtr     m_CityPtr;
};


#endif
