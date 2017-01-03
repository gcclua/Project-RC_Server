////////////////////////////////////////////////////////////////////////////////////////
//
//             ʱ�䣺15:22 2013-11-14
//             ˵����
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCInterface.h"
#include "Common/Config.h"
#include <sstream>

ODBCInterface::ODBCInterface()
{
	__ENTER_FUNCTION
	
	mConnected		= false;
	mAffectCount	=-1;
	mResult			=	SQL_SUCCESS;
	hEnv			=	0;
	hStmt			=	0;
	hDbc			=	0;
	memset(mErrorMsg,0,MAX_ERROR_MSG_LENGHT);
	m_Query.Clear();
	memset(m_ResultCache, 0, sizeof(m_ResultCache));
	m_FetchAlgoType = ODBCInterface::INVALID_TYPE;
	m_nDBExecIndex = invalid_id;

	__LEAVE_FUNCTION	  	
}

ODBCInterface::~ODBCInterface()
{
	__ENTER_FUNCTION	

	if (hStmt)	SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
	//if (hDbc)	SQLEndTran(SQL_HANDLE_DBC,hDbc,SQL_COMMIT);
	if (hDbc)	SQLDisconnect(hDbc);
	if (hDbc)	SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
	if (hEnv)	SQLFreeHandle(SQL_HANDLE_ENV,hEnv);

	__LEAVE_FUNCTION
}

bool ODBCInterface::Connect(const tchar *ConnectStr, 
							const tchar *UserName/* =NULL */,
							const tchar *Password/* =NULL */)
{
	__ENTER_FUNCTION

	Close();

	strncpy(mConnectStr, ConnectStr,DATABASE_STR_LEN);
	strncpy(mUserName, UserName,DB_USE_STR_LEN);
	strncpy(mPassWord, Password,DB_PASSWORD_STR_LEN);

	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv);
	SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc);
	mResult=SQLConnect(hDbc,(SQLCHAR *)mConnectStr,SQL_NTS,(SQLCHAR *)mUserName,SQL_NTS,
		(SQLCHAR *)mPassWord,SQL_NTS);
	
	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO)) 
	{
		tchar LogBuff[512];
		memset(LogBuff,0,512);
		tsnprintf(LogBuff,sizeof(LogBuff),"Connect string: %s",mConnectStr);
		tsnprintf(LogBuff,sizeof(LogBuff),"Connect string: %s",mUserName);
		DiagState();
		return false;
	}
	//SQLSetConnectAttr(hDbc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_OFF,0);	 
	SQLSetConnectAttr(hDbc,SQL_ATTR_TXN_ISOLATION,(SQLPOINTER)SQL_TXN_READ_COMMITTED,0); 

	mResult=	SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt);

	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO)) 
	{
		hStmt=0;
		return false;
	}

	mConnected = true;
	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCInterface::Connect()
{
	__ENTER_FUNCTION

	Close();
	SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv);
	SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc);

	mResult=SQLConnect(hDbc,(SQLCHAR *)mConnectStr,SQL_NTS,(SQLCHAR *)mUserName,SQL_NTS,
		(SQLCHAR *)mPassWord,SQL_NTS);
	
	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO)) 
	{
		tchar LogBuff[512];
		memset(LogBuff,0,512);
        tsnprintf(LogBuff,sizeof(LogBuff),"Connect string: %s",mConnectStr);
        tsnprintf(LogBuff,sizeof(LogBuff),"Connect string: %s",mUserName);
		DiagState();
		return false;
	}
	//SQLSetConnectAttr(hDbc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_OFF,0);	  
	SQLSetConnectAttr(hDbc,SQL_ATTR_TXN_ISOLATION,(SQLPOINTER)SQL_TXN_READ_COMMITTED,0); 

	mResult=	SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt);

	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO)) {
		hStmt=0;
		return false;
	}

	mConnected = true;
	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCInterface::Reconnect()
{
	__ENTER_FUNCTION

	for (int i = 0; i < MAX_RECONNECT_TIMES; i++)
	{
		if (Connect())
		{
			CacheLog(LOGDEF_INST(DBAgent), "reconnect success, ConnectStr %s, UserName %s, i %d", mConnectStr, mUserName, i);
			return true;
		}
		// ����Ƕ����ˣ�����3�Σ������ɹ�����true�����򷵻�false
		if (mErrorCode == CR_SERVER_LOST || mErrorCode == CR_CONN_HOST_ERROR || mErrorCode == CR_SERVER_GONE_ERROR)
		{
			_Sleep(300);
		}
	}

	return false;
	__LEAVE_FUNCTION
	return false;
}

