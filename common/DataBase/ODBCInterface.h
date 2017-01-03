////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：15:22 2013-11-14
//             说明：
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#ifndef		_ODBC_INTERFACE_H_
#define		_ODBC_INTERFACE_H_ 
#include "Base.h"
#include "DBStruct/DBStruct.h"
#include "DataBase/SqlTemplate.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

#include "sqlext.h"
#include "sql.h"


#define MAX_LONG_COLUMN_BUFFER  200000
#define MAX_COLUMN_BUFFER		32768
#define MAX_ERROR_MSG_LENGHT    255	 

#define CR_SERVER_LOST 2013
#define CR_CONN_HOST_ERROR 2003
#define CR_SERVER_GONE_ERROR 2006
#define MAX_RECONNECT_TIMES 3

class ODBCInterface
{
public:
	enum { 
			MAXCOL=64, 
			MAXREDUNDANCECOL=250,
			BLOBBATCH	=	10000,
			QUERYOK		=	0,
			QUERYNULL	=	-100, 
			QUERYEOF	=	-101, 
			QUERYNOCOL	=	-102, 
			QUERYERROR	=	-103 
		 };

	enum FetchType {
		INVALID_TYPE,
		MULTY_CACHE,
		LONG_CACHE,
		SINGLE_CACHE,
	};
private:
	tint16			m_nDBExecIndex;
private:
	void			SaveErrorSQL(const tchar* pLog,const tchar* pSQL);
public:
	bool			mConnected;

	SQLHENV			hEnv;												// 数据库环境
	SQLHDBC			hDbc;												//  
	SQLRETURN		mResult;											// Sql查询返回值
	tchar			Col[MAXCOL][MAX_COLUMN_BUFFER];						// Column 数
	tchar			m_ResultCache[32];									// 查询缓存
	tchar			m_LongResultCache[MAX_COLUMN_BUFFER];				// 查询缓存
	tchar			m_FetchAlgoType;
	
	
	tchar    mConnectStr[DATABASE_STR_LEN];
	tchar    mUserName[DB_USE_STR_LEN];
	tchar    mPassWord[DB_PASSWORD_STR_LEN];

	SQLLEN		mAffectCount;						// 影响行数
	SQLHSTMT	hStmt;								// 状态句柄
	SQLSMALLINT mColCount;							// Column 数量

	DB_QUERY		m_Query;							//查询结构体
	LONG_DB_QUERY	m_LongQuery;						//大结构体
	SQLINTEGER	mErrorCode;
	SQLCHAR		mErrorMsg[MAX_ERROR_MSG_LENGHT];		//消息错误内容
public:

	ODBCInterface();
	~ODBCInterface();

	bool Connect(const tchar *ConnectStr, 
				 const tchar *UserName=NULL, 
				 const tchar *Password=NULL);
	bool Connect();

	// 如果是断线了，重连3次，重连成功返回true，否则返回false
	bool Reconnect();

	bool Close();
	
	tint32	 GetError()
	{
		return mErrorCode;
	}

	tchar* GetErrorMsg()
	{
		return (tchar*)mErrorMsg;
	}

	bool IsConnected()
	{
		return mConnected;
	}

	tint32 GetAffectedRowCount()
	{
		return static_cast<tint32>(mAffectCount);
	}

	bool	IsPrepare()
	{
		return IsConnected();
	}
	
	void Clear();
	void Clear_NoCommit();

	bool Fetch();
	bool LongFetch();

	/*
	zhangning
	将堆中的数据放到栈中缓存，逼不得已不要使用
	*/
	bool			FetchEx();
	bool			GetDataEx(tint32 ColIndex, tchar* Buffer, tint32 BufferLen);
	tint32			GetIntEx(tint32 ColIndex,tint32& ErrorCode);
	tuint32			GetUIntEx(tint32 ColIndex,tint32& ErrorCode);
	tint32			Get64Ex(tint32 ColIndex, tuint32& High, tuint32& Low, tint32& ErrorCode);
	tuint64			GetU64Ex(tint32 ColIndex, tint32& ErrorCode);
	tint64          GetLongLongEx(tint32 ColIndex,  tint32& ErrorCode);
	void			GetStringEx(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);
	void			GetFieldEx(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode); //需要在函数外面转化成游戏需要的数据
	tuint16			GetUShortEx(tint32 ColIndex,tint32& ErrorCode) { return (tuint16)GetIntEx(ColIndex,ErrorCode);}
	tbyte			GetBYTEEx(tint32 ColIndex,tint32& ErrorCode) { return(tbyte)GetIntEx(ColIndex,ErrorCode);}
	tword			GetWORDEx(tint32 ColIndex,tint32& ErrorCode) { return(tword)GetIntEx(ColIndex,ErrorCode); }
	tint16			GetShortEx(tint32 ColIndex,tint32& ErrorCode)	 { return (tint16)GetIntEx(ColIndex,ErrorCode);}
	void			GetDoubleFieldEx(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode);
	bool			LongExecuteEx();

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

	tint32			GetInt(tint32 	ColIndex,tint32& ErrorCode);
	tuint32			GetUInt(tint32	ColIndex,tint32& ErrorCode);
	tfloat32		GetFloat(tint32	ColIndex,tint32& ErrorCode);
	tuint16			GetUShort(tint32 ColIndex,tint32& ErrorCode)
	{
		return (tuint16)GetInt(ColIndex,ErrorCode);
	}
	tbyte			GetBYTE(tint32		ColIndex,tint32& ErrorCode)
	{
		return(tbyte)GetInt(ColIndex,ErrorCode);
	}
	tword			GetWORD(tint32		ColIndex,tint32& ErrorCode)
	{
		return(tword)GetInt(ColIndex,ErrorCode);
	}
	tint16			GetShort(tint32 ColIndex,tint32& ErrorCode)	
	{
		return (tint16)GetInt(ColIndex,ErrorCode);
	}
	tint64			GetInt64(tint32 ColIndex, tint32& ErrorCode);
	tuint64			GetUInt64(tint32 	ColIndex,tint32& ErrorCode);

	tint32		Get64(tint32 ColIndex, tuint32& High, tuint32& Low, tint32& ErrorCode);
	tint64		GetLongLong(tint32 ColIndex,  tint32& ErrorCode);

	//会自动在最后加\0
	void			GetString(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);		
	void			GetField(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);
	void			GetLongField(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);
	void			GetDoubleField(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode);
	// 为了不影响现有逻辑，特殊针对用两个varchar(255)来存CHAR数组的解析
	void			GetDoubleFieldS(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode);
	
	//分析SqlState
	void			DiagState();
	void			DiagStateEx();

	void			CleanEnv();
	void			SetDBExceIndex(tint16 nIndex){m_nDBExecIndex = nIndex;}
};

#endif


