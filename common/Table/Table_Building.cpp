//This code create by CodeEngine,don't modify
#include "Table_Building.h"




bool Table_Building::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "Building Columns Differ"); 
 loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_ModelID,(tint32)ID_MODELID);
loader.ReadDirect(m_SlotType,(tint32)ID_SLOTTYPE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_Building);



