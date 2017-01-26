
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
	int64  m_ID; // �Ƽ�ID
	int    m_nLevel; // �ȼ�
	int    m_nType;  // ����
	int64  m_nCityID; // ��������
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
	int64 m_ID; // ����ID
	int   m_nType; // ���е�����
	int   m_nBeginTime; // ���п�ʼʱ��
	int   m_nLevel; // ԭ�ȼ�
	int   m_nCompleteTime; // ���ʱ��
	int64  m_nCityID; // ��������
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
	int   m_nType; // ��������
	int   m_nBeginTime; // ��ʼʱ��
	int   m_nCompleteTime; // ���ʱ��
	int64 m_nCityID; // ��������
	int   m_nHp;   // ѵ��Ѫ��
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
	int64 m_ID; //����Guid
	int   m_nLevel; // �ȼ�
	int   m_nSlot;  // λ��
	int   m_nType;  // ��������
	int64  m_nCityID; // ��������
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
	int64 m_ID; // ����ID
	int64 m_BuildId; // ������ID
	int   m_nBeginTime; // ���п�ʼʱ��
	int   m_nLevel; // ԭ�ȼ�
	int   m_nCompleteTime; // ���ʱ��
	int64  m_nCityID; // ��������
};


// ��ҳ�����Ϣ
struct DBCity
{
public:
	DBCity(){CleanUp();};
	~DBCity(){};

	void CleanUp( );
	void CopyFrom(const DBCity& rSource);

public:
	int   m_tileID; //�ؿ�ID
	int64 m_nCityID; //����ID
	int64 m_nPlayerId; // ���Id
	int   m_nLevel;  // ���еȼ�
	int64 m_nFood; //ʳ��
	int64 m_nStone; //ʯ��
	int64 m_nIron;  // ����
	int64 m_nGold;
	tfloat32   m_fPosX;
	tfloat32   m_fPosZ;
	DBBuilding m_BuildingList[BUILDING_MAX_SLOT]; // ���еĽ����б�
	DBTechnology m_TechList[TECHNOLOGYTYPE_MAX];// ���еĿƼ��б�
	DBTechResearch m_TechResearchList[MAX_CITY_RESEARCH_COUNT]; // �����о��Ķ���
	DBBuildConstruct m_ConstructList[MAX_CITY_CONSTRUCT_COUNT]; // ���ڽ���Ķ���
	DBTroopTrain  m_TrainList[BUILDING_BARRACK_MAX+BUILDING_WALL_MAX];// ѵ������
	//DBTroop          m_TroopList[MAX_TROOP_QUEUE];                // �����б�
	

	
};

typedef DBCommonData<DBCity> DBCityData;
typedef boost::shared_ptr<DBCityData> DBCityDataPtr;



#endif
