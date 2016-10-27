
#ifndef _GAMESTRUCT_WORLDMAP_H_
#define _GAMESTRUCT_WORLDMAP_H_

#include "Base.h"
#include "DBStruct/DBStruct_WordMap.h"


class TileInfo
{
public:
	TileInfo();
	virtual ~TileInfo(void);

public:
	void SerializeToDB(DBTile& rDest) const;
	void SerializeFromDB(const DBTile& rSource);

public:

	// 地块ID
	int    GetID() const {return m_tileID;}
	void   SetID(int val){m_tileID = val;}

	// X坐标
	int    GetPosX() const {return m_nPosX;}
	void   SetPosX(int val) {m_nPosX = val;}
	
	// Y坐标
	int    GetPosY() const {return m_nPosY;}
	void   SetPosY(int val){m_nPosY = val;}

	//  所属Block
	int    GetBlock() const {return m_nBlock;}
	void   SetBlock(int val) {m_nBlock = val;}

	// 地块类型
	int    GetType() const {return m_nType;}
	void   SetType(int val){m_nType = val;}

	// 城市ID
	int    GetCityID() const {return m_nCityId;}
	void   SetCityID(int val){m_nCityId = val;}

	// 玩家ID
	int64  GetPlayerID() const {return m_nPlayerId;}
	void   SetPlayerID(int val) {m_nPlayerId = val;}
private:
	
	int m_tileID; //地块ID
	int m_nPosX;  // X坐标
	int m_nPosY;  // Y坐标
	int m_nBlock; // 所属Block
	int m_nType;  // 地块类型
	int m_nCityId; // 城市ID
	int64 m_nPlayerId; // 玩家ID

};

typedef std::map<int,TileInfo> TileMap;

#endif