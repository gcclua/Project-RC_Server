////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_TROOPTRAINDATA_H_
#define _ODBC_TROOPTRAINDATA_H_

#include "Base.h"
#include "DataBase/ODBCBase.h"
#include "DBStruct/DBStruct_City.h"

class ODBCTroopTrainData:public ODBCBase
{
private: 
	int64	m_Id;
	int64   m_CityId;
public:
	ODBCTroopTrainData(ODBCInterface* pInterface);
	virtual bool	Load();
	virtual bool	Save(DBTroopTrain* pSource);
	virtual bool	ParseResult(DBCity* pResult);

public:
	void			SetId(int64 guid);
	int64			GetId();

	void            SetCityId(int64 cityId);
	int64           GetCityId();
};

#endif