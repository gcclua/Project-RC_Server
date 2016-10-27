#include "DBWorldMapTask.h"
#include "Clock.h"
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
	MsgPtr->m_nResult  = DBMsgResult::RESULT_FALL;
	
	MsgPtr->m_DataPtr = DBTileDataPtr(new DBTileData());
	AssertEx(MsgPtr->m_DataPtr,"");
	ODBCTileData TileObject(&rODBCInterface);


	int beofreLoadTime = (int)Clock::getCurrentSystemTime();
	if (false == TileObject.Load())
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);
		return false;
	}

	CACHE_LOG("DBAgent","[DBTileDataTask]:real load end \1 time ="<<Clock::getCurrentSystemTime()-beofreLoadTime);
	int resultCount = TileObject.GetResultCount();
	if (resultCount <= 0)
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);
		return false;
	}
	
	MsgPtr->m_DataPtr->InitDataArray(resultCount);
	TileObject.ParseResult(&MsgPtr->m_DataPtr);

	MsgPtr->m_nResult = DBMsgResult::RESULT_SUCESS;

	SendMessage2Srv(GetRetServiceID(),MsgPtr);
	SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);

	return true;
	__LEAVE_FUNCTION
		return false;
}

bool DBWorldMapTask::Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	DBRetSaveTileDataMsgPtr MsgPtr = POOLDEF_NEW(DBRetSaveTileDataMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nResult        = DBMsgResult::RESULT_FALL;
	
	AssertEx(m_DataPtr,"DBTileDataTask::m_DataPtr");

	ODBCTileData TileObject(&rODBCInterface);

	int beforeTime = (int)Clock::getCurrentSystemTime();
	if (false == TileObject.Save(&m_DataPtr))
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_FALL);
		return false;
	}

	CACHE_LOG("DBAgent","[DBTileDataTask]:real save end \1 time ="<<Clock::getCurrentSystemTime()-beforeTime);

	MsgPtr->m_nResult = DBMsgResult::RESULT_SUCESS;

	SendMessage2Srv(GetRetServiceID(),MsgPtr);
	SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);
	
	return true;

	__LEAVE_FUNCTION
		return false;
}



