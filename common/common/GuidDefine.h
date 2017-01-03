#ifndef _GUIDDEFINE_H_
#define _GUIDDEFINE_H_

#include "Base.h"
#include "GuidGenerator.h"

class GuidType
{
public:
	enum CONSTANT_VALUE
	{
		CHAR		= 0,	// 角色
		CITY        = 1,    // 城市
		BUILDING	= 2,	// 建筑
		HERO        = 3,    // 英雄
		MARCH       = 4,    // March
		TROOP       = 5,    // 军队

		MAX				//数量
	};
};


GUIDDEF_DECL(Char);
GUIDDEF_DECL(City);
GUIDDEF_DECL(Building);
GUIDDEF_DECL(Hero);
GUIDDEF_DECL(March);
GUIDDEF_DECL(Troop);
void InitGuidModule();

#endif