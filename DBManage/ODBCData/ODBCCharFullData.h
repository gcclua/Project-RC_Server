#ifndef _DB_CHARFULLDATA_H_
#define _DB_CHARFULLDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_User.h"

class ODBCCharFullData:public ODBCBase
{
	int64			m_CharGuid;
	uint32          m_CRCValue;
public:
	ODBCCharFullData(ODBCInterface* pInterface);

	virtual bool	Load();
	virtual bool	Save(void* pSource);
	virtual bool	ParseResult(void* pResult);

public:
	void			SetCharGuid(int64 guid);
	int64			GetCharGuid();
	uint32          GetCRCValue(){return m_CRCValue;}

private:
	uint32			CalcCRC(void* pSource);
};


#endif