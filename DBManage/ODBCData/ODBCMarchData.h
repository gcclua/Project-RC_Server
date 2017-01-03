////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_MARCHDATA_H_
#define _ODBC_MARCHDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_User.h"

class ODBCMarchData:public ODBCBase
{
private: 
	int64	m_MarchId;
	int64   m_CityId;
public:
	ODBCMarchData(ODBCInterface* pInterface);
	virtual bool	Load();
	virtual bool	Save(DBMarch* pSource);
	virtual bool	ParseResult(DBFullUserData* pResult);

public:
	void			SetMarchId(int64 guid);
	int64			GetMarchId();

	void            SetCityId(int64 cityId);
	int64           GetCityId();
};

#endif