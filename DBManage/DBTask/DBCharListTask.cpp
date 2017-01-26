#include "DBCharListTask.h"
#include "../ODBCData//ODBCCharList.h"
#include "Message/DBMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "DBStruct/DBStruct.h"

POOLDEF_IMPL(DBCharListTask);

DBCharListTask::DBCharListTask( void )
{
	__ENTER_FUNCTION

	m_AccName.CleanUp();
	m_CharDataList.CleanUp();
	m_nPlayerID=invalid_id;

	__LEAVE_FUNCTION
}

DBCharListTask::~DBCharListTask( void )
{

}

bool DBCharListTask::Load(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
	ODBCCharList CharDataList(&rODBCInterface);
	if(true == IsForLoad())
	{
		DBRetAskCharListMsgPtr MsgPtr = POOLDEF_NEW(DBRetAskCharListMsg);
		AssertEx(MsgPtr, "");
		MsgPtr->m_Result = DBMsgResult::RESULT_FAIL;
		MsgPtr->m_AccName = m_AccName;
		MsgPtr->m_nPlayerID=m_nPlayerID;

		CharDataList.SetAccName(m_AccName);
			
		tint32 beforeLoadTime = gTimeManager.SysRunTime();
			
		if(false == CharDataList.Load())
		{
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
			CacheLog( LOGDEF_INST(DBAgentError),"[charlist]:load failed \1 m_AccName=%s",m_AccName.GetCText());
			return false;
		}
		CacheLog( LOGDEF_INST(DBAgent),"[charlist]:load end \1 m_AccName=%s \1 %d",m_AccName.GetCText(),gTimeManager.SysRunTime()-beforeLoadTime);

		tint32 resultCount = CharDataList.GetResultCount();
		if(resultCount < 0 )
		{
			SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
			CacheLog( LOGDEF_INST(DBAgentError),"[charlist]:load failed \1 m_AccName=%s \1 resultCount=%d",m_AccName.GetCText(),resultCount);
			return false;
		}

		m_CharDataList.CleanUp();
		CharDataList.ParseResult(&m_CharDataList);	

		MsgPtr->m_Result = DBMsgResult::RESULT_SUCCESS;
		MsgPtr->m_CharDataList.CopyFrom(m_CharDataList);
		SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
		CacheLog( LOGDEF_INST(DBAgent),"[charlist]:load success \1 m_AccName=%s \1 resultCount=%d",m_AccName.GetCText(),resultCount);

	}
	return true;

	__LEAVE_FUNCTION
		return false;
}
void DBCharListTask::SetData( const ACCOUNTNAME& rSour )
{
	__ENTER_FUNCTION

	m_AccName = rSour;

	__LEAVE_FUNCTION
} 
const ACCOUNTNAME& DBCharListTask::GetData() const
{
	__ENTER_FUNCTION

	return m_AccName;

	__LEAVE_FUNCTION
} 
