#include "DBTroopTrainTask.h"
#include "Message/DBMsg.h"
#include "../ODBCData/ODBCTroopTrainData.h"
#include "service/MessageOp.h"

POOLDEF_IMPL(DBTroopTrainTask);

DBTroopTrainTask::DBTroopTrainTask(void)
{
	
}

DBTroopTrainTask::~DBTroopTrainTask()
{
	
}

void DBTroopTrainTask::SetData(const DBTroopTrain& val)
{
	__ENTER_FUNCTION
		m_Data.CopyFrom(val);
	__LEAVE_FUNCTION
}

bool DBTroopTrainTask::Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	ODBCTroopTrainData TroopTrainObj(&rODBCInterface);
	if(false==TroopTrainObj.Save(&m_Data))
	{ 
		CacheLog(LOGDEF_INST(Guid), "guid dbsave saveserial fail guid(%lld)",
			m_Data.m_ID);

		//给DB服务发送处理结束的消息
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);

		return false;
	}
	CacheLog(LOGDEF_INST(Guid), "guid dbsave saveserial fail guid(%lld)",m_Data.m_ID);

	//给DB服务发送处理结束的消息
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);


	return true;
	__LEAVE_FUNCTION
		return false;
}




