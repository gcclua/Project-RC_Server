#include "DBService.h"
#include "Message/DBMsg.h"
#include "DBStruct/DBStruct.h"
#include "service/MessageOp.h"
#include "DBTask/DBUserTask.h"
#include "DBTask/DBWorldMapTask.h"
#include "DBTask/DBGuidTask.h"
#include "DBTask/DBCreateCharTask.h"
#include "DBTask/DBCharListTask.h"
#include "DBTask/DBCreateCityTask.h"
#include "DBTask/DBWorldMarchTask.h"
#include "DBTask/DBRandomNameTask.h"
#include "DBTask/DBMarchTask.h"
#include "Config.h"

DBService::DBService(void)
{
	__ENTER_FUNCTION
		m_DBBaseTaskPtrList.clear();
	    for (int i=0;i<DB_TASK_MAX_NUM;i++)
		{
			m_CurProTaskPtrMap[i].clear();
		}
		m_UserDataLstSaveDBTime.clear();
		m_FinalSaveDelayTime = 0;
		m_TaskKeySerial      = 0;
	__LEAVE_FUNCTION
}

DBService::~DBService(void)
{

}

void DBService::Init(void)
{
	__ENTER_FUNCTION
		InitService();
	    NewServiceExec();
		InitServiceExec();
	__LEAVE_FUNCTION
}

void DBService::InitService()
{
	__ENTER_FUNCTION
		m_AssignTaskIndex = 0;
		AssertEx(m_DBBaseTaskPtrList.empty(),"");
		AssertEx(m_DBServiceExecPtrVec.empty(),"");
		for (int i=0;i<DB_TASK_MAX_NUM;i++)
		{
			AssertEx(m_CurProTaskPtrMap[i].empty(),"");
		}

		// 创建并添加调度器
		InvokerPtr ptr(new DBServiceInvoker(*this,"DBServiceInvoker"));
		AddInvoker(ptr);
	__LEAVE_FUNCTION
}

void DBService::NewServiceExec()
{
	__ENTER_FUNCTION 
		int nDBServiceExecCount = _GameConfig().m_nDBThreadCount;
	AssertEx(nDBServiceExecCount <= MAX_DB_SERVICEEXEC_COUNT ,"");
	AssertEx(nDBServiceExecCount >= MIN_DB_SERVICEEXEC_COUNT ,"");

	for (int i=0;i<nDBServiceExecCount;i++)
	{
		DBServiceExecPtr ptr(new DBServiceExec(i));
		m_DBServiceExecPtrVec.push_back(ptr);
	}
	__LEAVE_FUNCTION
}

void DBService::InitServiceExec(void)
{
	__ENTER_FUNCTION
		for (int i = 0; i < (int)m_DBServiceExecPtrVec.size();i++)
		{
			AssertEx(m_DBServiceExecPtrVec[i],"");
			InvokerPtr ptr = m_DBServiceExecPtrVec[i]->InitMyself();
			AssertEx(ptr,"");
			AddInvoker(ptr);
		}
	__LEAVE_FUNCTION
}

int DBService::GetRunState(void)
{
	return GetRunState_Base();
}

void DBService::Tick(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
	Service::Tick(rTimeInfo);

	Tick_AssignTask(rTimeInfo);

	Tick_FinalSave(rTimeInfo);

	Tick_CheckDBConnect(rTimeInfo);

	__LEAVE_FUNCTION
}

void DBService::OnStartRunning(void)
{
	__ENTER_FUNCTION
		
	__LEAVE_FUNCTION
}

