//This code create by CodeEngine,don't modify
#ifndef _SkillActiveTABLE_H
 #define _SkillActiveTABLE_H
 
 #include "DBCTable.h"

class Table_SkillActive:public DBC_Recorder_Loader<Table_SkillActive,50,50>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_INDEX,
ID_SKILLID=2,
ID_LEVEL,
ID_SKILLINDEX,
ID_TAB_CURCOL_COUNT,
MAX_ID=50,
MAX_RECORD=50
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Index;
 public:
 tint32 GetIndex() const { return m_Index; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

private:
 tint32 m_SKillIndex;
 public:
 tint32 GetSKillIndex() const { return m_SKillIndex; }

private:
 tint32 m_SkillId;
 public:
 tint32 GetSkillId() const { return m_SkillId; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SkillActive);
 
 //bool InitTable_SkillActiveTable( const tchar* szFileName );
 //bool InitTable_SkillActiveTableFromMemory( const DBCFile& rDB );
 //const Table_SkillActive* GetTable_SkillActiveByID(tint32 id);
 //const Table_SkillActive* GetTable_SkillActiveByIndex(tint32 index);
 //tint32 GetTable_SkillActiveCount(void);


 #endif
