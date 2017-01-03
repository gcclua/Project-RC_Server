
#ifndef _DBSERVICE_H_
#define _DBSERVICE_H_

#include "Service/Service.h"
#include "Service/Invoker.h"
#include "DBTask/DBBaseTask.h"
#include "DBServiceExec.h"

class DBLoadUserMsg;
class DBSaveUserMsg;
class DBCreateCharMsg;
class DBReqLoadTileDataMsg;
class DBReqSaveTileDataMsg;
class DBReqCreateBuildMsg;
class DBReqLoadRandomNameMsg;
class DBRetLoadMapMarchMsg;

class DBService :public Service
{
public:
	DBService(void);
	virtual ~DBService(void);

public:
	enum 
	{
#if defined(_WIN32)
	MIN_DB_SERVICEEXEC_COUNT = 1,
	MAX_DB_SERVICEEXEC_COUNT = 8,
#else
	MIN_DB_SERVICEEXEC_COUNT = 8,
	MAX_DB_SERVICEEXEC_COUNT = 32;
#endif
	};

public:
	virtual int GetServiceID(void){return ServiceID::DBAGENT;}

public:
	virtual void Init(void);
protected:
	virtual void  Finalsave(void);
private:
	void InitService(void);
	void NewServiceExec(void);
	void InitServiceExec(void);

public:
	virtual int GetRunState(void);

	// 供Invoker调度实现逻辑层的HeartBeat机制
	virtual void Tick(const TimeInfo &rTimeInfo);
	// 任务是否可以分配
	bool IsCanAssigned(const DBBaseTaskPtr Ptr);
	// 是否可以增加任务
	bool IsCanAddTask();
	// 是否是相同类型的任务
	bool IsTaskCanReplace(const DBBaseTaskPtr ptrOld,const DBBaseTaskPtr PtrNew) const;
	// 是否可以直接分配，不进入当前处理列表
	bool IsCanDirectAssigned(int TaskType);
	// 服务启动好之后
	virtual void OnStartRunning(void);
private:
	// 给执行器分配任务
	void Tick_AssignTask(const TimeInfo &rTimeInfo);

	// 最后存储Tick
	void Tick_FinalSave(const TimeInfo &rTimeInfo);

	// 每小时发起一次查询请求，避免时间过长无请求，Mysq自动断开连接
	void Tick_CheckDBConnect(const TimeInfo &rTimeInfo);

	// 存储任务缓存队列增加任务
	void AddTask(const DBBaseTaskPtr Ptr);

	void SendTaskByIndex(DBBaseTaskPtr baseTaskPtr);

public:
	virtual void HandleMessage(const DBSaveUserMsg &rMsg);
	virtual void HandleMessage(const DBLoadUserMsg &rMsg);
	virtual void HandleMessage(const DBReqLoadTileDataMsg &rMsg);
	virtual void HandleMessage(const DBReqSaveTileDataMsg &rMsg);
	virtual void HandleMessage(const DBReqCreateBuildMsg &rMsg);
	virtual void HandleMessage(const DBReqSaveGuidMsg &rMsg);

	virtual void HandleMessage(const DBCreateCharMsg &rMsg);
	virtual void HandleMessage(const DBAskCharListMsg &rMsg);
	virtual void HandleMessage(const DBReqLoadRandomNameMsg &rMsg);	
	virtual void HandleMessage(const DBReqCreateCityMsg &rMsg);

	virtual void HandleMessage(const DBReqLoadMapMarchMsg &rMsg);
	virtual void HandleMessage(const DBReqSaveMarchDataMsg &rMsg);

public:
	int  GetUserDataTaskSaveType(int64 UserGuid,bool ImmediateSave);
	void UpdateUserDataLastSaveDbTime(int64 UserGuid);
	int  GetTaskKeySerial(){return m_TaskKeySerial++;};

private:
	DBServiceExecPtrVec     m_DBServiceExecPtrVec; //存储执行器
	DBBaseTaskPtrList       m_DBBaseTaskPtrList;   // 存储任务缓存队列
	bsarray<DBBaseTaskPtrMap,DB_TASK_MAX_NUM> m_CurProTaskPtrMap; // 当前处理任务查找map
	DBLastSaveDBTimeMap     m_UserDataLstSaveDBTime;
	int                     m_AssignTaskIndex; // 任务指派序号
	int                     m_FinalSaveDelayTime;
	int                     m_TaskKeySerial; // DBTask中没有可以作为Key值的数值时，采用此值作为key值
};

typedef GeneralInvoker<DBService,200,200> DBServiceInvoker;


#endif