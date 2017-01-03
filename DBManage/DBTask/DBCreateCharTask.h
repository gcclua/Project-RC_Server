#ifndef _DBCreateCharTask_H_
#define _DBCreateCharTask_H_

#include "DBBaseTask.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_User.h"
/*******************************************************************************/
//DBTaskע�����
//	1���̳���DBBaseTask
//	2����һ���������͵�ö�٣�TASK_TYPE��ֵ��DB_TASK_TYPEö���е�����ֵ��
//	3��������Protected���͵��麯��Load��Save��SendOpResult����������ʵ�֡�
//	4����һ�����������麯��GetTaskType�����飬����ʵ�֡�
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