void DBService::Tick_FinalSave(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		if (!(GetStatus() == ServiceStatus::FINALSAVE_PROCESS))
		{
			return;
		}	

		if (rTimeInfo.m_bDiffSecond )
		{ 	
			m_FinalSaveDelayTime--;	

			CacheLog(LOGDEF_INST(ServerStatus), "DBService::Tick_FinalSave Wait, FinalSaveDelayTime(%d)",
				m_FinalSaveDelayTime);
		}

		if(m_FinalSaveDelayTime <= 0)
		{
			CacheLog(LOGDEF_INST(ServerStatus), "DBService::Tick_FinalSave, FinalSaveDelayTime(%d)",
				m_FinalSaveDelayTime);

			tint32 nEmptyCurMapCount = 0;
			for (tint32 i = 0;i < DB_TASK_MAX_NUM; i++)
			{
				if (m_CurProTaskPtrMap[i].empty())
				{
					nEmptyCurMapCount++;
				}
				else
				{
					CacheLog(LOGDEF_INST(ServerStatus), "DBService::Tick_FinalSave Not Empty TaskList, TaskType(%d),TaskCount(%d)",
						i,m_CurProTaskPtrMap[i].size());
				}
			}
			if (DB_TASK_MAX_NUM == nEmptyCurMapCount)
			{
				FinalsaveOk();
			}
			else
			{
				CacheLog(LOGDEF_INST(ServerStatus), "DBService::Tick_FinalSave Empty TaskList Count, Count(%d)",
					nEmptyCurMapCount);
			}
		}

	__LEAVE_FUNCTION
}

void DBService::Tick_AssignTask(const TimeInfo& rTimeInfo)
{
	__ENTER_FUNCTION
		if (m_DBBaseTaskPtrList.empty())
		{
			return;
		}

		for (DBBaseTaskPtrList::iterator itPos = m_DBBaseTaskPtrList.begin();itPos != m_DBBaseTaskPtrList.end();)
		{
			AssertEx(*itPos,"");
			int nTaskType = (*itPos)->GetTaskType();
			AssertEx((nTaskType >= 0 && nTaskType <DB_TASK_MAX_NUM),"");
			if (IsCanDirectAssigned(nTaskType))
			{
				SendTaskByIndex((*itPos));
				itPos = m_DBBaseTaskPtrList.erase(itPos);
			}
			else
			{
				if (IsCanAssigned((*itPos)))
				{
					SendTaskByIndex((*itPos));
					m_CurProTaskPtrMap[nTaskType].insert(std::make_pair((*itPos)->GetKey(),(*itPos)));
					itPos = m_DBBaseTaskPtrList.erase(itPos);
				}
				else
				{
					itPos++;
				}
			}
		}
	__LEAVE_FUNCTION
}

void DBService::SendTaskByIndex(DBBaseTaskPtr baseTaskPtr)
{
	__ENTER_FUNCTION
		AssertEx(baseTaskPtr,"");
	    if (baseTaskPtr->IsForLoad())
		{
			if (m_AssignTaskIndex%2 != 1)
			{
				m_AssignTaskIndex = (m_AssignTaskIndex + 1) % (int)m_DBServiceExecPtrVec.size();
			}
		}
		else if (baseTaskPtr->IsForSave())
		{
			if (m_AssignTaskIndex%2 != 0)
			{
				m_AssignTaskIndex = (m_AssignTaskIndex + 1) % (int)m_DBServiceExecPtrVec.size();
			}
		}

		AssertEx(0 <= m_AssignTaskIndex && m_AssignTaskIndex < (int)m_DBServiceExecPtrVec.size(),"");

		DBAssignTaskMsgPtr MsgPtr = POOLDEF_NEW(DBAssignTaskMsg);
		AssertEx(MsgPtr,"");
		MsgPtr->m_DBBaseTaskPtr = baseTaskPtr;
		AssertEx(m_DBServiceExecPtrVec[m_AssignTaskIndex],"");

		SendMessage2Srv(*(m_DBServiceExecPtrVec[m_AssignTaskIndex]),MsgPtr);

		m_AssignTaskIndex = (m_AssignTaskIndex + 1) % (int)m_DBServiceExecPtrVec.size();

	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqSaveMarchDataMsg &rMsg)
{
	__ENTER_FUNCTION
	DBMarchTaskPtr TaskPtr = POOLDEF_NEW(DBMarchTask);
	AssertEx(TaskPtr,"");

	TaskPtr->SetData(rMsg.m_March);

	DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask, DBMarchTask>(TaskPtr);	
	AssertEx(ptr,"");

	//设置操作类型
	ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_SAVE_DB);	
	ptr->SetKey(rMsg.m_March.m_nMarchId);  //为避免在队列中替换不同类型的GUID数据，用类型做key
	AddTask(ptr);
	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqSaveTileDataMsg &rMsg)
{
	__ENTER_FUNCTION
		DBWorldMapTaskPtr TaskPtr = POOLDEF_NEW(DBWorldMapTask);
		AssertEx(TaskPtr,"");
		TaskPtr->SetKey(TaskPtr->GetTaskType());

		DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask,DBWorldMapTask>(TaskPtr);
		AssertEx(ptr,"");

		ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_SAVE_DB);

		ptr->SetRetServiceID(ServiceID::WORLDMAP);

		AddTask(ptr);
	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqLoadTileDataMsg &rMsg)
{
	__ENTER_FUNCTION
		DBWorldMapTaskPtr TaskPtr = POOLDEF_NEW(DBWorldMapTask);
		AssertEx(TaskPtr,"");
		TaskPtr->SetKey(TaskPtr->GetTaskType());

		DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask,DBWorldMapTask>(TaskPtr);
		AssertEx(ptr,"");

		ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);
	
		ptr->SetRetServiceID(ServiceID::WORLDMAP);

		AddTask(ptr);

	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqCreateCityMsg &rMsg)
{
	__ENTER_FUNCTION
		DBCreateCityTaskPtr TaskPtr = POOLDEF_NEW(DBCreateCityTask);
	AssertEx(TaskPtr,"");
	TaskPtr->SetKey(TaskPtr->GetTaskType());
	TaskPtr->SetData(rMsg.m_Data);
	TaskPtr->SetPlayerId(rMsg.m_nPlayerID);
	DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask,DBCreateCityTask>(TaskPtr);
	AssertEx(ptr,"");

	ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);

	ptr->SetRetServiceID(ServiceID::WORLDMAP);

	AddTask(ptr);
	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqSaveGuidMsg &rMsg)
{
	__ENTER_FUNCTION
		DBGuidTaskPtr TaskPtr = POOLDEF_NEW(DBGuidTask);
	AssertEx(TaskPtr,"");

	DBGuidData tempGuidData;
	tempGuidData.m_Type   = rMsg.m_Type;
	tempGuidData.m_Serial = rMsg.m_Serial;
	TaskPtr->SetData(tempGuidData);

	DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask, DBGuidTask>(TaskPtr);	
	AssertEx(ptr,"");

	//设置操作类型
	ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_SAVE_DB);	
	ptr->SetKey(rMsg.m_Type);  //为避免在队列中替换不同类型的GUID数据，用类型做key
	AddTask(ptr);
	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqCreateBuildMsg &rMsg)
{

}

