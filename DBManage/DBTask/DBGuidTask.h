#ifndef _DBGuidTask_H_
#define _DBGuidTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct.h"
/*******************************************************************************/
//DBTaskע�����
//	1���̳���DBBaseTask
//	2����һ���������͵�ö�٣�TASK_TYPE��ֵ��DB_TASK_TYPEö���е�����ֵ��
//	3��������Protected���͵��麯��Load��Save��SendOpResult����������ʵ�֡�
//	4����һ�����������麯��GetTaskType�����飬����ʵ�֡�
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