#ifndef _CITYMANAGER_H_
#define _CITYMANAGER_H_

#pragma once

#include "../BaseManager.h"

#include "city/GameStruct_City.h"

#include "Scene/GameStruct_Scene.h"

class GC_CityData;
class GC_Building_LevelUp;
class GC_Troop_Train;

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

	// 建筑升级
	bool       BuildLevelUp(int64 nBuildId,GC_Building_LevelUp* pMessage);

	// 开始训练兵
	bool       BeginTrainTroop(int64 nBuildId,int nQueueIndex,int nType,int Count,GC_Troop_Train* pMessage);



public:
	void    FileData(GC_CityData* pCityData);


protected:

	CityPtr     m_CityPtr;
};


#endif
