////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺11:08 2013-11-15 
//			   ˵����������ݴ洢
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_HERODATA_H_
#define _ODBC_HERODATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_User.h"

class ODBCHeroData:public ODBCBase
{
private: 
	int64   m_CityId;
public:
	ODBCHeroData(ODBCInterface* pInterface);

	virtual bool	Load();
	virtual bool	Save(DBHero* pSource);
	virtual bool	ParseResult(DBFullUserData* pResult);

public:
	void            SetCityId(int64 cityId);
	int64           GetCityId();
};

#endif