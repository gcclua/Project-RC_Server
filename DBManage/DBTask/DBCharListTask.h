#ifndef _DBCharListTask_H_
#define _DBCharListTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_CharList.h"
/*******************************************************************************/
//DBTask注意事项：
//	1）继承自DBBaseTask
//	2）有一个公有类型的枚举，TASK_TYPE，值是DB_TASK_TYPE枚举中的类型值。
//	3）有三个Protected类型的虚函数Load，Save，SendOpResult。根据需求实现。
//	4）有一个公有类型虚函数GetTaskType，纯虚，必须实现。
/*******************************************************************************/
class DBCharListTask : public DBBaseTask
{
public:
	enum
	{
		TASK_TYPE =   DB_TASK_CHARLIST,
	};
public:
	DBCharListTask(void);
	virtual ~DBCharListTask(void);

public:
	virtual tint32			GetTaskType()const{return TASK_TYPE;}
	
public:
	void					SetData(const ACCOUNTNAME& rSour);
	const ACCOUNTNAME&		GetData()const;
	void					SetPlayerID(tint32 val) {m_nPlayerID = val;}
	tint32		            GetPlayerID()const{return m_nPlayerID;}

protected:
	virtual bool			Load(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface);

private:
	ACCOUNTNAME	   m_AccName;
	DBCharDataList m_CharDataList;
	tint32         m_nPlayerID;
};

POOLDEF_DECL(DBCharListTask);

#endif //_DBCharListTask_H_