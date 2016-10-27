
#ifndef _SERVICECELL_H_
#define _SERVICECELL_H_

#include "Base.h"
#include "BaseService.h"
#include "Invoker.h"

class ServiceCell : public BaseService
{
public:
	ServiceCell(void);
	virtual ~ServiceCell(void);

public:
	virtual void Tick( const TimeInfo &rTimeInfo);

public:
	virtual InvokerPtr Init(void);
public:
	virtual InvokerPtr InitMyself(void) = 0;

};

#endif