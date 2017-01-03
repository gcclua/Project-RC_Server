////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺11:08 2013-11-15 
//			   ˵����������ݴ洢
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_CREATECITY_H_
#define _ODBC_CREATECITY_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_CityCreate.h"

class ODBCCreateCity:public ODBCBase
{
private: 
	tuint32 m_CRCValue;
public:
	ODBCCreateCity(ODBCInterface* pInterface);

	bool	Save(DBCityCreate* pSource);
	bool	ParseResult(tint32* pResult);

public:
	tuint32 GetCRCValue(){return m_CRCValue;}
};

#endif