//This code create by CodeEngine,don't modify
#ifndef _RoleBaseAttrTABLE_H
 #define _RoleBaseAttrTABLE_H
 
 #include "DBCTable.h"

class Table_RoleBaseAttr:public DBC_Recorder_Loader<Table_RoleBaseAttr,4096,4096>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_T,
ID_CHARMODELID=2,
ID_NAME,
ID_SEX,
ID_LEVEL,
ID_ATTACKDISTYPE,
ID_SKILLSTRATEGYINDEX,
ID_MAXHP,
ID_MAXXP,
ID_XPSPEED,
ID_DEFENSE,
ID_ATTACK,
ID_HIT,
ID_ATTACKTIME,
ID_MOVESPEED,
ID_CAMP,
ID_SELECTRADIUS,
ID_CORPSETIME,
ID_EXP,
ID_ISATTACKFLY,
ID_DIEEFFECTID,
ID_RAMPTYPE,
ID_ENHANCEID,
ID_UNITDATAID,
ID_TAB_CURCOL_COUNT,
MAX_ID=4096,
MAX_RECORD=4096
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Attack;
 public:
 tint32 GetAttack() const { return m_Attack; }

private:
 tint32 m_AttackDisType;
 public:
 tint32 GetAttackDisType() const { return m_AttackDisType; }

private:
 tint32 m_AttackTime;
 public:
 tint32 GetAttackTime() const { return m_AttackTime; }

private:
 tint32 m_Camp;
 public:
 tint32 GetCamp() const { return m_Camp; }

private:
 tint32 m_CharModelID;
 public:
 tint32 GetCharModelID() const { return m_CharModelID; }

private:
 tint32 m_CorpseTime;
 public:
 tint32 GetCorpseTime() const { return m_CorpseTime; }

private:
 tint32 m_Defense;
 public:
 tint32 GetDefense() const { return m_Defense; }

private:
 tint32 m_DieEffectID;
 public:
 tint32 GetDieEffectID() const { return m_DieEffectID; }

private:
 tint32 m_EnhanceID;
 public:
 tint32 GetEnhanceID() const { return m_EnhanceID; }

private:
 tint32 m_Exp;
 public:
 tint32 GetExp() const { return m_Exp; }

private:
 tint32 m_Hit;
 public:
 tint32 GetHit() const { return m_Hit; }

private:
 tint32 m_IsAttackFly;
 public:
 tint32 GetIsAttackFly() const { return m_IsAttackFly; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

private:
 tint32 m_MaxHP;
 public:
 tint32 GetMaxHP() const { return m_MaxHP; }

private:
 tint32 m_MaxXP;
 public:
 tint32 GetMaxXP() const { return m_MaxXP; }

private:
 tint32 m_MoveSpeed;
 public:
 tint32 GetMoveSpeed() const { return m_MoveSpeed; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

private:
 tint32 m_RampType;
 public:
 tint32 GetRampType() const { return m_RampType; }

private:
 tfloat32 m_SelectRadius;
 public:
 tfloat32 GetSelectRadius() const { return m_SelectRadius; }

private:
 tint32 m_Sex;
 public:
 tint32 GetSex() const { return m_Sex; }

private:
 tint32 m_SkillstrategyIndex;
 public:
 tint32 GetSkillstrategyIndex() const { return m_SkillstrategyIndex; }

private:
 tint32 m_UnitDataID;
 public:
 tint32 GetUnitDataID() const { return m_UnitDataID; }

private:
 tint32 m_XpSpeed;
 public:
 tint32 GetXpSpeed() const { return m_XpSpeed; }

private:
 tint32 m_T;
 public:
 tint32 GetT() const { return m_T; }

};
 
 DECL_TABLE_FUNCTIONS(Table_RoleBaseAttr);
 
 //bool InitTable_RoleBaseAttrTable( const tchar* szFileName );
 //bool InitTable_RoleBaseAttrTableFromMemory( const DBCFile& rDB );
 //const Table_RoleBaseAttr* GetTable_RoleBaseAttrByID(tint32 id);
 //const Table_RoleBaseAttr* GetTable_RoleBaseAttrByIndex(tint32 index);
 //tint32 GetTable_RoleBaseAttrCount(void);


 #endif
