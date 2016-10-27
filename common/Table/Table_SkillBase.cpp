//This code create by CodeEngine,don't modify
#include "Table_SkillBase.h"





















bool Table_SkillBase::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SkillBase Columns Differ"); 
 loader.ReadDirect(m_Icon ,(tint32)ID_ICON );
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_IsAutoSelectTar,(tint32)ID_ISAUTOSELECTTAR);
loader.ReadDirect(m_IsBreakBeAttacked,(tint32)ID_ISBREAKBEATTACKED);
loader.ReadDirect(m_IsMove,(tint32)ID_ISMOVE);
loader.ReadDirect(m_IsMoveBreak,(tint32)ID_ISMOVEBREAK);
loader.ReadDirect(m_IsMoveToTarInAutoCombat,(tint32)ID_ISMOVETOTARINAUTOCOMBAT);
loader.ReadDirect(m_IsNeedStopEffectId,(tint32)ID_ISNEEDSTOPEFFECTID);
loader.ReadDirect(m_IsNeedWeapon,(tint32)ID_ISNEEDWEAPON);
loader.ReadDirect(m_IsPlayAttackSound,(tint32)ID_ISPLAYATTACKSOUND);
loader.ReadDirect(m_IsShowSkillName,(tint32)ID_ISSHOWSKILLNAME);
loader.ReadDirect(m_IsSkillBreak,(tint32)ID_ISSKILLBREAK);
loader.ReadDirect(m_IsTargetDieBreak,(tint32)ID_ISTARGETDIEBREAK);
loader.ReadDirect(m_Name,(tint32)ID_NAME);
loader.ReadDirect(m_PriorityAutoFight,(tint32)ID_PRIORITYAUTOFIGHT);
loader.ReadDirect(m_ProfessionId,(tint32)ID_PROFESSIONID);
loader.ReadDirect(m_SelLogic,(tint32)ID_SELLOGIC);
loader.ReadDirect(m_SkillClass,(tint32)ID_SKILLCLASS);
loader.ReadDirect(m_TargetType,(tint32)ID_TARGETTYPE);
loader.ReadDirect(m_UseType,(tint32)ID_USETYPE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_SkillBase);



