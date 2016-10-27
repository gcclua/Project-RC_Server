
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
	 void Load(const DBTileData& rData);
	 void Save(DBTileData& rData);

public:

	// ����ؿ���Ϣ
	void Tick_Save(const TimeInfo &rTimeInfo);

public:
	// �ؿ����
	virtual void HandleMessage(const DBRetLoadTileDataMsg &rMsg);

private:
	TileInfo* GetTileInfo(int tileId);

private:

	// ���洢�ĵؿ���Ϣ
	typedef std::list<int> SaveTileList;
	SaveTileList  m_lstSaveTile;

	// ���ݴ洢ʱ��
	int m_nDataSaveSec;

private:
	TileMap m_TileList;
};


typedef GeneralInvoker<WorldMapService,200,200> WorldMapInvoker;


#endif