#include "DBRandomNameTask.h"
#include "Message/DBMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "DBStruct/DBStruct.h"
#include "../ODBCData/ODBCRandomName.h"

POOLDEF_IMPL(DBRandomNameTask);

DBRandomNameTask::DBRandomNameTask( void )
{
	__ENTER_FUNCTION

	__LEAVE_FUNCTION
}

DBRandomNameTask::~DBRandomNameTask( void )
{
}

bool DBRandomNameTask::Load(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	DBRetReqLoadRandomNameMsgPtr MsgPtr = POOLDEF_NEW(DBRetReqLoadRandomNameMsg);
    AssertEx(MsgPtr,"");
	MsgPtr->m_Result = DBMsgResult::RESULT_FAIL;
	
	ODBCRandomName odbcObject(&rODBCInterface);
	tint32 beforeLoadTime = gTimeManager.SysRunTime();
	
	if(false==odbcObject.Load())
	{ 	
		SendMessage2Srv(GetRetServiceID(), MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL); //数据没有加载成功交给上层逻辑处理，DBService将该加载任务认为处理完毕
		return false;
	}

	CacheLog( LOGDEF_INST(DBAgent), "[DBRandomNameTask]:real load end \1 time=%d",gTimeManager.SysRunTime()-beforeLoadTime);

	tint32 resultCount = odbcObject.GetResultCount();
	if (resultCount < 0)
	{
		SendMessage2Srv(GetRetServiceID(), MsgPtr);	
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);
		return false;
	}
	else if(resultCount == 0)	
	{
		MsgPtr->m_Result = DBMsgResult::RESULT_SUCCESS;
		SendMessage2Srv(GetRetServiceID(), MsgPtr);	
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);
		return true;
	} 

	odbcObject.ParseResult(&MsgPtr->m_Data);		

	MsgPtr->m_Result = DBMsgResult::RESULT_SUCCESS;
	SendMessage2Srv(GetRetServiceID(), MsgPtr);
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
	return true;
	
	__LEAVE_FUNCTION
	return false;
}
