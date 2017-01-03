#ifndef _DBRandomNameTask_H_
#define _DBRandomNameTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_RandomName.h"
/*******************************************************************************/
//DBTask注意事项：
//	1）继承自DBBaseTask
//	2）有一个公有类型的枚举，TASK_TYPE，值是DB_TASK_TYPE枚举中的类型值。
//	3）有三个Protected类型的虚函数Load，Save，SendOpResult。根据需求实现。
//	4）有一个公有类型虚函数GetTaskType，纯虚，必须实现。
/*******************************************************************************/
class DBRandomNameTask : public DBBaseTask
{
public:
	enum
	{
		TASK_TYPE =   DB_TASK_RANDOMNAME,
	};
public:
	DBRandomNameTask(void);
	virtual ~DBRandomNameTask(void);

public:
	virtual tint32				GetTaskType()const{return TASK_TYPE;}
protected:
	virtual bool				Load(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface);	
};

POOLDEF_DECL(DBRandomNameTask);

#endif //_DBRandomNameTask_H_