#ifndef _GAMEDEFINE_OBSTACLE_H_
#define _GAMEDEFINE_OBSTACLE_H_

#include "Base.h"

#define OBSTACLESCALE 2

class ObstacleValue
{
public:
	enum
	{
		INVALID = -1,		//��Чֵ
		WALKABLE = 0,		//������
		WALKDISABLE = 1,	//��������
	};
};

#endif
