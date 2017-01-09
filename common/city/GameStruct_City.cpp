#include "GameStruct_City.h"
#include "packet/Packet/PBMessage.pb.h"

City::City()
{
	CleanUp();
}
City::~City(void)
{

}

void City::CleanUp()
{
	m_tileID    = 0; //地块ID
	m_nCityID   = 0; // 城市
	m_nPlayerId = 0; // 玩家ID
	m_nLevel    = 0; // 等级
	m_nFood     = 0; // 粮食
	m_nStone    = 0; // 石料
	m_nIron     = 0; //铁矿
	m_nPosX     = 0;
	m_nPosZ     = 0;
	m_mapBuilding.clear();
	m_mapTechnology.clear();
	m_mapTechResearch.clear();
	m_mapBuildConstruct.clear();
}

void City::SerializeToDB(DBCity& rDest) const
{
	__ENTER_FUNCTION
		rDest.m_tileID    = m_tileID; //地块ID
		rDest.m_nCityID   = m_nCityID;  // 城市
		rDest.m_nLevel    = m_nLevel;  // 等级
		rDest.m_nFood     = m_nFood; // 粮食
		rDest.m_nStone    = m_nStone;  // 石料
		rDest.m_nPlayerId = m_nPlayerId; // 玩家ID
		rDest.m_nIron     = m_nIron; //铁矿
		rDest.m_nPosZ     = m_nPosZ;
		rDest.m_nPosX     = m_nPosX;
		rDest.m_nGold     = m_nGold;
		int nBuildingIndex = 0;
		for (BuildingMap::const_iterator it = m_mapBuilding.begin();it != m_mapBuilding.end();it++)
		{
			AssertEx(nBuildingIndex>=0 && nBuildingIndex<BUIDINGTYPE_MAX,"");
			it->second->SerializeToDB(rDest.m_BuildingList[nBuildingIndex]);
			nBuildingIndex++;
		}

		int nTechIndex = 0;
		for (TechnologyMap::const_iterator it = m_mapTechnology.begin();it != m_mapTechnology.end(); it++)
		{
			AssertEx(nTechIndex>=0 && nTechIndex<TECHNOLOGYTYPE_MAX,"");
			it->second->SerializeToDB(rDest.m_TechList[nTechIndex]);
			nTechIndex++;
		}

		int nResearch = 0;
		for (TechResearchMap::const_iterator it = m_mapTechResearch.begin();it != m_mapTechResearch.end();it++)
		{
			AssertEx(nResearch>=0 && nResearch<MAX_CITY_RESEARCH_COUNT,"");
			it->second->SerializeToDB(rDest.m_TechResearchList[nResearch]);
			nResearch++;
		}

		int nCounstruct = 0;
		for (BuildConstructMap::const_iterator it = m_mapBuildConstruct.begin(); it != m_mapBuildConstruct.end();it++)
		{
			AssertEx(nCounstruct>=0 && nCounstruct < MAX_CITY_CONSTRUCT_COUNT,"");
			it->second->SerializeToDB(rDest.m_ConstructList[nCounstruct]);
			nCounstruct++;
		}

	__LEAVE_FUNCTION
}

BuildingPtr City::NewBuilding(int nBuildingType)
{
	__ENTER_FUNCTION
		AssertEx(nBuildingType >=BUILDINGTYPE_MIN && nBuildingType<=BUIDINGTYPE_MAX,"");

	BuildingPtr Ptr = null_ptr;
	switch (nBuildingType)
	{
	case BUIDINGTYPE_BARRACKS:
		Ptr = BuildingPtr(new BarrackBuilding(*this));
		break;
	case BUIDINGTYPE_FARM:
		Ptr = BuildingPtr(new FarmBuilding(*this));
		break;
	default:
		Ptr = BuildingPtr(new Building(*this));
		break;
	}
	return Ptr;
	__LEAVE_FUNCTION
	return null_ptr;
}

