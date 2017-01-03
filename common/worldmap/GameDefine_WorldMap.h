
#ifndef _GAMEDEFINE_WORLDMAP_H_
#define _GAMEDEFINE_WORLDMAP_H_

#include "Base.h"

//最大的地块数
#define  MAX_TILE_NUM 10000

#define  TILE_LOCK_TIME 30

// 地块类型
enum TILE_TYPE
{
	TILE_TYPE_INVALID = 0,
	TILE_TYPE_CITY = 1, //城市地块
	TILE_TYPE_PLAIN, // 平原
	TILE_TYPE_SOURCE, // 资源
	TILE_TYPE_WILD,    // 野地
};

enum TILE_STATE
{
	TILE_STATE_IDLE,// 空闲
	TILE_STATE_LOCK,// 锁定
	TILE_STATE_TAKE,// 建城或者生成资源点
};

#endif