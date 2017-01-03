#include "DBWorldMapTask.h"
#include "Message/DBMsg.h"
#include "../ODBCData/ODBCTileData.h"
#include "service/MessageOp.h"

POOLDEF_IMPL(DBWorldMapTask);

DBWorldMapTask::DBWorldMapTask(void)
{
	
}

DBWorldMapTask::~DBWorldMapTask()
{
	
}

bool DBWorldMapTask::Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	DBRetLoadTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBRetLoadTileDataMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nResult  = DBMsgResult::RESULT_FAIL;
	
	MsgPtr->m_DataPtr = DBTileDataPtr(new DBTileData());
	AssertEx(MsgPtr->m_DataPtr,"");
	ODBCTileData TileObject(&rODBCInterface);


	tuint32 beofreLoadTime = gTimeManager.SysRunTime();
	if (false == TileObject.Load())
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
		return false;
	}

	CacheLog(LOGDEF_INST(DBAgent), "[DBTileDataTask]:real load end \1 time(%d)",
		gTimeManager.SysRunTime()-beofreLoadTime);
	int resultCount = TileObject.GetResultCount();
	if (resultCount <= 0)
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
		return false;
	}
	
	MsgPtr->m_DataPtr->InitDataArray(resultCount);
	TileObject.ParseResult(&MsgPtr->m_DataPtr);

	MsgPtr->m_nResult = DBMsgResult::RESULT_SUCCESS;

	SendMessage2Srv(GetRetServiceID(),MsgPtr);
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);

	return true;
	__LEAVE_FUNCTION
		return false;
}

bool DBWorldMapTask::Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	DBRetSaveTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBRetSaveTileDataMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nResult        = DBMsgResult::RESULT_FAIL;
	
	AssertEx(m_DataPtr,"DBTileDataTask::m_DataPtr");

	ODBCTileData TileObject(&rODBCInterface);

	tuint32 beofreLoadTime = gTimeManager.SysRunTime();
	if (false == TileObject.Save(&m_DataPtr))
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);
		return false;
	}

	CacheLog(LOGDEF_INST(DBAgent), "[DBTileDataTask]:real save end \1 time(%d)",
		gTimeManager.SysRunTime()-beofreLoadTime);

	MsgPtr->m_nResult = DBMsgResult::RESULT_SUCCESS;

	SendMessage2Srv(GetRetServiceID(),MsgPtr);
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
	
	return true;

	__LEAVE_FUNCTION
		return false;
}



