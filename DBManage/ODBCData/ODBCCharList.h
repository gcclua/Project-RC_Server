////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家角色列表
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_CHARLIST_H_
#define _ODBC_CHARLIST_H_
#include "DataBase/ODBCBase.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_CharList.h"

class ODBCCharList:public ODBCBase
{
public:
	ODBCCharList(ODBCInterface* pInterface);

	bool	Load();
	bool	ParseResult(DBCharDataList* pResult);

public:
	void	SetAccName(const ACCOUNTNAME& rAccName);
private:
	ACCOUNTNAME m_AccName;
};

#endif