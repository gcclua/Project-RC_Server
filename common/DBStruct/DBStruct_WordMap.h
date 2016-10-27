
#ifndef __DBSTRUCT_WORLDMAP_H__
#define __DBSTRUCT_WORLDMAP_H__

#include "DBStruct.h"
#include "worldmap/GameDefine_WorldMap.h"



//需要保存的角色数据
struct DBTile
{
public:
	DBTile(){CleanUp();};
	~DBTile(){};

	void CleanUp( );
	void CopyFrom(const DBTile& rSource);

public:
	int m_tileID; //地块ID
	int m_nPosX;  // X坐标
	int m_nPosY;  // Y坐标
	int m_nBlock; // 所属Block
	int m_nType;  // 地块类型
	int m_nCityId; // 城市ID
	int64 m_nPlayerId; // 

	
};

typedef DBCommonData<DBTile> DBTileData;
typedef boost::shared_ptr<DBTileData> DBTileDataPtr;


#endif
