//This code create by CodeEngine,don't modify
#include "Table_CoolDownTime.h"



bool Table_CoolDownTime::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CoolDownTime Columns Differ"); 
 loader.ReadDirect(m_CDTime,(tint32)ID_CDTIME);
loader.ReadDirect(m_Id,(tint32)ID_ID);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_CoolDownTime);



