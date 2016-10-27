
#ifndef __DBSTRUCT_MARCH_H__
#define __DBSTRUCT_MARCH_H__

#include "DBStruct.h"
#include "DBStruct_Troop.h"
#include "DBStruct_Hero.h"
#include "Scene/GameStruct_Scene.h"

// 玩家城市信息
struct DBMarch
{
public:
	DBMarch(){CleanUp();};
	~DBMarch(){};

	void CleanUp( );
	void CopyFrom(const DBMarch& rSource);

public:

	DBHero    m_Hero; // 出战的英雄
	DBTroop   m_TroopList[TROOP_QUEUE_MAX_COUNT];                // 兵种列表

	ScenePos  m_pos;		//场景坐标
	int    m_nBeginTime; // 出发时间
	int    m_nEndTime;   // 返回时间
	int64  m_nMarchId;   // 唯一标示
	int64  m_nPlayerId;  // 玩家ID
	int64  m_nCityId;    // 城市ID
	int    m_nStatus;    // 状态

	
};

typedef DBCommonData<DBMarch> DBMarchData;
typedef boost::shared_ptr<DBMarchData> DBMarchDataPtr;



#endif
