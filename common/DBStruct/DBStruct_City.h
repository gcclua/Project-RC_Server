
#ifndef __DBSTRUCT_CITY_H__
#define __DBSTRUCT_CITY_H__

#include "DBStruct.h"
#include "city/GameDefine_City.h"
#include "building/GameDefine_Building.h"
#include "troop/GameDefine_Troop.h"
#include "hero/GameDefine_Hero.h"
#include "DBStruct/DBStruct_Troop.h"
#include "DBStruct/DBStruct_Hero.h"

struct DBTechnology
{
public:
	DBTechnology(){CleanUp();};
	~DBTechnology(){};
public:
	void CleanUp( );
	void CopyFrom(const DBTechnology& rSource);
public:
	int64  m_ID; // 科技ID
	int    m_nLevel; // 等级
	int    m_nType;  // 类型
	int64  m_nCityID; // 所属城市
};

struct DBTechResearch
{
public:
	DBTechResearch(){CleanUp();};
	~DBTechResearch(){};
public:
	void CleanUp( );
	void CopyFrom(const DBTechResearch& rSource);
public:
	int64 m_ID; // 科研ID
	int   m_nType; // 科研的类型
	int   m_nBeginTime; // 科研开始时间
	int   m_nLevel; // 原等级
	int   m_nCompleteTime; // 完成时间
	int64  m_nCityID; // 所属城市
};

struct DBTroopTrain
{
public:
	DBTroopTrain(){CleanUp();};
	~DBTroopTrain(){};
public:
	void CleanUp( );
	void CopyFrom(const DBTroopTrain& rSource);

	void InitTrain(int64 nBuildId,int64 nCityId);
public:
	int64 m_ID; // ID
	int   m_nType; // 兵种类型
	int   m_nBeginTime; // 开始时间
	int   m_nCompleteTime; // 完成时间
	int64 m_nCityID; // 所属城市
	int   m_nHp;   // 训兵血量
	int64 m_nBuildId;
	int   m_nQueueIndex;
};

struct DBBuilding
{
public:
	DBBuilding(){CleanUp();};
	~DBBuilding(){};
public:
	void CleanUp( );
	void CopyFrom(const DBBuilding& rSource);
public:
	int64 m_ID; //建筑Guid
	int   m_nLevel; // 等级
	int   m_nSlot;  // 位置
	int   m_nType;  // 建筑类型
	int64  m_nCityID; // 所属城市
};

struct DBBuildConstruct
{
public:
	DBBuildConstruct(){CleanUp();};
	~DBBuildConstruct(){};
public:
	void CleanUp( );
	void CopyFrom(const DBBuildConstruct& rSource);
public:
	int64 m_ID; // 建造ID
	int64 m_BuildId; // 建筑的ID
	int   m_nBeginTime; // 科研开始时间
	int   m_nLevel; // 原等级
	int   m_nCompleteTime; // 完成时间
	int64  m_nCityID; // 所属城市
};


// 玩家城市信息
struct DBCity
{
public:
	DBCity(){CleanUp();};
	~DBCity(){};

	void CleanUp( );
	void CopyFrom(const DBCity& rSource);

public:
	int   m_tileID; //地块ID
	int64 m_nCityID; //城市ID
	int64 m_nPlayerId; // 玩家Id
	int   m_nLevel;  // 城市等级
	int64 m_nFood; //食物
	int64 m_nStone; //石料
	int64 m_nIron;  // 铁矿
	int64 m_nGold;
	tfloat32   m_fPosX;
	tfloat32   m_fPosZ;
	DBBuilding m_BuildingList[BUILDING_MAX_SLOT]; // 所有的建筑列表
	DBTechnology m_TechList[TECHNOLOGYTYPE_MAX];// 所有的科技列表
	DBTechResearch m_TechResearchList[MAX_CITY_RESEARCH_COUNT]; // 正在研究的队列
	DBBuildConstruct m_ConstructList[MAX_CITY_CONSTRUCT_COUNT]; // 正在建造的队列
	DBTroopTrain  m_TrainList[BUILDING_BARRACK_MAX+BUILDING_WALL_MAX];// 训兵队列
	//DBTroop          m_TroopList[MAX_TROOP_QUEUE];                // 兵种列表
	

	
};

typedef DBCommonData<DBCity> DBCityData;
typedef boost::shared_ptr<DBCityData> DBCityDataPtr;



#endif
