#include "DBGuidTask.h"
#include "Message/DBMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "DBStruct/DBStruct.h"
#include "../ODBCData/ODBCGuid.h"

POOLDEF_IMPL(DBGuidTask);


void DBGuidTask::SetData(const DBGuidData& val)
{
	m_GuidData.CopyFrom(val);
}
bool DBGuidTask::Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION

	ODBCGuid GuidObj(&rODBCInterface);
	if(false==GuidObj.Save(&m_GuidData))
	{ 
		CacheLog(LOGDEF_INST(Guid), "guid dbsave saveserial fail type(%u),serial(%u)",
			static_cast<tuint32>(m_GuidData.m_Type),
			static_cast<tuint32>(m_GuidData.m_Serial));

		//给DB服务发送处理结束的消息
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);

		return false;
	}
	CacheLog(LOGDEF_INST(Guid), "guid dbsave saveserial sucess type(%u),serial(%u)",
		static_cast<tuint32>(m_GuidData.m_Type),
		static_cast<tuint32>(m_GuidData.m_Serial));
	
	//给DB服务发送处理结束的消息
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);

	return true;
	__LEAVE_FUNCTION
	return false;
}


