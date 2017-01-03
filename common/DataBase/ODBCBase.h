////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺15:23 2013-11-14
//             ˵����
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
		DB_INIT_EMPTY,	//��ʼ״̬
	};
	
#ifdef __WINDOWS__
	enum	ODBC_ERROR
	{
		DB_SAME_PRI_KEY = 2601, //�ظ��ؼ��ֶ�
	};
#else 
	enum	ODBC_ERROR
	{
		DB_SAME_PRI_KEY = 1062, //�ظ��ؼ��ֶ�
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
	bool			CheckDBConnect(const tchar* pInfo);		//���DB�������Ƿ�������������5������

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