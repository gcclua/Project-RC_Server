////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCCharList.h"
#include "DBStruct/DBStruct_CharList.h"

ODBCCharList::ODBCCharList(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_AccName.CleanUp();

	__LEAVE_FUNCTION
}

bool ODBCCharList::Load()
{
	__ENTER_FUNCTION

	if (m_AccName.GetLength() <= 0 || !StrSafeCheck(m_AccName.GetCText(), m_AccName.GetLength()))
	{
		return false;
	}

	DB_QUERY* pQuery = GetInternalQuery();
	AssertEx(pQuery,"");
	pQuery->Clear();

	pQuery->Parse(LoadCharList, m_AccName.GetCText());
	return ODBCBase::Load_Execute();
	__LEAVE_FUNCTION
		return false;
}

bool ODBCCharList::ParseResult(DBCharDataList* pResult)
{
	__ENTER_FUNCTION
	switch (mOPType)
	{
	case ODBCBase::DB_LOAD:
		{
			enum 
			{
				DB_CHARGUID = 1,
				DB_CHARNAME,					
			};
			AssertEx(pResult, "");
			AssertEx(mInterface, "");
			DBCharDataList& rCharListData = *pResult;

			tint32 ErrorCode;
			for(tint32 i=0; i<DB_CHAR_NUMBER; i++)
			{
				if(!mInterface->Fetch())
				{
					break;
				}
				rCharListData.m_CharDataList[i].m_Guid = mInterface->GetUInt64(DB_CHARGUID, ErrorCode);

				mInterface->GetString(DB_CHARNAME,rCharListData.m_CharDataList[i].m_CharName,MAX_NAME_SIZE,ErrorCode);
				rCharListData.m_CharNum++;

			}

			mInterface->Clear();
		}
		break;
	case ODBCBase::DB_SAVE:
		{
		}
		break;
	case ODBCBase::DB_DELETE:
		{
		}
		break;
	default:
		break;
	}
	AssertEx(mInterface, "");
	mInterface->Clear();
	return true;
	__LEAVE_FUNCTION
	return false;
}

void ODBCCharList::SetAccName(const ACCOUNTNAME& rAccName)
{
	__ENTER_FUNCTION
	m_AccName = rAccName;
	__LEAVE_FUNCTION
}
