
#include "ODBCTileData.h"
#include "DataBase/ODBCInterface.h"
#include "DataBase/SqlTemplate.h"



ODBCTileData::ODBCTileData(ODBCInterface* pInterface)
{

	mResult			= 0;
	mResultCount	= 0;
	AssertEx(pInterface,"");
	mInterface		=	pInterface;

}


bool ODBCTileData::Load()
{
	__ENTER_FUNCTION
		LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		AssertEx(false,"");
	}

	pQuery->Clear();

	pQuery->Parse(LoadTileData);

	return ODBCBase::LongLoad();
	__LEAVE_FUNCTION
		return false;
}

bool ODBCTileData::Save(DBTileDataPtr* pSource)
{
	__ENTER_FUNCTION
		LONG_DB_QUERY* pQuery = GetLongInterQuery();

	if(!pQuery)
	{
		return false;
	}

	AssertEx(pSource,"");

	DBTileDataPtr& rTileDataPtr = *pSource;

	AssertEx(rTileDataPtr,"ODBCTileData::rTilePtr");
	AssertEx(rTileDataPtr->m_Count <= MAX_TILE_NUM,"");

	for (int i=0;i<rTileDataPtr->m_Count;i++)
	{
		mInterface->Clear();
		CheckDBConnect("TileData");
		if (rTileDataPtr->m_pData[i].m_tileID <=0)
		{
			break;
		}
		pQuery->Clear();

		pQuery->Parse(UpdateTileData,
			TILE_TABLE,
			rTileDataPtr->m_pData[i].m_nPosX,
			rTileDataPtr->m_pData[i].m_nPosY,
			rTileDataPtr->m_pData[i].m_nBlock,
			rTileDataPtr->m_pData[i].m_nType,
			rTileDataPtr->m_pData[i].m_tileID
			);

		if (!ODBCBase::LongSave())
		{
			CACHE_LOG("DBAgentError","ODBCTileData::Save Fail tileId"<<rTileDataPtr->m_pData[i].m_tileID);
			return false;
		}

		mInterface->Clear();
	}

	return true;

	__LEAVE_FUNCTION
		return false;
}

bool ODBCTileData::ParseResult(DBTileDataPtr* pSource)
{
	__ENTER_FUNCTION
		switch(mOPType)
	{
		case DB_LOAD:
			{
				enum 
				{
					DB_TileId	=	1,
					DB_PosX,
					DB_PosY,
					DB_Block,
					DB_Type,
				};

				AssertEx(pSource,"");
				AssertEx(mInterface,"");

				DBTileDataPtr& rTileDataPtr = *pSource;

				AssertEx(rTileDataPtr,"");
				int	   ErrorCode;

				//加载基本属性
				for(int i =0;i<rTileDataPtr->m_Count;i++)
				{
					if(!mInterface->Fetch())
						break;

					rTileDataPtr->m_pData[i].m_tileID = mInterface->GetInt(DB_TileId,ErrorCode);
					rTileDataPtr->m_pData[i].m_nPosX  = mInterface->GetInt(DB_PosX,ErrorCode);
					rTileDataPtr->m_pData[i].m_nPosY  = mInterface->GetInt(DB_PosY,ErrorCode);
					rTileDataPtr->m_pData[i].m_nBlock = mInterface->GetInt(DB_Block,ErrorCode);
					rTileDataPtr->m_pData[i].m_nType  = mInterface->GetInt(DB_Type,ErrorCode);
					mInterface->Clear();

					

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

	AssertEx(mInterface,"");
	mInterface->Clear();

	return true;
	__LEAVE_FUNCTION
		return false;
}

