//This code create by CodeEngine,don't modify
#ifndef _InitialCombatAttrTABLE_H
 #define _InitialCombatAttrTABLE_H
 
 #include "DBCTable.h"

class Table_InitialCombatAttr:public DBC_Recorder_Loader<Table_InitialCombatAttr,1000,1000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_PROFESSIONID=2,
ID_LEVEL,
ID_MAXHP,
ID_MAXMP,
ID_MAXXP,
ID_PATTACK,
ID_MATTACK,
ID_PDEFENSE,
ID_MDEFENSE,
ID_HIT,
ID_DODGE,
ID_CRITICAL,
ID_DECRITICAL,
ID_STRIKE,
ID_DUCTICAL,
ID_CRITIADD,
ID_CRITIMIS,
ID_ATTACKSPEED,
ID_MOVESPEED,
ID_TAB_CURCOL_COUNT,
MAX_ID=1000,
MAX_RECORD=1000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_AttackSpeed;
 public:
 tint32 GetAttackSpeed() const { return m_AttackSpeed; }

private:
 tint32 m_CritiAdd;
 public:
 tint32 GetCritiAdd() const { return m_CritiAdd; }

private:
 tint32 m_CritiMis;
 public:
 tint32 GetCritiMis() const { return m_CritiMis; }

private:
 tint32 m_Critical;
 public:
 tint32 GetCritical() const { return m_Critical; }

private:
 tint32 m_DeCritical;
 public:
 tint32 GetDeCritical() const { return m_DeCritical; }

private:
 tint32 m_Dodge;
 public:
 tint32 GetDodge() const { return m_Dodge; }

private:
 tint32 m_Ductical;
 public:
 tint32 GetDuctical() const { return m_Ductical; }

private:
 tint32 m_Hit;
 public:
 tint32 GetHit() const { return m_Hit; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

private:
 tint32 m_MAttack;
 public:
 tint32 GetMAttack() const { return m_MAttack; }

private:
 tint32 m_MaxHp;
 public:
 tint32 GetMaxHp() const { return m_MaxHp; }

private:
 tint32 m_MaxMP;
 public:
 tint32 GetMaxMP() const { return m_MaxMP; }

private:
 tint32 m_MaxXP;
 public:
 tint32 GetMaxXP() const { return m_MaxXP; }

private:
 tint32 m_Mdefense;
 public:
 tint32 GetMdefense() const { return m_Mdefense; }

private:
 tint32 m_MoveSpeed;
 public:
 tint32 GetMoveSpeed() const { return m_MoveSpeed; }

private:
 tint32 m_PAttack;
 public:
 tint32 GetPAttack() const { return m_PAttack; }

private:
 tint32 m_PDefense;
 public:
 tint32 GetPDefense() const { return m_PDefense; }

private:
 tint32 m_ProfessionId;
 public:
 tint32 GetProfessionId() const { return m_ProfessionId; }

private:
 tint32 m_Strike;
 public:
 tint32 GetStrike() const { return m_Strike; }

};
 
 DECL_TABLE_FUNCTIONS(Table_InitialCombatAttr);
 
 //bool InitTable_InitialCombatAttrTable( const tchar* szFileName );
 //bool InitTable_InitialCombatAttrTableFromMemory( const DBCFile& rDB );
 //const Table_InitialCombatAttr* GetTable_InitialCombatAttrByID(tint32 id);
 //const Table_InitialCombatAttr* GetTable_InitialCombatAttrByIndex(tint32 index);
 //tint32 GetTable_InitialCombatAttrCount(void);


 #endif
