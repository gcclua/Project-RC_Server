#include "GameStruct_City.h"
#include "packet/Packet/PBMessage.pb.h"
#include "Message/CityMsg.h"
#include "Message/DBMsg.h"
#include "Table/Table_Troop.h"
#include "Table/Table_RoleBaseAttr.h"
#include "service/MessageOp.h"

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
	m_fPosX     = 0.f;
	m_fPosZ     = 0.f;
	m_mapBuilding.clear();
	m_mapTechnology.clear();
	m_mapTechResearch.clear();
	m_mapBuildConstruct.clear();
	m_mapTrainMap.clear();
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
		rDest.m_fPosZ     = m_fPosZ;
		rDest.m_fPosX     = m_fPosX;
		rDest.m_nGold     = m_nGold;
		int nBuildingIndex = 0;
		for (BuildingMap::const_iterator it = m_mapBuilding.begin();it != m_mapBuilding.end();it++)
		{
			AssertEx(nBuildingIndex>=0 && nBuildingIndex<BUILDING_MAX_SLOT,"");
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

		int nTrainCount = 0;
		for (TroopTrainMap::const_iterator it = m_mapTrainMap.begin(); it != m_mapTrainMap.end();it++)
		{
			AssertEx(nTrainCount>=0 && nTrainCount < BUILDING_BARRACK_MAX+BUILDING_WALL_MAX,"");
			it->second->SerializeToDB(rDest.m_TrainList[nTrainCount]);
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
		m_fPosX     = rSource.m_fPosX;
		m_fPosZ     = rSource.m_fPosZ;
		m_nGold     = rSource.m_nGold;
		for (int i=0;i<BUILDING_MAX_SLOT;i++)
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

		for (int i=0;i <  BUILDING_BARRACK_MAX+BUILDING_WALL_MAX;i++)
		{
			if (rSource.m_TrainList[i].m_ID == 0)
			{
				continue;;
			}
			TroopTrainPtr Ptr(new TroopTrain(*this));
			AssertEx(Ptr,"");
			Ptr->SerializeFromDB(rSource.m_TrainList[i]);
			AddTroopTrain(Ptr);
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

bool City::AddTroopTrain(TroopTrainPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
	AssertEx(Ptr->GetID(),"");
	if (m_mapTrainMap.find(Ptr->GetID()) != m_mapTrainMap.end())
	{
		return false;
	}

	m_mapTrainMap.insert(std::make_pair(Ptr->GetBuildId(),Ptr));
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

bool City::FileTrainData(TroopTrainPtr Ptr,GC_TrainData* pTrainData)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
		AssertEx(pTrainData,"");
		pTrainData->set_queueid(Ptr->GetID());
		pTrainData->set_buildid(Ptr->GetBuildId());
		pTrainData->set_trooptype(Ptr->GetType());
		pTrainData->set_hp(Ptr->GetHp());
		pTrainData->set_begintime(Ptr->GetBeginTime());
		pTrainData->set_completime(Ptr->GetCompleteTime());
		pTrainData->set_queueindex(Ptr->GetQueueIndex());
		return true;
	__LEAVE_FUNCTION
	return false;
}

bool City::BeginTrainTroop(int64 nBuildId,int nQueueIndex,int nType,int Count,GC_TrainData* pTrainData)
{
	__ENTER_FUNCTION
		BuildingPtr Ptr = GetBuilding(nBuildId);
		if (Ptr == null_ptr)
		{
			return false;
		}

		TroopTrainPtr TrainPtr = GetTroopTrain(nBuildId);
		if (TrainPtr==null_ptr)
		{
			return false;
		}

		if (TrainPtr->GetType() >0)
		{
			return false;
		}

		Table_Troop const* pTroop = GetTable_TroopByID(nType);
		if (pTroop == null_ptr)
		{
			return false;
		}

		Table_RoleBaseAttr const * pRoleBase = GetTable_RoleBaseAttrByID(pTroop->GetDataIDbyIndex(0));
		if (pRoleBase == null_ptr)
		{
			return false;
		}

		int nHp = pRoleBase->GetMaxHP()*Count;
		
		TrainPtr->SetType(nType);
		TrainPtr->SetBeginTime((int)gTimeManager.GetANSITime());
		TrainPtr->SetCompleteTime((int)gTimeManager.GetANSITime()+60);
		TrainPtr->SetHp(nHp);
		TrainPtr->SetQueueIndex(nQueueIndex);

		FileTrainData(TrainPtr,pTrainData);

		DBReqSaveTroopTrainMsgPtr MsgPtr= POOLDEF_NEW(DBReqSaveTroopTrainMsg);
		AssertEx(MsgPtr,"");
		TrainPtr->SerializeToDB(MsgPtr->m_Data);
		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);

		return true;


	__LEAVE_FUNCTION
	return false;
}

bool City::BuildingLevelUp(int64 nBuildingId)
{
	__ENTER_FUNCTION
		BuildingPtr Ptr = GetBuilding(nBuildingId);
	    if (Ptr == null_ptr)
		{
			return false;
		}
		Ptr->SetLevel(Ptr->GetLevel()+1);
		return true;
	__LEAVE_FUNCTION
		return false;
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

TroopTrainPtr  City::GetTroopTrain(int64 nBuildId)
{
	__ENTER_FUNCTION
		AssertEx(nBuildId>=0,"");

	TroopTrainMap::iterator it = m_mapTrainMap.find(nBuildId);
	if (it != m_mapTrainMap.end())
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
		pCityData->set_posx((int)(m_fPosX*100));
		pCityData->set_posz((int)(m_fPosZ*100));

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

	TroopTrainMap::iterator itTrain = m_mapTrainMap.begin();
	for (; itTrain != m_mapTrainMap.end();itTrain++)
	{
		TroopTrainPtr ptr = itTrain->second;
		AssertEx(ptr,"");
		GC_TrainData* pTrainData = pCityData->add_trainlist();
		FileTrainData(ptr,pTrainData);
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

void City::FinishTroopTrain(TroopTrainPtr Ptr)
{
	__ENTER_FUNCTION
		AssertEx(Ptr,"");
	TroopTrainMap::iterator it = m_mapTrainMap.find(Ptr->GetBuildId());
	if (it == m_mapTrainMap.end())
	{
		return;
	}
	TroopTrainPtr troopPtr = it->second;

	TrainTroopOverMsgPtr MsgPtr = POOLDEF_NEW(TrainTroopOverMsg);
	MsgPtr->m_ID = troopPtr->GetID();
	MsgPtr->m_nBuildId = troopPtr->GetBuildId();
	MsgPtr->m_nHp = troopPtr->GetHp();
	MsgPtr->m_nType = troopPtr->GetType();
	MsgPtr->m_nQueueIndex = troopPtr->GetQueueIndex();
	SendMessage2User(m_nPlayerId,MsgPtr);

	troopPtr->InitTrainQueue();

	DBReqSaveTroopTrainMsgPtr MsgSavePtr= POOLDEF_NEW(DBReqSaveTroopTrainMsg);
		AssertEx(MsgSavePtr,"");
		troopPtr->SerializeToDB(MsgSavePtr->m_Data);
		SendMessage2Srv(ServiceID::DBAGENT,MsgSavePtr);

	

	__LEAVE_FUNCTION
}

void City::Tick_Train(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		for (TroopTrainMap::iterator it = m_mapTrainMap.begin();it != m_mapTrainMap.end();it++)
		{
			TroopTrainPtr Ptr = it->second;
			if (Ptr->GetType()<=0)
			{
				continue;
			}
			AssertEx(Ptr,"");
			Ptr->Tick(rTimeInfo);
			if (Ptr->GetOverFlag())
			{
				FinishTroopTrain(Ptr);
				
			}
		}
		
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

void TroopTrain::InitTrainQueue()
{
	__ENTER_FUNCTION
		m_nType  = 0;
	m_nBeginTime  = 0;
	m_nCompleteTime = 0;
	m_nType = 0; // 兵种
	m_nHp = 0;   // 训兵血量
	m_bOverFlag = false;
	m_nQueueIndex = 0;
	__LEAVE_FUNCTION
}

void TroopTrain::CleanUp()
{
	m_nType  = 0;
	m_nBeginTime  = 0;
	m_ID = invalid_guid64;
	m_nCompleteTime = 0;
	m_nType = 0; // 兵种
	m_nHp = 0;   // 训兵血量
	m_nBuildId = invalid_guid64;
	m_bOverFlag = false;
	m_nQueueIndex = 0;
}

TroopTrain::TroopTrain(City &rCity)
	: m_City(rCity)
{
	CleanUp();
}

TroopTrain::~TroopTrain()
{

}

void TroopTrain::Tick(const TimeInfo& rTimeInfo)
{
	if ((int)rTimeInfo.m_nAnsiTime > m_nCompleteTime && !m_bOverFlag)
	{
		m_bOverFlag = true;
	}
}

void TroopTrain::SerializeToDB(DBTroopTrain& rDest) const
{
	rDest.m_ID            = m_ID ; // ID
	rDest.m_nType         = m_nType; // 兵种类型
	rDest.m_nBeginTime    = m_nBeginTime; // 开始时间
	rDest.m_nCompleteTime = m_nCompleteTime; // 完成时间
	rDest.m_nHp           = m_nHp;   // 训兵血量 
	rDest.m_nBuildId      = m_nBuildId;
	rDest.m_nQueueIndex   = m_nQueueIndex;
}
void TroopTrain::SerializeFromDB(const DBTroopTrain& rSource)
{
	m_ID            = rSource.m_ID ; // ID
	m_nType         = rSource.m_nType; // 兵种类型
	m_nBeginTime    = rSource.m_nBeginTime; // 开始时间
	m_nCompleteTime = rSource.m_nCompleteTime; // 完成时间
	m_nHp           = rSource.m_nHp;   // 训兵血量 
	m_nBuildId      = rSource.m_nBuildId;
	m_nQueueIndex   = rSource.m_nQueueIndex;
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
