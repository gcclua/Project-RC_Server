#include "WorldMapService.h"
#include "DBStruct/DBStruct.h"
#include "GameServerConfig.h"
#include "service/MessageOp.h"
#include "Message/DBMsg.h"

WorldMapService::WorldMapService()
{
	m_nDataSaveSec = TILE_DATA_SAVE_SEC;
	m_lstSaveTile.clear();
}

WorldMapService::~WorldMapService(void)
{

}

void WorldMapService::Init(void)
{
	__ENTER_FUNCTION
		
		InvokerPtr ptr(new WorldMapInvoker(*this,"WorldMapService"));
		AddInvoker(ptr);

	__LEAVE_FUNCTION
}

void WorldMapService::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
	Service::Tick(rTimeInfo);

	Tick_Save(rTimeInfo);

	__LEAVE_FUNCTION
}



void WorldMapService::Tick_Save(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (GetStatus() != ServiceStatus::RUNNING)
		{
			return;
		}
		if (rTimeInfo.m_bDiffSecond)
		{
			--m_nDataSaveSec;
			if (m_nDataSaveSec <= 0)
			{
				m_nDataSaveSec = TILE_DATA_SAVE_SEC;
				DBReqSaveTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBReqSaveTileDataMsg);
				AssertEx(MsgPtr,"");
				MsgPtr->m_DataPtr = DBTileDataPtr(new DBTileData);
				AssertEx(MsgPtr->m_DataPtr,"");
				Save(*(MsgPtr->m_DataPtr));
				SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);
			}
		}
	__LEAVE_FUNCTION
}

void WorldMapService::Load(const DBTileData& rData)
{
	__ENTER_FUNCTION
		if (rData.m_pData == null_ptr)
		{
			return;
		}

		AssertEx(rData.m_Count < MAX_TILE_NUM,"");
		for (int i = 0; i< rData.m_Count; i++)
		{
			TileInfo tempTile;
			tempTile.SerializeFromDB(rData.m_pData[i]);
			m_TileList.insert(std::make_pair(tempTile.GetID(),tempTile));

		}
		__LEAVE_FUNCTION
}
void WorldMapService::Save(DBTileData& rData)
{
	__ENTER_FUNCTION
		int nTileCount = (int)m_lstSaveTile.size();
	    if (nTileCount>0)
		{
			rData.InitDataArray(nTileCount);
			int nDataIndex = 0;
			for (SaveTileList::iterator it = m_lstSaveTile.begin(); it != m_lstSaveTile.end();it++)
			{
				int tileID = (*it);
				TileInfo* pTile = GetTileInfo(tileID);
				AssertEx(pTile,"");
				pTile->SerializeToDB(rData.m_pData[nDataIndex]);
				
				nDataIndex++;

			}
			m_lstSaveTile.clear();
			AssertEx(nDataIndex == nTileCount,"");
		}
	__LEAVE_FUNCTION
}

void WorldMapService::Openup(void)
{
	__ENTER_FUNCTION
		DBReqLoadTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBReqLoadTileDataMsg);
		AssertEx(MsgPtr,"");
		SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);
	__LEAVE_FUNCTION
}
void WorldMapService::Shutdown(void)
{
	__ENTER_FUNCTION
		DBReqSaveTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBReqSaveTileDataMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_DataPtr = DBTileDataPtr(new DBTileData);
		AssertEx(MsgPtr->m_DataPtr,"");
		Save(*(MsgPtr->m_DataPtr));
		SendMessage2Srv(ServiceID::DBAGEMT,MsgPtr);
		ShutdownOk();
	__LEAVE_FUNCTION
}

TileInfo* WorldMapService::GetTileInfo(int tileId)
{
	__ENTER_FUNCTION
		if (tileId<=0)
		{
			return null_ptr;
		}
		TileMap::iterator it = m_TileList.find(tileId);
		if (it != m_TileList.end())
		{
			return &((*it).second);
		}
	__LEAVE_FUNCTION
		return null_ptr;
}

void WorldMapService::HandleMessage(const DBRetLoadTileDataMsg &rMsg)
{
	__ENTER_FUNCTION
		AssertEx(rMsg.m_nResult == DBMsgResult::RESULT_SUCESS,"");
	    AssertEx(rMsg.m_DataPtr,"");

		Load(*rMsg.m_DataPtr);
		OpenupOk();
	__LEAVE_FUNCTION
}