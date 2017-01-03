#ifndef _DBCreateCharTask_H_
#define _DBCreateCharTask_H_

#include "DBBaseTask.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_User.h"
/*******************************************************************************/
//DBTask注意事项：
//	1）继承自DBBaseTask
//	2）有一个公有类型的枚举，TASK_TYPE，值是DB_TASK_TYPE枚举中的类型值。
//	3）有三个Protected类型的虚函数Load，Save，SendOpResult。根据需求实现。
//	4）有一个公有类型虚函数GetTaskType，纯虚，必须实现。
/*******************************************************************************/
class DBCreateCharTask : public DBBaseTask
{
public:
	enum
	{
		TASK_TYPE =   DB_TASK_CREATERCHAR,
	};
public:
	DBCreateCharTask(void);
	virtual ~DBCreateCharTask(void);

public:
	void					SetUserGuid(int64 val) {m_UserData.SetGuid(val);}
	const int64 			GetUserGuid()const{return m_UserData.GetGuid();}
	void					SetAccName(const ACCOUNTNAME& val) {m_AccName = val;}
	const ACCOUNTNAME&		GetAccName()const{return m_AccName;}
	void					SetPlayerID(int val) {m_nPlayerID = val;}
	int                     GetPlayerID() const{return m_nPlayerID;}

public:
	bool					Execute(ODBCInterface &rODBCInterface, LibMemInterface &rLibMemInterface);
	virtual tint32			GetTaskType()const{return TASK_TYPE;}
	
public:
	void					SetData(const DBFullUserData& rSour);
	const DBFullUserData&	GetData()const;
	void					DataCleanUp();

private:
	DBFullUserData m_UserData;
	ACCOUNTNAME	   m_AccName;
	int         m_nPlayerID;
};

POOLDEF_DECL(DBCreateCharTask);

#endif //_DBUserTask_H_