//This code create by CodeEngine,don't modify
#include "Table_RoleBaseAttr.h"

























bool Table_RoleBaseAttr::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "RoleBaseAttr Columns Differ"); 
 loader.ReadDirect(m_Attack,(tint32)ID_ATTACK);
loader.ReadDirect(m_AttackDisType,(tint32)ID_ATTACKDISTYPE);
loader.ReadDirect(m_AttackTime,(tint32)ID_ATTACKTIME);
loader.ReadDirect(m_Camp,(tint32)ID_CAMP);
loader.ReadDirect(m_CharModelID,(tint32)ID_CHARMODELID);
loader.ReadDirect(m_CorpseTime,(tint32)ID_CORPSETIME);
loader.ReadDirect(m_Defense,(tint32)ID_DEFENSE);
loader.ReadDirect(m_DieEffectID,(tint32)ID_DIEEFFECTID);
loader.ReadDirect(m_EnhanceID,(tint32)ID_ENHANCEID);
loader.ReadDirect(m_Exp,(tint32)ID_EXP);
loader.ReadDirect(m_Hit,(tint32)ID_HIT);
loader.ReadDirect(m_IsAttackFly,(tint32)ID_ISATTACKFLY);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);
loader.ReadDirect(m_MaxHP,(tint32)ID_MAXHP);
loader.ReadDirect(m_MaxXP,(tint32)ID_MAXXP);
loader.ReadDirect(m_MoveSpeed,(tint32)ID_MOVESPEED);
loader.ReadDirect(m_Name,(tint32)ID_NAME);
loader.ReadDirect(m_RampType,(tint32)ID_RAMPTYPE);
loader.ReadDirect(m_SelectRadius,(tint32)ID_SELECTRADIUS);
loader.ReadDirect(m_Sex,(tint32)ID_SEX);
loader.ReadDirect(m_SkillstrategyIndex,(tint32)ID_SKILLSTRATEGYINDEX);
loader.ReadDirect(m_UnitDataID,(tint32)ID_UNITDATAID);
loader.ReadDirect(m_XpSpeed,(tint32)ID_XPSPEED);
loader.ReadDirect(m_T,(tint32)ID_T);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_RoleBaseAttr);



