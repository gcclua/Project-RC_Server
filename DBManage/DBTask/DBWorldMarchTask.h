#ifndef _DBWORDMARCHTASK_H_
#define _DBWORDMARCHTASK_H_
#pragma once

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_March.h"

class DBWorldMarchTask : public DBBaseTask
{
public:
	enum 
	{
		TASK_TYPE = DB_TASK_WORDMARCH,
	};

public:
	DBWorldMarchTask(void);
	virtual ~DBWorldMarchTask(void);

public:

public:

	// 获取当前的任务类型
	virtual int           GetTaskType() const {return TASK_TYPE;};

protected:
	virtual bool          Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);

};

POOLDEF_DECL(DBWorldMarchTask);

#endif
