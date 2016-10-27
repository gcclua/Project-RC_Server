
#ifndef __SERVERDEFINE_H__
#define __SERVERDEFINE_H__

#include "Base.h"

class ServiceID
{
public:
	enum 
	{
		DBAGEMT = 0,       //´æ´¢
		LOGIN,             //µÇÂ¼
		WORLDMAP,          //µØÍ¼
		WORLDUSER,         //Íæ¼Ò
		SCENE,
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
