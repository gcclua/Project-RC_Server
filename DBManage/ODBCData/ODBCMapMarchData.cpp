////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCMapMarchData.h"
#include "ODBCTroopData.h"
ODBCMapMarchData::ODBCMapMarchData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	__LEAVE_FUNCTION
}

bool ODBCMapMarchData::Load()
{
	__ENTER_FUNCTION
	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	} 

	mInterface->Clear();
	pQuery->Clear(); 


	pQuery->Parse(LoadMapMarch);

	return ODBCBase::Load_Execute();

	__LEAVE_FUNCTION

		return false;
}

bool ODBCMapMarchData::ParseResult(DBMarchDataPtr* pResult)
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
			DBMarchDataPtr& pMapMarch = *pResult;

			enum 
			{
				DB_MarchId = 1,
				DB_HeroId,			
				DB_CharGuid,			
				DB_BuildId,
				DB_CityId,
				DB_PosX,
				DB_PosZ,
				DB_State,
				DB_BeginTime,
				DB_EndTime,
				

			};
			AssertEx(mResultCount>=0,"");
			AssertEx(mInterface,"");

			tint32	   ErrorCode;

			for (int i=0;i<mResultCount;i++)
			{
				if (!mInterface->Fetch())
				{
					break;
				}

				//加载角色基本属性
				pMapMarch->m_pData[i].m_nMarchId       = mInterface->GetLongLong(DB_MarchId,ErrorCode);
				pMapMarch->m_pData[i].m_Hero.m_nHeroId = mInterface->GetLongLong(DB_HeroId,ErrorCode);
				pMapMarch->m_pData[i].m_nPlayerId      = mInterface->GetLongLong(DB_CharGuid,ErrorCode);
				pMapMarch->m_pData[i].m_nBuildId       = mInterface->GetLongLong(DB_BuildId,ErrorCode);
				pMapMarch->m_pData[i].m_pos.m_nX       = mInterface->GetInt(DB_PosX,ErrorCode);
				pMapMarch->m_pData[i].m_pos.m_nZ       = mInterface->GetInt(DB_PosZ,ErrorCode);
				pMapMarch->m_pData[i].m_nBeginTime     = mInterface->GetInt(DB_BeginTime,ErrorCode);
				pMapMarch->m_pData[i].m_nEndTime       = mInterface->GetInt(DB_EndTime,ErrorCode);
				pMapMarch->m_pData[i].m_nStatus        = mInterface->GetBYTE(DB_State,ErrorCode);
				pMapMarch->m_pData[i].m_nCityId        = mInterface->GetLongLong(DB_CityId,ErrorCode);
			}
			mInterface->Clear();
			int iSize = (int)pMapMarch->m_Count;
			for (tint32 i = 0;i < iSize; ++i)
			{
				DBMarch &rMarch= pMapMarch->m_pData[i];
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

