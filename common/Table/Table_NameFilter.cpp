//This code create by CodeEngine,don't modify
#include "Table_NameFilter.h"



bool Table_NameFilter::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "NameFilter Columns Differ"); 
 loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_Name,(tint32)ID_NAME);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_NameFilter);



