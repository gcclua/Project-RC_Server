#ifndef _DBCharListTask_H_
#define _DBCharListTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_CharList.h"
/*******************************************************************************/
//DBTaskע�����
//	1���̳���DBBaseTask
//	2����һ���������͵�ö�٣�TASK_TYPE��ֵ��DB_TASK_TYPEö���е�����ֵ��
//	3��������Protected���͵��麯��Load��Save��SendOpResult����������ʵ�֡�
//	4����һ�����������麯��GetTaskType�����飬����ʵ�֡�
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