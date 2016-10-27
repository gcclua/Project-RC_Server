#include "DBBaseTask.h"
#include "Clock.h"
#include "Message/DBMsg.h"
#include "service/MessageOp.h"

DBBaseTask::DBBaseTask(void)
	:m_OperationType(INVALID_ID),
	m_key(INVALID_ID)
{
	m_ReqOptTime = (int)Clock::getCurrentSystemTime();
}

DBBaseTask::~DBBaseTask()
{
	
}

bool DBBaseTask::Execute(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	bool bResult = false;
	if (IsForLoad())
	{
		Load(rODBCInterface,rLibMemInterface);
	}
	else if (IsForSave())
	{
		Save(rODBCInterface,rLibMemInterface);
	}
	else
	{

	}
	return bResult;
}

void DBBaseTask::SendOpResult(uint32 ServiceId,uint32 retVal) const
{
	if (ServiceId <0 || ServiceId >= ServiceID::MAX)
	{
		return;
	}

	// ·¢ËÍDBOpRetMsg
	DBOpRetMsgPtr MsgPtr = POOLDEF_NEW(DBOpRetMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_Key       = m_key;
	MsgPtr->m_OpRet     = retVal;
	MsgPtr->m_OpType    = GetOperationType();
	MsgPtr->m_TaskType  = GetTaskType();
	MsgPtr->m_ReqOpTime = GetOptTime();
	SendMessage2Srv(ServiceId,MsgPtr);
}
