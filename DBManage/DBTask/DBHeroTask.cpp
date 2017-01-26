#include "DBHeroTask.h"
#include "Message/DBMsg.h"
#include "Service/Service.h"
#include "Service/MessageOp.h"
#include "DBStruct/DBStruct.h"
#include "../ODBCData/ODBCHeroData.h"

POOLDEF_IMPL(DBHeroTask);


void DBHeroTask::SetData(const DBHero& val)
{
	m_Hero.CopyFrom(val);
}
bool DBHeroTask::Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION

	ODBCHeroData HeroObj(&rODBCInterface);
	if(false==HeroObj.Save(&m_Hero))
	{ 
		CacheLog(LOGDEF_INST(HeroData), "hero dbsave save herodata fail heroid(%lld),time(%d)",m_Hero.m_nHeroId,gTimeManager.SysRunTime());

		//给DB服务发送处理结束的消息
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);

		return false;
	}
	CacheLog(LOGDEF_INST(HeroData), "hero dbsave save herodata fail heroid(%lld),time(%d)",m_Hero.m_nHeroId,gTimeManager.SysRunTime());
	
	//给DB服务发送处理结束的消息
	SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);

	return true;
	__LEAVE_FUNCTION
	return false;
}


