//This code create by CodeEngine,don't modify
#ifndef _ServerConfigListTABLE_H
 #define _ServerConfigListTABLE_H
 
 #include "DBCTable.h"

class Table_ServerConfigList:public DBC_Recorder_Loader<Table_ServerConfigList,39999,40000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_WORLDTYPE=2,
ID_WORLDNAME,
ID_BATTLEWORLDID,
ID_STARTTIME,
ID_STARTTIMEFOREXPLIMIT,
ID_SELFIP,
ID_PORTFORCLIENT,
ID_PORTFORGMI,
ID_PORTFORNEWGM,
ID_PORTFORPARALLEL,
ID_THREADCOUNT,
ID_DBNAME,
ID_DBUSER,
ID_DBPSW,
ID_DBTHREADCOUNT,
ID_TAB_CURCOL_COUNT,
MAX_ID=39999,
MAX_RECORD=40000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_BattleWorldID;
 public:
 tint32 GetBattleWorldID() const { return m_BattleWorldID; }

private:
 const tchar* m_DBName;
 public:
 const tchar* GetDBName() const { return m_DBName; }

private:
 const tchar* m_DBPsw;
 public:
 const tchar* GetDBPsw() const { return m_DBPsw; }

private:
 tint32 m_DBThreadCount;
 public:
 tint32 GetDBThreadCount() const { return m_DBThreadCount; }

private:
 const tchar* m_DBUser;
 public:
 const tchar* GetDBUser() const { return m_DBUser; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_PortForClient;
 public:
 tint32 GetPortForClient() const { return m_PortForClient; }

private:
 tint32 m_PortForGMI;
 public:
 tint32 GetPortForGMI() const { return m_PortForGMI; }

private:
 tint32 m_PortForNewGM;
 public:
 tint32 GetPortForNewGM() const { return m_PortForNewGM; }

private:
 tint32 m_PortForParallel;
 public:
 tint32 GetPortForParallel() const { return m_PortForParallel; }

private:
 const tchar* m_SelfIp;
 public:
 const tchar* GetSelfIp() const { return m_SelfIp; }

private:
 const tchar* m_StartTime;
 public:
 const tchar* GetStartTime() const { return m_StartTime; }

private:
 const tchar* m_StartTimeForExpLimit;
 public:
 const tchar* GetStartTimeForExpLimit() const { return m_StartTimeForExpLimit; }

private:
 tint32 m_ThreadCount;
 public:
 tint32 GetThreadCount() const { return m_ThreadCount; }

private:
 const tchar* m_WorldName;
 public:
 const tchar* GetWorldName() const { return m_WorldName; }

private:
 tint32 m_WorldType;
 public:
 tint32 GetWorldType() const { return m_WorldType; }

};
 
 DECL_TABLE_FUNCTIONS(Table_ServerConfigList);
 
 //bool InitTable_ServerConfigListTable( const tchar* szFileName );
 //bool InitTable_ServerConfigListTableFromMemory( const DBCFile& rDB );
 //const Table_ServerConfigList* GetTable_ServerConfigListByID(tint32 id);
 //const Table_ServerConfigList* GetTable_ServerConfigListByIndex(tint32 index);
 //tint32 GetTable_ServerConfigListCount(void);


 #endif