void City::SerializeFromDB(const DBCity& rSource)
{
	__ENTER_FUNCTION
		m_tileID    = rSource.m_tileID; //地块ID
		m_nCityID   = rSource.m_nCityID; // 城市
		m_nLevel    = rSource.m_nLevel;  // 等级
		m_nFood     = rSource.m_nFood;   // 粮食
		m_nStone    = rSource.m_nStone;  // 石料
		m_nIron     = rSource.m_nIron;   //铁矿
		m_nPlayerId = rSource.m_nPlayerId;//玩家ID
		m_nPosX     = rSource.m_nPosX;
		m_nPosZ     = rSource.m_nPosX;
		m_nGold     = rSource.m_nGold;
		for (int i=0;i<BUIDINGTYPE_MAX;i++)
		{
			if (rSource.m_BuildingList[i].m_ID == 0)
			{
				continue;;
			}
			BuildingPtr Ptr = NewBuilding(rSource.m_BuildingList[i].m_nType);;
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_BuildingList[i]);
			AddBuilding(Ptr);
		
		}
		for (int i=0;i<TECHNOLOGYTYPE_MAX;i++)
		{
			if (rSource.m_TechList[i].m_ID == 0)
			{
				continue;;
			}
			TechnologyPtr Ptr(new Technology(*this));
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_TechList[i]);
			AddTechnology(Ptr);
			
		}

		for (int i=0;i < MAX_CITY_CONSTRUCT_COUNT;i++)
		{
			if (rSource.m_ConstructList[i].m_ID == 0)
			{
				continue;;
			}
			BuildConstructPtr Ptr(new BuildConstruct(*this));
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_ConstructList[i]);
			AddConstruct(Ptr);
		}

		for (int i=0;i < MAX_CITY_CONSTRUCT_COUNT;i++)
		{
			if (rSource.m_TechResearchList[i].m_ID == 0)
			{
				continue;;
			}
			TechResearchPtr Ptr(new TechResearch(*this));
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_TechResearchList[i]);
			AddResearch(Ptr);
		}

	__LEAVE_FUNCTION
}

bool City::AddResearch(TechResearchPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
	AssertEx(Ptr->GetID(),"");
	if (m_mapTechResearch.find(Ptr->GetID()) != m_mapTechResearch.end())
	{
		return false;
	}

	m_mapTechResearch.insert(std::make_pair(Ptr->GetID(),Ptr));
	return true;
	__LEAVE_FUNCTION
		return false;
}

bool City::AddConstruct(BuildConstructPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
		AssertEx(Ptr->GetID(),"");
		if (m_mapBuildConstruct.find(Ptr->GetID()) != m_mapBuildConstruct.end())
		{
			return false;
		}

	m_mapBuildConstruct.insert(std::make_pair(Ptr->GetID(),Ptr));
	return true;
	__LEAVE_FUNCTION
		return false;
}

bool City::AddTechnology(TechnologyPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
		AssertEx(Ptr->GetID(),"");
		if (m_mapTechnology.find(Ptr->GetID()) != m_mapTechnology.end())
		{
			return false;
		}

		m_mapTechnology.insert(std::make_pair(Ptr->GetID(),Ptr));
		return true;
	__LEAVE_FUNCTION
		return false;
}

bool City::AddBuilding(BuildingPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
		AssertEx(Ptr->GetID(),"");
		if (m_mapBuilding.find(Ptr->GetID()) != m_mapBuilding.end())
		{
			return false;
		}

		m_mapBuilding.insert(std::make_pair(Ptr->GetID(),Ptr));
		
		return true;
	__LEAVE_FUNCTION
		return false;
}

BuildingPtr City::GetBuilding(int64 Id) 
{
	__ENTER_FUNCTION
		AssertEx(Id>0,"");
	BuildingMap::iterator it = m_mapBuilding.find(Id);
	if (it != m_mapBuilding.end())
	{
		return it->second;
	}
	
	return null_ptr;
	__LEAVE_FUNCTION
		return null_ptr;
}

