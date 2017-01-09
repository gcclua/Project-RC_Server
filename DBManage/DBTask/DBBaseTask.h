#ifndef _DBBASETASK_H_
#define _DBBASETASK_H_
#pragma once

#include "Base.h"
#include "DataBase/LibMemInterface.h"
#include "DataBase/ODBCInterface.h"

class DBBaseTask
{
public:
	enum 
	{
		OPERATION_TYPE_UNKNOW = -1,
		OPERATION_TYPE_LOAD = 0,
		OPERATION_TYPE_SAVE_MEM,
		OPERATION_TYPE_SAVE_DB,
	};

public:
	DBBaseTask(void);
	virtual ~DBBaseTask(void);

public:
	// ִ�����ݿ��д����
	virtual bool Execute(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);

	// ��ȡ��ǰ����������
	virtual int  GetTaskType() const = 0;
protected:
	virtual bool Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface){return false;}
	virtual bool Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface){return false;}

	virtual void SendOpResult(uint32 ServiceId,uint32 retVal) const;


public:
	inline void   SetOperationType(int val){m_OperationType=val;}
	inline int    GetOperationType() const{return m_OperationType;}
	inline void   SetOptTime(tuint32 val){m_ReqOptTime=val;}
	inline tuint32 GetOptTime()const{return m_ReqOptTime;}
	inline void   SetKey(int64 val){m_key=val;}
	inline int64  GetKey(){return m_key;}
	inline bool   IsForLoad() const{return OPERATION_TYPE_LOAD==m_OperationType;}
	inline bool   IsForSave() const{return (OPERATION_TYPE_SAVE_MEM==m_OperationType || OPERATION_TYPE_SAVE_DB==m_OperationType);}
	inline void   SetRetServiceID(int val){m_RetServieID=val;}
	inline int    GetRetServiceID() const {return m_RetServieID;}
	inline void   SetSaveFail(bool val) {m_SaveFail = val;}
	inline bool   GetSaveFail() const {return m_SaveFail;}
private:
	int      m_OperationType; //��������
	tuint32  m_ReqOptTime;    // ����ʱ��
	int      m_RetServieID;   // ��Ҫ�ѽ�����ص�ServiceID
	int64    m_key;         // key
	bool     m_SaveFail;     // Task�Ƿ�洢ʧ��
};

typedef boost::shared_ptr<DBBaseTask> DBBaseTaskPtr;
typedef std::list<DBBaseTaskPtr>      DBBaseTaskPtrList;
typedef std::map<int64,DBBaseTaskPtr> DBBaseTaskPtrMap;
typedef std::map<int64,tuint32>       DBLastSaveDBTimeMap;

#endif
