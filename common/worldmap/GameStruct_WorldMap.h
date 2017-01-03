
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
	int64  GetUserId() const {return m_nUserId;}
	void   SetUserId(int64 val) {m_nUserId = val;}

	// 状态
	int    GetState() const {return m_nState;}
	void   SetState(int val){m_nState=val;}

private:
	
	int m_tileID; //地块ID
	int m_nPosX;  // X坐标
	int m_nPosY;  // Y坐标
	int m_nBlock; // 所属Block
	int m_nType;  // 地块类型
	int m_nCityId; // 城市ID
	int64 m_nUserId; // 玩家ID
	int m_nState;  // 状态
	time_t m_lockTime; // 锁定时间

};
typedef boost::shared_ptr<TileInfo> TileInfoPtr;
typedef std::map<int,TileInfoPtr> TileMap;

#endif