TechnologyPtr City::GetTechnology(int nType)
{
	__ENTER_FUNCTION
	AssertEx(nType>=TECHNOLOGYTYPE_MIN && nType<TECHNOLOGYTYPE_MAX,"");

	TechnologyMap::iterator it = m_mapTechnology.find(nType);
	if (it != m_mapTechnology.end())
	{
		return it->second;
	}
	return null_ptr;
	__LEAVE_FUNCTION
	return null_ptr;

}


void  City::FileData(GC_CityData* pCityData)
{
	__ENTER_FUNCTION
		pCityData->set_cityid(m_nCityID);
		pCityData->set_tileid(m_tileID);
		pCityData->set_level(m_nLevel);
		pCityData->set_food(m_nFood);
		pCityData->set_stone(m_nStone);
		pCityData->set_iron(m_nIron);

	BuildingMap::iterator it = m_mapBuilding.begin();
	for( ;it != m_mapBuilding.end();it++)
	{
		BuildingPtr ptr = it->second;
		AssertEx(ptr,"");
		GC_BuildingData* pBuildData = pCityData->add_buildlist();
		pBuildData->set_guid(ptr->GetID());
		pBuildData->set_type(ptr->GetGuildingType());
		pBuildData->set_slot(ptr->GetSlot());
		pBuildData->set_level(ptr->GetLevel());
	}

	__LEAVE_FUNCTION
}

void City::Init()
{
	
}

void City::OnLogin()
{
	__ENTER_FUNCTION
	BuildingMap::iterator it = m_mapBuilding.begin();
	for( ;it != m_mapBuilding.end();it++)
	{
		BuildingPtr ptr = it->second;
		AssertEx(ptr,"");
		ptr->OnLogin();
	}
	__LEAVE_FUNCTION
}

bool City::CheckSendMarchIntoMap(int64 nBuildId)
{
	__ENTER_FUNCTION
	BuildingMap::iterator it = m_mapBuilding.find(nBuildId);
	if (it == m_mapBuilding.end())
	{
		return false;
	}

	BuildingPtr Ptr = it->second;
	AssertEx(Ptr,"");
	if (Ptr->GetGuildingType() != BUIDINGTYPE_BARRACKS)
	{
		return false;
	}

	return true;
	
	__LEAVE_FUNCTION
		return false;
}

/*bool City::CheckAssignHero(int64 nBuildId)
{
	__ENTER_FUNCTION
		BuildingMap::iterator it = m_mapBuilding.find(nBuildId);
		if (it == m_mapBuilding.end())
		{
			return false;
		}

		BuildingPtr Ptr = it->second;
		AssertEx(Ptr,"");
		if (Ptr->GetGuildingType() != BUIDINGTYPE_BARRACKS && Ptr->GetGuildingType() != BUIDINGTYPE_WALL)
		{
			return false;
		}

		return true;
	__LEAVE_FUNCTION
		return false;
}*/

void City::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		Tick_Building(rTimeInfo);

		Tick_TechResearch(rTimeInfo);

		Tick_Train(rTimeInfo);
		
	__LEAVE_FUNCTION
}

void City::Tick_Building(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		BuildingMap::iterator it = m_mapBuilding.begin();
	for( ;it != m_mapBuilding.end();it++)
	{
		BuildingPtr ptr = it->second;
		AssertEx(ptr,"");
		ptr->Tick(rTimeInfo);
	}
	__LEAVE_FUNCTION
}

void City::Tick_TechResearch(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		TechResearchMap::iterator it = m_mapTechResearch.begin();
	for( ;it != m_mapTechResearch.end();)
	{
		TechResearchPtr ptr = it->second;
		AssertEx(ptr,"");
		ptr->Tick(rTimeInfo);
		if (ptr->GetOverFlag())
		{
			FinishResearch(ptr);
			it = m_mapTechResearch.erase(it);
		}
		else
		{
			it++;
		}

	}
	__LEAVE_FUNCTION
}

