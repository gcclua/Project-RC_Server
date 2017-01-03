////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCCityData.h"

ODBCCityData::ODBCCityData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_UserId = invalid_guid64;

	__LEAVE_FUNCTION
}

void ODBCCityData::SetUserId(int64 userId)
{
	m_UserId = userId;
}
int64 ODBCCityData::GetUserId()
{
	return m_UserId;
}

bool ODBCCityData::Load()
{
	__ENTER_FUNCTION
	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	} 

	if(m_UserId==invalid_guid64)
	{
		return false;
	}

	mInterface->Clear();
	pQuery->Clear(); 


	pQuery->Parse(LoadCity,m_UserId);

	return ODBCBase::Load_Execute();
	return true;

	__LEAVE_FUNCTION

		return false;
}

bool ODBCCityData::Save(DBCity* pSource)
{
 	__ENTER_FUNCTION
	LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}
	pQuery->Clear();

	AssertEx(pSource != null_ptr,"");
	DBCity& rCityData = *pSource;

	pQuery->Parse(UpdateCity,
		rCityData.m_nCityID,
		rCityData.m_tileID,
		rCityData.m_nPosX,
		rCityData.m_nPosZ,
		rCityData.m_nLevel,
		rCityData.m_nFood,
		rCityData.m_nStone,
		rCityData.m_nIron,
		rCityData.m_nGold
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCCityData::Save]:Fail \1 cityid=%lld",
			rCityData.m_nCityID);
		return false;	
	}  	   
	
	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCCityData::ParseResult(DBCity* pResult)
{
	__ENTER_FUNCTION

		bool bRet = false;
	switch(mOPType)
	{
	case DB_LOAD:
		{
			enum 
			{
				DB_Cityid = 1,
				DB_ChargGuid,
				DB_TileId,
				DB_PosX,
				DB_PosZ,
				DB_Level,
				DB_Food,
				DB_Stone,
				DB_Iron,
				DB_Gold
			};
			//加载Guild属性
			AssertEx(mInterface,"");

			AssertEx(pResult,"")
				DBCity& rCity = *pResult;	  
			tint32 ErrorCode;

			//加载基本属性
			if (mInterface->Fetch() )
			{
				//加载角色基本属性
				rCity.m_nCityID   = mInterface->GetLongLong(DB_Cityid,ErrorCode);
				rCity.m_nPlayerId = mInterface->GetLongLong(DB_ChargGuid,ErrorCode);
				rCity.m_tileID    = mInterface->GetInt(DB_TileId,ErrorCode);
				rCity.m_nPosX     = mInterface->GetInt(DB_PosX,ErrorCode);
				rCity.m_nPosZ     = mInterface->GetInt(DB_PosZ,ErrorCode);
				rCity.m_nLevel    = mInterface->GetInt(DB_Level,ErrorCode);

				rCity.m_nFood     = mInterface->GetLongLong(DB_Food,ErrorCode);
				rCity.m_nStone    = mInterface->GetLongLong(DB_Stone,ErrorCode);
				rCity.m_nIron     = mInterface->GetLongLong(DB_Iron,ErrorCode);
				rCity.m_nGold     = mInterface->GetLongLong(DB_Gold,ErrorCode);
				
				mInterface->Clear();
			}

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
	return bRet;
	__LEAVE_FUNCTION
		return false;
}

