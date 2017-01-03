#ifndef _LOGSERVICE_H_
#define _LOGSERVICE_H_

#include "Base.h"
#include "service/Service.h"
#include "service/Invoker.h"

class LogService : public Service
{
public:
	LogService(void);
	virtual ~LogService(void);

public:
	virtual tint32 GetServiceID(void);
	virtual void Init(void);

public:
	virtual tint32 GetRunState(void);
public:
	virtual void Tick(const TimeInfo &rTimeInfo);

private:
	void FlushAll(void);
	void RebuildAll(void);
};


typedef GeneralInvoker<LogService, 2000, 2000> LogInvoker;

#endif