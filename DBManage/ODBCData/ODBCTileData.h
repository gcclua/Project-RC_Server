#ifndef _ODBC_TILEDATA_H_
#define _ODBC_TILEDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_WordMap.h"

class ODBCTileData:public ODBCBase
{
	int64			m_CharGuid;
	uint32          m_CRCValue;
public:
	ODBCTileData(ODBCInterface* pInterface);

	virtual bool	Load();
	virtual bool	Save(DBTileDataPtr* pSource);
	virtual bool	ParseResult(DBTileDataPtr* pResult);
};

#endif
