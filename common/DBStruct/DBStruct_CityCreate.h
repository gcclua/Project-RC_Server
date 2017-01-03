
#ifndef __DBSTRUCT_CITYCREATE_H__
#define __DBSTRUCT_CITYCREATE_H__

#include "DBStruct/DBStruct_Hero.h"
#include "DBStruct/DBStruct_City.h"
#include "DBStruct/DBStruct_March.h"

// 玩家城市信息
struct DBCityCreate
{
public:
	DBCityCreate(){CleanUp();};
	~DBCityCreate(){};

	void CleanUp( );
	void CopyFrom(const DBCityCreate& rSource);

public:
	int   m_tileID; //地块ID
	int64 m_nCityID; //城市ID
	int64 m_UserId; // 玩家Id
	int   m_nLevel;  // 城市等级
	int   m_nPosX;   // 
	int   m_nPosZ;
	int64 m_nFood;
	int64 m_nStone;
	int64 m_nIron;
	int64 m_nGold;
	bsvector<DBBuilding> m_lstBuilding;
	DBHero m_Hero;
	bsvector<DBMarch> m_lstMarch;
	

	
};

typedef DBCommonData<DBCity> DBCityData;
typedef boost::shared_ptr<DBCityData> DBCityDataPtr;



#endif
