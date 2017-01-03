#ifndef _DBRandomNameTask_H_
#define _DBRandomNameTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_RandomName.h"
/*******************************************************************************/
//DBTaskע�����
//	1���̳���DBBaseTask
//	2����һ���������͵�ö�٣�TASK_TYPE��ֵ��DB_TASK_TYPEö���е�����ֵ��
//	3��������Protected���͵��麯��Load��Save��SendOpResult����������ʵ�֡�
//	4����һ�����������麯��GetTaskType�����飬����ʵ�֡�
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