#ifndef _DBMARCHTASK_H_
#define _DBMARCHTASK_H_
#pragma once

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_March.h"

class DBMarchTask : public DBBaseTask
{
public:
	enum 
	{
		TASK_TYPE = DB_TASK_MARCH,
	};

public:
	DBMarchTask(void);
	virtual ~DBMarchTask(void);

public:

	void					SetData(const DBMarch& val);              

public:

	// 获取当前的任务类型
	virtual int           GetTaskType() const {return TASK_TYPE;};

protected:
	virtual bool          Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);

private:
	DBMarch    m_Data;

};

POOLDEF_DECL(DBMarchTask);

#endif
