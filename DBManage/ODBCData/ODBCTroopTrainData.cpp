////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCTroopTrainData.h"
#include "ODBCTroopData.h"
ODBCTroopTrainData::ODBCTroopTrainData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_Id       = invalid_guid64;
	m_CityId   = invalid_guid64;
	__LEAVE_FUNCTION
}

bool ODBCTroopTrainData::Save(DBTroopTrain* pSource)
{
	int debug = 1;
 	__ENTER_FUNCTION
	LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}
	pQuery->Clear();

	AssertEx(pSource != null_ptr,"");
	DBTroopTrain& rTroopData = *pSource;

	pQuery->Parse(UpdateTroopTrain,
		rTroopData.m_ID,
		rTroopData.m_nCityID,
		rTroopData.m_nBeginTime,
		rTroopData.m_nCompleteTime,
		rTroopData.m_nType,
		rTroopData.m_nHp,
		rTroopData.m_nBuildId,
		rTroopData.m_nQueueIndex
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCTroopTrainData::Save]:Fail \1 id=%lld,debug=%d",
			rTroopData.m_ID,debug);
		return false;	
	} 



	return true;

	__LEAVE_FUNCTION

	return false;
}

void ODBCTroopTrainData::SetId(int64 guid)
{
	m_Id = guid;
}
int64 ODBCTroopTrainData::GetId()
{
	return m_Id;
}

void ODBCTroopTrainData::SetCityId(int64 cityId)
{
	 m_CityId = cityId;
}
int64 ODBCTroopTrainData::GetCityId()
{
	return m_CityId;
}

bool ODBCTroopTrainData::Load()
{
	__ENTER_FUNCTION
	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	} 

	if(m_CityId==invalid_guid64)
	{
		return false;
	}

	mInterface->Clear();
	pQuery->Clear(); 


	pQuery->Parse(LoadTroopTrain,m_CityId);

	return ODBCBase::Load_Execute();

	__LEAVE_FUNCTION

		return false;
}

bool ODBCTroopTrainData::ParseResult(DBCity* pResult)
{
	__ENTER_FUNCTION

	bool bRet = false;
	switch(mOPType)
	{
	case DB_SAVE:
		{
			
		}
		break;
	case DB_LOAD:
		{
			AssertEx(pResult,"");
			DBCity& rCity = *pResult;

			enum 
			{
				DB_ID = 1,		
				DB_BEGINTIME,			
				DB_ENDTIME,
				DB_TROOPTYPE,
				DB_PHP,
				DB_BUILDID,
				DB_QUEUEINDEX,
			};
			AssertEx(mResultCount>=0,"");
			AssertEx(mInterface,"");

			tint32	   ErrorCode;

			for (tint32 i = 0; i < BUILDING_BARRACK_MAX+BUILDING_WALL_MAX; ++i)
			{
				DBTroopTrain &rTroopTrain= rCity.m_TrainList[i];
				rTroopTrain.CleanUp();
				if (!mInterface->Fetch())
				{
					break;
				}

				//加载角色基本属性
				rTroopTrain.m_ID             = mInterface->GetLongLong(DB_ID,ErrorCode);
				rTroopTrain.m_nCityID        = m_CityId;
				rTroopTrain.m_nBeginTime     = mInterface->GetInt(DB_BEGINTIME,ErrorCode);
				rTroopTrain.m_nCompleteTime  = mInterface->GetInt(DB_ENDTIME,ErrorCode);
				rTroopTrain.m_nType          = mInterface->GetInt(DB_TROOPTYPE,ErrorCode);
				rTroopTrain.m_nHp            = mInterface->GetInt(DB_PHP,ErrorCode);
				rTroopTrain.m_nBuildId       = mInterface->GetInt(DB_BUILDID,ErrorCode);
				rTroopTrain.m_nQueueIndex    = mInterface->GetInt(DB_QUEUEINDEX,ErrorCode);
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

