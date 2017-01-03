////////////////////////////////////////////////////////////////////////////////////////
//时间：2014年7月2日14:12:35
//说明：随机名字数据库
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_RandomName_H_
#define _ODBC_RandomName_H_
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_RandomName.h"

class ODBCRandomName:public ODBCBase
{
public:
	ODBCRandomName(ODBCInterface* pInterface);

	bool	Load();		
	bool	ParseResult(DBRandomNameList* pResult);
};

#endif//_ODBC_RandomName_H_