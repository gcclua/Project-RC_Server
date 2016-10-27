//This code create by CodeEngine,don't modify
#ifndef _NameFilterTABLE_H
 #define _NameFilterTABLE_H
 
 #include "DBCTable.h"

class Table_NameFilter:public DBC_Recorder_Loader<Table_NameFilter,20480,20481>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_NAME=2,
ID_TAB_CURCOL_COUNT,
MAX_ID=20480,
MAX_RECORD=20481
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

};
 
 DECL_TABLE_FUNCTIONS(Table_NameFilter);
 
 //bool InitTable_NameFilterTable( const tchar* szFileName );
 //bool InitTable_NameFilterTableFromMemory( const DBCFile& rDB );
 //const Table_NameFilter* GetTable_NameFilterByID(tint32 id);
 //const Table_NameFilter* GetTable_NameFilterByIndex(tint32 index);
 //tint32 GetTable_NameFilterCount(void);


 #endif
