#ifndef _GAMEDEFINE_OBSTACLE_H_
#define _GAMEDEFINE_OBSTACLE_H_

#include "Base.h"

#define OBSTACLESCALE 2

class ObstacleValue
{
public:
	enum
	{
		INVALID = -1,		//无效值
		WALKABLE = 0,		//可行走
		WALKDISABLE = 1,	//不可行走
	};
};

#endif
