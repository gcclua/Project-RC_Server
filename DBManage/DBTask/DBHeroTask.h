#ifndef _DBHeroTask_H_
#define _DBHeroTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_Hero.h"
/*******************************************************************************/
//DBTask注意事项：
//	1）继承自DBBaseTask
//	2）有一个公有类型的枚举，TASK_TYPE，值是DB_TASK_TYPE枚举中的类型值。
//	3）有三个Protected类型的虚函数Load，Save，SendOpResult。根据需求实现。
//	4）有一个公有类型虚函数GetTaskType，纯虚，必须实现。
/*******************************************************************************/
class DBHeroTask : public DBBaseTask
{
public:
	enum
	{
		TASK_TYPE =   DB_TASK_HERO,
	};
public:
	DBHeroTask(void){};
	virtual ~DBHeroTask(void){};
public:
	void				SetData(const DBHero& val);
	const DBHero&		GetData()const{return m_Hero;}
public:
	virtual bool			Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface);
	virtual tint32			GetTaskType()const{return TASK_TYPE;}
public:

private:
	DBHero				m_Hero;
};

POOLDEF_DECL(DBHeroTask);

#endif //_DBGuidTask_H_