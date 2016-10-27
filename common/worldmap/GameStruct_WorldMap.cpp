#include "GameStruct_WorldMap.h"

TileInfo::TileInfo()
{
	m_tileID = 0; //地块ID
	m_nPosX = 0;  // X坐标
	m_nPosY = 0;  // Y坐标
	m_nBlock = 0; // 所属Block
	m_nType = TILE_TYPE_INVALID;  // 地块类型
	m_nCityId = 0;
	m_nPlayerId = 0;
}

TileInfo::~TileInfo()
{

}

void TileInfo::SerializeToDB(DBTile& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_tileID = m_tileID; //地块ID
		rDest.m_nPosX  = m_nPosX;  // X坐标
		rDest.m_nPosY  = m_nPosY;  // Y坐标
		rDest.m_nBlock = m_nBlock; // 所属Block
		rDest.m_nType  = m_nType;  // 地块类型
		rDest.m_nPlayerId = m_nPlayerId; // 玩家ID
		rDest.m_nCityId = m_nCityId; //城市ID
	__LEAVE_FUNCTION
}
void TileInfo::SerializeFromDB(const DBTile& rSource)
{
	__ENTER_FUNCTION
		m_tileID    = rSource.m_tileID; //地块ID
		m_nPosX     = rSource.m_nPosX;  // X坐标
		m_nPosY     = rSource.m_nPosY;  // Y坐标
		m_nBlock    = rSource.m_nBlock; // 所属Block
		m_nType     = rSource.m_nType;  // 地块类型
		m_nCityId   = rSource.m_nCityId;//城市ID
		m_nPlayerId = rSource.m_nPlayerId;//玩家ID
	__LEAVE_FUNCTION
}