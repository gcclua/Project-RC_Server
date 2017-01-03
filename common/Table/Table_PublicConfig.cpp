//This code create by CodeEngine,don't modify
#include "Table_PublicConfig.h"






bool Table_PublicConfig::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "PublicConfig Columns Differ"); 
 loader.ReadDirect(m_FloatValue,(tint32)ID_FLOATVALUE);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_IntValue,(tint32)ID_INTVALUE);
loader.ReadDirect(m_Key,(tint32)ID_KEY);
loader.ReadDirect(m_StringValue,(tint32)ID_STRINGVALUE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_PublicConfig);



