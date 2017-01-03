//This code create by CodeEngine,don't modify
#include "Table_CityBuildingLevel.h"
















bool Table_CityBuildingLevel::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CityBuildingLevel Columns Differ"); 
 loader.ReadDirect(m_BuildingType,(tint32)ID_BUILDINGTYPE);
loader.ReadDirect(m_Description,(tint32)ID_DESCRIPTION);
loader.ReadDirect(m_Icon,(tint32)ID_ICON);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);
loader.ReadDirect(m_Name,(tint32)ID_NAME);
loader.ReadDirect(m_NeedBuilding[0],(tint32)ID_NEEDBUILDING1);
loader.ReadDirect(m_NeedBuilding[1],(tint32)ID_NEEDBUILDING2);
loader.ReadDirect(m_NeedBuilding[2],(tint32)ID_NEEDBUILDING3);
loader.ReadDirect(m_NeedFood,(tint32)ID_NEEDFOOD);
loader.ReadDirect(m_NeedGold,(tint32)ID_NEEDGOLD);
loader.ReadDirect(m_NeedIron,(tint32)ID_NEEDIRON);
loader.ReadDirect(m_NeedProsperity,(tint32)ID_NEEDPROSPERITY);
loader.ReadDirect(m_NeedStone,(tint32)ID_NEEDSTONE);
loader.ReadDirect(m_NeedTime,(tint32)ID_NEEDTIME);
loader.ReadDirect(m_Prosperity,(tint32)ID_PROSPERITY);
loader.ReadDirect(m_Res,(tint32)ID_RES);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_CityBuildingLevel);



