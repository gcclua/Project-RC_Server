#ifndef _BASEMANAGER_H_
#define _BASEMANAGER_H_
#pragma once

#include "Base.h"

class User;
struct DBFullUserData;

class BaseManager
{
public:
	BaseManager(User &rUser)
		: m_rUser(rUser)
	{
	}
	virtual ~BaseManager(void){};

	virtual void	Init() = 0;
	virtual void	OnLogin() = 0;
	virtual void	SerializeFromDB(const DBFullUserData& rSource) = 0;
	virtual void	SerializeToDB(DBFullUserData& rDesc) = 0;
	virtual void    Tick(const TimeInfo& rTimeInfo) = 0;

protected:
	User        &m_rUser;
};



#endif
