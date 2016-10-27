//This code create by CodeEngine,don't modify
#ifndef _CopySceneTABLE_H
 #define _CopySceneTABLE_H
 
 #include "DBCTable.h"

class Table_CopyScene:public DBC_Recorder_Loader<Table_CopyScene,1024,1025>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_NAME=2,
ID_DESCINFO,
ID_SCRIPTID,
ID_PLAYERSDEMANDMIN,
ID_PLAYERSDEMANDMAX,
ID_WAITTIME,
ID_HEARTBEATTIME,
ID_RULE1,
ID_RULE2,
ID_RULE3,
ID_RULE4,
ID_RULETEAM1,
ID_RULETEAM2,
ID_RULETEAM3,
ID_RULETEAM4,
ID_EXISTTIME,
ID_NOLEVELLIMIT,
ID_TAB_CURCOL_COUNT,
MAX_ID=1024,
MAX_RECORD=1025
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 const tchar* m_DescInfo;
 public:
 const tchar* GetDescInfo() const { return m_DescInfo; }

private:
 tint32 m_ExistTime;
 public:
 tint32 GetExistTime() const { return m_ExistTime; }

private:
 tint32 m_HeartbeatTime;
 public:
 tint32 GetHeartbeatTime() const { return m_HeartbeatTime; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

private:
 tint32 m_NoLevelLimit;
 public:
 tint32 GetNoLevelLimit() const { return m_NoLevelLimit; }

private:
 tint32 m_PlayersDemandMax;
 public:
 tint32 GetPlayersDemandMax() const { return m_PlayersDemandMax; }

private:
 tint32 m_PlayersDemandMin;
 public:
 tint32 GetPlayersDemandMin() const { return m_PlayersDemandMin; }

public:
 tint32 getRuleCount() const { return 4; } 
 private:
 tint32 m_Rule[4];
 public:
 tint32 GetRulebyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_Rule[idx];
 return -1;
 }

public:
 tint32 getRuleTeamCount() const { return 4; } 
 private:
 tint32 m_RuleTeam[4];
 public:
 tint32 GetRuleTeambyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<4) return m_RuleTeam[idx];
 return -1;
 }

private:
 tint32 m_ScriptID;
 public:
 tint32 GetScriptID() const { return m_ScriptID; }

private:
 tint32 m_WaitTime;
 public:
 tint32 GetWaitTime() const { return m_WaitTime; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CopyScene);
 
 //bool InitTable_CopySceneTable( const tchar* szFileName );
 //bool InitTable_CopySceneTableFromMemory( const DBCFile& rDB );
 //const Table_CopyScene* GetTable_CopySceneByID(tint32 id);
 //const Table_CopyScene* GetTable_CopySceneByIndex(tint32 index);
 //tint32 GetTable_CopySceneCount(void);


 #endif
