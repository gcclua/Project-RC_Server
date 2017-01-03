//This code create by CodeEngine,don't modify
#include "Table_InitialCombatAttr.h"





















bool Table_InitialCombatAttr::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "InitialCombatAttr Columns Differ"); 
 loader.ReadDirect(m_AttackSpeed,(tint32)ID_ATTACKSPEED);
loader.ReadDirect(m_CritiAdd,(tint32)ID_CRITIADD);
loader.ReadDirect(m_CritiMis,(tint32)ID_CRITIMIS);
loader.ReadDirect(m_Critical,(tint32)ID_CRITICAL);
loader.ReadDirect(m_DeCritical,(tint32)ID_DECRITICAL);
loader.ReadDirect(m_Dodge,(tint32)ID_DODGE);
loader.ReadDirect(m_Ductical,(tint32)ID_DUCTICAL);
loader.ReadDirect(m_Hit,(tint32)ID_HIT);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);
loader.ReadDirect(m_MAttack,(tint32)ID_MATTACK);
loader.ReadDirect(m_MaxHp,(tint32)ID_MAXHP);
loader.ReadDirect(m_MaxMP,(tint32)ID_MAXMP);
loader.ReadDirect(m_MaxXP,(tint32)ID_MAXXP);
loader.ReadDirect(m_Mdefense,(tint32)ID_MDEFENSE);
loader.ReadDirect(m_MoveSpeed,(tint32)ID_MOVESPEED);
loader.ReadDirect(m_PAttack,(tint32)ID_PATTACK);
loader.ReadDirect(m_PDefense,(tint32)ID_PDEFENSE);
loader.ReadDirect(m_ProfessionId,(tint32)ID_PROFESSIONID);
loader.ReadDirect(m_Strike,(tint32)ID_STRIKE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_InitialCombatAttr);



