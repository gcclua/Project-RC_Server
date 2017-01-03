////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCHeroData.h"

ODBCHeroData::ODBCHeroData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_CityId = invalid_guid64;

	__LEAVE_FUNCTION
}

void ODBCHeroData::SetCityId(int64 cityId)
{
	m_CityId = cityId;
}
int64 ODBCHeroData::GetCityId()
{
	return m_CityId;
}

bool ODBCHeroData::Load()
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


	pQuery->Parse(LoadHero,m_CityId);

	return ODBCBase::Load_Execute();
	return true;

	__LEAVE_FUNCTION

		return false;
}

bool ODBCHeroData::Save(DBHero* pSource)
{
 	__ENTER_FUNCTION
	LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}
	pQuery->Clear();

	AssertEx(pSource != null_ptr,"");
	DBHero& rHeroData = *pSource;

	pQuery->Parse(UpdateHero,
		rHeroData.m_nHeroId,
		rHeroData.m_nCityID,
		rHeroData.m_nMarchId,
		rHeroData.m_nType,
		rHeroData.m_nLevel,
		rHeroData.m_nQuality,
		rHeroData.m_nStatus,
		rHeroData.m_nExp,
		rHeroData.m_nQueueIndex,
		rHeroData.m_nArrangeIndex,
		rHeroData.m_nHp
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCHeroData::Save]:Fail \1 guid=%lld",
			rHeroData.m_nHeroId);
		return false;	
	}  	   
	
	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCHeroData::ParseResult(DBFullUserData* pResult)
{
	__ENTER_FUNCTION

		bool bRet = false;
	switch(mOPType)
	{
	case DB_LOAD:
		{
			enum 
			{
				DB_HeroId	=	1,
				DB_Cityid,
				DB_MarchId,
				DB_Type,
				DB_LEVEL,
				DB_Quality,
				DB_State,
				DB_Exp,
				DB_Hp,
				DB_QueueIndex,
				DB_ArrangeIndex
			};
			//加载Guild属性
			AssertEx(mInterface,"");

			AssertEx(pResult,"")
				DBFullUserData& rUser = *pResult;	  			

			tint32 ErrorCode;
			for (tint32 i = 0; i < HEROTYPE_MAX; ++i)
			{
				DBHero &rHero= rUser.m_HeroList[i];
				rHero.CleanUp();
				if (!mInterface->Fetch())
				{
					break;
				}

				rHero.m_nHeroId          = mInterface->GetUInt64(DB_HeroId, ErrorCode);
				rHero.m_nMarchId         = mInterface->GetUInt64(DB_MarchId, ErrorCode);
				rHero.m_nCityID          = mInterface->GetUInt64(DB_Cityid, ErrorCode);
				rHero.m_nType            = mInterface->GetBYTE(DB_Type, ErrorCode);
				rHero.m_nLevel           = mInterface->GetBYTE(DB_LEVEL, ErrorCode);
				rHero.m_nQuality         = mInterface->GetBYTE(DB_Quality, ErrorCode);
				rHero.m_nExp             = mInterface->GetBYTE(DB_Exp, ErrorCode);
				rHero.m_nHp              = mInterface->GetInt(DB_Hp,ErrorCode);
				rHero.m_nQueueIndex      = mInterface->GetBYTE(DB_QueueIndex, ErrorCode);
				rHero.m_nArrangeIndex    = mInterface->GetBYTE(DB_ArrangeIndex, ErrorCode);
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
	return bRet;
	__LEAVE_FUNCTION
		return false;
}

