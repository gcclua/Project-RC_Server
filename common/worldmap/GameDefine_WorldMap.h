
#ifndef _GAMEDEFINE_WORLDMAP_H_
#define _GAMEDEFINE_WORLDMAP_H_

#include "Base.h"

//最大的地块数
#define  MAX_TILE_NUM 10000

// 地块类型
enum TILE_TYPE
{
	TILE_TYPE_INVALID = 0,
	TILE_TYPE_CITY = 1, //城市地块
	TILE_TYPE_PLAIN, // 平原
	TILE_TYPE_SOURCE, // 资源
	TILE_TYPE_WILD,    // 野地
};

#endif