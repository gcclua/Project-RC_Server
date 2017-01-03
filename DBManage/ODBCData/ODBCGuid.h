////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：14:10 2014-06-20 
//			   说明：GUID数据存储
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_GUID_H_
#define _ODBC_GUID_H_

#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct.h"

class ODBCGuid : public ODBCBase
{																			                    
public:
	ODBCGuid(ODBCInterface* pInterface);

public:
	bool			Save(DBGuidData* pSource);
};

#endif