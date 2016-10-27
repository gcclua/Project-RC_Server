//This code create by CodeEngine,don't modify
#ifndef _SnareObjBuffInfoTABLE_H
 #define _SnareObjBuffInfoTABLE_H
 
 #include "DBCTable.h"

class Table_SnareObjBuffInfo:public DBC_Recorder_Loader<Table_SnareObjBuffInfo,1000,1000>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_IMPACTID=2,
ID_DELAYTIME,
ID_SCANINTERVALTIME,
ID_MAXEFFECTTIME,
ID_ISEFFECTBYHIT,
ID_VALIDRADIUS,
ID_MAXVALIDNUM,
ID_TAB_CURCOL_COUNT,
MAX_ID=1000,
MAX_RECORD=1000
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_DelayTime;
 public:
 tint32 GetDelayTime() const { return m_DelayTime; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_ImpactId;
 public:
 tint32 GetImpactId() const { return m_ImpactId; }

private:
 tint32 m_IsEffectByHit;
 public:
 tint32 GetIsEffectByHit() const { return m_IsEffectByHit; }

private:
 tint32 m_MaxEffectTime;
 public:
 tint32 GetMaxEffectTime() const { return m_MaxEffectTime; }

private:
 tint32 m_MaxValidNum;
 public:
 tint32 GetMaxValidNum() const { return m_MaxValidNum; }

private:
 tint32 m_ScanIntervalTime;
 public:
 tint32 GetScanIntervalTime() const { return m_ScanIntervalTime; }

private:
 tint32 m_ValidRadius;
 public:
 tint32 GetValidRadius() const { return m_ValidRadius; }

};
 
 DECL_TABLE_FUNCTIONS(Table_SnareObjBuffInfo);
 
 //bool InitTable_SnareObjBuffInfoTable( const tchar* szFileName );
 //bool InitTable_SnareObjBuffInfoTableFromMemory( const DBCFile& rDB );
 //const Table_SnareObjBuffInfo* GetTable_SnareObjBuffInfoByID(tint32 id);
 //const Table_SnareObjBuffInfo* GetTable_SnareObjBuffInfoByIndex(tint32 index);
 //tint32 GetTable_SnareObjBuffInfoCount(void);


 #endif
