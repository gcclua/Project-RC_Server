#include "DBCreateCityTask.h"
#include "../ODBCData/ODBCCreateCity.h"
#include "Message/DBMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "DBStruct/DBStruct.h"

POOLDEF_IMPL(DBCreateCityTask);

DBCreateCityTask::DBCreateCityTask( void )
{
	__ENTER_FUNCTION

	m_Data.CleanUp();
	__LEAVE_FUNCTION
}

DBCreateCityTask::~DBCreateCityTask( void )
{

}
void DBCreateCityTask::SetData( const DBCityCreate& rSour )
{
	__ENTER_FUNCTION

		m_Data.CopyFrom(rSour);

	__LEAVE_FUNCTION
} 

void DBCreateCityTask::DataCleanUp()
{
	__ENTER_FUNCTION

		m_Data.CleanUp();

	__LEAVE_FUNCTION
}	

bool DBCreateCityTask::Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
		CacheLog(LOGDEF_INST(CreateChar),"DBCreateCityTask:: start  \1 userId=%d,\2 cityid=%d,\3 time=%d",m_Data.m_UserId,m_Data.m_nCityID,gTimeManager.GetANSITime());
	DBRetCreateCityMsgPtr MsgPtr = POOLDEF_NEW(DBRetCreateCityMsg);
	AssertEx(MsgPtr, "");
	MsgPtr->m_Result = DBMsgResult::RESULT_FAIL;
	MsgPtr->m_nPlayerID = m_nPlayerID;
	tint32 RetVal = DBMsgResult::RESULT_FAIL;

	ODBCCreateCity createCity(&rODBCInterface);
    tint32 beforeSaveTime=gTimeManager.SysRunTime();
	if(false==createCity.Save(&m_Data))
	{ 	
		SendMessage2Srv(GetRetServiceID(), MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);
		return false;
	}
	CacheLog( LOGDEF_INST(DBAgent), "[CreateTask]:user real save end.\1 cityId=%lld \1 guid=%lld \1 tileId=%d \1 time=%d",\
		m_Data.m_nCityID,GetUserGuid(),\
		m_Data.m_tileID,gTimeManager.SysRunTime()-beforeSaveTime);
		
	bool RetAddNew = createCity.ParseResult(&RetVal);
	if(!RetAddNew)
	{
		//MsgPtr->m_Result = RetVal;
		//SendMessage2Srv(GetRetServiceID(), MsgPtr);

		//CacheLog( LOGDEF_INST(DBAgentError), "[CreateTask]:user create error.\1 reason=%d \1 cityId=%lld \1 guid=%lld \1 tileId=%d \1 time=%d",\
			//m_Data.m_nCityID,GetUserGuid(),\
			//m_Data.m_tileID,gTimeManager.SysRunTime()-beforeSaveTime);

		//return false;
	}
	
	
	//返回数据 发送DBRetCreateCharMsg
	MsgPtr->m_Result = DBMsgResult::RESULT_SUCCESS;
	MsgPtr->m_Data.CopyFrom(m_Data);
	SendMessage2Srv(ServiceID::LOGIN, MsgPtr);

	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);

	CacheLog(LOGDEF_INST(CreateChar),"DBCreateCityTask:: end  \1 userId=%d,\2 cityid=%d,\3 time=%d",m_Data.m_UserId,m_Data.m_nCityID,gTimeManager.GetANSITime());
	return true;
	__LEAVE_FUNCTION
	return false;
}

