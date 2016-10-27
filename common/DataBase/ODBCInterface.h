#ifndef		_ODBC_INTERFACE_H_
#define		_ODBC_INTERFACE_H_

#include "Base.h"
#include "DBStruct/DBStruct.h"

#if defined(_WIN32)
	#include <Windows.h>
#endif


#include "sqlext.h"
#include "sql.h"



#define MAX_COLUMN_NAME			30
#define MAX_COLUMN_BUFFER		2049

#define MAX_LONG_COLUMN_BUFFER  200000

#define MAX_ERROR_MSG_LENGHT    255

class ODBCInterface
{
	enum { 
			MAXCOL=64, 
			BLOBBATCH	=	10000,
			QUERYOK		=	0,
			QUERYNULL	=	-100, 
			QUERYEOF	=	-101, 
			QUERYNOCOL	=	-102, 
			QUERYERROR	=	-103 
		 };

	bool			mConnected;
public:
	SQLHENV			hEnv;												// 数据库环境
	SQLHDBC			hDbc;												//  
	SQLRETURN		mResult;											// Sql查询返回值
	char			Col[MAXCOL][MAX_COLUMN_BUFFER];						// Column 数据
	
	
	char    mConnectStr[DATABASE_STR_LEN];
	char    mUserName[DB_USE_STR_LEN];
	char    mPassWord[DB_PASSWORD_STR_LEN];

	SQLINTEGER	mAffectCount;						// 影响行数
	SQLHSTMT	hStmt;								// 状态句柄
	SQLSMALLINT mColCount;							// Column 数量
	SQLCHAR		ColName[MAXCOL][MAX_COLUMN_NAME];	// Column 名称
	SQLINTEGER  mCollocate[MAXCOL];					// Col    位置

	DB_QUERY		m_Query;							//查询结构体
	LONG_DB_QUERY	m_LongQuery;						//大结构体
	SQLINTEGER	mErrorCode;
	SQLCHAR		mErrorMsg[MAX_ERROR_MSG_LENGHT];						//消息错误内容
public:

	ODBCInterface();
	~ODBCInterface();

	bool Connect(const char *ConnectStr, 
				 const char *UserName=NULL, 
				 const char *Password=NULL);
	bool Connect();

	bool Close();
	
	int	 GetError()
	{
		return mErrorCode;
	}

	char* GetErrorMsg()
	{
		return (char*)mErrorMsg;
	}

	bool IsConnected()
	{
		return mConnected;
	}

	int GetAffectedRowCount()
	{
		return mAffectCount;
	}

	bool	IsPrepare()
	{
		return IsConnected();
	}
	
	void Clear();

	bool Fetch();
	bool LongFetch();

	DB_QUERY&	GetQuery()
	{
		return m_Query;
	}

	LONG_DB_QUERY&	GetLongQuery()
	{
		return m_LongQuery;
	}

	bool		Execute();		
	bool		LongExecute();

	int			    GetInt(int 		ColIndex,int& ErrorCode);
	tuint32			GetUInt(int		ColIndex,int& ErrorCode);
	FLOAT			GetFloat(int	ColIndex,int& ErrorCode);
	UCHAR			GetBYTE(int		ColIndex,int& ErrorCode)
	{
		return(UCHAR)GetInt(ColIndex,ErrorCode);
	}
	WORD			GetWORD(int		ColIndex,int& ErrorCode)
	{
		return(WORD)GetInt(ColIndex,ErrorCode);
	}
	SHORT			GetShort(int ColIndex,int& ErrorCode)	
	{
		return (SHORT)GetInt(ColIndex,ErrorCode);
	}

	void			GetString(int nCol, char*buf,int BufLen,int& ErrorCode);		
	void			GetField(int nCol, char*buf,int BufLen,int& ErrorCode);
	void			GetLongField(int nCol, char*buf,int BufLen,int& ErrorCode);

	//分析SqlState
	void			DiagState();
	void			DiagStateEx();
	void			SaveLog(const char* pLog);
	void			SaveErrorLog(const char* pLog);

	void			CleanEnv();

};

#endif


