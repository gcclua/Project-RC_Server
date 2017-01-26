////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCCharFullData.h"
#include "ODBCCityData.h"
#include "ODBCBuildingData.h"
#include "ODBCHeroData.h"
#include "ODBCMarchData.h"
#include "ODBCTroopTrainData.h"

ODBCCharFullData::ODBCCharFullData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

		mResult			= 0;
		mResultCount	= 0;
		m_CharGuid		= invalid_guid64;
		AssertEx(pInterface,"");
		mInterface		=	pInterface;
		m_CRCValue      = 0;
		m_DebugStep     = 0;

	__LEAVE_FUNCTION
}


bool ODBCCharFullData::Load()
{
	__ENTER_FUNCTION

		DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	} 

	if(m_CharGuid==invalid_guid64)
	{
		return false;
	}

	mInterface->Clear();
	pQuery->Clear(); 


	pQuery->Parse(LoadCharFullData,m_CharGuid);

	return ODBCBase::Load_Execute();

	__LEAVE_FUNCTION

		return false;
}

bool ODBCCharFullData::Save(DBFullUserData* pSource)
{
	__ENTER_FUNCTION
		LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}

	pQuery->Clear();

	m_DebugStep = 10;
	if(m_CharGuid==invalid_guid64)
	{
		return false;
	}

	AssertEx(pSource != null_ptr,"");
	DBFullUserData& rUserFullData = *pSource;

	m_DebugStep = 15;

	if(!StrSafeCheck(rUserFullData.m_User.m_AccName,sizeof(rUserFullData.m_User.m_AccName)))
	{
		return false;
	}

	if(!StrSafeCheck(rUserFullData.m_User.m_CharName,sizeof(rUserFullData.m_User.m_CharName)))
	{
		return false;
	}

	

	m_DebugStep = 20;

	//公共数据
	STATIC_ASSERT(sizeof(rUserFullData.m_User.m_CommonData) == 2048);
	tchar COMMONDATA[sizeof(rUserFullData.m_User.m_CommonData)*2+1];
	memset(COMMONDATA,0,sizeof(COMMONDATA));
	Binary2String((tchar*)rUserFullData.m_User.m_CommonData,sizeof(rUserFullData.m_User.m_CommonData),COMMONDATA,sizeof(COMMONDATA));

	//公共标记位
	STATIC_ASSERT(sizeof(rUserFullData.m_User.m_CommonFlag) == 20);
	tchar COMMONFLAG[sizeof(rUserFullData.m_User.m_CommonFlag)*2+1];
	memset(COMMONFLAG,0,sizeof(COMMONFLAG));
	Binary2String((tchar*)rUserFullData.m_User.m_CommonFlag,sizeof(rUserFullData.m_User.m_CommonFlag) ,COMMONFLAG,sizeof(COMMONFLAG));


	//计算CRC
	m_CRCValue = rUserFullData.CalcCRC();

	pQuery->Parse(UpdateCharFullData,
		rUserFullData.GetGuid(),
		rUserFullData.m_User.m_CharName,
		rUserFullData.m_User.m_AccName,
		rUserFullData.m_User.m_IsValid,
		COMMONDATA,
		COMMONFLAG,
		rUserFullData.m_User.m_CityId,
		rUserFullData.m_User.m_LastLogoutTime
		);
	m_DebugStep = 50;
	tint32 beforeSaveTime = gTimeManager.SysRunTime();

	if (!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[DBUserFullData::Save]:Fail \1 UserGUID=%lld",
			rUserFullData.GetGuid());
		return false;
	}

	m_DebugStep = 60;

	AssertEx(mResultCount<=5,"");
	mInterface->Clear();

	if (mResultCount == 0)
	{
		DiskLog(LOGDEF_INST(DBAgentError), "UpdateCharFullData AffectRowCount==0,UserGUID=%lld",
			rUserFullData.GetGuid());
		//return true;
	}

	tuint32 beforSaveTime = 0;


	CacheLog(LOGDEF_INST(DBAgent),"[DBUserFullData::Save]:DBFullUser \1 UserGUID=%lld \1 time=%d",
			rUserFullData.GetGuid(),gTimeManager.SysRunTime()-beforeSaveTime);
	beforeSaveTime = gTimeManager.SysRunTime();


	
	return true;

	__LEAVE_FUNCTION

		return false;
}

