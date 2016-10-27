
#ifndef _DBSERVICEEXEC_H_
#define _DBSERVICEEXEC_H_

#include "Service/ServiceCell.h"
#include "Service/Invoker.h"
#include "DataBase/LibMemInterface.h"
#include "DataBase/ODBCInterface.h"

class DBAssignTaskMsg;
class DBCheckConnectMsg;



class DBServiceExec :public ServiceCell
{
public:
	DBServiceExec(int iIndex);
	virtual ~DBServiceExec(void);

public:
	virtual InvokerPtr InitMyself(void);
	virtual int GetRunState(void);

public:
	// 供Invoker调度实现逻辑层HearBeat机制
	virtual void Tick(const TimeInfo &rTimeInfo);

public:
	// 消息相应接口
	virtual void HandleMessage(const DBAssignTaskMsg &rMsg);
	virtual void HandleMessage(const DBCheckConnectMsg &rMsg);

private:
	bool CheckDBVersion();
	bool ODBCInterfaceInit(void);
	bool LibMemInterfaceInit(void);

private:
	ODBCInterface   m_ODBCInterface;
	LibMemInterface m_LibMemInterface;
	int             m_MyIndex;

};

typedef boost::shared_ptr<DBServiceExec> DBServiceExecPtr;
typedef bsvector<DBServiceExecPtr>       DBServiceExecPtrVec;

typedef GeneralInvoker<DBServiceExec,500,10000> DBServiceExecInvoker;


#endif