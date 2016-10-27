
#ifndef _GAMESTRUCT_BUILDING_H_
#define _GAMESTRUCT_BUILDING_H_

#include "Base.h"
#include "building/GameDefine_Building.h"
#include "service/TimeInfo.h"
#include "DBStruct/DBStruct_City.h"
#include "troop/GameStruct_Troop.h"

class City;


class Building
{
public:
	Building(City &rCity);
	virtual ~Building();

public:
	virtual void OnLevelUp(){};
	virtual int  GetGuildingType() {return 0;};
	virtual void Tick(const TimeInfo& rTimeInfo){};
	virtual void Init(){};

public:
	void SerializeToDB(DBBuilding& rDest);
	void SerializeFromDB(const DBBuilding& rSource);

public:

	// ����ID
	int64      GetID() const {return m_ID;}
	void       SetID(int64 val) { m_ID = val;}

	// �ȼ�
	int        GetLevel() const {return m_nLevel;}
	void       SetLevel(int val){m_nLevel = val;}

	// λ��
	int        GetSlot() const {return m_nSlot;}
	void       SetSlot(int val){m_nSlot = val;}

private:
	City& m_City;

private:
	int64 m_ID; //����Guid
	int   m_nLevel; // �ȼ�
	int   m_nSlot;  // λ��
	int   m_nType;  // ��������


};
typedef boost::shared_ptr<Building> BuildingPtr;
// ����ID�б�������¼ĳЩ�������ж��
typedef std::list<int64> IDList; 

typedef std::map<int64,BuildingPtr> BuildingMap;


class FarmBuilding : public Building
{
	enum 
	{
		BUILDIN_GTYPE = BUIDINGTYPE_FARM,
	};
public:
	FarmBuilding();
	virtual ~FarmBuilding();
public:
	virtual void OnLevelUp() {};
	virtual int  GetBuildingType() {return BUILDIN_GTYPE;}
	virtual void Tick(const TimeInfo& rTimeInfo){};
};

class BarrackBuilding : public Building
{
	enum 
	{
		BUILDIN_GTYPE = BUIDINGTYPE_BARRACKS,
	};
public:
	BarrackBuilding();
	virtual ~BarrackBuilding();

public:
	void SerializeToDB(DBBuilding& rDest);
	void SerializeFromDB(const DBBuilding& rSource);
public:
	virtual void OnLevelUp() {};
	virtual int  GetBuildingType() {return BUILDIN_GTYPE;}
	virtual void Tick(const TimeInfo& rTimeInfo){};
	virtual void Init();



private:
	TroopPtr m_Troop[TROOP_QUEUE_MAX_COUNT];
	int      m_Arrange[TROOP_ARRANGE_MAX_POSITION];
};

typedef boost::shared_ptr<BarrackBuilding> BarrackBuildingPtr;

class WallBuilding : public BarrackBuilding
{
	enum 
	{
		BUILDIN_GTYPE = BUIDINGTYPE_WALL,
	};

	WallBuilding();
	~WallBuilding();
public: 
	virtual void OnLevelUp() {};
	virtual int  GetBuildingType() {return BUILDIN_GTYPE;}
	virtual void Tick(const TimeInfo& rTimeInfo){};



};

typedef boost::shared_ptr<WallBuilding> WallBuildingPtr;

#endif