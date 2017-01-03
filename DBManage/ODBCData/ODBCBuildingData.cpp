////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCBuildIngData.h"

ODBCBuildIngData::ODBCBuildIngData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_nCityId = invalid_guid64;

	__LEAVE_FUNCTION
}

void ODBCBuildIngData::SetCityId(int64 guid)
{
	m_nCityId = guid;
}
int64 ODBCBuildIngData::GetCityId()
{
	return m_nCityId;
}

bool ODBCBuildIngData::Load()
{
	__ENTER_FUNCTION
	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	} 

	if(m_nCityId==invalid_guid64)
	{
		return false;
	}

	mInterface->Clear();
	pQuery->Clear(); 


	pQuery->Parse(LoadBuilding,m_nCityId);

	return ODBCBase::Load_Execute();
		return true;

	__LEAVE_FUNCTION

		return false;
}

bool ODBCBuildIngData::Save(DBBuilding* pSource)
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
	DBBuilding& rBuildingData = *pSource;

	pQuery->Parse(UpdateBuilding,
		rBuildingData.m_ID,
		rBuildingData.m_nCityID,
		rBuildingData.m_nType,
		rBuildingData.m_nSlot,
		rBuildingData.m_nLevel
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCBuildIngData::Save]:Fail \1 guid=%lld,cityid=%d",
			rBuildingData.m_ID,rBuildingData.m_nCityID);
		return false;	
	}  	   
	
	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCBuildIngData::ParseResult(DBCity* pResult)
{
	__ENTER_FUNCTION

	bool bRet = false;
	switch(mOPType)
	{
	case DB_LOAD:
		{
			enum 
			{
				DB_Guid	=	1,
				DB_Type,
				DB_Slot,
				DB_LEVEL
			};
			//加载Guild属性
			AssertEx(mInterface,"");

			AssertEx(pResult,"")
				DBCity& rCity = *pResult;	  			

			tint32 ErrorCode;
			for (tint32 i = 0; i < BUIDINGTYPE_MAX; ++i)
			{
				DBBuilding &rBuild = rCity.m_BuildingList[i];
				rBuild.CleanUp();
				if (!mInterface->Fetch())
				{
					break;
				}

				rBuild.m_ID               = mInterface->GetUInt64(DB_Guid, ErrorCode);
				rBuild.m_nCityID          = m_nCityId;
				rBuild.m_nType            = mInterface->GetBYTE(DB_Type, ErrorCode);
				rBuild.m_nSlot            = mInterface->GetInt(DB_Slot,ErrorCode);
				rBuild.m_nLevel           = mInterface->GetBYTE(DB_LEVEL, ErrorCode);
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

