
#ifndef _GAMEDEFINE_MARCH_H_
#define _GAMEDEFINE_MARCH_H_

#include "Base.h"

#define  MAX_MARCH_TROOPCOUNT 100

enum MARCHSTATUS
{
	MARCHSTATUS_PROCESS = 0, //行进或者停留状态
	MARCHSTATUS_STATION = 1, // 驻扎状态
	MARCHSTATUS_DEFENCE,     // 防御状态
	MARCHSTATUS_FIGHT,       // 战斗状态
	MARCHSTATUS_OVER ,       // 结束状态
	MARCHSTATUS_COLLECT,      // 采集资源
};



#endif