bool ODBCInterface::Close()
{
	__ENTER_FUNCTION

	if (hStmt)	
	{
		try
		{
			SQLCloseCursor(hStmt);
			SQLFreeStmt(hStmt, SQL_UNBIND);
			SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
			hStmt = NULL;
		}
		catch(...)
		{
			hStmt = NULL;
		}
	}
	if (hDbc)
	{
		//SQLEndTran(SQL_HANDLE_DBC,hDbc,SQL_COMMIT);
		try
		{
			SQLDisconnect(hDbc);
			SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
			hDbc = NULL;
		}
		catch(...)
		{
			hDbc = NULL;
		}
	}
	if (hEnv)	
	{
		try
		{
			SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
			hEnv = NULL;
		}
		catch(...)
		{
			hEnv = NULL;
		}
	}
	mConnected = false;						//��������״̬

	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCInterface::Execute()
{
	try
	{
		//INT ColIndex;
		bool bIsRecc = false;
		while (true)
		{
			mResult=SQLExecDirect(hStmt,(SQLCHAR *)m_Query.m_SqlStr,SQL_NTS);
			if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
			{
				DiagState();
				if (bIsRecc)
				{
					// �Ѿ��������ˣ�������
					return false;
				}
				if (!Reconnect())
				{
					return false;
				}
				bIsRecc = true;
			}
			else
			{
				break;
			}
		}
			// Update, Delete, Insert Ӱ��Ľ��
		SQLRowCount(hStmt,&mAffectCount);
		SQLNumResultCols(hStmt,&mColCount);
		if (mColCount > MAXCOL) 
		{
				return false;
		}
			
		if (mColCount <= 0 && mAffectCount <= 0)
		{
				Clear();
				return true;
		}

		return true;
	}
	catch(...)
	{
		//��������Sql���
		tchar ErrorBuffer[DB_MAX_ERROR_BUFF] = {0};
		tsnprintf(ErrorBuffer,sizeof(ErrorBuffer),"Huge Error occur:");
		SaveErrorSQL(ErrorBuffer,(const tchar*)m_Query.m_SqlStr);
	}
	return false;
}

bool ODBCInterface::LongExecute()
{
	try
	{
		//INT ColIndex;
		bool bIsRecc = false;
		while (true)
		{
			mResult=SQLExecDirect(hStmt,(SQLCHAR *)m_LongQuery.m_SqlStr,SQL_NTS);
			if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
			{
				DiagStateEx();
				if (bIsRecc)
				{
					// �Ѿ��������ˣ�������
					return false;
				}
				if (!Reconnect())
				{
					return false;
				}
				bIsRecc = true;
			}
			else
			{
				break;
			}
		}
		
		// Update, Delete, Insert Ӱ��Ľ��
		SQLRowCount(hStmt,&mAffectCount);
		SQLNumResultCols(hStmt,&mColCount);
		if (mColCount > MAXCOL) 
		{
			return false;
		}

		if (mColCount <= 0 && mAffectCount <= 0)
		{
			Clear();
			return true;
		}

		//for (ColIndex=0;ColIndex<mColCount;ColIndex++) 
		//{
			//SQLBindCol(hStmt,ColIndex+1,SQL_C_CHAR,Col[ColIndex],MAX_COLUMN_BUFFER,&mCollocate[ColIndex]);
			//SQLDescribeCol(hStmt,ColIndex+1,ColName[ColIndex],MAX_COLUMN_NAME,NULL,NULL,NULL,NULL,NULL);
		//}
		return true;

	}
	catch(...)
	{
		//��������Sql���
		tchar ErrorBuffer[DB_MAX_ERROR_BUFF] = {0};
		tsnprintf(ErrorBuffer,sizeof(ErrorBuffer),"Huge Error occur:");
		SaveErrorSQL(ErrorBuffer,(const tchar*)m_LongQuery.m_SqlStr);
	}
	return false;
}

bool ODBCInterface::LongExecuteEx() {
	try
	{
		//INT ColIndex;
		bool bIsRecc = false;
		while (true)
		{
			mResult=SQLExecDirect(hStmt,(SQLCHAR *)m_LongQuery.m_SqlStr,SQL_NTS);
			if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
			{
				DiagStateEx();
				if (bIsRecc)
				{
					// �Ѿ��������ˣ�������				
					return false;
				}
				if (!Reconnect())
				{
					return false;
				}
				bIsRecc = true;
			}
			else
			{
				break;
			}
		}
		
		// Update, Delete, Insert Ӱ��Ľ��
		SQLRowCount(hStmt,&mAffectCount);
		SQLNumResultCols(hStmt,&mColCount);

		if (mColCount <= 0 && mAffectCount <= 0)
		{
			Clear();
			return true;
		}
		return true;
	}
	catch(...)
	{
		//��������Sql���
		tchar ErrorBuffer[DB_MAX_ERROR_BUFF] = {0};
		tsnprintf(ErrorBuffer,sizeof(ErrorBuffer),"Huge Error occur:");
		SaveErrorSQL(ErrorBuffer,(const tchar*)m_LongQuery.m_SqlStr);
	}
	return false;
}


void ODBCInterface::Clear_NoCommit()
{
__ENTER_FUNCTION
	SQLCloseCursor(hStmt);
	SQLFreeStmt(hStmt, SQL_UNBIND);
__LEAVE_FUNCTION
}

void ODBCInterface::Clear()
{
__ENTER_FUNCTION
	SQLCloseCursor(hStmt);
	SQLFreeStmt(hStmt, SQL_UNBIND);
	//SQLEndTran(SQL_HANDLE_DBC,hDbc,SQL_COMMIT);
__LEAVE_FUNCTION
}

bool	ODBCInterface::FetchEx()
{
__ENTER_FUNCTION
	m_FetchAlgoType = SINGLE_CACHE;
	mResult	=	SQLFetch(hStmt);

	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
	{
		DiagState();
		return false;
	}

	if(mResult == SQL_NO_DATA)
	{
		return false;
	}

	return true;
__LEAVE_FUNCTION
	return false;
}

bool	ODBCInterface::GetDataEx(tint32 ColIndex, tchar* Buffer, tint32 BufferLen)
{
__ENTER_FUNCTION
	AssertEx(SINGLE_CACHE==m_FetchAlgoType,"");
	SQLLEN LenData = 0;
	
	SQLGetData(hStmt, ColIndex, SQL_C_CHAR, Buffer, BufferLen, &LenData); 	

	if(BufferLen < LenData)
	{
		AssertEx(false,"");
	}
	
	return true;
__LEAVE_FUNCTION
	return false;
}


bool	ODBCInterface::Fetch()
{
	__ENTER_FUNCTION
	m_FetchAlgoType = MULTY_CACHE;
	mResult	=	SQLFetch(hStmt);

	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
	{
		DiagState();
		return false;
	}

	if(mResult == SQL_NO_DATA)
	{
		return false;
	}

	for (tint32 ColIndex=0;ColIndex<mColCount;ColIndex++)
	{
		tint32			TotalGet = 0;		
		SQLLEN			LenData = 0;
		/*int				Ret		= 0;*/
		SQLGetData(hStmt, ColIndex+1, SQL_C_CHAR,Col[ColIndex]+TotalGet,MAX_COLUMN_BUFFER,&LenData);
	
		if(LenData == -1)
		{
			memset(Col[ColIndex]+TotalGet, 0, MAX_COLUMN_BUFFER);
		}
		//printf("sql length=%d ret=%d,LenData=%d\r\n",TotalGet,Ret,LenData);
	}

	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCInterface::LongFetch()
{
__ENTER_FUNCTION
	m_FetchAlgoType = LONG_CACHE;
	mResult	=	SQLFetch(hStmt);

	if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
	{
		DiagState();
		return false;
	}

	if(mResult == SQL_NO_DATA)
	{
		return false;
	}

	for (tint32 ColIndex=0;ColIndex<mColCount;ColIndex++)
	{
		tint32				TotalGet = 0;
		SQLLEN				LenData  = 0;
		//tint32				Ret		 = 0;
		/* ��ע�⣬������һ��Ǳ���򣡣���[3/2/2007]
			* Col[ColIndex]�Ĵ�С��MAX_COLUMN_BUFFER 2049
			* �������ȡ�Ĵ�С��MAX_LONG_COLUMN_BUFFER	200000
			* ���Ե�ʹ��LongFetch��ȡ����2049���еķ���ֵʱ��һ��Ҫ��֤���������һ��
			* ����ע�⣡��������ע�⣡��������ע�⣡��������ע�⣡����
			*/
		SQLGetData(hStmt, ColIndex+1, SQL_C_CHAR,Col[ColIndex]+TotalGet,MAX_LONG_COLUMN_BUFFER,&LenData);
	
		//printf("sql length=%d ret=%d,LenData=%d\r\n",TotalGet,Ret,LenData);
	}
	
	return true;

__LEAVE_FUNCTION

	return false;
}


tint32 ODBCInterface::GetInt(tint32 ColIndex,tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	ErrorCode = QUERYOK;
	return atoi(Col[ColIndex-1]);
	
 __LEAVE_FUNCTION

	 return QUERYNULL;
}

tint32 ODBCInterface::GetIntEx(tint32 ColIndex,tint32& ErrorCode)
{
__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	memset(m_ResultCache, 0, sizeof(m_ResultCache));
	GetDataEx(ColIndex, m_ResultCache, sizeof(m_ResultCache));
	ErrorCode = QUERYOK;
	return (tint32)atoi(m_ResultCache);

__LEAVE_FUNCTION

	return QUERYNULL;
}

tuint32 ODBCInterface::GetUInt(tint32 ColIndex,tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	ErrorCode =	QUERYOK;
	return (tuint32)atoi(Col[ColIndex-1]);
	
	__LEAVE_FUNCTION

		return QUERYNULL;
}

tuint32 ODBCInterface::GetUIntEx(tint32 ColIndex,tint32& ErrorCode)
{
__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	memset(m_ResultCache, 0, sizeof(m_ResultCache));
	GetDataEx(ColIndex, m_ResultCache, sizeof(m_ResultCache));
	ErrorCode =	QUERYOK;
	return (tuint32)atoi(m_ResultCache);

__LEAVE_FUNCTION

	return QUERYNULL;
}

tint32 ODBCInterface::Get64Ex(tint32 ColIndex, tuint32& High, tuint32& Low, tint32& ErrorCode)
{
	__ENTER_FUNCTION

		if (ColIndex > mColCount)
		{
			ErrorCode = QUERYNOCOL;
			AssertEx(false,"");
			return QUERYNOCOL;
		}

		memset(m_ResultCache, 0, sizeof(m_ResultCache));
		GetDataEx(ColIndex, m_ResultCache, sizeof(m_ResultCache));
		ErrorCode =	QUERYOK;
		tint64 Data = tatoll(m_ResultCache);
		Low = (tint32)Data;
		Data = Data >> 32;
		High = (tint32)Data;
		return QUERYOK;

	__LEAVE_FUNCTION

		return QUERYNULL;
}

tuint64	ODBCInterface::GetU64Ex(tint32 ColIndex, tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	memset(m_ResultCache, 0, sizeof(m_ResultCache));
	GetDataEx(ColIndex, m_ResultCache, sizeof(m_ResultCache));
	ErrorCode =	QUERYOK;

	std::stringstream str_stream;
	str_stream << m_ResultCache;
	tuint64 retval = 0;
	str_stream >> retval;

	return retval;

	__LEAVE_FUNCTION
	return QUERYNULL;
}

tint64 ODBCInterface::GetLongLongEx(tint32 ColIndex, tint32& ErrorCode)
{
	__ENTER_FUNCTION

		if (ColIndex > mColCount)
		{
			ErrorCode = QUERYNOCOL;
			AssertEx(false,"");
			return QUERYNOCOL;
		}

		memset(m_ResultCache, 0, sizeof(m_ResultCache));
		GetDataEx(ColIndex, m_ResultCache, sizeof(m_ResultCache));
		ErrorCode =	QUERYOK;
		return tatoll(m_ResultCache);

	__LEAVE_FUNCTION
		return QUERYNULL;
}

tint64 ODBCInterface::GetInt64(tint32 ColIndex, tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}
	
	std::stringstream str_stream;
	str_stream << Col[ColIndex-1];
	tint64 retval = 0;
	str_stream >> retval;

	return retval;

	__LEAVE_FUNCTION
	return QUERYNULL;
}

tuint64 ODBCInterface::GetUInt64(tint32 ColIndex,tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	std::stringstream str_stream;
	str_stream << Col[ColIndex-1];
	tuint64 retval = 0;
	str_stream >> retval;

	return retval;

	__LEAVE_FUNCTION
	return QUERYNULL;
}

tint32 ODBCInterface::Get64(tint32 ColIndex, tuint32& High, tuint32& Low, tint32& ErrorCode)
{
	__ENTER_FUNCTION

		if (ColIndex > mColCount)
		{
			ErrorCode = QUERYNOCOL;
			AssertEx(false,"");
			return QUERYNOCOL;
		}

		ErrorCode =	QUERYOK;
		tint64 Data = tatoll(Col[ColIndex-1]);
		Low = (tint32)Data;
		Data = Data >> 32;
		High = (tint32)Data;
		return QUERYOK;

	__LEAVE_FUNCTION
		return QUERYNULL;
}

tint64 ODBCInterface::GetLongLong(tint32 ColIndex, tint32& ErrorCode)
{
__ENTER_FUNCTION
	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	ErrorCode =	QUERYOK;
	return tatoll(Col[ColIndex-1]);
__LEAVE_FUNCTION
	return QUERYNULL;
}

tfloat32 ODBCInterface::GetFloat(tint32 ColIndex,tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode =  QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	
	ErrorCode = QUERYOK;
	return (tfloat32)atof(Col[ColIndex-1]);

	__LEAVE_FUNCTION

		return QUERYNULL;
}

void ODBCInterface::GetStringEx(tint32 ColIndex, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	GetDataEx(ColIndex, buf, BufLen);
	buf[BufLen-1] = '\0';	
	ErrorCode = QUERYOK;

__LEAVE_FUNCTION
}


void ODBCInterface::GetString(tint32 ColIndex, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
	__ENTER_FUNCTION

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if(BufLen<MAX_COLUMN_BUFFER)
	{
		strncpy(buf,Col[ColIndex-1],BufLen-1);
	}
	else
	{
		strncpy(buf,Col[ColIndex-1],MAX_COLUMN_BUFFER-1);
	}
	ErrorCode = QUERYOK;

	__LEAVE_FUNCTION
}

void ODBCInterface::GetFieldEx(tint32 ColIndex, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
__ENTER_FUNCTION	

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	memset(m_LongResultCache, 0, sizeof(m_LongResultCache));
	GetDataEx(ColIndex, m_LongResultCache, sizeof(m_LongResultCache));

	if (BufLen < MAX_COLUMN_BUFFER)
	{
		tuint32 OutLength = 0;
		DBStr2Binary(m_LongResultCache,MAX_COLUMN_BUFFER,buf,BufLen,OutLength);
		AssertEx((tint32)OutLength<=BufLen,"");
		ErrorCode = QUERYOK;
	}
	else 
	{
		ErrorCode = QUERYERROR;
		AssertEx(false,"");
	}

__LEAVE_FUNCTION
}

void ODBCInterface::GetField(tint32 ColIndex, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
	__ENTER_FUNCTION	

	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if (BufLen < MAX_COLUMN_BUFFER)
	{
		tuint32 OutLength = 0;
		DBStr2Binary(Col[ColIndex-1],MAX_COLUMN_BUFFER,buf,BufLen,OutLength);
		AssertEx((tint32)OutLength<=BufLen,"");
	}
	else
	{
		memcpy(buf,Col[ColIndex-1],MAX_COLUMN_BUFFER);
		AssertEx(false,"");
	}
	ErrorCode = QUERYOK;

	__LEAVE_FUNCTION
}

void ODBCInterface::GetLongField(tint32 ColIndex, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
	__ENTER_FUNCTION	

		if (ColIndex > mColCount)
		{
			ErrorCode = QUERYNOCOL;
			buf[0] = '\0';
			AssertEx(false,"");
			return;
		}

		if (BufLen < MAX_LONG_COLUMN_BUFFER)
		{
			tuint32 OutLength = 0;
			DBStr2Binary(Col[ColIndex-1],MAX_LONG_COLUMN_BUFFER,buf,BufLen,OutLength);
			AssertEx((tint32)OutLength<=BufLen,"");
		}
		else
		{
			memcpy(buf,Col[ColIndex-1],MAX_LONG_COLUMN_BUFFER);
			AssertEx(false,"");
		}
		ErrorCode = QUERYOK;

		__LEAVE_FUNCTION
}

void ODBCInterface::GetDoubleField(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
__ENTER_FUNCTION	

	if (ColIndex > mColCount || Col2Index > mColCount )
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if (BufLen < MAX_COLUMN_BUFFER)
	{
		tuint32 OutLength = 0;
		DBStr2Binary(Col[ColIndex-1],MAX_COLUMN_BUFFER,buf,BufLen,OutLength);
		AssertEx((tint32)OutLength<=BufLen,"");

		tuint32 OutLength2 = 0;
		DBStr2Binary(Col[Col2Index-1],MAX_COLUMN_BUFFER,buf+OutLength,BufLen-OutLength, OutLength2);
		AssertEx((tint32)(OutLength+OutLength2)<=BufLen,"");
	}
	else
	{
		memcpy(buf,Col[ColIndex-1],MAX_COLUMN_BUFFER);
		AssertEx(false,"");
	}
	ErrorCode = QUERYOK;

__LEAVE_FUNCTION
}

void ODBCInterface::GetDoubleFieldS(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
__ENTER_FUNCTION	

	if (ColIndex > mColCount || Col2Index > mColCount )
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if (BufLen < MAX_COLUMN_BUFFER)
	{
		// �Ƚ���ǰ254�ֽ�
		tuint32 OutLength = 0;
		DBStr2Binary(Col[ColIndex-1],MAX_COLUMN_BUFFER,buf,126,OutLength);
		AssertEx((tint32)OutLength<=BufLen,"");

		tuint32 OutLength2 = 0;
		DBStr2Binary(Col[Col2Index-1],MAX_COLUMN_BUFFER,buf+OutLength,BufLen-126, OutLength2);
		AssertEx((tint32)(OutLength+OutLength2)<=BufLen,"");
	}
	else
	{
		memcpy(buf,Col[ColIndex-1],MAX_COLUMN_BUFFER);
		AssertEx(false,"");
	}
	ErrorCode = QUERYOK;

__LEAVE_FUNCTION
}

void ODBCInterface::GetDoubleFieldEx(tint32 ColIndex, tint32 Col2Index, tchar * buf,tint32 BufLen,tint32& ErrorCode)
{
	__ENTER_FUNCTION
	if (ColIndex > mColCount || Col2Index > mColCount )
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if (BufLen < MAX_COLUMN_BUFFER)
	{
		memset(m_LongResultCache, 0, sizeof(m_LongResultCache));
		GetDataEx(ColIndex, m_LongResultCache, sizeof(m_LongResultCache));

		tuint32 OutLength = 0;
		DBStr2Binary(m_LongResultCache,MAX_COLUMN_BUFFER,buf,BufLen,OutLength);
		AssertEx((tint32)OutLength<=BufLen,"");

		memset(m_LongResultCache, 0, sizeof(m_LongResultCache));
		GetDataEx(Col2Index, m_LongResultCache, sizeof(m_LongResultCache));
		tuint32 OutLength2 = 0;
		DBStr2Binary(m_LongResultCache,MAX_COLUMN_BUFFER,buf,BufLen+OutLength, OutLength2);
		AssertEx((tint32)(OutLength+OutLength2)<=BufLen,"");
	}
	else
	{
		memcpy(buf, Col[ColIndex-1], MAX_COLUMN_BUFFER);
		AssertEx(false,"");
	}
	ErrorCode = QUERYOK;

	__LEAVE_FUNCTION
}

void	ODBCInterface::DiagState()
{
	__ENTER_FUNCTION
	tint32			ii=1;
	SQLINTEGER		NativeError;
	SQLCHAR			SqlState[6];
	SQLSMALLINT		MsgLen;
	memset(mErrorMsg,0,MAX_ERROR_MSG_LENGHT);	
	while (/*mResult=*/SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, ii, SqlState, &NativeError, 
		mErrorMsg, sizeof(mErrorMsg), &MsgLen) !=SQL_NO_DATA) 
	{
		ii++;
		
	}
	
	mErrorMsg[MAX_ERROR_MSG_LENGHT-1] = '\0'; //��ֹ������Ϣ���
	
	if(strlen((const tchar*)mErrorMsg) == 0)
	{//�Զ������ݿ����
			
					mResult	=	SQLError(hEnv,hDbc,hStmt,SqlState,
						&NativeError,mErrorMsg,sizeof(mErrorMsg),&MsgLen);
	}
	mErrorCode =  NativeError;

	switch(mErrorCode) 
	{
	case 2601: //��ɫ��������Ҫ�ر�����
		break;
	case 1062: //��ɫ�ظ�
		break;
	case 1213:
		//if (!_GameConfig().m_CloseInterfaceOnDeadLock)
		{
			break;//����������Ҫ��ر����ӣ�
		}
	default:
		{
			Close();
		}
		break;
	}

	tchar szTime[MAXPATH];
	memset(szTime, 0, MAXPATH);

	tsnprintf( szTime, MAXPATH, 
		"(T0=%d-%d-%d_%d:%d:%d T1=%.4f)", 
		gTimeManager.GetYear(),
		gTimeManager.GetMonth()+1,
		gTimeManager.GetDay(),
		gTimeManager.GetHour(),
		gTimeManager.GetMinute(),
		gTimeManager.GetSecond(),
		(tfloat32)(gTimeManager.RunTime())/1000.0 );
	
	if ( 1213 == mErrorCode )
	{
		// ���ڹ������ʹ����߼���ԭ�򣬳��ֵ�����������ʱ���ӵ�������־�У��������ִ���̫��������������־
		CacheLog(LOGDEF_INST(DBAgentError),"Time = %s, ErrorCode = %d,ErrorMessage = %s,ErrorSql=%s",szTime, mErrorCode,mErrorMsg, (const tchar*)m_Query.m_SqlStr);
	}
	else
	{
		tchar ErrorBuffer[DB_MAX_ERROR_BUFF] = {0};
		tsnprintf(ErrorBuffer,sizeof(ErrorBuffer),"ErrorCode = %d,Result = %d,ErrorMessage = %s", mErrorCode,mResult,mErrorMsg);
		//��������Sql���
		SaveErrorSQL(ErrorBuffer,(const tchar*)m_Query.m_SqlStr);
	}
	__LEAVE_FUNCTION
}

