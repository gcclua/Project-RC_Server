//This code create by CodeEngine,don't modify
#ifndef _CityBuildingLevelTABLE_H
 #define _CityBuildingLevelTABLE_H
 
 #include "DBCTable.h"

class Table_CityBuildingLevel:public DBC_Recorder_Loader<Table_CityBuildingLevel,99999,1024>
 {
 public:
 enum _ID
 {
 INVLAID_INDEX=-1,
ID_ID,
ID_BUILDINGTYPE=2,
ID_NAME,
ID_LEVEL,
ID_DESCRIPTION,
ID_ICON,
ID_RES,
ID_PROSPERITY,
ID_NEEDBUILDING1,
ID_NEEDBUILDING2,
ID_NEEDBUILDING3,
ID_NEEDPROSPERITY,
ID_NEEDTIME,
ID_NEEDSTONE,
ID_NEEDGOLD,
ID_NEEDIRON,
ID_NEEDFOOD,
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

private:
 const tchar* m_Description;
 public:
 const tchar* GetDescription() const { return m_Description; }

private:
 const tchar* m_Icon;
 public:
 const tchar* GetIcon() const { return m_Icon; }

private:
 tint32 m_Id;
 public:
 tint32 GetId() const { return m_Id; }

private:
 tint32 m_Level;
 public:
 tint32 GetLevel() const { return m_Level; }

private:
 const tchar* m_Name;
 public:
 const tchar* GetName() const { return m_Name; }

public:
 tint32 getNeedBuildingCount() const { return 3; } 
 private:
 tint32 m_NeedBuilding[3];
 public:
 tint32 GetNeedBuildingbyIndex(tint32 idx) const 
 {
 if(idx>=0 && idx<3) return m_NeedBuilding[idx];
 return -1;
 }

private:
 tint32 m_NeedFood;
 public:
 tint32 GetNeedFood() const { return m_NeedFood; }

private:
 tint32 m_NeedGold;
 public:
 tint32 GetNeedGold() const { return m_NeedGold; }

private:
 tint32 m_NeedIron;
 public:
 tint32 GetNeedIron() const { return m_NeedIron; }

private:
 tint32 m_NeedProsperity;
 public:
 tint32 GetNeedProsperity() const { return m_NeedProsperity; }

private:
 tint32 m_NeedStone;
 public:
 tint32 GetNeedStone() const { return m_NeedStone; }

private:
 tint32 m_NeedTime;
 public:
 tint32 GetNeedTime() const { return m_NeedTime; }

private:
 tint32 m_Prosperity;
 public:
 tint32 GetProsperity() const { return m_Prosperity; }

private:
 const tchar* m_Res;
 public:
 const tchar* GetRes() const { return m_Res; }

};
 
 DECL_TABLE_FUNCTIONS(Table_CityBuildingLevel);
 
 //bool InitTable_CityBuildingLevelTable( const tchar* szFileName );
 //bool InitTable_CityBuildingLevelTableFromMemory( const DBCFile& rDB );
 //const Table_CityBuildingLevel* GetTable_CityBuildingLevelByID(tint32 id);
 //const Table_CityBuildingLevel* GetTable_CityBuildingLevelByIndex(tint32 index);
 //tint32 GetTable_CityBuildingLevelCount(void);


 #endif
