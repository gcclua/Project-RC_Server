#ifndef _DBWORDMAPTASK_H_
#define _DBWORDMAPTASK_H_
#pragma once

#include "DBBaseTask.h"
#include "DBStruct/DBStruct_WordMap.h"

class DBWorldMapTask : public DBBaseTask
{
public:
	enum 
	{
		TASK_TYPE = DB_TASK_WORDMAP,
	};

public:
	DBWorldMapTask(void);
	virtual ~DBWorldMapTask(void);

public:

public:

	// ��ȡ��ǰ����������
	virtual int           GetTaskType() const {return TASK_TYPE;};
public:
	void                  SetData(const DBTileDataPtr Ptr){m_DataPtr=Ptr;};
	const DBTileDataPtr& GetData() const{return m_DataPtr;}

protected:
	virtual bool          Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);
	virtual bool          Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);

public:
	
private:
	
	DBTileDataPtr m_DataPtr;      // ��ҵ�����

};

POOLDEF_DECL(DBWorldMapTask);

#endif
