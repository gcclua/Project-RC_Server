////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCCreateChar.h"

ODBCCreateChar::ODBCCreateChar(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_CRCValue = 0;

	__LEAVE_FUNCTION
}

bool ODBCCreateChar::Save(DBFullUserData* pSource)
{
 	__ENTER_FUNCTION
	LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}
	pQuery->Clear();

	AssertEx(pSource != null_ptr,"");
	DBFullUserData& rUserFullData = *pSource;

	if(!StrSafeCheck(rUserFullData.m_User.m_AccName, sizeof(rUserFullData.m_User.m_AccName)))
	{
		return false;
	}

	if(!StrSafeCheck(rUserFullData.m_User.m_CharName,sizeof(rUserFullData.m_User.m_CharName)))
	{
		return false;
	}
	

	tuint32 crcValue = rUserFullData.CalcCRC();

	pQuery->Parse(CreateChar,
				  rUserFullData.GetGuid(),
				  rUserFullData.m_User.m_CharName,
				  rUserFullData.m_User.m_AccName,
				  rUserFullData.m_User.m_Level,
				  rUserFullData.m_User.m_Gender);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCCreateChar::Save]:Fail \1 UserGUID=%lld",
			rUserFullData.GetGuid());
		return false;	
	}  	   

	AssertEx(mResultCount>0,"");

	if(mResultCount==0)
	{
		DiskLog(LOGDEF_INST(DBAgentError),"ODBCCreateChar AffectRowCount==0: \1 %s",
			(const tchar*)pQuery->m_SqlStr);
		return true;
	} 

	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCCreateChar::ParseResult(tint32* pResult)
{
	__ENTER_FUNCTION

	bool bRet = false;
	switch(mOPType)
	{
	case DB_SAVE:
		{
			enum
			{
				DB_CreatResult = 1,
			};

			enum
			{
				Duplicate_CharName	= -2,
				Invalid_CharGuid	= -3,
				Max_CharNum			= -4,
				CreateOk			= 1,
			};

			AssertEx(pResult,"");
			AssertEx(mInterface,"");
			if(!mInterface->Fetch())	
				return false;
			tint32& rAskResult = *pResult;

			tint32 ErrorCode;
			tint32 ResultCode = mInterface->GetInt(DB_CreatResult,ErrorCode);

			switch(ResultCode)
			{
			case Duplicate_CharName:
				rAskResult = DBMsgResult::RESULT_SAME_NAME;
				break;
			case CreateOk:
				rAskResult = DBMsgResult::RESULT_SUCCESS;
				bRet = true;
				break;
			case Invalid_CharGuid:
				rAskResult = DBMsgResult::RESULT_SAME_GUID;
				break;
			default:
				rAskResult = DBMsgResult::RESULT_FAIL;
				break;
			}

			mInterface->Clear();
		}
		break;
	default:
		break;
	}

	AssertEx(mInterface,"");
	mInterface->Clear();
	return bRet;
	__LEAVE_FUNCTION
		return false;
}

