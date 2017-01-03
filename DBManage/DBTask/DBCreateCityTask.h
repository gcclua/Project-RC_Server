#ifndef _DBCreateCityTask_H_
#define _DBCreateCityTask_H_

#include "DBBaseTask.h"
#include "Scene/GameDefine_Scene.h"
#include "DBStruct/DBStruct_CityCreate.h"
/*******************************************************************************/
//DBTaskע�����
//	1���̳���DBBaseTask
//	2����һ���������͵�ö�٣�TASK_TYPE��ֵ��DB_TASK_TYPEö���е�����ֵ��
//	3��������Protected���͵��麯��Load��Save��SendOpResult����������ʵ�֡�
//	4����һ�����������麯��GetTaskType�����飬����ʵ�֡�
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