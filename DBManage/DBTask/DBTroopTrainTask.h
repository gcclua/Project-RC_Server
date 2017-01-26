#ifndef _DBTROOPTRAINTASK_H_
#define _DBTROOPTRAINTASK_H_
#pragma once

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_City.h"

class DBTroopTrainTask : public DBBaseTask
{
public:
	enum 
	{
		TASK_TYPE = DB_TASK_MARCH,
	};

public:
	DBTroopTrainTask(void);
	virtual ~DBTroopTrainTask(void);

public:

	void				SetData(const DBTroopTrain& val);              

public:

	// 获取当前的任务类型
	virtual int           GetTaskType() const {return TASK_TYPE;};

protected:
	virtual bool          Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);

private:
	DBTroopTrain    m_Data;

};

POOLDEF_DECL(DBTroopTrainTask);

#endif
