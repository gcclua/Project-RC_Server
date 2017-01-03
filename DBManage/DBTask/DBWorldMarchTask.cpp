#include "DBWorldMarchTask.h"
#include "Message/DBMsg.h"
#include "../ODBCData/ODBCMapMarchData.h"
#include "service/MessageOp.h"

POOLDEF_IMPL(DBWorldMarchTask);

DBWorldMarchTask::DBWorldMarchTask(void)
{
	
}

DBWorldMarchTask::~DBWorldMarchTask()
{
	
}

bool DBWorldMarchTask::Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	DBRetLoadMapMarchMsgPtr MsgPtr = POOLDEF_NEW(DBRetLoadMapMarchMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nResult  = DBMsgResult::RESULT_FAIL;
	
	MsgPtr->m_DataPtr = DBMarchDataPtr(new DBMarchData());
	AssertEx(MsgPtr->m_DataPtr,"");
	ODBCMapMarchData MapMarchObject(&rODBCInterface);


	tuint32 beofreLoadTime = gTimeManager.SysRunTime();
	if (false == MapMarchObject.Load())
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
		return false;
	}

	CacheLog(LOGDEF_INST(DBAgent), "[DBTileDataTask]:real load end \1 time(%d)",
		gTimeManager.SysRunTime()-beofreLoadTime);
	int resultCount = MapMarchObject.GetResultCount();
	/*if (resultCount <= 0)
	{
		SendMessage2Srv(GetRetServiceID(),MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
		return false;
	}*/
	
	if (resultCount>0)
	{
		MsgPtr->m_DataPtr->InitDataArray(resultCount);
		MapMarchObject.ParseResult(&MsgPtr->m_DataPtr);
	}
	
	MsgPtr->m_nResult = DBMsgResult::RESULT_SUCCESS;

	SendMessage2Srv(GetRetServiceID(),MsgPtr);
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);

	return true;
	__LEAVE_FUNCTION
		return false;
}




