
#include "ODBCBase.h"


ODBCBase::ODBCBase()
{
	mResult = 0;
	mResultCount = 0;
	
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

int			ODBCBase::GetInternalAffectCount()
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

bool  ODBCBase::CheckDBConnect(const char* pInfo)
{
	__ENTER_FUNCTION
		AssertEx(mInterface,"");
		char info[256] = {0};
		if (pInfo)
		{
			strncpy(info,pInfo,255);
		}
		if (!mInterface->IsConnected())
		{
			CACHE_LOG("DBAgentError","ERROR:"<<info<<"...connect database is fails");
			for (int i = 0;i < 5; i++)
			{
				_Sleep(5000);
				if (mInterface->Connect())
				{
					CACHE_LOG("DBAgentError","ERROR:"<<info<<"... Reconnect database");
					return true;
				}
				CACHE_LOG("DBAgentError","ERROR:"<<info<<"... can't connect database("<<i<<")");
			}
		}
	__LEAVE_FUNCTION
	return false;
}

bool	ODBCBase::Load()
{
	
	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;
	
	if(!pInterface)
		return false;

	mOPType = DB_LOAD;

	mResult = pInterface->Execute();
	
	mResultCount	= pInterface->mAffectCount;

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool	ODBCBase::LongLoad()
{
	
	__ENTER_FUNCTION

		if(!IsPrepare())
			return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_LOAD;

	mResult = pInterface->LongExecute();

	mResultCount	= pInterface->mAffectCount;

	return mResult;

	__LEAVE_FUNCTION

		return false;
}


bool	ODBCBase::AddNew()
{
	
	__ENTER_FUNCTION
	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_ADDNEW;

	mResult = pInterface->Execute();

	mResultCount	= pInterface->mAffectCount;

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCBase::Delete()
{
	__ENTER_FUNCTION

    if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_DELETE;

	mResult = pInterface->Execute();

	mResultCount	= pInterface->mAffectCount;

	return mResult;

	__LEAVE_FUNCTION	

	return false;
}

bool	ODBCBase::Save()
{

	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_SAVE;

	mResult = pInterface->Execute();

	mResultCount	= pInterface->mAffectCount;

	return mResult;

	__LEAVE_FUNCTION

	return false;
}

bool	ODBCBase::LongSave()
{

	__ENTER_FUNCTION

	if(!IsPrepare())
		return false;

	ODBCInterface* pInterface= 	mInterface;

	if(!pInterface)
		return false;

	mOPType = DB_SAVE;

	mResult = pInterface->LongExecute();

	mResultCount	= pInterface->mAffectCount;

	return mResult;

	__LEAVE_FUNCTION

	return false;
}



VOID ODBCBase::SetDBName(DB_NAMES dbName)
{
	mDBName = dbName;
}

int	ODBCBase::GetErrorCode()
{
	return mInterface->GetError();
}

char* ODBCBase::GetErrorMessage()
{
	return mInterface->GetErrorMsg();
}