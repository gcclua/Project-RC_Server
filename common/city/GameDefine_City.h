
#ifndef _GAMEDEFINE_CITY_H_
#define _GAMEDEFINE_CITY_H_

#include "Base.h"
#include "building/GameDefine_Building.h"
#include "troop/GameDefine_Troop.h"
// 最大的研究队列数
#define MAX_CITY_RESEARCH_COUNT 2
// 最大的建造队列数
#define MAX_CITY_CONSTRUCT_COUNT 2

// 最大的兵的队列数
#define MAX_TROOP_QUEUE          ((BUILDING_BARRACK_MAX+BUILDING_WALL_MAX)*TROOP_QUEUE_MAX_COUNT)     

// 城市地基类型
enum CITY_SLOT
{
	CITY_SLOT_INNERBIG = 1,     //城内大
	CITY_SLOT_INNERMIDDLE,  //城内中
	CITY_SLOT_INNERSMALL,   //城内小

	CITY_SLOT_OUTERBIG,     //城外大
	CITY_SLOT_OUTERMIDDLE,  //城外中
	CITY_SLOT_OUTERSMALL,   //城外小
};

enum SOURCETYPE
{
	SOURCETYPE_FOOD = 1,       // 食物
	SOURCETYPE_STONE,          // 石料
	SOURCETYPE_IRON,           // 铁矿
	SOURCETYPE_GOLD,           // 金币
};

enum TECHNOLOGYTYPE
{
	TECHNOLOGYTYPE_MIN = 0,
	TECHNOLOGYTYPE_FOOD = TECHNOLOGYTYPE_MIN,  // 产生粮食的速度
	TECHNOLOGYTYPE_STONE, // 生成石料的速度
	TECHNOLOGYTYPE_IRON,  // 生成铁矿的速度
	TECHNOLOGYTYPE_TRAIN, // 训兵的速度

	TECHNOLOGYTYPE_MAX,   // 最大的科技数
};


#endif