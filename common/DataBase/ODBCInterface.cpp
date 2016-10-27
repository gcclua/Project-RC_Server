
#include "ODBCInterface.h"

ODBCInterface::ODBCInterface()
{
	
	mConnected		= false;
	mAffectCount	=-1;
	mResult			=	SQL_SUCCESS;
	hEnv			=	0;
	hStmt			=	0;
	hDbc			=	0;
	memset(mErrorMsg,0,MAX_ERROR_MSG_LENGHT);
	m_Query.Clear();

	
}

ODBCInterface::~ODBCInterface()
{

	if (hStmt)	SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
	if (hDbc)	SQLDisconnect(hDbc);
	if (hDbc)	SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
	if (hEnv)	SQLFreeHandle(SQL_HANDLE_ENV,hEnv);

}

bool ODBCInterface::Connect(const char *ConnectStr, 
							const char *UserName/* =NULL */,
							const char *Password/* =NULL */)
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
		char LogBuff[512];
		memset(LogBuff,0,512);
		sprintf(LogBuff,"Connect string: %s",mConnectStr);
		sprintf(LogBuff,"Connect string: %s",mUserName);
		DiagState();
		return false;
	}
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
		char LogBuff[512];
		memset(LogBuff,0,512);
		sprintf(LogBuff,"Connect string: %s",mConnectStr);
		sprintf(LogBuff,"Connect string: %s",mUserName);
		DiagState();
		return false;
	}


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

bool ODBCInterface::Close()
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
		SQLFreeHandle(SQL_HANDLE_DESC,hDbc);
		SQLDisconnect(hDbc);
		hDbc = NULL;
	}
	if (hEnv)	
	{
		SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
		hEnv = NULL;
	}
	mConnected = false;						//设置连接状态

	return true;
	__LEAVE_FUNCTION
		return false;

}

bool ODBCInterface::Execute()
{
	__ENTER_FUNCTION
	try
	{
		int ColIndex;
 		mResult=SQLExecDirect(hStmt,(SQLCHAR *)m_Query.m_SqlStr,SQL_NTS);
		if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
		{
			DiagState();
		
			return false;
		}
			// Update, Delete, Insert 影响的结果
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

		for (ColIndex=0;ColIndex<mColCount;ColIndex++) 
		{
			SQLBindCol(hStmt,ColIndex+1,SQL_C_CHAR,Col[ColIndex],MAX_COLUMN_BUFFER,&mCollocate[ColIndex]);
			SQLDescribeCol(hStmt,ColIndex+1,ColName[ColIndex],MAX_COLUMN_NAME,NULL,NULL,NULL,NULL,NULL);
		}
		return true;

	}
	catch(...)
	{
			SaveLog((const char*)m_Query.m_SqlStr);//保存错误的Sql语句
	}
	return false;
	__LEAVE_FUNCTION
		return false;
}

bool ODBCInterface::LongExecute()
{
	__ENTER_FUNCTION
	try
	{
		int ColIndex;
		mResult=SQLExecDirect(hStmt,(SQLCHAR *)m_LongQuery.m_SqlStr,SQL_NTS);
		if ((mResult != SQL_SUCCESS) && (mResult != SQL_SUCCESS_WITH_INFO) && (mResult != SQL_NO_DATA)) 
		{
			DiagStateEx();
			return false;
		}
		// Update, Delete, Insert 影响的结果
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

		for (ColIndex=0;ColIndex<mColCount;ColIndex++) 
		{
			//SQLBindCol(hStmt,ColIndex+1,SQL_C_CHAR,Col[ColIndex],MAX_COLUMN_BUFFER,&mCollocate[ColIndex]);
			//SQLDescribeCol(hStmt,ColIndex+1,ColName[ColIndex],MAX_COLUMN_NAME,NULL,NULL,NULL,NULL,NULL);
		}
		return true;

	}
	catch(...)
	{
		SaveErrorLog("Huge Error occur:");
		SaveErrorLog((const char*)m_LongQuery.m_SqlStr);//保存错误的Sql语句
	}
	return false;
	__LEAVE_FUNCTION
		return false;
}

void ODBCInterface::SaveErrorLog(const char* pLog)
{
		if(strlen(pLog)==0)
			return;
	FILE* f = fopen( "./Log/dberror.log", "a" ) ;
	if(f)
	{
		fwrite( pLog, 1, strlen(pLog), f ) ;
		fwrite( "\r\n", 1, 2, f ) ;
		fclose(f) ;
	}
}

void ODBCInterface::Clear()
{

	SQLCloseCursor(hStmt);
	SQLFreeStmt(hStmt, SQL_UNBIND);


}


