#include "DBCreateCharTask.h"
#include "../ODBCData/ODBCCreateChar.h"
#include "Message/DBMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "DBStruct/DBStruct.h"

POOLDEF_IMPL(DBCreateCharTask);

DBCreateCharTask::DBCreateCharTask( void )
{
	__ENTER_FUNCTION

	m_UserData.CleanUp();
	m_nPlayerID=invalid_id;
	__LEAVE_FUNCTION
}

DBCreateCharTask::~DBCreateCharTask( void )
{

}
void DBCreateCharTask::SetData( const DBFullUserData& rSour )
{
	__ENTER_FUNCTION

		m_UserData.CopyFrom(rSour);

	__LEAVE_FUNCTION
} 
const DBFullUserData& DBCreateCharTask::GetData() const
{
	__ENTER_FUNCTION

		return m_UserData;

	__LEAVE_FUNCTION
} 
void DBCreateCharTask::DataCleanUp()
{
	__ENTER_FUNCTION

		m_UserData.CleanUp();

	__LEAVE_FUNCTION
}	

bool DBCreateCharTask::Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION

	DBRetCreateCharMsgPtr MsgPtr = POOLDEF_NEW(DBRetCreateCharMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_AccName    = m_AccName;
	MsgPtr->m_nPlayerID  = m_nPlayerID;
	MsgPtr->m_Result = DBMsgResult::RESULT_FAIL;
	tint32 RetVal = DBMsgResult::RESULT_FAIL;

	CacheLog(LOGDEF_INST(CreateChar),"DBCreateCharTask:: start \1 playerid=%d, \2 userId=%d,\3 account =%s , \4 time=%d",m_nPlayerID,m_UserData.GetGuid(),m_AccName,gTimeManager.GetANSITime());
	ODBCCreateChar createChar(&rODBCInterface);
    tint32 beforeSaveTime=gTimeManager.SysRunTime();
	if(false==createChar.Save(&m_UserData))
	{ 	
		SendMessage2Srv(GetRetServiceID(), MsgPtr);
		return false;
	}
	CacheLog( LOGDEF_INST(DBAgent), "[CreateTask]:user real save end.\1 name=%s \1 guid=%lld \1 m_AccName=%s \1 time=%d",\
		m_UserData.m_User.m_CharName,m_UserData.GetGuid(),\
		m_UserData.m_User.m_AccName,gTimeManager.SysRunTime()-beforeSaveTime);
		
	bool RetAddNew = createChar.ParseResult(&RetVal);
	if(!RetAddNew)
	{
		MsgPtr->m_Result = RetVal;
		SendMessage2Srv(GetRetServiceID(), MsgPtr);

		CacheLog( LOGDEF_INST(DBAgentError), "[CreateTask]:user create error.\1 reason=%d \1 name=%s \1 guid=%lld\1 m_AccName=%s \1 time=%d",\
			RetVal,m_UserData.m_User.m_CharName,m_UserData.GetGuid(),\
			m_UserData.m_User.m_AccName,gTimeManager.SysRunTime()-beforeSaveTime);

		return false;
	}
	
	
	//返回数据 发送DBRetCreateCharMsg
	MsgPtr->m_Result = DBMsgResult::RESULT_SUCCESS;
	MsgPtr->m_UserData.CopyFrom(m_UserData);
	SendMessage2Srv(ServiceID::LOGIN, MsgPtr);
	CacheLog(LOGDEF_INST(CreateChar),"DBCreateCharTask:: end \1 playerid=%d, \2 userId=%d,\3 account =%s , \4 time=%d",m_nPlayerID,m_UserData.GetGuid(),m_AccName,gTimeManager.GetANSITime());

	return true;
	__LEAVE_FUNCTION
	return false;
}

