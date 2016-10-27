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
	};
	
	enum	ODBC_ERROR
	{
		DB_SAME_PRI_KEY = 2601, //�ظ��ؼ��ֶ�
	};
protected:
	int				mResultCount;
	bool			mResult;
	DB_NAMES		mDBName;
	DBOP_TYPE		mOPType;
	ODBCInterface*	mInterface;
	DB_QUERY*		GetInternalQuery();

	LONG_DB_QUERY*	GetLongInterQuery();

	int				GetInternalAffectCount();
	
	bool			IsPrepare();
	bool            CheckDBConnect(const char* pInfo); // ���DB�������Ƿ�������������5������
	
	bool			LongLoad();
	bool			LongSave();
public:
	

	ODBCBase();
	VOID			SetDBName(DB_NAMES dbName);
	tuint32			GetResultCount();
	virtual bool	Load();
	virtual bool	AddNew();
	virtual bool	Delete();
	virtual bool	Save();

	int				GetErrorCode();
	char*			GetErrorMessage();
};

#endif