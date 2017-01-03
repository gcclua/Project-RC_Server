//This code create by CodeEngine,don't modify
#ifndef _CityBuildingSlotTABLE_H
 #define _CityBuildingSlotTABLE_H
 
 #include "DBCTable.h"

class Table_CityBuildingSlot:public DBC_Recorder_Loader<Table_CityBuildingSlot,99999,1024>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_BUILDINGTYPE=2,
ID_UNLOCKLEVEL,
ID_EFFECT_1,
ID_EFFECT_2,
ID_EFFECT_3,
ID_EFFECT_4,
ID_EFFECT_5,
ID_TAB_CURCOL_COUNT,
MAX_ID=99999,
MAX_RECORD=1024
 };
 public:
 bool __Load(DBC_Loader &loader);

private:
 tint32 m_BuildingType;
 public:
 tint32 GetBuildingType() const { return m_BuildingType; }

public:
 tint32 getEffectCount() const { return 5; } 
 private:
 tint32 m_Effect[5];
 public:
 tint32 GetEffectbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<5) return m_Effect[idx];
 return -1;
 }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_UnlockLevel;
 public:
 tint32 GetUnlockLevel() const { return m_UnlockLevel; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CityBuildingSlot);
 
 //bool InitTable_CityBuildingSlotTable( const tchar* szFileName );
 //bool InitTable_CityBuildingSlotTableFromMemory( const DBCFile& rDB );
 //const Table_CityBuildingSlot* GetTable_CityBuildingSlotByID(tint32 id);
 //const Table_CityBuildingSlot* GetTable_CityBuildingSlotByIndex(tint32 index);
 //tint32 GetTable_CityBuildingSlotCount(void);


 #endif