bool ODBCCharFullData::ParseResult(DBFullUserData* pResult)
{
	__ENTER_FUNCTION

		switch(mOPType)
	{
		case DB_LOAD:
			{

				AssertEx(pResult,"");
				DBFullUserData& rUserFullData = *pResult;

				rUserFullData.CleanUp();
				enum 
				{
					DB_AccName = 1,
					DB_CharName,
					DB_CharGuid,
					DB_IsValid,
					DB_CommonFlag,
					DB_CommonData,
					DB_LastLogoutTime,
					DB_CreateRoleTime,
					DB_CityId,
					DB_Gender
					
				};
				AssertEx(mResultCount<=1,"");
				AssertEx(mInterface,"");

				tint32	   ErrorCode;

				//加载基本属性
				if (mInterface->Fetch() )
				{
					//加载角色基本属性
					rUserFullData.m_User.m_Guid = m_CharGuid;

					mInterface->GetString(DB_AccName, rUserFullData.m_User.m_AccName, sizeof(rUserFullData.m_User.m_AccName), ErrorCode);

					mInterface->GetString(DB_CharName,rUserFullData.m_User.m_CharName,sizeof(rUserFullData.m_User.m_CharName),ErrorCode);


					rUserFullData.m_User.m_IsValid = mInterface->GetBYTE(DB_IsValid,ErrorCode); 
					rUserFullData.m_User.m_LastLogoutTime = mInterface->GetLongLong(DB_LastLogoutTime,ErrorCode); 
					rUserFullData.m_User.m_CreateRoleTime = mInterface->GetLongLong(DB_CreateRoleTime,ErrorCode); 
					rUserFullData.m_User.m_CityId         = mInterface->GetLongLong(DB_CityId,ErrorCode);
					rUserFullData.m_User.m_Gender         = mInterface->GetBYTE(DB_Gender,ErrorCode);
					mInterface->Clear();
				}

				//加载城市信息
				{				
					ODBCCityData CityDataObject(mInterface);
					CityDataObject.SetUserId(m_CharGuid);
					if(!CityDataObject.Load())
					{
						return false;
					}
					CityDataObject.ParseResult(&(rUserFullData.m_City));
				}

				// 加载建筑信息
				{				
					ODBCBuildIngData BuildingDataObject(mInterface);
					BuildingDataObject.SetCityId(rUserFullData.m_City.m_nCityID);
					if(!BuildingDataObject.Load())
					{
						return false;
					}
					BuildingDataObject.ParseResult(&(rUserFullData.m_City));
				}

				// 加载英雄信息
				{				
					ODBCHeroData HeroDataObject(mInterface);
					HeroDataObject.SetCityId(rUserFullData.m_City.m_nCityID);
					if(!HeroDataObject.Load())
					{
						return false;
					}
					HeroDataObject.ParseResult(&rUserFullData);
				}

				// 加载March信息
				{				
					ODBCMarchData MarchDataObject(mInterface);
					MarchDataObject.SetCityId(rUserFullData.m_City.m_nCityID);
					if(!MarchDataObject.Load())
					{
						return false;
					}
					MarchDataObject.ParseResult(&rUserFullData);

					ODBCTroopTrainData TroopTrainObject(mInterface);
					TroopTrainObject.SetCityId(rUserFullData.m_City.m_nCityID);

					if(!TroopTrainObject.Load())
					{
						return false;
					}
					TroopTrainObject.ParseResult(&rUserFullData.m_City);
				}
				
			}

			break;
		case DB_SAVE:
			{
				
			}
			break;
		default:
			break;
	}

	



	m_DebugStep = 305;
	AssertEx(mInterface,"");
	mInterface->Clear();
	return true;

	__LEAVE_FUNCTION

		return false;
}

int64	ODBCCharFullData::GetCharGuid()
{
	return m_CharGuid;
}

void	ODBCCharFullData::SetCharGuid(int64 guid)
{
	m_CharGuid	 = guid;
}
