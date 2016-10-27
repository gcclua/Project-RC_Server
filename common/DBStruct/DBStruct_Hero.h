
#ifndef __DBSTRUCT_HERO_H__
#define __DBSTRUCT_HERO_H__

#include "DBStruct.h"
#include "troop/GameDefine_Troop.h"



// 玩家城市信息
struct DBHero
{
public:
	DBHero(){CleanUp();};
	~DBHero(){};

	void CleanUp( );
	void CopyFrom(const DBHero& rSource);

public:
	int     m_nType;    //英雄类型
	int     m_nLevel;   //等级
	int     m_nQuality; // 品质
	int64   m_nCityID;  // 城市ID
	int64   m_nExp;     // 经验值
};

typedef DBCommonData<DBHero> DBHeroData;
typedef boost::shared_ptr<DBHeroData> DBHeroDataPtr;


#endif
