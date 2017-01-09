
#ifndef _GAMESTRUCT_CITY_H_
#define _GAMESTRUCT_CITY_H_

#include "Base.h"
#include "DBStruct/DBStruct_City.h"
#include "building/GameStruct_Building.h"
#include "service/TimeInfo.h"


class City;

class Technology
{
public:
	Technology(City &rCity);
	virtual ~Technology(void);
public:
	void SerializeToDB(DBTechnology& rDest) const;
	void SerializeFromDB(const DBTechnology& rSource);

private:
	City& m_City;

public:

	int64 GetID() const {return m_ID;}
	void  SetID(int64 nVal){m_ID=nVal;}

	// 科技类型
	int   GetType() const {return m_nType;}
	void  SetType(int nVal) {m_nType = nVal;}

	// 等级
	int   GetLevel() const {return m_nLevel;}
	void  SetLevel(int nVal) {m_nLevel = nVal;}

private:
	int64  m_ID; // 科技ID
	int    m_nLevel; // 等级
	int    m_nType; // 类型
};

typedef boost::shared_ptr<Technology> TechnologyPtr;
typedef std::map<int64,TechnologyPtr> TechnologyMap;

class TechResearch
{
public:
	TechResearch(City &rCity);
	~TechResearch();

public:
	void Tick(const TimeInfo& rTimeInfo);

	void SerializeToDB(DBTechResearch& rDest) const;
	void SerializeFromDB(const DBTechResearch& rSource);

private:
	City& m_City;

public:

	int64 GetID() const {return m_ID;}
	void  SetID(int64 nVal){m_ID = nVal;}

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}

	int  GetLevel() const {return m_nLevel;}
	void SetLevel(int nVal) {m_nLevel = nVal;}

	bool GetOverFlag() const {return m_bOverFlag;}
	void SetOverFlag(bool bVal){m_bOverFlag = bVal;}

	int  GetBeginTime() const {return m_nBeginTime;}
	void SetBeginTime(int nVal){m_nBeginTime=nVal;}

	int  GetCompleteTime() const {return m_nCompleteTime;}
	void SetCompleteTime(int nVal){m_nCompleteTime=nVal;}
private:

	// 结束标记
	bool m_bOverFlag;


private:

	int64 m_ID; // 科研ID
	int   m_nType; // 科研的类型
	int   m_nBeginTime; // 科研开始时间
	int   m_nLevel; // 原等级
	int   m_nCompleteTime; // 完成时间

};

typedef boost::shared_ptr<TechResearch> TechResearchPtr;
typedef std::map<int64,TechResearchPtr> TechResearchMap;

class BuildConstruct
{
public:
	BuildConstruct(City &rCity);
	~BuildConstruct();
public:
	void Tick(const TimeInfo& rTimeInfo);

	void SerializeToDB(DBBuildConstruct& rDest) const;
	void SerializeFromDB(const DBBuildConstruct& rSource);

private:
	City& m_City;

public:
	int64 GetBuildId() const {return m_BuildId;}
	void SetBuildId(int64 nVal) {m_BuildId = nVal;}

	int  GetLevel() const {return m_nLevel;}
	void SetLevel(int nVal) {m_nLevel = nVal;}

	bool GetOverFlag() const {return m_bOverFlag;}
	void SetOverFlag(bool bVal){m_bOverFlag = bVal;}

	int  GetBeginTime() const {return m_nBeginTime;}
	void SetBeginTime(int nVal){m_nBeginTime=nVal;}

	int  GetCompleteTime() const {return m_nCompleteTime;}
	void SetCompleteTime(int nVal){m_nCompleteTime=nVal;}

	int64 GetID() const {return m_ID;}
	void  SetID(int64 nVal){m_ID = nVal;}

private:

	// 结束标记
	bool m_bOverFlag;

private:
	int64 m_ID; // 建造ID
	int64 m_BuildId; // 建筑的ID
	int   m_nBeginTime; // 科研开始时间
	int   m_nLevel; // 原等级
	int   m_nCompleteTime; // 完成时间
};

