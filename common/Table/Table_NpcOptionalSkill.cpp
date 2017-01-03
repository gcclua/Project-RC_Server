//This code create by CodeEngine,don't modify
#include "Table_NpcOptionalSkill.h"





bool Table_NpcOptionalSkill::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "NpcOptionalSkill Columns Differ"); 
 loader.ReadDirect(m_ActivateLogic,(tint32)ID_ACTIVATELOGIC);
loader.ReadDirect(m_ActivateParam[0],(tint32)ID_ACTIVATEPARAM1);
loader.ReadDirect(m_ActivateParam[1],(tint32)ID_ACTIVATEPARAM2);
loader.ReadDirect(m_SeleTargetLogic,(tint32)ID_SELETARGETLOGIC);
loader.ReadDirect(m_SkillId,(tint32)ID_SKILLID);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_NpcOptionalSkill);



