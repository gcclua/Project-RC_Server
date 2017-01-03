//This code create by CodeEngine,don't modify
#ifndef _CopySceneRuleTABLE_H
 #define _CopySceneRuleTABLE_H
 
 #include "DBCTable.h"

class Table_CopySceneRule:public DBC_Recorder_Loader<Table_CopySceneRule,1024,1025>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_LEVEL=2,
ID_NUMBER,
ID_EXISTTIME,
ID_FIVESTARDIECOUNTSTRDICID,
ID_FIVESTARTIMESTRDICID,
ID_STARTTIME,
ID_ENDTIME,
ID_TAB_CURCOL_COUNT,
MAX_ID=1024,
MAX_RECORD=1025
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_EndTime;
 public:
 tint32 GetEndTime() const { return m_EndTime; }

private:
 tint32 m_ExistTime;
 public:
 tint32 GetExistTime() const { return m_ExistTime; }

private:
 tint32 m_FiveStarDieCountStrDicID;
 public:
 tint32 GetFiveStarDieCountStrDicID() const { return m_FiveStarDieCountStrDicID; }

private:
 tint32 m_FiveStarTimeStrDicID;
 public:
 tint32 GetFiveStarTimeStrDicID() const { return m_FiveStarTimeStrDicID; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_Number;
 public:
 tint32 GetNumber() const { return m_Number; }

private:
 tint32 m_StartTime;
 public:
 tint32 GetStartTime() const { return m_StartTime; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CopySceneRule);
 
 //bool InitTable_CopySceneRuleTable( const tchar* szFileName );
 //bool InitTable_CopySceneRuleTableFromMemory( const DBCFile& rDB );
 //const Table_CopySceneRule* GetTable_CopySceneRuleByID(tint32 id);
 //const Table_CopySceneRule* GetTable_CopySceneRuleByIndex(tint32 index);
 //tint32 GetTable_CopySceneRuleCount(void);


 #endif
