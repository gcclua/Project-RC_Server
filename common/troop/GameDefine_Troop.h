
#ifndef _GAMEDEFINE_TROOP_H_
#define _GAMEDEFINE_TROOP_H_

#include "Base.h"

enum TROOPTYPE
{
	TROOPTYPE_INVILID = 0,
	TROOPTYPE_INFANTRY = 1,    // 步兵
	TROOPTYPE_HEAVYSHIELD,     // 重盾步兵
	TROOPTYPE_CAVALRY,         // 骑兵
	TROOPTYPE_ARCHER,          // 弓箭兵
	TROOPTYPE_ARTILLERY,       // 火炮

	TROOPTYPE_MAX,             // 兵种总数
};

// 阵型最大的位置
#define  TROOP_ARRANGE_MAX_POSITION 9 

// 最大的队列数
#define  TROOP_QUEUE_MAX_COUNT 5

// 每队兵的最大数量
#define  TROOP_QUEUE_MAX_SIGCOUNT 18

#define TROOP_OWNSKILL 6

typedef IDContainer_T<TROOP_OWNSKILL> TroopOwnSkillList;

typedef std::map<int64,int64> BarrackMarchMap;

#endif