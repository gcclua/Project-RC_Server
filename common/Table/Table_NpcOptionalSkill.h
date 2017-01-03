//This code create by CodeEngine,don't modify
#ifndef _NpcOptionalSkillTABLE_H
 #define _NpcOptionalSkillTABLE_H
 
 #include "DBCTable.h"

class Table_NpcOptionalSkill:public DBC_Recorder_Loader<Table_NpcOptionalSkill,99999,500>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_SKILLID,
ID_SELETARGETLOGIC=2,
ID_ACTIVATELOGIC,
ID_ACTIVATEPARAM1,
ID_ACTIVATEPARAM2,
ID_TAB_CURCOL_COUNT,
MAX_ID=99999,
MAX_RECORD=500
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_ActivateLogic;
 public:
 tint32 GetActivateLogic() const { return m_ActivateLogic; }

public:
 tint32 getActivateParamCount() const { return 2; } 
 private:
 tint32 m_ActivateParam[2];
 public:
 tint32 GetActivateParambyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<2) return m_ActivateParam[idx];
 return -1;
 }

private:
 tint32 m_SeleTargetLogic;
 public:
 tint32 GetSeleTargetLogic() const { return m_SeleTargetLogic; }

private:
 tint32 m_SkillId;
 public:
 tint32 GetSkillId() const { return m_SkillId; }

};
 
 DECL_TABLE_FUNCTIONS(Table_NpcOptionalSkill);
 
 //bool InitTable_NpcOptionalSkillTable( const tchar* szFileName );
 //bool InitTable_NpcOptionalSkillTableFromMemory( const DBCFile& rDB );
 //const Table_NpcOptionalSkill* GetTable_NpcOptionalSkillByID(tint32 id);
 //const Table_NpcOptionalSkill* GetTable_NpcOptionalSkillByIndex(tint32 index);
 //tint32 GetTable_NpcOptionalSkillCount(void);


 #endif
