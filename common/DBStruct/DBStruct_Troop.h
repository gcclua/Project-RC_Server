
#ifndef __DBSTRUCT_TROOP_H__
#define __DBSTRUCT_TROOP_H__

#include "DBStruct.h"
#include "troop/GameDefine_Troop.h"



// 玩家城市信息
struct DBTroop
{
public:
	DBTroop(){CleanUp();};
	~DBTroop(){};

	void CleanUp( );
	void CopyFrom(const DBTroop& rSource);

	void InitTroop(int nArrangeIndex,int nQueueIndex,int64 nMarchId);

public:
	int64   m_nId;
	int     m_nType; //兵类型
	int     m_nLevel;//等级
	int     m_nCount; // 数量
	int64   m_nMarchId; // 所属兵营ID
	int     m_nHp;       // 当前总血量
	int     m_nArrangeIndex; // 队形的位置
	int     m_nQueueIndex;   // 队列的位子
	
};

typedef DBCommonData<DBTroop> DBTroopData;
typedef boost::shared_ptr<DBTroopData> DBTroopDataPtr;


#endif
