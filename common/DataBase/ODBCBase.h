////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：15:23 2013-11-14
//             说明：
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef _ODBC_BASE_H_
#define _ODBC_BASE_H_
#include "Base.h"
#include "ODBCInterface.h"	

class ODBCBase
{
public:
	enum	DBOP_TYPE
	{
		DB_LOAD,
		DB_SAVE,
		DB_ADDNEW,
		DB_DELETE,
		DB_INIT_EMPTY,	//初始状态
	};
	
#ifdef __WINDOWS__
	enum	ODBC_ERROR
	{
		DB_SAME_PRI_KEY = 2601, //重复关键字段
	};
#else 
	enum	ODBC_ERROR
	{
		DB_SAME_PRI_KEY = 1062, //重复关键字段
	};
#endif
protected:
	tint32			mResultCount;
	bool			mResult;
	DBOP_TYPE		mOPType;
	ODBCInterface*	mInterface;

	DB_QUERY*		GetInternalQuery();	   
	LONG_DB_QUERY*	GetLongInterQuery();	
	tint32			GetInternalAffectCount();
	
	bool			IsPrepare();	
	bool			CheckDBConnect(const tchar* pInfo);		//检查DB的连接是否正常，并尝试5次重连

	bool			LongLoad_Execute();
	bool			LongSave_Execute();
	bool			LongDelete_Execute();	
	bool			LongLoadEx_Execute();

	bool			Load_Execute();
	bool			AddNew_Execute();
	bool			Delete_Execute();
	bool			Save_Execute();	
public:	  
	ODBCBase();
	tuint32			GetResultCount();  	

	tint32			GetErrorCode();
	tchar*			GetErrorMessage();
};

#endif