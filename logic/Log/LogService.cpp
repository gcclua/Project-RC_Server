#include "LogService.h"
#include "Config.h"


LogService::LogService( void )
{

}

LogService::~LogService( void )
{

}

tint32 LogService::GetServiceID( void )
{
    return ServiceID::LOG;
}

void LogService::Init( void )
{
    __ENTER_FUNCTION

    InvokerPtr ptr(new LogInvoker(*this, "LogInvoker"));
    AddInvoker(ptr);

    __LEAVE_FUNCTION
}

tint32 LogService::GetRunState(void)
{
    return GetRunState_Base();
}

void LogService::Tick( const TimeInfo &rTimeInfo )
{
    __ENTER_FUNCTION

    Service::Tick(rTimeInfo);

    if (rTimeInfo.m_bDiffHour)
    {
        RebuildAll();
    }

    FlushAll();

    __LEAVE_FUNCTION
}

void LogService::FlushAll( void )
{
    __ENTER_FUNCTION

    //普通日志
    LOGDEF_FLUSH(ServerStatus);
    LOGDEF_FLUSH(Login);
    LOGDEF_FLUSH(Warning);
    LOGDEF_FLUSH(Error);
    LOGDEF_FLUSH(DBAgentError);
    LOGDEF_FLUSH(DBAgent);
    LOGDEF_FLUSH(SystemShop);
    LOGDEF_FLUSH(TitleInvestitive);
    LOGDEF_FLUSH(Lua);
    LOGDEF_FLUSH(UserConsume);
    LOGDEF_FLUSH(Mission);
    LOGDEF_FLUSH(Chat);
    LOGDEF_FLUSH(GMCommand);
    LOGDEF_FLUSH(Fellow);
    LOGDEF_FLUSH(Pool);
    LOGDEF_FLUSH(Packet);
    LOGDEF_FLUSH(Scene);
	LOGDEF_FLUSH(Player);
	LOGDEF_FLUSH(CopyScene);
	

    //统计日志
    LOGDEF_FLUSH(Audit_Item);
	LOGDEF_FLUSH(Audit_CopyScene);

    //CMBI日志
    LOGDEF_FLUSH(login);
    LOGDEF_FLUSH(rolebuild);
    LOGDEF_FLUSH(rolelogin);
    LOGDEF_FLUSH(newstages);
    LOGDEF_FLUSH(logout);
    __LEAVE_FUNCTION
}

void LogService::RebuildAll( void )
{
    __ENTER_FUNCTION

        //普通日志
        LOGDEF_REBUILDPATH(ServerStatus);
        LOGDEF_REBUILDPATH(Login);
        LOGDEF_REBUILDPATH(Warning);
        LOGDEF_REBUILDPATH(Error);
        LOGDEF_REBUILDPATH(DBAgentError);
        LOGDEF_REBUILDPATH(DBAgent);
        LOGDEF_REBUILDPATH(SystemShop);
        LOGDEF_REBUILDPATH(TitleInvestitive);
        LOGDEF_REBUILDPATH(Lua);
        LOGDEF_REBUILDPATH(UserConsume);
        LOGDEF_REBUILDPATH(Mission);
        LOGDEF_REBUILDPATH(Chat);
        LOGDEF_REBUILDPATH(GMCommand);
        LOGDEF_REBUILDPATH(Fellow);
        LOGDEF_REBUILDPATH(Pool);
        LOGDEF_REBUILDPATH(Packet);
        LOGDEF_REBUILDPATH(Scene);
		LOGDEF_REBUILDPATH(Player);
		LOGDEF_REBUILDPATH(CopyScene);

        //统计日志
        LOGDEF_REBUILDPATH(Audit_Item);
		LOGDEF_REBUILDPATH(Audit_CopyScene);
		

        //CMBI日志
        LOGDEF_REBUILDPATH(login);
        LOGDEF_REBUILDPATH(rolebuild);
        LOGDEF_REBUILDPATH(rolelogin);
        LOGDEF_REBUILDPATH(newstages);
        LOGDEF_REBUILDPATH(logout);
    __LEAVE_FUNCTION
}
