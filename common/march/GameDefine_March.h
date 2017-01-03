
#ifndef _GAMEDEFINE_MARCH_H_
#define _GAMEDEFINE_MARCH_H_

#include "Base.h"

#define  MAX_MARCH_TROOPCOUNT 100

//拥有伙伴最大数量
#define MARCH_MAX_COUNT 4

enum MARCHSTATUS
{
	MARCHSTATUS_INVALID = invalid_id,//未激活状态
	MARCHSTATUS_IDLE = 1,// 空闲状态
	MARCHSTATUS_READY,   // 准备出发
	MARCHSTATUS_PROCESS =10, //行进或者停留状态
	MARCHSTATUS_STATION , // 驻扎状态
	MARCHSTATUS_DEFENCE,     // 防御状态
	MARCHSTATUS_FIGHT,       // 战斗状态
	MARCHSTATUS_OVER ,       // 结束状态
	MARCHSTATUS_COLLECT,      // 采集资源

	MARCHSTATUS_MAX,
};

enum MARCHFORCE  // 战斗势力，攻击方还是防守方
{
	MARCHFORCE_ATTACK = 0,
	MARCHFORCE_DEFENCE,
};

#endif