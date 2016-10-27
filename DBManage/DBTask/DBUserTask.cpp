#include "DBUserTask.h"
#include "Clock.h"
#include "SysLog.h"
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
	MsgPtr->m_nResult  = DBMsgResult::RESULT_FALL;
	MsgPtr->m_UserName = m_UserName;
	MsgPtr->m_UserGuid = m_UserGuid;
	__ENTER_PROTECT_EX
	{
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
				CACHE_LOG("DBAgentError","[UserDataErrr]:User Load Failed 1 guid="<< m_UserGuid);

				MsgPtr->m_nResult = DBMsgResult::RESULT_FALL;
				SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
				SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_FALL);//数据没有加载成功交给上层逻辑处理，DBService将加载任务认为处理完毕
				return false;
			}
			
			// 返回数据
			MsgPtr->m_nResult = DBMsgResult::RESULT_SUCESS;
			MsgPtr->m_UserData.CopyFrom(m_UserData);
			SendMessage2Srv(ServiceID::LOGIN,MsgPtr);

			//返回结果
			SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);
			return true;
		}
		
	}
	__CATCH_PROTECT_EX
	{
		CACHE_LOG("DBAgentError","[UserDataError]:User Load Exception \1 guid"<<m_UserGuid);

		// 通知失败
		MsgPtr->m_nResult = DBMsgResult::RESULT_FALL;
		SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
		SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_FALL);//数据没有加载成功交给上层逻辑处理，DBService将加载任务认为处理完毕
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
	MsgPtr->m_nResult        = DBMsgResult::RESULT_FALL;
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
				SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);
				return true;
			}
			// 数据存储到数据库中
			bool dbSaveRet = DBSave(rODBCInterface);
			if (dbSaveRet)
			{
				MsgPtr->m_nResult = DBMsgResult::RESULT_SUCESS;
				SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
				SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_SUCESS);
			}
			else
			{
				MsgPtr->m_nResult = DBMsgResult::RESULT_FALL;
				SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
				SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_FALL);
			}
		}
	}
	__CATCH_PROTECT_EX
	{
		CACHE_LOG("DBAgentError","[UserDataError]:User Load Exception \1 guid"<<m_UserGuid);

		// 通知失败
		MsgPtr->m_nResult = DBMsgResult::RESULT_FALL;
		SendMessage2Srv(ServiceID::LOGIN,MsgPtr);
		SendOpResult(ServiceID::DBAGEMT,DBMsgResult::RESULT_FALL);
		return false;
	}
	return true;
	__LEAVE_PROTECT_EX
		return false;
}

bool DBUserTask::DBLoad(ODBCInterface &rODBCInterface)
{
	__ENTER_FUNCTION
		time_t beforeLoadTime = Clock::getCurrentSystemTime();
	
		ODBCCharFullData userData(&rODBCInterface);
		if (true == IsForLoad())
		{
			userData.SetCharGuid(m_UserGuid);
			if (false == userData.Load())
			{
				CACHE_LOG("DBAgentError","[UserDataError]: Real Load User Error \1 guid="<<m_UserGuid<<" \1 m_AccName="<<m_UserName);

				return false;
			}

			uint32 resultCount = userData.GetResultCount();
			if (resultCount <= 0)
			{
				CACHE_LOG("DBAgentError","[UserDataError]: Real Load User Error \1 guid="<<m_UserGuid<<" \1 m_AccName="<<m_UserName);
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
		if (false == userData.Save(&m_UserData))
		{
			CACHE_LOG("DBAgentError","[UserDataError]: Real Save User Error \1 guid="<<m_UserGuid<<" \1 m_AccName="<<m_UserName);
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
		tsnprintf(szKey,sizeof(szKey)-1,"%x",m_UserGuid);
		szKey[sizeof(szKey)-1] = '0';
		size_t retValLen = 0;
		int beforeTime = (int)Clock::getCurrentSystemTime();
		char* szRetVal = rLibMemInterface.Get(szKey,static_cast<uint32>(strlen(szKey)),&retValLen);
		CACHE_LOG("DBAgent","[UserData]: \1 guid="<<m_UserGuid<<" \1 time="<<Clock::getCurrentSystemTime()-beforeTime<<" Mem Load End.");

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
		tsnprintf(szKey,sizeof(szKey)-1,"%x",m_UserGuid);
		szKey[sizeof(szKey)-1] = '0';
		MemFullUserData tempMemUserData;
		tempMemUserData.m_UserData.CopyFrom(m_UserData);

		int beforeTime = (int)Clock::getCurrentSystemTime();
		bool bSet = rLibMemInterface.Set(szKey,static_cast<uint32>(strlen(szKey)),(char*)(&tempMemUserData),sizeof(tempMemUserData),0);
		CACHE_LOG("DBAgent","[UserData]: User \1 guid="<<m_UserGuid<<" \1 time="<<Clock::getCurrentSystemTime()-beforeTime<<" Mem Save End.");

		if (false == bSet)
		{
			CACHE_LOG("DBAgentError","[UserData]: User \1 guid="<<m_UserData.getGuid()<<" Mem Save Failed.");
			
			if (!rLibMemInterface.Delete(szKey,static_cast<uint32>(strlen(szKey)),0))
			{
				CACHE_LOG("DBAgentError","[UserData]: User \1 guid="<<m_UserData.getGuid()<<" Mem Delete Failed.");
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
