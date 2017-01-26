#ifndef _DBHeroTask_H_
#define _DBHeroTask_H_

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_Hero.h"
/*******************************************************************************/
//DBTaskע�����
//	1���̳���DBBaseTask
//	2����һ���������͵�ö�٣�TASK_TYPE��ֵ��DB_TASK_TYPEö���е�����ֵ��
//	3��������Protected���͵��麯��Load��Save��SendOpResult����������ʵ�֡�
//	4����һ�����������麯��GetTaskType�����飬����ʵ�֡�
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