////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺11:08 2013-11-15 
//			   ˵�������ͼ���ݴ洢
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_MAPMARCHDATA_H_
#define _ODBC_MAPMARCHDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_March.h"

class ODBCMapMarchData:public ODBCBase
{
private: 

public:
	ODBCMapMarchData(ODBCInterface* pInterface);
	virtual bool	Load();
	virtual bool	ParseResult(DBMarchDataPtr* pResult);

};

#endif