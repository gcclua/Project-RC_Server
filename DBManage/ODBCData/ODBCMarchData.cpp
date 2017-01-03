////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCMarchData.h"
#include "ODBCTroopData.h"
ODBCMarchData::ODBCMarchData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_MarchId  = invalid_guid64;
	m_CityId   = invalid_guid64;
	__LEAVE_FUNCTION
}

bool ODBCMarchData::Save(DBMarch* pSource)
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
	DBMarch& rMarchData = *pSource;

	pQuery->Parse(UpdateMarch,
		rMarchData.m_nMarchId,
		rMarchData.m_Hero.m_nHeroId,
		rMarchData.m_nPlayerId,
		rMarchData.m_nCityId,
		rMarchData.m_nBuildId,
		rMarchData.m_pos.m_nX,
		rMarchData.m_pos.m_nZ,
		rMarchData.m_nBeginTime,
		rMarchData.m_nEndTime,
		rMarchData.m_nStatus
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCMarchData::Save]:Fail \1 marchid=%lld,debug=%d",
			rMarchData.m_nMarchId,debug);
		return false;	
	}  	   
	
	debug = 2;

	for (tint32 i = 0;i < TROOP_QUEUE_MAX_COUNT; ++i)
	{
		DBTroop &rTroop= rMarchData.m_TroopList[i];
		if (rTroop.m_nId>0)
		{
			ODBCTroopData TroopDataObj(mInterface);
			if(!TroopDataObj.Save(&rTroop))
			{
				return false;
			}
		}
	}



	return true;

	__LEAVE_FUNCTION

	return false;
}

void ODBCMarchData::SetMarchId(int64 guid)
{
	m_MarchId = guid;
}
int64 ODBCMarchData::GetMarchId()
{
	return m_MarchId;
}

void ODBCMarchData::SetCityId(int64 cityId)
{
	 m_CityId = cityId;
}
int64 ODBCMarchData::GetCityId()
{
	return m_CityId;
}

bool ODBCMarchData::Load()
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


	pQuery->Parse(LoadMarch,m_CityId);

	return ODBCBase::Load_Execute();

	__LEAVE_FUNCTION

		return false;
}

bool ODBCMarchData::ParseResult(DBFullUserData* pResult)
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
			DBFullUserData& rUser = *pResult;

			enum 
			{
				DB_MarchId = 1,
				DB_HeroId,			
				DB_CharGuid,			
				DB_BuildId,
				DB_PosX,
				DB_PosZ,
				DB_State,
				DB_BeginTime,
				DB_EndTime,
				

			};
			AssertEx(mResultCount<=1,"");
			AssertEx(mInterface,"");

			tint32	   ErrorCode;

			for (tint32 i = 0; i < MARCH_MAX_COUNT; ++i)
			{
				DBMarch &rMarch= rUser.m_MarchList[i];
				rMarch.CleanUp();
				if (!mInterface->Fetch())
				{
					break;
				}

				//加载角色基本属性
				rMarch.m_nMarchId       = mInterface->GetLongLong(DB_MarchId,ErrorCode);
				rMarch.m_Hero.m_nHeroId = mInterface->GetLongLong(DB_HeroId,ErrorCode);
				rMarch.m_nPlayerId      = mInterface->GetLongLong(DB_CharGuid,ErrorCode);
				rMarch.m_nBuildId       = mInterface->GetLongLong(DB_BuildId,ErrorCode);
				rMarch.m_pos.m_nX       = mInterface->GetInt(DB_PosX,ErrorCode);
				rMarch.m_pos.m_nZ       = mInterface->GetInt(DB_PosZ,ErrorCode);
				rMarch.m_nBeginTime     = mInterface->GetInt(DB_BeginTime,ErrorCode);
				rMarch.m_nEndTime       = mInterface->GetInt(DB_EndTime,ErrorCode);
				rMarch.m_nStatus        = mInterface->GetBYTE(DB_State,ErrorCode);
				rMarch.m_nCityId        = m_CityId;
			}
			mInterface->Clear();

			for (tint32 i = 0;i < MARCH_MAX_COUNT; ++i)
			{
				DBMarch &rMarch= rUser.m_MarchList[i];
				if (rMarch.m_nMarchId>0)
				{
					ODBCTroopData TroopDataObj(mInterface);
					TroopDataObj.SetMarchId(rMarch.m_nMarchId);
					if(!TroopDataObj.Load())
					{
						return false;
					}
					TroopDataObj.ParseResult(&rMarch);
				}
			}


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

