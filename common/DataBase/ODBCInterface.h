////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺15:22 2013-11-14
//             ˵����
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

	SQLHENV			hEnv;												// ���ݿ⻷��
	SQLHDBC			hDbc;												//  
	SQLRETURN		mResult;											// Sql��ѯ����ֵ
	tchar			Col[MAXCOL][MAX_COLUMN_BUFFER];						// Column ��
	tchar			m_ResultCache[32];									// ��ѯ����
	tchar			m_LongResultCache[MAX_COLUMN_BUFFER];				// ��ѯ����
	tchar			m_FetchAlgoType;
	
	
	tchar    mConnectStr[DATABASE_STR_LEN];
	tchar    mUserName[DB_USE_STR_LEN];
	tchar    mPassWord[DB_PASSWORD_STR_LEN];

	SQLLEN		mAffectCount;						// Ӱ������
	SQLHSTMT	hStmt;								// ״̬���
	SQLSMALLINT mColCount;							// Column ����

	DB_QUERY		m_Query;							//��ѯ�ṹ��
	LONG_DB_QUERY	m_LongQuery;						//��ṹ��
	SQLINTEGER	mErrorCode;
	SQLCHAR		mErrorMsg[MAX_ERROR_MSG_LENGHT];		//��Ϣ��������
public:

	ODBCInterface();
	~ODBCInterface();

	bool Connect(const tchar *ConnectStr, 
				 const tchar *UserName=NULL, 
				 const tchar *Password=NULL);
	bool Connect();

	// ����Ƕ����ˣ�����3�Σ������ɹ�����true�����򷵻�false
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
	�����е����ݷŵ�ջ�л��棬�Ʋ����Ѳ�Ҫʹ��
	*/
	bool			FetchEx();
	bool			GetDataEx(tint32 ColIndex, tchar* Buffer, tint32 BufferLen);
	tint32			GetIntEx(tint32 ColIndex,tint32& ErrorCode);
	tuint32			GetUIntEx(tint32 ColIndex,tint32& ErrorCode);
	tint32			Get64Ex(tint32 ColIndex, tuint32& High, tuint32& Low, tint32& ErrorCode);
	tuint64			GetU64Ex(tint32 ColIndex, tint32& ErrorCode);
	tint64          GetLongLongEx(tint32 ColIndex,  tint32& ErrorCode);
	void			GetStringEx(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);
	void			GetFieldEx(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode); //��Ҫ�ں�������ת������Ϸ��Ҫ������
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

	//���Զ�������\0
	void			GetString(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);		
	void			GetField(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);
	void			GetLongField(tint32 nCol, tchar*buf,tint32 BufLen,tint32& ErrorCode);
	void			GetDoubleField(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode);
	// Ϊ�˲�Ӱ�������߼����������������varchar(255)����CHAR����Ľ���
	void			GetDoubleFieldS(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode);
	
	//����SqlState
	void			DiagState();
	void			DiagStateEx();

	void			CleanEnv();
	void			SetDBExceIndex(tint16 nIndex){m_nDBExecIndex = nIndex;}
};

#endif


