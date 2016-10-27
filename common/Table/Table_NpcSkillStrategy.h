//This code create by CodeEngine,don't modify
#ifndef _NpcSkillStrategyTABLE_H
 #define _NpcSkillStrategyTABLE_H
 
 #include "DBCTable.h"

class Table_NpcSkillStrategy:public DBC_Recorder_Loader<Table_NpcSkillStrategy,1000,1000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_DEFAULTSKILLID=2,
ID_DEFAULTSKILLWEIGHT,
ID_ISHAVEOPTIONALSKILL,
ID_SKILLID1,
ID_SKILLID2,
ID_SKILLID3,
ID_SKILLID4,
ID_SKILLID5,
ID_SKILLID6,
ID_SKILLID7,
ID_TAB_CURCOL_COUNT,
MAX_ID=1000,
MAX_RECORD=1000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_DefaultSkillId;
 public:
 tint32 GetDefaultSkillId() const { return m_DefaultSkillId; }

private:
 tint32 m_DefaultSkillWeight;
 public:
 tint32 GetDefaultSkillWeight() const { return m_DefaultSkillWeight; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_IsHaveOptionalSkill;
 public:
 tint32 GetIsHaveOptionalSkill() const { return m_IsHaveOptionalSkill; }

public:
 tint32 getSkillIdCount() const { return 7; } 
 private:
 tint32 m_SkillId[7];
 public:
 tint32 GetSkillIdbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<7) return m_SkillId[idx];
 return -1;
 }

};
 
 DECL_TABLE_FUNCTIONS(Table_NpcSkillStrategy);
 
 //bool InitTable_NpcSkillStrategyTable( const tchar* szFileName );
 //bool InitTable_NpcSkillStrategyTableFromMemory( const DBCFile& rDB );
 //const Table_NpcSkillStrategy* GetTable_NpcSkillStrategyByID(tint32 id);
 //const Table_NpcSkillStrategy* GetTable_NpcSkillStrategyByIndex(tint32 index);
 //tint32 GetTable_NpcSkillStrategyCount(void);


 #endif