bool	ODBCInterface::Fetch()
{
	__ENTER_FUNCTION
	memset(Col, 0, MAXCOL*MAX_COLUMN_BUFFER);

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

bool ODBCInterface::LongFetch()
{
	__ENTER_FUNCTION
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

	for (int ColIndex=0;ColIndex<mColCount;ColIndex++)
	{
		int				TotalGet = 0;
		SQLINTEGER		LenData  = 0;
		int				Ret		 = 0;
		while(Ret=SQLGetData(hStmt, ColIndex+1, SQL_C_CHAR,Col[ColIndex]+TotalGet,MAX_LONG_COLUMN_BUFFER,&LenData)!=SQL_NO_DATA)
		{
			break;
		}
		//printf("sql length=%d ret=%d,LenData=%d\r\n",TotalGet,Ret,LenData);
	}

	return true;
	__LEAVE_FUNCTION
		return false;
}


int ODBCInterface::GetInt(int ColIndex,int& ErrorCode)
{
	__ENTER_FUNCTION
	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	if (mCollocate[ColIndex-1]==SQL_NULL_DATA)
	{
		ErrorCode = QUERYNULL;
		AssertEx(false,"");
		return QUERYNULL;
	} 
	else 
	{
		ErrorCode = QUERYOK;
		return atoi(Col[ColIndex-1]);
	}
	__LEAVE_FUNCTION
		return QUERYNULL;
}

tuint32 ODBCInterface::GetUInt(int ColIndex,int& ErrorCode)
{
	__ENTER_FUNCTION
	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	if (mCollocate[ColIndex-1]==SQL_NULL_DATA)
	{
		ErrorCode = QUERYNULL;
		AssertEx(false,"");
		return QUERYNULL;
	} 
	else 
	{
		ErrorCode =	QUERYOK;
        return (tuint32)atoi(Col[ColIndex-1]);
	}
	__LEAVE_FUNCTION
		return QUERYNULL;
}

FLOAT ODBCInterface::GetFloat(int ColIndex,int& ErrorCode)
{
	__ENTER_FUNCTION
	if (ColIndex > mColCount)
	{
		ErrorCode =  QUERYNOCOL;
		AssertEx(false,"");
		return QUERYNOCOL;
	}

	if (mCollocate[ColIndex-1]==SQL_NULL_DATA) 
	{
		ErrorCode = QUERYNULL;
		AssertEx(false,"");
		return QUERYNULL;
		
	}
	else 
	{
		ErrorCode = QUERYOK;
		return (FLOAT)atof(Col[ColIndex-1]);
	}
	__LEAVE_FUNCTION
		return QUERYNULL;
}


void ODBCInterface::GetString(int ColIndex, char * buf,int BufLen,int& ErrorCode)
{
	__ENTER_FUNCTION
	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if (mCollocate[ColIndex-1]==SQL_NULL_DATA) 
	{
		ErrorCode = QUERYNULL;
		buf[0] = '\0';
		AssertEx(false,"");
	} 
	else 
	{
		if(BufLen<MAX_COLUMN_BUFFER)
			strncpy(buf,Col[ColIndex-1],BufLen);
		else
		{
			strncpy(buf,Col[ColIndex-1],MAX_COLUMN_BUFFER);
		}
		ErrorCode = QUERYOK;
	}
	__LEAVE_FUNCTION
}

void ODBCInterface::GetField(int ColIndex, char * buf,int BufLen,int& ErrorCode)
{
		
	__ENTER_FUNCTION
	if (ColIndex > mColCount)
	{
		ErrorCode = QUERYNOCOL;
		buf[0] = '\0';
		AssertEx(false,"");
		return;
	}

	if (mCollocate[ColIndex-1]==SQL_NULL_DATA) 
	{
		ErrorCode = QUERYNULL;
		buf[0] = '\0';
		AssertEx(false,"");
	} 
	else 
	{
		if(BufLen<MAX_COLUMN_BUFFER)
		{
			tuint32 OutLength = 0;
			DBStr2Binary(Col[ColIndex-1],MAX_COLUMN_BUFFER,buf,BufLen,OutLength);
			AssertEx((int)OutLength<=BufLen,"");
		}
		else
		{
			memcpy(buf,Col[ColIndex-1],MAX_COLUMN_BUFFER);
			AssertEx(false,"");
		}
		ErrorCode = QUERYOK;
	}

	__LEAVE_FUNCTION
}

void ODBCInterface::GetLongField(int ColIndex, char * buf,int BufLen,int& ErrorCode)
{
		
	__ENTER_FUNCTION
		if (ColIndex > mColCount)
		{
			ErrorCode = QUERYNOCOL;
			buf[0] = '\0';
			AssertEx(false,"");
			return;
		}

		if (mCollocate[ColIndex-1]==SQL_NULL_DATA) 
		{
			ErrorCode = QUERYNULL;
			buf[0] = '\0';
			AssertEx(false,"");
		} 
		else 
		{
			if(BufLen<MAX_LONG_COLUMN_BUFFER)
			{
				tuint32 OutLength = 0;
				DBStr2Binary(Col[ColIndex-1],MAX_LONG_COLUMN_BUFFER,buf,BufLen,OutLength);
				AssertEx((int)OutLength<=BufLen,"");
			}
			else
			{
				memcpy(buf,Col[ColIndex-1],MAX_LONG_COLUMN_BUFFER);
				AssertEx(false,"");
			}
			ErrorCode = QUERYOK;
		}

		__LEAVE_FUNCTION
}




void	ODBCInterface::DiagState()
{
	
	__ENTER_FUNCTION
	int				ii=1;
	SQLINTEGER		NativeError;
	SQLCHAR			SqlState[6];
	SQLSMALLINT		MsgLen;
	memset(mErrorMsg,0,MAX_ERROR_MSG_LENGHT);	
	while (mResult=SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, ii, SqlState, &NativeError, 
		mErrorMsg, sizeof(mErrorMsg), &MsgLen) !=SQL_NO_DATA) 
	{
		ii++;
		
	}
	
	mErrorMsg[MAX_ERROR_MSG_LENGHT-1] = '\0'; //防止错误消息溢出
	
	if(strlen((const char*)mErrorMsg) == 0)
	{//自定义数据库错误
			
					mResult	=	SQLError(hEnv,hDbc,hStmt,SqlState,
						&NativeError,mErrorMsg,sizeof(mErrorMsg),&MsgLen);
	}
	mErrorCode =  NativeError;

	switch(mErrorCode) 
	{
	case 2601: //角色重名不需要关闭连接
		break;
	default:
		{
			Close();
		}
	}
	SaveLog((const char*)m_Query.m_SqlStr);//保存错误的Sql语句
	char ErrorBuffer[512] = {0};
	sprintf(ErrorBuffer,"ErrorCode = %d,ErrorMessage = %s",mErrorCode,mErrorMsg);
	SaveLog(ErrorBuffer);
	__LEAVE_FUNCTION
}

