#ifndef _CITYMANAGER_H_
#define _CITYMANAGER_H_

#pragma once

#include "../BaseManager.h"

#include "city/GameStruct_City.h"


class CityManager : public BaseManager
{
public:
	CityManager(User &rUser);
	virtual ~CityManager(void);

	void		Init();
	void		SerializeFromDB(const DBFullUserData& rSource);
	void		SerializeToDB(DBFullUserData& rDesc) ;

	void        Tick(const TimeInfo& rTimeInfo);

	void		OnLogin();

protected:

	CityPtr     m_CityPtr;
};


#endif
