#include "DBStruct_WordMap.h"

void DBTile::CleanUp( )
{
	__ENTER_FUNCTION
	 m_tileID = 0; //�ؿ�ID
	 m_nPosX = 0;  // X����
	 m_nPosY = 0;  // Y����
	 m_nBlock = 0; // ����Block
	 m_nType = TILE_TYPE_INVALID;  // �ؿ�����
	 m_nCityId = 0;
	 m_nPlayerId = 0;
	__LEAVE_FUNCTION
}
void DBTile::CopyFrom(const DBTile& rSource)
{
	__ENTER_FUNCTION
		m_tileID = rSource.m_tileID; //�ؿ�ID
		m_nPosX = rSource.m_nPosX;  // X����
		m_nPosY = rSource.m_nPosY;  // Y����
		m_nBlock = rSource.m_nBlock; // ����Block
		m_nType = rSource.m_nType;  // �ؿ�����
		m_nCityId = rSource.m_nCityId;
		m_nPlayerId = rSource.m_nPlayerId;
	__LEAVE_FUNCTION
}
