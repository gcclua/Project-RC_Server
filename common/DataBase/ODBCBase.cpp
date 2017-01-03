////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：15:23 2013-11-14
//             说明：
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCBase.h"

ODBCBase::ODBCBase()
{
	mResult = 0;
	mResultCount = 0;
	mOPType = DB_INIT_EMPTY;
}

tuint32 ODBCBase::GetResultCount()
{
	return mResultCount;
}

DB_QUERY*	ODBCBase::GetInternalQuery()
{
	return &mInterface->GetQuery();
}
LONG_DB_QUERY*	ODBCBase::GetLongInterQuery()
{
	return &mInterface->GetLongQuery();
}

tint32			ODBCBase::GetInternalAffectCount()
{
	return mInterface->GetAffectedRowCount();
}

bool	ODBCBase::IsPrepare()
{
	__ENTER_FUNCTION

	return mInterface->IsPrepare();

	__LEAVE_FUNCTION

	return false;
}

bool	ODBCBase::Load_Execute()
{
	__ENTER_FUNCTION


	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;
	
	if(!pInterface)
		return false;

	mOPType = DB_LOAD;

	mResult = pInterface->Execute();
	
	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool	ODBCBase::LongLoad_Execute()
{
	__ENTER_FUNCTION


	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_LOAD;

	mResult = pInterface->LongExecute();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool	ODBCBase::LongLoadEx_Execute()
{
	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_LOAD;

	mResult = pInterface->LongExecuteEx();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool	ODBCBase::AddNew_Execute()
{
	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_ADDNEW;

	mResult = pInterface->Execute();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCBase::Delete_Execute()
{
	__ENTER_FUNCTION

    if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_DELETE;

	mResult = pInterface->Execute();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION	

	return false;
}

bool ODBCBase::LongDelete_Execute()
{
__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_DELETE;

	mResult = pInterface->LongExecute();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

__LEAVE_FUNCTION	

	return false;
}

bool	ODBCBase::Save_Execute()
{

	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_SAVE;

	mResult = pInterface->Execute();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION

		return false;
}

bool	ODBCBase::LongSave_Execute()
{

	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_SAVE;

	mResult = pInterface->LongExecute();

	mResultCount	= static_cast<tint32>(pInterface->mAffectCount);

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

tint32	ODBCBase::GetErrorCode()
{
	return mInterface->GetError();
}

tchar* ODBCBase::GetErrorMessage()
{
	return mInterface->GetErrorMsg();
}

bool ODBCBase::CheckDBConnect(const tchar* pInfo)
{
__ENTER_FUNCTION
	AssertEx(mInterface,"");
	tchar info[256] = {0};
	if(pInfo)	strncpy(info,pInfo,255);

	if(!mInterface->IsConnected())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"ERROR:%s...connect database is fails",info);
		for(tint32 i = 0; i < 5; ++i)
		{
			_Sleep(5000);
			//暂不使用g_DBConnectThread尽量避免并发重连[2007/12/03 YangJun]
			//这个接口只在ShareMemory程序内使用
			if(mInterface->Connect())
			{
				CacheLog(LOGDEF_INST(DBAgentError),"ERROR:%s...Reconnect database",info);
				return true;
			}

			CacheLog(LOGDEF_INST(DBAgentError),"ERROR:%s...Can't connect database(%d)",info,i);
		}

		return false;
	}

	return true;
__LEAVE_FUNCTION
	return false;
}