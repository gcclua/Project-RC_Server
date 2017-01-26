//This code create by CodeEngine,don't modify
#ifndef _HeroTABLE_H
 #define _HeroTABLE_H
 
 #include "DBCTable.h"

class Table_Hero:public DBC_Recorder_Loader<Table_Hero,20,20>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_MODELID=2,
ID_PORTRAIT,
ID_MODELSIZE,
ID_SIZE,
ID_ACTIONID,
ID_INITQUALITY,
ID_TYPE,
ID_DATAID1,
ID_DATAID2,
ID_DATAID3,
ID_DATAID4,
ID_DATAID5,
ID_DATAID6,
ID_DATAID7,
ID_DATAID8,
ID_DATAID9,
ID_DATAID10,
ID_TAB_CURCOL_COUNT,
MAX_ID=20,
MAX_RECORD=20
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_ActionId;
 public:
 tint32 GetActionId() const { return m_ActionId; }

public:
 tint32 getDataIDCount() const { return 10; } 
 private:
 tint32 m_DataID[10];
 public:
 tint32 GetDataIDbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<10) return m_DataID[idx];
 return -1;
 }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_InitQuality;
 public:
 tint32 GetInitQuality() const { return m_InitQuality; }

private:
 tint32 m_ModelID;
 public:
 tint32 GetModelID() const { return m_ModelID; }

private:
 tint32 m_ModelSize;
 public:
 tint32 GetModelSize() const { return m_ModelSize; }

private:
 const tchar* m_Portrait;
 public:
 const tchar* GetPortrait() const { return m_Portrait; }

private:
 tint32 m_Size;
 public:
 tint32 GetSize() const { return m_Size; }

private:
 tint32 m_Type;
 public:
 tint32 GetType() const { return m_Type; }

};
 
 DECL_TABLE_FUNCTIONS(Table_Hero);
 
 //bool InitTable_HeroTable( const tchar* szFileName );
 //bool InitTable_HeroTableFromMemory( const DBCFile& rDB );
 //const Table_Hero* GetTable_HeroByID(tint32 id);
 //const Table_Hero* GetTable_HeroByIndex(tint32 index);
 //tint32 GetTable_HeroCount(void);


 #endif
