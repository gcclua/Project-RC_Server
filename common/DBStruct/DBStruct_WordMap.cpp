#include "DBStruct_WordMap.h"

void DBTile::CleanUp( )
{
	__ENTER_FUNCTION
	 m_tileID = 0; //地块ID
	 m_nPosX = 0;  // X坐标
	 m_nPosY = 0;  // Y坐标
	 m_nBlock = 0; // 所属Block
	 m_nType = TILE_TYPE_INVALID;  // 地块类型
	 m_nCityId = 0;
	 m_nPlayerId = 0;
	__LEAVE_FUNCTION
}
void DBTile::CopyFrom(const DBTile& rSource)
{
	__ENTER_FUNCTION
		m_tileID = rSource.m_tileID; //地块ID
		m_nPosX = rSource.m_nPosX;  // X坐标
		m_nPosY = rSource.m_nPosY;  // Y坐标
		m_nBlock = rSource.m_nBlock; // 所属Block
		m_nType = rSource.m_nType;  // 地块类型
		m_nCityId = rSource.m_nCityId;
		m_nPlayerId = rSource.m_nPlayerId;
	__LEAVE_FUNCTION
}