void	ODBCInterface::DiagStateEx()
{
	__ENTER_FUNCTION
	tint32			ii=1;
	SQLINTEGER		NativeError;
	SQLCHAR			SqlState[6];
	SQLSMALLINT		MsgLen;
	memset(mErrorMsg,0,MAX_ERROR_MSG_LENGHT);	
	while (/*mResult=*/SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, ii, SqlState, &NativeError, 
		mErrorMsg, sizeof(mErrorMsg), &MsgLen) !=SQL_NO_DATA) 
	{
		ii++;

	}

	mErrorMsg[MAX_ERROR_MSG_LENGHT-1] = '\0'; //��ֹ������Ϣ���

	if(strlen((const tchar*)mErrorMsg) == 0)
	{//�Զ������ݿ����

		mResult	=	SQLError(hEnv,hDbc,hStmt,SqlState,
			&NativeError,mErrorMsg,sizeof(mErrorMsg),&MsgLen);
	}
	mErrorCode =  NativeError;

	switch(mErrorCode) 
	{
	case 2601: //��ɫ����
		break;
	case 1062: //��ɫ����
		break;
	case 1213:
		//if (!_GameConfig().m_CloseInterfaceOnDeadLock)
		{
			break;//����������Ҫ��ر����ӣ�
		}
	default:
		{
			Close();
		}
		break;
	}

	tchar szTime[MAXPATH];
	memset(szTime, 0, MAXPATH);

	tsnprintf( szTime, MAXPATH, 
		"(T0=%d-%d-%d_%d:%d:%d T1=%.4f)", 
		gTimeManager.GetYear(),
		gTimeManager.GetMonth()+1,
		gTimeManager.GetDay(),
		gTimeManager.GetHour(),
		gTimeManager.GetMinute(),
		gTimeManager.GetSecond(),
		(tfloat32)(gTimeManager.RunTime())/1000.0 );

	if ( 1213 == mErrorCode )
	{
		// ���ڹ������ʹ����߼���ԭ�򣬳��ֵ�����������ʱ���ӵ�������־�У��������ִ���̫��������������־
		CacheLog(LOGDEF_INST(DBAgentError),"Time = %s, ErrorCode = %d,ErrorMessage = %s,ErrorSql=%s",szTime, mErrorCode,mErrorMsg, (const tchar*)m_LongQuery.m_SqlStr);
	}
	else
	{
		tchar ErrorBuffer[DB_MAX_ERROR_BUFF] = {0};
		tsnprintf(ErrorBuffer,sizeof(ErrorBuffer),"ErrorCode = %d,Result = %d,ErrorMessage = %s",mErrorCode,mResult,mErrorMsg);
		//��������Sql���
		SaveErrorSQL(ErrorBuffer,(const tchar*)m_LongQuery.m_SqlStr);
	}
	__LEAVE_FUNCTION
}

