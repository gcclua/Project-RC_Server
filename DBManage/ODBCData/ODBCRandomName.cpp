////////////////////////////////////////////////////////////////////////////////////////
//时间：2014年7月2日14:12:35
//说明：随机名字数据库
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCRandomName.h"

ODBCRandomName::ODBCRandomName(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION
AssertEx(pInterface, "");
	mInterface = pInterface;
	__LEAVE_FUNCTION
}					  

bool ODBCRandomName::Load()
{
	__ENTER_FUNCTION

	DB_QUERY* pQuery = GetInternalQuery();
	if(!pQuery)
	{
		AssertEx(false,"");
	}
	pQuery->Clear();
	pQuery->Parse(LoadRandomName);

	return ODBCBase::Load_Execute();

	__LEAVE_FUNCTION

	return false;
}

bool ODBCRandomName::ParseResult(DBRandomNameList* pResult)
{
	__ENTER_FUNCTION

	switch(mOPType)
	{
		case DB_LOAD:
			{
				enum 
				{
					DB_NAME	=	1,
				};

				AssertEx(mInterface,"");
				AssertEx(pResult,"");
				DBRandomNameList& rPtr = *pResult;
									
				rPtr.CleanUp();
				tint32 ErrorCode;
				for(tint32 i = 0;i < RANDOM_NAME_BUFFER_MAX; i++)
				{
					if(!mInterface->Fetch())
					{
						break;
					}

					mInterface->GetString(DB_NAME, rPtr.m_RandomNameList[i].m_szName, MAX_NAME_SIZE, ErrorCode);
				}
				mInterface->Clear();
			}
			break;
		case DB_DELETE:
			{

			}
			break;
		default:
			break;
	}

	AssertEx(mInterface,"");
	mInterface->Clear();
	return true;

	__LEAVE_FUNCTION

	return false;
}