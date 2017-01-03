//This code create by CodeEngine,don't modify
#ifndef _BuildingTABLE_H
 #define _BuildingTABLE_H
 
 #include "DBCTable.h"

class Table_Building:public DBC_Recorder_Loader<Table_Building,20,20>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_MODELID=2,
ID_SLOTTYPE,
ID_TAB_CURCOL_COUNT,
MAX_ID=20,
MAX_RECORD=20
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_ModelID;
 public:
 tint32 GetModelID() const { return m_ModelID; }

private:
 tint32 m_SlotType;
 public:
 tint32 GetSlotType() const { return m_SlotType; }

};
 
 DECL_TABLE_FUNCTIONS(Table_Building);
 
 //bool InitTable_BuildingTable( const tchar* szFileName );
 //bool InitTable_BuildingTableFromMemory( const DBCFile& rDB );
 //const Table_Building* GetTable_BuildingByID(tint32 id);
 //const Table_Building* GetTable_BuildingByIndex(tint32 index);
 //tint32 GetTable_BuildingCount(void);


 #endif
