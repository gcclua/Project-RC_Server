////////////////////////////////////////////////////////////////////////////////////////
//
//             时间：11:08 2013-11-15 
//			   说明：玩家数据存储
//
//
/////////////////////////////////////////////////////////////////////////////////////////
#include "ODBCTroopData.h"

ODBCTroopData::ODBCTroopData(ODBCInterface* pInterface)
{
	__ENTER_FUNCTION

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

	m_nMarchId = invalid_guid64;

	__LEAVE_FUNCTION
}


void ODBCTroopData::SetMarchId(int64 marchId)
{
	m_nMarchId=marchId;
}
int64 ODBCTroopData::GetMarchId()
{
	return m_nMarchId;
}

bool ODBCTroopData::Load()
{
	__ENTER_FUNCTION
	DB_QUERY* pQuery = GetInternalQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	} 

	if(m_nMarchId==invalid_guid64)
	{
		return false;
	}

	mInterface->Clear();
	pQuery->Clear(); 


	pQuery->Parse(LoadMarchTroop,m_nMarchId);

	return ODBCBase::Load_Execute();
		return true;

	__LEAVE_FUNCTION

		return false;
}

bool ODBCTroopData::Save(DBTroop* pSource)
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
	DBTroop& rTroopData = *pSource;

	pQuery->Parse(UpdateTroop,
		rTroopData.m_nId,
		rTroopData.m_nMarchId,
		rTroopData.m_nType,
		rTroopData.m_nLevel,
		rTroopData.m_nQueueIndex,
		rTroopData.m_nArrangeIndex,
		rTroopData.m_nHp
		);
	if(!ODBCBase::LongSave_Execute())
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[ODBCTroopData::Save]:Fail \1 troopid=%lld,marchid=%d",
			rTroopData.m_nId,rTroopData.m_nMarchId);
		return false;	
	}  	   
	
	return true;

	__LEAVE_FUNCTION

	return false;
}

bool ODBCTroopData::ParseResult(DBMarch* pResult)
{
	__ENTER_FUNCTION

	bool bRet = false;
	switch(mOPType)
	{
	case DB_LOAD:
		{
			enum 
			{
				DB_TroopId	=	1,
				DB_MarchId,
				DB_Type,
				DB_LEVEL,
				DB_HP,
				DB_QueueIndex,
				DB_ArrangeIndex
			};
			//加载Guild属性
			AssertEx(mInterface,"");

			AssertEx(pResult,"")
				DBMarch& rMarch = *pResult;	  			

			tint32 ErrorCode;
			for (tint32 i = 0; i < TROOP_QUEUE_MAX_COUNT; ++i)
			{
				DBTroop &rTroop = rMarch.m_TroopList[i];
				rTroop.CleanUp();
				if (!mInterface->Fetch())
				{
					break;
				}

				rTroop.m_nId              = mInterface->GetUInt64(DB_TroopId, ErrorCode);
				rTroop.m_nMarchId         = mInterface->GetUInt64(DB_MarchId, ErrorCode);
				rTroop.m_nType            = mInterface->GetBYTE(DB_Type, ErrorCode);
				rTroop.m_nHp              = mInterface->GetInt(DB_HP,ErrorCode);
				rTroop.m_nLevel           = mInterface->GetBYTE(DB_LEVEL, ErrorCode);
				rTroop.m_nQueueIndex      = mInterface->GetBYTE(DB_QueueIndex, ErrorCode);
				rTroop.m_nArrangeIndex    = mInterface->GetBYTE(DB_ArrangeIndex, ErrorCode);
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