void DBService::HandleMessage(const DBSaveUserMsg &rMsg)
{
	__ENTER_FUNCTION
		if (rMsg.m_UserGuid <=0)
		{
			return;
		}

		DBUserTaskPtr TaskPtr = POOLDEF_NEW(DBUserTask);
		AssertEx(TaskPtr,"");
		TaskPtr->SetKey(rMsg.m_UserGuid);
		TaskPtr->SetUserGuid(rMsg.m_UserGuid);
		TaskPtr->SetData(rMsg.m_UserData);
		TaskPtr->SetImmediateSave(rMsg.m_bImmediateSave);
		TaskPtr->SetFinalSave(rMsg.m_bFinalSave);

		DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask,DBUserTask>(TaskPtr);
		AssertEx(ptr,"");

		int operationType = GetUserDataTaskSaveType(rMsg.m_UserGuid,rMsg.m_bImmediateSave);
		ptr->SetOperationType(operationType);
		ptr->SetRetServiceID(ServiceID::LOGIN);

		AddTask(ptr);


	__LEAVE_FUNCTION
}
void DBService::HandleMessage(const DBLoadUserMsg &rMsg)
{
	__ENTER_FUNCTION
		if (rMsg.m_UserGuid <0)
		{
			return;
		}

		DBUserTaskPtr TaskPtr = POOLDEF_NEW(DBUserTask);
		AssertEx(TaskPtr,"");
		TaskPtr->SetKey(rMsg.m_UserGuid);
		TaskPtr->SetUserGuid(rMsg.m_UserGuid);
		TaskPtr->SetAccountName(rMsg.m_AccName);
		TaskPtr->SetPlayerId(rMsg.m_nPlayerID);
		//TaskPtr->SetData(rMsg.m_UserData);

		DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask,DBUserTask>(TaskPtr);
		AssertEx(ptr,"");

		ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);

		AddTask(ptr);

	__LEAVE_FUNCTION
}
void DBService::HandleMessage(const DBCreateCharMsg &rMsg)
{
	__ENTER_FUNCTION
		DBCreateCharTaskPtr TaskPtr = POOLDEF_NEW(DBCreateCharTask);
	AssertEx(TaskPtr, "");
	TaskPtr->SetKey(rMsg.m_UserData.GetGuid());
	TaskPtr->SetData(rMsg.m_UserData);
	TaskPtr->SetAccName(rMsg.m_AccName);
	TaskPtr->SetPlayerID(rMsg.m_nPlayerID);
	DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask, DBCreateCharTask>(TaskPtr);	
	AssertEx(ptr,"");

	//设置操作类型
	ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);

	ptr->SetRetServiceID(ServiceID::LOGIN);

	AddTask(ptr);
	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBAskCharListMsg &rMsg)
{
	__ENTER_FUNCTION
		DBCharListTaskPtr TaskPtr = POOLDEF_NEW(DBCharListTask);
	AssertEx(TaskPtr, "");
	TaskPtr->SetData(rMsg.m_AccName);
	TaskPtr->SetPlayerID(rMsg.m_nPlayerID);
	TaskPtr->SetKey(rMsg.m_nPlayerID);

	DBBaseTaskPtr ptr = boost::static_pointer_cast<DBBaseTask, DBCharListTask>(TaskPtr);
	AssertEx(ptr,"");

	//设置操作类型
	ptr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);

	ptr->SetRetServiceID(ServiceID::LOGIN);

	AddTask(ptr);
	__LEAVE_FUNCTION
}

