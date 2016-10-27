//This code create by CodeEngine,don't modify
#ifndef _SnareObjInfoTABLE_H
 #define _SnareObjInfoTABLE_H
 
 #include "DBCTable.h"

class Table_SnareObjInfo:public DBC_Recorder_Loader<Table_SnareObjInfo,1000,1000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_CHARMODELID=2,
ID_STEALTHLEV,
ID_ISOWNERCANSEE,
ID_ISACTIVATECANSEE,
ID_ISDELOWNERLEAVE,
ID_ALIVEEFFECTID1,
ID_ALIVEEFFECTID2,
ID_ALIVEEFFECTID3,
ID_ALIVESOUNDID1,
ID_ALIVESOUNDID2,
ID_ALIVESOUNDID3,
ID_ACTIVATEEFFECTID,
ID_ACTIVATESOUND,
ID_DEADEFFECTID,
ID_DEADSOUND,
ID_LIFETIME,
ID_DELAYTIME,
ID_ACTIVATEMODEL,
ID_ACTIVATERADIUS,
ID_TARGETTYPE,
ID_BUFFINDEX1,
ID_BUFFINDEX2,
ID_BUFFINDEX3,
ID_BUFFINDEX4,
ID_BUFFINDEX5,
ID_BUFFINDEX6,
ID_TAB_CURCOL_COUNT,
MAX_ID=1000,
MAX_RECORD=1000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_ActivateEffectId;
 public:
 tint32 GetActivateEffectId() const { return m_ActivateEffectId; }

private:
 tint32 m_ActivateModel;
 public:
 tint32 GetActivateModel() const { return m_ActivateModel; }

private:
 tint32 m_ActivateRadius;
 public:
 tint32 GetActivateRadius() const { return m_ActivateRadius; }

private:
 tint32 m_ActivateSound;
 public:
 tint32 GetActivateSound() const { return m_ActivateSound; }

public:
 tint32 getAliveEffectIdCount() const { return 3; } 
 private:
 tint32 m_AliveEffectId[3];
 public:
 tint32 GetAliveEffectIdbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_AliveEffectId[idx];
 return -1;
 }

public:
 tint32 getAliveSoundIdCount() const { return 3; } 
 private:
 tint32 m_AliveSoundId[3];
 public:
 tint32 GetAliveSoundIdbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_AliveSoundId[idx];
 return -1;
 }

public:
 tint32 getBUffIndexCount() const { return 6; } 
 private:
 tint32 m_BUffIndex[6];
 public:
 tint32 GetBUffIndexbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<6) return m_BUffIndex[idx];
 return -1;
 }

private:
 tint32 m_CharModelId;
 public:
 tint32 GetCharModelId() const { return m_CharModelId; }

private:
 tint32 m_DeadEffectId;
 public:
 tint32 GetDeadEffectId() const { return m_DeadEffectId; }

private:
 tint32 m_DeadSound;
 public:
 tint32 GetDeadSound() const { return m_DeadSound; }

private:
 tint32 m_DelayTime;
 public:
 tint32 GetDelayTime() const { return m_DelayTime; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_IsActivateCanSee;
 public:
 tint32 GetIsActivateCanSee() const { return m_IsActivateCanSee; }

private:
 tint32 m_IsDelOwnerLeave;
 public:
 tint32 GetIsDelOwnerLeave() const { return m_IsDelOwnerLeave; }

private:
 tint32 m_IsOwnerCanSee;
 public:
 tint32 GetIsOwnerCanSee() const { return m_IsOwnerCanSee; }

private:
 tint32 m_LifeTime;
 public:
 tint32 GetLifeTime() const { return m_LifeTime; }

private:
 tint32 m_StealthLev;
 public:
 tint32 GetStealthLev() const { return m_StealthLev; }

private:
 tint32 m_TargetType;
 public:
 tint32 GetTargetType() const { return m_TargetType; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SnareObjInfo);
 
 //bool InitTable_SnareObjInfoTable( const tchar* szFileName );
 //bool InitTable_SnareObjInfoTableFromMemory( const DBCFile& rDB );
 //const Table_SnareObjInfo* GetTable_SnareObjInfoByID(tint32 id);
 //const Table_SnareObjInfo* GetTable_SnareObjInfoByIndex(tint32 index);
 //tint32 GetTable_SnareObjInfoCount(void);


 #endif