void	ODBCInterface::DiagStateEx()
{
	
	__ENTER_FUNCTION
	int				ii=1;
	SQLINTEGER		NativeError;
	SQLCHAR			SqlState[6];
	SQLSMALLINT		MsgLen;
	memset(mErrorMsg,0,MAX_ERROR_MSG_LENGHT);	
	while (mResult=SQLGetDiagRec(SQL_HANDLE_DBC, hDbc, ii, SqlState, &NativeError, 
		mErrorMsg, sizeof(mErrorMsg), &MsgLen) !=SQL_NO_DATA) 
	{
		ii++;

	}

	mErrorMsg[MAX_ERROR_MSG_LENGHT-1] = '\0'; //防止错误消息溢出

	if(strlen((const char*)mErrorMsg) == 0)
	{//自定义数据库错误

		mResult	=	SQLError(hEnv,hDbc,hStmt,SqlState,
			&NativeError,mErrorMsg,sizeof(mErrorMsg),&MsgLen);
	}
	mErrorCode =  NativeError;

	switch(mErrorCode) 
	{
	case 2601: //角色重名
		break;
	case 3621: //角色重名
		break;
	default:
		{
			Close();
		}
	}

	char ErrorBuffer[512] = {0};
	sprintf(ErrorBuffer,"ErrorCode = %d,ErrorMessage = %s,ErrorSql",mErrorCode,mErrorMsg);
	SaveErrorLog(ErrorBuffer);
	SaveErrorLog((const char*)m_LongQuery.m_SqlStr);//保存错误的Sql语句
	__LEAVE_FUNCTION
}

void ODBCInterface::SaveLog(const char* pLog)
{
	

	if(strlen(pLog)==0)
		return;

	FILE* f = fopen( "./Log/database.log", "a" ) ;
	fwrite( pLog, 1, strlen(pLog), f ) ;
	fwrite( "\r\n", 1, 2, f ) ;
	fclose(f) ;

	
}

void ODBCInterface::CleanEnv()
{
	if (hStmt)	
	{
		SQLCloseCursor(hStmt);
		SQLFreeStmt(hStmt, SQL_UNBIND);
		SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
		hStmt = NULL;
	}
	if (hDbc)
	{
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DESC,hDbc);
		hDbc = NULL;
	}
	if (hEnv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
		hEnv = NULL;
	}
}