bool DBService::IsCanAssigned(const DBBaseTaskPtr Ptr)
{
	__ENTER_FUNCTION
		if (Ptr)
		{
			int taskType = Ptr->GetTaskType();
			AssertEx(taskType>=0 && taskType<DB_TASK_MAX_NUM,"");
			DBBaseTaskPtrMap::const_iterator itPos = m_CurProTaskPtrMap[taskType].find(Ptr->GetKey());
			if (itPos == m_CurProTaskPtrMap[taskType].end())
			{
				return true;
			}

		}
		return false;
	__LEAVE_FUNCTION
		return false;
}

void DBService::HandleMessage(const DBReqLoadMapMarchMsg &rMsg)
{
	__ENTER_FUNCTION
		DBWorldMarchTaskPtr TaskPtr = POOLDEF_NEW(DBWorldMarchTask);
	AssertEx(TaskPtr,"");
	TaskPtr->SetKey(TaskPtr->GetTaskType());

	DBBaseTaskPtr BasePtr = boost::static_pointer_cast<DBBaseTask, DBWorldMarchTask>(TaskPtr);
	AssertEx(BasePtr,"");
	//设置操作类型
	TaskPtr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);
	BasePtr->SetRetServiceID(ServiceID::SCENE);

	AddTask(BasePtr);
	__LEAVE_FUNCTION
}

void DBService::HandleMessage(const DBReqLoadRandomNameMsg& rMsg)
{
	__ENTER_FUNCTION
		DBRandomNameTaskPtr TaskPtr = POOLDEF_NEW(DBRandomNameTask);
	AssertEx(TaskPtr,"");
	TaskPtr->SetKey(TaskPtr->GetTaskType());

	DBBaseTaskPtr BasePtr = boost::static_pointer_cast<DBBaseTask, DBRandomNameTask>(TaskPtr);
	AssertEx(BasePtr,"");

	BasePtr->SetOperationType(DBBaseTask::OPERATION_TYPE_LOAD);
	BasePtr->SetRetServiceID(ServiceID::LOGIN);

	AddTask(BasePtr);
	__LEAVE_FUNCTION
}

