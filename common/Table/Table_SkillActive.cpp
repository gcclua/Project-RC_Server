//This code create by CodeEngine,don't modify
#include "Table_SkillActive.h"





bool Table_SkillActive::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SkillActive Columns Differ"); 
 loader.ReadDirect(m_Index,(tint32)ID_INDEX);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);
loader.ReadDirect(m_SKillIndex,(tint32)ID_SKILLINDEX);
loader.ReadDirect(m_SkillId,(tint32)ID_SKILLID);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_SkillActive);