typedef boost::shared_ptr<BuildConstruct> BuildConstructPtr;
typedef std::map<int64,BuildConstructPtr> BuildConstructMap;

class GC_CityData;

class City
{
public:
	City();
	virtual ~City(void);

	void CleanUp();

public:
	void Tick(const TimeInfo& rTimeInfo);
	void OnLogin();

	// 初始化建筑
	void Init();

public:
	void    FileData(GC_CityData* pCityData);

public:
	// 检测某个兵营或者城墙能否驻扎英雄
	//bool       CheckAssignHero(int64 nBuildId);


	// 从城市中派遣一队兵到大地图
	bool       CheckSendMarchIntoMap(int64 nBuildId);

private:
	// 建筑心跳，比如产资源
	void Tick_Building(const TimeInfo& rTimeInfo);

	// 科技研究
	void Tick_TechResearch(const TimeInfo& rTimeInfo);

	// 训兵
	void Tick_Train(const TimeInfo& rTimeInfo);

private:
	BuildingPtr NewBuilding(int nBuildingType);

public:
	void SerializeToDB(DBCity& rDest) const;
	void SerializeFromDB(const DBCity& rSource);

public:
	bool AddBuilding(BuildingPtr Ptr); //增加一个建筑
	bool AddTechnology(TechnologyPtr Ptr); // 增加一个科技
	bool AddResearch(TechResearchPtr Ptr);
	bool AddConstruct(BuildConstructPtr Ptr);
	

	// 建造一个建筑物
	bool CreateBuilding(int nType,int nSlot);

public:
	BuildingPtr GetBuilding(int64 Id) ;

private:
	// 建筑列表
	BuildingMap m_mapBuilding;
	bsarray<IDList,BUIDINGTYPE_MAX> m_BuildTypeMap; // 每一类建筑物列表 

public:
	TechnologyPtr GetTechnology(int nType);

private:
	TechnologyMap m_mapTechnology;

private:
	void FinishResearch(TechResearchPtr Ptr);
	
private:
	TechResearchMap m_mapTechResearch;

private:
	BuildConstructMap m_mapBuildConstruct;


private:
	//BarrackTroopMap   m_mapTroop;
	//BarrackArrangeMap m_mapArrange;
	BarrackMarchMap    m_mapMarch;
public:

	// 地块ID
	int    GetTileID() const {return m_tileID;}
	void   SettileID(int val){m_tileID = val;}

	// 城市ID
	int64  GetCityID() const {return m_nCityID;}
	void   SetCityID(int64 val) {m_nCityID = val;}
	
	// 玩家ID
	int64  GetPlayerId() const {return m_nPlayerId;}
	void   SetPlayerId(int64 val){m_nPlayerId = val;}

	//  城市等级
	int    GetLevel() const {return m_nLevel;}
	void   SetLevel(int val) {m_nLevel = val;}

	// 食物
	int64  GetFood() const {return m_nFood;}
	void   SetFood(int64 val){m_nFood = val;}

	// 石料
	int64  GetStone() const {return m_nStone;}
	void   SetStone(int64 val){m_nStone = val;}

	// 铁矿
	int64  GetIron() const {return m_nIron;}
	void   SetIron(int64 val) {m_nIron = val;}

	int   GetPosX() const {return m_nPosX;}
	void  SetPosX(int val) {m_nPosX = val;}

	int  GetPosZ() const {return m_nPosZ;}
	void SetPosZ(int val) {m_nPosZ = val;}

	int64  GetGold() const {return m_nGold;}
	void   SetGold(int64 val){m_nGold=val;}

private:
	
	int   m_tileID; //地块ID
	int64 m_nCityID; //城市ID
	int64 m_nPlayerId; // 玩家Id
	int   m_nLevel;  // 城市等级
	int64 m_nFood; //食物
	int64 m_nStone; //石料
	int64 m_nIron;  // 铁矿
	int64 m_nGold;
	int m_nPosX;
	int m_nPosZ;
};

typedef boost::shared_ptr<City> CityPtr;
#endif