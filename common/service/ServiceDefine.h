
#ifndef __SERVERDEFINE_H__
#define __SERVERDEFINE_H__

#include "Base.h"

class ServiceID
{
public:
	enum 
	{
		DBAGEMT = 0,       //�洢
		LOGIN,             //��¼
		WORLDMAP,          //��ͼ
		WORLDUSER,         //���
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
