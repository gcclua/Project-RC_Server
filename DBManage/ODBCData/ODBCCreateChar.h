////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺11:08 2013-11-15 
//			   ˵����������ݴ洢
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_CREATECHAR_H_
#define _ODBC_CREATECHAR_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_User.h"

class ODBCCreateChar:public ODBCBase
{
private: 
	tuint32 m_CRCValue;
public:
	ODBCCreateChar(ODBCInterface* pInterface);

	bool	Save(DBFullUserData* pSource);
	bool	ParseResult(tint32* pResult);

public:
	tuint32 GetCRCValue(){return m_CRCValue;}
};

#endif