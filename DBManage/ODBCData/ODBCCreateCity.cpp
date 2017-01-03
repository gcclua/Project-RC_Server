////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCCreateCity.h"
#include "ODBCBuildIngData.h"
#include "ODBCMarchData.h"
#include "ODBCHeroData.h"

ODBCCreateCity::ODBCCreateCity(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_CRCValue = 0;

	__LEAVE_FUNCTION
}

bool ODBCCreateCity::Save(DBCityCreate* pSource)
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
	DBCityCreate& rCityCreateData = *pSource;

	pQuery->Parse(CreateCity,
		rCityCreateData.m_nCityID,
		rCityCreateData.m_UserId,
		rCityCreateData.m_tileID,
		rCityCreateData.m_nPosX,
		rCityCreateData.m_nPosZ,
		rCityCreateData.m_nLevel,
		rCityCreateData.m_nFood,
		rCityCreateData.m_nStone,
		rCityCreateData.m_nIron,
		rCityCreateData.m_nGold
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCCreateCity::Save]:Fail \1 UserGUID=%lld,debug=%d",
			rCityCreateData.m_UserId,debug);
		return false;	
	}  	   
	
	debug = 2;

	for (int i=0;i<rCityCreateData.m_lstBuilding.size();i++)
	{
		DBBuilding rBuilding = rCityCreateData.m_lstBuilding[i];
		pQuery->Clear();
		ODBCBuildIngData ODBCBuild(mInterface);
		if (!ODBCBuild.Save(&rBuilding))
		{
			return false;
		}
	}

	for (int i=0;i<rCityCreateData.m_lstMarch.size();i++)
	{
		DBMarch rMarch = rCityCreateData.m_lstMarch[i];
		pQuery->Clear();
		ODBCMarchData ODBCMarch(mInterface);
		if (!ODBCMarch.Save(&rMarch))
		{
			return false;
		}

	}

	pQuery->Clear();
	ODBCHeroData ODBCHero(mInterface);
	if (!ODBCHero.Save(&rCityCreateData.m_Hero))
	{
		return false;
	}


	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCCreateCity::ParseResult(tint32* pResult)
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

