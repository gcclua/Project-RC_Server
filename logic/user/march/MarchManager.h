#ifndef _MARCHMANAGER_H_
#define _MARCHMANAGER_H_

#pragma once

#include "../BaseManager.h"
#include "service/TimeInfo.h"
#include "march/GameStruct_March.h"

class GC_MarchList;
class GC_MarchData;

class MarchManager : public BaseManager
{
public:
	MarchManager(User &rUser);
	virtual ~MarchManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	void		OnLogin();
public:
	void    FileData(GC_MarchList* pMarchList);


private:
	void    FileSingMarch(MarchPtr Ptr,GC_MarchData * pMarchData);

public:

	// 初始marchinfo
	bool        InitMarchInfo(int64 nBuildId,const TroopList_T& rTroopList,const Hero& rHero,March& rMarch);

	// 更新march的状态
	bool        UpdateMarchState(int64 nMarchId,int nState);

	// 检测某个兵营或者城墙能否驻扎英雄
	bool        CheckAssignHero(int64 nMarchId);
	// 将一个英雄驻扎到兵营或者城墙
	void        AssignHeroToMarch(int64 nMarchId,const Hero& rHero);

	// 从城市中派遣一队兵到大地图
	bool       CheckSendMarchIntoMap(int64 nMarchId);

	// 更新march数据
	bool       UpdateMarchData(const March &rMarch);

public:

	MarchPtr      GetMarchInfo(int64 nMarchId);

public:
	bool        AddTroop(int64 nMarchId,int nType,int nHp);

protected:

	MarchPtrMap     m_mapMarch;
	// 建筑与march的映射表，现在跟策划的前提是一个兵营有且只有一个march，扩march就的扩兵营
	BuildMarchMap   m_mapBuildMarch;
};

#endif
