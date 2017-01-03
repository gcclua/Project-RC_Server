//This code create by CodeEngine,don't modify
#include "Table_CityBuildingDefault.h"





bool Table_CityBuildingDefault::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CityBuildingDefault Columns Differ"); 
 loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_IsUpgrade,(tint32)ID_ISUPGRADE);
loader.ReadDirect(m_MaxLevel,(tint32)ID_MAXLEVEL);
loader.ReadDirect(m_Name,(tint32)ID_NAME);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_CityBuildingDefault);



