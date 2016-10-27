//This code create by CodeEngine,don't modify
#include "Table_SnareObjInfo.h"



















bool Table_SnareObjInfo::__Load(DBC_Loader & loader)
 {
 __ENTER_FUNCTION
 
 AssertEx(ID_TAB_CURCOL_COUNT==loader.GetFieldsNum(), "SnareObjInfo Columns Differ"); 
 loader.ReadDirect(m_ActivateEffectId,(tint32)ID_ACTIVATEEFFECTID);
loader.ReadDirect(m_ActivateModel,(tint32)ID_ACTIVATEMODEL);
loader.ReadDirect(m_ActivateRadius,(tint32)ID_ACTIVATERADIUS);
loader.ReadDirect(m_ActivateSound,(tint32)ID_ACTIVATESOUND);
loader.ReadDirect(m_AliveEffectId[0],(tint32)ID_ALIVEEFFECTID1);
loader.ReadDirect(m_AliveEffectId[1],(tint32)ID_ALIVEEFFECTID2);
loader.ReadDirect(m_AliveEffectId[2],(tint32)ID_ALIVEEFFECTID3);
loader.ReadDirect(m_AliveSoundId[0],(tint32)ID_ALIVESOUNDID1);
loader.ReadDirect(m_AliveSoundId[1],(tint32)ID_ALIVESOUNDID2);
loader.ReadDirect(m_AliveSoundId[2],(tint32)ID_ALIVESOUNDID3);
loader.ReadDirect(m_BUffIndex[0],(tint32)ID_BUFFINDEX1);
loader.ReadDirect(m_BUffIndex[1],(tint32)ID_BUFFINDEX2);
loader.ReadDirect(m_BUffIndex[2],(tint32)ID_BUFFINDEX3);
loader.ReadDirect(m_BUffIndex[3],(tint32)ID_BUFFINDEX4);
loader.ReadDirect(m_BUffIndex[4],(tint32)ID_BUFFINDEX5);
loader.ReadDirect(m_BUffIndex[5],(tint32)ID_BUFFINDEX6);
loader.ReadDirect(m_CharModelId,(tint32)ID_CHARMODELID);
loader.ReadDirect(m_DeadEffectId,(tint32)ID_DEADEFFECTID);
loader.ReadDirect(m_DeadSound,(tint32)ID_DEADSOUND);
loader.ReadDirect(m_DelayTime,(tint32)ID_DELAYTIME);
loader.ReadDirect(m_Id,(tint32)ID_ID);
loader.ReadDirect(m_IsActivateCanSee,(tint32)ID_ISACTIVATECANSEE);
loader.ReadDirect(m_IsDelOwnerLeave,(tint32)ID_ISDELOWNERLEAVE);
loader.ReadDirect(m_IsOwnerCanSee,(tint32)ID_ISOWNERCANSEE);
loader.ReadDirect(m_LifeTime,(tint32)ID_LIFETIME);
loader.ReadDirect(m_StealthLev,(tint32)ID_STEALTHLEV);
loader.ReadDirect(m_TargetType,(tint32)ID_TARGETTYPE);

 return true;
 __LEAVE_FUNCTION
 return false;
 }


 DEFINE_SEQUENCE_TABLE_FUNCTIONS(Table_SnareObjInfo);



