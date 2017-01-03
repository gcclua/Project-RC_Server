#include "DBServiceExec.h"
#include "../DBManage/DBTask/DBBaseTask.h"
#include "service/ServiceManager.h"
#include "Message/DBMsg.h"
#include "ServerConfig.h"

extern ServerConfig serverConfig;
DBServiceExec::DBServiceExec(int index)
{
	m_MyIndex = index; 
}

DBServiceExec::~DBServiceExec(void)
{

}

int DBServiceExec::GetRunState(void)
{
	switch (gServiceManager.GetStatus())
	{
	case ServiceManagerStatus::EMPTY:
		{
			AssertEx(false,"");
			return BaseService::RUNSTATE_PAUSE;
		}
		break;
	case ServiceManagerStatus::OPENUP:
	case ServiceManagerStatus::RUNNING:
	case ServiceManagerStatus::SHUTDOWN:
	case ServiceManagerStatus::FINALSAVE:
		{
			if (m_ODBCInterface.IsConnected())
			{
				return (IsHaveUnHandleMessage()?BaseService::RUNSTATE_NORMAL : BaseService::RUNSTATE_SLOWLY);
			}
			else
			{
				return BaseService::RUNSTATE_SLOWLY;
			}
		}
		break;
	default:
		{
			AssertEx(false,"");
			return BaseService::RUNSTATE_PAUSE;
		}
		break;
	}
}

InvokerPtr DBServiceExec::InitMyself( void )
{
	__ENTER_FUNCTION

	ODBCInterfaceInit();

	//LibMemInterfaceInit();


	tchar szInvokerName[64] = {0};
	tsnprintfex(szInvokerName, sizeof(szInvokerName), "DBServiceExecInvoker(%d)", m_MyIndex);
	InvokerPtr ptr(new DBServiceExecInvoker(*this,szInvokerName));
	return ptr;
	__LEAVE_FUNCTION
		InvokerPtr retPtr;
	return retPtr;
}

void DBServiceExec::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (!m_ODBCInterface.IsConnected())
		{
			bool bConnRet = m_ODBCInterface.Connect();
			if (!bConnRet)
			{
				return;
			}
			
		}
		ServiceCell::Tick(rTimeInfo);

	__LEAVE_FUNCTION
}

void DBServiceExec::HandleMessage(const DBAssignTaskMsg &rMsg)
{
	__ENTER_FUNCTION
		DBBaseTaskPtr ptr = rMsg.m_DBBaseTaskPtr;
	    AssertEx(ptr,"");
		ptr->Execute(m_ODBCInterface,m_LibMemInterface);
	__LEAVE_FUNCTION
}

void DBServiceExec::HandleMessage(const DBCheckConnectMsg &rMsg)
{

}

bool DBServiceExec::ODBCInterfaceInit()
{
	__ENTER_FUNCTION
		// 从config中读取DB相关的数据
		// 数据源名称
		char szDatabase[DATABASE_STR_LEN];
	    strncpy(szDatabase,serverConfig.dbGamedName(1).c_str(),DATABASE_STR_LEN);
	    szDatabase[DATABASE_STR_LEN-1] = '\0';

		// 用户名
		char szUser[DB_USE_STR_LEN] = {0};
		strncpy(szUser,serverConfig.dbGamedUser(1).c_str(),DB_USE_STR_LEN);
		szUser[DB_USE_STR_LEN-1] = '\0';

		// 密码
		char szPassword[DB_PASSWORD_STR_LEN] = {0};
		strncpy(szPassword,serverConfig.dbGamedPassword(1).c_str(),DB_PASSWORD_STR_LEN);
		szUser[DB_USE_STR_LEN-1] = '\0';

		m_ODBCInterface.Connect(szDatabase,szUser,szPassword);

		return m_ODBCInterface.IsConnected();



	__LEAVE_FUNCTION
		return false;
}

bool DBServiceExec::LibMemInterfaceInit()
{
	__ENTER_FUNCTION
		char ServerList[DB_MEM_SERVERLIST_LEN];
	    strncpy(ServerList,serverConfig.getMemCache(1).c_str(),DB_MEM_SERVERLIST_LEN);
		ServerList[DB_MEM_SERVERLIST_LEN-1] = '\0';
		return m_LibMemInterface.Init(ServerList);
	__LEAVE_FUNCTION
		return false;
}