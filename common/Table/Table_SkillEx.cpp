//This code create by CodeEngine,don't modify
#include "Table_SkillEx.h"

























bool Table_SkillEx::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SkillEx Columns Differ"); 
 loader.ReadDirect(m_BaseId,(tint32)ID_BASEID);
loader.ReadDirect(m_BulletEffectID[0],(tint32)ID_BULLETEFFECTID_01);
loader.ReadDirect(m_BulletEffectID[1],(tint32)ID_BULLETEFFECTID_02);
loader.ReadDirect(m_BulletEffectID[2],(tint32)ID_BULLETEFFECTID_03);
loader.ReadDirect(m_CDTimeId,(tint32)ID_CDTIMEID);
loader.ReadDirect(m_CameraRockId,(tint32)ID_CAMERAROCKID);
loader.ReadDirect(m_CameraRockRate,(tint32)ID_CAMERAROCKRATE);
loader.ReadDirect(m_DelNum,(tint32)ID_DELNUM);
loader.ReadDirect(m_DelType,(tint32)ID_DELTYPE);
loader.ReadDirect(m_Impact[0],(tint32)ID_IMPACT_01);
loader.ReadDirect(m_Impact[1],(tint32)ID_IMPACT_2);
loader.ReadDirect(m_Impact[2],(tint32)ID_IMPACT_03);
loader.ReadDirect(m_Impact[3],(tint32)ID_IMPACT_04);
loader.ReadDirect(m_Impact[4],(tint32)ID_IMPACT_05);
loader.ReadDirect(m_Impact[5],(tint32)ID_IMPACT_06);
loader.ReadDirect(m_LogicParam[0],(tint32)ID_LOGICPARAM01);
loader.ReadDirect(m_LogicParam[1],(tint32)ID_LOGICPARAM02);
loader.ReadDirect(m_LogicParam[2],(tint32)ID_LOGICPARAM03);
loader.ReadDirect(m_LogicParam[3],(tint32)ID_LOGICPARAM04);
loader.ReadDirect(m_NextSkillId,(tint32)ID_NEXTSKILLID);
loader.ReadDirect(m_Radius,(tint32)ID_RADIUS);
loader.ReadDirect(m_RangeEffectSize[0],(tint32)ID_RANGEEFFECTSIZE01);
loader.ReadDirect(m_RangeEffectSize[1],(tint32)ID_RANGEEFFECTSIZE02);
loader.ReadDirect(m_RangeEffectTarType,(tint32)ID_RANGEEFFECTTARTYPE);
loader.ReadDirect(m_RangeEffectType,(tint32)ID_RANGEEFFECTTYPE);
loader.ReadDirect(m_RefixThreat,(tint32)ID_REFIXTHREAT);
loader.ReadDirect(m_SatrtMotionId,(tint32)ID_SATRTMOTIONID);
loader.ReadDirect(m_SceneEffectId,(tint32)ID_SCENEEFFECTID);
loader.ReadDirect(m_SecondMotionId,(tint32)ID_SECONDMOTIONID);
loader.ReadDirect(m_SkillContinueTime,(tint32)ID_SKILLCONTINUETIME);
loader.ReadDirect(m_SkillDelayTime,(tint32)ID_SKILLDELAYTIME);
loader.ReadDirect(m_SkillDesc,(tint32)ID_SKILLDESC);
loader.ReadDirect(m_SkillExID,(tint32)ID_SKILLEXID);
loader.ReadDirect(m_SkillLogic,(tint32)ID_SKILLLOGIC);
loader.ReadDirect(m_Level,(tint32)ID_LEVEL);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_SkillEx);



