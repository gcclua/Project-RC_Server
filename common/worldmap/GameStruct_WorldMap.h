
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

	// �ؿ�ID
	int    GetID() const {return m_tileID;}
	void   SetID(int val){m_tileID = val;}

	// X����
	int    GetPosX() const {return m_nPosX;}
	void   SetPosX(int val) {m_nPosX = val;}
	
	// Y����
	int    GetPosY() const {return m_nPosY;}
	void   SetPosY(int val){m_nPosY = val;}

	//  ����Block
	int    GetBlock() const {return m_nBlock;}
	void   SetBlock(int val) {m_nBlock = val;}

	// �ؿ�����
	int    GetType() const {return m_nType;}
	void   SetType(int val){m_nType = val;}

	// ����ID
	int    GetCityID() const {return m_nCityId;}
	void   SetCityID(int val){m_nCityId = val;}

	// ���ID
	int64  GetPlayerID() const {return m_nPlayerId;}
	void   SetPlayerID(int val) {m_nPlayerId = val;}
private:
	
	int m_tileID; //�ؿ�ID
	int m_nPosX;  // X����
	int m_nPosY;  // Y����
	int m_nBlock; // ����Block
	int m_nType;  // �ؿ�����
	int m_nCityId; // ����ID
	int64 m_nPlayerId; // ���ID

};

typedef std::map<int,TileInfo> TileMap;

#endif