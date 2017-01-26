#include "DBUserTask.h"
#include "service/MessageOp.h"
#include "Exception.h"
#include "../ODBCData/ODBCCharFullData.h"

POOLDEF_IMPL(DBUserTask);

DBUserTask::DBUserTask(void)
{
	m_UserData.CleanUp();
}

DBUserTask::~DBUserTask()
{
	
}

bool DBUserTask::Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	DBRetLoadUserMsgPtr MsgPtr = POOLDEF_NEW(DBRetLoadUserMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nResult  = DBMsgResult::RESULT_FAIL;
	MsgPtr->m_AccountName = m_AccountName;
	MsgPtr->m_nPlayerID = m_nPlayerID;
	__ENTER_PROTECT_EX
	{
		CacheLog(LOGDEF_INST(CreateChar),"DBUserTask:: start  \1 userId=%d,\2 account =%s,\3 time=%d",m_UserGuid,m_AccountName,gTimeManager.GetANSITime());
		if (IsForLoad())
		{
			// 从memcached加载
			bool memLoadRet = MemLoad(rLibMemInterface);

			// memcached中没有去数据库加载
			bool dbLoadRet = false;
			if (false == memLoadRet)
			{
				dbLoadRet = DBLoad(rODBCInterface);
			}

			if (!memLoadRet && !dbLoadRet)
			{
				CacheLog( LOGDEF_INST(DBAgentError), "[UserDataError]:User Load Failed \1 guid=%08X",\
					m_UserGuid);

				MsgPtr->m_nResult = DBMsgResult::RESULT_FAIL;
				SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
				SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);//数据没有加载成功交给上层逻辑处理，DBService将加载任务认为处理完毕
				return false;
			}
			
			// 返回数据
			MsgPtr->m_nResult = DBMsgResult::RESULT_SUCCESS;
			MsgPtr->m_UserData.CopyFrom(m_UserData);
			SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
			CacheLog(LOGDEF_INST(CreateChar),"DBUserTask:: end  \1 userId=%d,\2 account =%s,\3 time=%d",m_UserGuid,m_AccountName,gTimeManager.GetANSITime());

			//返回结果
			SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
			return true;
		}
		
	}
	__CATCH_PROTECT_EX
	{
		CacheLog( LOGDEF_INST(DBAgentError), "[UserDataError]:User Load Exception \1 guid=%08X",m_UserGuid);
		// 通知失败
		MsgPtr->m_nResult = DBMsgResult::RESULT_FAIL;
		SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);//数据没有加载成功交给上层逻辑处理，DBService将加载任务认为处理完毕
		return false;
	}
	return true;
	
	__LEAVE_PROTECT_EX
		return false;
}

bool DBUserTask::Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface)
{
	
	DBRetSaveUserMsgPtr MsgPtr = POOLDEF_NEW(DBRetSaveUserMsg);
	AssertEx(MsgPtr,"");
	MsgPtr->m_nResult        = DBMsgResult::RESULT_FAIL;
	MsgPtr->m_UserGuid       = m_UserGuid;
	MsgPtr->m_bImmediateSave = m_bImmediateSave;
	MsgPtr->m_bFinalSave     = m_bFinalSave;

	__ENTER_PROTECT_EX
	{
		
		if (true == IsForSave())
		{
			// 数据存储到memcache
			bool memSaveRet = MemSave(rLibMemInterface);
			if (DBBaseTask::OPERATION_TYPE_SAVE_MEM == GetOperationType())
			{
				SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
				return true;
			}
			// 数据存储到数据库中
			bool dbSaveRet = DBSave(rODBCInterface);
			if (dbSaveRet)
			{
				MsgPtr->m_nResult = DBMsgResult::RESULT_SUCCESS;
				SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
				SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_SUCCESS);
			}
			else
			{
				MsgPtr->m_nResult = DBMsgResult::RESULT_FAIL;
				SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
				SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);
			}
		}
	}
	__CATCH_PROTECT_EX
	{
		CacheLog(LOGDEF_INST(DBAgentError),"[UserDataError]:User Save Exception \1 guid=%08X",m_UserGuid);
		// 通知失败
		MsgPtr->m_nResult = DBMsgResult::RESULT_FAIL;
		SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
		SendOpResult(ServiceID::DBAGENT,DBMsgResult::RESULT_FAIL);
		return false;
	}
	
	return true;
	
	__LEAVE_PROTECT_EX
		return false;
}

