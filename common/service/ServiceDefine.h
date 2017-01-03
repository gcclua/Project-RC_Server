
#ifndef __SERVERDEFINE_H__
#define __SERVERDEFINE_H__

#include "Base.h"

class ServiceID
{
public:
	enum 
	{
		DBAGENT = 0,       //存储
		LOGIN,             //登录
		WORLDMAP,          //地图
		WORLDUSER,         //玩家
		SCENE,
		LOG,               //日志
		MAX,
	};
};

class ServiceStatus
{
public:
	enum 
	{
		EMPTY = 0,
		OPENUP,
		OPENUP_PROCESS,
		OPENUP_OK,

		RUNNING,
		SHUTDOWN,
		SHUTDOWN_PROCESS,
		SHUTDOWN_OK,

		FINALSAVE,
		FINALSAVE_PROCESS,
		FINALSAVE_OK,
	};
};
class ServiceManagerStatus
{
public:
	enum 
	{
		EMPTY = 0,
		OPENUP,
		RUNNING,
		SHUTDOWN,
		FINALSAVE,
	};
};

class ServiceRunState
{
public:
	enum
	{
		NORMAL = 0,
		SLOWLY,
		PAUSE,
	};
};

#endif
