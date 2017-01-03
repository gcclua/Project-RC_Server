//This code create by CodeEngine,don't modify
#include "Table_CopySceneRule.h"









bool Table_CopySceneRule::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "CopySceneRule Columns Differ"); 
 loader.ReadDirect(m_EndTime,(tint32)ID_ENDTIME);
loader.ReadDirect(m_ExistTime,(tint32)ID_EXISTTIME);
loader.ReadDirect(m_FiveStarDieCountStrDicID,(tint32)ID_FIVESTARDIECOUNTSTRDICID);
loader.ReadDirect(m_FiveStarTimeStrDicID,(tint32)ID_FIVESTARTIMESTRDICID);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_Number,(tint32)ID_NUMBER);
loader.ReadDirect(m_StartTime,(tint32)ID_STARTTIME);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_CopySceneRule);