bool DBUserTask::DBLoad(ODBCInterface &rODBCInterface)
{
	__ENTER_FUNCTION
		tint32 beforeLoadTime = gTimeManager.SysRunTime();
	
		ODBCCharFullData userData(&rODBCInterface);
		if (true == IsForLoad())
		{
			userData.SetCharGuid(m_UserGuid);
			if (false == userData.Load())
			{
				CacheLog( LOGDEF_INST(DBAgentError), "[UserData]:Real Load user Error \1 guid=%08X \1 m_AccName=%s", \
					m_UserGuid,m_AccountName);
				return false;
			}

			uint32 resultCount = userData.GetResultCount();
			if (resultCount <= 0)
			{
				CacheLog( LOGDEF_INST(DBAgentError), "[UserData]:Real Load user Result Error \1 guid=%08X \1 m_AccName=%s", \
					m_UserGuid,m_AccountName);
				return false;
			}
			m_UserData.CleanUp();
			userData.ParseResult(&m_UserData);

			uint32 CRCValue = m_UserData.CalcCRC();
			if (CRCValue != userData.GetCRCValue() && 0 != userData.GetCRCValue())
			{


			}
		}
		
		return true;
	
		__LEAVE_FUNCTION

		return false;

}
bool DBUserTask::DBSave(ODBCInterface &rODBCInterface)
{
	__ENTER_FUNCTION
		//存盘操作
		ODBCCharFullData userData(&rODBCInterface);
		userData.SetCharGuid(m_UserData.GetGuid());
		if (false == userData.Save(&m_UserData))
		{
			CacheLog( LOGDEF_INST(DBAgentError), "[UserData]:Real Save user Error \1 guid=%08X \1 m_AccName=%s", \
				m_UserGuid,m_AccountName);
			return false;
		}

		return true;
		__LEAVE_FUNCTION

		return false;
}
bool DBUserTask::MemLoad(LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
		char szKey[MAXPATH] = {0};
		tsnprintf(szKey,sizeof(szKey)-1,"%lld",m_UserGuid);
		szKey[sizeof(szKey)-1] = '0';
		size_t retValLen = 0;
		tuint32 beforeTime = gTimeManager.SysRunTime();
		char* szRetVal = rLibMemInterface.Get(szKey,static_cast<uint32>(strlen(szKey)),&retValLen);

		CacheLog( LOGDEF_INST(DBAgent), "[UserData]:User  \1 guid=%lld \1 time=%d \1 Mem Load End.",\
			m_UserGuid,gTimeManager.SysRunTime()-beforeTime);

		MemFullUserData tempMemUserData;
		if (retValLen == sizeof(tempMemUserData))
		{
			memcpy(&tempMemUserData,szRetVal,retValLen);
			if (szRetVal != null_ptr)
			{
				free(szRetVal);
				szRetVal = null_ptr;
			}

			m_UserData.CopyFrom(tempMemUserData.m_UserData);
			return true;
		}
		else
		{
			if (szRetVal != null_ptr)
			{
				free(szRetVal);
				szRetVal = null_ptr;
			}
			return false;
		}
		return false;
		__LEAVE_FUNCTION

		return false;
}
bool DBUserTask::MemSave(LibMemInterface &rLibMemInterface)
{
	__ENTER_FUNCTION
		char szKey[MAXPATH] = {0};
		tsnprintf(szKey,sizeof(szKey)-1,"%lld",m_UserGuid);
		szKey[sizeof(szKey)-1] = '0';
		MemFullUserData tempMemUserData;
		tempMemUserData.m_UserData.CopyFrom(m_UserData);

		tuint32 beforeTime = gTimeManager.SysRunTime();
		bool bSet = rLibMemInterface.Set(szKey,static_cast<uint32>(strlen(szKey)),(char*)(&tempMemUserData),sizeof(tempMemUserData),0);

		CacheLog( LOGDEF_INST(DBAgent), "[UserData]:User  \1 guid=%lld,%lld \1 time=%d \1 Mem Save End.",\
			m_UserGuid,gTimeManager.SysRunTime()-beforeTime);
		if (false == bSet)
		{
			CacheLog( LOGDEF_INST(DBAgentError), "[UserData]:User \1 guid=%lld \1 Mem Save Failed.",m_UserGuid);
			
			if (!rLibMemInterface.Delete(szKey,static_cast<uint32>(strlen(szKey)),0))
			{
				CacheLog( LOGDEF_INST(DBAgentError), "[UserData]:User \1 guid=%lld \1 Mem Delete Failed.",m_UserGuid);
			}
		}
		return true;
	__LEAVE_FUNCTION

		return false;
}

void DBUserTask::SetData(const DBFullUserData& rSour)
{
	__ENTER_FUNCTION
		m_UserData.CopyFrom(rSour);
	__LEAVE_FUNCTION
}

const DBFullUserData& DBUserTask::GetData() const
{
	__ENTER_FUNCTION
		return m_UserData;
	__LEAVE_FUNCTION
}

void DBUserTask::DataCleanUp()
{

	__ENTER_FUNCTION
		m_UserData.CleanUp();
	__LEAVE_FUNCTION

}