void City::FinishResearch(TechResearchPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
		TechnologyMap::iterator it = m_mapTechnology.find(Ptr->GetType());
		if (it == m_mapTechnology.end())
		{
			return;
		}
		TechnologyPtr techPtr = it->second;
		AssertEx(techPtr,"");
		if (techPtr->GetLevel()<=Ptr->GetLevel())
		{
			techPtr->SetLevel(Ptr->GetLevel()+1);
		}
		
	__LEAVE_FUNCTION
}

void City::Tick_Train(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
	__LEAVE_FUNCTION
}

Technology::Technology(City &rCity)
	: m_City(rCity)
{
	m_ID = 0; // 科技ID
	m_nLevel = 0; // 等级
	m_nType = 0; // 类型
}
Technology::~Technology(void)
{

}

void Technology::SerializeToDB(DBTechnology& rDest) const
{
	rDest.m_ID     = m_ID; 
	rDest.m_nLevel = m_nLevel;  
	rDest.m_nType  = m_nType; 
}
void Technology::SerializeFromDB(const DBTechnology& rSource)
{
	 m_ID     = rSource.m_ID;
	 m_nLevel = rSource.m_nLevel;
	 m_nType  = rSource.m_nType;
}


TechResearch::TechResearch(City &rCity)
	: m_City(rCity)
{
	m_nType  = 0;
	m_nBeginTime  = 0;
	m_nLevel = 0;
	m_bOverFlag = false;
	m_nCompleteTime = 0;
}

TechResearch::~TechResearch()
{

}
void TechResearch::Tick(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		m_bOverFlag = false;
	 if ((int)rTimeInfo.m_nAnsiTime > m_nCompleteTime)
	 {
		 m_bOverFlag = true;
	 }

	__LEAVE_FUNCTION
}

void TechResearch::SerializeToDB(DBTechResearch& rDest) const
{
	rDest.m_nType          = m_nType; 
	rDest.m_nBeginTime     = m_nBeginTime;  
	rDest.m_nLevel         = m_nLevel;
	rDest.m_nCompleteTime  = m_nCompleteTime;
}
void TechResearch::SerializeFromDB(const DBTechResearch& rSource)
{
	m_nType         = rSource.m_nType;
	m_nBeginTime    = rSource.m_nBeginTime;
	m_nLevel        = rSource.m_nLevel;
	m_nCompleteTime = rSource.m_nCompleteTime;
}

BuildConstruct::BuildConstruct(City &rCity)
	: m_City(rCity)
{
	m_BuildId  = 0;
	m_nBeginTime  = 0;
	m_nLevel = 0;
	m_bOverFlag = false;
	m_nCompleteTime = 0;
}

BuildConstruct::~BuildConstruct()
{

}


void BuildConstruct::Tick(const TimeInfo& rTimeInfo)
{
	m_bOverFlag = false;
	if ((int)rTimeInfo.m_nAnsiTime > m_nCompleteTime)
	{
		m_bOverFlag = true;
	}
}

void BuildConstruct::SerializeToDB(DBBuildConstruct& rDest) const
{
	rDest.m_BuildId        = m_BuildId; 
	rDest.m_nBeginTime     = m_nBeginTime;  
	rDest.m_nLevel         = m_nLevel;
	rDest.m_nCompleteTime  = m_nCompleteTime;
}
void BuildConstruct::SerializeFromDB(const DBBuildConstruct& rSource)
{
	m_BuildId       = rSource.m_BuildId;
	m_nBeginTime    = rSource.m_nBeginTime;
	m_nLevel        = rSource.m_nLevel;
	m_nCompleteTime = rSource.m_nCompleteTime;
}
