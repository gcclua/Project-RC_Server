
#ifndef _GAMESTRUCT_MARCH_H_
#define _GAMESTRUCT_MARCH_H_

#include "Base.h"
#include "GameDefine_March.h"
#include "service/TimeInfo.h"
#include "troop/GameStruct_Troop.h"
#include "hero/GameStruct_Hero.h"
#include "DBStruct/DBStruct_March.h"
#include "Scene/GameStruct_Scene.h"

class March
{
public:
	March();
	virtual ~March();

	void CleanUp();

public:
	void SerializeToDB(DBMarch& rDest) const;
	void SerializeFromDB(const DBMarch& rSource);

public:
	
	ScenePos  GetPosX() const {return m_pos;}
	void  SetPosX(ScenePos nVal){m_pos = nVal;}


	int   GetBeginTime() const {return m_nBeginTime;}
	void  SetBeginTime(int nVal) {m_nBeginTime = nVal;}

	int   GetEndTime() const {return m_nEndTime;}
	void  SetEndTime(int nVal) {m_nEndTime = nVal;}

	int64 GetMarchId() const {return m_nMarchId;}
	void  SetMarchId(int64 nVal) {m_nMarchId = nVal;}

	int64 GetPlayerId() const {return m_nPlayerId;}
	void  SetPlayerId(int64 nVal) {m_nPlayerId = nVal;}

	int64 GetCityId() const {return m_nCityId;}
	void  SetCityId(int64 nVal) {m_nCityId = nVal;}

	int   GetStatus() const {return m_nStatus;}
	void  SetStatus(int nStatus){m_nStatus = nStatus;}

	HERONAME GetName() const {return m_Hero.GetName();}

public:
	Hero GetHero() {return m_Hero;}
	void SetHero(const Hero& rHero){m_Hero = rHero;}
	
	TroopList_T GetTroopList() {return m_TroopList;}
	void SetTroopList(const TroopList_T& rTroopList) {m_TroopList = rTroopList;}

private:
	// 领军的hero
	Hero m_Hero;

public:

	// 获取每个队伍的数量
	Troop GetQueueTroop(int nIndex);

private:
	TroopList_T m_TroopList;

private:
	ScenePos  m_pos;		//场景坐标
	int    m_nBeginTime; // 出发时间
	int    m_nEndTime;   // 返回时间
	int64  m_nMarchId;   // 唯一标示
	int64  m_nPlayerId;  // 玩家ID
	int64  m_nCityId;    // 城市ID
	int    m_nStatus;    // 状态
	int    m_nSpeed;     // 速度
};
typedef boost::shared_ptr<March> MarchPtr;
#endif