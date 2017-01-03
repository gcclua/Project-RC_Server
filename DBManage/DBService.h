
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

	// ��Invoker����ʵ���߼����HeartBeat����
	virtual void Tick(const TimeInfo &rTimeInfo);
	// �����Ƿ���Է���
	bool IsCanAssigned(const DBBaseTaskPtr Ptr);
	// �Ƿ������������
	bool IsCanAddTask();
	// �Ƿ�����ͬ���͵�����
	bool IsTaskCanReplace(const DBBaseTaskPtr ptrOld,const DBBaseTaskPtr PtrNew) const;
	// �Ƿ����ֱ�ӷ��䣬�����뵱ǰ�����б�
	bool IsCanDirectAssigned(int TaskType);
	// ����������֮��
	virtual void OnStartRunning(void);
private:
	// ��ִ������������
	void Tick_AssignTask(const TimeInfo &rTimeInfo);

	// ���洢Tick
	void Tick_FinalSave(const TimeInfo &rTimeInfo);

	// ÿСʱ����һ�β�ѯ���󣬱���ʱ�����������Mysq�Զ��Ͽ�����
	void Tick_CheckDBConnect(const TimeInfo &rTimeInfo);

	// �洢���񻺴������������
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
	DBServiceExecPtrVec     m_DBServiceExecPtrVec; //�洢ִ����
	DBBaseTaskPtrList       m_DBBaseTaskPtrList;   // �洢���񻺴����
	bsarray<DBBaseTaskPtrMap,DB_TASK_MAX_NUM> m_CurProTaskPtrMap; // ��ǰ�����������map
	DBLastSaveDBTimeMap     m_UserDataLstSaveDBTime;
	int                     m_AssignTaskIndex; // ����ָ�����
	int                     m_FinalSaveDelayTime;
	int                     m_TaskKeySerial; // DBTask��û�п�����ΪKeyֵ����ֵʱ�����ô�ֵ��Ϊkeyֵ
};

typedef GeneralInvoker<DBService,200,200> DBServiceInvoker;


#endif