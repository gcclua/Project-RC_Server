//This code create by CodeEngine,don't modify
#ifndef _ImpactTABLE_H
 #define _ImpactTABLE_H
 
 #include "DBCTable.h"

class Table_Impact:public DBC_Recorder_Loader<Table_Impact,999999,30000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_IMPACTID,
ID_NAME=2,
ID_ISFOREVER,
ID_LIFETYPE,
ID_MAXOVERLAYCOUNT,
ID_ISNEEDNOTICECLIENT,
ID_BUFFICON,
ID_BUFFTYPE,
ID_DEBUFFPRI,
ID_LOGICID,
ID_DELAYTIME,
ID_EFFECTID,
ID_PLAYTIME,
ID_ISREMOVEEFFECTFADEOUT,
ID_FADEOUTRULE,
ID_MUTEXCOLLECTIONID,
ID_MUTEXPRIORITY,
ID_PARAMVALUE_01,
ID_PARAMVALUE_02,
ID_PARAMVALUE_03,
ID_PARAMVALUE_04,
ID_PARAMVALUE_05,
ID_PARAMVALUE_06,
ID_PARAMVALUE_07,
ID_PARAMVALUE_08,
ID_PARAMVALUE_09,
ID_PARAMVALUE_10,
ID_PARAMVALUE_11,
ID_PARAMVALUE_12,
ID_PARAMVALUE_13,
ID_PARAMVALUE_14,
ID_PARAMVALUE_15,
ID_TAB_CURCOL_COUNT,
MAX_ID=999999,
MAX_RECORD=30000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 const tchar* m_BuffIcon;
 public:
 const tchar* GetBuffIcon() const { return m_BuffIcon; }

private:
 tint32 m_BuffType;
 public:
 tint32 GetBuffType() const { return m_BuffType; }

private:
 tint32 m_DebuffPRI;
 public:
 tint32 GetDebuffPRI() const { return m_DebuffPRI; }

private:
 tint32 m_DelayTime;
 public:
 tint32 GetDelayTime() const { return m_DelayTime; }

private:
 tint32 m_EffectId;
 public:
 tint32 GetEffectId() const { return m_EffectId; }

private:
 tint32 m_FadeOutRule;
 public:
 tint32 GetFadeOutRule() const { return m_FadeOutRule; }

private:
 tint32 m_ImpactID;
 public:
 tint32 GetImpactID() const { return m_ImpactID; }

private:
 tint32 m_IsForever;
 public:
 tint32 GetIsForever() const { return m_IsForever; }

private:
 tint32 m_IsNeedNoticeClient;
 public:
 tint32 GetIsNeedNoticeClient() const { return m_IsNeedNoticeClient; }

private:
 tint32 m_IsRemoveEffectFadeOut;
 public:
 tint32 GetIsRemoveEffectFadeOut() const { return m_IsRemoveEffectFadeOut; }

private:
 tint32 m_LifeType;
 public:
 tint32 GetLifeType() const { return m_LifeType; }

private:
 tint32 m_LogicID;
 public:
 tint32 GetLogicID() const { return m_LogicID; }

private:
 tint32 m_MaxOverlayCount;
 public:
 tint32 GetMaxOverlayCount() const { return m_MaxOverlayCount; }

private:
 tint32 m_MutexcollectionId;
 public:
 tint32 GetMutexcollectionId() const { return m_MutexcollectionId; }

private:
 tint32 m_Mutexpriority;
 public:
 tint32 GetMutexpriority() const { return m_Mutexpriority; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

public:
 tint32 getParamValueCount() const { return 15; } 
 private:
 tint32 m_ParamValue[15];
 public:
 tint32 GetParamValuebyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<15) return m_ParamValue[idx];
 return -1;
 }

private:
 tint32 m_PlayTime;
 public:
 tint32 GetPlayTime() const { return m_PlayTime; }

};
 
 DECL_TABLE_FUNCTIONS(Table_Impact);
 
 //bool InitTable_ImpactTable( const tchar* szFileName );
 //bool InitTable_ImpactTableFromMemory( const DBCFile& rDB );
 //const Table_Impact* GetTable_ImpactByID(tint32 id);
 //const Table_Impact* GetTable_ImpactByIndex(tint32 index);
 //tint32 GetTable_ImpactCount(void);


 #endif
