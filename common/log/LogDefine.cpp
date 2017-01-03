#include "Base.h"
#include "LogDefine.h"

#include "Config.h"

//普通日志
LOGDEF_IMPL(ServerStatus, LogFormatType::NORMAL);
LOGDEF_IMPL(Login, LogFormatType::NORMAL);
LOGDEF_IMPL(Warning, LogFormatType::NORMAL);
LOGDEF_IMPL(Error, LogFormatType::NORMAL); 
LOGDEF_IMPL(DBAgentError, LogFormatType::NORMAL);
LOGDEF_IMPL(DBAgent, LogFormatType::NORMAL);
LOGDEF_IMPL(SystemShop, LogFormatType::NORMAL);
LOGDEF_IMPL(TitleInvestitive, LogFormatType::NORMAL);
LOGDEF_IMPL(Lua, LogFormatType::NORMAL);
LOGDEF_IMPL(UserConsume, LogFormatType::NORMAL);
LOGDEF_IMPL(Mission, LogFormatType::NORMAL);
LOGDEF_IMPL(Chat, LogFormatType::NORMAL);
LOGDEF_IMPL(GMCommand, LogFormatType::NORMAL);
LOGDEF_IMPL(Fellow, LogFormatType::NORMAL);
LOGDEF_IMPL(Pool, LogFormatType::NORMAL);
LOGDEF_IMPL(Packet, LogFormatType::NORMAL);
LOGDEF_IMPL(Scene, LogFormatType::NORMAL);
LOGDEF_IMPL(Player, LogFormatType::NORMAL);
LOGDEF_IMPL(CopyScene, LogFormatType::NORMAL);
LOGDEF_IMPL(Efficiency, LogFormatType::NORMAL);
LOGDEF_IMPL(Guid,LogFormatType::NORMAL);

//统计日志
LOGDEF_IMPL(Audit_Item, LogFormatType::AUDIT);
LOGDEF_IMPL(Audit_CopyScene, LogFormatType::AUDIT);
LOGDEF_IMPL(Audit_Role, LogFormatType::AUDIT);

//CMBI日志
LOGDEF_IMPL(login, LogFormatType::CMBI);
LOGDEF_IMPL(rolebuild, LogFormatType::CMBI);
LOGDEF_IMPL(rolelogin, LogFormatType::CMBI);
LOGDEF_IMPL(newstages, LogFormatType::CMBI);
LOGDEF_IMPL(logout, LogFormatType::CMBI);

void InitLogDefineModule( tint32 nWorldID )
{
	__ENTER_FUNCTION

	//普通日志
	LOGDEF_INIT(ServerStatus, nWorldID);
	LOGDEF_INIT(Login, nWorldID);
	LOGDEF_INIT(Warning, nWorldID);
	LOGDEF_INIT(Error, nWorldID);
	LOGDEF_INIT(DBAgentError, nWorldID);
	LOGDEF_INIT(DBAgent, nWorldID);
	LOGDEF_INIT(SystemShop, nWorldID);
	LOGDEF_INIT(TitleInvestitive, nWorldID);
	LOGDEF_INIT(Lua, nWorldID);
	LOGDEF_INIT(UserConsume, nWorldID);
	LOGDEF_INIT(Mission, nWorldID);
	LOGDEF_INIT(Chat, nWorldID);
	LOGDEF_INIT(GMCommand, nWorldID);
	LOGDEF_INIT(Fellow, nWorldID);
	LOGDEF_INIT(Pool, nWorldID);
	LOGDEF_INIT(Packet, nWorldID);
	LOGDEF_INIT(Scene, nWorldID);
	LOGDEF_INIT(Player, nWorldID);
	LOGDEF_INIT(CopyScene, nWorldID);
	LOGDEF_INIT(Efficiency, nWorldID);
	LOGDEF_INIT(Guid,nWorldID);

	//统计日志
	LOGDEF_INIT(Audit_Item, nWorldID);
	LOGDEF_INIT(Audit_CopyScene, nWorldID);
	LOGDEF_INIT(Audit_Role, nWorldID);

	//CMBI日志
	LOGDEF_INIT(login, nWorldID);
	LOGDEF_INIT(rolebuild, nWorldID);
	LOGDEF_INIT(rolelogin, nWorldID);
	LOGDEF_INIT(newstages, nWorldID);
	LOGDEF_INIT(logout, nWorldID);
	__LEAVE_FUNCTION
}

