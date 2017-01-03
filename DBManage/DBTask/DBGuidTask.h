#ifndef _DBGuidTask_H_
#define _DBGuidTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct.h"
/*******************************************************************************/
//DBTask注意事项：
//	1）继承自DBBaseTask
//	2）有一个公有类型的枚举，TASK_TYPE，值是DB_TASK_TYPE枚举中的类型值。
//	3）有三个Protected类型的虚函数Load，Save，SendOpResult。根据需求实现。
//	4）有一个公有类型虚函数GetTaskType，纯虚，必须实现。
/*******************************************************************************/
class DBGuidTask : public DBBaseTask
{
public:
	enum
	{
		TASK_TYPE =   DB_TASK_GUID,
	};
public:
	DBGuidTask(void){};
	virtual ~DBGuidTask(void){};
public:
	void					SetData(const DBGuidData& val);
	const DBGuidData&		GetData()const{return m_GuidData;}
public:
	virtual bool			Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface);
	virtual tint32			GetTaskType()const{return TASK_TYPE;}
public:

private:
	DBGuidData				m_GuidData;
};

POOLDEF_DECL(DBGuidTask);

#endif //_DBGuidTask_H_