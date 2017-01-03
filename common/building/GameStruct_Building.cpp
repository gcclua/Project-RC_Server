#include "GameStruct_Building.h"

Building::Building(City &rCity)
	: m_City(rCity)
{
	m_ID = 0;
	m_nLevel = 0;
	m_nSlot  = 0;
	m_nType  = 0;
}
Building::~Building()
{

}

void Building::SerializeToDB(DBBuilding& rDest)
{
	rDest.m_ID     = m_ID;
	rDest.m_nLevel = m_nLevel;
	rDest.m_nSlot  = m_nSlot;
	rDest.m_nType  = m_nType;
}
void Building::SerializeFromDB(const DBBuilding& rSource)
{
	m_ID     = rSource.m_ID;
	m_nLevel = rSource.m_nLevel;
	m_nSlot  = rSource.m_nSlot;
	m_nType  = rSource.m_nType;
	
}

FarmBuilding::FarmBuilding(City &rCity)
	:Building(rCity)
{

}


FarmBuilding::~FarmBuilding()
{

}


BarrackBuilding::BarrackBuilding(City &rCity)
	:Building(rCity)
{
	
}

BarrackBuilding::~BarrackBuilding()
{

}

