//This code create by CodeEngine,don't modify
#include "Table_Impact.h"



















bool Table_Impact::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "Impact Columns Differ"); 
 loader.ReadDirect(m_BuffIcon,(tint32)ID_BUFFICON);
loader.ReadDirect(m_BuffType,(tint32)ID_BUFFTYPE);
loader.ReadDirect(m_DebuffPRI,(tint32)ID_DEBUFFPRI);
loader.ReadDirect(m_DelayTime,(tint32)ID_DELAYTIME);
loader.ReadDirect(m_EffectId,(tint32)ID_EFFECTID);
loader.ReadDirect(m_FadeOutRule,(tint32)ID_FADEOUTRULE);
loader.ReadDirect(m_ImpactID,(tint32)ID_IMPACTID);
loader.ReadDirect(m_IsForever,(tint32)ID_ISFOREVER);
loader.ReadDirect(m_IsNeedNoticeClient,(tint32)ID_ISNEEDNOTICECLIENT);
loader.ReadDirect(m_IsRemoveEffectFadeOut,(tint32)ID_ISREMOVEEFFECTFADEOUT);
loader.ReadDirect(m_LifeType,(tint32)ID_LIFETYPE);
loader.ReadDirect(m_LogicID,(tint32)ID_LOGICID);
loader.ReadDirect(m_MaxOverlayCount,(tint32)ID_MAXOVERLAYCOUNT);
loader.ReadDirect(m_MutexcollectionId,(tint32)ID_MUTEXCOLLECTIONID);
loader.ReadDirect(m_Mutexpriority,(tint32)ID_MUTEXPRIORITY);
loader.ReadDirect(m_Name,(tint32)ID_NAME);
loader.ReadDirect(m_ParamValue[0],(tint32)ID_PARAMVALUE_01);
loader.ReadDirect(m_ParamValue[1],(tint32)ID_PARAMVALUE_02);
loader.ReadDirect(m_ParamValue[2],(tint32)ID_PARAMVALUE_03);
loader.ReadDirect(m_ParamValue[3],(tint32)ID_PARAMVALUE_04);
loader.ReadDirect(m_ParamValue[4],(tint32)ID_PARAMVALUE_05);
loader.ReadDirect(m_ParamValue[5],(tint32)ID_PARAMVALUE_06);
loader.ReadDirect(m_ParamValue[6],(tint32)ID_PARAMVALUE_07);
loader.ReadDirect(m_ParamValue[7],(tint32)ID_PARAMVALUE_08);
loader.ReadDirect(m_ParamValue[8],(tint32)ID_PARAMVALUE_09);
loader.ReadDirect(m_ParamValue[9],(tint32)ID_PARAMVALUE_10);
loader.ReadDirect(m_ParamValue[10],(tint32)ID_PARAMVALUE_11);
loader.ReadDirect(m_ParamValue[11],(tint32)ID_PARAMVALUE_12);
loader.ReadDirect(m_ParamValue[12],(tint32)ID_PARAMVALUE_13);
loader.ReadDirect(m_ParamValue[13],(tint32)ID_PARAMVALUE_14);
loader.ReadDirect(m_ParamValue[14],(tint32)ID_PARAMVALUE_15);
loader.ReadDirect(m_PlayTime,(tint32)ID_PLAYTIME);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_HASH_TABLE_FUNCTIONS(Table_Impact);



