////////////////////////////////////////////////////////////////////////////////////////
//ʱ�䣺2014��7��2��14:12:35
//˵��������������ݿ�
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