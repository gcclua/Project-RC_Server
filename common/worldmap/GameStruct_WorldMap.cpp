#include "GameStruct_WorldMap.h"

TileInfo::TileInfo()
{
	m_tileID = 0; //�ؿ�ID
	m_nPosX = 0;  // X����
	m_nPosY = 0;  // Y����
	m_nBlock = 0; // ����Block
	m_nType = TILE_TYPE_INVALID;  // �ؿ�����
	m_nCityId = 0;
	m_nUserId = 0;
	m_lockTime  = 0;
	m_nState    = TILE_STATE_IDLE;
}

TileInfo::~TileInfo()
{

}

void TileInfo::SerializeToDB(DBTile& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_tileID = m_tileID; //�ؿ�ID
		rDest.m_nPosX  = m_nPosX;  // X����
		rDest.m_nPosY  = m_nPosY;  // Y����
		rDest.m_nBlock = m_nBlock; // ����Block
		rDest.m_nType  = m_nType;  // �ؿ�����
		rDest.m_nUserId = m_nUserId; // ���ID
		rDest.m_nCityId = m_nCityId; //����ID
		rDest.m_nState  = m_nState;
	__LEAVE_FUNCTION
}
void TileInfo::SerializeFromDB(const DBTile& rSource)
{
	__ENTER_FUNCTION
		m_tileID    = rSource.m_tileID; //�ؿ�ID
		m_nPosX     = rSource.m_nPosX;  // X����
		m_nPosY     = rSource.m_nPosY;  // Y����
		m_nBlock    = rSource.m_nBlock; // ����Block
		m_nType     = rSource.m_nType;  // �ؿ�����
		m_nCityId   = rSource.m_nCityId;//����ID
		m_nUserId   = rSource.m_nUserId;//���ID
		m_nState    = rSource.m_nState;
	__LEAVE_FUNCTION
}