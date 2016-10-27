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
ID_SELECTPARAM1,
ID_SELECTPARAM2,
ID_USETYPE,
ID_SKILLPRIORITY,
ID_WEIGHT,
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

public:
 tint32 getSelectParamCount() const { return 2; } 
 private:
 tint32 m_SelectParam[2];
 public:
 tint32 GetSelectParambyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<2) return m_SelectParam[idx];
 return -1;
 }

private:
 tint32 m_SkillId;
 public:
 tint32 GetSkillId() const { return m_SkillId; }

private:
 tint32 m_SkillPriority;
 public:
 tint32 GetSkillPriority() const { return m_SkillPriority; }

private:
 tint32 m_UseType;
 public:
 tint32 GetUseType() const { return m_UseType; }

private:
 tint32 m_Weight;
 public:
 tint32 GetWeight() const { return m_Weight; }

};
 
 DECL_TABLE_FUNCTIONS(Table_NpcOptionalSkill);
 
 //bool InitTable_NpcOptionalSkillTable( const tchar* szFileName );
 //bool InitTable_NpcOptionalSkillTableFromMemory( const DBCFile& rDB );
 //const Table_NpcOptionalSkill* GetTable_NpcOptionalSkillByID(tint32 id);
 //const Table_NpcOptionalSkill* GetTable_NpcOptionalSkillByIndex(tint32 index);
 //tint32 GetTable_NpcOptionalSkillCount(void);


 #endif