bool DBService::IsTaskCanReplace(const DBBaseTaskPtr PtrOld,const DBBaseTaskPtr PtrNew) const
{
	__ENTER_FUNCTION
		if (PtrNew && PtrOld)
		{
			if (PtrOld->GetTaskType() == PtrNew->GetTaskType()
				&& PtrNew->GetKey() == PtrOld->GetKey())
			{
				if (PtrOld->GetOperationType() == PtrNew->GetOperationType())
				{
					return true;
				}
				else
				{
					if (DB_TASK_USER_DATA == PtrOld->GetTaskType() && DB_TASK_USER_DATA == PtrNew->GetTaskType())
					{
						if (DBBaseTask::OPERATION_TYPE_SAVE_DB == PtrOld->GetOperationType() || DBBaseTask::OPERATION_TYPE_SAVE_MEM == PtrOld->GetOperationType())
						{
							if (DBBaseTask::OPERATION_TYPE_SAVE_DB == PtrNew->GetOperationType() || DBBaseTask::OPERATION_TYPE_SAVE_MEM == PtrNew->GetOperationType())
							{
								if (DBBaseTask::OPERATION_TYPE_SAVE_DB == PtrOld->GetOperationType())
								{
									PtrNew->SetOperationType(DBBaseTask::OPERATION_TYPE_SAVE_DB);
								}
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	__LEAVE_FUNCTION
	return false;
}

void DBService::AddTask(const DBBaseTaskPtr Ptr )
{
	__ENTER_FUNCTION
		if (!Ptr)
		{
			CacheLog(LOGDEF_INST(DBAgentError),"DBService::InValid DBBaseTaskPtr asked to add.");
			return;
		}
		if (!IsCanAddTask())
		{

			if (Ptr->GetSaveFail())
			{
				//存储失败的Task重新申请加入队列，不返回
				//将存储失败的Task重新加入队列处理，主要是避免停服存盘时，死锁存储失败的任务不能被处理。
				CacheLog(LOGDEF_INST(DBAgentError),"DBService::Save Fail DBBaseTask asked to add after final save.");
			}
			else
			{
				CacheLog(LOGDEF_INST(DBAgentError),"DBService::InValid DBBaseTask asked to add after final save.");
				return;
			}
		}

		//如果是可以直接分配的任务，直接加入队列
		if (IsCanDirectAssigned(Ptr->GetTaskType()))
		{
			m_DBBaseTaskPtrList.push_back(Ptr);

			CacheLog(LOGDEF_INST(DBAgent),"DBService::New DBTask Added to List newTaskType=%d newOpType=%d",
				Ptr->GetTaskType(), Ptr->GetOperationType());

			return;
		}

		DBBaseTaskPtrList::reverse_iterator itPos = m_DBBaseTaskPtrList.rbegin();
		DBBaseTaskPtrList::reverse_iterator itEnd = m_DBBaseTaskPtrList.rend();
		//轮询队列查找可替换的DBTask
		for (itPos; itPos != itEnd; itPos++)
		{
			//相同的任务
			if (IsTaskCanReplace(*itPos,Ptr))
			{
				//新DBTask的请求晚于旧DBTask
				if ((*itPos)->GetOptTime() >0 && (*itPos)->GetOptTime() <= Ptr->GetOptTime())
				{
					//替换
					CacheLog(LOGDEF_INST(DBAgent),"DBService::Old DBTask Replace Begin, \1 oldTaskType=%d \1 oldKey=%lld \1 oldOpType=%d \1 oldReqOpTime=%u \1 newTaskType=%d \1 newKey=%lld  \1 newOpType=%d \1 newReqOpTime=%u",
						(*itPos)->GetTaskType(),(*itPos)->GetKey(),(*itPos)->GetOperationType(),(*itPos)->GetOptTime(),
						Ptr->GetTaskType(),Ptr->GetKey(),Ptr->GetOperationType(),Ptr->GetOptTime());

					(*itPos) = Ptr;

					CacheLog(LOGDEF_INST(DBAgent),"DBService::Old DBTask Replace End,\1 Key=%lld",(*itPos)->GetKey());
					return;
				}
				//新DBTask的请求操作时间早于旧DBTask
				else
				{
					//忽略
					CacheLog(LOGDEF_INST(DBAgent),"DBService::New DBTask Ignored,\1 oldTaskType=%d \1 oldKey=%lld \1 oldOpType=%d \1 oldReqOpTime=%u \1 newTaskType=%d \1 newKey=%lld \1 newOpType=%d \1 newReqOpTime=%u",
						(*itPos)->GetTaskType(),(*itPos)->GetKey(),(*itPos)->GetOperationType(),(*itPos)->GetOptTime(),
						Ptr->GetTaskType(),Ptr->GetKey(),Ptr->GetOperationType(),Ptr->GetOptTime());
					return;
				}
			}
		}
		//队列中没有相同的DBTask
		if (itPos == itEnd)
		{
			m_DBBaseTaskPtrList.push_back(Ptr);
			return;
		}

		//数据没有能加入队列
		DiskLog(LOGDEF_INST(DBAgentError),"DBService::New DBTask Missied,\1 newTaskType=%d \1 newKey=%lld\1 newOpType=%d \1 newReqOpTime=%u",					 
			Ptr->GetTaskType(),Ptr->GetKey(),\
			Ptr->GetOperationType(),Ptr->GetOptTime());

		AssertEx(false,":New DBTask Missied");

		__LEAVE_FUNCTION
}  

bool DBService::IsCanDirectAssigned(int taskType)
{
	__ENTER_FUNCTION
		// 逻辑上不怕并发阀盖存储的任务才可以直接分发
		if (taskType == DB_TASK_CREATECHAR)
		{
			return true;
		}
		return false;
	__LEAVE_FUNCTION
		return false;
}

int DBService::GetUserDataTaskSaveType(int64 UserGuid,bool ImmediateSave)
{
	__ENTER_FUNCTION
		if (UserGuid<=0)
		{
			return DBBaseTask::OPERATION_TYPE_UNKNOW;
		}
		
		// 要求立即存储,返回DB存储
		if (ImmediateSave)
		{
			return DBBaseTask::OPERATION_TYPE_SAVE_DB;
		}

		DBLastSaveDBTimeMap::iterator itPos = m_UserDataLstSaveDBTime.find(UserGuid);
		if (itPos != m_UserDataLstSaveDBTime.end())
		{
			int lastSaveDBTime = itPos->second;
			if (_GameConfig().m_nUserDataSaveDBInterval < (gTimeManager.SysRunTime() - lastSaveDBTime))
			{
				//需要存储DB
				return DBBaseTask::OPERATION_TYPE_SAVE_DB;
			}
			else
			{
				return DBBaseTask::OPERATION_TYPE_SAVE_MEM;
			}
		}
		else
		{
			//增加记录
			UpdateUserDataLastSaveDbTime(UserGuid);
			// 第一次先存DB
			return DBBaseTask::OPERATION_TYPE_SAVE_DB;
		}
		
		//错误的操作类型
		CacheLog(LOGDEF_INST(DBAgentError),"DBService::GetUserDataTaskSaveType \1 OPERATION_TYPE_UNKNOWN=%lld \1 SaveType=%d",
			UserGuid,ImmediateSave);
		return DBBaseTask::OPERATION_TYPE_UNKNOW;
	__LEAVE_FUNCTION
		return DBBaseTask::OPERATION_TYPE_UNKNOW;
}

void DBService::UpdateUserDataLastSaveDbTime(int64 UserGuid)
{
	__ENTER_FUNCTION
		if (UserGuid<=0)
		{
			return;
		}
		DBLastSaveDBTimeMap::iterator itPos = m_UserDataLstSaveDBTime.find(UserGuid);
		if (itPos != m_UserDataLstSaveDBTime.end())
		{
			itPos->second = gTimeManager.SysRunTime();
		}
		else
		{
			m_UserDataLstSaveDBTime.insert(std::make_pair(UserGuid,gTimeManager.SysRunTime()));
		}
	__LEAVE_FUNCTION
}

void DBService::Finalsave(void)
{
	__ENTER_FUNCTION
		m_FinalSaveDelayTime = DB_FINAL_SAVE_DELAY_TIME;
	__LEAVE_FUNCTION
}

bool DBService::IsCanAddTask()
{
	__ENTER_FUNCTION
	if (GetStatus() == ServiceStatus::FINALSAVE_PROCESS)
	{
		if (m_FinalSaveDelayTime > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
	return false;
	__LEAVE_FUNCTION
	return false;
}

void DBService::Tick_CheckDBConnect(const TimeInfo &rTimeInfo)
{
	__ENTER_FUNCTION
		if (rTimeInfo.m_bDiffHour)
		{
			for (int i=0;i<(int)m_DBServiceExecPtrVec.size();i++)
			{
				AssertEx(m_DBServiceExecPtrVec[i],"");
				DBCheckConnectMsgPtr MsgPtr = POOLDEF_NEW(DBCheckConnectMsg);
				AssertEx(MsgPtr,"");
				SendMessage2Srv(*(m_DBServiceExecPtrVec[i]),MsgPtr);
			}
		}
	__LEAVE_FUNCTION
}

