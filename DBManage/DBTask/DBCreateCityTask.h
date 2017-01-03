#ifndef _DBCreateCityTask_H_
#define _DBCreateCityTask_H_

#include "DBBaseTask.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_CityCreate.h"
/*******************************************************************************/
//DBTask注意事项：
//	1）继承自DBBaseTask
//	2）有一个公有类型的枚举，TASK_TYPE，值是DB_TASK_TYPE枚举中的类型值。
//	3）有三个Protected类型的虚函数Load，Save，SendOpResult。根据需求实现。
//	4）有一个公有类型虚函数GetTaskType，纯虚，必须实现。
/*******************************************************************************/
class DBCreateCityTask : public DBBaseTask
{
public:
	enum
	{
		TASK_TYPE =   DB_TASK_CREATERCITY,
	};
public:
	DBCreateCityTask(void);
	virtual ~DBCreateCityTask(void);

public:
	const int64 			GetUserGuid()const{return m_Data.m_UserId;}
	void					SetAccName(const ACCOUNTNAME& val) {m_AccName = val;}
	const ACCOUNTNAME&		GetAccName()const{return m_AccName;}

public:
	bool					Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface);
	virtual tint32			GetTaskType()const{return TASK_TYPE;}
	
public:
	void					SetData(const DBCityCreate& rSour);
	void					DataCleanUp();

	void					SetPlayerId(int val){m_nPlayerID = val;}
	int						GetPlayerId() const {return m_nPlayerID;}

private:
	DBCityCreate   m_Data;
	ACCOUNTNAME	   m_AccName;
	int            m_nPlayerID;
};

POOLDEF_DECL(DBCreateCityTask);

#endif //_DBUserTask_H_