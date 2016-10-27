
#ifndef _SERVICE_H_
#define _SERVICE_H_

#include "Base.h"
#include "BaseService.h"
#include "Invoker.h"
#include "ServiceDefine.h"

class Service :public BaseService
{
public:
	Service(void);
	virtual ~Service(void);

public:
	enum 
	{
		RUNSTATE_NORMAL = 0,
		RUNSTATE_SLOWLY,
		RUNSTATE_PAUSE,
	};

public:
	virtual int GetRunState(void);

protected:
	int GetRunState_General(void);
	int GetRunState_Base(void);

public:
	virtual void Tick(const TimeInfo &rTimeInfo);

public:
	virtual int GetServiceID() = 0;
	virtual void Init() = 0;
protected:

	virtual void Openup(void);
	virtual void Shutdown(void);
	virtual void Finalsave(void);
protected:
	void OpenupOk(void);
	void ShutdownOk(void);
	void FinalsaveOk(void);

protected:
	virtual void OnStartRunning(void) {}

private:
	bool m_bCanCallOnStartRuning;

protected:

	void Tick_Status(const TimeInfo &rTimeInfo);

public:
	int GetStatus(void ) const {return m_nStatus;}
	void SetStatus(int nStatus) {m_nStatus = nStatus;}



private:
	int m_nStatus;

public:
	InvokerPtr FetchInvoker(void);

protected:
	void AddInvoker(const InvokerPtr Ptr);
private:
	InvokerTSList m_InvokerPtrTSList;

};

typedef boost::shared_ptr<Service> ServicePtr;
typedef bsvector<ServicePtr>       ServicePtrVec;



#endif