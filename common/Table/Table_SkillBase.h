//This code create by CodeEngine,don't modify
#ifndef _SkillBaseTABLE_H
 #define _SkillBaseTABLE_H
 
 #include "DBCTable.h"

class Table_SkillBase:public DBC_Recorder_Loader<Table_SkillBase,1000,1000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_NAME=2,
ID_ISSHOWSKILLNAME,
ID_ICON ,
ID_SKILLCLASS,
ID_USETYPE,
ID_ISMOVE,
ID_ISMOVEBREAK,
ID_ISSKILLBREAK,
ID_ISBREAKBEATTACKED,
ID_TARGETTYPE,
ID_SELLOGIC,
ID_ISPLAYATTACKSOUND,
ID_ISNEEDSTOPEFFECTID,
ID_ISTARGETDIEBREAK,
ID_TAB_CURCOL_COUNT,
MAX_ID=1000,
MAX_RECORD=1000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 const tchar* m_Icon ;
 public:
 const tchar* GetIcon () const { return m_Icon ; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_IsBreakBeAttacked;
 public:
 tint32 GetIsBreakBeAttacked() const { return m_IsBreakBeAttacked; }

private:
 tint32 m_IsMove;
 public:
 tint32 GetIsMove() const { return m_IsMove; }

private:
 tint32 m_IsMoveBreak;
 public:
 tint32 GetIsMoveBreak() const { return m_IsMoveBreak; }

private:
 tint32 m_IsNeedStopEffectId;
 public:
 tint32 GetIsNeedStopEffectId() const { return m_IsNeedStopEffectId; }

private:
 tint32 m_IsPlayAttackSound;
 public:
 tint32 GetIsPlayAttackSound() const { return m_IsPlayAttackSound; }

private:
 tint32 m_IsShowSkillName;
 public:
 tint32 GetIsShowSkillName() const { return m_IsShowSkillName; }

private:
 tint32 m_IsSkillBreak;
 public:
 tint32 GetIsSkillBreak() const { return m_IsSkillBreak; }

private:
 tint32 m_IsTargetDieBreak;
 public:
 tint32 GetIsTargetDieBreak() const { return m_IsTargetDieBreak; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

private:
 tint32 m_SelLogic;
 public:
 tint32 GetSelLogic() const { return m_SelLogic; }

private:
 tint32 m_SkillClass;
 public:
 tint32 GetSkillClass() const { return m_SkillClass; }

private:
 tint32 m_TargetType;
 public:
 tint32 GetTargetType() const { return m_TargetType; }

private:
 tint32 m_UseType;
 public:
 tint32 GetUseType() const { return m_UseType; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SkillBase);
 
 //bool InitTable_SkillBaseTable( const tchar* szFileName );
 //bool InitTable_SkillBaseTableFromMemory( const DBCFile& rDB );
 //const Table_SkillBase* GetTable_SkillBaseByID(tint32 id);
 //const Table_SkillBase* GetTable_SkillBaseByIndex(tint32 index);
 //tint32 GetTable_SkillBaseCount(void);


 #endif
