
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

	// �Ƽ�����
	int   GetType() const {return m_nType;}
	void  SetType(int nVal) {m_nType = nVal;}

	// �ȼ�
	int   GetLevel() const {return m_nLevel;}
	void  SetLevel(int nVal) {m_nLevel = nVal;}

private:
	int64  m_ID; // �Ƽ�ID
	int    m_nLevel; // �ȼ�
	int    m_nType; // ����
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

	// �������
	bool m_bOverFlag;


private:

	int64 m_ID; // ����ID
	int   m_nType; // ���е�����
	int   m_nBeginTime; // ���п�ʼʱ��
	int   m_nLevel; // ԭ�ȼ�
	int   m_nCompleteTime; // ���ʱ��

};

typedef boost::shared_ptr<TechResearch> TechResearchPtr;
typedef std::map<int64,TechResearchPtr> TechResearchMap;

class TroopTrain
{
public:
	TroopTrain(City &rCity);
	~TroopTrain();

public:
	void Tick(const TimeInfo& rTimeInfo);

	void SerializeToDB(DBTroopTrain& rDest) const;
	void SerializeFromDB(const DBTroopTrain& rSource);

	void CleanUp();

	void InitTrainQueue();

private:
	City& m_City;

public:

	int64 GetID() const {return m_ID;}
	void  SetID(int64 nVal){m_ID = nVal;}

	int  GetType() const {return m_nType;}
	void SetType(int nVal) {m_nType = nVal;}

	int  GetBeginTime() const {return m_nBeginTime;}
	void SetBeginTime(int nVal){m_nBeginTime=nVal;}

	int  GetCompleteTime() const {return m_nCompleteTime;}
	void SetCompleteTime(int nVal){m_nCompleteTime=nVal;}

	int  GetHp() const {return m_nHp;}
	void SetHp(int val) {m_nHp = val;}

	int64 GetBuildId() const {return m_nBuildId;}
	void  SetBuildId(int64 val) {m_nBuildId=val;}

	bool GetOverFlag() const {return m_bOverFlag;}
	void SetOverFlag(bool bVal){m_bOverFlag = bVal;}

	int GetQueueIndex() const {return m_nQueueIndex;}
	void SetQueueIndex(int val) {m_nQueueIndex=val;}

private:
	bool   m_bOverFlag;

private:

	int64 m_ID; // ID
	int   m_nType; // ����
	int   m_nHp;   // ѵ��Ѫ��
	int   m_nBeginTime; // ��ʼʱ��
	int   m_nCompleteTime; // ʱ��
	int64 m_nBuildId;
	int   m_nQueueIndex;
};

typedef boost::shared_ptr<TroopTrain> TroopTrainPtr;
typedef std::map<int64,TroopTrainPtr> TroopTrainMap;

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

	// �������
	bool m_bOverFlag;

private:
	int64 m_ID; // ����ID
	int64 m_BuildId; // ������ID
	int   m_nBeginTime; // ���п�ʼʱ��
	int   m_nLevel; // ԭ�ȼ�
	int   m_nCompleteTime; // ���ʱ��
};

typedef boost::shared_ptr<BuildConstruct> BuildConstructPtr;
typedef std::map<int64,BuildConstructPtr> BuildConstructMap;

class GC_CityData;
class GC_TrainData;

class City
{
public:
	City();
	virtual ~City(void);

	void CleanUp();

public:
	void Tick(const TimeInfo& rTimeInfo);
	void OnLogin();

	// ��ʼ������
	void Init();

public:
	void    FileData(GC_CityData* pCityData);

public:
	// ���ĳ����Ӫ���߳�ǽ�ܷ�פ��Ӣ��
	//bool       CheckAssignHero(int64 nBuildId);


	// �ӳ�������ǲһ�ӱ������ͼ
	bool       CheckSendMarchIntoMap(int64 nBuildId);

private:
	// �����������������Դ
	void Tick_Building(const TimeInfo& rTimeInfo);

	// �Ƽ��о�
	void Tick_TechResearch(const TimeInfo& rTimeInfo);

	// ѵ��
	void Tick_Train(const TimeInfo& rTimeInfo);


private:
	BuildingPtr NewBuilding(int nBuildingType);

public:
	void SerializeToDB(DBCity& rDest) const;
	void SerializeFromDB(const DBCity& rSource);

public:
	bool AddBuilding(BuildingPtr Ptr); //����һ������
	bool AddTechnology(TechnologyPtr Ptr); // ����һ���Ƽ�
	bool AddResearch(TechResearchPtr Ptr);
	bool AddConstruct(BuildConstructPtr Ptr);
	bool AddTroopTrain(TroopTrainPtr Ptr);
	
public:
	// ����һ��������
	bool CreateBuilding(int nType,int nSlot);
	bool BuildingLevelUp(int64 nBuildingId);
	bool BeginTrainTroop(int64 nBuildId,int nQueueIndex,int nType,int Count,GC_TrainData* pTrainData);

	bool FileTrainData(TroopTrainPtr Ptr,GC_TrainData* pTrainData);

public:
	BuildingPtr GetBuilding(int64 Id) ;

private:
	// �����б�
	BuildingMap m_mapBuilding;
	bsarray<IDList,BUIDINGTYPE_MAX> m_BuildTypeMap; // ÿһ�ཨ�����б� 

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

public:
	TroopTrainPtr  GetTroopTrain(int64 nBuildId);

private:
	void FinishTroopTrain(TroopTrainPtr Ptr);

private:
	TroopTrainMap    m_mapTrainMap;

private:
	//BarrackTroopMap   m_mapTroop;
	//BarrackArrangeMap m_mapArrange;
	BarrackMarchMap    m_mapMarch;
public:

	// �ؿ�ID
	int    GetTileID() const {return m_tileID;}
	void   SettileID(int val){m_tileID = val;}

	// ����ID
	int64  GetCityID() const {return m_nCityID;}
	void   SetCityID(int64 val) {m_nCityID = val;}
	
	// ���ID
	int64  GetPlayerId() const {return m_nPlayerId;}
	void   SetPlayerId(int64 val){m_nPlayerId = val;}

	//  ���еȼ�
	int    GetLevel() const {return m_nLevel;}
	void   SetLevel(int val) {m_nLevel = val;}

	// ʳ��
	int64  GetFood() const {return m_nFood;}
	void   SetFood(int64 val){m_nFood = val;}

	// ʯ��
	int64  GetStone() const {return m_nStone;}
	void   SetStone(int64 val){m_nStone = val;}

	// ����
	int64  GetIron() const {return m_nIron;}
	void   SetIron(int64 val) {m_nIron = val;}

	tfloat32   GetPosX() const {return m_fPosX;}
	void  SetPosX(tfloat32 val) {m_fPosX = val;}

	tfloat32  GetPosZ() const {return m_fPosZ;}
	void SetPosZ(tfloat32 val) {m_fPosZ = val;}

	int64  GetGold() const {return m_nGold;}
	void   SetGold(int64 val){m_nGold=val;}

private:
	
	int   m_tileID; //�ؿ�ID
	int64 m_nCityID; //����ID
	int64 m_nPlayerId; // ���Id
	int   m_nLevel;  // ���еȼ�
	int64 m_nFood; //ʳ��
	int64 m_nStone; //ʯ��
	int64 m_nIron;  // ����
	int64 m_nGold;
	tfloat32 m_fPosX;
	tfloat32 m_fPosZ;
};

typedef boost::shared_ptr<City> CityPtr;
#endif