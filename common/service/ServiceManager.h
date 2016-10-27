
#ifndef _SERVICEMANAGER_H_
#define _SERVICEMANAGER_H_
#include "threadpool/threadpool.hpp"
#include "Base.h"
#include "Service.h"


class ServiceManager
{
public:
	ServiceManager(void);
	virtual ~ServiceManager(void);

public:
	void Create(int nServiceCOunt,int nThreadCount);
	void Register(Service * pInst);
	void InitAllService(void);
	void Run(void);
	
	
protected:
	void RunOpenup(void);
	void RunMainLogic(void);
	void RunShutdown(void);
	void RunFinalSave(void);
protected:
	void Wait(int nSecondTImeOut);
protected:
	bool IsAllServiceStatusEqual(int nStatus);
	void SetAllServiceStatus(int nStatus);
	bool IsShoudShutdown(void);

public:
	virtual int GetStatus() const {return m_nStatus;};
private:
	int m_nStatus;
public:
	void ReceiveMessage(int nServiceID,ConstMessagePtr ConstPtr);
protected: 
	void Tick(int nElapse);
protected:
	void UpdateAllService(int nElapse);
	void UpdateAllInvoker(int nElapse);
	void UpdateInvokeMonitor(int nElapse);

protected:
	int m_nInvokeMonitor_Time;
	int m_nInvokeMonitor_JoinCount;
	int m_nInvokeMonitor_ScheduleCount;

protected:
	int m_nLogCpuMemStat_Time;

protected:
	ServicePtrVec m_ServicePtrVec;
	InvokerPtrSet m_InvokerPtrSet;
protected:
	typedef boost::threadpool::fifo_pool CPUPool;
	typedef boost::shared_ptr<CPUPool>   CPUPoolPtr;
protected:
	CPUPoolPtr m_CPUPoolPtr;
};

extern ServiceManager gServiceManager;

#endif