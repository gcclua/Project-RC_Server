//This code create by CodeEngine,don't modify
#include "Table_CityBuildingSlot.h"





bool Table_CityBuildingSlot::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CityBuildingSlot Columns Differ"); 
 loader.ReadDirect(m_BuildingType,(tint32)ID_BUILDINGTYPE);
loader.ReadDirect(m_Effect[0],(tint32)ID_EFFECT_1);
loader.ReadDirect(m_Effect[1],(tint32)ID_EFFECT_2);
loader.ReadDirect(m_Effect[2],(tint32)ID_EFFECT_3);
loader.ReadDirect(m_Effect[3],(tint32)ID_EFFECT_4);
loader.ReadDirect(m_Effect[4],(tint32)ID_EFFECT_5);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_UnlockLevel,(tint32)ID_UNLOCKLEVEL);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_CityBuildingSlot);



