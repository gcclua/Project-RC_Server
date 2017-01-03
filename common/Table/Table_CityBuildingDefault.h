//This code create by CodeEngine,don't modify
#ifndef _CityBuildingDefaultTABLE_H
 #define _CityBuildingDefaultTABLE_H
 
 #include "DBCTable.h"

class Table_CityBuildingDefault:public DBC_Recorder_Loader<Table_CityBuildingDefault,99999,1024>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_NAME=2,
ID_ISUPGRADE,
ID_MAXLEVEL,
ID_TAB_CURCOL_COUNT,
MAX_ID=99999,
MAX_RECORD=1024
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_IsUpgrade;
 public:
 tint32 GetIsUpgrade() const { return m_IsUpgrade; }

private:
 tint32 m_MaxLevel;
 public:
 tint32 GetMaxLevel() const { return m_MaxLevel; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CityBuildingDefault);
 
 //bool InitTable_CityBuildingDefaultTable( const tchar* szFileName );
 //bool InitTable_CityBuildingDefaultTableFromMemory( const DBCFile& rDB );
 //const Table_CityBuildingDefault* GetTable_CityBuildingDefaultByID(tint32 id);
 //const Table_CityBuildingDefault* GetTable_CityBuildingDefaultByIndex(tint32 index);
 //tint32 GetTable_CityBuildingDefaultCount(void);


 #endif
