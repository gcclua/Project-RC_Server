////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_BUILDINGDATA_H_
#define _ODBC_BUILDINGDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_City.h"

class ODBCBuildIngData:public ODBCBase
{
	
private: 
	int64 m_nCityId;
public:
	ODBCBuildIngData(ODBCInterface* pInterface);
	virtual bool	Load();
	virtual bool	Save(DBBuilding* pSource);
	virtual bool	ParseResult(DBCity* pResult);

public:

	void			SetCityId(int64 guid);
	int64			GetCityId();
};

#endif