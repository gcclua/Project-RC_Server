////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_TROOPDATA_H_
#define _ODBC_TROOPDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_March.h"

class ODBCTroopData:public ODBCBase
{
	
private: 
	int64 m_nMarchId;
public:
	ODBCTroopData(ODBCInterface* pInterface);
	virtual bool	Load();
	virtual bool	Save(DBTroop* pSource);
	virtual bool	ParseResult(DBMarch* pResult);

public:

	void			SetMarchId(int64 marchId);
	int64			GetMarchId();
};

#endif