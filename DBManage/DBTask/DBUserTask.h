#ifndef _DBUSERTASK_H_
#define _DBUSERTASK_H_
#pragma once

#include "DBBaseTask.h"

#include "Message/DBMsg.h"

class DBUserTask : public DBBaseTask
{
public:
	enum 
	{
		TASK_TYPE = DB_TASK_USER_DATA,
	};

public:
	DBUserTask(void);
	virtual ~DBUserTask(void);

public:
	void                 SetUserGuid(const int64& val) {m_UserGuid = val;}
	int64                GetUserGuid() const { return m_UserGuid;}
	void                 SetUserName(const string& val){m_UserName = val;}
	string               GetuserName() const {return m_UserName;}

	void                 SetImmediateSave(bool val){m_bImmediateSave=val;}
	bool                 GetImmediateSave() const {return m_bImmediateSave;}

	void                 SetFinalSave(bool val){m_bFinalSave = val;}
	bool                 GetFinalSave() const {return m_bFinalSave;}

public:

	// ��ȡ��ǰ����������
	virtual int           GetTaskType() const {return TASK_TYPE;};
public:
	void                  SetData(const DBFullUserData& rSource);
	const DBFullUserData& GetData() const;
	void                  DataCleanUp();

protected:
	virtual bool          Load(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);
	virtual bool          Save(ODBCInterface& rODBCInterface,LibMemInterface &rLibMemInterface);


protected:
	bool                  DBLoad(ODBCInterface &rODBCInterface);
	bool                  DBSave(ODBCInterface &rODBCInterface);
	bool                  MemLoad(LibMemInterface &rLibMemInterface);
	bool                  MemSave(LibMemInterface &rLibMemInterface);

public:
	
private:
	int64          m_UserGuid;        //��ҵ�uid
	string         m_UserName;       // ������� 
	DBFullUserData m_UserData;      // ��ҵ�����
	bool           m_bImmediateSave;
	bool           m_bFinalSave;

};

POOLDEF_DECL(DBUserTask);

#endif
