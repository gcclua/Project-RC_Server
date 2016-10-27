//This code create by CodeEngine,don't modify
#include "Table_NpcSkillStrategy.h"






bool Table_NpcSkillStrategy::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "NpcSkillStrategy Columns Differ"); 
 loader.ReadDirect(m_DefaultSkillId,(tint32)ID_DEFAULTSKILLID);
loader.ReadDirect(m_DefaultSkillWeight,(tint32)ID_DEFAULTSKILLWEIGHT);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_IsHaveOptionalSkill,(tint32)ID_ISHAVEOPTIONALSKILL);
loader.ReadDirect(m_SkillId[0],(tint32)ID_SKILLID1);
loader.ReadDirect(m_SkillId[1],(tint32)ID_SKILLID2);
loader.ReadDirect(m_SkillId[2],(tint32)ID_SKILLID3);
loader.ReadDirect(m_SkillId[3],(tint32)ID_SKILLID4);
loader.ReadDirect(m_SkillId[4],(tint32)ID_SKILLID5);
loader.ReadDirect(m_SkillId[5],(tint32)ID_SKILLID6);
loader.ReadDirect(m_SkillId[6],(tint32)ID_SKILLID7);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_NpcSkillStrategy);



