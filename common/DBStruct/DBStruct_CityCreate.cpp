#include "DBStruct_CityCreate.h"

void DBCityCreate::CleanUp( )
{
	__ENTER_FUNCTION
		m_tileID    = 0; //µØ¿éID
		m_nCityID   = 0;
		m_UserId = 0;
		m_nLevel    = 0;
		m_nPosX     = 0;
		m_nPosZ     = 0;
		m_lstMarch.clear();
		m_lstBuilding.clear();
		m_Hero.CleanUp();
	
		
	__LEAVE_FUNCTION
}
void DBCityCreate::CopyFrom(const DBCityCreate& rSource)
{
	__ENTER_FUNCTION
		CleanUp();
		m_tileID    = rSource.m_tileID; //µØ¿éID
		m_nCityID   = rSource.m_nCityID;
		m_UserId    = rSource.m_UserId;
		m_nLevel    = rSource.m_nLevel;
		m_nPosX     = rSource.m_nPosX;
		m_nPosZ     = rSource.m_nPosZ;
		m_nFood     = rSource.m_nFood;
		m_nStone    = rSource.m_nStone;
		m_nIron     = rSource.m_nIron;
		m_nGold     = rSource.m_nGold;

		
	
		int nBuildSize = (int)rSource.m_lstBuilding.size();
		m_lstBuilding.resize(nBuildSize);
		for (int i=0;i<nBuildSize;i++)
		{
			m_lstBuilding[i].CopyFrom(rSource.m_lstBuilding[i]);
		}
		
		int nMarchSize = (int)rSource.m_lstMarch.size();
		m_lstMarch.resize(nMarchSize);
		for (int i=0;i<nMarchSize;i++)
		{
			m_lstMarch[i].CopyFrom(rSource.m_lstMarch[i]);
		}

		m_Hero.CopyFrom(rSource.m_Hero);

	__LEAVE_FUNCTION
}
