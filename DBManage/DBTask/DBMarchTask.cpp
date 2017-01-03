#include "DBMarchTask.h"
#include "Message/DBMsg.h"
#include "../ODBCData/ODBCMarchData.h"
#include "service/MessageOp.h"

POOLDEF_IMPL(DBMarchTask);

DBMarchTask::DBMarchTask(void)
{
	
}

DBMarchTask::~DBMarchTask()
{
	
}

void DBMarchTask::SetData(const DBMarch& val)
{
	__ENTER_FUNCTION
		m_Data.CopyFrom(val);
	__LEAVE_FUNCTION
}

bool DBMarchTask::Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	ODBCMarchData MarchObj(&rODBCInterface);
	if(false==MarchObj.Save(&m_Data))
	{ 
		CacheLog(LOGDEF_INST(Guid), "guid dbsave saveserial fail guid(%lld)",
			m_Data.m_nMarchId);

		//给DB服务发送处理结束的消息
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);

		return false;
	}
	CacheLog(LOGDEF_INST(Guid), "guid dbsave saveserial fail guid(%lld)",m_Data.m_nMarchId);

	//给DB服务发送处理结束的消息
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);


	return true;
	__LEAVE_FUNCTION
		return false;
}




