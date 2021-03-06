
#ifndef _WORLDMAPSERVICE_H_
#define _WORLDMAPSERVICE_H_

#include "Base.h"
#include "service/Invoker.h"
#include "service/Service.h"
#include "worldmap/GameStruct_WorldMap.h"

class DBRetLoadTileDataMsg;


class WorldMapService :public Service
{
public:
	explicit WorldMapService();
	virtual ~WorldMapService(void);


public:
	virtual int GetServiceID(void){return ServiceID::WORLDMAP;}

public:
	virtual void Init(void);
	virtual void Tick(const TimeInfo &rTimeInfo);

protected:
	virtual void Openup(void);
	virtual void Shutdown(void);

private:
	 void LoadTile(const DBTileData& rData);
	 void Save(DBTileData& rData);

public:

	// 保存地块信息
	void Tick_Save(const TimeInfo &rTimeInfo);

public:
	TileInfoPtr GetPlainTile();

public:
	// 地块加载
	virtual void HandleMessage(const DBRetLoadTileDataMsg &rMsg);
	virtual void HandleMessage(const ReqIdleTileMsg &rMsg);
	virtual void HandleMessage(const ReqSetTileOwerMsg &rMsg);


private:
	TileInfoPtr GetTileInfo(int tileId);

private:
	void PushSaveList(TileInfoPtr Ptr);

private:

	// 待存储的地块信息
	typedef std::map<int,TileInfoPtr> SaveTileList;
	SaveTileList  m_lstSaveTile;

	// 数据存储时间
	int m_nDataSaveSec;

private:
	TileMap m_TileList;
};


typedef GeneralInvoker<WorldMapService,200,200> WorldMapInvoker;


#endif