void ODBCInterface::CleanEnv()
{
	__ENTER_FUNCTION
	if (hStmt)	
	{
		SQLCloseCursor(hStmt);
		SQLFreeStmt(hStmt, SQL_UNBIND);
		SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
		hStmt = NULL;
	}
	if (hDbc)
	{
		//SQLEndTran(SQL_HANDLE_DBC,hDbc,SQL_COMMIT);
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
		hDbc = NULL;
	}
	if (hEnv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
		hEnv = NULL;
	}
	__LEAVE_FUNCTION
}

void ODBCInterface::SaveErrorSQL(const tchar* pLog,const tchar* pSQL)
{
	__ENTER_FUNCTION
	if (invalid_id == m_nDBExecIndex)
	{
		return;
	}
	if (strlen(pLog) <= 0 || strlen(pSQL)<=0)
	{
		return;
	}

	tm ltm;
	_localtime(_ansitime(), ltm);

	tchar szTemp[MAX_LONG_SQL_LENGTH+DB_MAX_ERROR_BUFF] = {0};
	tsnprintf(szTemp, sizeof(szTemp), "(%.4d-%.2d-%.2d_%.2d:%.2d:%.2d)%s:%s\n",
		ltm.tm_year+1900, ltm.tm_mon+1, ltm.tm_mday, ltm.tm_hour, ltm.tm_min, ltm.tm_sec,
		pLog,
		pSQL);
	szTemp[sizeof(szTemp) - 1] = '\0';

	tchar szFileName[256] = {0};
	tsnprintf(szFileName, sizeof(szFileName), "./../RuntimeData/Log/DBSQLError%.2d.%.4d-%.2d-%.2d-%.2d.log",
		 m_nDBExecIndex,ltm.tm_year+1900, ltm.tm_mon+1, ltm.tm_mday, ltm.tm_hour);
	szFileName[sizeof(szFileName) - 1] = '\0';

	try
	{
		FILE *f = fopen(szFileName, "a+");
		if(f)
		{
			fwrite(szTemp, 1, strlen(szTemp), f);
			fclose(f);
		}
	}
	catch(...)
	{}

	__LEAVE_FUNCTION
}
