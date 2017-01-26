#include "WorldMapService.h"
#include "DBStruct/DBStruct.h"
#include "service/MessageOp.h"
#include "Message/DBMsg.h"
#include "Message/LoginMsg.h"

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
				SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);
			}
		}
	__LEAVE_FUNCTION
}

void WorldMapService::LoadTile(const DBTileData& rData)
{
	__ENTER_FUNCTION
		if (rData.m_pData == null_ptr)
		{
			return;
		}

		AssertEx(rData.m_Count < MAX_TILE_NUM,"");
		for (int i = 0; i< rData.m_Count; i++)
		{
			TileInfoPtr tempTile = TileInfoPtr(new TileInfo());
			tempTile->SerializeFromDB(rData.m_pData[i]);
			m_TileList.insert(std::make_pair(tempTile->GetID(),tempTile));

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
				TileInfoPtr pTile = (*it).second;
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
		//OpenupOk();
		DBReqLoadTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBReqLoadTileDataMsg);
		AssertEx(MsgPtr,"");
		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);

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
		SendMessage2Srv(ServiceID::DBAGENT,MsgPtr);
		ShutdownOk();
	__LEAVE_FUNCTION
}

void WorldMapService::PushSaveList(TileInfoPtr Ptr)
{
	__ENTER_FUNCTION
		bool bFind = false;
		for (SaveTileList::iterator it = m_lstSaveTile.begin(); it != m_lstSaveTile.end();it++)
		{
			int nTileId = it->first;
			if (nTileId == Ptr->GetID())
			{
				it->second = Ptr;
				bFind = true;
				break;
			}
		}
		if (!bFind)
		{
			m_lstSaveTile.insert(std::make_pair(Ptr->GetID(),Ptr));
		}
	__LEAVE_FUNCTION
}

TileInfoPtr WorldMapService::GetPlainTile()
{
	__ENTER_FUNCTION
		for (TileMap::iterator it = m_TileList.begin();it != m_TileList.end();it++)
		{
			TileInfoPtr pTileInfo = it->second;
			if ( pTileInfo->GetState() ==  TILE_STATE_IDLE)
			{
				pTileInfo->SetState(TILE_STATE_TAKE);
				PushSaveList(pTileInfo);
				return pTileInfo;
			}
		}
		return null_ptr;
	__LEAVE_FUNCTION
	return null_ptr;
}

TileInfoPtr WorldMapService::GetTileInfo(int tileId)
{
	__ENTER_FUNCTION
		if (tileId<=0)
		{
			return null_ptr;
		}
		TileMap::iterator it = m_TileList.find(tileId);
		if (it != m_TileList.end())
		{
			return ((*it).second);
		}
	__LEAVE_FUNCTION
		return null_ptr;
}

void WorldMapService::HandleMessage(const ReqSetTileOwerMsg &rMsg)
{
	__ENTER_FUNCTION
		int tileId = rMsg.m_tileId;
	TileMap::iterator it = m_TileList.find(tileId);
	if (it != m_TileList.end())
	{
		TileInfoPtr Ptr = it->second;
		Ptr->SetUserId(rMsg.m_userId);
		Ptr->SetState(TILE_STATE_TAKE);
	}
	__LEAVE_FUNCTION
}

void WorldMapService::HandleMessage(const DBRetLoadTileDataMsg &rMsg)
{
	__ENTER_FUNCTION
		AssertEx(rMsg.m_nResult == DBMsgResult::RESULT_SUCCESS,"");
	    AssertEx(rMsg.m_DataPtr,"");

		LoadTile(*rMsg.m_DataPtr);
		OpenupOk();
	__LEAVE_FUNCTION
}

void WorldMapService::HandleMessage(const ReqIdleTileMsg &rMsg)
{
	__ENTER_FUNCTION
		RetIdleTileMsgPtr MsgPtr = POOLDEF_NEW(RetIdleTileMsg);
		CacheLog(LOGDEF_INST(CreateChar),"ReqIdleTileMsg:: start \1 playerid=%d, \2 userId=%d,\3 time=%d",rMsg.m_nPlayerID,rMsg.m_userId,gTimeManager.GetANSITime());
		TileInfoPtr Ptr = GetPlainTile();
		int tileId = INVALID_ID;
		int nX = INVALID_ID;
		int nY = INVALID_ID;
		if (null_ptr != Ptr)
		{
			tileId = Ptr->GetID();
			nX     = Ptr->GetPosX();
			nY     = Ptr->GetPosY();
		}
		MsgPtr->m_tileId = tileId;
		MsgPtr->m_posX   = nX;
		MsgPtr->m_posY   = nY;
		MsgPtr->m_userId = rMsg.m_userId;
		MsgPtr->m_nPlayerID = rMsg.m_nPlayerID;

		SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
			CacheLog(LOGDEF_INST(CreateChar),"ReqIdleTileMsg:: start \1 playerid=%d, \2 userId=%d,\3 tileid =%d , \4 time=%d",rMsg.m_nPlayerID,rMsg.m_userId,tileId,gTimeManager.GetANSITime());
	__LEAVE_FUNCTION
}