
#ifndef __DBSTRUCT_WORLDMAP_H__
#define __DBSTRUCT_WORLDMAP_H__

#include "DBStruct.h"
#include "worldmap/GameDefine_WorldMap.h"



//��Ҫ����Ľ�ɫ����
struct DBTile
{
public:
	DBTile(){CleanUp();};
	~DBTile(){};

	void CleanUp( );
	void CopyFrom(const DBTile& rSource);

public:
	int m_tileID; //�ؿ�ID
	int m_nPosX;  // X����
	int m_nPosY;  // Y����
	int m_nBlock; // ����Block
	int m_nType;  // �ؿ�����
	int m_nCityId; // ����ID
	int64 m_nPlayerId; // 

	
};

typedef DBCommonData<DBTile> DBTileData;
typedef boost::shared_ptr<DBTileData> DBTileDataPtr;


#endif
